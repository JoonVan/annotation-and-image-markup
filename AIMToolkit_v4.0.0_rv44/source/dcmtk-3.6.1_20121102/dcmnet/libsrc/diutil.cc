/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "dcmtk/config/osconfig.h"    /* make sure OS specific configuration is included first */

#define INCLUDE_CSTDLIB
#define INCLUDE_CSTDIO
#define INCLUDE_CSTRING
#define INCLUDE_CCTYPE
#include "dcmtk/ofstd/ofstdinc.h"

#ifdef HAVE_UNIX_H
#if defined(macintosh) && defined (HAVE_WINSOCK_H)
/* unix.h defines timeval incompatible with winsock.h */
#define timeval _UNWANTED_timeval
#endif
#include <unix.h>       /* for unlink() under Metrowerks C++ (Macintosh) */
#undef timeval
#endif
#ifdef HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif
#ifdef HAVE_SYS_STAT_H
#include <sys/stat.h>
#endif
#ifdef HAVE_STAT_H
#include <stat.h>
#endif

#include "dcmtk/dcmnet/diutil.h"
#include "dcmtk/dcmdata/dcdatset.h"
#include "dcmtk/dcmdata/dcfilefo.h"
#include "dcmtk/dcmdata/dcmetinf.h"
#include "dcmtk/dcmdata/dcdeftag.h"
#include "dcmtk/dcmdata/dcuid.h"
#include "dcmtk/dcmdata/dcbytstr.h"

static char staticBuf[256];

OFLogger DCM_dcmnetLogger = OFLog::getLogger(DCMNET_LOGGER_NAME);

#define TO_UCHAR(s) OFstatic_cast(unsigned char, (s))
void
DU_stripTrailingSpaces(char *s)
{
    int i, n;

    if (s)
    {
        n = strlen(s);
        for (i = n - 1; i >= 0 && isspace(TO_UCHAR(s[i])); i--)
            s[i] = '\0';
    }
}

void
DU_stripLeadingSpaces(char *s)
{
    int i, j, n;

    if (s == NULL) return;
    n = strlen(s);
    if (n == 0) return;
    if (!isspace(s[0])) return; /* no leading space */

    /* first non-space */
    for (i=0; i<n && isspace(TO_UCHAR(s[i])); i++)
        /* do nothing, just iterate */
        ;
    if (i<n) {
        /* found non-space, pull to front (inclusive '\0') */
        for (j=i; j<=n; j++) {
            s[j-i] = s[j];
        }
    } else {
        /* all spaces */
        s[0] = '\0';
    }
}

void
DU_stripLeadingAndTrailingSpaces(char *s)
{
    DU_stripLeadingSpaces(s);
    DU_stripTrailingSpaces(s);
}
#undef TO_UCHAR

OFBool
DU_getStringDOElement(DcmItem *obj, DcmTagKey t, char *s)
{
    DcmByteString *elem;
    DcmStack stack;
    OFCondition ec = EC_Normal;
    char* aString;

    ec = obj->search(t, stack);
    elem = (DcmByteString*) stack.top();
    if (ec == EC_Normal && elem != NULL) {
        if (elem->getLength() == 0) {
            s[0] = '\0';
        } else {
            ec =  elem->getString(aString);
            strcpy(s, aString);
        }
    }
    return (ec == EC_Normal);
}

OFBool
DU_putStringDOElement(DcmItem *obj, DcmTagKey t, const char *s)
{
    OFCondition ec = EC_Normal;
    DcmElement *e = NULL;
    DcmTag tag(t);

    ec = newDicomElement(e, tag);
    if (ec == EC_Normal && s != NULL) {
        ec = e->putString(s);
    }
    if (ec == EC_Normal) {
        ec = obj->insert(e, OFTrue);
    }

    return (ec == EC_Normal);
}

OFBool
DU_getShortDOElement(DcmItem *obj, DcmTagKey t, Uint16 *us)
{
    DcmElement *elem;
    DcmStack stack;
    OFCondition ec = EC_Normal;

    ec = obj->search(t, stack);
    elem = (DcmElement*) stack.top();
    if (ec == EC_Normal && elem != NULL) {
        ec = elem->getUint16(*us, 0);
    }

    return (ec == EC_Normal);
}

OFBool
DU_putShortDOElement(DcmItem *obj, DcmTagKey t, Uint16 us)
{
    OFCondition ec = EC_Normal;
    DcmElement *e = NULL;
    DcmTag tag(t);

    ec = newDicomElement(e, tag);
    if (ec == EC_Normal) {
        ec = e->putUint16(us);
    }
    if (ec == EC_Normal) {
        ec = obj->insert(e, OFTrue);
    }
    return (ec == EC_Normal);
}

OFBool
DU_findSOPClassAndInstanceInDataSet(
  DcmItem *obj,
  char* sopClass,
  char* sopInstance,
  OFBool tolerateSpacePaddedUIDs)
{
    OFBool result = (DU_getStringDOElement(obj, DCM_SOPClassUID, sopClass) &&
        DU_getStringDOElement(obj, DCM_SOPInstanceUID, sopInstance));

    if (tolerateSpacePaddedUIDs)
    {
        /* gracefully correct space-padded UID strings */
        int slength;

        if ((0 < (slength=strlen(sopClass)))&&(sopClass[slength-1]==' '))
            sopClass[slength-1]=0;
        if ((0 < (slength=strlen(sopInstance)))&&(sopInstance[slength-1]==' '))
            sopInstance[slength-1]=0;
    }
    return result;
}

OFBool
DU_findSOPClassAndInstanceInFile(
  const char *fname,
  char* sopClass,
  char* sopInstance,
  OFBool tolerateSpacePaddedUIDs)
{
    DcmFileFormat ff;
    if (! ff.loadFile(fname, EXS_Unknown, EGL_noChange).good())
        return OFFalse;

    /* look in the meta-header first */
    OFBool found = DU_findSOPClassAndInstanceInDataSet(
        ff.getMetaInfo(), sopClass, sopInstance, tolerateSpacePaddedUIDs);

    if (!found) {
        found = DU_findSOPClassAndInstanceInDataSet(
            ff.getDataset(), sopClass, sopInstance, tolerateSpacePaddedUIDs);
    }

    return found;
}

const char *
DU_cechoStatusString(Uint16 statusCode)
{
    const char *s = NULL;

    if (statusCode == STATUS_Success)
        s = "Success";
    else {
        sprintf(staticBuf, "Unknown Status: 0x%x", (unsigned int)statusCode);
        s = staticBuf;
    }
    return s;
}

const char *
DU_cstoreStatusString(Uint16 statusCode)
{
    const char *s = NULL;

    switch (statusCode) {
      case STATUS_Success:
          s = "Success";
          break;
      case STATUS_STORE_Warning_CoersionOfDataElements:
          s = "Warning: CoersionOfDataElements";
          break;
      case STATUS_STORE_Warning_DataSetDoesNotMatchSOPClass:
          s = "Warning: DataSetDoesNotMatchSOPClass";
          break;
      case STATUS_STORE_Warning_ElementsDiscarded:
          s = "Warning: ElementsDiscarded";
          break;
    }
    if (s)
        return s;

    switch (statusCode & 0xff00) {      /* high byte significant */
      case STATUS_STORE_Refused_OutOfResources:   /* high byte */
          s = "Refused: OutOfResources";
          break;
      case STATUS_STORE_Refused_SOPClassNotSupported:     /* high byte */
          s = "Error: SOPClassNotSupported";
          break;
      case STATUS_STORE_Error_DataSetDoesNotMatchSOPClass:        /* high byte */
          s = "Error: DataSetDoesNotMatchSOPClass";
          break;
    }
    if (s)
        return s;

    switch (statusCode & 0xf000) {      /* high nibble significant */
      case STATUS_STORE_Error_CannotUnderstand:   /* high nibble */
          s = "Error: CannotUnderstand";
          break;
    }

    if (s == NULL) {
        sprintf(staticBuf, "Unknown Status: 0x%x", (unsigned int)statusCode);
        s = staticBuf;
    }
    return s;
}


const char *
DU_cfindStatusString(Uint16 statusCode)
{
    const char *s = NULL;

    switch (statusCode) {
      case STATUS_Success:
          s = "Success";
          break;
      case STATUS_Pending:
          s = "Pending";
          break;
      case STATUS_FIND_Refused_OutOfResources:
          s = "Refused: OutOfResources";
          break;
      case STATUS_FIND_Refused_SOPClassNotSupported:
          s = "Refused: SOPClassNotSupported";
          break;
      case STATUS_FIND_Failed_IdentifierDoesNotMatchSOPClass:
          s = "Failed: IdentifierDoesNotMatchSOPClass";
          break;
      case STATUS_FIND_Cancel_MatchingTerminatedDueToCancelRequest:
          s = "Cancel: MatchingTerminatedDueToCancelRequest";
          break;
      case STATUS_FIND_Pending_WarningUnsupportedOptionalKeys:
          s = "Pending: WarningUnsupportedOptionalKeys";
          break;
    }
    if (s)
        return s;

    switch (statusCode & 0xf000) {      /* high nibble significant */
    case STATUS_FIND_Failed_UnableToProcess:    /* high nibble */
        s = "Failed: UnableToProcess";
        break;
    }

    if (s == NULL) {
        sprintf(staticBuf, "Unknown Status: 0x%x", (unsigned int)statusCode);
        s = staticBuf;
    }
    return s;
}

const char *
DU_cmoveStatusString(Uint16 statusCode)
{
    const char *s = NULL;

    switch (statusCode) {
      case STATUS_Success:
          s = "Success";
          break;
      case STATUS_Pending:
          s = "Pending";
          break;
      case STATUS_MOVE_Refused_OutOfResourcesNumberOfMatches:
          s = "Refused: OutOfResourcesNumberOfMatches";
          break;
      case STATUS_MOVE_Refused_OutOfResourcesSubOperations:
          s = "Refused: OutOfResourcesSubOperations";
          break;
      case STATUS_MOVE_Failed_SOPClassNotSupported:
          s = "Failed: SOPClassNotSupported";
          break;
      case STATUS_MOVE_Failed_MoveDestinationUnknown:
          s = "Failed: MoveDestinationUnknown";
          break;
      case STATUS_MOVE_Failed_IdentifierDoesNotMatchSOPClass:
          s = "Failed: IdentifierDoesNotMatchSOPClass";
          break;
      case STATUS_MOVE_Cancel_SubOperationsTerminatedDueToCancelIndication:
          s = "Cancel: SubOperationsTerminatedDueToCancelIndication";
          break;
      case STATUS_MOVE_Warning_SubOperationsCompleteOneOrMoreFailures:
          s = "Warning: SubOperationsCompleteOneOrMoreFailures";
          break;

    }
    if (s)
        return s;

    switch (statusCode & 0xf000) {      /* high nibble significant */
      case STATUS_MOVE_Failed_UnableToProcess:    /* high nibble */
          s = "Failed: UnableToProcess";
          break;
    }

    if (s == NULL) {
        sprintf(staticBuf, "Unknown Status: 0x%x", (unsigned int)statusCode);
        s = staticBuf;
    }
    return s;
}

const char *
DU_cgetStatusString(Uint16 statusCode)
{
    const char *s = NULL;

    switch (statusCode) {
      case STATUS_Success:
          s = "Success";
          break;
      case STATUS_Pending:
          s = "Pending";
          break;
      case STATUS_GET_Refused_OutOfResourcesNumberOfMatches:
          s = "Refused: OutOfResourcesNumberOfMatches";
          break;
      case STATUS_GET_Refused_OutOfResourcesSubOperations:
          s = "Refused: OutOfResourcesSubOperations";
          break;
      case STATUS_GET_Failed_SOPClassNotSupported:
          s = "Failed: SOPClassNotSupported";
          break;
      case STATUS_GET_Failed_IdentifierDoesNotMatchSOPClass:
          s = "Failed: IdentifierDoesNotMatchSOPClass";
          break;
      case STATUS_GET_Cancel_SubOperationsTerminatedDueToCancelIndication:
          s = "Cancel: SubOperationsTerminatedDueToCancelIndication";
          break;
      case STATUS_GET_Warning_SubOperationsCompleteOneOrMoreFailures:
          s = "Warning: SubOperationsCompleteOneOrMoreFailures";
          break;

    }
    if (s)
        return s;

    switch (statusCode & 0xf000) {      /* high nibble significant */
      case STATUS_GET_Failed_UnableToProcess:    /* high nibble */
          s = "Failed: UnableToProcess";
          break;
    }

    if (s == NULL) {
        sprintf(staticBuf, "Unknown Status: 0x%x", (unsigned int)statusCode);
        s = staticBuf;
    }
    return s;
}

const char *
DU_ncreateStatusString(Uint16 statusCode)
{
    const char *s = NULL;

    switch (statusCode) {
      case STATUS_Success:
          s = "Success";
          break;
      case STATUS_N_ClassInstanceConflict:
          s = "Failure: ClassInstanceConflict";
          break;
      case STATUS_N_DuplicateInvocation:
          s = "Failure: DuplicateInvocation";
          break;
      case STATUS_N_DuplicateSOPInstance:
          s = "Failure: DuplicateSOPInstance";
          break;
      case STATUS_N_InvalidAttributeValue:
          s = "Failure: InvalidAttributeValue";
          break;
      case STATUS_N_InvalidObjectInstance:
          s = "Failure: InvalidObjectInstance";
          break;
      case STATUS_N_MissingAttribute:
          s = "Failure: MissingAttribute";
          break;
      case STATUS_N_MissingAttributeValue:
          s = "Failure: MissingAttributeValue";
          break;
      case STATUS_N_MistypedArgument:
          s = "Failure: MistypedArgument";
          break;
      case STATUS_N_NoSuchAttribute:
          s = "Failure: NoSuchAttribute";
          break;
      case STATUS_N_NoSuchSOPClass:
          s = "Failure: NoSuchSOPClass";
          break;
      case STATUS_N_NoSuchObjectInstance:
          s = "Failure: NoSuchObjectInstance";
          break;
      case STATUS_N_ProcessingFailure:
          s = "Failure: ProcessingFailure";
          break;
      case STATUS_N_ResourceLimitation:
          s = "Failure: ResourceLimitation";
          break;
      case STATUS_N_UnrecognizedOperation:
          s = "Failure: UnrecognizedOperation";
          break;
      case STATUS_N_AttributeValueOutOfRange:
          s = "Warning: AttributeValueOutOfRange";
          break;
    }
    if (s)
          return s;

    switch (statusCode & 0xf000) {        /* high nibble significant */
      case STATUS_FIND_Failed_UnableToProcess:    /* high nibble */
          s = "Failed: UnableToProcess";
          break;
    }

    if (s == NULL) {
        sprintf(staticBuf, "Unknown Status: 0x%x", (unsigned int)statusCode);
        s = staticBuf;
    }
    return s;
}

const char *
DU_ngetStatusString(Uint16 statusCode)
{
    const char *s = NULL;

    switch (statusCode) {
      case STATUS_Success:
          s = "Success";
          break;
      case STATUS_N_ClassInstanceConflict:
          s = "Failure: ClassInstanceConflict";
          break;
      case STATUS_N_DuplicateInvocation:
          s = "Failure: DuplicateInvocation";
          break;
      case STATUS_N_InvalidObjectInstance:
          s = "Failure: InvalidObjectInstance";
          break;
      case STATUS_N_MistypedArgument:
          s = "Failure: MistypedArgument";
          break;
      case STATUS_N_NoSuchSOPClass:
          s = "Failure: NoSuchSOPClass";
          break;
      case STATUS_N_NoSuchObjectInstance:
          s = "Failure: NoSuchObjectInstance";
          break;
      case STATUS_N_ProcessingFailure:
          s = "Failure: ProcessingFailure";
          break;
      case STATUS_N_ResourceLimitation:
          s = "Failure: ResourceLimitation";
          break;
      case STATUS_N_AttributeListError:
          s = "Warning: AttributeListError";
          break;
      case STATUS_N_AttributeValueOutOfRange:
          s = "Warning: AttributeValueOutOfRange";
          break;
    }
    if (s)
        return s;

    switch (statusCode & 0xf000) {        /* high nibble significant */
      case STATUS_FIND_Failed_UnableToProcess:    /* high nibble */
          s = "Failed: UnableToProcess";
          break;
    }

    if (s == NULL) {
          sprintf(staticBuf, "Unknown Status: 0x%x", (unsigned int)statusCode);
          s = staticBuf;
    }
    return s;
}

const char *
DU_nsetStatusString(Uint16 statusCode)
{
    const char *s = NULL;

    switch (statusCode) {
      case STATUS_Success:
          s = "Success";
          break;
      case STATUS_N_ClassInstanceConflict:
          s = "Failure: ClassInstanceConflict";
          break;
      case STATUS_N_DuplicateInvocation:
          s = "Failure: DuplicateInvocation";
          break;
      case STATUS_N_InvalidAttributeValue:
          s = "Failure: InvalidAttributeValue";
          break;
      case STATUS_N_MistypedArgument:
          s = "Failure: MistypedArgument";
          break;
      case STATUS_N_InvalidObjectInstance:
          s = "Failure: InvalidObjectInstance";
          break;
      case STATUS_N_MissingAttributeValue:
          s = "Failure: MissingAttributeValue";
          break;
      case STATUS_N_NoSuchAttribute:
          s = "Failure: NoSuchAttribute";
          break;
      case STATUS_N_NoSuchSOPClass:
          s = "Failure: NoSuchSOPClass";
          break;
      case STATUS_N_NoSuchObjectInstance:
          s = "Failure: NoSuchObjectInstance";
          break;
      case STATUS_N_ProcessingFailure:
          s = "Failure: ProcessingFailure";
          break;
      case STATUS_N_ResourceLimitation:
          s = "Failure: ResourceLimitation";
          break;
      case STATUS_N_UnrecognizedOperation:
          s = "Failure: UnrecognizedOperation";
          break;
      case STATUS_N_AttributeValueOutOfRange:
          s = "Warning: AttributeValueOutOfRange";
          break;
    }
    if (s)
        return s;

    switch (statusCode & 0xf000) {        /* high nibble significant */
      case STATUS_FIND_Failed_UnableToProcess:    /* high nibble */
          s = "Failed: UnableToProcess";
          break;
    }

    if (s == NULL) {
        sprintf(staticBuf, "Unknown Status: 0x%x", (unsigned int)statusCode);
        s = staticBuf;
    }
    return s;
}

const char *
DU_nactionStatusString(Uint16 statusCode)
{
    const char *s = NULL;

    switch (statusCode) {
      case STATUS_Success:
          s = "Success";
          break;
      case STATUS_N_ClassInstanceConflict:
          s = "Failure: ClassInstanceConflict";
          break;
      case STATUS_N_DuplicateInvocation:
          s = "Failure: DuplicateInvocation";
          break;
      case STATUS_N_InvalidArgumentValue:
          s = "Failure: InvalidArgumentValue";
          break;
      case STATUS_N_InvalidObjectInstance:
          s = "Failure: InvalidObjectInstance";
          break;
      case STATUS_N_MistypedArgument:
          s = "Failure: MistypedArgument";
          break;
      case STATUS_N_NoSuchAction:
          s = "Failure: NoSuchAction";
          break;
      case STATUS_N_NoSuchArgument:
          s = "Failure: NoSuchArgument";
          break;
      case STATUS_N_NoSuchSOPClass:
          s = "Failure: NoSuchSOPClass";
          break;
      case STATUS_N_NoSuchObjectInstance:
          s = "Failure: NoSuchObjectInstance";
          break;
      case STATUS_N_ProcessingFailure:
          s = "Failure: ProcessingFailure";
          break;
      case STATUS_N_ResourceLimitation:
          s = "Failure: ResourceLimitation";
          break;
      case STATUS_N_UnrecognizedOperation:
          s = "Failure: UnrecognizedOperation";
          break;
    }
    if (s)
        return s;

    switch (statusCode & 0xf000) {        /* high nibble significant */
      case STATUS_FIND_Failed_UnableToProcess:    /* high nibble */
          s = "Failed: UnableToProcess";
          break;
    }

    if (s == NULL) {
        sprintf(staticBuf, "Unknown Status: 0x%x", (unsigned int)statusCode);
        s = staticBuf;
    }
    return s;
}

const char *
DU_ndeleteStatusString(Uint16 statusCode)
{
    const char *s = NULL;

    switch (statusCode) {
      case STATUS_Success:
          s = "Success";
          break;
      case STATUS_N_ClassInstanceConflict:
          s = "Failure: ClassInstanceConflict";
          break;
      case STATUS_N_DuplicateInvocation:
          s = "Failure: DuplicateInvocation";
          break;
      case STATUS_N_InvalidObjectInstance:
          s = "Failure: InvalidObjectInstance";
          break;
      case STATUS_N_MistypedArgument:
          s = "Failure: MistypedArgument";
          break;
      case STATUS_N_NoSuchSOPClass:
          s = "Failure: NoSuchSOPClass";
          break;
      case STATUS_N_NoSuchObjectInstance:
          s = "Failure: NoSuchObjectInstance";
          break;
      case STATUS_N_ProcessingFailure:
          s = "Failure: ProcessingFailure";
          break;
      case STATUS_N_ResourceLimitation:
          s = "Failure: ResourceLimitation";
          break;
      case STATUS_N_UnrecognizedOperation:
          s = "Failure: UnrecognizedOperation";
          break;
    }
    if (s)
        return s;

    switch (statusCode & 0xf000) {        /* high nibble significant */
      case STATUS_FIND_Failed_UnableToProcess:    /* high nibble */
          s = "Failed: UnableToProcess";
          break;
    }

    if (s == NULL) {
        sprintf(staticBuf, "Unknown Status: 0x%x", (unsigned int)statusCode);
        s = staticBuf;
    }
    return s;
}

const char *
DU_neventReportStatusString(Uint16 statusCode)
{
    const char *s = NULL;

    switch (statusCode) {
      case STATUS_Success:
          s = "Success";
          break;
      case STATUS_N_ClassInstanceConflict:
          s = "Failure: ClassInstanceConflict";
          break;
      case STATUS_N_DuplicateInvocation:
          s = "Failure: DuplicateInvocation";
          break;
      case STATUS_N_InvalidArgumentValue:
          s = "Failure: InvalidArgumentValue";
          break;
      case STATUS_N_InvalidObjectInstance:
          s = "Failure: InvalidObjectInstance";
          break;
      case STATUS_N_MistypedArgument:
          s = "Failure: MistypedArgument";
          break;
      case STATUS_N_NoSuchArgument:
          s = "Failure: NoSuchArgument";
          break;
      case STATUS_N_NoSuchEventType:
          s = "Failure: NoSuchEventType";
          break;
      case STATUS_N_NoSuchSOPClass:
          s = "Failure: NoSuchSOPClass";
          break;
      case STATUS_N_NoSuchObjectInstance:
          s = "Failure: NoSuchObjectInstance";
          break;
      case STATUS_N_ProcessingFailure:
          s = "Failure: ProcessingFailure";
          break;
      case STATUS_N_ResourceLimitation:
          s = "Failure: ResourceLimitation";
          break;
      case STATUS_N_UnrecognizedOperation:
          s = "Failure: UnrecognizedOperation";
          break;
    }
    if (s)
        return s;

    switch (statusCode & 0xf000) {        /* high nibble significant */
      case STATUS_FIND_Failed_UnableToProcess:    /* high nibble */
          s = "Failed: UnableToProcess";
          break;
    }

    if (s == NULL) {
        sprintf(staticBuf, "Unknown Status: 0x%x", (unsigned int)statusCode);
        s = staticBuf;
    }
    return s;
}