/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "dcmtk/config/osconfig.h"    /* make sure OS specific configuration is included first */

#define INCLUDE_CSTDIO
#define INCLUDE_CSTRING
#include "dcmtk/ofstd/ofstdinc.h"

#include "dcmtk/dcmdata/dcdicent.h"

/*
** DcmDictEntry member functions
*/

static
char* strdup_new(const char* str)
{
    char* s = NULL;
    if (str != NULL) {
        s = new char[strlen(str)+1];
        strcpy(s, str);
    }
    return s;
}

DcmDictEntry::DcmDictEntry(Uint16 g, Uint16 e, DcmVR vr, 
        const char* nam, int vmMin, int vmMax,
        const char* vers, OFBool doCopyStrings, 
        const char* pcreator)
  : DcmTagKey(g,e),
    upperKey(),
    valueRepresentation(EVR_UNKNOWN),
    tagName(nam),
    valueMultiplicityMin(vmMin),
    valueMultiplicityMax(vmMax),
    standardVersion(vers),
    stringsAreCopies(doCopyStrings),
    groupRangeRestriction(DcmDictRange_Unspecified),
    elementRangeRestriction(DcmDictRange_Unspecified),
    privateCreator(pcreator)
{
    upperKey.set(g,e);  /* default: make upper key same as normal key */
    valueRepresentation.setVR(vr);
    if (doCopyStrings) {
        tagName = strdup_new(nam);
        standardVersion = strdup_new(vers);
        privateCreator = strdup_new(pcreator);
    }
}

DcmDictEntry::DcmDictEntry(Uint16 g, Uint16 e, Uint16 ug, Uint16 ue, DcmVR vr, 
        const char* nam, int vmMin, int vmMax,
        const char* vers, OFBool doCopyStrings, 
        const char* pcreator)
  : DcmTagKey(g,e),
    upperKey(),
    valueRepresentation(EVR_UNKNOWN),
    tagName(nam),
    valueMultiplicityMin(vmMin),
    valueMultiplicityMax(vmMax),
    standardVersion(vers),
    stringsAreCopies(doCopyStrings),
    groupRangeRestriction(DcmDictRange_Unspecified),
    elementRangeRestriction(DcmDictRange_Unspecified),
    privateCreator(pcreator)
{
    upperKey.set(ug, ue);
    valueRepresentation.setVR(vr);
    if (doCopyStrings) {
        tagName = strdup_new(nam);
        standardVersion = strdup_new(vers);
        privateCreator = strdup_new(pcreator);
    }
}

DcmDictEntry::DcmDictEntry(const DcmDictEntry& e)
  : DcmTagKey(e),
    upperKey(e.upperKey),
    valueRepresentation(e.valueRepresentation),
    tagName(e.tagName),
    valueMultiplicityMin(e.valueMultiplicityMin),
    valueMultiplicityMax(e.valueMultiplicityMax),
    standardVersion(e.standardVersion),
    stringsAreCopies(e.stringsAreCopies),
    groupRangeRestriction(e.groupRangeRestriction),
    elementRangeRestriction(e.elementRangeRestriction),
    privateCreator(e.privateCreator)
{
    if (stringsAreCopies)
    {
        tagName = strdup_new(e.tagName);
        standardVersion = strdup_new(e.standardVersion);
        privateCreator = strdup_new(e.privateCreator);
    }
}


DcmDictEntry::~DcmDictEntry()
{
    if (stringsAreCopies) {
        /* we have allocated them so it is ok to deallocate them */
        delete[] OFconst_cast(char *, tagName);
        delete[] OFconst_cast(char *, standardVersion);
        delete[] OFconst_cast(char *, privateCreator);
    }
}

/*
** DcmDictEntry friend functions
*/

STD_NAMESPACE ostream& operator<<(STD_NAMESPACE ostream& s, const DcmDictEntry& e) {

    const DcmDictEntry* ep = &e;
    if (ep == NULL) {
        s << "(nil)";
        return s;
    }

    char tagBuf[16];

    sprintf(tagBuf, "(%04x", e.getGroup());
    s << tagBuf;
    if (e.isRepeatingGroup()) {
        sprintf(tagBuf, "-%04x", e.getUpperGroup());
        s << tagBuf;
    }
    sprintf(tagBuf, ",%04x", e.getElement());
    s << tagBuf;
    if (e.isRepeatingElement()) {
        sprintf(tagBuf, "-%04x", e.getUpperElement());
        s << tagBuf;
    }
    s << ")";


    s << " " << e.getVR().getVRName() << " \"" << e.getTagName() << "\" ";
    if (e.isFixedSingleVM()) {
        s << "vm=" << e.getVMMax() << " ";
    } else if (e.isVariableRangeVM()) {
        s << "vm=" << e.getVMMin() << "-n ";
    } else if (e.isFixedRangeVM()){
        s << "vm=" << e.getVMMin() << "-" << e.getVMMax() << " ";
    } else {
        s << "vm=?(" <<  e.getVMMin() << "-" << e.getVMMax() << ")? ";
    }
    if (e.getStandardVersion() != NULL) {
        s << " Version=\"" << e.getStandardVersion() << "\" ";
    }
    if (e.getPrivateCreator() != NULL) {
        s << " priv=\"" << e.getPrivateCreator() << "\" ";
    }

    return s;
}