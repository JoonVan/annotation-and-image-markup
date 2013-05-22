/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#ifndef DSRNUMVL_H
#define DSRNUMVL_H

#include "dcmtk/config/osconfig.h"   /* make sure OS specific configuration is included first */

#include "dcmtk/dcmsr/dsrcodvl.h"

#include "dcmtk/ofstd/ofstring.h"


/*---------------------*
 *  class declaration  *
 *---------------------*/

/** Class for numeric measurement values
 */
class DCMTK_DCMSR_EXPORT DSRNumericMeasurementValue
{
    // allow access to getValuePtr()
    friend class DSRContentItem;

  public:

    /** default constructor
     */
    DSRNumericMeasurementValue();

    /** constructor
     ** @param  numericValue     numeric measurement value (VR=DS, mandatory)
     *  @param  measurementUnit  code representing the units of measurement (mandatory)
     *  @param  check            if enabled, check 'numericValue' and 'measurementUnit' for
     *                           validity before setting them.  See checkXXX() methods for
     *                           details.  Empty values are never accepted.
     */
    DSRNumericMeasurementValue(const OFString &numericValue,
                               const DSRCodedEntryValue &measurementUnit,
                               const OFBool check = OFTrue);

    /** constructor
     ** @param  numericValue     numeric measurement value (VR=DS, mandatory)
     *  @param  measurementUnit  code representing the units of measurement (mandatory)
     *  @param  valueQualifier   code representing the numeric value qualifier (optional).
     *                           Can also be used to specify the reason for the absence of
     *                           the measured value sequence.
     *  @param  check            if enabled, check values for validity before setting them.
     *                           See checkXXX() for details.  Empty values are only accepted
     *                           for non-mandatory attributes.
     */
    DSRNumericMeasurementValue(const OFString &numericValue,
                               const DSRCodedEntryValue &measurementUnit,
                               const DSRCodedEntryValue &valueQualifier,
                               const OFBool check = OFTrue);

    /** copy constructor
     ** @param  numericMeasurement  numeric measurement value to be copied (not checked !)
     */
    DSRNumericMeasurementValue(const DSRNumericMeasurementValue &numericMeasurement);

    /** destructor
     */
    virtual ~DSRNumericMeasurementValue();

    /** assignment operator
     ** @param  numericMeasurement  numeric measurement value to be copied (not checked !)
     ** @return reference to this numeric value after 'numericMeasurement' has been copied
     */
    DSRNumericMeasurementValue &operator=(const DSRNumericMeasurementValue &numericMeasurement);

    /** clear all internal variables.
     *  Use this method to create an empty numeric measurement value.
     */
    virtual void clear();

    /** check whether the current numeric measurement value is valid.
     *  The value is valid if isEmpty() is true or all three values (numeric value, measurement
     *  unit and value qualifier) do contain valid values (see checkXXX() methods).  The
     *  possibly available additional representations of the numeric value are never checked.
     ** @return OFTrue if value is valid, OFFalse otherwise
     */
    virtual OFBool isValid() const;

    /** check whether the current numeric measurement value is empty.
     *  Checks whether both the numeric value and the measurement are empty.  The optional
     *  value qualifier is not checked since it might contain the reason for the absence of
     *  the measured value sequence.
     ** @return OFTrue if value is empty, OFFalse otherwise
     */
    virtual OFBool isEmpty() const;

    /** print numeric measurement value.
     *  The output of a typical numeric measurement value looks like this:
     *  "3.5" (cm,UCUM[1.4],"centimeter").  If the value is empty the text "empty" is printed
     *  instead.  The numeric value qualifier as well as the possibly available additional
     *  floating point and rational representations of the numeric value are never printed.
     ** @param  stream  output stream to which the numeric measurement value should be printed
     *  @param  flags   flag used to customize the output (not used)
     ** @return status, EC_Normal if successful, an error code otherwise
     */
    virtual OFCondition print(STD_NAMESPACE ostream &stream,
                              const size_t flags) const;

    /** read numeric measurement value from XML document
     ** @param  doc     document containing the XML file content
     *  @param  cursor  cursor pointing to the starting node
     ** @return status, EC_Normal if successful, an error code otherwise
     */
    virtual OFCondition readXML(const DSRXMLDocument &doc,
                                DSRXMLCursor cursor);

    /** write numeric measurement value in XML format
     ** @param  stream  output stream to which the XML document is written
     *  @param  flags   flag used to customize the output (see DSRTypes::XF_xxx)
     ** @return status, EC_Normal if successful, an error code otherwise
     */
    virtual OFCondition writeXML(STD_NAMESPACE ostream &stream,
                                 const size_t flags) const;

    /** read measured value sequence and numeric value qualifier code sequence from dataset.
     *  The number of items within the sequences is checked.  If error/warning output are
     *  enabled, a warning message is printed if a sequence is absent or contains more than
     *  one item.
     ** @param  dataset  DICOM dataset from which the sequences should be read
     ** @return status, EC_Normal if successful, an error code otherwise
     */
    virtual OFCondition readSequence(DcmItem &dataset);

    /** write measured value sequence and numeric value qualifier code sequence to dataset.
     *  The measured value sequence is always written (might be empty, though).  The numeric
     *  value qualifier code sequence is optional and, therefore, only written if non-empty.
     ** @param  dataset  DICOM dataset to which the sequences should be written
     ** @return status, EC_Normal if successful, an error code otherwise
     */
    virtual OFCondition writeSequence(DcmItem &dataset) const;

    /** render numeric measurement value in HTML/XHTML format
     ** @param  docStream    output stream to which the main HTML/XHTML document is written
     *  @param  annexStream  output stream to which the HTML/XHTML document annex is written
     *  @param  annexNumber  reference to the variable where the current annex number is stored.
     *                       Value is increased automatically by 1 after a new entry has been added.
     *  @param  flags        flag used to customize the output (see DSRTypes::HF_xxx)
     ** @return status, EC_Normal if successful, an error code otherwise
     */
    virtual OFCondition renderHTML(STD_NAMESPACE ostream &docStream,
                                   STD_NAMESPACE ostream &annexStream,
                                   size_t &annexNumber,
                                   const size_t flags) const;

    /** get reference to numeric measurement value
     ** @return reference to numeric measurement value
     */
    inline const DSRNumericMeasurementValue &getValue() const
    {
        return *this;
    }

    /** get copy of numeric measurement value
     ** @param  numericMeasurement  reference to variable in which the value should be stored
     ** @return always returns EC_Normal
     */
    OFCondition getValue(DSRNumericMeasurementValue &numericMeasurement) const;

    /** get numeric value
     ** @return current numeric value (might be invalid or an empty string)
     */
    inline const OFString &getNumericValue() const
    {
        return NumericValue;
    }

    /** get measurement unit
     ** @return reference to current measurement unit code (might be invalid or empty)
     */
    inline const DSRCodedEntryValue &getMeasurementUnit() const
    {
        return MeasurementUnit;
    }

    /** get numeric value qualifier (optional)
     ** @return reference to current numeric value qualifier code (might be invalid or empty)
     */
    inline const DSRCodedEntryValue &getNumericValueQualifier() const
    {
        return ValueQualifier;
    }

    /** get copy of measurement unit
     ** @param  measurementUnit  reference to variable in which the code should be stored
     ** @return always returns EC_Normal
     */
    OFCondition getMeasurementUnit(DSRCodedEntryValue &measurementUnit) const;

    /** get copy of numeric value qualifier (optional).
     *  Can be used to specify the reason for the absence of the measured value sequence.
     ** @param  valueQualifier  reference to variable in which the code should be stored
     ** @return always returns EC_Normal
     */
    OFCondition getNumericValueQualifier(DSRCodedEntryValue &valueQualifier) const;

    /** get floating point representation of the numeric value (optional)
     ** @param  floatingPoint  reference to variable in which the floating point representation
     *                         should be stored
     ** @return status, EC_Normal if successful, an error code otherwise.  Returns
     *    SR_EC_RepresentationNotAvailable if floating point representation is not available.
     */
    OFCondition getFloatingPointRepresentation(Float64 &floatingPoint) const;

    /** get rational representation of the numeric value (optional)
     ** @param  rationalNumerator    reference to variable in which the integer numerator of
     *                               the rational representation should be stored
     ** @param  rationalDenominator  reference to variable in which the integer denominator of
     *                               the rational representation should be stored
     ** @return status, EC_Normal if successful, an error code otherwise.  Returns
     *    SR_EC_RepresentationNotAvailable if rational representation is not available.
     */
    OFCondition getRationalRepresentation(Sint32 &rationalNumerator,
                                          Uint32 &rationalDenominator) const;

    /** set numeric measurement value.
     *  Before setting the value, it is usually checked.  If the value is invalid, the current
     *  value is not replaced and remains unchanged.
     ** @param  numericMeasurement  value to be set
     *  @param  check               if enabled, check value for validity before setting it.
     *                              See checkXXX() methods for details.  Empty values are only
     *                              accepted for non-mandatory attributes.
     ** @return status, EC_Normal if successful, an error code otherwise
     */
    OFCondition setValue(const DSRNumericMeasurementValue &numericMeasurement,
                         const OFBool check = OFTrue);

    /** set numeric value and measurement unit.
     *  Before setting the values, they are usually checked.  If the value pair is invalid,
     *  the current value pair is not replaced and remains unchanged.  If the value pair is
     *  replaced, the optional floating point and rational representations are cleared, i.e.
     *  they have to be set manually if needed.
     ** @param  numericValue     numeric value to be set (VR=DS, mandatory)
     *  @param  measurementUnit  measurement unit to be set (mandatory)
     *  @param  check            if enabled, check values for validity before setting them.
     *                           See checkXXX() methods for details.
     ** @return status, EC_Normal if successful, an error code otherwise
     */
    OFCondition setValue(const OFString &numericValue,
                         const DSRCodedEntryValue &measurementUnit,
                         const OFBool check = OFTrue);

    /** set numeric value, measurement unit and numeric value qualifier.
     *  Before setting the values, they are usually checked.  If one of the three values is
     *  invalid, the current numeric measurement value is not replaced and remains unchanged.
     *  If the values are replaced, the optional floating point and rational representations
     *  are cleared, i.e. they have to be set manually if needed.
     ** @param  numericValue     numeric value to be set (VR=DS, mandatory)
     *  @param  measurementUnit  measurement unit to be set (mandatory)
     *  @param  valueQualifier   numeric value qualifier to be set (optional).  Can also be
     *                           used to specify the reason for the absence of the measured
     *                           value sequence.  Use an empty code to remove the current
     *                           value.
     *  @param  check            if enabled, check values for validity before setting them.
     *                           See checkXXX() methods for details.  Empty values are only
     *                           accepted for non-mandatory attributes.
     ** @return status, EC_Normal if successful, an error code otherwise
     */
    OFCondition setValue(const OFString &numericValue,
                         const DSRCodedEntryValue &measurementUnit,
                         const DSRCodedEntryValue &valueQualifier,
                         const OFBool check = OFTrue);

    /** set numeric value.
     *  Before setting the value, it is usually checked.  If the value is invalid, the current
     *  value is not replaced and remains unchanged.  If the value is replaced, the optional
     *  floating point and rational representations are cleared, i.e. they have to be set
     *  manually if needed.
     ** @param  numericValue  numeric value to be set (VR=DS, mandatory)
     *  @param  check         if enabled, check value for validity before setting it.
     *                        See checkNumericValue() method for details.  An empty value is
     *                        never accepted.
     ** @return status, EC_Normal if successful, an error code otherwise
     */
    OFCondition setNumericValue(const OFString &numericValue,
                                const OFBool check = OFTrue);

    /** set measurement unit.
     *  Before setting the code, it is usually checked.  If the code is invalid the current
     *  code is not replaced and remains unchanged.
     ** @param  measurementUnit  measurement unit to be set (mandatory)
     *  @param  check            if enabled, check value for validity before setting it.
     *                           See checkMeasurementUnit() method for details.  An empty
     *                           value is never accepted.
     ** @return status, EC_Normal if successful, an error code otherwise
     */
    OFCondition setMeasurementUnit(const DSRCodedEntryValue &measurementUnit,
                                   const OFBool check = OFTrue);

    /** set numeric value qualifier.
     *  This optional code specifies the qualification of the Numeric Value in the Measured
     *  Value Sequence, or the reason for the absence of the Measured Value Sequence Item.
     *  Before setting the code, it is usually checked.  If the code is invalid the current
     *  code is not replaced and remains unchanged.
     ** @param  valueQualifier  numeric value qualifier to be set (optional).  Use an empty
     *                          code to remove the current value.
     *  @param  check           if enabled, check value for validity before setting it.
     *                          See checkNumericValueQualifier() method for details.
     ** @return status, EC_Normal if successful, an error code otherwise
     */
    OFCondition setNumericValueQualifier(const DSRCodedEntryValue &valueQualifier,
                                         const OFBool check = OFTrue);

    /** set floating point representation of the numeric value.
     *  According to the DICOM standard, this value is "required if the numeric value has
     *  insufficient precision to represent the value as a string.  May be present otherwise."
     *  Please note that it is not checked whether this representation is consistent with the
     *  numeric value stored as a string.
     ** @param  floatingPoint  floating point representation of the numeric value
     *  @param  check          dummy parameter (currently not used)
     ** @return status, EC_Normal if successful, an error code otherwise
     */
    OFCondition setFloatingPointRepresentation(const Float64 floatingPoint,
                                               const OFBool check = OFTrue);

    /** set rational representation of the numeric value.
     *  According to the DICOM standard, this value is "required if the numeric value has
     *  insufficient precision to represent a rational value as a string.  May be present
     *  otherwise."  Please note that it is not checked whether this representation is
     *  consistent with the numeric value stored as a string.
     ** @param  rationalNumerator    integer numerator of a rational representation of the
     *                               numeric value (encoded as a signed integer value)
     *  @param  rationalDenominator  integer denominator of a rational representation of the
     *                               numeric value (encoded as a non-zero unsigned integer
     *                               value)
     *  @param  check                if enabled, check values for validity before setting them.
     *                               See checkRationalRepresentation() method for details.
     ** @return status, EC_Normal if successful, an error code otherwise
     */
    OFCondition setRationalRepresentation(const Sint32 rationalNumerator,
                                          const Uint32 rationalDenominator,
                                          const OFBool check = OFTrue);

    /** remove floating point representation of the numeric value (if any).
     *  Internally, all elements that belong to this representation are cleared.
     */
    void removeFloatingPointRepresentation();

    /** remove rational representation of the numeric value (if any).
     *  Internally, all elements that belong to this representation are cleared.
     */
    void removeRationalRepresentation();


  protected:

    /** get pointer to numeric measurement value
     ** @return pointer to numeric measurement value (never NULL)
     */
    inline DSRNumericMeasurementValue *getValuePtr()
    {
        return this;
    }

    /** read numeric measurement value from dataset
     ** @param  dataset    DICOM dataset from which the value should be read
     ** @return status, EC_Normal if successful, an error code otherwise
     */
    virtual OFCondition readItem(DcmItem &dataset);

    /** write numeric measurement value to dataset
     ** @param  dataset    DICOM dataset to which the value should be written
     ** @return status, EC_Normal if successful, an error code otherwise
     */
    virtual OFCondition writeItem(DcmItem &dataset) const;

    /** check the specified numeric value for validity.
     *  Currently, the only checks performed are that the string is non-empty and that the
     *  given value conforms to the corresponding VR (DS) and VM (1).
     ** @param  numericValue  numeric value to be checked
     ** @return status, EC_Normal if numeric value is valid, an error code otherwise
     */
    OFCondition checkNumericValue(const OFString &numericValue) const;

    /** check the specified measurement unit for validity.
     *  Internally, the methods DSRCodedEntryValue::isEmpty() and
     *  DSRCodedEntryValue::checkCurrentValue() are used for this purpose.  Conformance
     *  with the Context Group 82 (as defined in the DICOM standard) is not yet checked.
     ** @param  measurementUnit  measurement unit to be checked
     ** @return status, EC_Normal if measurement unit is valid, an error code otherwise
     */
    OFCondition checkMeasurementUnit(const DSRCodedEntryValue &measurementUnit) const;

    /** check the specified numeric value qualifier for validity.
     *  Internally, the methods DSRCodedEntryValue::isEmpty() and
     *  DSRCodedEntryValue::checkCurrentValue() are used for this purpose.  Conformance
     *  with the Context Group 42 (as defined in the DICOM standard) is not yet checked.
     ** @param  valueQualifier  numeric value qualifier to be checked
     ** @return status, EC_Normal if value qualifier is valid, an error code otherwise
     */
    OFCondition checkNumericValueQualifier(const DSRCodedEntryValue &valueQualifier) const;

    /** check the specified rational representation for validity.
     *  The only check that is performed is that the 'rationalDenominator' is not zero, i.e.
     *  it is not checked whether this representation is consistent with the numeric value
     *  stored as a string.
     ** @param  rationalNumerator    numerator of the rational representation to be checked
     *  @param  rationalDenominator  denominator of a rational representation to be checked
     ** @return status, EC_Normal if rational representation is valid, an error code otherwise
     */
    OFCondition checkRationalRepresentation(const Sint32 rationalNumerator,
                                            const Uint32 rationalDenominator) const;

    /** check the currently stored numeric measurement value for validity.
     *  See above checkXXX() methods for details.
     ** @return status, EC_Normal if current value is valid, an error code otherwise
     */
    OFCondition checkCurrentValue() const;


  private:

    /// Numeric Value (VR=DS, type 1)
    OFString               NumericValue;
    /// Measurement Unit (type 2)
    DSRCodedEntryValue     MeasurementUnit;
    /// Numeric Value Qualifier (type 3)
    DSRCodedEntryValue     ValueQualifier;
    /// Floating Point Value (VR=FD, type 1C)
    DcmFloatingPointDouble FloatingPointValue;
    /// Rational Numerator Value (VR=SL, type 1C)
    DcmSignedLong          RationalNumeratorValue;
    /// Rational Denominator Value (VR=UL, type 1C)
    DcmUnsignedLong        RationalDenominatorValue;
};


#endif
