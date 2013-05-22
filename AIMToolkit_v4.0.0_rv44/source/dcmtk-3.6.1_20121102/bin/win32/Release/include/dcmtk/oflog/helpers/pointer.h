/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

//
// Note: Some of this code uses ideas from "More Effective C++" by Scott
// Myers, Addison Wesley Longmain, Inc., (c) 1996, Chapter 29, pp. 183-213
//

/** @file */

#ifndef DCMTK__LOG4CPLUS_HELPERS_POINTERS_HEADER_
#define DCMTK__LOG4CPLUS_HELPERS_POINTERS_HEADER_

#include "dcmtk/oflog/config.h"
//#include <memory>
//#include <stdexcept>
//#include <string>
//#include <algorithm>
//#include <cassert>

#define INCLUDE_CASSERT
#include "dcmtk/ofstd/ofstdinc.h"

namespace dcmtk {
namespace log4cplus {
    namespace helpers {

        /******************************************************************************
         *                       Class SharedObject (from pp. 204-205)                *
         ******************************************************************************/

        class DCMTK_LOG4CPLUS_EXPORT SharedObject
        {
        public:
            void addReference() const;
            void removeReference() const;

        protected:
          // Ctor
            SharedObject()
                : access_mutex(DCMTK_LOG4CPLUS_MUTEX_CREATE)
                , count(0)
            { }

            SharedObject(const SharedObject&)
                : access_mutex(DCMTK_LOG4CPLUS_MUTEX_CREATE)
                , count(0)
            { }

          // Dtor
            virtual ~SharedObject();

          // Operators
            SharedObject& operator=(const SharedObject&) { return *this; }

        public:
            DCMTK_LOG4CPLUS_MUTEX_PTR_DECLARE access_mutex;

        private:
            mutable int count;
        };


        /******************************************************************************
         *           Template Class SharedObjectPtr (from pp. 203, 206)               *
         ******************************************************************************/
        template<class T>
        class SharedObjectPtr
        {
        public:
            // Ctor
            explicit
            SharedObjectPtr(T* realPtr = 0)
                : pointee(realPtr)
            {
                addref ();
            }

            SharedObjectPtr(const SharedObjectPtr& rhs)
                : pointee(rhs.pointee)
            {
                addref ();
            }

            // Dtor
            ~SharedObjectPtr()
            {
                if (pointee)
                    pointee->removeReference();
            }

            // Operators
            bool operator==(const SharedObjectPtr& rhs) const { return (pointee == rhs.pointee); }
            bool operator!=(const SharedObjectPtr& rhs) const { return (pointee != rhs.pointee); }
            bool operator==(const T* rhs) const { return (pointee == rhs); }
            bool operator!=(const T* rhs) const { return (pointee != rhs); }
            T* operator->() const {assert (pointee); return pointee; }
            T& operator*() const {assert (pointee); return *pointee; }

            SharedObjectPtr& operator=(const SharedObjectPtr& rhs)
            {
                return this->operator = (rhs.pointee);
            }

            SharedObjectPtr& operator=(T* rhs)
            {
                SharedObjectPtr<T> (rhs).swap (*this);
                return *this;
            }

          // Methods
            T* get() const { return pointee; }

            void swap (SharedObjectPtr & other) throw ()
            {
                T* tmp = pointee;
                pointee = other.pointee;
                other.pointee = tmp;
                //STD_NAMESPACE swap (pointee, other.pointee);
            }

            typedef T * (SharedObjectPtr:: * unspec_bool_type) () const;
            operator unspec_bool_type () const
            {
                return pointee ? &SharedObjectPtr::get : 0;
            }

            bool operator ! () const
            {
                return ! pointee;
            }

        private:
          // Methods
            void addref() const
            {
                if (pointee)
                    pointee->addReference();
            }

          // Data
            T* pointee;
        };

    } // end namespace helpers
} // end namespace log4cplus
} // namespace dcmtk


#endif // DCMTK__LOG4CPLUS_HELPERS_POINTERS_HEADER_