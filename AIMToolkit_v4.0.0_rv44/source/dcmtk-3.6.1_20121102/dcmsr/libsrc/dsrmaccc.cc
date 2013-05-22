/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "dcmtk/config/osconfig.h"    /* make sure OS specific configuration is included first */

#include "dcmtk/dcmsr/dsrmaccc.h"


DSRMacularGridThicknessAndVolumeReportConstraintChecker::DSRMacularGridThicknessAndVolumeReportConstraintChecker()
  : DSRIODConstraintChecker()
{
}


DSRMacularGridThicknessAndVolumeReportConstraintChecker::~DSRMacularGridThicknessAndVolumeReportConstraintChecker()
{
}


OFBool DSRMacularGridThicknessAndVolumeReportConstraintChecker::isByReferenceAllowed() const
{
    return OFFalse;
}


OFBool DSRMacularGridThicknessAndVolumeReportConstraintChecker::isTemplateSupportRequired() const
{
    return OFTrue;
}


const char *DSRMacularGridThicknessAndVolumeReportConstraintChecker::getRootTemplateIdentifier() const
{
    return "2100";
}


DSRTypes::E_DocumentType DSRMacularGridThicknessAndVolumeReportConstraintChecker::getDocumentType() const
{
    return DT_MacularGridThicknessAndVolumeReport;
}


OFBool DSRMacularGridThicknessAndVolumeReportConstraintChecker::checkContentRelationship(const E_ValueType sourceValueType,
                                                                                         const E_RelationshipType relationshipType,
                                                                                         const E_ValueType targetValueType,
                                                                                         const OFBool byReference) const
{
    /* the following code implements the constraints of table A.35.11.3.1.2-1 in DICOM PS3.3 */
    OFBool result = OFFalse;
    /* by-reference relationships not allowed at all */
    if (!byReference)
    {
        /* row 1 of the table */
        if ((relationshipType == RT_hasObsContext) && (sourceValueType == VT_Container))
        {
            result = (targetValueType == VT_Code) || (targetValueType == VT_PName) ||
                     (targetValueType == VT_Text) || (targetValueType == VT_UIDRef) ||
                     (targetValueType == VT_Date) || (targetValueType == VT_Num);
        }
        /* row 2 of the table */
        else if ((relationshipType == RT_contains) && (sourceValueType == VT_Container))
        {
            result = (targetValueType == VT_Container) || (targetValueType == VT_Num) ||
                     (targetValueType == VT_Text) || (targetValueType == VT_Code);
        }
        /* row 3 of the table */
        else if (relationshipType == RT_hasConceptMod)
        {
            result = (targetValueType == VT_Code);
        }
        /* row 4 of the table */
        else if ((relationshipType == RT_hasObsContext) && (sourceValueType == VT_Num))
        {
            result = (targetValueType == VT_Text);
        }
        /* row 5 of the table */
        else if ((relationshipType == RT_inferredFrom) && (sourceValueType == VT_Num))
        {
            result = (targetValueType == VT_Image);
        }
    }
    return result;
}
