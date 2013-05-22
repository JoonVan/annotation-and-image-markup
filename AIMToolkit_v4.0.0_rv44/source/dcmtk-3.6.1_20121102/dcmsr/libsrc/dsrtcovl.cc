/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "dcmtk/config/osconfig.h"    /* make sure OS specific configuration is included first */

#include "dcmtk/dcmsr/dsrtcovl.h"
#include "dcmtk/dcmsr/dsrxmld.h"


DSRTemporalCoordinatesValue::DSRTemporalCoordinatesValue()
  : TemporalRangeType(DSRTypes::TRT_invalid),
    SamplePositionList(),
    TimeOffsetList(),
    DateTimeList()
{
}


DSRTemporalCoordinatesValue::DSRTemporalCoordinatesValue(const DSRTypes::E_TemporalRangeType temporalRangeType)
  : TemporalRangeType(temporalRangeType),
    SamplePositionList(),
    TimeOffsetList(),
    DateTimeList()
{
}


DSRTemporalCoordinatesValue::DSRTemporalCoordinatesValue(const DSRTemporalCoordinatesValue &coordinatesValue)
  : TemporalRangeType(coordinatesValue.TemporalRangeType),
    SamplePositionList(coordinatesValue.SamplePositionList),
    TimeOffsetList(coordinatesValue.TimeOffsetList),
    DateTimeList(coordinatesValue.DateTimeList)
{
}


DSRTemporalCoordinatesValue::~DSRTemporalCoordinatesValue()
{
}


DSRTemporalCoordinatesValue &DSRTemporalCoordinatesValue::operator=(const DSRTemporalCoordinatesValue &coordinatesValue)
{
    TemporalRangeType = coordinatesValue.TemporalRangeType;
    SamplePositionList = coordinatesValue.SamplePositionList;
    TimeOffsetList = coordinatesValue.TimeOffsetList;
    DateTimeList = coordinatesValue.DateTimeList;
    return *this;
}


void DSRTemporalCoordinatesValue::clear()
{
    TemporalRangeType = DSRTypes::TRT_invalid;
    SamplePositionList.clear();
    TimeOffsetList.clear();
    DateTimeList.clear();
}


OFBool DSRTemporalCoordinatesValue::isValid() const
{
    return checkData(TemporalRangeType, SamplePositionList, TimeOffsetList, DateTimeList).good();
}


OFBool DSRTemporalCoordinatesValue::isShort(const size_t flags) const
{
    return (SamplePositionList.isEmpty() && TimeOffsetList.isEmpty() && DateTimeList.isEmpty()) ||
          !(flags & DSRTypes::HF_renderFullData);
}


OFCondition DSRTemporalCoordinatesValue::print(STD_NAMESPACE ostream &stream,
                                               const size_t flags) const
{
    /* TemporalRangeType */
    stream << "(" << DSRTypes::temporalRangeTypeToEnumeratedValue(TemporalRangeType);
    /* print data */
    stream << ",";
    /* print only one list */
    if (!SamplePositionList.isEmpty())
        SamplePositionList.print(stream, flags);
    else if (!TimeOffsetList.isEmpty())
        TimeOffsetList.print(stream, flags);
    else
        DateTimeList.print(stream, flags);
    stream << ")";
    return EC_Normal;
}


OFCondition DSRTemporalCoordinatesValue::readXML(const DSRXMLDocument &doc,
                                                 DSRXMLCursor cursor)
{
    OFCondition result = SR_EC_CorruptedXMLStructure;
    if (cursor.valid())
    {
        /* graphic data (required) */
        cursor = doc.getNamedNode(cursor.getChild(), "data");
        if (cursor.valid())
        {
            OFString tmpString, typeString;
            /* read 'type' and check validity */
            doc.getStringFromAttribute(cursor, typeString, "type");
            if (typeString == "SAMPLE POSITION")
            {
                /* put value to the sample position list */
                result = SamplePositionList.putString(doc.getStringFromNodeContent(cursor, tmpString).c_str());
            }
            else if (typeString == "TIME OFFSET")
            {
                /* put value to the time offset list */
                result = TimeOffsetList.putString(doc.getStringFromNodeContent(cursor, tmpString).c_str());
            }
            else if (typeString == "DATETIME")
            {
                /* put value to the date/time list (tbd: convert from ISO 8601 format?) */
                result = DateTimeList.putString(doc.getStringFromNodeContent(cursor, tmpString).c_str());
            } else {
                DSRTypes::printUnknownValueWarningMessage("TCOORD data type", typeString.c_str());
                result = SR_EC_InvalidValue;
            }
        }
    }
    return result;
}


OFCondition DSRTemporalCoordinatesValue::writeXML(STD_NAMESPACE ostream &stream,
                                                  const size_t flags) const
{
    /* TemporalRangeType is written in TreeNode class */
    if ((flags & DSRTypes::XF_writeEmptyTags) || !SamplePositionList.isEmpty() ||
         !TimeOffsetList.isEmpty() || !DateTimeList.isEmpty())
    {
        stream << "<data type=\"";
        /* print only one list */
        if (!SamplePositionList.isEmpty())
        {
            stream << "SAMPLE POSITION\">";
            SamplePositionList.print(stream);
        }
        else if (!TimeOffsetList.isEmpty())
        {
            stream << "TIME OFFSET\">";
            TimeOffsetList.print(stream);
        } else {
            /* tbd: convert output to ISO 8601 format? */
            stream << "DATETIME\">";
            DateTimeList.print(stream);
        }
        stream << "</data>" << OFendl;
    }
    return EC_Normal;
}


OFCondition DSRTemporalCoordinatesValue::read(DcmItem &dataset)
{
    /* read TemporalRangeType */
    OFString tmpString;
    OFCondition result = DSRTypes::getAndCheckStringValueFromDataset(dataset, DCM_TemporalRangeType, tmpString, "1", "1", "TCOORD content item");
    if (result.good())
    {
        TemporalRangeType = DSRTypes::enumeratedValueToTemporalRangeType(tmpString);
        /* check TemporalRangeType */
        if (TemporalRangeType == DSRTypes::TRT_invalid)
            DSRTypes::printUnknownValueWarningMessage("TemporalRangeType", tmpString.c_str());
        /* first read data (all three lists) */
        SamplePositionList.read(dataset);
        TimeOffsetList.read(dataset);
        DateTimeList.read(dataset);
        /* then check data and report warnings if any */
        checkData(TemporalRangeType, SamplePositionList, TimeOffsetList, DateTimeList, OFTrue /*reportWarnings*/);
    }
    return result;
}


OFCondition DSRTemporalCoordinatesValue::write(DcmItem &dataset) const
{
    /* write TemporalRangeType */
    OFCondition result = DSRTypes::putStringValueToDataset(dataset, DCM_TemporalRangeType, DSRTypes::temporalRangeTypeToEnumeratedValue(TemporalRangeType));
    if (result.good())
    {
        /* write data (only one list) */
        if (!SamplePositionList.isEmpty())
            SamplePositionList.write(dataset);
        else if (!TimeOffsetList.isEmpty())
            TimeOffsetList.write(dataset);
        else
            DateTimeList.write(dataset);
    }
    /* check data and report warnings if any */
    checkData(TemporalRangeType, SamplePositionList, TimeOffsetList, DateTimeList, OFTrue /*reportWarnings*/);
    return result;
}


OFCondition DSRTemporalCoordinatesValue::renderHTML(STD_NAMESPACE ostream &docStream,
                                                    STD_NAMESPACE ostream &annexStream,
                                                    size_t &annexNumber,
                                                    const size_t flags) const
{
    /* render TemporalRangeType */
    docStream << DSRTypes::temporalRangeTypeToReadableName(TemporalRangeType);
    /* render data */
    if (!isShort(flags))
    {
        const char *lineBreak = (flags & DSRTypes::HF_renderSectionTitlesInline) ? " " :
                                (flags & DSRTypes::HF_XHTML11Compatibility) ? "<br />" : "<br>";
        if (flags & DSRTypes::HF_currentlyInsideAnnex)
        {
            docStream << OFendl << "<p>" << OFendl;
            /* render data list (= print)*/
            if (!SamplePositionList.isEmpty())
            {
                docStream << "<b>Reference Sample Positions:</b>" << lineBreak;
                SamplePositionList.print(docStream);
            }
            else if (!TimeOffsetList.isEmpty())
            {
                docStream << "<b>Referenced Time Offsets:</b>" << lineBreak;
                TimeOffsetList.print(docStream);
            } else {
                docStream << "<b>Referenced Date/Time:</b>" << lineBreak;
                DateTimeList.print(docStream);
            }
            docStream << "</p>";
        } else {
            DSRTypes::createHTMLAnnexEntry(docStream, annexStream, "for more details see", annexNumber, flags);
            annexStream << "<p>" << OFendl;
            /* render data list (= print)*/
            if (!SamplePositionList.isEmpty())
            {
                annexStream << "<b>Reference Sample Positions:</b>" << lineBreak;
                SamplePositionList.print(annexStream);
            }
            else if (!TimeOffsetList.isEmpty())
            {
                annexStream << "<b>Referenced Time Offsets:</b>" << lineBreak;
                TimeOffsetList.print(annexStream);
            } else {
                annexStream << "<b>Referenced Date/Time:</b>" << lineBreak;
                DateTimeList.print(annexStream);
            }
            annexStream << "</p>" << OFendl;
        }
    }
    return EC_Normal;
}


OFCondition DSRTemporalCoordinatesValue::setValue(const DSRTemporalCoordinatesValue &coordinatesValue,
                                                  const OFBool check)
{
    OFCondition result = EC_Normal;
    if (check)
    {
        /* check whether the passed value is valid */
        result = checkData(coordinatesValue.TemporalRangeType, coordinatesValue.SamplePositionList,
                           coordinatesValue.TimeOffsetList, coordinatesValue.DateTimeList);
    } else {
        /* make sure that the mandatory values are non-empty/invalid */
        if ((coordinatesValue.TemporalRangeType == DSRTypes::TRT_invalid) ||
            (coordinatesValue.SamplePositionList.isEmpty() &&
             coordinatesValue.TimeOffsetList.isEmpty() &&
             coordinatesValue.DateTimeList.isEmpty()))
        {
            result = EC_IllegalParameter;
        }
    }
    if (result.good())
    {
        TemporalRangeType = coordinatesValue.TemporalRangeType;
        SamplePositionList = coordinatesValue.SamplePositionList;
        TimeOffsetList = coordinatesValue.TimeOffsetList;
        DateTimeList = coordinatesValue.DateTimeList;
    }
    return result;
}


OFCondition DSRTemporalCoordinatesValue::getValue(DSRTemporalCoordinatesValue &coordinatesValue) const
{
    coordinatesValue = *this;
    return EC_Normal;
}


OFCondition DSRTemporalCoordinatesValue::setTemporalRangeType(const DSRTypes::E_TemporalRangeType temporalRangeType,
                                                              const OFBool /*check*/)
{
    OFCondition result = EC_IllegalParameter;
    /* check whether the passed value is valid */
    if (temporalRangeType != DSRTypes::TRT_invalid)
    {
        TemporalRangeType = temporalRangeType;
        result = EC_Normal;
    }
    return result;
}


// helper macro to avoid annoying check of boolean flag
#define REPORT_WARNING(msg) { if (reportWarnings) DCMSR_WARN(msg); }

OFCondition DSRTemporalCoordinatesValue::checkData(const DSRTypes::E_TemporalRangeType temporalRangeType,
                                                   const DSRReferencedSamplePositionList &samplePositionList,
                                                   const DSRReferencedTimeOffsetList &timeOffsetList,
                                                   const DSRReferencedDateTimeList &dateTimeList,
                                                   const OFBool reportWarnings) const
{
    OFCondition result = EC_Normal;
    if (temporalRangeType == DSRTypes::TRT_invalid)
        REPORT_WARNING("Invalid TemporalRangeType for TCOORD content item")
    const OFBool list1 = !samplePositionList.isEmpty();
    const OFBool list2 = !timeOffsetList.isEmpty();
    const OFBool list3 = !dateTimeList.isEmpty();
    if (list1 && list2 && list3)
        REPORT_WARNING("ReferencedSamplePositions/TimeOffsets/DateTime present in TCOORD content item")
    else if (list1 && list2)
        REPORT_WARNING("ReferencedSamplePositions/TimeOffsets present in TCOORD content item")
    else if (list1 && list3)
        REPORT_WARNING("ReferencedSamplePositions/DateTime present in TCOORD content item")
    else if (list2 && list3)
        REPORT_WARNING("ReferencedTimeOffsets/DateTime present in TCOORD content item")
    else if (!list1 && !list2 && !list3)
    {
        REPORT_WARNING("ReferencedSamplePositions/TimeOffsets/DateTime empty in TCOORD content item")
        /* invalid: all lists are empty (type 1C) */
        result = SR_EC_InvalidValue;
    }
    return result;
}