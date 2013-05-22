/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: DOMNodeIteratorImpl.hpp 671894 2008-06-26 13:29:21Z borisk $
 */

#if !defined(XERCESC_INCLUDE_GUARD_DOMNODEITERATORIMPL_HPP)
#define XERCESC_INCLUDE_GUARD_DOMNODEITERATORIMPL_HPP

//
//  This file is part of the internal implementation of the C++ XML DOM.
//  It should NOT be included or used directly by application programs.
//
//  Applications should include the file <xercesc/dom/DOM.hpp> for the entire
//  DOM API, or xercesc/dom/DOM*.hpp for individual DOM classes, where the class
//  name is substituded for the *.
//

//////////////////////////////////////////////////////////////////////
// DOMNodeIteratorImpl.hpp: interface for the DOMNodeIteratorImpl class.
//
//////////////////////////////////////////////////////////////////////

#include <xercesc/dom/DOMNode.hpp>
#include <xercesc/dom/DOMNodeIterator.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class CDOM_EXPORT DOMNodeIteratorImpl : public DOMNodeIterator {
    protected:
        //
        // Data
        //
        // The root.
        DOMNode* fRoot;

        // The Document used to create this iterator
        DOMDocument* fDocument;

        // The whatToShow mask.
        DOMNodeFilter::ShowType fWhatToShow;

        // The NodeFilter reference.
        DOMNodeFilter* fNodeFilter;


        // The expandEntity reference flag.
        bool  fExpandEntityReferences;
        bool fDetached;


        //
        // Iterator state - current node and direction.
        //
        // Note: The current node and direction are sufficient to implement
        // the desired behaviour of the current pointer being _between_
        // two nodes. The fCurrentNode is actually the last node returned,
        // and the
        // direction is whether the pointer is in front or behind this node.
        // (usually akin to whether the node was returned via nextNode())
        // (eg fForward = true) or previousNode() (eg fForward = false).
        // The last Node returned.
        DOMNode* fCurrentNode;

        // The direction of the iterator on the fCurrentNode.
        //  <code>
        //  nextNode()  ==      fForward = true;<br>
        //  previousNode() ==   fForward = false;<br>
        //  </code>
        bool fForward;

    public:
        virtual ~DOMNodeIteratorImpl ();
        DOMNodeIteratorImpl (
            DOMDocument* fDocument,
            DOMNode* root,
            DOMNodeFilter::ShowType whatToShow,
            DOMNodeFilter* nodeFilter,
            bool expandEntityRef);

        DOMNodeIteratorImpl ( const DOMNodeIteratorImpl& toCopy);
        DOMNodeIteratorImpl& operator= (const DOMNodeIteratorImpl& other);

        virtual DOMNode* getRoot ();
        virtual DOMNodeFilter::ShowType getWhatToShow ();
        virtual DOMNodeFilter* getFilter ();
        // Get the expandEntity reference flag.
        virtual bool getExpandEntityReferences();

        virtual DOMNode* nextNode ();
        virtual DOMNode* previousNode ();
        virtual void detach ();

        virtual void release();
        void removeNode (DOMNode* node);

    protected:
        DOMNode* matchNodeOrParent (DOMNode* node);
        DOMNode* nextNode (DOMNode* node, bool visitChildren);
        DOMNode* previousNode (DOMNode* node);
        bool acceptNode (DOMNode* node);

};

XERCES_CPP_NAMESPACE_END

#endif
