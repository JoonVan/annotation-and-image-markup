/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "dcmtk/oflog/helpers/sockbuff.h"
#include "dcmtk/oflog/helpers/loglog.h"
//#include <cstring>
#define INCLUDE_CSTRING
//#include <limits>
#define INCLUDE_CLIMITS
#include "dcmtk/ofstd/ofstdinc.h"

#if !defined(_WIN32)
#  ifdef HAVE_NETDB_H
#    include <netdb.h>
#  endif
#else
#include <winsock.h>
#endif

#if defined (__CYGWIN__) || defined (DCMTK_LOG4CPLUS_HAVE_NETINET_IN_H)
#include <netinet/in.h>
#endif

using namespace dcmtk::log4cplus;
using namespace dcmtk::log4cplus::helpers;


//////////////////////////////////////////////////////////////////////////////
// SocketBuffer ctors and dtor
//////////////////////////////////////////////////////////////////////////////

SocketBuffer::SocketBuffer(size_t maxsize_)
: maxsize(maxsize_),
  size(0),
  pos(0),
  buffer(new char[maxsize_])
{
}



SocketBuffer::SocketBuffer(const SocketBuffer& rhs)
    : LogLogUser ()
{
    copy(rhs);
}



SocketBuffer::~SocketBuffer()
{
    delete [] buffer;
}



SocketBuffer&
SocketBuffer::operator=(const SocketBuffer& rhs)
{
    if(&rhs != this) {
        delete buffer;
        copy(rhs);
    }

    return *this;
}



void
SocketBuffer::copy(const SocketBuffer& r)
{
    SocketBuffer& rhs = OFconst_cast(SocketBuffer&, r);
    maxsize = rhs.maxsize;
    size = rhs.size;
    pos = rhs.pos;
    buffer = rhs.buffer;

    rhs.maxsize = 0;
    rhs.size = 0;
    rhs.pos = 0;
    rhs.buffer = 0;
}




//////////////////////////////////////////////////////////////////////////////
// SocketBuffer methods
//////////////////////////////////////////////////////////////////////////////

unsigned char
SocketBuffer::readByte()
{
    if(pos >= maxsize) {
        getLogLog().error(DCMTK_LOG4CPLUS_TEXT("SocketBuffer::readByte()- end of buffer reached"));
        return 0;
    }
    else if((pos + sizeof(unsigned char)) > maxsize) {
        getLogLog().error(DCMTK_LOG4CPLUS_TEXT("SocketBuffer::readByte()- Attempt to read beyond end of buffer"));
        return 0;
    }

    unsigned char ret = *(OFreinterpret_cast(unsigned char*, &buffer[pos]));
    pos += sizeof(unsigned char);

    return ret;
}



unsigned short
SocketBuffer::readShort()
{
    if(pos >= maxsize) {
        getLogLog().error(DCMTK_LOG4CPLUS_TEXT("SocketBuffer::readShort()- end of buffer reached"));
        return 0;
    }
    else if((pos + sizeof(unsigned short)) > maxsize) {
        getLogLog().error(DCMTK_LOG4CPLUS_TEXT("SocketBuffer::readShort()- Attempt to read beyond end of buffer"));
        return 0;
    }

    unsigned short ret;
    memcpy(&ret, buffer + pos, sizeof(ret));
    ret = ntohs(ret);
    pos += sizeof(unsigned short);

    return ret;
}



unsigned int
SocketBuffer::readInt()
{
    if(pos >= maxsize) {
        getLogLog().error(DCMTK_LOG4CPLUS_TEXT("SocketBuffer::readInt()- end of buffer reached"));
        return 0;
    }
    else if((pos + sizeof(unsigned int)) > maxsize) {
        getLogLog().error(DCMTK_LOG4CPLUS_TEXT("SocketBuffer::readInt()- Attempt to read beyond end of buffer"));
        return 0;
    }

    unsigned int ret;
    memcpy (&ret, buffer + pos, sizeof(ret));
    ret = ntohl(ret);
    pos += sizeof(unsigned int);

    return ret;
}


tstring
SocketBuffer::readString(unsigned char sizeOfChar)
{
    size_t strlen = readInt();
    size_t bufferLen = strlen * sizeOfChar;

    if(strlen == 0) {
        return tstring();
    }
    if(pos > maxsize) {
        getLogLog().error(DCMTK_LOG4CPLUS_TEXT("SocketBuffer::readString()- end of buffer reached"));
        return tstring();
    }

    if((pos + bufferLen) > maxsize) {
        getLogLog().error(DCMTK_LOG4CPLUS_TEXT("SocketBuffer::readString()- Attempt to read beyond end of buffer"));
        bufferLen = (maxsize - 1) - pos;
        strlen = bufferLen / sizeOfChar;
    }

    if(sizeOfChar == 1) {
        tstring ret(&buffer[pos], strlen);
        pos += strlen;
        return ret;
    }
    else if(sizeOfChar == 2) {
        tstring ret;
        for(tstring::size_type i=0; i<strlen; ++i) {
            unsigned short tmp = readShort();
            ret += OFstatic_cast(char, tmp < 256 ? tmp : ' ');
        }
        return ret;
    }
    else {
        getLogLog().error(DCMTK_LOG4CPLUS_TEXT("SocketBuffer::readString()- Invalid sizeOfChar!!!!"));
    }


    return tstring();
}



void
SocketBuffer::appendByte(unsigned char val)
{
    if((pos + sizeof(unsigned char)) > maxsize) {
        getLogLog().error(DCMTK_LOG4CPLUS_TEXT("SocketBuffer::appendByte()- Attempt to write beyond end of buffer"));
        return;
    }

    *(OFreinterpret_cast(unsigned char*, &buffer[pos])) = val;
    pos += sizeof(unsigned char);
    size = pos;
}



void
SocketBuffer::appendShort(unsigned short val)
{
    if((pos + sizeof(unsigned short)) > maxsize) {
        getLogLog().error(DCMTK_LOG4CPLUS_TEXT("SocketBuffer::appendShort()- Attempt to write beyond end of buffer"));
        return;
    }

    unsigned short s = htons(val);
    memcpy(buffer + pos, &s, sizeof (s));
    pos += sizeof(s);
    size = pos;
}



void
SocketBuffer::appendInt(unsigned int val)
{
    if((pos + sizeof(unsigned int)) > maxsize) {
        getLogLog().error(DCMTK_LOG4CPLUS_TEXT("SocketBuffer::appendInt()- Attempt to write beyond end of buffer"));
        return;
    }

    int i = htonl(val);
    memcpy(buffer + pos, &i, sizeof (i));
    pos += sizeof(i);
    size = pos;
}



void
SocketBuffer::appendSize_t(size_t val)
{
    if ((pos + sizeof(unsigned)) > maxsize)
    {
        getLogLog().error(DCMTK_LOG4CPLUS_TEXT("SocketBuffer::appendInt(size_t)- ")
            DCMTK_LOG4CPLUS_TEXT("Attempt to write beyond end of buffer"));
        return;
    }
    //if (val > (STD_NAMESPACE numeric_limits<unsigned>::max) ())
    // htonl expects a 32 bit value
    if (val > UINT_MAX)
    {
        getLogLog().error(DCMTK_LOG4CPLUS_TEXT("SocketBuffer::appendInt(size_t)-")
            DCMTK_LOG4CPLUS_TEXT(" Attempt to write value greater than")
            DCMTK_LOG4CPLUS_TEXT(" STD_NAMESPACE numeric_limits<unsigned>::max"));
        return;
    }

    unsigned st = htonl(OFstatic_cast(unsigned, val));
    memcpy(buffer + pos, &st, sizeof(st));
    pos += sizeof(st);
    size = pos;
}


void
SocketBuffer::appendString(const tstring& str)
{
    size_t strlen = str.length();

    if((pos + sizeof(unsigned int) + strlen) > maxsize) {
        getLogLog().error(DCMTK_LOG4CPLUS_TEXT("SocketBuffer::appendString()- Attempt to write beyond end of buffer"));
        return;
    }

    appendInt(OFstatic_cast(unsigned, strlen));
    memcpy(&buffer[pos], str.data(), strlen);
    pos += strlen;
    size = pos;
}



void
SocketBuffer::appendBuffer(const SocketBuffer& buf)
{
    if((pos + buf.getSize()) > maxsize) {
        getLogLog().error(DCMTK_LOG4CPLUS_TEXT("SocketBuffer::appendBuffer()- Attempt to write beyond end of buffer"));
        return;
    }

    memcpy(&buffer[pos], buf.buffer, buf.getSize());
    pos += buf.getSize();
    size = pos;
}



