/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: XSerializable.hpp 527149 2007-04-10 14:56:39Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_XSERIALIZABLE_HPP)
#define XERCESC_INCLUDE_GUARD_XSERIALIZABLE_HPP

#include <xercesc/internal/XSerializeEngine.hpp>
#include <xercesc/internal/XProtoType.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class XMLUTIL_EXPORT XSerializable
{
public :

    // -----------------------------------------------------------------------
    //  Constructors and Destructor
    // -----------------------------------------------------------------------
    virtual ~XSerializable() {} ;

    // -----------------------------------------------------------------------
    //  Serialization Interface
    // -----------------------------------------------------------------------   
    virtual bool        isSerializable()               const = 0;

    virtual void        serialize(XSerializeEngine& )        = 0;

    virtual XProtoType* getProtoType()                 const = 0;

protected:
    XSerializable() {}
    XSerializable(const XSerializable& ) {}             

private:
    // -----------------------------------------------------------------------
    //  Unimplemented assignment operator
    // -----------------------------------------------------------------------
	XSerializable& operator=(const XSerializable&);

};

inline void XSerializable::serialize(XSerializeEngine& )
{
}

/***
 * Macro to be included in XSerializable derivatives'
 * declaration's public section
 ***/
#define DECL_XSERIALIZABLE(class_name) \
public: \
\
DECL_XPROTOTYPE(class_name) \
\
virtual bool                    isSerializable()                  const ;  \
virtual XProtoType*             getProtoType()                    const;   \
virtual void                    serialize(XSerializeEngine&); \
\
inline friend XSerializeEngine& operator>>(XSerializeEngine& serEng  \
                                         , class_name*&      objPtr) \
{objPtr = (class_name*) serEng.read(XPROTOTYPE_CLASS(class_name));   \
 return serEng; \
};
	
/***
 * Macro to be included in the implementation file
 * of XSerializable derivatives' which is instantiable
 ***/
#define IMPL_XSERIALIZABLE_TOCREATE(class_name) \
IMPL_XPROTOTYPE_TOCREATE(class_name) \
IMPL_XSERIAL(class_name)

/***
 * Macro to be included in the implementation file
 * of XSerializable derivatives' which is UN-instantiable
 ***/
#define IMPL_XSERIALIZABLE_NOCREATE(class_name) \
IMPL_XPROTOTYPE_NOCREATE(class_name) \
IMPL_XSERIAL(class_name)

/***
 * Helper Macro 
 ***/
#define IMPL_XSERIAL(class_name) \
bool        class_name::isSerializable() const \
{return true; } \
XProtoType* class_name::getProtoType()   const \
{return XPROTOTYPE_CLASS(class_name); } 

#define IS_EQUIVALENT(lptr, rptr) \
    if (lptr == rptr)             \
        return true;              \
    if (( lptr && !rptr) || (!lptr &&  rptr))  \
        return false;

XERCES_CPP_NAMESPACE_END

#endif

