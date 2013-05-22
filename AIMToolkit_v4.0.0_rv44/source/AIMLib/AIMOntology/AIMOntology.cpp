/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "StdAfx.h"
#include <string.h>
#include <tchar.h>
#include "AIMOntology.h"


#include "../AltovaXML/XercesString.h"




// turn off warning: "this" used in base initializer list
#pragma warning(disable:4355)


namespace AIMOntology
{


xercesc::DOMNode* TypeBase::GetElementNth(const altova::MemberInfo* member, unsigned index)
{
	for (XercesTreeOperations::MemberIterator it = XercesTreeOperations::GetElements(m_node, member); it; ++it)
	{
		if (index-- == 0)
			return *it;
	}
	return 0;
}

xercesc::DOMNode* TypeBase::GetElementLast(const altova::MemberInfo* member)
{
	xercesc::DOMNode* p;
	for (XercesTreeOperations::MemberIterator it = XercesTreeOperations::GetElements(m_node, member); it; ++it)
	{
		p = *it;
	}
	return p;
}

unsigned TypeBase::CountElement(const altova::MemberInfo* member)
{
	unsigned count = 0;
	for (XercesTreeOperations::MemberIterator it = XercesTreeOperations::GetElements(m_node, member); it; ++it)
	{
		++count;
	}
	return count;
}

void TypeBase::RemoveElement(const altova::MemberInfo* member)
{
	XercesTreeOperations::RemoveElements(m_node, member);
}



namespace aim
{	

CAnatomicEntityXML::CAnatomicEntityXML(xercesc::DOMNode* const& node)
: TypeBase(node)
, codeMeaning(*this)	// "codeMeaning"
, codingSchemeDesignator(*this)	// "codingSchemeDesignator"
, codeValue(*this)	// "codeValue"
, relationship(*this)	// "relationship"
, relatedAnatomicEntityXML(*this)	// "relatedAnatomicEntityXML"
{
}

CAnatomicEntityXML::CAnatomicEntityXML(CAnatomicEntityXML const& other)
: TypeBase(other.GetNode())
, codeMeaning(*this)	// "codeMeaning"
, codingSchemeDesignator(*this)	// "codingSchemeDesignator"
, codeValue(*this)	// "codeValue"
, relationship(*this)	// "relationship"
, relatedAnatomicEntityXML(*this)	// "relatedAnatomicEntityXML"
{
}

void CAnatomicEntityXML::SetXsiType()
{
	XercesTreeOperations::SetAttribute(m_node, _T("xsi:type"), _T("http://www.w3.org/2001/XMLSchema-instance"), 
		_T("AnatomicEntityXML"), _T("http://www.radiology.northwestern.edu/aim/1/ontology/1"));
}

CAnnotationDescriptionXML::CAnnotationDescriptionXML(xercesc::DOMNode* const& node)
: TypeBase(node)
, anatomicEntityCollectionXML(*this)	// "anatomicEntityCollectionXML"
, imagingObservationCollectionXML(*this)	// "imagingObservationCollectionXML"
{
}

CAnnotationDescriptionXML::CAnnotationDescriptionXML(CAnnotationDescriptionXML const& other)
: TypeBase(other.GetNode())
, anatomicEntityCollectionXML(*this)	// "anatomicEntityCollectionXML"
, imagingObservationCollectionXML(*this)	// "imagingObservationCollectionXML"
{
}

void CAnnotationDescriptionXML::SetXsiType()
{
	XercesTreeOperations::SetAttribute(m_node, _T("xsi:type"), _T("http://www.w3.org/2001/XMLSchema-instance"), 
		_T("AnnotationDescriptionXML"), _T("http://www.radiology.northwestern.edu/aim/1/ontology/1"));
}

CImagingObservationCharacteristicXML::CImagingObservationCharacteristicXML(xercesc::DOMNode* const& node)
: TypeBase(node)
, codeMeaning(*this)	// "codeMeaning"
, codingSchemeDesignator(*this)	// "codingSchemeDesignator"
, codeValue(*this)	// "codeValue"
, comment(*this)	// "comment"
, relationship(*this)	// "relationship"
, relatedImagingObservationCharacteristicXML(*this)	// "relatedImagingObservationCharacteristicXML"
{
}

CImagingObservationCharacteristicXML::CImagingObservationCharacteristicXML(CImagingObservationCharacteristicXML const& other)
: TypeBase(other.GetNode())
, codeMeaning(*this)	// "codeMeaning"
, codingSchemeDesignator(*this)	// "codingSchemeDesignator"
, codeValue(*this)	// "codeValue"
, comment(*this)	// "comment"
, relationship(*this)	// "relationship"
, relatedImagingObservationCharacteristicXML(*this)	// "relatedImagingObservationCharacteristicXML"
{
}

void CImagingObservationCharacteristicXML::SetXsiType()
{
	XercesTreeOperations::SetAttribute(m_node, _T("xsi:type"), _T("http://www.w3.org/2001/XMLSchema-instance"), 
		_T("ImagingObservationCharacteristicXML"), _T("http://www.radiology.northwestern.edu/aim/1/ontology/1"));
}

CImagingObservationXML::CImagingObservationXML(xercesc::DOMNode* const& node)
: TypeBase(node)
, codeMeaning(*this)	// "codeMeaning"
, codingSchemeDesignator(*this)	// "codingSchemeDesignator"
, codeValue(*this)	// "codeValue"
, comment(*this)	// "comment"
, relationship(*this)	// "relationship"
, relatedImagingObservationXML(*this)	// "relatedImagingObservationXML"
, imagingObservationCharacteristicCollectionXML(*this)	// "imagingObservationCharacteristicCollectionXML"
{
}

CImagingObservationXML::CImagingObservationXML(CImagingObservationXML const& other)
: TypeBase(other.GetNode())
, codeMeaning(*this)	// "codeMeaning"
, codingSchemeDesignator(*this)	// "codingSchemeDesignator"
, codeValue(*this)	// "codeValue"
, comment(*this)	// "comment"
, relationship(*this)	// "relationship"
, relatedImagingObservationXML(*this)	// "relatedImagingObservationXML"
, imagingObservationCharacteristicCollectionXML(*this)	// "imagingObservationCharacteristicCollectionXML"
{
}

void CImagingObservationXML::SetXsiType()
{
	XercesTreeOperations::SetAttribute(m_node, _T("xsi:type"), _T("http://www.w3.org/2001/XMLSchema-instance"), 
		_T("ImagingObservationXML"), _T("http://www.radiology.northwestern.edu/aim/1/ontology/1"));
}

CAIMOntology::CAIMOntology(xercesc::DOMNode* const& node)
: TypeBase(node)
, AnnotationDescriptionXML(*this)	// "AnnotationDescriptionXML"
{
}

CAIMOntology::CAIMOntology(CAIMOntology const& other)
: TypeBase(other.GetNode())
, AnnotationDescriptionXML(*this)	// "AnnotationDescriptionXML"
{
}

void CAIMOntology::SetXsiType()
{
	XercesTreeOperations::SetAttribute(m_node, _T("xsi:type"), _T("http://www.w3.org/2001/XMLSchema-instance"), 
		_T("AIMOntology"), _T("http://www.radiology.northwestern.edu/aim/1/ontology/1"));
}

CAIMOntology CAIMOntology::LoadFromFile(const string_type& fileName)
{
	return CAIMOntology(XercesTreeOperations::LoadDocument(fileName));
}

CAIMOntology CAIMOntology::LoadFromString(const string_type& text)
{
	return CAIMOntology(XercesTreeOperations::LoadXml(text));
}

void CAIMOntology::SaveToFile(const string_type& fileName, bool prettyPrint)
{
	XercesTreeOperations::SaveDocument(GetDocumentNode(), fileName, prettyPrint, _T("UTF-8"), false, false);
}

void CAIMOntology::SaveToFile(const string_type& fileName, bool prettyPrint, const string_type& encoding)
{
	XercesTreeOperations::SaveDocument(GetDocumentNode(), fileName, prettyPrint, encoding, _tcsicmp(encoding.c_str(), _T("UTF-16BE")) == 0, _tcsicmp(encoding.c_str(), _T("UTF-16")) == 0);
}

void CAIMOntology::SaveToFile(const string_type& fileName, bool prettyPrint, const string_type& encoding, bool bBigEndian, bool bBOM)
{
	XercesTreeOperations::SaveDocument(GetDocumentNode(), fileName, prettyPrint, encoding, bBigEndian, bBOM);
}

string_type CAIMOntology::SaveToString(bool prettyPrint)
{
	return XercesTreeOperations::SaveXml(GetDocumentNode(), prettyPrint);
}

CAIMOntology CAIMOntology::CreateDocument()
{
	return XercesTreeOperations::CreateDocument();
}

void CAIMOntology::DestroyDocument()
{
	XercesTreeOperations::DocumentType doc = GetDocumentNode();
	XercesTreeOperations::FreeDocument(doc);
	m_node = 0;
}

void CAIMOntology::SetDTDLocation(const string_type& dtdLocation)
{

	xercesc::DOMDocument* document = (xercesc::DOMDocument*)GetNode();
	xercesc::DOMDocumentType* doctype = document->getDoctype();
	if (doctype != 0)
	{
		document->removeChild(doctype);
	}

	xercesc::DOMElement* rootElement = document->getDocumentElement();
	if (rootElement == 0)
		throw altova::InvalidOperationException(_T("You have to add a root element before setting DTD location."));

	doctype = document->createDocumentType(rootElement->getNodeName(), XercesStringTemp(_T("")), XercesStringTemp(dtdLocation));
	document->insertBefore(doctype, rootElement);

}

void CAIMOntology::SetSchemaLocation(const string_type& schemaLocation)
{

	xercesc::DOMDocument* document = (xercesc::DOMDocument*)GetNode();
	xercesc::DOMElement* rootElement = document->getDocumentElement();
	if (rootElement == 0)
		throw altova::InvalidOperationException(_T("You have to add a root element before setting schema location."));

	string_type namespaceURI = XercesUnstringTemp(rootElement->getNamespaceURI());
	
	
	if (namespaceURI.empty())
		XercesTreeOperations::SetAttribute(rootElement, _T("xsi:noNamespaceSchemaLocation"), _T("http://www.w3.org/2001/XMLSchema-instance"), schemaLocation);
	else
		XercesTreeOperations::SetAttribute(rootElement, _T("xsi:schemaLocation"), _T("http://www.w3.org/2001/XMLSchema-instance"), namespaceURI + _T(" ") + schemaLocation);

}

CAIMOntology CAIMOntology::LoadFromBinary(const std::vector<unsigned char>& data)
{
	return XercesTreeOperations::LoadFromBinary(data);
}

std::vector<unsigned char> CAIMOntology::SaveToBinary(bool prettyPrint)
{
	return XercesTreeOperations::SaveToBinary((XercesTreeOperations::DocumentType)GetNode(), prettyPrint);
}

std::vector<unsigned char> CAIMOntology::SaveToBinary(bool prettyPrint, const string_type& encoding)
{
	std::vector<unsigned char> result;
	XercesTreeOperations::SaveToBinary(result, (XercesTreeOperations::DocumentType)GetNode(), prettyPrint, encoding, _tcsicmp(encoding.c_str(), _T("UTF-16BE")) == 0, _tcsicmp(encoding.c_str(), _T("UTF-16")) == 0);
	return result;
}

std::vector<unsigned char> CAIMOntology::SaveToBinary(bool prettyPrint, const string_type& encoding, bool bBigEndian, bool bBOM)
{
	std::vector<unsigned char> result;
	XercesTreeOperations::SaveToBinary(result, (XercesTreeOperations::DocumentType)GetNode(), prettyPrint, encoding, bBigEndian, bBOM);
	return result;
}




CrelatedAnatomicEntityXMLType::CrelatedAnatomicEntityXMLType(xercesc::DOMNode* const& node)
: TypeBase(node)
, AnatomicEntityXML(*this)	// "AnatomicEntityXML"
{
}

CrelatedAnatomicEntityXMLType::CrelatedAnatomicEntityXMLType(CrelatedAnatomicEntityXMLType const& other)
: TypeBase(other.GetNode())
, AnatomicEntityXML(*this)	// "AnatomicEntityXML"
{
}


CanatomicEntityCollectionXMLType::CanatomicEntityCollectionXMLType(xercesc::DOMNode* const& node)
: TypeBase(node)
, AnatomicEntityXML(*this)	// "AnatomicEntityXML"
{
}

CanatomicEntityCollectionXMLType::CanatomicEntityCollectionXMLType(CanatomicEntityCollectionXMLType const& other)
: TypeBase(other.GetNode())
, AnatomicEntityXML(*this)	// "AnatomicEntityXML"
{
}


CimagingObservationCollectionXMLType::CimagingObservationCollectionXMLType(xercesc::DOMNode* const& node)
: TypeBase(node)
, ImagingObservationXML(*this)	// "ImagingObservationXML"
{
}

CimagingObservationCollectionXMLType::CimagingObservationCollectionXMLType(CimagingObservationCollectionXMLType const& other)
: TypeBase(other.GetNode())
, ImagingObservationXML(*this)	// "ImagingObservationXML"
{
}


CrelatedImagingObservationCharacteristicXMLType::CrelatedImagingObservationCharacteristicXMLType(xercesc::DOMNode* const& node)
: TypeBase(node)
, ImagingObservationCharacteristicXML(*this)	// "ImagingObservationCharacteristicXML"
{
}

CrelatedImagingObservationCharacteristicXMLType::CrelatedImagingObservationCharacteristicXMLType(CrelatedImagingObservationCharacteristicXMLType const& other)
: TypeBase(other.GetNode())
, ImagingObservationCharacteristicXML(*this)	// "ImagingObservationCharacteristicXML"
{
}


CrelatedImagingObservationXMLType::CrelatedImagingObservationXMLType(xercesc::DOMNode* const& node)
: TypeBase(node)
, ImagingObservationXML(*this)	// "ImagingObservationXML"
{
}

CrelatedImagingObservationXMLType::CrelatedImagingObservationXMLType(CrelatedImagingObservationXMLType const& other)
: TypeBase(other.GetNode())
, ImagingObservationXML(*this)	// "ImagingObservationXML"
{
}


CimagingObservationCharacteristicCollectionXMLType::CimagingObservationCharacteristicCollectionXMLType(xercesc::DOMNode* const& node)
: TypeBase(node)
, ImagingObservationCharacteristicXML(*this)	// "ImagingObservationCharacteristicXML"
{
}

CimagingObservationCharacteristicCollectionXMLType::CimagingObservationCharacteristicCollectionXMLType(CimagingObservationCharacteristicCollectionXMLType const& other)
: TypeBase(other.GetNode())
, ImagingObservationCharacteristicXML(*this)	// "ImagingObservationCharacteristicXML"
{
}


} // namespace aim


namespace xs
{	

CENTITIES::CENTITIES(xercesc::DOMNode* const& node)
: TypeBase(node)
{
}

CENTITIES::CENTITIES(CENTITIES const& other)
: TypeBase(other.GetNode())
{
}


CENTITY::CENTITY(xercesc::DOMNode* const& node)
: TypeBase(node)
{
}

CENTITY::CENTITY(CENTITY const& other)
: TypeBase(other.GetNode())
{
}


CID::CID(xercesc::DOMNode* const& node)
: TypeBase(node)
{
}

CID::CID(CID const& other)
: TypeBase(other.GetNode())
{
}


CIDREF::CIDREF(xercesc::DOMNode* const& node)
: TypeBase(node)
{
}

CIDREF::CIDREF(CIDREF const& other)
: TypeBase(other.GetNode())
{
}


CIDREFS::CIDREFS(xercesc::DOMNode* const& node)
: TypeBase(node)
{
}

CIDREFS::CIDREFS(CIDREFS const& other)
: TypeBase(other.GetNode())
{
}


CNCName::CNCName(xercesc::DOMNode* const& node)
: TypeBase(node)
{
}

CNCName::CNCName(CNCName const& other)
: TypeBase(other.GetNode())
{
}


CNMTOKEN::CNMTOKEN(xercesc::DOMNode* const& node)
: TypeBase(node)
{
}

CNMTOKEN::CNMTOKEN(CNMTOKEN const& other)
: TypeBase(other.GetNode())
{
}


CNMTOKENS::CNMTOKENS(xercesc::DOMNode* const& node)
: TypeBase(node)
{
}

CNMTOKENS::CNMTOKENS(CNMTOKENS const& other)
: TypeBase(other.GetNode())
{
}


CNOTATION::CNOTATION(xercesc::DOMNode* const& node)
: TypeBase(node)
{
}

CNOTATION::CNOTATION(CNOTATION const& other)
: TypeBase(other.GetNode())
{
}


CName::CName(xercesc::DOMNode* const& node)
: TypeBase(node)
{
}

CName::CName(CName const& other)
: TypeBase(other.GetNode())
{
}


CQName::CQName(xercesc::DOMNode* const& node)
: TypeBase(node)
{
}

CQName::CQName(CQName const& other)
: TypeBase(other.GetNode())
{
}


CanySimpleType::CanySimpleType(xercesc::DOMNode* const& node)
: TypeBase(node)
{
}

CanySimpleType::CanySimpleType(CanySimpleType const& other)
: TypeBase(other.GetNode())
{
}


CanyType::CanyType(xercesc::DOMNode* const& node)
: TypeBase(node)
{
}

CanyType::CanyType(CanyType const& other)
: TypeBase(other.GetNode())
{
}

void CanyType::SetXsiType()
{
	XercesTreeOperations::SetAttribute(m_node, _T("xsi:type"), _T("http://www.w3.org/2001/XMLSchema-instance"), 
		_T("anyType"), _T("http://www.w3.org/2001/XMLSchema"));
}

CanyURI::CanyURI(xercesc::DOMNode* const& node)
: TypeBase(node)
{
}

CanyURI::CanyURI(CanyURI const& other)
: TypeBase(other.GetNode())
{
}


Cbase64Binary::Cbase64Binary(xercesc::DOMNode* const& node)
: TypeBase(node)
{
}

Cbase64Binary::Cbase64Binary(Cbase64Binary const& other)
: TypeBase(other.GetNode())
{
}


Cboolean::Cboolean(xercesc::DOMNode* const& node)
: TypeBase(node)
{
}

Cboolean::Cboolean(Cboolean const& other)
: TypeBase(other.GetNode())
{
}


Cbyte::Cbyte(xercesc::DOMNode* const& node)
: TypeBase(node)
{
}

Cbyte::Cbyte(Cbyte const& other)
: TypeBase(other.GetNode())
{
}


Cdate::Cdate(xercesc::DOMNode* const& node)
: TypeBase(node)
{
}

Cdate::Cdate(Cdate const& other)
: TypeBase(other.GetNode())
{
}


CdateTime::CdateTime(xercesc::DOMNode* const& node)
: TypeBase(node)
{
}

CdateTime::CdateTime(CdateTime const& other)
: TypeBase(other.GetNode())
{
}


Cdecimal::Cdecimal(xercesc::DOMNode* const& node)
: TypeBase(node)
{
}

Cdecimal::Cdecimal(Cdecimal const& other)
: TypeBase(other.GetNode())
{
}


Cdouble::Cdouble(xercesc::DOMNode* const& node)
: TypeBase(node)
{
}

Cdouble::Cdouble(Cdouble const& other)
: TypeBase(other.GetNode())
{
}


Cduration::Cduration(xercesc::DOMNode* const& node)
: TypeBase(node)
{
}

Cduration::Cduration(Cduration const& other)
: TypeBase(other.GetNode())
{
}


Cfloat::Cfloat(xercesc::DOMNode* const& node)
: TypeBase(node)
{
}

Cfloat::Cfloat(Cfloat const& other)
: TypeBase(other.GetNode())
{
}


CgDay::CgDay(xercesc::DOMNode* const& node)
: TypeBase(node)
{
}

CgDay::CgDay(CgDay const& other)
: TypeBase(other.GetNode())
{
}


CgMonth::CgMonth(xercesc::DOMNode* const& node)
: TypeBase(node)
{
}

CgMonth::CgMonth(CgMonth const& other)
: TypeBase(other.GetNode())
{
}


CgMonthDay::CgMonthDay(xercesc::DOMNode* const& node)
: TypeBase(node)
{
}

CgMonthDay::CgMonthDay(CgMonthDay const& other)
: TypeBase(other.GetNode())
{
}


CgYear::CgYear(xercesc::DOMNode* const& node)
: TypeBase(node)
{
}

CgYear::CgYear(CgYear const& other)
: TypeBase(other.GetNode())
{
}


CgYearMonth::CgYearMonth(xercesc::DOMNode* const& node)
: TypeBase(node)
{
}

CgYearMonth::CgYearMonth(CgYearMonth const& other)
: TypeBase(other.GetNode())
{
}


ChexBinary::ChexBinary(xercesc::DOMNode* const& node)
: TypeBase(node)
{
}

ChexBinary::ChexBinary(ChexBinary const& other)
: TypeBase(other.GetNode())
{
}


Cint::Cint(xercesc::DOMNode* const& node)
: TypeBase(node)
{
}

Cint::Cint(Cint const& other)
: TypeBase(other.GetNode())
{
}


Cinteger::Cinteger(xercesc::DOMNode* const& node)
: TypeBase(node)
{
}

Cinteger::Cinteger(Cinteger const& other)
: TypeBase(other.GetNode())
{
}


Clanguage::Clanguage(xercesc::DOMNode* const& node)
: TypeBase(node)
{
}

Clanguage::Clanguage(Clanguage const& other)
: TypeBase(other.GetNode())
{
}


Clong::Clong(xercesc::DOMNode* const& node)
: TypeBase(node)
{
}

Clong::Clong(Clong const& other)
: TypeBase(other.GetNode())
{
}


CnegativeInteger::CnegativeInteger(xercesc::DOMNode* const& node)
: TypeBase(node)
{
}

CnegativeInteger::CnegativeInteger(CnegativeInteger const& other)
: TypeBase(other.GetNode())
{
}


CnonNegativeInteger::CnonNegativeInteger(xercesc::DOMNode* const& node)
: TypeBase(node)
{
}

CnonNegativeInteger::CnonNegativeInteger(CnonNegativeInteger const& other)
: TypeBase(other.GetNode())
{
}


CnonPositiveInteger::CnonPositiveInteger(xercesc::DOMNode* const& node)
: TypeBase(node)
{
}

CnonPositiveInteger::CnonPositiveInteger(CnonPositiveInteger const& other)
: TypeBase(other.GetNode())
{
}


CnormalizedString::CnormalizedString(xercesc::DOMNode* const& node)
: TypeBase(node)
{
}

CnormalizedString::CnormalizedString(CnormalizedString const& other)
: TypeBase(other.GetNode())
{
}


CpositiveInteger::CpositiveInteger(xercesc::DOMNode* const& node)
: TypeBase(node)
{
}

CpositiveInteger::CpositiveInteger(CpositiveInteger const& other)
: TypeBase(other.GetNode())
{
}


Cshort::Cshort(xercesc::DOMNode* const& node)
: TypeBase(node)
{
}

Cshort::Cshort(Cshort const& other)
: TypeBase(other.GetNode())
{
}


Cstring::Cstring(xercesc::DOMNode* const& node)
: TypeBase(node)
{
}

Cstring::Cstring(Cstring const& other)
: TypeBase(other.GetNode())
{
}


Ctime::Ctime(xercesc::DOMNode* const& node)
: TypeBase(node)
{
}

Ctime::Ctime(Ctime const& other)
: TypeBase(other.GetNode())
{
}


Ctoken::Ctoken(xercesc::DOMNode* const& node)
: TypeBase(node)
{
}

Ctoken::Ctoken(Ctoken const& other)
: TypeBase(other.GetNode())
{
}


CunsignedByte::CunsignedByte(xercesc::DOMNode* const& node)
: TypeBase(node)
{
}

CunsignedByte::CunsignedByte(CunsignedByte const& other)
: TypeBase(other.GetNode())
{
}


CunsignedInt::CunsignedInt(xercesc::DOMNode* const& node)
: TypeBase(node)
{
}

CunsignedInt::CunsignedInt(CunsignedInt const& other)
: TypeBase(other.GetNode())
{
}


CunsignedLong::CunsignedLong(xercesc::DOMNode* const& node)
: TypeBase(node)
{
}

CunsignedLong::CunsignedLong(CunsignedLong const& other)
: TypeBase(other.GetNode())
{
}


CunsignedShort::CunsignedShort(xercesc::DOMNode* const& node)
: TypeBase(node)
{
}

CunsignedShort::CunsignedShort(CunsignedShort const& other)
: TypeBase(other.GetNode())
{
}


CstringType::CstringType(xercesc::DOMNode* const& node)
: TypeBase(node)
{
}

CstringType::CstringType(CstringType const& other)
: TypeBase(other.GetNode())
{
}

void CstringType::SetXsiType()
{
	XercesTreeOperations::SetAttribute(m_node, _T("xsi:type"), _T("http://www.w3.org/2001/XMLSchema-instance"), 
		_T("string"), _T("http://www.w3.org/2001/XMLSchema"));
}

} // namespace xs


namespace aim
{	

} // namespace aim


namespace xs
{	

void CanyType::operator=(const string_type& value) { 
	XercesTreeOperations::SetValue(GetNode(), members + _altova_mi_xs_altova_CanyType_altova_unnamed, value);
}

CanyType::operator string_type() {
	return CastAs<string_type >::Do(GetNode(), members + _altova_mi_xs_altova_CanyType_altova_unnamed);
}

void CstringType::operator=(const string_type& value) { 
	XercesTreeOperations::SetValue(GetNode(), members + _altova_mi_xs_altova_CstringType_altova_unnamed, value);
}

CstringType::operator string_type() {
	return CastAs<string_type >::Do(GetNode(), members + _altova_mi_xs_altova_CstringType_altova_unnamed);
}

} // namespace xs


}
