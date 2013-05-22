/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CCOLL_ED_Narrative
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CCOLL_ED_Narrative

#include "type_iso.CANY.h"


namespace AIMXML
{

namespace iso
{	

class CCOLL_ED_Narrative : public ::AIMXML::iso::CANY
{
public:
	AIMXML_EXPORT CCOLL_ED_Narrative(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CCOLL_ED_Narrative(CCOLL_ED_Narrative const& init);
	void operator=(CCOLL_ED_Narrative const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CCOLL_ED_Narrative); }
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CCOLL_ED_Narrative
