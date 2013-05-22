/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "dcmtk/oflog/configrt.h"
#include "dcmtk/oflog/hierlock.h"
#include "dcmtk/oflog/helpers/loglog.h"
#include "dcmtk/oflog/helpers/sleep.h"
#include "dcmtk/oflog/helpers/strhelp.h"
#include "dcmtk/oflog/helpers/property.h"
#include "dcmtk/oflog/helpers/syncprims.h"
#include "dcmtk/oflog/spi/factory.h"
#include "dcmtk/oflog/spi/logimpl.h"

#ifdef HAVE_SYS_STAT_H
#  include <sys/stat.h>
#endif
//#include <algorithm>
//#include <vector>
//#include <cstdlib>
#define INCLUDE_CSTDLIB
#include "dcmtk/ofstd/ofstdinc.h"

namespace dcmtk
{

namespace log4cplus
{

using namespace dcmtk::log4cplus::helpers;
using namespace dcmtk::log4cplus::spi;


void initializeLog4cplus();


namespace
{
    static tchar const DELIM_START[] = DCMTK_LOG4CPLUS_TEXT("${");
    static tchar const DELIM_STOP[] = DCMTK_LOG4CPLUS_TEXT("}");
    static size_t const DELIM_START_LEN = 2;
    static size_t const DELIM_STOP_LEN = 1;


    /**
     * Perform variable substitution in string <code>val</code> from
     * environment variables.
     *
     * <p>The variable substitution delimeters are <b>${</b> and <b>}</b>.
     *
     * <p>For example, if the System properties contains "key=value", then
     * the call
     * <pre>
     * string s;
     * substEnvironVars(s, "Value of key is ${key}.");
     * </pre>
     *
     * will set the variable <code>s</code> to "Value of key is value.".
     *
     * <p>If no value could be found for the specified key, then
     * substitution defaults to the empty string.
     *
     * <p>For example, if there is no environment variable "inexistentKey",
     * then the call
     *
     * <pre>
     * string s;
     * substEnvironVars(s, "Value of inexistentKey is [${inexistentKey}]");
     * </pre>
     * will set <code>s</code> to "Value of inexistentKey is []"
     *
     * @param val The string on which variable substitution is performed.
     * @param dest The result.
     */
    static
    bool
    substVars (tstring & dest, const tstring & val, Properties const & props,
        helpers::LogLog& loglog, unsigned flags)
    {
        tstring::size_type i = 0;
        tstring::size_type var_start, var_end;
        tstring pattern (val);
        tstring key;
        tstring replacement;
        bool changed = false;
        bool const empty_vars
            = !! (flags & PropertyConfigurator::fAllowEmptyVars);
        bool const shadow_env
            = !! (flags & PropertyConfigurator::fShadowEnvironment);
        bool const rec_exp
            = !! (flags & PropertyConfigurator::fRecursiveExpansion);

        while (true)
        {
            // Find opening paren of variable substitution.
            var_start = pattern.find(DELIM_START, i);
            if (var_start == OFString_npos)
            {
                dest = pattern;
                return changed;
            }

            // Find closing paren of variable substitution.
            var_end = pattern.find(DELIM_STOP, var_start);
            if (var_end == OFString_npos)
            {
                tostringstream buffer;
                buffer << '"' << pattern
                       << "\" has no closing brace. "
                       << "Opening brace at position " << var_start << ".";
                OFSTRINGSTREAM_GETOFSTRING(buffer, str)
                loglog.error(str);
                dest = val;
                return false;
            }

            key.assign (pattern, var_start + DELIM_START_LEN,
                var_end - (var_start + DELIM_START_LEN));
            replacement.clear ();
            if (shadow_env)
                replacement = props.getProperty (key);
#ifdef HAVE_GETENV
            if (! shadow_env || (! empty_vars && replacement.empty ()))
            {
                char const * env_var
                    = getenv(DCMTK_LOG4CPLUS_TSTRING_TO_STRING(key).c_str());
                if (env_var)
                    replacement = DCMTK_LOG4CPLUS_STRING_TO_TSTRING (env_var);
            }
#endif

            if (empty_vars || ! replacement.empty ())
            {
                // Substitute the variable with its value in place.
                pattern.replace (var_start, var_end - var_start + DELIM_STOP_LEN,
                    replacement);
                changed = true;
                if (rec_exp)
                    // Retry expansion on the same spot.
                    continue;
                else
                    // Move beyond the just substitued part.
                    i = var_start + replacement.size ();
            }
            else
                // Nothing has been subtituted, just move beyond the
                // unexpanded variable.
                i = var_end + DELIM_STOP_LEN;
        } // end while loop

    } // end substVars()

} // namespace



//////////////////////////////////////////////////////////////////////////////
// PropertyConfigurator ctor and dtor
//////////////////////////////////////////////////////////////////////////////

PropertyConfigurator::PropertyConfigurator(const tstring& propertyFile,
    Hierarchy& h_, unsigned flags_)
    : h(h_)
    , propertyFilename(propertyFile)
    , properties(propertyFile)
    , flags (flags_)
{
    init();
}


PropertyConfigurator::PropertyConfigurator(const helpers::Properties& props,
    Hierarchy& h_, unsigned flags_)
    : h(h_)
    , propertyFilename( DCMTK_LOG4CPLUS_TEXT("UNAVAILABLE") )
    , properties( props )
    , flags (flags_)
{
    init();
}


PropertyConfigurator::PropertyConfigurator(tistream& propertyStream,
    Hierarchy& h_, unsigned flags_)
    : h(h_)
    , propertyFilename( DCMTK_LOG4CPLUS_TEXT("UNAVAILABLE") )
    , properties(propertyStream)
    , flags (flags_)
{
    init();
}


void
PropertyConfigurator::init()
{
    replaceEnvironVariables();
    properties = properties.getPropertySubset( DCMTK_LOG4CPLUS_TEXT("log4cplus.") );
}


PropertyConfigurator::~PropertyConfigurator()
{
}



//////////////////////////////////////////////////////////////////////////////
// PropertyConfigurator static methods
//////////////////////////////////////////////////////////////////////////////

void
PropertyConfigurator::doConfigure(const tstring& file, Hierarchy& h,
    unsigned flags)
{
    PropertyConfigurator tmp(file, h, flags);
    tmp.configure();
}



//////////////////////////////////////////////////////////////////////////////
// PropertyConfigurator public methods
//////////////////////////////////////////////////////////////////////////////

void
PropertyConfigurator::configure()
{
    // Configure log4cplus internals.
    tstring val = properties.getProperty (
        DCMTK_LOG4CPLUS_TEXT ("configDebug"), DCMTK_LOG4CPLUS_TEXT ("false"));
    getLogLog ().setInternalDebugging (
        helpers::toLower (val) == DCMTK_LOG4CPLUS_TEXT ("true"));

    initializeLog4cplus();
    configureAppenders();
    configureLoggers();
    configureAdditivity();

    // Erase the appenders so that we are not artificially keeping them "alive".
    appenders.clear ();
}


helpers::Properties const &
PropertyConfigurator::getProperties () const
{
    return properties;
}


tstring const &
PropertyConfigurator::getPropertyFilename () const
{
    return propertyFilename;
}


//////////////////////////////////////////////////////////////////////////////
// PropertyConfigurator protected methods
//////////////////////////////////////////////////////////////////////////////

void
PropertyConfigurator::reconfigure()
{
    properties = Properties(propertyFilename);
    init();
    configure();
}


void
PropertyConfigurator::replaceEnvironVariables()
{
    tstring val, subKey, subVal;
    bool const rec_exp
        = !! (flags & PropertyConfigurator::fRecursiveExpansion);
    bool changed;

    do
    {
        changed = false;
        OFList<tstring> keys = properties.propertyNames();
        for (OFListConstIterator(tstring) it = keys.begin();
            it != keys.end(); ++it)
        {
            tstring const & key = *it;
            val = properties.getProperty(key);

            subKey.clear ();
            if (substVars(subKey, key, properties, getLogLog(), flags))
            {
                properties.removeProperty(key);
                properties.setProperty(subKey, val);
                changed = true;
            }

            subVal.clear ();
            if (substVars(subVal, val, properties, getLogLog(), flags))
            {
                properties.setProperty(subKey, subVal);
                changed = true;
            }
        }
    }
    while (changed && rec_exp);
}



void
PropertyConfigurator::configureLoggers()
{
    if(properties.exists( DCMTK_LOG4CPLUS_TEXT("rootLogger") ))
    {
        Logger root = h.getRoot();
        configureLogger(root,
                        properties.getProperty(DCMTK_LOG4CPLUS_TEXT("rootLogger")));
    }

    Properties loggerProperties
        = properties.getPropertySubset(DCMTK_LOG4CPLUS_TEXT("logger."));
    OFList<tstring> loggers = loggerProperties.propertyNames();
    for(OFListIterator(tstring) it=loggers.begin(); it!=loggers.end();
        ++it)
    {
        Logger log = getLogger(*it);
        configureLogger(log, loggerProperties.getProperty(*it));
    }
}



void
PropertyConfigurator::configureLogger(Logger logger, const tstring& config)
{
    // Remove all spaces from config
    tstring configString;
//    remove_copy_if(config.begin(), config.end(),
//        string_append_iterator<tstring>(configString),
//        STD_NAMESPACE bind1st(STD_NAMESPACEequal_to<tchar>(), DCMTK_LOG4CPLUS_TEXT(' ')));
    for (size_t i = 0; i < config.length(); i++)
    {
        if (config[i] != ' ')
            configString += config[i];
    }

    // "Tokenize" configString
    OFList<tstring> tokens;
    tokenize(configString, ',', tokens);

    if(tokens.size() == 0) {
        getLogLog().error(
            DCMTK_LOG4CPLUS_TEXT("PropertyConfigurator::configureLogger()")
            DCMTK_LOG4CPLUS_TEXT("- Invalid config string(Logger = ")
            + logger.getName()
            + DCMTK_LOG4CPLUS_TEXT("): \"")
            + config
            + DCMTK_LOG4CPLUS_TEXT("\""));
        return;
    }

    // Set the loglevel
    tstring loglevel = *tokens.begin();
    if (loglevel != DCMTK_LOG4CPLUS_TEXT("INHERITED"))
        logger.setLogLevel( getLogLevelManager().fromString(loglevel) );
    else
        logger.setLogLevel (NOT_SET_LOG_LEVEL);

    // Remove all existing appenders first so that we do not duplicate output.
    logger.removeAllAppenders ();

    // Set the Appenders
    OFListIterator(tstring) it = tokens.begin();

    // The first entry is the log level name
    if (it != tokens.end())
        it++;
    for(; it != tokens.end(); it++)
    {
        AppenderMap::iterator appenderIt = appenders.find(*it);
        if (appenderIt == appenders.end())
        {
            getLogLog().error(
                DCMTK_LOG4CPLUS_TEXT("PropertyConfigurator::configureLogger()")
                DCMTK_LOG4CPLUS_TEXT("- Invalid appender: ")
                + *it);
            continue;
        }
        addAppender(logger, appenderIt->second);
    }
}



void
PropertyConfigurator::configureAppenders()
{
    Properties appenderProperties =
        properties.getPropertySubset(DCMTK_LOG4CPLUS_TEXT("appender."));
    OFList<tstring> appendersProps = appenderProperties.propertyNames();
    tstring factoryName;
    for(OFListIterator(tstring) it=appendersProps.begin();
        it != appendersProps.end(); ++it)
    {
        if( it->find( DCMTK_LOG4CPLUS_TEXT('.') ) == OFString_npos )
        {
            factoryName = appenderProperties.getProperty(*it);
            AppenderFactory* factory
                = getAppenderFactoryRegistry().get(factoryName);
            if (factory == 0)
            {
                tstring err =
                    DCMTK_LOG4CPLUS_TEXT("PropertyConfigurator::configureAppenders()")
                    DCMTK_LOG4CPLUS_TEXT("- Cannot find AppenderFactory: ");
                getLogLog().error(err + factoryName);
                continue;
            }

            Properties my_properties
                = appenderProperties.getPropertySubset((*it)
                    + DCMTK_LOG4CPLUS_TEXT("."));
            try
            {
                tstring error;
                SharedAppenderPtr appender = factory->createObject(my_properties, error);
                if (appender.get() == 0)
                {
                    tstring err =
                        DCMTK_LOG4CPLUS_TEXT("PropertyConfigurator::")
                        DCMTK_LOG4CPLUS_TEXT("configureAppenders()")
                        DCMTK_LOG4CPLUS_TEXT("- Failed to create appender: ");
                    getLogLog().error(err + *it + " " + error);
                }
                else
                {
                    appender->setName(*it);
                    appenders[*it] = appender;
                }
            }
            catch(...)
            {
                tstring err =
                    DCMTK_LOG4CPLUS_TEXT("PropertyConfigurator::")
                    DCMTK_LOG4CPLUS_TEXT("configureAppenders()")
                    DCMTK_LOG4CPLUS_TEXT("- Exception caught while creating Appender");
                getLogLog().error(err);
            }
        }
    } // end for loop
}


void
PropertyConfigurator::configureAdditivity()
{
    Properties additivityProperties =
        properties.getPropertySubset(DCMTK_LOG4CPLUS_TEXT("additivity."));
    OFList<tstring> additivitysProps = additivityProperties.propertyNames();

    tstring actualValue;
    tstring value;

    for(OFListConstIterator(tstring) it = additivitysProps.begin();
        it != additivitysProps.end(); ++it)
    {
        Logger logger = getLogger(*it);
        actualValue = additivityProperties.getProperty(*it);
        value = toLower(actualValue);

        if(value == DCMTK_LOG4CPLUS_TEXT("true"))
            logger.setAdditivity(true);
        else if(value == DCMTK_LOG4CPLUS_TEXT("false"))
            logger.setAdditivity(false);
        else
            getLogLog().warn(  DCMTK_LOG4CPLUS_TEXT("Invalid Additivity value: \"")
                             + actualValue
                             + DCMTK_LOG4CPLUS_TEXT("\""));
    }
}



Logger
PropertyConfigurator::getLogger(const tstring& name)
{
    return h.getInstance(name);
}


void
PropertyConfigurator::addAppender(Logger &logger, SharedAppenderPtr& appender)
{
    logger.addAppender(appender);
}



//////////////////////////////////////////////////////////////////////////////
// BasicConfigurator ctor and dtor
//////////////////////////////////////////////////////////////////////////////

BasicConfigurator::BasicConfigurator(Hierarchy& h_)
    : PropertyConfigurator( DCMTK_LOG4CPLUS_TEXT(""), h_ )
{
    properties.setProperty(DCMTK_LOG4CPLUS_TEXT("rootLogger"),
                           DCMTK_LOG4CPLUS_TEXT("DEBUG, STDOUT"));
    properties.setProperty(DCMTK_LOG4CPLUS_TEXT("appender.STDOUT"),
                           DCMTK_LOG4CPLUS_TEXT("log4cplus::ConsoleAppender"));
}




BasicConfigurator::~BasicConfigurator()
{
}


//////////////////////////////////////////////////////////////////////////////
// BasicConfigurator static methods
//////////////////////////////////////////////////////////////////////////////

void
BasicConfigurator::doConfigure(Hierarchy& h)
{
    BasicConfigurator tmp(h);
    tmp.configure();
}


#if !defined(DCMTK_LOG4CPLUS_SINGLE_THREADED)

//////////////////////////////////////////////////////////////////////////////
// ConfigurationWatchDogThread implementation
//////////////////////////////////////////////////////////////////////////////

class ConfigurationWatchDogThread
    : public thread::AbstractThread,
      public PropertyConfigurator
{
public:
    ConfigurationWatchDogThread(const tstring& file, unsigned int millis)
        : PropertyConfigurator(file)
        , waitMillis(millis < 1000 ? 1000 : millis)
        , shouldTerminate(false)
        , lock(NULL)
    { }

    virtual ~ConfigurationWatchDogThread ()
    { }

    void terminate ()
    {
        shouldTerminate.signal ();
        join ();
    }

protected:
    virtual void run();
    virtual Logger getLogger(const tstring& name);
    virtual void addAppender(Logger &logger, SharedAppenderPtr& appender);

    bool checkForFileModification(Time & mtime);
    void updateLastModTime(Time const & mtime);

private:
    unsigned int const waitMillis;
    thread::ManualResetEvent shouldTerminate;
    Time lastModTime;
    HierarchyLocker* lock;
};


void
ConfigurationWatchDogThread::run()
{
    Time mtime;

    // Initialize last modification time.
    checkForFileModification (mtime);
    updateLastModTime (mtime);

    while (! shouldTerminate.timed_wait (waitMillis))
    {
        bool modified = checkForFileModification(mtime);
        if(modified) {
            // Lock the Hierarchy
            HierarchyLocker theLock(h);
            lock = &theLock;

            // reconfigure the Hierarchy
            theLock.resetConfiguration();
            reconfigure();
            updateLastModTime(mtime);

            // release the lock
            lock = NULL;
        }
    }
}


Logger
ConfigurationWatchDogThread::getLogger(const tstring& name)
{
    if(lock)
        return lock->getInstance(name);
    else
        return PropertyConfigurator::getLogger(name);
}


void
ConfigurationWatchDogThread::addAppender(Logger& logger,
                                         SharedAppenderPtr& appender)
{
    if(lock)
        lock->addAppender(logger, appender);
    else
        PropertyConfigurator::addAppender(logger, appender);
}


bool
ConfigurationWatchDogThread::checkForFileModification(Time & mtime)
{
    struct stat fileStatus;
    if(::stat(DCMTK_LOG4CPLUS_TSTRING_TO_STRING(propertyFilename).c_str(),
            &fileStatus) == -1)
        return false;  // stat() returned error, so the file must not exist
    mtime = Time (fileStatus.st_mtime);
    bool modified = mtime != lastModTime;

#if defined(DCMTK_LOG4CPLUS_HAVE_LSTAT)
    if(!modified && S_ISLNK(fileStatus.st_mode))
    {
        ::lstat(DCMTK_LOG4CPLUS_TSTRING_TO_STRING(propertyFilename).c_str(),
            &fileStatus);
        mtime = Time (fileStatus.st_mtime);
        modified = mtime != lastModTime;
    }
#endif

    return modified;
}


void
ConfigurationWatchDogThread::updateLastModTime(Time const & mtime)
{
    lastModTime = mtime;
}



//////////////////////////////////////////////////////////////////////////////
// PropertyConfiguratorWatchDog ctor and dtor
//////////////////////////////////////////////////////////////////////////////

ConfigureAndWatchThread::ConfigureAndWatchThread(const tstring& file,
    unsigned int millis)
    : watchDogThread(0)
{
    watchDogThread = new ConfigurationWatchDogThread(file, millis);
    watchDogThread->addReference ();
    watchDogThread->configure();
    watchDogThread->start();
}


ConfigureAndWatchThread::~ConfigureAndWatchThread()
{
    if (watchDogThread)
    {
        watchDogThread->terminate();
        watchDogThread->removeReference ();
    }
}


#endif


} // namespace log4cplus

} // namespace dcmtk
