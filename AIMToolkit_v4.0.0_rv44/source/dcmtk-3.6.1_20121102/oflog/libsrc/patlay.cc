/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "dcmtk/oflog/layout.h"
#include "dcmtk/oflog/helpers/loglog.h"
#include "dcmtk/oflog/helpers/timehelp.h"
#include "dcmtk/oflog/helpers/strhelp.h"
#include "dcmtk/oflog/helpers/socket.h"
#include "dcmtk/oflog/spi/logevent.h"

//#include <stdlib.h>
//#include <exception>

#define INCLUDE_CSTDLIB
#define INCLUDE_UNISTD              /* needed for declaration of getpid() */
#include "dcmtk/ofstd/ofstdinc.h"

#ifdef DCMTK_LOG4CPLUS_HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif
#ifdef DCMTK_LOG4CPLUS_HAVE_UNISTD_H
#include <unistd.h>
#endif
#ifdef _WIN32
#include <process.h>                /* needed for declaration of getpid() */
#endif

namespace
{

static
#if defined (_WIN32)
DWORD
get_process_id ()
{
    return GetCurrentProcessId ();
}

#elif defined (DCMTK_LOG4CPLUS_HAVE_GETPID)
pid_t
get_process_id ()
{
    return getpid ();
}

#else
int
get_process_id ()
{
    return 0;
}

#endif

} // namespace


using namespace std;
using namespace dcmtk::log4cplus;
using namespace dcmtk::log4cplus::helpers;
using namespace dcmtk::log4cplus::spi;


#define ESCAPE_CHAR DCMTK_LOG4CPLUS_TEXT('%')


namespace dcmtk {
namespace log4cplus {
    namespace pattern {

        /**
         * This is used by PatternConverter class to inform them how to format
         * their output.
         */
        struct FormattingInfo {
            int minLen;
            size_t maxLen;
            bool leftAlign;
            FormattingInfo() { reset(); }

            void reset();
            void dump(LogLog&);
        };



        /**
         * This is the base class of all "Converter" classes that format a
         * field of InternalLoggingEvent objects.  In fact, the PatternLayout
         * class simply uses an array of PatternConverter objects to format
         * and append a logging event.
         */
        class PatternConverter : protected LogLogUser {
        public:
            PatternConverter(const FormattingInfo& info);
            virtual ~PatternConverter() {}
            void formatAndAppend(tostream& output,
                                 const InternalLoggingEvent& event);

        protected:
            virtual tstring convert(const InternalLoggingEvent& event) = 0;

        private:
            int minLen;
            size_t maxLen;
            bool leftAlign;
        };



        /**
         * This PatternConverter returns a constant string.
         */
        class LiteralPatternConverter : public PatternConverter {
        public:
            LiteralPatternConverter(const tstring& str);
            virtual tstring convert(const InternalLoggingEvent&) {
                return str;
            }

        private:
            tstring str;
        };



        /**
         * This PatternConverter is used to format most of the "simple" fields
         * found in the InternalLoggingEvent object.
         */
        class BasicPatternConverter : public PatternConverter {
        public:
            enum Type { THREAD_CONVERTER,
                        PROCESS_CONVERTER,
                        LOGLEVEL_CONVERTER,
                        LOGLEVEL_PREFIX_CONVERTER,
                        NDC_CONVERTER,
                        MESSAGE_CONVERTER,
                        NEWLINE_CONVERTER,
                        FILE_CONVERTER,
                        LINE_CONVERTER,
                        FULL_LOCATION_CONVERTER,
                        FUNCTION_CONVERTER };
            BasicPatternConverter(const FormattingInfo& info, Type type);
            virtual tstring convert(const InternalLoggingEvent& event);

        private:
          // Disable copy
            BasicPatternConverter(const BasicPatternConverter&);
            BasicPatternConverter& operator=(BasicPatternConverter&);

            LogLevelManager& llmCache;
            Type type;
        };



        /**
         * This PatternConverter is used to format the Logger field found in
         * the InternalLoggingEvent object.
         */
        class LoggerPatternConverter : public PatternConverter {
        public:
            LoggerPatternConverter(const FormattingInfo& info, int precision);
            virtual tstring convert(const InternalLoggingEvent& event);

        private:
            int precision;
        };



        /**
         * This PatternConverter is used to format the timestamp field found in
         * the InternalLoggingEvent object.  It will be formatted according to
         * the specified "pattern".
         */
        class DatePatternConverter : public PatternConverter {
        public:
            DatePatternConverter(const FormattingInfo& info,
                                 const tstring& pattern,
                                 bool use_gmtime);
            virtual tstring convert(const InternalLoggingEvent& event);

        private:
            bool use_gmtime;
            tstring format;
        };



        /**
         * This PatternConverter is used to format the hostname field.
         */
        class HostnamePatternConverter : public PatternConverter {
        public:
            HostnamePatternConverter(const FormattingInfo& info, bool fqdn);
            virtual tstring convert(const InternalLoggingEvent& event);

        private:
            tstring hostname_;
        };



        /**
         * This class parses a "pattern" string into an array of
         * PatternConverter objects.
         * <p>
         * @see PatternLayout for the formatting of the "pattern" string.
         */
        class PatternParser : protected LogLogUser {
        public:
            PatternParser(const tstring& pattern);
            OFauto_ptr<OFList<PatternConverter*> > parse();

        private:
          // Types
            enum ParserState { LITERAL_STATE,
                               CONVERTER_STATE,
                               DOT_STATE,
                               MIN_STATE,
                               MAX_STATE };

          // Methods
            tstring extractOption();
            int extractPrecisionOption();
            void finalizeConverter(tchar c);

          // Data
            tstring pattern;
            FormattingInfo formattingInfo;
            OFauto_ptr<OFList<PatternConverter*> > list;
            ParserState state;
            tstring::size_type pos;
            tstring currentLiteral;
        };
    }
}

} // namespace dcmtk

using namespace dcmtk::log4cplus::pattern;
typedef OFList<PatternConverter*> PatternConverterList;
typedef OFListIterator(PatternConverter*) PatternConverterListIterator;



////////////////////////////////////////////////
// PatternConverter methods:
////////////////////////////////////////////////

void
FormattingInfo::reset() {
    minLen = -1;
    maxLen = 0x7FFFFFFF;
    leftAlign = false;
}


void
FormattingInfo::dump(LogLog& loglog) {
    tostringstream buf;
    buf << DCMTK_LOG4CPLUS_TEXT("min=") << minLen
        << DCMTK_LOG4CPLUS_TEXT(", max=") << maxLen
        << DCMTK_LOG4CPLUS_TEXT(", leftAlign=")
        << (leftAlign ? DCMTK_LOG4CPLUS_TEXT("true") : DCMTK_LOG4CPLUS_TEXT("false"));
    OFSTRINGSTREAM_GETOFSTRING(buf, str)
    loglog.debug(str);
}




////////////////////////////////////////////////
// PatternConverter methods:
////////////////////////////////////////////////

PatternConverter::PatternConverter(const FormattingInfo& i)
{
    minLen = i.minLen;
    maxLen = i.maxLen;
    leftAlign = i.leftAlign;
}



void
PatternConverter::formatAndAppend
                     (tostream& output, const InternalLoggingEvent& event)
{
    tstring s = convert(event);
    size_t len = s.length();

    if(len > maxLen) {
        output << s.substr(len - maxLen);
    }
    else if(OFstatic_cast(int, len) < minLen) {
        if(leftAlign) {
            output << s;
            output << tstring(minLen - len, DCMTK_LOG4CPLUS_TEXT(' '));
        }
        else {
            output << tstring(minLen - len, DCMTK_LOG4CPLUS_TEXT(' '));
            output << s;
        }
    }
    else {
        output << s;
    }
}



////////////////////////////////////////////////
// LiteralPatternConverter methods:
////////////////////////////////////////////////

LiteralPatternConverter::LiteralPatternConverter
                                                      (const tstring& str_)
: PatternConverter(FormattingInfo()),
  str(str_)
{
}



////////////////////////////////////////////////
// BasicPatternConverter methods:
////////////////////////////////////////////////

BasicPatternConverter::BasicPatternConverter
                                        (const FormattingInfo& info, Type type_)
: PatternConverter(info),
  llmCache(getLogLevelManager()),
  type(type_)
{
}



tstring
BasicPatternConverter::convert
                                            (const InternalLoggingEvent& event)
{
    switch(type) {
    case LOGLEVEL_CONVERTER:        return llmCache.toString(event.getLogLevel());
    case LOGLEVEL_PREFIX_CONVERTER: return llmCache.toString(event.getLogLevel()).substr(0, 1);
    case NDC_CONVERTER:             return event.getNDC();
    case MESSAGE_CONVERTER:         return event.getMessage();
    case NEWLINE_CONVERTER:         return DCMTK_LOG4CPLUS_TEXT("\n");
    case FILE_CONVERTER:            return event.getFile();
    case THREAD_CONVERTER:          return event.getThread();
    case PROCESS_CONVERTER:         return convertIntegerToString(get_process_id ());
    case FUNCTION_CONVERTER:        return event.getFunction ();

    case LINE_CONVERTER:
        {
            int line = event.getLine();
            if(line != -1) {
                return convertIntegerToString(line);
            }
            else {
                return tstring();
            }
        }

    case FULL_LOCATION_CONVERTER:
        {
            tstring const & filename = event.getFile();
            if(! filename.empty ()) {
                return   filename
                       + DCMTK_LOG4CPLUS_TEXT(":")
                       + convertIntegerToString(event.getLine());
            }
            else {
                return DCMTK_LOG4CPLUS_TEXT(":");
            }
        }
    }

    return DCMTK_LOG4CPLUS_TEXT("INTERNAL DCMTK_LOG4CPLUS ERROR");
}



////////////////////////////////////////////////
// LoggerPatternConverter methods:
////////////////////////////////////////////////

LoggerPatternConverter::LoggerPatternConverter
                                    (const FormattingInfo& info, int precision_)
: PatternConverter(info),
  precision(precision_)
{
}



tstring
LoggerPatternConverter::convert
                                            (const InternalLoggingEvent& event)
{
    const tstring& name = event.getLoggerName();
    if (precision <= 0) {
        return name;
    }
    else {
        size_t len = name.length();

        // We substract 1 from 'len' when assigning to 'end' to avoid out of
        // bounds exception in return r.substring(end+1, len). This can happen
        // if precision is 1 and the logger name ends with a dot.
        tstring::size_type end = len - 1;
        for(int i=precision; i>0; --i) {
            end = name.rfind(DCMTK_LOG4CPLUS_TEXT('.'), end - 1);
            if(end == OFString_npos) {
                return name;
            }
        }
        return name.substr(end + 1);
    }
}



////////////////////////////////////////////////
// DatePatternConverter methods:
////////////////////////////////////////////////


DatePatternConverter::DatePatternConverter
                                               (const FormattingInfo& info,
                                                const tstring& pattern,
                                                bool use_gmtime_)
: PatternConverter(info),
  use_gmtime(use_gmtime_),
  format(pattern)
{
}



tstring
DatePatternConverter::convert
                                            (const InternalLoggingEvent& event)
{
    return event.getTimestamp().getFormattedTime(format, use_gmtime);
}




////////////////////////////////////////////////
// HostnamePatternConverter methods:
////////////////////////////////////////////////

HostnamePatternConverter::HostnamePatternConverter (
    const FormattingInfo& info, bool fqdn)
    : PatternConverter(info)
    , hostname_ (getHostname (fqdn))
{ }


tstring
HostnamePatternConverter::convert (
    const InternalLoggingEvent &)
{
    return hostname_;
}



////////////////////////////////////////////////
// PatternParser methods:
////////////////////////////////////////////////

PatternParser::PatternParser(const tstring& pattern_)
: pattern(pattern_),
  list(new OFList<PatternConverter*>),
  state(LITERAL_STATE),
  pos(0)
{
}



tstring
PatternParser::extractOption()
{
    if (   (pos < pattern.length())
        && (pattern[pos] == DCMTK_LOG4CPLUS_TEXT('{')))
    {
        tstring::size_type end = pattern.find_first_of(DCMTK_LOG4CPLUS_TEXT('}'), pos);
        if (end != OFString_npos) {
            tstring r = pattern.substr(pos + 1, end - pos - 1);
            pos = end + 1;
            return r;
        }
        else {
            getLogLog().error(DCMTK_LOG4CPLUS_TEXT("No matching '}' found in conversion pattern string \"")
                    + pattern + DCMTK_LOG4CPLUS_TEXT("\""));
            pos = pattern.length();
        }
    }

    return DCMTK_LOG4CPLUS_TEXT("");
}


int
PatternParser::extractPrecisionOption()
{
    tstring opt = extractOption();
    int r = 0;
    if(opt.length() > 0) {
        r = atoi(DCMTK_LOG4CPLUS_TSTRING_TO_STRING(opt).c_str());
    }
    return r;
}



OFauto_ptr<PatternConverterList>
PatternParser::parse()
{
    tchar c;
    pos = 0;
    while(pos < pattern.length()) {
        c = pattern[pos++];
        switch (state) {
        case LITERAL_STATE :
            // In literal state, the last char is always a literal.
            if(pos == pattern.length()) {
                currentLiteral += c;
                continue;
            }
            if(c == ESCAPE_CHAR) {
                // peek at the next char.
                switch (pattern[pos]) {
                case ESCAPE_CHAR:
                    currentLiteral += c;
                    pos++; // move pointer
                    break;
                default:
                    if(currentLiteral.length() != 0) {
                        list->push_back
                             (new LiteralPatternConverter(currentLiteral));
                        //getLogLog().debug("Parsed LITERAL converter: \""
                        //                  +currentLiteral+"\".");
                    }
                    currentLiteral.resize(0);
                    currentLiteral += c; // append %
                    state = CONVERTER_STATE;
                    formattingInfo.reset();
                }
            }
            else {
                currentLiteral += c;
            }
            break;

        case CONVERTER_STATE:
            currentLiteral += c;
            switch (c) {
            case DCMTK_LOG4CPLUS_TEXT('-'):
                formattingInfo.leftAlign = true;
                break;
            case DCMTK_LOG4CPLUS_TEXT('.'):
                state = DOT_STATE;
                break;
            default:
                if(c >= DCMTK_LOG4CPLUS_TEXT('0') && c <= DCMTK_LOG4CPLUS_TEXT('9')) {
                    formattingInfo.minLen = c - DCMTK_LOG4CPLUS_TEXT('0');
                    state = MIN_STATE;
                }
                else {
                    finalizeConverter(c);
                }
            } // switch
            break;

        case MIN_STATE:
            currentLiteral += c;
            if (c >= DCMTK_LOG4CPLUS_TEXT('0') && c <= DCMTK_LOG4CPLUS_TEXT('9')) {
                formattingInfo.minLen = formattingInfo.minLen * 10 + (c - DCMTK_LOG4CPLUS_TEXT('0'));
            }
            else if(c == DCMTK_LOG4CPLUS_TEXT('.')) {
                state = DOT_STATE;
            }
            else {
                finalizeConverter(c);
            }
            break;

        case DOT_STATE:
            currentLiteral += c;
            if(c >= DCMTK_LOG4CPLUS_TEXT('0') && c <= DCMTK_LOG4CPLUS_TEXT('9')) {
                formattingInfo.maxLen = c - DCMTK_LOG4CPLUS_TEXT('0');
                state = MAX_STATE;
            }
            else {
                tostringstream buf;
                buf << DCMTK_LOG4CPLUS_TEXT("Error occured in position ")
                    << pos
                    << DCMTK_LOG4CPLUS_TEXT(".\n Was expecting digit, instead got char \"")
                    << c
                    << DCMTK_LOG4CPLUS_TEXT("\".");
                OFSTRINGSTREAM_GETOFSTRING(buf, str)
                getLogLog().error(str);
                state = LITERAL_STATE;
            }
            break;

         case MAX_STATE:
            currentLiteral += c;
            if (c >= DCMTK_LOG4CPLUS_TEXT('0') && c <= DCMTK_LOG4CPLUS_TEXT('9'))
                formattingInfo.maxLen = formattingInfo.maxLen * 10 + (c - DCMTK_LOG4CPLUS_TEXT('0'));
            else {
                finalizeConverter(c);
                state = LITERAL_STATE;
            }
            break;
        } // end switch
    } // end while

    if(currentLiteral.length() != 0) {
        list->push_back(new LiteralPatternConverter(currentLiteral));
      //getLogLog().debug("Parsed LITERAL converter: \""+currentLiteral+"\".");
    }

    return list;
}



void
PatternParser::finalizeConverter(tchar c)
{
    PatternConverter* pc = 0;
    switch (c) {
        case DCMTK_LOG4CPLUS_TEXT('c'):
            pc = new LoggerPatternConverter(formattingInfo,
                                            extractPrecisionOption());
            getLogLog().debug( DCMTK_LOG4CPLUS_TEXT("LOGGER converter.") );
            formattingInfo.dump(getLogLog());
            break;

        case DCMTK_LOG4CPLUS_TEXT('d'):
        case DCMTK_LOG4CPLUS_TEXT('D'):
            {
                tstring dOpt = extractOption();
                if(dOpt.length() == 0) {
                    dOpt = DCMTK_LOG4CPLUS_TEXT("%Y-%m-%d %H:%M:%S");
                }
                bool use_gmtime = c == DCMTK_LOG4CPLUS_TEXT('d');
                pc = new DatePatternConverter(formattingInfo, dOpt, use_gmtime);
                //if(use_gmtime) {
                //    getLogLog().debug("GMT DATE converter.");
                //}
                //else {
                //    getLogLog().debug("LOCAL DATE converter.");
                //}
                //formattingInfo.dump(getLogLog());
            }
            break;

        case DCMTK_LOG4CPLUS_TEXT('f'):
            pc = new BasicPatternConverter
                          (formattingInfo,
                           BasicPatternConverter::FUNCTION_CONVERTER);
            //getLogLog().debug("FUNCTION NAME converter.");
            //formattingInfo.dump(getLogLog());
            break;

        case DCMTK_LOG4CPLUS_TEXT('F'):
            pc = new BasicPatternConverter
                          (formattingInfo,
                           BasicPatternConverter::FILE_CONVERTER);
            //getLogLog().debug("FILE NAME converter.");
            //formattingInfo.dump(getLogLog());
            break;

        case DCMTK_LOG4CPLUS_TEXT('h'):
        case DCMTK_LOG4CPLUS_TEXT('H'):
            {
                bool fqdn = (c == DCMTK_LOG4CPLUS_TEXT('H'));
                pc = new HostnamePatternConverter(formattingInfo, fqdn);
                // getLogLog().debug( DCMTK_LOG4CPLUS_TEXT("HOSTNAME converter.") );
                // formattingInfo.dump(getLogLog());
            }
            break;

        case DCMTK_LOG4CPLUS_TEXT('l'):
            pc = new BasicPatternConverter
                          (formattingInfo,
                           BasicPatternConverter::FULL_LOCATION_CONVERTER);
            //getLogLog().debug("FULL LOCATION converter.");
            //formattingInfo.dump(getLogLog());
            break;

        case DCMTK_LOG4CPLUS_TEXT('L'):
            pc = new BasicPatternConverter
                          (formattingInfo,
                           BasicPatternConverter::LINE_CONVERTER);
            //getLogLog().debug("LINE NUMBER converter.");
            //formattingInfo.dump(getLogLog());
            break;

        case DCMTK_LOG4CPLUS_TEXT('m'):
            pc = new BasicPatternConverter
                          (formattingInfo,
                           BasicPatternConverter::MESSAGE_CONVERTER);
            //getLogLog().debug("MESSAGE converter.");
            //formattingInfo.dump(getLogLog());
            break;

        case DCMTK_LOG4CPLUS_TEXT('n'):
            pc = new BasicPatternConverter
                          (formattingInfo,
                           BasicPatternConverter::NEWLINE_CONVERTER);
            //getLogLog().debug("NEWLINE converter.");
            //formattingInfo.dump(getLogLog());
            break;

        case DCMTK_LOG4CPLUS_TEXT('p'):
            pc = new BasicPatternConverter
                          (formattingInfo,
                           BasicPatternConverter::LOGLEVEL_CONVERTER);
            //getLogLog().debug("LOGLEVEL converter.");
            //formattingInfo.dump(getLogLog());
            break;

        case DCMTK_LOG4CPLUS_TEXT('P'):
            pc = new BasicPatternConverter
                          (formattingInfo,
                           BasicPatternConverter::LOGLEVEL_PREFIX_CONVERTER);
            //getLogLog().debug("LOGLEVEL PREFIX converter.");
            //formattingInfo.dump(getLogLog());
            break;

        case DCMTK_LOG4CPLUS_TEXT('t'):
            pc = new BasicPatternConverter
                          (formattingInfo,
                           BasicPatternConverter::THREAD_CONVERTER);
            //getLogLog().debug("THREAD converter.");
            //formattingInfo.dump(getLogLog());
            break;

        case DCMTK_LOG4CPLUS_TEXT('i'):
            pc = new BasicPatternConverter
                          (formattingInfo,
                           BasicPatternConverter::PROCESS_CONVERTER);
            //getLogLog().debug("PROCESS_CONVERTER converter.");
            //formattingInfo.dump(getLogLog());
            break;

        case DCMTK_LOG4CPLUS_TEXT('x'):
            pc = new BasicPatternConverter
                          (formattingInfo,
                           BasicPatternConverter::NDC_CONVERTER);
            //getLogLog().debug("NDC converter.");
            break;

        default:
            tostringstream buf;
            buf << DCMTK_LOG4CPLUS_TEXT("Unexpected char [")
                << c
                << DCMTK_LOG4CPLUS_TEXT("] at position ")
                << pos
                << DCMTK_LOG4CPLUS_TEXT(" in conversion pattern.");
            OFSTRINGSTREAM_GETOFSTRING(buf, str)
            getLogLog().error(str);
            pc = new LiteralPatternConverter(currentLiteral);
    }

    currentLiteral.resize(0);
    list->push_back(pc);
    state = LITERAL_STATE;
    formattingInfo.reset();
}





////////////////////////////////////////////////
// PatternLayout methods:
////////////////////////////////////////////////

PatternLayout::PatternLayout(const tstring& pattern_, bool formatEachLine_)
{
    init(pattern_, formatEachLine_);
}


PatternLayout::PatternLayout(const Properties& properties, tstring& error)
{
    bool hasPattern = properties.exists( DCMTK_LOG4CPLUS_TEXT("Pattern") );
    bool hasConversionPattern = properties.exists( DCMTK_LOG4CPLUS_TEXT("ConversionPattern") );
    tstring eachLine = properties.getProperty( DCMTK_LOG4CPLUS_TEXT("FormatEachLine"), "yes");
    bool formatEachLine_ = true;

    if (eachLine == DCMTK_LOG4CPLUS_TEXT("yes"))
        formatEachLine_ = true;
    else if (eachLine == DCMTK_LOG4CPLUS_TEXT("no"))
        formatEachLine_ = false;
    else
        getLogLog().warn( DCMTK_LOG4CPLUS_TEXT("PatternLayout- the \"FormatEachLine\" property has an invalid value, assuming \"yes\""));

    if(hasPattern) {
        getLogLog().warn( DCMTK_LOG4CPLUS_TEXT("PatternLayout- the \"Pattern\" property has been deprecated.  Use \"ConversionPattern\" instead."));
    }

    if(hasConversionPattern) {
        init(properties.getProperty( DCMTK_LOG4CPLUS_TEXT("ConversionPattern") ), formatEachLine_);
    }
    else if(hasPattern) {
        init(properties.getProperty( DCMTK_LOG4CPLUS_TEXT("Pattern") ), formatEachLine_);
    }
    else {
        error = DCMTK_LOG4CPLUS_TEXT("ConversionPattern not specified in properties");
        //throw STD_NAMESPACE runtime_error("ConversionPattern not specified in properties");
        return;
    }
    error.clear();
}


void
PatternLayout::init(const tstring& pattern_, bool formatEachLine_)
{
    this->pattern = pattern_;
    this->formatEachLine = formatEachLine_;
    this->parsedPattern = PatternParser(pattern).parse();

    // Let's validate that our parser didn't give us any NULLs.  If it did,
    // we will convert them to a valid PatternConverter that does nothing so
    // at least we don't core.
    for(PatternConverterListIterator it=parsedPattern->begin();
        it!=parsedPattern->end();
        ++it)
    {
        if( (*it) == 0 ) {
            getLogLog().error(DCMTK_LOG4CPLUS_TEXT("Parsed Pattern created a NULL PatternConverter"));
            (*it) = new LiteralPatternConverter( DCMTK_LOG4CPLUS_TEXT("") );
        }
    }
    if(parsedPattern->size() == 0) {
        getLogLog().warn(DCMTK_LOG4CPLUS_TEXT("PatternLayout pattern is empty.  Using default..."));
        parsedPattern->push_back
           (new BasicPatternConverter(FormattingInfo(),
                                      BasicPatternConverter::MESSAGE_CONVERTER));
    }
}



PatternLayout::~PatternLayout()
{
    if (parsedPattern.get() == NULL)
        return;
    for(PatternConverterListIterator it=parsedPattern->begin();
        it!=parsedPattern->end();
        ++it)
    {
        delete (*it);
    }
}



void
PatternLayout::formatAndAppend(tostream& output,
                               const InternalLoggingEvent& event)
{
    if (formatEachLine && event.getMessage().find('\n') != OFString_npos)
    {
        size_t pos = 0;
        size_t last_pos = 0;

        while (pos != OFString_npos)
        {
            pos = event.getMessage().find('\n', last_pos);

            // Create a substring from just this single line
            tstring tmp_message(event.getMessage().substr(last_pos, (pos == OFString_npos) ? pos : pos - last_pos));

            // Then create a temporary InternalLoggingEvent for this one line
            InternalLoggingEvent tmp_event(event.getLoggerName(), event.getLogLevel(),
                event.getNDC(), tmp_message, event.getThread(), event.getTimestamp(),
                event.getFile(), event.getLine(), event.getFunction());
            // And finally, log this single line
            formatAndAppend(output, tmp_event);

            // Skip the "\n"
            last_pos = pos + 1;
        }
    }
    else
    {
        for(PatternConverterListIterator it=parsedPattern->begin();
            it!=parsedPattern->end();
            ++it)
        {
            (*it)->formatAndAppend(output, event);
        }
    }
}


