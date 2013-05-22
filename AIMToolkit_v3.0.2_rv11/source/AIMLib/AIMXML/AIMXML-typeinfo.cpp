/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "StdAfx.h"
#include "AIMXML-typeinfo.h"
#include "../Altova/xs-types.h"

namespace AIMXML
{

const altova::Binder binder = { namespaces, types, members, facets };

// Array of all namespaces with pointers to types:
const altova::NamespaceInfo namespaces[] = 
{
	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T(""), _altova_tif, _altova_til },
	{ &binder, _T("http://www.w3.org/2001/XMLSchema"), _T("xs"), _altova_tif_xs, _altova_til_xs },
	{ 0 },
};

// Array of all types with pointers to members:
const altova::TypeInfo types[] = 
{
	{ &binder, _altova_ni, _T("AimStatus"), _altova_ti_xs_altova_CanyType, _altova_mif_altova_CAimStatus, _altova_mil_altova_CAimStatus,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T("AnatomicEntity"), _altova_ti_xs_altova_CanyType, _altova_mif_altova_CAnatomicEntity, _altova_mil_altova_CAnatomicEntity,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T("AnatomicEntityCharacteristic"), _altova_ti_xs_altova_CanyType, _altova_mif_altova_CAnatomicEntityCharacteristic, _altova_mil_altova_CAnatomicEntityCharacteristic,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T("Annotation"), _altova_ti_xs_altova_CanyType, _altova_mif_altova_CAnnotation, _altova_mil_altova_CAnnotation,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T("AnnotationOfAnnotation"), _altova_ti_altova_CAnnotation, _altova_mif_altova_CAnnotationOfAnnotation, _altova_mil_altova_CAnnotationOfAnnotation,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T("AnnotationRole"), _altova_ti_xs_altova_CanyType, _altova_mif_altova_CAnnotationRole, _altova_mil_altova_CAnnotationRole,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T("Calculation"), _altova_ti_xs_altova_CanyType, _altova_mif_altova_CCalculation, _altova_mil_altova_CCalculation,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T("CalculationData"), _altova_ti_xs_altova_CanyType, _altova_mif_altova_CCalculationData, _altova_mil_altova_CCalculationData,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T("CalculationResult"), _altova_ti_xs_altova_CanyType, _altova_mif_altova_CCalculationResult, _altova_mil_altova_CCalculationResult,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T("CalculationResultIdentifier"), _altova_ti_xs_altova_Cstring, _altova_mif_altova_CCalculationResultIdentifier, _altova_mil_altova_CCalculationResultIdentifier,  0 , altova::Whitespace_Unknown, &altova::AnySimpleTypeFormatter },
	{ &binder, _altova_ni, _T("CharacteristicQuantification"), _altova_ti_xs_altova_CanyType, _altova_mif_altova_CCharacteristicQuantification, _altova_mil_altova_CCharacteristicQuantification,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T("Circle"), _altova_ti_altova_CGeometricShape, _altova_mif_altova_CCircle, _altova_mil_altova_CCircle,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T("ComparisonOperators"), _altova_ti_xs_altova_Cstring, _altova_mif_altova_CComparisonOperators, _altova_mil_altova_CComparisonOperators,  6 , altova::Whitespace_Unknown, &altova::AnySimpleTypeFormatter },
	{ &binder, _altova_ni, _T("Coordinate"), _altova_ti_xs_altova_CanyType, _altova_mif_altova_CCoordinate, _altova_mil_altova_CCoordinate,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T("DICOMImageReference"), _altova_ti_altova_CImageReference, _altova_mif_altova_CDICOMImageReference, _altova_mil_altova_CDICOMImageReference,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T("Dimension"), _altova_ti_xs_altova_CanyType, _altova_mif_altova_CDimension, _altova_mil_altova_CDimension,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T("Ellipse"), _altova_ti_altova_CGeometricShape, _altova_mif_altova_CEllipse, _altova_mil_altova_CEllipse,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T("Equipment"), _altova_ti_xs_altova_CanyType, _altova_mif_altova_CEquipment, _altova_mil_altova_CEquipment,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T("GeometricShape"), _altova_ti_xs_altova_CanyType, _altova_mif_altova_CGeometricShape, _altova_mil_altova_CGeometricShape,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T("Image"), _altova_ti_xs_altova_CanyType, _altova_mif_altova_CImage, _altova_mil_altova_CImage,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T("ImageAnnotation"), _altova_ti_altova_CAnnotation, _altova_mif_altova_CImageAnnotation, _altova_mil_altova_CImageAnnotation,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T("ImageReference"), _altova_ti_xs_altova_CanyType, _altova_mif_altova_CImageReference, _altova_mil_altova_CImageReference,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T("ImageSeries"), _altova_ti_xs_altova_CanyType, _altova_mif_altova_CImageSeries, _altova_mil_altova_CImageSeries,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T("ImageStudy"), _altova_ti_xs_altova_CanyType, _altova_mif_altova_CImageStudy, _altova_mil_altova_CImageStudy,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T("ImagingObservation"), _altova_ti_xs_altova_CanyType, _altova_mif_altova_CImagingObservation, _altova_mil_altova_CImagingObservation,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T("ImagingObservationCharacteristic"), _altova_ti_xs_altova_CanyType, _altova_mif_altova_CImagingObservationCharacteristic, _altova_mil_altova_CImagingObservationCharacteristic,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T("Inference"), _altova_ti_xs_altova_CanyType, _altova_mif_altova_CInference, _altova_mil_altova_CInference,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T("Interval"), _altova_ti_altova_CCharacteristicQuantification, _altova_mif_altova_CInterval, _altova_mil_altova_CInterval,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T("MultiPoint"), _altova_ti_altova_CGeometricShape, _altova_mif_altova_CMultiPoint, _altova_mil_altova_CMultiPoint,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T("NonQuantifiable"), _altova_ti_altova_CCharacteristicQuantification, _altova_mif_altova_CNonQuantifiable, _altova_mil_altova_CNonQuantifiable,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T("Numerical"), _altova_ti_altova_CCharacteristicQuantification, _altova_mif_altova_CNumerical, _altova_mil_altova_CNumerical,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T("Person"), _altova_ti_xs_altova_CanyType, _altova_mif_altova_CPerson, _altova_mil_altova_CPerson,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T("Point"), _altova_ti_altova_CGeometricShape, _altova_mif_altova_CPoint, _altova_mil_altova_CPoint,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T("Polyline"), _altova_ti_altova_CGeometricShape, _altova_mif_altova_CPolyline, _altova_mil_altova_CPolyline,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T("PresentationState"), _altova_ti_xs_altova_CanyType, _altova_mif_altova_CPresentationState, _altova_mil_altova_CPresentationState,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T("Quantile"), _altova_ti_altova_CCharacteristicQuantification, _altova_mif_altova_CQuantile, _altova_mil_altova_CQuantile,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T("ReferencedAnnotation"), _altova_ti_xs_altova_CanyType, _altova_mif_altova_CReferencedAnnotation, _altova_mil_altova_CReferencedAnnotation,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T("ReferencedCalculation"), _altova_ti_xs_altova_CanyType, _altova_mif_altova_CReferencedCalculation, _altova_mil_altova_CReferencedCalculation,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T("ReferencedGeometricShape"), _altova_ti_xs_altova_CanyType, _altova_mif_altova_CReferencedGeometricShape, _altova_mil_altova_CReferencedGeometricShape,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T("Scale"), _altova_ti_altova_CCharacteristicQuantification, _altova_mif_altova_CScale, _altova_mil_altova_CScale,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T("Segmentation"), _altova_ti_xs_altova_CanyType, _altova_mif_altova_CSegmentation, _altova_mil_altova_CSegmentation,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T("SpatialCoordinate"), _altova_ti_xs_altova_CanyType, _altova_mif_altova_CSpatialCoordinate, _altova_mil_altova_CSpatialCoordinate,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T("TextAnnotation"), _altova_ti_xs_altova_CanyType, _altova_mif_altova_CTextAnnotation, _altova_mil_altova_CTextAnnotation,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T("ThreeDimensionSpatialCoordinate"), _altova_ti_altova_CSpatialCoordinate, _altova_mif_altova_CThreeDimensionSpatialCoordinate, _altova_mil_altova_CThreeDimensionSpatialCoordinate,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T("TwoDimensionSpatialCoordinate"), _altova_ti_altova_CSpatialCoordinate, _altova_mif_altova_CTwoDimensionSpatialCoordinate, _altova_mil_altova_CTwoDimensionSpatialCoordinate,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T("User"), _altova_ti_xs_altova_CanyType, _altova_mif_altova_CUser, _altova_mil_altova_CUser,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T("WebImageReference"), _altova_ti_altova_CImageReference, _altova_mif_altova_CWebImageReference, _altova_mil_altova_CWebImageReference,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T("AIMXML"), ~0, _altova_mif_altova_CAIMXML, _altova_mil_altova_CAIMXML,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T(""), _altova_ti_xs_altova_CanyType, _altova_mif_altova_CanatomicEntityCharacteristicCollectionType, _altova_mil_altova_CanatomicEntityCharacteristicCollectionType,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T(""), _altova_ti_xs_altova_CanyType, _altova_mif_altova_CcharacteristicQuantificationCollectionType, _altova_mil_altova_CcharacteristicQuantificationCollectionType,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T(""), _altova_ti_xs_altova_CanyType, _altova_mif_altova_CcalculationCollectionType, _altova_mil_altova_CcalculationCollectionType,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T(""), _altova_ti_xs_altova_CanyType, _altova_mif_altova_CinferenceCollectionType, _altova_mil_altova_CinferenceCollectionType,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T(""), _altova_ti_xs_altova_CanyType, _altova_mif_altova_CuserType, _altova_mil_altova_CuserType,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T(""), _altova_ti_xs_altova_CanyType, _altova_mif_altova_CequipmentType, _altova_mil_altova_CequipmentType,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T(""), _altova_ti_xs_altova_CanyType, _altova_mif_altova_CanatomicEntityCollectionType, _altova_mil_altova_CanatomicEntityCollectionType,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T(""), _altova_ti_xs_altova_CanyType, _altova_mif_altova_CimagingObservationCollectionType, _altova_mil_altova_CimagingObservationCollectionType,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T(""), _altova_ti_xs_altova_CanyType, _altova_mif_altova_CaimStatusType, _altova_mil_altova_CaimStatusType,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T(""), _altova_ti_xs_altova_CanyType, _altova_mif_altova_CreferencedAnnotationCollectionType, _altova_mil_altova_CreferencedAnnotationCollectionType,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T(""), _altova_ti_xs_altova_CanyType, _altova_mif_altova_CreferencedCalculationCollectionType, _altova_mil_altova_CreferencedCalculationCollectionType,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T(""), _altova_ti_xs_altova_CanyType, _altova_mif_altova_CcalculationResultCollectionType, _altova_mil_altova_CcalculationResultCollectionType,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T(""), _altova_ti_xs_altova_CanyType, _altova_mif_altova_CreferencedGeometricShapeCollectionType, _altova_mil_altova_CreferencedGeometricShapeCollectionType,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T(""), _altova_ti_xs_altova_CanyType, _altova_mif_altova_CcoordinateCollectionType, _altova_mil_altova_CcoordinateCollectionType,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T(""), _altova_ti_xs_altova_CanyType, _altova_mif_altova_CcalculationDataCollectionType, _altova_mil_altova_CcalculationDataCollectionType,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T(""), _altova_ti_xs_altova_CanyType, _altova_mif_altova_CdimensionCollectionType, _altova_mil_altova_CdimensionCollectionType,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T(""), _altova_ti_xs_altova_CanyType, _altova_mif_altova_CspatialCoordinateCollectionType, _altova_mil_altova_CspatialCoordinateCollectionType,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T(""), _altova_ti_xs_altova_CanyType, _altova_mif_altova_CimageStudyType, _altova_mil_altova_CimageStudyType,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T(""), _altova_ti_xs_altova_CanyType, _altova_mif_altova_CpresentationStateCollectionType, _altova_mil_altova_CpresentationStateCollectionType,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T(""), _altova_ti_xs_altova_CanyType, _altova_mif_altova_CsegmentationCollectionType, _altova_mil_altova_CsegmentationCollectionType,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T(""), _altova_ti_xs_altova_CanyType, _altova_mif_altova_CimageReferenceCollectionType, _altova_mil_altova_CimageReferenceCollectionType,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T(""), _altova_ti_xs_altova_CanyType, _altova_mif_altova_CgeometricShapeCollectionType, _altova_mil_altova_CgeometricShapeCollectionType,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T(""), _altova_ti_xs_altova_CanyType, _altova_mif_altova_CpersonType, _altova_mil_altova_CpersonType,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T(""), _altova_ti_xs_altova_CanyType, _altova_mif_altova_CtextAnnotationCollectionType, _altova_mil_altova_CtextAnnotationCollectionType,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T(""), _altova_ti_xs_altova_CanyType, _altova_mif_altova_CimageCollectionType, _altova_mil_altova_CimageCollectionType,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T(""), _altova_ti_xs_altova_CanyType, _altova_mif_altova_CimageSeriesType, _altova_mil_altova_CimageSeriesType,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T(""), _altova_ti_xs_altova_CanyType, _altova_mif_altova_CimagingObservationCharacteristicCollectionType, _altova_mil_altova_CimagingObservationCharacteristicCollectionType,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T(""), _altova_ti_xs_altova_CanyType, _altova_mif_altova_CreferencedGeometricShapeType, _altova_mil_altova_CreferencedGeometricShapeType,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T(""), _altova_ti_xs_altova_CanyType, _altova_mif_altova_CcharacteristicQuantificationCollectionType2, _altova_mil_altova_CcharacteristicQuantificationCollectionType2,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T(""), _altova_ti_xs_altova_CanyType, _altova_mif_altova_CannotationRoleType, _altova_mil_altova_CannotationRoleType,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T(""), _altova_ti_xs_altova_CanyType, _altova_mif_altova_CimagingObservationType, _altova_mil_altova_CimagingObservationType,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni, _T(""), _altova_ti_xs_altova_CanyType, _altova_mif_altova_CmultiPointType, _altova_mil_altova_CmultiPointType,  ~0 , altova::Whitespace_Unknown },

	{ &binder, _altova_ni_xs, _T("ENTITIES"), _altova_ti_xs_altova_CanySimpleType, _altova_mif_xs_altova_CENTITIES, _altova_mil_xs_altova_CENTITIES,  13 , altova::Whitespace_Collapse, &altova::AnySimpleTypeFormatter },
	{ &binder, _altova_ni_xs, _T("ENTITY"), _altova_ti_xs_altova_CNCName, _altova_mif_xs_altova_CENTITY, _altova_mil_xs_altova_CENTITY,  ~0 , altova::Whitespace_Unknown, &altova::AnySimpleTypeFormatter },
	{ &binder, _altova_ni_xs, _T("ID"), _altova_ti_xs_altova_CNCName, _altova_mif_xs_altova_CID, _altova_mil_xs_altova_CID,  ~0 , altova::Whitespace_Unknown, &altova::AnySimpleTypeFormatter },
	{ &binder, _altova_ni_xs, _T("IDREF"), _altova_ti_xs_altova_CNCName, _altova_mif_xs_altova_CIDREF, _altova_mil_xs_altova_CIDREF,  ~0 , altova::Whitespace_Unknown, &altova::AnySimpleTypeFormatter },
	{ &binder, _altova_ni_xs, _T("IDREFS"), _altova_ti_xs_altova_CanySimpleType, _altova_mif_xs_altova_CIDREFS, _altova_mil_xs_altova_CIDREFS,  16 , altova::Whitespace_Collapse, &altova::AnySimpleTypeFormatter },
	{ &binder, _altova_ni_xs, _T("NCName"), _altova_ti_xs_altova_CName, _altova_mif_xs_altova_CNCName, _altova_mil_xs_altova_CNCName,  19 , altova::Whitespace_Unknown, &altova::AnySimpleTypeFormatter },
	{ &binder, _altova_ni_xs, _T("NMTOKEN"), _altova_ti_xs_altova_Ctoken, _altova_mif_xs_altova_CNMTOKEN, _altova_mil_xs_altova_CNMTOKEN,  21 , altova::Whitespace_Unknown, &altova::AnySimpleTypeFormatter },
	{ &binder, _altova_ni_xs, _T("NMTOKENS"), _altova_ti_xs_altova_CanySimpleType, _altova_mif_xs_altova_CNMTOKENS, _altova_mil_xs_altova_CNMTOKENS,  23 , altova::Whitespace_Collapse, &altova::AnySimpleTypeFormatter },
	{ &binder, _altova_ni_xs, _T("NOTATION"), _altova_ti_xs_altova_CanySimpleType, _altova_mif_xs_altova_CNOTATION, _altova_mil_xs_altova_CNOTATION,  28 , altova::Whitespace_Collapse, &altova::AnySimpleTypeFormatter },
	{ &binder, _altova_ni_xs, _T("Name"), _altova_ti_xs_altova_Ctoken, _altova_mif_xs_altova_CName, _altova_mil_xs_altova_CName,  30 , altova::Whitespace_Unknown, &altova::AnySimpleTypeFormatter },
	{ &binder, _altova_ni_xs, _T("QName"), _altova_ti_xs_altova_CanySimpleType, _altova_mif_xs_altova_CQName, _altova_mil_xs_altova_CQName,  32 , altova::Whitespace_Collapse, &altova::AnySimpleTypeFormatter },
	{ &binder, _altova_ni_xs, _T("anySimpleType"), ~0, _altova_mif_xs_altova_CanySimpleType, _altova_mil_xs_altova_CanySimpleType,  ~0 , altova::Whitespace_Unknown, &altova::AnySimpleTypeFormatter },
	{ &binder, _altova_ni_xs, _T("anyType"), ~0, _altova_mif_xs_altova_CanyType, _altova_mil_xs_altova_CanyType,  ~0 , altova::Whitespace_Unknown, &altova::AnySimpleTypeFormatter },
	{ &binder, _altova_ni_xs, _T("anyURI"), _altova_ti_xs_altova_CanySimpleType, _altova_mif_xs_altova_CanyURI, _altova_mil_xs_altova_CanyURI,  34 , altova::Whitespace_Collapse, &altova::AnySimpleTypeFormatter },
	{ &binder, _altova_ni_xs, _T("base64Binary"), _altova_ti_xs_altova_CanySimpleType, _altova_mif_xs_altova_Cbase64Binary, _altova_mil_xs_altova_Cbase64Binary,  36 , altova::Whitespace_Collapse, &altova::AnySimpleTypeFormatter },
	{ &binder, _altova_ni_xs, _T("boolean"), _altova_ti_xs_altova_CanySimpleType, _altova_mif_xs_altova_Cboolean, _altova_mil_xs_altova_Cboolean,  38 , altova::Whitespace_Collapse, &altova::AnySimpleTypeFormatter },
	{ &binder, _altova_ni_xs, _T("byte"), _altova_ti_xs_altova_Cshort, _altova_mif_xs_altova_Cbyte, _altova_mil_xs_altova_Cbyte,  40 , altova::Whitespace_Unknown, &altova::IntegerFormatter },
	{ &binder, _altova_ni_xs, _T("date"), _altova_ti_xs_altova_CanySimpleType, _altova_mif_xs_altova_Cdate, _altova_mil_xs_altova_Cdate,  43 , altova::Whitespace_Collapse, &altova::DateFormatter },
	{ &binder, _altova_ni_xs, _T("dateTime"), _altova_ti_xs_altova_CanySimpleType, _altova_mif_xs_altova_CdateTime, _altova_mil_xs_altova_CdateTime,  45 , altova::Whitespace_Collapse, &altova::DateTimeFormatter },
	{ &binder, _altova_ni_xs, _T("decimal"), _altova_ti_xs_altova_CanySimpleType, _altova_mif_xs_altova_Cdecimal, _altova_mil_xs_altova_Cdecimal,  47 , altova::Whitespace_Collapse, &altova::DecimalFormatter },
	{ &binder, _altova_ni_xs, _T("double"), _altova_ti_xs_altova_CanySimpleType, _altova_mif_xs_altova_Cdouble, _altova_mil_xs_altova_Cdouble,  49 , altova::Whitespace_Collapse, &altova::DoubleFormatter },
	{ &binder, _altova_ni_xs, _T("duration"), _altova_ti_xs_altova_CanySimpleType, _altova_mif_xs_altova_Cduration, _altova_mil_xs_altova_Cduration,  51 , altova::Whitespace_Collapse, &altova::AnySimpleTypeFormatter },
	{ &binder, _altova_ni_xs, _T("float"), _altova_ti_xs_altova_CanySimpleType, _altova_mif_xs_altova_Cfloat, _altova_mil_xs_altova_Cfloat,  53 , altova::Whitespace_Collapse, &altova::DoubleFormatter },
	{ &binder, _altova_ni_xs, _T("gDay"), _altova_ti_xs_altova_CanySimpleType, _altova_mif_xs_altova_CgDay, _altova_mil_xs_altova_CgDay,  55 , altova::Whitespace_Collapse, &altova::GDayFormatter },
	{ &binder, _altova_ni_xs, _T("gMonth"), _altova_ti_xs_altova_CanySimpleType, _altova_mif_xs_altova_CgMonth, _altova_mil_xs_altova_CgMonth,  57 , altova::Whitespace_Collapse, &altova::GMonthFormatter },
	{ &binder, _altova_ni_xs, _T("gMonthDay"), _altova_ti_xs_altova_CanySimpleType, _altova_mif_xs_altova_CgMonthDay, _altova_mil_xs_altova_CgMonthDay,  59 , altova::Whitespace_Collapse, &altova::GMonthDayFormatter },
	{ &binder, _altova_ni_xs, _T("gYear"), _altova_ti_xs_altova_CanySimpleType, _altova_mif_xs_altova_CgYear, _altova_mil_xs_altova_CgYear,  61 , altova::Whitespace_Collapse, &altova::GYearFormatter },
	{ &binder, _altova_ni_xs, _T("gYearMonth"), _altova_ti_xs_altova_CanySimpleType, _altova_mif_xs_altova_CgYearMonth, _altova_mil_xs_altova_CgYearMonth,  63 , altova::Whitespace_Collapse, &altova::GYearMonthFormatter },
	{ &binder, _altova_ni_xs, _T("hexBinary"), _altova_ti_xs_altova_CanySimpleType, _altova_mif_xs_altova_ChexBinary, _altova_mil_xs_altova_ChexBinary,  65 , altova::Whitespace_Collapse, &altova::HexBinaryFormatter },
	{ &binder, _altova_ni_xs, _T("int"), _altova_ti_xs_altova_Clong, _altova_mif_xs_altova_Cint, _altova_mil_xs_altova_Cint,  67 , altova::Whitespace_Unknown, &altova::IntegerFormatter },
	{ &binder, _altova_ni_xs, _T("integer"), _altova_ti_xs_altova_Cdecimal, _altova_mif_xs_altova_Cinteger, _altova_mil_xs_altova_Cinteger,  70 , altova::Whitespace_Unknown, &altova::IntegerFormatter },
	{ &binder, _altova_ni_xs, _T("language"), _altova_ti_xs_altova_Ctoken, _altova_mif_xs_altova_Clanguage, _altova_mil_xs_altova_Clanguage,  73 , altova::Whitespace_Unknown, &altova::AnySimpleTypeFormatter },
	{ &binder, _altova_ni_xs, _T("long"), _altova_ti_xs_altova_Cinteger, _altova_mif_xs_altova_Clong, _altova_mil_xs_altova_Clong,  75 , altova::Whitespace_Unknown, &altova::IntegerFormatter },
	{ &binder, _altova_ni_xs, _T("negativeInteger"), _altova_ti_xs_altova_CnonPositiveInteger, _altova_mif_xs_altova_CnegativeInteger, _altova_mil_xs_altova_CnegativeInteger,  78 , altova::Whitespace_Unknown, &altova::IntegerFormatter },
	{ &binder, _altova_ni_xs, _T("nonNegativeInteger"), _altova_ti_xs_altova_Cinteger, _altova_mif_xs_altova_CnonNegativeInteger, _altova_mil_xs_altova_CnonNegativeInteger,  80 , altova::Whitespace_Unknown, &altova::IntegerFormatter },
	{ &binder, _altova_ni_xs, _T("nonPositiveInteger"), _altova_ti_xs_altova_Cinteger, _altova_mif_xs_altova_CnonPositiveInteger, _altova_mil_xs_altova_CnonPositiveInteger,  82 , altova::Whitespace_Unknown, &altova::IntegerFormatter },
	{ &binder, _altova_ni_xs, _T("normalizedString"), _altova_ti_xs_altova_Cstring, _altova_mif_xs_altova_CnormalizedString, _altova_mil_xs_altova_CnormalizedString,  84 , altova::Whitespace_Replace, &altova::AnySimpleTypeFormatter },
	{ &binder, _altova_ni_xs, _T("positiveInteger"), _altova_ti_xs_altova_CnonNegativeInteger, _altova_mif_xs_altova_CpositiveInteger, _altova_mil_xs_altova_CpositiveInteger,  86 , altova::Whitespace_Unknown, &altova::IntegerFormatter },
	{ &binder, _altova_ni_xs, _T("short"), _altova_ti_xs_altova_Cint, _altova_mif_xs_altova_Cshort, _altova_mil_xs_altova_Cshort,  88 , altova::Whitespace_Unknown, &altova::IntegerFormatter },
	{ &binder, _altova_ni_xs, _T("string"), _altova_ti_xs_altova_CanySimpleType, _altova_mif_xs_altova_Cstring, _altova_mil_xs_altova_Cstring,  91 , altova::Whitespace_Preserve, &altova::AnySimpleTypeFormatter },
	{ &binder, _altova_ni_xs, _T("time"), _altova_ti_xs_altova_CanySimpleType, _altova_mif_xs_altova_Ctime, _altova_mil_xs_altova_Ctime,  93 , altova::Whitespace_Collapse, &altova::TimeFormatter },
	{ &binder, _altova_ni_xs, _T("token"), _altova_ti_xs_altova_CnormalizedString, _altova_mif_xs_altova_Ctoken, _altova_mil_xs_altova_Ctoken,  95 , altova::Whitespace_Collapse, &altova::AnySimpleTypeFormatter },
	{ &binder, _altova_ni_xs, _T("unsignedByte"), _altova_ti_xs_altova_CunsignedShort, _altova_mif_xs_altova_CunsignedByte, _altova_mil_xs_altova_CunsignedByte,  97 , altova::Whitespace_Unknown, &altova::IntegerFormatter },
	{ &binder, _altova_ni_xs, _T("unsignedInt"), _altova_ti_xs_altova_CunsignedLong, _altova_mif_xs_altova_CunsignedInt, _altova_mil_xs_altova_CunsignedInt,  99 , altova::Whitespace_Unknown, &altova::IntegerFormatter },
	{ &binder, _altova_ni_xs, _T("unsignedLong"), _altova_ti_xs_altova_CnonNegativeInteger, _altova_mif_xs_altova_CunsignedLong, _altova_mil_xs_altova_CunsignedLong,  101 , altova::Whitespace_Unknown, &altova::IntegerFormatter },
	{ &binder, _altova_ni_xs, _T("unsignedShort"), _altova_ti_xs_altova_CunsignedInt, _altova_mif_xs_altova_CunsignedShort, _altova_mil_xs_altova_CunsignedShort,  103 , altova::Whitespace_Unknown, &altova::IntegerFormatter },

{ 0 },
};

const altova::MemberInfo members[] = 
{
	{ &binder, _T(""), _T("cagridId"), _altova_ti_altova_CAimStatus, _altova_ti_xs_altova_Cinteger, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("annotationVersion"), _altova_ti_altova_CAimStatus, _altova_ti_xs_altova_Cdouble, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("codeValue"), _altova_ti_altova_CAimStatus, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("codeMeaning"), _altova_ti_altova_CAimStatus, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("codingSchemeDesignator"), _altova_ti_altova_CAimStatus, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("codingSchemeVersion"), _altova_ti_altova_CAimStatus, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 0, 1 },
	{ &binder, _T(""), _T("authorizedBy"), _altova_ti_altova_CAimStatus, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 0, 1 },

	{ &binder, _T(""), _T("cagridId"), _altova_ti_altova_CAnatomicEntity, _altova_ti_xs_altova_Cinteger, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("codeValue"), _altova_ti_altova_CAnatomicEntity, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("codeMeaning"), _altova_ti_altova_CAnatomicEntity, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("codingSchemeDesignator"), _altova_ti_altova_CAnatomicEntity, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("codingSchemeVersion"), _altova_ti_altova_CAnatomicEntity, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 0, 1 },
	{ &binder, _T(""), _T("annotatorConfidence"), _altova_ti_altova_CAnatomicEntity, _altova_ti_xs_altova_Cdouble, MemberFlags_IsAttribute, 0, 1 },
	{ &binder, _T(""), _T("isPresent"), _altova_ti_altova_CAnatomicEntity, _altova_ti_xs_altova_Cboolean, MemberFlags_IsAttribute, 0, 1 },
	{ &binder, _T(""), _T("label"), _altova_ti_altova_CAnatomicEntity, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("anatomicEntityCharacteristicCollection"), _altova_ti_altova_CAnatomicEntity, _altova_ti_altova_CanatomicEntityCharacteristicCollectionType, MemberFlags_None, 0, 1 },

	{ &binder, _T(""), _T("cagridId"), _altova_ti_altova_CAnatomicEntityCharacteristic, _altova_ti_xs_altova_Cinteger, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("codeValue"), _altova_ti_altova_CAnatomicEntityCharacteristic, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("codeMeaning"), _altova_ti_altova_CAnatomicEntityCharacteristic, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("codingSchemeDesignator"), _altova_ti_altova_CAnatomicEntityCharacteristic, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("codingSchemeVersion"), _altova_ti_altova_CAnatomicEntityCharacteristic, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 0, 1 },
	{ &binder, _T(""), _T("annotatorConfidence"), _altova_ti_altova_CAnatomicEntityCharacteristic, _altova_ti_xs_altova_Cdouble, MemberFlags_IsAttribute, 0, 1 },
	{ &binder, _T(""), _T("label"), _altova_ti_altova_CAnatomicEntityCharacteristic, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("characteristicQuantificationCollection"), _altova_ti_altova_CAnatomicEntityCharacteristic, _altova_ti_altova_CcharacteristicQuantificationCollectionType, MemberFlags_None, 0, 1 },

	{ &binder, _T(""), _T("cagridId"), _altova_ti_altova_CAnnotation, _altova_ti_xs_altova_Cinteger, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("aimVersion"), _altova_ti_altova_CAnnotation, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("comment"), _altova_ti_altova_CAnnotation, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 0, 1 },
	{ &binder, _T(""), _T("dateTime"), _altova_ti_altova_CAnnotation, _altova_ti_xs_altova_CdateTime, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("name"), _altova_ti_altova_CAnnotation, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("uniqueIdentifier"), _altova_ti_altova_CAnnotation, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("codeValue"), _altova_ti_altova_CAnnotation, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("codeMeaning"), _altova_ti_altova_CAnnotation, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("codingSchemeDesignator"), _altova_ti_altova_CAnnotation, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("codingSchemeVersion"), _altova_ti_altova_CAnnotation, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 0, 1 },
	{ &binder, _T(""), _T("precedentReferencedAnnotationUID"), _altova_ti_altova_CAnnotation, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 0, 1 },
	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("calculationCollection"), _altova_ti_altova_CAnnotation, _altova_ti_altova_CcalculationCollectionType, MemberFlags_None, 0, 1 },
	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("inferenceCollection"), _altova_ti_altova_CAnnotation, _altova_ti_altova_CinferenceCollectionType, MemberFlags_None, 0, 1 },
	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("user"), _altova_ti_altova_CAnnotation, _altova_ti_altova_CuserType, MemberFlags_None, 0, 1 },
	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("equipment"), _altova_ti_altova_CAnnotation, _altova_ti_altova_CequipmentType, MemberFlags_None, 0, 1 },
	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("anatomicEntityCollection"), _altova_ti_altova_CAnnotation, _altova_ti_altova_CanatomicEntityCollectionType, MemberFlags_None, 0, 1 },
	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("imagingObservationCollection"), _altova_ti_altova_CAnnotation, _altova_ti_altova_CimagingObservationCollectionType, MemberFlags_None, 0, 1 },
	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("aimStatus"), _altova_ti_altova_CAnnotation, _altova_ti_altova_CaimStatusType, MemberFlags_None, 0, 1 },

	{ &binder, _T(""), _T("cagridId"), _altova_ti_altova_CAnnotationOfAnnotation, _altova_ti_xs_altova_Cinteger, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("aimVersion"), _altova_ti_altova_CAnnotationOfAnnotation, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("comment"), _altova_ti_altova_CAnnotationOfAnnotation, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 0, 1 },
	{ &binder, _T(""), _T("dateTime"), _altova_ti_altova_CAnnotationOfAnnotation, _altova_ti_xs_altova_CdateTime, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("name"), _altova_ti_altova_CAnnotationOfAnnotation, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("uniqueIdentifier"), _altova_ti_altova_CAnnotationOfAnnotation, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("codeValue"), _altova_ti_altova_CAnnotationOfAnnotation, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("codeMeaning"), _altova_ti_altova_CAnnotationOfAnnotation, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("codingSchemeDesignator"), _altova_ti_altova_CAnnotationOfAnnotation, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("codingSchemeVersion"), _altova_ti_altova_CAnnotationOfAnnotation, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 0, 1 },
	{ &binder, _T(""), _T("precedentReferencedAnnotationUID"), _altova_ti_altova_CAnnotationOfAnnotation, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 0, 1 },
	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("calculationCollection"), _altova_ti_altova_CAnnotationOfAnnotation, _altova_ti_altova_CcalculationCollectionType, MemberFlags_None, 0, 1 },
	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("inferenceCollection"), _altova_ti_altova_CAnnotationOfAnnotation, _altova_ti_altova_CinferenceCollectionType, MemberFlags_None, 0, 1 },
	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("user"), _altova_ti_altova_CAnnotationOfAnnotation, _altova_ti_altova_CuserType, MemberFlags_None, 0, 1 },
	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("equipment"), _altova_ti_altova_CAnnotationOfAnnotation, _altova_ti_altova_CequipmentType, MemberFlags_None, 0, 1 },
	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("anatomicEntityCollection"), _altova_ti_altova_CAnnotationOfAnnotation, _altova_ti_altova_CanatomicEntityCollectionType, MemberFlags_None, 0, 1 },
	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("imagingObservationCollection"), _altova_ti_altova_CAnnotationOfAnnotation, _altova_ti_altova_CimagingObservationCollectionType, MemberFlags_None, 0, 1 },
	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("aimStatus"), _altova_ti_altova_CAnnotationOfAnnotation, _altova_ti_altova_CaimStatusType, MemberFlags_None, 0, 1 },
	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("referencedAnnotationCollection"), _altova_ti_altova_CAnnotationOfAnnotation, _altova_ti_altova_CreferencedAnnotationCollectionType, MemberFlags_None, 1, 1 },

	{ &binder, _T(""), _T("cagridId"), _altova_ti_altova_CAnnotationRole, _altova_ti_xs_altova_Cinteger, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("codeValue"), _altova_ti_altova_CAnnotationRole, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("codeMeaning"), _altova_ti_altova_CAnnotationRole, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("codingSchemeDesignator"), _altova_ti_altova_CAnnotationRole, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("codingSchemeVersion"), _altova_ti_altova_CAnnotationRole, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 0, 1 },
	{ &binder, _T(""), _T("roleSequenceNumber"), _altova_ti_altova_CAnnotationRole, _altova_ti_xs_altova_Cinteger, MemberFlags_IsAttribute, 1, 1 },

	{ &binder, _T(""), _T("cagridId"), _altova_ti_altova_CCalculation, _altova_ti_xs_altova_Cinteger, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("uid"), _altova_ti_altova_CCalculation, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("description"), _altova_ti_altova_CCalculation, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("mathML"), _altova_ti_altova_CCalculation, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 0, 1 },
	{ &binder, _T(""), _T("codeValue"), _altova_ti_altova_CCalculation, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("codeMeaning"), _altova_ti_altova_CCalculation, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("codingSchemeDesignator"), _altova_ti_altova_CCalculation, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("codingSchemeVersion"), _altova_ti_altova_CCalculation, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 0, 1 },
	{ &binder, _T(""), _T("algorithmName"), _altova_ti_altova_CCalculation, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 0, 1 },
	{ &binder, _T(""), _T("algorithmVersion"), _altova_ti_altova_CCalculation, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 0, 1 },
	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("referencedCalculationCollection"), _altova_ti_altova_CCalculation, _altova_ti_altova_CreferencedCalculationCollectionType, MemberFlags_None, 0, 1 },
	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("calculationResultCollection"), _altova_ti_altova_CCalculation, _altova_ti_altova_CcalculationResultCollectionType, MemberFlags_None, 0, 1 },
	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("referencedGeometricShapeCollection"), _altova_ti_altova_CCalculation, _altova_ti_altova_CreferencedGeometricShapeCollectionType, MemberFlags_None, 0, 1 },

	{ &binder, _T(""), _T("cagridId"), _altova_ti_altova_CCalculationData, _altova_ti_xs_altova_Cinteger, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("value"), _altova_ti_altova_CCalculationData, _altova_ti_xs_altova_Cdouble, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("coordinateCollection"), _altova_ti_altova_CCalculationData, _altova_ti_altova_CcoordinateCollectionType, MemberFlags_None, 1, 1 },

	{ &binder, _T(""), _T("cagridId"), _altova_ti_altova_CCalculationResult, _altova_ti_xs_altova_Cinteger, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("type"), _altova_ti_altova_CCalculationResult, _altova_ti_altova_CCalculationResultIdentifier, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("numberOfDimensions"), _altova_ti_altova_CCalculationResult, _altova_ti_xs_altova_Cinteger, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("unitOfMeasure"), _altova_ti_altova_CCalculationResult, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("calculationDataCollection"), _altova_ti_altova_CCalculationResult, _altova_ti_altova_CcalculationDataCollectionType, MemberFlags_None, 0, 1 },
	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("dimensionCollection"), _altova_ti_altova_CCalculationResult, _altova_ti_altova_CdimensionCollectionType, MemberFlags_None, 1, 1 },

	{ &binder, _T(""), _T("cagridId"), _altova_ti_altova_CCharacteristicQuantification, _altova_ti_xs_altova_Cinteger, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("name"), _altova_ti_altova_CCharacteristicQuantification, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("annotatorConfidence"), _altova_ti_altova_CCharacteristicQuantification, _altova_ti_xs_altova_Cdouble, MemberFlags_IsAttribute, 0, 1 },

	{ &binder, _T(""), _T("cagridId"), _altova_ti_altova_CCircle, _altova_ti_xs_altova_Cinteger, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("lineColor"), _altova_ti_altova_CCircle, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 0, 1 },
	{ &binder, _T(""), _T("lineOpacity"), _altova_ti_altova_CCircle, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 0, 1 },
	{ &binder, _T(""), _T("lineStyle"), _altova_ti_altova_CCircle, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 0, 1 },
	{ &binder, _T(""), _T("lineThickness"), _altova_ti_altova_CCircle, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 0, 1 },
	{ &binder, _T(""), _T("includeFlag"), _altova_ti_altova_CCircle, _altova_ti_xs_altova_Cboolean, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("shapeIdentifier"), _altova_ti_altova_CCircle, _altova_ti_xs_altova_Cinteger, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("spatialCoordinateCollection"), _altova_ti_altova_CCircle, _altova_ti_altova_CspatialCoordinateCollectionType, MemberFlags_None, 1, 1 },

	{ &binder, _T(""), _T("cagridId"), _altova_ti_altova_CCoordinate, _altova_ti_xs_altova_Cinteger, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("dimensionIndex"), _altova_ti_altova_CCoordinate, _altova_ti_xs_altova_Cinteger, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("position"), _altova_ti_altova_CCoordinate, _altova_ti_xs_altova_Cinteger, MemberFlags_IsAttribute, 1, 1 },

	{ &binder, _T(""), _T("cagridId"), _altova_ti_altova_CDICOMImageReference, _altova_ti_xs_altova_Cinteger, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("imageStudy"), _altova_ti_altova_CDICOMImageReference, _altova_ti_altova_CimageStudyType, MemberFlags_None, 1, 1 },
	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("presentationStateCollection"), _altova_ti_altova_CDICOMImageReference, _altova_ti_altova_CpresentationStateCollectionType, MemberFlags_None, 0, 1 },

	{ &binder, _T(""), _T("cagridId"), _altova_ti_altova_CDimension, _altova_ti_xs_altova_Cinteger, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("index"), _altova_ti_altova_CDimension, _altova_ti_xs_altova_Cinteger, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("size"), _altova_ti_altova_CDimension, _altova_ti_xs_altova_Cinteger, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("label"), _altova_ti_altova_CDimension, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },

	{ &binder, _T(""), _T("cagridId"), _altova_ti_altova_CEllipse, _altova_ti_xs_altova_Cinteger, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("lineColor"), _altova_ti_altova_CEllipse, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 0, 1 },
	{ &binder, _T(""), _T("lineOpacity"), _altova_ti_altova_CEllipse, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 0, 1 },
	{ &binder, _T(""), _T("lineStyle"), _altova_ti_altova_CEllipse, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 0, 1 },
	{ &binder, _T(""), _T("lineThickness"), _altova_ti_altova_CEllipse, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 0, 1 },
	{ &binder, _T(""), _T("includeFlag"), _altova_ti_altova_CEllipse, _altova_ti_xs_altova_Cboolean, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("shapeIdentifier"), _altova_ti_altova_CEllipse, _altova_ti_xs_altova_Cinteger, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("spatialCoordinateCollection"), _altova_ti_altova_CEllipse, _altova_ti_altova_CspatialCoordinateCollectionType, MemberFlags_None, 1, 1 },

	{ &binder, _T(""), _T("cagridId"), _altova_ti_altova_CEquipment, _altova_ti_xs_altova_Cinteger, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("manufacturerName"), _altova_ti_altova_CEquipment, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("manufacturerModelName"), _altova_ti_altova_CEquipment, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 0, 1 },
	{ &binder, _T(""), _T("softwareVersion"), _altova_ti_altova_CEquipment, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 0, 1 },

	{ &binder, _T(""), _T("cagridId"), _altova_ti_altova_CGeometricShape, _altova_ti_xs_altova_Cinteger, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("lineColor"), _altova_ti_altova_CGeometricShape, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 0, 1 },
	{ &binder, _T(""), _T("lineOpacity"), _altova_ti_altova_CGeometricShape, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 0, 1 },
	{ &binder, _T(""), _T("lineStyle"), _altova_ti_altova_CGeometricShape, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 0, 1 },
	{ &binder, _T(""), _T("lineThickness"), _altova_ti_altova_CGeometricShape, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 0, 1 },
	{ &binder, _T(""), _T("includeFlag"), _altova_ti_altova_CGeometricShape, _altova_ti_xs_altova_Cboolean, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("shapeIdentifier"), _altova_ti_altova_CGeometricShape, _altova_ti_xs_altova_Cinteger, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("spatialCoordinateCollection"), _altova_ti_altova_CGeometricShape, _altova_ti_altova_CspatialCoordinateCollectionType, MemberFlags_None, 1, 1 },

	{ &binder, _T(""), _T("cagridId"), _altova_ti_altova_CImage, _altova_ti_xs_altova_Cinteger, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("sopClassUID"), _altova_ti_altova_CImage, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("sopInstanceUID"), _altova_ti_altova_CImage, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },

	{ &binder, _T(""), _T("cagridId"), _altova_ti_altova_CImageAnnotation, _altova_ti_xs_altova_Cinteger, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("aimVersion"), _altova_ti_altova_CImageAnnotation, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("comment"), _altova_ti_altova_CImageAnnotation, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 0, 1 },
	{ &binder, _T(""), _T("dateTime"), _altova_ti_altova_CImageAnnotation, _altova_ti_xs_altova_CdateTime, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("name"), _altova_ti_altova_CImageAnnotation, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("uniqueIdentifier"), _altova_ti_altova_CImageAnnotation, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("codeValue"), _altova_ti_altova_CImageAnnotation, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("codeMeaning"), _altova_ti_altova_CImageAnnotation, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("codingSchemeDesignator"), _altova_ti_altova_CImageAnnotation, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("codingSchemeVersion"), _altova_ti_altova_CImageAnnotation, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 0, 1 },
	{ &binder, _T(""), _T("precedentReferencedAnnotationUID"), _altova_ti_altova_CImageAnnotation, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 0, 1 },
	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("calculationCollection"), _altova_ti_altova_CImageAnnotation, _altova_ti_altova_CcalculationCollectionType, MemberFlags_None, 0, 1 },
	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("inferenceCollection"), _altova_ti_altova_CImageAnnotation, _altova_ti_altova_CinferenceCollectionType, MemberFlags_None, 0, 1 },
	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("user"), _altova_ti_altova_CImageAnnotation, _altova_ti_altova_CuserType, MemberFlags_None, 0, 1 },
	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("equipment"), _altova_ti_altova_CImageAnnotation, _altova_ti_altova_CequipmentType, MemberFlags_None, 0, 1 },
	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("anatomicEntityCollection"), _altova_ti_altova_CImageAnnotation, _altova_ti_altova_CanatomicEntityCollectionType, MemberFlags_None, 0, 1 },
	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("imagingObservationCollection"), _altova_ti_altova_CImageAnnotation, _altova_ti_altova_CimagingObservationCollectionType, MemberFlags_None, 0, 1 },
	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("aimStatus"), _altova_ti_altova_CImageAnnotation, _altova_ti_altova_CaimStatusType, MemberFlags_None, 0, 1 },
	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("segmentationCollection"), _altova_ti_altova_CImageAnnotation, _altova_ti_altova_CsegmentationCollectionType, MemberFlags_None, 0, 1 },
	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("imageReferenceCollection"), _altova_ti_altova_CImageAnnotation, _altova_ti_altova_CimageReferenceCollectionType, MemberFlags_None, 1, 1 },
	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("geometricShapeCollection"), _altova_ti_altova_CImageAnnotation, _altova_ti_altova_CgeometricShapeCollectionType, MemberFlags_None, 0, 1 },
	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("person"), _altova_ti_altova_CImageAnnotation, _altova_ti_altova_CpersonType, MemberFlags_None, 1, 1 },
	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("textAnnotationCollection"), _altova_ti_altova_CImageAnnotation, _altova_ti_altova_CtextAnnotationCollectionType, MemberFlags_None, 0, 1 },

	{ &binder, _T(""), _T("cagridId"), _altova_ti_altova_CImageReference, _altova_ti_xs_altova_Cinteger, MemberFlags_IsAttribute, 1, 1 },

	{ &binder, _T(""), _T("cagridId"), _altova_ti_altova_CImageSeries, _altova_ti_xs_altova_Cinteger, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("instanceUID"), _altova_ti_altova_CImageSeries, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("imageCollection"), _altova_ti_altova_CImageSeries, _altova_ti_altova_CimageCollectionType, MemberFlags_None, 1, 1 },

	{ &binder, _T(""), _T("cagridId"), _altova_ti_altova_CImageStudy, _altova_ti_xs_altova_Cinteger, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("instanceUID"), _altova_ti_altova_CImageStudy, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("startDate"), _altova_ti_altova_CImageStudy, _altova_ti_xs_altova_CdateTime, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("startTime"), _altova_ti_altova_CImageStudy, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("imageSeries"), _altova_ti_altova_CImageStudy, _altova_ti_altova_CimageSeriesType, MemberFlags_None, 1, 1 },

	{ &binder, _T(""), _T("cagridId"), _altova_ti_altova_CImagingObservation, _altova_ti_xs_altova_Cinteger, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("codeValue"), _altova_ti_altova_CImagingObservation, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("codeMeaning"), _altova_ti_altova_CImagingObservation, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("codingSchemeDesignator"), _altova_ti_altova_CImagingObservation, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("codingSchemeVersion"), _altova_ti_altova_CImagingObservation, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 0, 1 },
	{ &binder, _T(""), _T("comment"), _altova_ti_altova_CImagingObservation, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 0, 1 },
	{ &binder, _T(""), _T("annotatorConfidence"), _altova_ti_altova_CImagingObservation, _altova_ti_xs_altova_Cdouble, MemberFlags_IsAttribute, 0, 1 },
	{ &binder, _T(""), _T("isPresent"), _altova_ti_altova_CImagingObservation, _altova_ti_xs_altova_Cboolean, MemberFlags_IsAttribute, 0, 1 },
	{ &binder, _T(""), _T("label"), _altova_ti_altova_CImagingObservation, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("imagingObservationCharacteristicCollection"), _altova_ti_altova_CImagingObservation, _altova_ti_altova_CimagingObservationCharacteristicCollectionType, MemberFlags_None, 0, 1 },
	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("referencedGeometricShape"), _altova_ti_altova_CImagingObservation, _altova_ti_altova_CreferencedGeometricShapeType, MemberFlags_None, 0, 1 },

	{ &binder, _T(""), _T("cagridId"), _altova_ti_altova_CImagingObservationCharacteristic, _altova_ti_xs_altova_Cinteger, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("codeValue"), _altova_ti_altova_CImagingObservationCharacteristic, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("codeMeaning"), _altova_ti_altova_CImagingObservationCharacteristic, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("codingSchemeDesignator"), _altova_ti_altova_CImagingObservationCharacteristic, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("codingSchemeVersion"), _altova_ti_altova_CImagingObservationCharacteristic, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 0, 1 },
	{ &binder, _T(""), _T("comment"), _altova_ti_altova_CImagingObservationCharacteristic, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 0, 1 },
	{ &binder, _T(""), _T("annotatorConfidence"), _altova_ti_altova_CImagingObservationCharacteristic, _altova_ti_xs_altova_Cdouble, MemberFlags_IsAttribute, 0, 1 },
	{ &binder, _T(""), _T("label"), _altova_ti_altova_CImagingObservationCharacteristic, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("characteristicQuantificationCollection"), _altova_ti_altova_CImagingObservationCharacteristic, _altova_ti_altova_CcharacteristicQuantificationCollectionType2, MemberFlags_None, 0, 1 },

	{ &binder, _T(""), _T("cagridId"), _altova_ti_altova_CInference, _altova_ti_xs_altova_Cinteger, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("codeValue"), _altova_ti_altova_CInference, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("codeMeaning"), _altova_ti_altova_CInference, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("codingSchemeDesignator"), _altova_ti_altova_CInference, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("codingSchemeVersion"), _altova_ti_altova_CInference, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 0, 1 },
	{ &binder, _T(""), _T("annotatorConfidence"), _altova_ti_altova_CInference, _altova_ti_xs_altova_Cdouble, MemberFlags_IsAttribute, 0, 1 },
	{ &binder, _T(""), _T("imageEvidence"), _altova_ti_altova_CInference, _altova_ti_xs_altova_Cboolean, MemberFlags_IsAttribute, 1, 1 },

	{ &binder, _T(""), _T("cagridId"), _altova_ti_altova_CInterval, _altova_ti_xs_altova_Cinteger, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("name"), _altova_ti_altova_CInterval, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("annotatorConfidence"), _altova_ti_altova_CInterval, _altova_ti_xs_altova_Cdouble, MemberFlags_IsAttribute, 0, 1 },
	{ &binder, _T(""), _T("minValue"), _altova_ti_altova_CInterval, _altova_ti_xs_altova_Cdouble, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("maxValue"), _altova_ti_altova_CInterval, _altova_ti_xs_altova_Cdouble, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("minOperator"), _altova_ti_altova_CInterval, _altova_ti_altova_CComparisonOperators, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("ucumString"), _altova_ti_altova_CInterval, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("maxOperator"), _altova_ti_altova_CInterval, _altova_ti_altova_CComparisonOperators, MemberFlags_IsAttribute, 1, 1 },

	{ &binder, _T(""), _T("cagridId"), _altova_ti_altova_CMultiPoint, _altova_ti_xs_altova_Cinteger, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("lineColor"), _altova_ti_altova_CMultiPoint, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 0, 1 },
	{ &binder, _T(""), _T("lineOpacity"), _altova_ti_altova_CMultiPoint, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 0, 1 },
	{ &binder, _T(""), _T("lineStyle"), _altova_ti_altova_CMultiPoint, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 0, 1 },
	{ &binder, _T(""), _T("lineThickness"), _altova_ti_altova_CMultiPoint, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 0, 1 },
	{ &binder, _T(""), _T("includeFlag"), _altova_ti_altova_CMultiPoint, _altova_ti_xs_altova_Cboolean, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("shapeIdentifier"), _altova_ti_altova_CMultiPoint, _altova_ti_xs_altova_Cinteger, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("spatialCoordinateCollection"), _altova_ti_altova_CMultiPoint, _altova_ti_altova_CspatialCoordinateCollectionType, MemberFlags_None, 1, 1 },

	{ &binder, _T(""), _T("cagridId"), _altova_ti_altova_CNonQuantifiable, _altova_ti_xs_altova_Cinteger, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("name"), _altova_ti_altova_CNonQuantifiable, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("annotatorConfidence"), _altova_ti_altova_CNonQuantifiable, _altova_ti_xs_altova_Cdouble, MemberFlags_IsAttribute, 0, 1 },
	{ &binder, _T(""), _T("codeValue"), _altova_ti_altova_CNonQuantifiable, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("codeMeaning"), _altova_ti_altova_CNonQuantifiable, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("codingSchemeDesignator"), _altova_ti_altova_CNonQuantifiable, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("codingSchemeVersion"), _altova_ti_altova_CNonQuantifiable, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 0, 1 },

	{ &binder, _T(""), _T("cagridId"), _altova_ti_altova_CNumerical, _altova_ti_xs_altova_Cinteger, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("name"), _altova_ti_altova_CNumerical, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("annotatorConfidence"), _altova_ti_altova_CNumerical, _altova_ti_xs_altova_Cdouble, MemberFlags_IsAttribute, 0, 1 },
	{ &binder, _T(""), _T("ucumString"), _altova_ti_altova_CNumerical, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("value"), _altova_ti_altova_CNumerical, _altova_ti_xs_altova_Cdouble, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("operator"), _altova_ti_altova_CNumerical, _altova_ti_altova_CComparisonOperators, MemberFlags_IsAttribute, 0, 1 },

	{ &binder, _T(""), _T("cagridId"), _altova_ti_altova_CPerson, _altova_ti_xs_altova_Cinteger, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("name"), _altova_ti_altova_CPerson, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("id"), _altova_ti_altova_CPerson, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("birthDate"), _altova_ti_altova_CPerson, _altova_ti_xs_altova_CdateTime, MemberFlags_IsAttribute, 0, 1 },
	{ &binder, _T(""), _T("sex"), _altova_ti_altova_CPerson, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 0, 1 },
	{ &binder, _T(""), _T("ethnicGroup"), _altova_ti_altova_CPerson, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 0, 1 },

	{ &binder, _T(""), _T("cagridId"), _altova_ti_altova_CPoint, _altova_ti_xs_altova_Cinteger, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("lineColor"), _altova_ti_altova_CPoint, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 0, 1 },
	{ &binder, _T(""), _T("lineOpacity"), _altova_ti_altova_CPoint, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 0, 1 },
	{ &binder, _T(""), _T("lineStyle"), _altova_ti_altova_CPoint, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 0, 1 },
	{ &binder, _T(""), _T("lineThickness"), _altova_ti_altova_CPoint, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 0, 1 },
	{ &binder, _T(""), _T("includeFlag"), _altova_ti_altova_CPoint, _altova_ti_xs_altova_Cboolean, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("shapeIdentifier"), _altova_ti_altova_CPoint, _altova_ti_xs_altova_Cinteger, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("spatialCoordinateCollection"), _altova_ti_altova_CPoint, _altova_ti_altova_CspatialCoordinateCollectionType, MemberFlags_None, 1, 1 },

	{ &binder, _T(""), _T("cagridId"), _altova_ti_altova_CPolyline, _altova_ti_xs_altova_Cinteger, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("lineColor"), _altova_ti_altova_CPolyline, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 0, 1 },
	{ &binder, _T(""), _T("lineOpacity"), _altova_ti_altova_CPolyline, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 0, 1 },
	{ &binder, _T(""), _T("lineStyle"), _altova_ti_altova_CPolyline, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 0, 1 },
	{ &binder, _T(""), _T("lineThickness"), _altova_ti_altova_CPolyline, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 0, 1 },
	{ &binder, _T(""), _T("includeFlag"), _altova_ti_altova_CPolyline, _altova_ti_xs_altova_Cboolean, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("shapeIdentifier"), _altova_ti_altova_CPolyline, _altova_ti_xs_altova_Cinteger, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("spatialCoordinateCollection"), _altova_ti_altova_CPolyline, _altova_ti_altova_CspatialCoordinateCollectionType, MemberFlags_None, 1, 1 },

	{ &binder, _T(""), _T("cagridId"), _altova_ti_altova_CPresentationState, _altova_ti_xs_altova_Cinteger, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("sopInstanceUID"), _altova_ti_altova_CPresentationState, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },

	{ &binder, _T(""), _T("cagridId"), _altova_ti_altova_CQuantile, _altova_ti_xs_altova_Cinteger, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("name"), _altova_ti_altova_CQuantile, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("annotatorConfidence"), _altova_ti_altova_CQuantile, _altova_ti_xs_altova_Cdouble, MemberFlags_IsAttribute, 0, 1 },
	{ &binder, _T(""), _T("bin"), _altova_ti_altova_CQuantile, _altova_ti_xs_altova_Cinteger, MemberFlags_IsAttribute, 1, 1 },

	{ &binder, _T(""), _T("cagridId"), _altova_ti_altova_CReferencedAnnotation, _altova_ti_xs_altova_Cinteger, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("referencedAnnotationUID"), _altova_ti_altova_CReferencedAnnotation, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("annotationRole"), _altova_ti_altova_CReferencedAnnotation, _altova_ti_altova_CannotationRoleType, MemberFlags_None, 0, 1 },

	{ &binder, _T(""), _T("cagridId"), _altova_ti_altova_CReferencedCalculation, _altova_ti_xs_altova_Cinteger, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("uniqueIdentifier"), _altova_ti_altova_CReferencedCalculation, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },

	{ &binder, _T(""), _T("cagridId"), _altova_ti_altova_CReferencedGeometricShape, _altova_ti_xs_altova_Cinteger, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("referencedShapeIdentifier"), _altova_ti_altova_CReferencedGeometricShape, _altova_ti_xs_altova_Cinteger, MemberFlags_IsAttribute, 1, 1 },

	{ &binder, _T(""), _T("cagridId"), _altova_ti_altova_CScale, _altova_ti_xs_altova_Cinteger, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("name"), _altova_ti_altova_CScale, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("annotatorConfidence"), _altova_ti_altova_CScale, _altova_ti_xs_altova_Cdouble, MemberFlags_IsAttribute, 0, 1 },
	{ &binder, _T(""), _T("comment"), _altova_ti_altova_CScale, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 0, 1 },
	{ &binder, _T(""), _T("description"), _altova_ti_altova_CScale, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 0, 1 },
	{ &binder, _T(""), _T("value"), _altova_ti_altova_CScale, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },

	{ &binder, _T(""), _T("cagridId"), _altova_ti_altova_CSegmentation, _altova_ti_xs_altova_Cinteger, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("sopInstanceUID"), _altova_ti_altova_CSegmentation, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("sopClassUID"), _altova_ti_altova_CSegmentation, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("referencedSopInstanceUID"), _altova_ti_altova_CSegmentation, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("segmentNumber"), _altova_ti_altova_CSegmentation, _altova_ti_xs_altova_Cinteger, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("imagingObservation"), _altova_ti_altova_CSegmentation, _altova_ti_altova_CimagingObservationType, MemberFlags_None, 0, 1 },

	{ &binder, _T(""), _T("cagridId"), _altova_ti_altova_CSpatialCoordinate, _altova_ti_xs_altova_Cinteger, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("coordinateIndex"), _altova_ti_altova_CSpatialCoordinate, _altova_ti_xs_altova_Cinteger, MemberFlags_IsAttribute, 1, 1 },

	{ &binder, _T(""), _T("cagridId"), _altova_ti_altova_CTextAnnotation, _altova_ti_xs_altova_Cinteger, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("font"), _altova_ti_altova_CTextAnnotation, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 0, 1 },
	{ &binder, _T(""), _T("fontColor"), _altova_ti_altova_CTextAnnotation, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 0, 1 },
	{ &binder, _T(""), _T("fontEffect"), _altova_ti_altova_CTextAnnotation, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 0, 1 },
	{ &binder, _T(""), _T("fontSize"), _altova_ti_altova_CTextAnnotation, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 0, 1 },
	{ &binder, _T(""), _T("fontStyle"), _altova_ti_altova_CTextAnnotation, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 0, 1 },
	{ &binder, _T(""), _T("text"), _altova_ti_altova_CTextAnnotation, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("textJustify"), _altova_ti_altova_CTextAnnotation, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 0, 1 },
	{ &binder, _T(""), _T("fontOpacity"), _altova_ti_altova_CTextAnnotation, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 0, 1 },
	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("multiPoint"), _altova_ti_altova_CTextAnnotation, _altova_ti_altova_CmultiPointType, MemberFlags_None, 0, 1 },

	{ &binder, _T(""), _T("cagridId"), _altova_ti_altova_CThreeDimensionSpatialCoordinate, _altova_ti_xs_altova_Cinteger, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("coordinateIndex"), _altova_ti_altova_CThreeDimensionSpatialCoordinate, _altova_ti_xs_altova_Cinteger, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("x"), _altova_ti_altova_CThreeDimensionSpatialCoordinate, _altova_ti_xs_altova_Cdouble, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("y"), _altova_ti_altova_CThreeDimensionSpatialCoordinate, _altova_ti_xs_altova_Cdouble, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("z"), _altova_ti_altova_CThreeDimensionSpatialCoordinate, _altova_ti_xs_altova_Cdouble, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("frameOfReferenceUID"), _altova_ti_altova_CThreeDimensionSpatialCoordinate, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },

	{ &binder, _T(""), _T("cagridId"), _altova_ti_altova_CTwoDimensionSpatialCoordinate, _altova_ti_xs_altova_Cinteger, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("coordinateIndex"), _altova_ti_altova_CTwoDimensionSpatialCoordinate, _altova_ti_xs_altova_Cinteger, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("imageReferenceUID"), _altova_ti_altova_CTwoDimensionSpatialCoordinate, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("referencedFrameNumber"), _altova_ti_altova_CTwoDimensionSpatialCoordinate, _altova_ti_xs_altova_Cinteger, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("x"), _altova_ti_altova_CTwoDimensionSpatialCoordinate, _altova_ti_xs_altova_Cdouble, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("y"), _altova_ti_altova_CTwoDimensionSpatialCoordinate, _altova_ti_xs_altova_Cdouble, MemberFlags_IsAttribute, 1, 1 },

	{ &binder, _T(""), _T("cagridId"), _altova_ti_altova_CUser, _altova_ti_xs_altova_Cinteger, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("name"), _altova_ti_altova_CUser, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("loginName"), _altova_ti_altova_CUser, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("roleInTrial"), _altova_ti_altova_CUser, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 0, 1 },
	{ &binder, _T(""), _T("numberWithinRoleOfClinicalTrial"), _altova_ti_altova_CUser, _altova_ti_xs_altova_Cinteger, MemberFlags_IsAttribute, 0, 1 },

	{ &binder, _T(""), _T("cagridId"), _altova_ti_altova_CWebImageReference, _altova_ti_xs_altova_Cinteger, MemberFlags_IsAttribute, 1, 1 },
	{ &binder, _T(""), _T("uri"), _altova_ti_altova_CWebImageReference, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },

	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("AnnotationOfAnnotation"), _altova_ti_altova_CAIMXML, _altova_ti_altova_CAnnotationOfAnnotation, MemberFlags_None, 0, 1 },
	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("ImageAnnotation"), _altova_ti_altova_CAIMXML, _altova_ti_altova_CImageAnnotation, MemberFlags_None, 0, 1 },

	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("AnatomicEntityCharacteristic"), _altova_ti_altova_CanatomicEntityCharacteristicCollectionType, _altova_ti_altova_CAnatomicEntityCharacteristic, MemberFlags_None, 0, -1 },

	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("CharacteristicQuantification"), _altova_ti_altova_CcharacteristicQuantificationCollectionType, _altova_ti_altova_CCharacteristicQuantification, MemberFlags_None, 0, -1 },

	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("Calculation"), _altova_ti_altova_CcalculationCollectionType, _altova_ti_altova_CCalculation, MemberFlags_None, 0, -1 },

	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("Inference"), _altova_ti_altova_CinferenceCollectionType, _altova_ti_altova_CInference, MemberFlags_None, 0, -1 },

	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("User"), _altova_ti_altova_CuserType, _altova_ti_altova_CUser, MemberFlags_None, 0, 1 },

	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("Equipment"), _altova_ti_altova_CequipmentType, _altova_ti_altova_CEquipment, MemberFlags_None, 0, 1 },

	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("AnatomicEntity"), _altova_ti_altova_CanatomicEntityCollectionType, _altova_ti_altova_CAnatomicEntity, MemberFlags_None, 0, -1 },

	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("ImagingObservation"), _altova_ti_altova_CimagingObservationCollectionType, _altova_ti_altova_CImagingObservation, MemberFlags_None, 0, -1 },

	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("AimStatus"), _altova_ti_altova_CaimStatusType, _altova_ti_altova_CAimStatus, MemberFlags_None, 0, 1 },

	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("ReferencedAnnotation"), _altova_ti_altova_CreferencedAnnotationCollectionType, _altova_ti_altova_CReferencedAnnotation, MemberFlags_None, 1, -1 },

	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("ReferencedCalculation"), _altova_ti_altova_CreferencedCalculationCollectionType, _altova_ti_altova_CReferencedCalculation, MemberFlags_None, 0, -1 },

	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("CalculationResult"), _altova_ti_altova_CcalculationResultCollectionType, _altova_ti_altova_CCalculationResult, MemberFlags_None, 0, -1 },

	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("ReferencedGeometricShape"), _altova_ti_altova_CreferencedGeometricShapeCollectionType, _altova_ti_altova_CReferencedGeometricShape, MemberFlags_None, 0, -1 },

	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("Coordinate"), _altova_ti_altova_CcoordinateCollectionType, _altova_ti_altova_CCoordinate, MemberFlags_None, 1, -1 },

	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("CalculationData"), _altova_ti_altova_CcalculationDataCollectionType, _altova_ti_altova_CCalculationData, MemberFlags_None, 0, -1 },

	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("Dimension"), _altova_ti_altova_CdimensionCollectionType, _altova_ti_altova_CDimension, MemberFlags_None, 1, -1 },

	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("SpatialCoordinate"), _altova_ti_altova_CspatialCoordinateCollectionType, _altova_ti_altova_CSpatialCoordinate, MemberFlags_None, 1, -1 },

	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("ImageStudy"), _altova_ti_altova_CimageStudyType, _altova_ti_altova_CImageStudy, MemberFlags_None, 1, 1 },

	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("PresentationState"), _altova_ti_altova_CpresentationStateCollectionType, _altova_ti_altova_CPresentationState, MemberFlags_None, 0, -1 },

	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("Segmentation"), _altova_ti_altova_CsegmentationCollectionType, _altova_ti_altova_CSegmentation, MemberFlags_None, 0, -1 },

	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("ImageReference"), _altova_ti_altova_CimageReferenceCollectionType, _altova_ti_altova_CImageReference, MemberFlags_None, 1, -1 },

	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("GeometricShape"), _altova_ti_altova_CgeometricShapeCollectionType, _altova_ti_altova_CGeometricShape, MemberFlags_None, 0, -1 },

	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("Person"), _altova_ti_altova_CpersonType, _altova_ti_altova_CPerson, MemberFlags_None, 1, 1 },

	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("TextAnnotation"), _altova_ti_altova_CtextAnnotationCollectionType, _altova_ti_altova_CTextAnnotation, MemberFlags_None, 0, -1 },

	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("Image"), _altova_ti_altova_CimageCollectionType, _altova_ti_altova_CImage, MemberFlags_None, 1, -1 },

	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("ImageSeries"), _altova_ti_altova_CimageSeriesType, _altova_ti_altova_CImageSeries, MemberFlags_None, 1, 1 },

	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("ImagingObservationCharacteristic"), _altova_ti_altova_CimagingObservationCharacteristicCollectionType, _altova_ti_altova_CImagingObservationCharacteristic, MemberFlags_None, 0, -1 },

	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("ReferencedGeometricShape"), _altova_ti_altova_CreferencedGeometricShapeType, _altova_ti_altova_CReferencedGeometricShape, MemberFlags_None, 0, 1 },

	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("CharacteristicQuantification"), _altova_ti_altova_CcharacteristicQuantificationCollectionType2, _altova_ti_altova_CCharacteristicQuantification, MemberFlags_None, 0, -1 },

	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("AnnotationRole"), _altova_ti_altova_CannotationRoleType, _altova_ti_altova_CAnnotationRole, MemberFlags_None, 0, 1 },

	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("ImagingObservation"), _altova_ti_altova_CimagingObservationType, _altova_ti_altova_CImagingObservation, MemberFlags_None, 0, 1 },

	{ &binder, _T("gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIM"), _T("MultiPoint"), _altova_ti_altova_CmultiPointType, _altova_ti_altova_CMultiPoint, MemberFlags_None, 0, 1 },

	{ &binder, _T(""), _T(""), _altova_ti_xs_altova_CanyType, _altova_ti_xs_altova_CanySimpleType, MemberFlags_IsAttribute, 0, -1 },

{ 0 },
};

const altova::FacetInfo facets[] = 
{
	// CalculationResultIdentifier
	{ 0, _T("enumeration"), _T("Scalar"), 0 }, 
	{ 0, _T("enumeration"), _T("Vector"), 0 }, 
	{ 0, _T("enumeration"), _T("Histogram"), 0 }, 
	{ 0, _T("enumeration"), _T("Matrix"), 0 }, 
	{ 0, _T("enumeration"), _T("Array"), 0 }, 
	{ 0, 0, 0, 0 },
	// ComparisonOperators
	{ 0, _T("enumeration"), _T("Equal"), 0 }, 
	{ 0, _T("enumeration"), _T("NotEqual"), 0 }, 
	{ 0, _T("enumeration"), _T("LessThan"), 0 }, 
	{ 0, _T("enumeration"), _T("LessThanEqual"), 0 }, 
	{ 0, _T("enumeration"), _T("GreaterThan"), 0 }, 
	{ 0, _T("enumeration"), _T("GreaterThanEqual"), 0 }, 
	{ 0, 0, 0, 0 },
	// ENTITIES
	{ 0, _T("whitespace"), _T("collapse"), 0 },
	{ 0, _T("minLength"), _T("1"), 1 }, 
	{ 0, 0, 0, 0 },
	// IDREFS
	{ 0, _T("whitespace"), _T("collapse"), 0 },
	{ 0, _T("minLength"), _T("1"), 1 }, 
	{ 0, 0, 0, 0 },
	// NCName
	{ 0, _T("pattern"), _T("[\\i-[:]][\\c-[:]]*"), 0 }, 
	{ 0, 0, 0, 0 },
	// NMTOKEN
	{ 0, _T("pattern"), _T("\\c+"), 0 }, 
	{ 0, 0, 0, 0 },
	// NMTOKENS
	{ 0, _T("whitespace"), _T("collapse"), 0 },
	{ 0, _T("minLength"), _T("1"), 1 }, 
	{ 0, _T("pattern"), _T("\\c+"), 0 }, 
	{ 0, _T("pattern"), _T("\\c+"), 0 }, 
	{ 0, 0, 0, 0 },
	// NOTATION
	{ 0, _T("whitespace"), _T("collapse"), 0 },
	{ 0, 0, 0, 0 },
	// Name
	{ 0, _T("pattern"), _T("\\i\\c*"), 0 }, 
	{ 0, 0, 0, 0 },
	// QName
	{ 0, _T("whitespace"), _T("collapse"), 0 },
	{ 0, 0, 0, 0 },
	// anyURI
	{ 0, _T("whitespace"), _T("collapse"), 0 },
	{ 0, 0, 0, 0 },
	// base64Binary
	{ 0, _T("whitespace"), _T("collapse"), 0 },
	{ 0, 0, 0, 0 },
	// boolean
	{ 0, _T("whitespace"), _T("collapse"), 0 },
	{ 0, 0, 0, 0 },
	// byte
	{ 0, _T("minInclusive"), _T("-128"), 0 }, 
	{ 0, _T("maxInclusive"), _T("127"), 0 }, 
	{ 0, 0, 0, 0 },
	// date
	{ 0, _T("whitespace"), _T("collapse"), 0 },
	{ 0, 0, 0, 0 },
	// dateTime
	{ 0, _T("whitespace"), _T("collapse"), 0 },
	{ 0, 0, 0, 0 },
	// decimal
	{ 0, _T("whitespace"), _T("collapse"), 0 },
	{ 0, 0, 0, 0 },
	// double
	{ 0, _T("whitespace"), _T("collapse"), 0 },
	{ 0, 0, 0, 0 },
	// duration
	{ 0, _T("whitespace"), _T("collapse"), 0 },
	{ 0, 0, 0, 0 },
	// float
	{ 0, _T("whitespace"), _T("collapse"), 0 },
	{ 0, 0, 0, 0 },
	// gDay
	{ 0, _T("whitespace"), _T("collapse"), 0 },
	{ 0, 0, 0, 0 },
	// gMonth
	{ 0, _T("whitespace"), _T("collapse"), 0 },
	{ 0, 0, 0, 0 },
	// gMonthDay
	{ 0, _T("whitespace"), _T("collapse"), 0 },
	{ 0, 0, 0, 0 },
	// gYear
	{ 0, _T("whitespace"), _T("collapse"), 0 },
	{ 0, 0, 0, 0 },
	// gYearMonth
	{ 0, _T("whitespace"), _T("collapse"), 0 },
	{ 0, 0, 0, 0 },
	// hexBinary
	{ 0, _T("whitespace"), _T("collapse"), 0 },
	{ 0, 0, 0, 0 },
	// int
	{ 0, _T("minInclusive"), _T("-2147483648"), 0 }, 
	{ 0, _T("maxInclusive"), _T("2147483647"), 0 }, 
	{ 0, 0, 0, 0 },
	// integer
	{ 0, _T("fractionDigits"), _T("0"), 0 }, 
	{ 0, _T("pattern"), _T("[\\-+]?[0-9]+"), 0 }, 
	{ 0, 0, 0, 0 },
	// language
	{ 0, _T("pattern"), _T("[a-zA-Z]{1,8}(-[a-zA-Z0-9]{1,8})*"), 0 }, 
	{ 0, 0, 0, 0 },
	// long
	{ 0, _T("minInclusive"), _T("-9223372036854775808"), 0 }, 
	{ 0, _T("maxInclusive"), _T("9223372036854775807"), 0 }, 
	{ 0, 0, 0, 0 },
	// negativeInteger
	{ 0, _T("maxInclusive"), _T("-1"), 0 }, 
	{ 0, 0, 0, 0 },
	// nonNegativeInteger
	{ 0, _T("minInclusive"), _T("0"), 0 }, 
	{ 0, 0, 0, 0 },
	// nonPositiveInteger
	{ 0, _T("maxInclusive"), _T("0"), 0 }, 
	{ 0, 0, 0, 0 },
	// normalizedString
	{ 0, _T("whitespace"), _T("replace"), 0 },
	{ 0, 0, 0, 0 },
	// positiveInteger
	{ 0, _T("minInclusive"), _T("1"), 0 }, 
	{ 0, 0, 0, 0 },
	// short
	{ 0, _T("minInclusive"), _T("-32768"), 0 }, 
	{ 0, _T("maxInclusive"), _T("32767"), 0 }, 
	{ 0, 0, 0, 0 },
	// string
	{ 0, _T("whitespace"), _T("preserve"), 0 },
	{ 0, 0, 0, 0 },
	// time
	{ 0, _T("whitespace"), _T("collapse"), 0 },
	{ 0, 0, 0, 0 },
	// token
	{ 0, _T("whitespace"), _T("collapse"), 0 },
	{ 0, 0, 0, 0 },
	// unsignedByte
	{ 0, _T("maxInclusive"), _T("255"), 0 }, 
	{ 0, 0, 0, 0 },
	// unsignedInt
	{ 0, _T("maxInclusive"), _T("4294967295"), 0 }, 
	{ 0, 0, 0, 0 },
	// unsignedLong
	{ 0, _T("maxInclusive"), _T("18446744073709551615"), 0 }, 
	{ 0, 0, 0, 0 },
	// unsignedShort
	{ 0, _T("maxInclusive"), _T("65535"), 0 }, 
	{ 0, 0, 0, 0 },
{ 0 },
};

}  // namespace AIMXML