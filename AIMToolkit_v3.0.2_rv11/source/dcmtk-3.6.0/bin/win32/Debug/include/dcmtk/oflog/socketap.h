/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/** @file */

#ifndef _LOG4CPLUS_SOCKET_APPENDER_HEADER_
#define _LOG4CPLUS_SOCKET_APPENDER_HEADER_

#include "dcmtk/oflog/config.h"
#include "dcmtk/oflog/appender.h"
#include "dcmtk/oflog/helpers/socket.h"
#include "dcmtk/oflog/helpers/syncprims.h"


#define LOG4CPLUS_MAX_MESSAGE_SIZE (8*1024)


namespace log4cplus {

    /**
     * Sends {@link spi::InternalLoggingEvent} objects to a remote a log server.
     *
     * The SocketAppender has the following properties:
     *
     * <ul>
     *
     *   <li>Remote logging is non-intrusive as far as the log event
     *   is concerned. In other words, the event will be logged with
     *   the same time stamp, NDC, location info as if it were logged
     *   locally by the client.
     *
     *   <li>SocketAppenders do not use a layout.
     *
     *   <li>Remote logging uses the TCP protocol. Consequently, if
     *   the server is reachable, then log events will eventually arrive
     *   at the server.
     *
     *   <li>If the remote server is down, the logging requests are
     *   simply dropped. However, if and when the server comes back up,
     *   then event transmission is resumed transparently. This
     *   transparent reconneciton is performed by a <em>connector</em>
     *   thread which periodically attempts to connect to the server.
     *
     *   <li>Logging events are automatically <em>buffered</em> by the
     *   native TCP implementation. This means that if the link to server
     *   is slow but still faster than the rate of (log) event production
     *   by the client, the client will not be affected by the slow
     *   network connection. However, if the network connection is slower
     *   then the rate of event production, then the client can only
     *   progress at the network rate. In particular, if the network link
     *   to the the server is down, the client will be blocked.
     *
     *   <li>On the other hand, if the network link is up, but the server
     *   is down, the client will not be blocked when making log requests
     *   but the log events will be lost due to server unavailability.
     * </ul>
     *
     * <h3>Properties</h3>
     * <dl>
     * <dt><tt>host</tt></dt>
     * <dd>Remote host name to connect and send events to.</dd>
     *
     * <dt><tt>port</tt></dt>
     * <dd>Port on remote host to send events to.</dd>
     *
     * <dt><tt>ServerName</tt></dt>
     * <dd>Host name of event's origin prepended to each event.</dd>
     *
     * </dl>
     */
    class LOG4CPLUS_EXPORT SocketAppender : public Appender {
    public:
      // Ctors
        SocketAppender(const log4cplus::tstring& host, int port,
                       const log4cplus::tstring& serverName = tstring());
        SocketAppender(const log4cplus::helpers::Properties & properties, log4cplus::tstring& error);

      // Dtor
        ~SocketAppender();

      // Methods
        virtual void close();

    protected:
        void openSocket();
        void initConnector ();
        virtual void append(const spi::InternalLoggingEvent& event);

      // Data
        log4cplus::helpers::Socket socket;
        log4cplus::tstring host;
        int port;
        log4cplus::tstring serverName;

#if ! defined (LOG4CPLUS_SINGLE_THREADED)
        class LOG4CPLUS_EXPORT ConnectorThread;
        friend class ConnectorThread;

        class LOG4CPLUS_EXPORT ConnectorThread
            : public thread::AbstractThread
            , public helpers::LogLogUser
        {
        public:
            ConnectorThread (SocketAppender &);
            virtual ~ConnectorThread ();

            virtual void run();

            void terminate ();
            void trigger ();

        protected:
            SocketAppender & sa;
            thread::ManualResetEvent trigger_ev;
            bool exit_flag;
        };

        volatile bool connected;
        helpers::SharedObjectPtr<ConnectorThread> connector;
#endif

    private:
      // Disallow copying of instances of this class
        SocketAppender(const SocketAppender&);
        SocketAppender& operator=(const SocketAppender&);
    };

    namespace helpers {
        LOG4CPLUS_EXPORT
        SocketBuffer convertToBuffer(const log4cplus::spi::InternalLoggingEvent& event,
                                     const log4cplus::tstring& serverName);

        LOG4CPLUS_EXPORT
        log4cplus::spi::InternalLoggingEvent readFromBuffer(SocketBuffer& buffer);
    } // end namespace helpers

} // end namespace log4cplus

#endif // _LOG4CPLUS_SOCKET_APPENDER_HEADER_

