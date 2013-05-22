/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/** @file */

#ifndef DCMTK__LOG4CPLUS_SYSLOG_APPENDER_HEADER_
#define DCMTK__LOG4CPLUS_SYSLOG_APPENDER_HEADER_

#include "dcmtk/oflog/config.h"

#if defined(DCMTK_LOG4CPLUS_HAVE_SYSLOG_H) && !defined(_WIN32)
#include "dcmtk/oflog/appender.h"

namespace dcmtk {
namespace log4cplus {

    /**
     * Appends log events to a file.
     *
     * <h3>Properties</h3>
     * <dl>
     * <dt><tt>ident</tt></dt>
     * <dd>First argument to <code>openlog()</code>, a string that
     * will be prepended to every message.</dd>
     * </dl>
     */
    class DCMTK_LOG4CPLUS_EXPORT SysLogAppender : public Appender {
    public:
      // Ctors
        SysLogAppender(const tstring& ident);
        SysLogAppender(const helpers::Properties properties, tstring& error);

      // Dtor
        virtual ~SysLogAppender();

      // Methods
        virtual void close();

    protected:
        virtual int getSysLogLevel(const LogLevel& ll) const;
        virtual void append(const spi::InternalLoggingEvent& event);

      // Data
        tstring ident;

    private:
      // Disallow copying of instances of this class
        SysLogAppender(const SysLogAppender&);
        SysLogAppender& operator=(const SysLogAppender&);
    };

} // end namespace log4cplus
} // end namespace dcmtk

#endif // defined(HAVE_SYSLOG_H)

#endif // DCMTK__LOG4CPLUS_SYSLOG_APPENDER_HEADER_
