/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "dcmtk/oflog/streams.h"
#include "dcmtk/oflog/helpers/pointer.h"
#include "dcmtk/oflog/helpers/threads.h"
//#include <assert.h>


namespace dcmtk { namespace log4cplus { namespace helpers {


///////////////////////////////////////////////////////////////////////////////
// dcmtk::log4cplus::helpers::SharedObject dtor
///////////////////////////////////////////////////////////////////////////////

SharedObject::~SharedObject()
{
    assert(count == 0);
    DCMTK_LOG4CPLUS_MUTEX_FREE( access_mutex );
}



///////////////////////////////////////////////////////////////////////////////
// dcmtk::log4cplus::helpers::SharedObject public methods
///////////////////////////////////////////////////////////////////////////////

void
SharedObject::addReference() const
{
    DCMTK_LOG4CPLUS_BEGIN_SYNCHRONIZE_ON_MUTEX( access_mutex )
        assert (count >= 0);
        ++count;
    DCMTK_LOG4CPLUS_END_SYNCHRONIZE_ON_MUTEX;
}


void
SharedObject::removeReference() const
{
    bool destroy = false;
    DCMTK_LOG4CPLUS_BEGIN_SYNCHRONIZE_ON_MUTEX( access_mutex );
        assert (count > 0);
        if (--count == 0)
            destroy = true;
    DCMTK_LOG4CPLUS_END_SYNCHRONIZE_ON_MUTEX;
    if (destroy)
        delete this;
}


} } } // namespace dcmtk { namespace log4cplus { namespace helpers
