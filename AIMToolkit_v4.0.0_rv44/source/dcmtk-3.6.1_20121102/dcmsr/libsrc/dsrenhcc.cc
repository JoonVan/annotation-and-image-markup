/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "dcmtk/config/osconfig.h"    /* make sure OS specific configuration is included first */

#include "dcmtk/dcmsr/dsrenhcc.h"


DSREnhancedSRConstraintChecker::DSREnhancedSRConstraintChecker()
  : DSRIODConstraintChecker()
{
}


DSREnhancedSRConstraintChecker::~DSREnhancedSRConstraintChecker()
{
}


OFBool DSREnhancedSRConstraintChecker::isByReferenceAllowed() const
{
    return OFFalse;
}


OFBool DSREnhancedSRConstraintChecker::isTemplateSupportRequired() const
{
    return OFFalse;
}


const char *DSREnhancedSRConstraintChecker::getRootTemplateIdentifier() const
{
    return NULL;
}


DSRTypes::E_DocumentType DSREnhancedSRConstraintChecker::getDocumentType() const
{
    return DT_EnhancedSR;
}


OFBool DSREnhancedSRConstraintChecker::checkContentRelationship(const E_ValueType sourceValueType,
                                                                const E_RelationshipType relationshipType,
                                                                const E_ValueType targetValueType,
                                                                const OFBool byReference) const
{
    /* the following code implements the constraints of table A.35.2-2 in DICOM PS3.3 */
    OFBool result = OFFalse;
    /* by-reference relationships not allowed at all */
    if (!byReference)
    {
        /* row 1 of the table */
        if ((relationshipType == RT_contains) && (sourceValueType == VT_Container))
        {
            result = (targetValueType == VT_Text)     || (targetValueType == VT_Code)      || (targetValueType == VT_Num)    ||
                     (targetValueType == VT_DateTime) || (targetValueType == VT_Date)      || (targetValueType == VT_Time)   ||
                     (targetValueType == VT_UIDRef)   || (targetValueType == VT_PName)     || (targetValueType == VT_SCoord) ||
                     (targetValueType == VT_TCoord)   || (targetValueType == VT_Composite) || (targetValueType == VT_Image)  ||
                     (targetValueType == VT_Waveform) || (targetValueType == VT_Container);
        }
        /* row 2 of the table */
        else if ((relationshipType == RT_hasObsContext) && (sourceValueType == VT_Container))
        {
            result = (targetValueType == VT_Text)     || (targetValueType == VT_Code)  || (targetValueType == VT_Num)  ||
                     (targetValueType == VT_DateTime) || (targetValueType == VT_Date)  || (targetValueType == VT_Time) ||
                     (targetValueType == VT_UIDRef)   || (targetValueType == VT_PName) || (targetValueType == VT_Composite);
        }
        /* row 3 of the table */
        else if ((relationshipType == RT_hasAcqContext) && ((sourceValueType == VT_Container) || (sourceValueType == VT_Image) ||
            (sourceValueType == VT_Waveform) || (sourceValueType == VT_Composite) || (sourceValueType == VT_Num)))
        {
            result = (targetValueType == VT_Text)     || (targetValueType == VT_Code) || (targetValueType == VT_Num)  ||
                     (targetValueType == VT_DateTime) || (targetValueType == VT_Date) || (targetValueType == VT_Time) ||
                     (targetValueType == VT_UIDRef)   || (targetValueType == VT_PName);
        }
        /* row 4 of the table */
        else if (relationshipType == RT_hasConceptMod)
        {
            result = (targetValueType == VT_Text) || (targetValueType == VT_Code);
        }
        /* row 5 of the table */
        else if ((relationshipType == RT_hasProperties) &&
            ((sourceValueType == VT_Text) || (sourceValueType == VT_Code) || (sourceValueType == VT_Num)))
        {
            result = (targetValueType == VT_Text)     || (targetValueType == VT_Code)      || (targetValueType == VT_Num)    ||
                     (targetValueType == VT_DateTime) || (targetValueType == VT_Date)      || (targetValueType == VT_Time)   ||
                     (targetValueType == VT_UIDRef)   || (targetValueType == VT_PName)     || (targetValueType == VT_Image)  ||
                     (targetValueType == VT_Waveform) || (targetValueType == VT_Composite) || (targetValueType == VT_SCoord) ||
                     (targetValueType == VT_TCoord);
        }
        /* row 6 of the table - introduced with CP 1076 */
        else if ((relationshipType == RT_hasProperties) && (sourceValueType == VT_PName))
        {
            result = (targetValueType == VT_Text) || (targetValueType == VT_Code) || (targetValueType == VT_DateTime) ||
                     (targetValueType == VT_Date) || (targetValueType == VT_Time) || (targetValueType == VT_UIDRef)   ||
                     (targetValueType == VT_PName);
        }
        /* row 7 of the table */
        else if ((relationshipType == RT_inferredFrom) &&
            ((sourceValueType == VT_Text) || (sourceValueType == VT_Code) || (sourceValueType == VT_Num)))
        {
            result = (targetValueType == VT_Text)     || (targetValueType == VT_Code)      || (targetValueType == VT_Num)    ||
                     (targetValueType == VT_DateTime) || (targetValueType == VT_Date)      || (targetValueType == VT_Time)   ||
                     (targetValueType == VT_UIDRef)   || (targetValueType == VT_PName)     || (targetValueType == VT_Image)  ||
                     (targetValueType == VT_Waveform) || (targetValueType == VT_Composite) || (targetValueType == VT_SCoord) ||
                     (targetValueType == VT_TCoord);
        }
        /* row 8 of the table */
        else if ((relationshipType == RT_selectedFrom) && (sourceValueType == VT_SCoord))
        {
            result = (targetValueType == VT_Image);
        }
        /* row 9 of the table */
        else if ((relationshipType == RT_selectedFrom) && (sourceValueType == VT_TCoord))
        {
            result = (targetValueType == VT_SCoord) || (targetValueType == VT_Image) || (targetValueType == VT_Waveform);
        }
    }
    return result;
}
