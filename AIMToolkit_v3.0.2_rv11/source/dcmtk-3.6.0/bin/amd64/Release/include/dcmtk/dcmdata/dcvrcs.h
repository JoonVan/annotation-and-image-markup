/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#ifndef DCVRCS_H
#define DCVRCS_H

#include "dcmtk/config/osconfig.h"    /* make sure OS specific configuration is included first */

#include "dcmtk/dcmdata/dcbytstr.h"


/** a class representing the DICOM value representation 'Code String' (CS)
 */
class DcmCodeString
  : public DcmByteString
{

  public:

    /** constructor.
     *  Create new element from given tag and length.
     *  @param tag DICOM tag for the new element
     *  @param len value length for the new element
     */
    DcmCodeString(const DcmTag &tag,
                  const Uint32 len = 0);

    /** copy constructor
     *  @param old element to be copied
     */
    DcmCodeString(const DcmCodeString &old);

    /** destructor
     */
    virtual ~DcmCodeString();

    /** assignment operator
     *  @param obj element to be assigned/copied
     *  @return reference to this object
     */
    DcmCodeString &operator=(const DcmCodeString &obj);

    /** clone method
     *  @return deep copy of this object
     */
    virtual DcmObject *clone() const
    {
      return new DcmCodeString(*this);
    }

    /** Virtual object copying. This method can be used for DcmObject
     *  and derived classes to get a deep copy of an object. Internally
     *  the assignment operator is called if the given DcmObject parameter
     *  is of the same type as "this" object instance. If not, an error
     *  is returned. This function permits copying an object by value
     *  in a virtual way which therefore is different to just calling the
     *  assignment operator of DcmElement which could result in slicing
     *  the object.
     *  @param rhs - [in] The instance to copy from. Has to be of the same
     *                class type as "this" object
     *  @return EC_Normal if copying was successful, error otherwise
     */
    virtual OFCondition copyFrom(const DcmObject& rhs);

    /** get element type identifier
     *  @return type identifier of this class (EVR_CS)
     */
    virtual DcmEVR ident() const;

    /** check whether stored value conforms to the VR and to the specified VM
     *  @param vm value multiplicity (according to the data dictionary) to be checked for.
     *    (valid values: "1", "1-2", "1-3", "1-8", "1-99", "1-n", "2", "2-n", "2-2n",
     *                   "3", "3-n", "3-3n", "4", "6", "9", "16", "32")
     *  @param oldFormat parameter not used for this VR (only for DA, TM, PN)
     *  @return status of the check, EC_Normal if value is correct, an error code otherwise
     */
    virtual OFCondition checkValue(const OFString &vm = "1-n",
                                   const OFBool oldFormat = OFFalse);

    /** get a copy of a particular string component
     *  @param stringVal variable in which the result value is stored
     *  @param pos index of the value in case of multi-valued elements (0..vm-1)
     *  @param normalize delete leading and trailing spaces if OFTrue
     *  @return status, EC_Normal if successful, an error code otherwise
     */
    virtual OFCondition getOFString(OFString &stringVal,
                                    const unsigned long pos,
                                    OFBool normalize = OFTrue);

    /* --- static helper functions --- */

    /** check whether given value conforms to value representation CS (Code String).
     *  Valid characters are: A-Z, 0-9, _ and ' ' (space).  The maximum length is 16.
     *  NB: This method is only used by the DicomDirInterface class and might be
     *      replaced by the following method (checkStringValue) in the future.
     *  @param value string value to be checked (single value only)
     *  @param pos returns index of first invalid character (0..n-1) if not NULL.
     *    Points to trailing zero byte (eos) if value is valid.
     *  @param checkLength check maximum length if OFTrue, ignore length if OFFalse
     *  @return OFTrue if value is valid, OFFalse otherwise
     */
    static OFBool checkVR(const OFString &value,
                          size_t *pos = NULL,
                          const OFBool checkLength = OFTrue);

    /** check whether given string value conforms to the VR "CS" (Code String)
     *  and to the specified VM.
     *  @param value string value to be checked (possibly multi-valued)
     *  @param vm value multiplicity (according to the data dictionary) to be checked for.
     *    (valid values: "1", "1-2", "1-3", "1-8", "1-99", "1-n", "2", "2-n", "2-2n",
     *                   "3", "3-n", "3-3n", "4", "6", "9", "16", "32")
     *  @return status of the check, EC_Normal if value is correct, an error code otherwise
     */
    static OFCondition checkStringValue(const OFString &value,
                                        const OFString &vm = "1-n");
};


#endif // DCVRCS_H


/*
** CVS/RCS Log:
** $Log: dcvrcs.h,v $
** Revision 1.25  2010-11-05 09:34:11  joergr
** Added support for checking the value multiplicity "9" (see Supplement 131).
**
** Revision 1.24  2010-10-14 13:15:42  joergr
** Updated copyright header. Added reference to COPYRIGHT file.
**
** Revision 1.23  2010-04-23 15:26:12  joergr
** Specify an appropriate default value for the "vm" parameter of checkValue().
**
** Revision 1.22  2010-04-23 14:25:27  joergr
** Added new method to all VR classes which checks whether the stored value
** conforms to the VR definition and to the specified VM.
**
** Revision 1.21  2010-04-22 09:31:30  joergr
** Revised misleading parameter documentation for the checkValue() method.
**
** Revision 1.20  2010-04-22 08:59:10  joergr
** Added support for further VM values ("1-8", "1-99", "16", "32") to be checked.
**
** Revision 1.19  2009-08-03 09:05:30  joergr
** Added methods that check whether a given string value conforms to the VR and
** VM definitions of the DICOM standards.
**
** Revision 1.18  2008-07-17 11:19:49  onken
** Updated copyFrom() documentation.
**
** Revision 1.17  2008-07-17 10:30:23  onken
** Implemented copyFrom() method for complete DcmObject class hierarchy, which
** permits setting an instance's value from an existing object. Implemented
** assignment operator where necessary.
**
** Revision 1.16  2005-12-08 16:28:54  meichel
** Changed include path schema for all DCMTK header files
**
** Revision 1.15  2004/07/01 12:28:25  meichel
** Introduced virtual clone method for DcmObject and derived classes.
**
** Revision 1.14  2003/06/12 13:30:58  joergr
** Added static function checkVR().
**
** Revision 1.13  2002/12/06 12:49:14  joergr
** Enhanced "print()" function by re-working the implementation and replacing
** the boolean "showFullData" parameter by a more general integer flag.
** Added doc++ documentation.
** Made source code formatting more consistent with other modules/files.
**
** Revision 1.12  2002/04/25 09:48:10  joergr
** Removed getOFStringArray() implementation.
**
** Revision 1.11  2001/09/25 17:19:30  meichel
** Adapted dcmdata to class OFCondition
**
** Revision 1.10  2001/06/01 15:48:48  meichel
** Updated copyright header
**
** Revision 1.9  2000/03/08 16:26:22  meichel
** Updated copyright header.
**
** Revision 1.8  1999/03/31 09:24:57  meichel
** Updated copyright header in module dcmdata
**
** Revision 1.7  1998/11/12 16:47:46  meichel
** Implemented operator= for all classes derived from DcmObject.
**
** Revision 1.6  1997/09/11 15:13:12  hewett
** Modified getOFString method arguments by removing a default value
** for the pos argument.  By requiring the pos argument to be provided
** ensures that callers realise getOFString only gets one component of
** a multi-valued string.
**
** Revision 1.5  1997/08/29 08:32:40  andreas
** - Added methods getOFString and getOFStringArray for all
**   string VRs. These methods are able to normalise the value, i. e.
**   to remove leading and trailing spaces. This will be done only if
**   it is described in the standard that these spaces are not relevant.
**   These methods do not test the strings for conformance, this means
**   especially that they do not delete spaces where they are not allowed!
**   getOFStringArray returns the string with all its parts separated by \
**   and getOFString returns only one value of the string.
**   CAUTION: Currently getString returns a string with trailing
**   spaces removed (if dcmEnableAutomaticInputDataCorrection == OFTrue) and
**   truncates the original string (since it is not copied!). If you rely on this
**   behaviour please change your application now.
**   Future changes will ensure that getString returns the original
**   string from the DICOM object (NULL terminated) inclusive padding.
**   Currently, if you call getOF... before calling getString without
**   normalisation, you can get the original string read from the DICOM object.
**
** Revision 1.4  1996/01/09 11:06:17  andreas
** New Support for Visual C++
** Correct problems with inconsistent const declarations
**
** Revision 1.3  1996/01/05 13:23:03  andreas
** - changed to support new streaming facilities
** - more cleanups
** - merged read / write methods for block and file transfer
**
*/