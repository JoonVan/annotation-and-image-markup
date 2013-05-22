/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#ifndef DSRUIDTN_H
#define DSRUIDTN_H

#include "dcmtk/config/osconfig.h"   /* make sure OS specific configuration is included first */

#include "dcmtk/dcmsr/dsrdoctn.h"
#include "dcmtk/dcmsr/dsrstrvl.h"


/*---------------------*
 *  class declaration  *
 *---------------------*/

/** Class for content item UIDREF
 */
class DCMTK_DCMSR_EXPORT DSRUIDRefTreeNode
  : public DSRDocumentTreeNode,
    public DSRStringValue
{

  public:

    /** constructor
     ** @param  relationshipType  type of relationship to the parent tree node.
     *                            Should not be RT_invalid or RT_isRoot.
     */
    DSRUIDRefTreeNode(const E_RelationshipType relationshipType);

    /** constructor.
     ** @param  relationshipType  type of relationship to the parent tree node.
     *                            Should not be RT_invalid or RT_isRoot.
     *  @param  uidValue          initial value to be set (VR=UI, mandatory)
     *  @param  check             if enabled, check 'uidValue' for validity before setting
     *                            it.  See checkValue() for details.  An empty value is never
     *                            accepted.
     */
    DSRUIDRefTreeNode(const E_RelationshipType relationshipType,
                      const OFString &uidValue,
                      const OFBool check = OFTrue);

    /** destructor
     */
    virtual ~DSRUIDRefTreeNode();

    /** clear all member variables.
     *  Please note that the content item might become invalid afterwards.
     */
    virtual void clear();

    /** check whether the content item is valid.
     *  The content item is valid if the base classes, the concept name and the currently
     *  stored date value are valid.
     ** @return OFTrue if tree node is valid, OFFalse otherwise
     */
    virtual OFBool isValid() const;

    /** print content item.
     *  A typical output looks like this:  contains UIDREF:(,,"Code")="1.2.3.4.5"
     ** @param  stream  output stream to which the content item should be printed
     *  @param  flags   flag used to customize the output (see DSRTypes::PF_xxx)
     ** @return status, EC_Normal if successful, an error code otherwise
     */
    virtual OFCondition print(STD_NAMESPACE ostream &stream,
                              const size_t flags) const;

    /** write content item in XML format
     ** @param  stream  output stream to which the XML document is written
     *  @param  flags   flag used to customize the output (see DSRTypes::XF_xxx)
     ** @return status, EC_Normal if successful, an error code otherwise
     */
    virtual OFCondition writeXML(STD_NAMESPACE ostream &stream,
                                 const size_t flags) const;


  protected:

    /** read content item (value) from dataset
     ** @param  dataset  DICOM dataset from which the content item should be read
     ** @return status, EC_Normal if successful, an error code otherwise
     */
    virtual OFCondition readContentItem(DcmItem &dataset);

    /** write content item (value) to dataset
     ** @param  dataset  DICOM dataset to which the content item should be written
     ** @return status, EC_Normal if successful, an error code otherwise
     */
    virtual OFCondition writeContentItem(DcmItem &dataset) const;

    /** read content item specific XML data
     ** @param  doc     document containing the XML file content
     *  @param  cursor  cursor pointing to the starting node
     ** @return status, EC_Normal if successful, an error code otherwise
     */
    virtual OFCondition readXMLContentItem(const DSRXMLDocument &doc,
                                           DSRXMLCursor cursor);

    /** render content item (value) in HTML/XHTML format
     ** @param  docStream     output stream to which the main HTML/XHTML document is written
     *  @param  annexStream   output stream to which the HTML/XHTML document annex is written
     *  @param  nestingLevel  current nesting level.  Used to render section headings.
     *  @param  annexNumber   reference to the variable where the current annex number is stored.
     *                        Value is increased automatically by 1 after a new entry has been added.
     *  @param  flags         flag used to customize the output (see DSRTypes::HF_xxx)
     ** @return status, EC_Normal if successful, an error code otherwise
     */
    virtual OFCondition renderHTMLContentItem(STD_NAMESPACE ostream &docStream,
                                              STD_NAMESPACE ostream &annexStream,
                                              const size_t nestingLevel,
                                              size_t &annexNumber,
                                              const size_t flags) const;

    /** check the specified UID value for validity.
     *  In addition to the base class check for a non-empty value, this method also checks
     *  whether the given value conforms to the corresponding VR (UI) and VM (1).
     ** @param  uidValue  value to be checked
     ** @return status, EC_Normal if value is valid, an error code otherwise
     */
    virtual OFCondition checkValue(const OFString &uidValue) const;


  private:

 // --- declaration of default/copy constructor and assignment operator

    DSRUIDRefTreeNode();
    DSRUIDRefTreeNode(const DSRUIDRefTreeNode &);
    DSRUIDRefTreeNode &operator=(const DSRUIDRefTreeNode &);
};


#endif
