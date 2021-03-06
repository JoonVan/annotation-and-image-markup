/*
*  2007 � 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSU_CO
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSU_CO

#include "type_iso.CQSET_CO.h"


namespace AIMXML
{

namespace iso
{	

class CQSU_CO : public ::AIMXML::iso::CQSET_CO
{
public:
	AIMXML_EXPORT CQSU_CO(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CQSU_CO(CQSU_CO const& init);
	void operator=(CQSU_CO const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CQSU_CO); }
	MemberElement<iso::CQSET_CO, _altova_mi_iso_altova_CQSU_CO_altova_term> term;
	struct term { typedef Iterator<iso::CQSET_CO> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSU_CO
