/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/** @file */

#ifndef DCMTK__LOG4CPLUS_SPI_INTERNAL_LOGGING_EVENT_HEADER_
#define DCMTK__LOG4CPLUS_SPI_INTERNAL_LOGGING_EVENT_HEADER_

#include "dcmtk/oflog/config.h"
#include "dcmtk/oflog/loglevel.h"
#include "dcmtk/oflog/ndc.h"
#include "dcmtk/oflog/tstring.h"
#include "dcmtk/oflog/helpers/timehelp.h"
#include "dcmtk/oflog/helpers/threads.h"

#include "dcmtk/ofstd/ofaptr.h"

namespace dcmtk {
namespace log4cplus {
    namespace spi {
        /**
         * The internal representation of logging events. When an affirmative
         * decision is made to log then a <code>InternalLoggingEvent</code>
         * instance is created. This instance is passed around to the
         * different log4cplus components.
         *
         * This class is of concern to those wishing to extend log4cplus.
         */
        class DCMTK_LOG4CPLUS_EXPORT InternalLoggingEvent {
        public:
          // Ctors
             /**
              * Instantiate a LoggingEvent from the supplied parameters.
              *
              * @param logger   The logger of this event.
              * @param ll_      The LogLevel of this event.
              * @param message_ The message of this event.
              * @param filename Name of file where this event has occurred,
              * can be NULL.
              * @param line_    Line number in file specified by
              *                 the <code>filename</code> parameter.
              * @param function_ Function where this event has occurred
              */
             InternalLoggingEvent(const tstring& logger,
                                  LogLevel ll_,
                                  const tstring& message_,
                                  const char* filename,
                                  int line_,
                                  const char* function_)
              : message(message_),
                loggerName(logger),
                ll(ll_),
                ndc(),
                thread(),
                timestamp(helpers::Time::gettimeofday()),
                file( (  filename
                       ? DCMTK_LOG4CPLUS_C_STR_TO_TSTRING(filename)
                       : tstring()) ),
                line(line_),
                function( ( function_
                          ? DCMTK_LOG4CPLUS_C_STR_TO_TSTRING(function_)
                          : tstring()) ),
                threadCached(false),
                ndcCached(false)
             {
             }

             InternalLoggingEvent(const tstring& logger,
                                  LogLevel ll_,
                                  const tstring& ndc_,
                                  const tstring& message_,
                                  const tstring& thread_,
                                  helpers::Time time,
                                  const tstring& file_,
                                  int line_,
                                  const tstring& function_)
              : message(message_),
                loggerName(logger),
                ll(ll_),
                ndc(ndc_),
                thread(thread_),
                timestamp(time),
                file(file_),
                line(line_),
                function(function_),
                threadCached(true),
                ndcCached(true)
             {
             }

             InternalLoggingEvent(const spi::InternalLoggingEvent& rhs)
              : message(rhs.getMessage()),
                loggerName(rhs.getLoggerName()),
                ll(rhs.getLogLevel()),
                ndc(rhs.getNDC()),
                thread(rhs.getThread()),
                timestamp(rhs.getTimestamp()),
                file(rhs.getFile()),
                line(rhs.getLine()),
                function(rhs.getFunction()),
                threadCached(true),
                ndcCached(true)
             {
             }

            virtual ~InternalLoggingEvent();


          // public virtual methods
            /** The application supplied message of logging event. */
            virtual const tstring& getMessage() const;

            /** Returns the 'type' of InternalLoggingEvent.  Derived classes
             *  should override this method.  (NOTE: Values <= 1000 are
             *  reserved for log4cplus and should not be used.)
             */
            virtual unsigned int getType() const;

           /** Returns a copy of this object.  Derived classes
             *  should override this method.
	     */
            virtual OFauto_ptr<InternalLoggingEvent> clone() const;



          // public methods
            /** The logger of the logging event. It is set by
             *  the LoggingEvent constructor.
	     */
            const tstring& getLoggerName() const { return loggerName; }

            /** LogLevel of logging event. */
            LogLevel getLogLevel() const { return ll; }

            /** The nested diagnostic context (NDC) of logging event. */
            const tstring& getNDC() const {
                if(!ndcCached) {
                    ndc = dcmtk::log4cplus::getNDC().get();
                    ndcCached = true;
                }
                return ndc;
            }

            /** The name of thread in which this logging event was generated. */
            const tstring& getThread() const {
                if(!threadCached) {
                    thread = DCMTK_LOG4CPLUS_GET_CURRENT_THREAD_NAME;
                    threadCached = true;
                }
                return thread;
            }

            /** The number of milliseconds elapsed from 1/1/1970 until logging event
             *  was created. */
            const helpers::Time& getTimestamp() const { return timestamp; }

            /** The is the file where this log statement was written */
            const tstring& getFile() const { return file; }

            /** The is the line where this log statement was written */
            int getLine() const { return line; }

            /** The is the function where this log statement was written */
            const tstring& getFunction() const { return function; }

          // public operators
            spi::InternalLoggingEvent&
            operator=(const spi::InternalLoggingEvent& rhs);

          // static methods
            static unsigned int getDefaultType();

        protected:
          // Data
            tstring message;

        private:
            tstring loggerName;
            LogLevel ll;
            mutable tstring ndc;
            mutable tstring thread;
            helpers::Time timestamp;
            tstring file;
            int line;
            tstring function;
            /** Indicates whether or not the Threadname has been retrieved. */
            mutable bool threadCached;
            /** Indicates whether or not the NDC has been retrieved. */
            mutable bool ndcCached;
        };

    } // end namespace spi
} // end namespace log4cplus
} // end namespace dcmtk

#endif // DCMTK__LOG4CPLUS_SPI_INTERNAL_LOGGING_EVENT_HEADER_