/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: WFXMLScanner.hpp 810580 2009-09-02 15:52:22Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_WFXMLSCANNER_HPP)
#define XERCESC_INCLUDE_GUARD_WFXMLSCANNER_HPP

#include <xercesc/internal/XMLScanner.hpp>
#include <xercesc/util/ValueHashTableOf.hpp>
#include <xercesc/util/ValueVectorOf.hpp>
#include <xercesc/validators/DTD/DTDElementDecl.hpp>

XERCES_CPP_NAMESPACE_BEGIN


//  This is a a non-validating scanner. No DOCTYPE or XML Schema processing
//  will take place.
class XMLPARSER_EXPORT WFXMLScanner : public XMLScanner
{
public :
    // -----------------------------------------------------------------------
    //  Constructors and Destructor
    // -----------------------------------------------------------------------
    WFXMLScanner
    (
        XMLValidator* const       valToAdopt
        , GrammarResolver* const  grammarResolver
        , MemoryManager* const    manager = XMLPlatformUtils::fgMemoryManager
    );
    WFXMLScanner
    (
        XMLDocumentHandler* const docHandler
        , DocTypeHandler* const   docTypeHandler
        , XMLEntityHandler* const entityHandler
        , XMLErrorReporter* const errReporter
        , XMLValidator* const     valToAdopt
        , GrammarResolver* const  grammarResolver
        , MemoryManager* const    manager = XMLPlatformUtils::fgMemoryManager
    );
    virtual ~WFXMLScanner();

    // -----------------------------------------------------------------------
    //  XMLScanner public virtual methods
    // -----------------------------------------------------------------------
    virtual const XMLCh* getName() const;
    virtual NameIdPool<DTDEntityDecl>* getEntityDeclPool();
    virtual const NameIdPool<DTDEntityDecl>* getEntityDeclPool() const;
    virtual void scanDocument
    (
        const   InputSource&    src
    );
    virtual bool scanNext(XMLPScanToken& toFill);
    virtual Grammar* loadGrammar
    (
        const   InputSource&    src
        , const short           grammarType
        , const bool            toCache = false
    );

private :
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    WFXMLScanner();
    WFXMLScanner(const WFXMLScanner&);
    WFXMLScanner& operator=(const WFXMLScanner&);

    // -----------------------------------------------------------------------
    //  XMLScanner virtual methods
    // -----------------------------------------------------------------------
    virtual void scanCDSection();
    virtual void scanCharData(XMLBuffer& toToUse);
    virtual EntityExpRes scanEntityRef
    (
        const   bool    inAttVal
        ,       XMLCh&  firstCh
        ,       XMLCh&  secondCh
        ,       bool&   escaped
    );
    virtual void scanDocTypeDecl();
    virtual void scanReset(const InputSource& src);
    virtual void sendCharData(XMLBuffer& toSend);
    virtual InputSource* resolveSystemId(const XMLCh* const sysId
                                        ,const XMLCh* const pubId);

    // -----------------------------------------------------------------------
    //  Private helper methods
    // -----------------------------------------------------------------------
    void commonInit();
    void cleanUp();

    // -----------------------------------------------------------------------
    //  Private scanning methods
    // -----------------------------------------------------------------------
    bool scanAttValue
    (
        const   XMLCh* const    attrName
        ,       XMLBuffer&      toFill
    );
    bool scanContent();
    void scanEndTag(bool& gotData);
    bool scanStartTag(bool& gotData);
    bool scanStartTagNS(bool& gotData);

    // -----------------------------------------------------------------------
    //  Data members
    //
    //  fEntityTable
    //      This the table that contains the default entity entries.
    //
    //  fAttrNameHashList
    //      This contains the hash value for attribute names. It's used when
    //      checking for duplicate attributes.
    //
    //  fAttrNSList
    //      This contains XMLAttr objects that we need to map their prefixes
    //      to URIs when namespace is enabled.
    //
    // -----------------------------------------------------------------------
    unsigned int                       fElementIndex;
    RefVectorOf<XMLElementDecl>*       fElements;
    ValueHashTableOf<XMLCh>*           fEntityTable;
    ValueVectorOf<XMLSize_t>*          fAttrNameHashList;
    ValueVectorOf<XMLAttr*>*           fAttrNSList;
    RefHashTableOf<XMLElementDecl>*    fElementLookup;  
};

inline const XMLCh* WFXMLScanner::getName() const
{
    return XMLUni::fgWFXMLScanner;
}


XERCES_CPP_NAMESPACE_END

#endif
