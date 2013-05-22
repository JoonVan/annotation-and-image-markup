/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

//#include <cstdlib>
#include "dcmtk/oflog/socketap.h"
#include "dcmtk/oflog/layout.h"
#include "dcmtk/oflog/helpers/loglog.h"
#include "dcmtk/oflog/spi/logevent.h"
#include "dcmtk/oflog/helpers/sleep.h"

#define INCLUDE_CSTDLIB
#include "dcmtk/ofstd/ofstdinc.h"

#define DCMTK_LOG4CPLUS_MESSAGE_VERSION 2


namespace dcmtk
{

namespace log4cplus
{

#if ! defined (DCMTK_LOG4CPLUS_SINGLE_THREADED)
SocketAppender::ConnectorThread::ConnectorThread (
    SocketAppender & socket_appender)
    : sa (socket_appender)
    , exit_flag (false)
{ }


SocketAppender::ConnectorThread::~ConnectorThread ()
{ }


void
SocketAppender::ConnectorThread::run ()
{
    while (true)
    {
        trigger_ev.timed_wait (30 * 1000);

        getLogLog().debug (
            DCMTK_LOG4CPLUS_TEXT("SocketAppender::ConnectorThread::run()")
            DCMTK_LOG4CPLUS_TEXT("- running..."));

        // Check exit condition as the very first thing.

        {
            thread::Guard guard (access_mutex);
            if (exit_flag)
                return;
            trigger_ev.reset ();
        }

        // Do not try to re-open already open socket.

        {
            thread::Guard guard (sa.access_mutex);
            if (sa.socket.isOpen ())
                continue;
        }

        // The socket is not open, try to reconnect.

        helpers::Socket socket (sa.host, sa.port);
        if (! socket.isOpen ())
        {
            getLogLog().error(
                DCMTK_LOG4CPLUS_TEXT("SocketAppender::ConnectorThread::run()")
                DCMTK_LOG4CPLUS_TEXT("- Cannot connect to server"));

            // Sleep for a short while after unsuccessful connection attempt
            // so that we do not try to reconnect after each logging attempt
            // which could be many times per second.
            helpers::sleep (5);

            continue;
        }

        // Connection was successful, move the socket into SocketAppender.

        {
            thread::Guard guard (sa.access_mutex);
            sa.socket = socket;
            sa.connected = true;
        }
    }
}


void
SocketAppender::ConnectorThread::terminate ()
{
    {
        thread::Guard guard (access_mutex);
        exit_flag = true;
        trigger_ev.signal ();
    }
    join ();
}


void
SocketAppender::ConnectorThread::trigger ()
{
    trigger_ev.signal ();
}

#endif


//////////////////////////////////////////////////////////////////////////////
// SocketAppender ctors and dtor
//////////////////////////////////////////////////////////////////////////////

SocketAppender::SocketAppender(const tstring& host_, int port_,
    const tstring& serverName_)
: host(host_),
  port(port_),
  serverName(serverName_)
{
    openSocket();
    initConnector ();
}



SocketAppender::SocketAppender(const helpers::Properties & properties, tstring&)
 : Appender(properties),
   port(9998)
{
    host = properties.getProperty( DCMTK_LOG4CPLUS_TEXT("host") );
    if(properties.exists( DCMTK_LOG4CPLUS_TEXT("port") )) {
        tstring tmp = properties.getProperty( DCMTK_LOG4CPLUS_TEXT("port") );
        port = atoi(DCMTK_LOG4CPLUS_TSTRING_TO_STRING(tmp).c_str());
    }
    serverName = properties.getProperty( DCMTK_LOG4CPLUS_TEXT("ServerName") );

    openSocket();
    initConnector ();
}



SocketAppender::~SocketAppender()
{
#if ! defined (DCMTK_LOG4CPLUS_SINGLE_THREADED)
    connector->terminate ();
#endif

    destructorImpl();
}



//////////////////////////////////////////////////////////////////////////////
// SocketAppender public methods
//////////////////////////////////////////////////////////////////////////////

void
SocketAppender::close()
{
    getLogLog().debug(DCMTK_LOG4CPLUS_TEXT("Entering SocketAppender::close()..."));

#if ! defined (DCMTK_LOG4CPLUS_SINGLE_THREADED)
    connector->terminate ();
#endif

    socket.close();
    closed = true;
}



//////////////////////////////////////////////////////////////////////////////
// SocketAppender protected methods
//////////////////////////////////////////////////////////////////////////////

void
SocketAppender::openSocket()
{
    if(!socket.isOpen()) {
        socket = helpers::Socket(host, port);
    }
}


void
SocketAppender::initConnector ()
{
#if ! defined (DCMTK_LOG4CPLUS_SINGLE_THREADED)
    connected = true;
    connector = new ConnectorThread (*this);
    connector->start ();
#endif
}


void
SocketAppender::append(const spi::InternalLoggingEvent& event)
{
#if ! defined (DCMTK_LOG4CPLUS_SINGLE_THREADED)
    if (! connected)
    {
        connector->trigger ();
        return;
    }

#else
    if(!socket.isOpen()) {
        openSocket();
        if(!socket.isOpen()) {
            getLogLog().error(DCMTK_LOG4CPLUS_TEXT("SocketAppender::append()- Cannot connect to server"));
            return;
        }
    }

#endif

    helpers::SocketBuffer buffer = helpers::convertToBuffer(event, serverName);
    helpers::SocketBuffer msgBuffer(DCMTK_LOG4CPLUS_MAX_MESSAGE_SIZE);

    msgBuffer.appendSize_t(buffer.getSize());
    msgBuffer.appendBuffer(buffer);

    bool ret = socket.write(msgBuffer);
    if (! ret)
    {
#if ! defined (DCMTK_LOG4CPLUS_SINGLE_THREADED)
        connected = false;
        connector->trigger ();
#endif
    }
}


/////////////////////////////////////////////////////////////////////////////
// namespace helpers methods
/////////////////////////////////////////////////////////////////////////////

namespace helpers
{

SocketBuffer
convertToBuffer(const spi::InternalLoggingEvent& event,
    const tstring& serverName)
{
    SocketBuffer buffer(DCMTK_LOG4CPLUS_MAX_MESSAGE_SIZE - sizeof(unsigned int));

    buffer.appendByte(DCMTK_LOG4CPLUS_MESSAGE_VERSION);
    buffer.appendByte(1);

    buffer.appendString(serverName);
    buffer.appendString(event.getLoggerName());
    buffer.appendInt(event.getLogLevel());
    buffer.appendString(event.getNDC());
    buffer.appendString(event.getMessage());
    buffer.appendString(event.getThread());
    buffer.appendInt( OFstatic_cast(unsigned int, event.getTimestamp().sec()) );
    buffer.appendInt( OFstatic_cast(unsigned int, event.getTimestamp().usec()) );
    buffer.appendString(event.getFile());
    buffer.appendInt(event.getLine());

    return buffer;
}


spi::InternalLoggingEvent
readFromBuffer(SocketBuffer& buffer)
{
    unsigned char msgVersion = buffer.readByte();
    if(msgVersion != DCMTK_LOG4CPLUS_MESSAGE_VERSION) {
        SharedObjectPtr<LogLog> loglog = LogLog::getLogLog();
        loglog->warn(DCMTK_LOG4CPLUS_TEXT("readFromBuffer() received socket message with an invalid version"));
    }

    unsigned char sizeOfChar = buffer.readByte();

    tstring serverName = buffer.readString(sizeOfChar);
    tstring loggerName = buffer.readString(sizeOfChar);
    LogLevel ll = buffer.readInt();
    tstring ndc = buffer.readString(sizeOfChar);
    if(serverName.length() > 0) {
        if(ndc.length() == 0) {
            ndc = serverName;
        }
        else {
            ndc = serverName + DCMTK_LOG4CPLUS_TEXT(" - ") + ndc;
        }
    }
    tstring message = buffer.readString(sizeOfChar);
    tstring thread = buffer.readString(sizeOfChar);
    long sec = buffer.readInt();
    long usec = buffer.readInt();
    tstring file = buffer.readString(sizeOfChar);
    int line = buffer.readInt();

    return spi::InternalLoggingEvent(loggerName,
                                                ll,
                                                ndc,
                                                message,
                                                thread,
                                                Time(sec, usec),
                                                file,
                                                line,
                                                "");
}

} // namespace helpers

} // namespace log4cplus

} // namespace dcmtk
