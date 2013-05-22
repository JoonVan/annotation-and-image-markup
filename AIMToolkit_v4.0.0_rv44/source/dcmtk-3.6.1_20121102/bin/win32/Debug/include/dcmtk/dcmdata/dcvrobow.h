/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#ifndef DCVROBOW_H
#define DCVROBOW_H

#include "dcmtk/config/osconfig.h"    /* make sure OS specific configuration is included first */
#include "dcmtk/dcmdata/dcelem.h"


/** a class representing the DICOM value representations 'Other Byte String' (OB)
 *  and 'Other Word String' (OW)
 */
class DCMTK_DCMDATA_EXPORT DcmOtherByteOtherWord
  : public DcmElement
{

 public:

    /** constructor.
     *  Create new element from given tag and length.
     *  @param tag DICOM tag for the new element
     *  @param len value length for the new element
     */
    DcmOtherByteOtherWord(const DcmTag &tag,
                          const Uint32 len = 0);

    /** copy constructor
     *  @param old element to be copied
     */
    DcmOtherByteOtherWord(const DcmOtherByteOtherWord &old);

    /** destructor
     */
    virtual ~DcmOtherByteOtherWord();

    /** assignment operator
     *  @param obj element to be assigned/copied
     *  @return reference to this object
     */
    DcmOtherByteOtherWord &operator=(const DcmOtherByteOtherWord &obj);

    /** clone method
     *  @return deep copy of this object
     */
    virtual DcmObject *clone() const
    {
      return new DcmOtherByteOtherWord(*this);
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
     *  @return type identifier of this class
     */
    virtual DcmEVR ident() const;

    /** check whether stored value conforms to the VR and to the specified VM
     *  @param vm parameter not used for this VR
     *  @param oldFormat parameter not used for this VR (only for DA, TM, PN)
     *  @return always returns EC_Normal, i.e. currently no checks are performed
     */
    virtual OFCondition checkValue(const OFString &vm = "",
                                   const OFBool oldFormat = OFFalse);

    /** get value multiplicity
     *  @return always returns 1 (according to the DICOM standard)
     */
    virtual unsigned long getVM();

    /** set/change the current value representation
     *  @param vr new value representation to be set.  All VRs except for OW (Other
     *    Word String) are treated as 8 bit data (OB).  This is particularily useful
     *    for unknown (UN) or unsupported VRs.
     *  @return status status, EC_Normal if successful, an error code otherwise
     */
    virtual OFCondition setVR(DcmEVR vr);

    /** print the current value to a stream.
     *  The output format of the binary value is a backslash separated sequence of
     *  2- or 4-digit hex numbers, e.g. "00\01\dd" or "0000\7777\aaaa\ffff".
     *  @param out output stream
     *  @param flags optional flag used to customize the output (see DCMTypes::PF_xxx)
     *  @param level current level of nested items. Used for indentation.
     *  @param pixelFileName not used
     *  @param pixelCounter not used
     */
    virtual void print(STD_NAMESPACE ostream&out,
                       const size_t flags = 0,
                       const int level = 0,
                       const char *pixelFileName = NULL,
                       size_t *pixelCounter = NULL);

    /** check whether the transfer syntax can be changed as specified
     *  @param newXfer transfer syntax to be checked
     *  @param oldXfer not used
     *  @return OFTrue if transfer syntax can be changed to the new one, OFFalse otherwise
     */
    virtual OFBool canWriteXfer(const E_TransferSyntax newXfer,
                                const E_TransferSyntax oldXfer);

    /** write object to a stream
     *  @param outStream DICOM output stream
     *  @param oxfer output transfer syntax
     *  @param enctype encoding types (undefined or explicit length)
     *  @param wcache pointer to write cache object, may be NULL
     *  @return status, EC_Normal if successful, an error code otherwise
     */
    virtual OFCondition write(DcmOutputStream &outStream,
                              const E_TransferSyntax oxfer,
                              const E_EncodingType enctype,
                              DcmWriteCache *wcache);

    /** write object in XML format to a stream
     *  @param out output stream to which the XML document is written
     *  @param flags optional flag used to customize the output (see DCMTypes::XF_xxx)
     *  @return status, EC_Normal if successful, an error code otherwise
     */
    virtual OFCondition writeXML(STD_NAMESPACE ostream&out,
                                 const size_t flags = 0);

    /** special write method for creation of digital signatures
     *  @param outStream DICOM output stream
     *  @param oxfer output transfer syntax
     *  @param enctype encoding types (undefined or explicit length)
     *  @param wcache pointer to write cache object, may be NULL
     *  @return status, EC_Normal if successful, an error code otherwise
     */
    virtual OFCondition writeSignatureFormat(DcmOutputStream &outStream,
                                             const E_TransferSyntax oxfer,
                                             const E_EncodingType enctype,
                                             DcmWriteCache *wcache);

    /** get particular 8 bit value.
     *  This method is only applicable to non-OW data, e.g. OB.
     *  @param byteVal reference to result variable (cleared in case of error)
     *  @param pos index of the value to be retrieved (0..vm-1)
     *  @return status, EC_Normal if successful, an error code otherwise
     */
    virtual OFCondition getUint8(Uint8 &byteVal,
                                 const unsigned long pos = 0);

    /** get particular 16 bit value.
     *  This method is only applicable to OW data.
     *  @param wordVal reference to result variable (cleared in case of error)
     *  @param pos index of the value to be retrieved (0..vm-1)
     *  @return status status, EC_Normal if successful, an error code otherwise
     */
    virtual OFCondition getUint16(Uint16 &wordVal,
                                  const unsigned long pos = 0);

    /** get reference to stored 8 bit data.
     *  This method is only applicable to non-OW data, e.g. OB.
     *  @param byteVals reference to result variable
     *  @return status status, EC_Normal if successful, an error code otherwise
     */
    virtual OFCondition getUint8Array(Uint8 *&byteVals);

    /** get reference to stored 16 bit data.
     *  This method is only applicable to OW data.
     *  @param wordVals reference to result variable
     *  @return status status, EC_Normal if successful, an error code otherwise
     */
    virtual OFCondition getUint16Array(Uint16 *&wordVals);

    /** get a particular value as a character string.
     *  The numeric value is converted to hex mode, i.e. an 8 bit value is
     *  represented by 2 characters (00..ff) and a 16 bit value by 4 characters
     *  (0000..ffff).
     *  @param stringVal variable in which the result value is stored
     *  @param pos index of the value in case of multi-valued elements (0..vm-1)
     *  @param normalize not used
     *  @return status, EC_Normal if successful, an error code otherwise
     */
    virtual OFCondition getOFString(OFString &stringVal,
                                    const unsigned long pos,
                                    OFBool normalize = OFTrue);

    /** get element value as a character string.
     *  The numeric values are converted to hex mode, i.e. an 8 bit value is
     *  represented by 2 characters (00..ff) and a 16 bit value by 4 characters
     *  (0000..ffff).
     *  In case of VM > 1 the individual values are separated by a backslash ('\').
     *  @param stringVal variable in which the result value is stored
     *  @param normalize not used
     *  @return status, EC_Normal if successful, an error code otherwise
     */
    virtual OFCondition getOFStringArray(OFString &stringVal,
                                         OFBool normalize = OFTrue);

    /** set element value to given 8 bit data.
     *  This method is only applicable to non-OW data, e.g. OB.
     *  @param byteValue 8 bit data to be set (copied)
     *  @param numBytes number of bytes (8 bit) to be set
     *  @return status, EC_Normal if successful, an error code otherwise
     */
    virtual OFCondition putUint8Array(const Uint8 *byteValue,
                                      const unsigned long numBytes);

    /** set element value to given 16 bit data.
     *  This method is only applicable to OW data.
     *  @param wordValue 16 bit data to be set (copied)
     *  @param numWords number of words (16 bit) to be set. Local byte-ordering
     *    expected.
     *  @return status, EC_Normal if successful, an error code otherwise
     */
    virtual OFCondition putUint16Array(const Uint16 *wordValue,
                                       const unsigned long numWords);

    /** create an empty Uint8 array of given number of bytes and set it.
     *  All array elements are initialized with a value of 0 (using 'memzero').
     *  This method is only applicable to non-OW data, e.g. OB.
     *  @param numBytes number of bytes (8 bit) to be created
     *  @param bytes stores the pointer to the resulting buffer
     *  @return status, EC_Normal if successful, an error code otherwise
     */
    virtual OFCondition createUint8Array(const Uint32 numBytes,
                                         Uint8 *&bytes);

    /** create an empty Uint16 array of given number of words and set it.
     *  All array elements are initialized with a value of 0 (using 'memzero').
     *  This method is only applicable to OW data.
     *  @param numWords number of words (16 bit) to be created
     *  @param words stores the pointer to the resulting buffer
     *  @return status, EC_Normal if successful, an error code otherwise
     */
    virtual OFCondition createUint16Array(const Uint32 numWords,
                                          Uint16 *&words);

    /** set element value from the given character string.
     *  The input string is expected to have the same format as described for
     *  'getOFStringArray()' above, i.e. a backslash separated sequence of
     *  hexa-decimal numbers.
     *  @param stringVal input character string
     *  @return status, EC_Normal if successful, an error code otherwise
     */
    virtual OFCondition putString(const char *stringVal);

    /** set element value from the given character string.
     *  The input string is expected to have the same format as described for
     *  'getOFStringArray()' above, i.e. a backslash separated sequence of
     *  hexa-decimal numbers.
     *  The length of the string has to be specified explicitly. The string can, therefore,
     *  also contain more than one NULL byte.
     *  @param stringVal input character string
     *  @param stringLen length of the string (number of characters without the
     *    trailing NULL byte)
     *  @return status, EC_Normal if successful, an error code otherwise
     */
    virtual OFCondition putString(const char *stringVal,
                                  const Uint32 stringLen);

    /** check the currently stored element value
     *  @param autocorrect correct value padding (even length) if OFTrue
     *  @return status, EC_Normal if value length is correct, an error code otherwise
     */
    virtual OFCondition verify(const OFBool autocorrect = OFFalse);


 protected:

    /** method is called after the element value has been loaded.
     *  Can be used to correct the value before it is used for the first time.
     */
    virtual void postLoadValue();

    /** align the element value to an even length (padding)
     *  @return status, EC_Normal if successful, an error code otherwise
     */
    OFCondition alignValue();

    /** print pixel data and optionally write it to a binary file.
     *  Optional pixel data file is always written in little endian byte-ordering.
     *  @param out output stream
     *  @param flags optional flag used to customize the output (see DCMTypes::PF_xxx)
     *  @param level current level of nested items. Used for indentation.
     *  @param pixelFileName optional filename used to write the raw pixel data file
     *  @param pixelCounter optional counter used for automatic pixel data filename creation
     */
    void printPixel(STD_NAMESPACE ostream&out,
                    const size_t flags,
                    const int level,
                    const char *pixelFileName,
                    size_t *pixelCounter);

private:

    /** this flag is used during write operations and indicates that compact() should be
     *  called once the write operation finishes.
     */
    OFBool compactAfterTransfer;

};


#endif // DCVROBOW_H