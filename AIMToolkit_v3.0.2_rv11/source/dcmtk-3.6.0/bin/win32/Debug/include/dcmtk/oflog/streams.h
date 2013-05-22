/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/** @file */

#ifndef LOG4CPLUS_STREAMS_HEADER_
#define LOG4CPLUS_STREAMS_HEADER_

#include "dcmtk/oflog/config.h"
#include "dcmtk/oflog/tstring.h"
#include "dcmtk/ofstd/ofstream.h"

#define LOG4CPLUS_STREAM_NAMESPACE std

namespace log4cplus {
    typedef STD_NAMESPACE ostream tostream;
    typedef STD_NAMESPACE istream tistream;
    typedef OFOStringStream        tostringstream;
}

#endif // LOG4CPLUS_STREAMS_HEADER_

