/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "dcmtk/oflog/hierarchy.h"
#include "dcmtk/oflog/helpers/loglog.h"
#include "dcmtk/oflog/spi/logimpl.h"
#include "dcmtk/oflog/spi/rootlog.h"
//#include <utility>

#define INCLUDE_CSTDLIB
#include "dcmtk/ofstd/ofstdinc.h"

using namespace dcmtk::log4cplus;
using namespace dcmtk::log4cplus::helpers;


//////////////////////////////////////////////////////////////////////////////
// File "Local" methods
//////////////////////////////////////////////////////////////////////////////

namespace
{

static
bool startsWith(tstring const & teststr, tstring const & substr)
{
    bool val = false;
    tstring::size_type const len = substr.length();
    if (teststr.length() > len)
        val = teststr.compare (0, len, substr) == 0;

    return val;
}

}


//////////////////////////////////////////////////////////////////////////////
// dcmtk::log4cplus::Hierarchy static declarations
//////////////////////////////////////////////////////////////////////////////

const LogLevel Hierarchy::DISABLE_OFF = -1;
const LogLevel Hierarchy::DISABLE_OVERRIDE = -2;



//////////////////////////////////////////////////////////////////////////////
// dcmtk::log4cplus::Hierarchy ctor and dtor
//////////////////////////////////////////////////////////////////////////////

Hierarchy::Hierarchy()
  : hashtable_mutex(DCMTK_LOG4CPLUS_MUTEX_CREATE),
    defaultFactory(new DefaultLoggerFactory()),
    root(NULL),
    disableValue(DISABLE_OFF),  // Don't disable any LogLevel level by default.
    emittedNoAppenderWarning(false),
    emittedNoResourceBundleWarning(false)
{
    root = Logger( new spi::RootLogger(*this, DEBUG_LOG_LEVEL) );
}


Hierarchy::~Hierarchy()
{
    shutdown();
    DCMTK_LOG4CPLUS_MUTEX_FREE( hashtable_mutex );
}



//////////////////////////////////////////////////////////////////////////////
// dcmtk::log4cplus::Hierarchy public methods
//////////////////////////////////////////////////////////////////////////////

void
Hierarchy::clear()
{
    DCMTK_LOG4CPLUS_BEGIN_SYNCHRONIZE_ON_MUTEX( hashtable_mutex )
        provisionNodes.erase(provisionNodes.begin(), provisionNodes.end());
        loggerPtrs.erase(loggerPtrs.begin(), loggerPtrs.end());
    DCMTK_LOG4CPLUS_END_SYNCHRONIZE_ON_MUTEX;
}


bool
Hierarchy::exists(const tstring& name)
{
    DCMTK_LOG4CPLUS_BEGIN_SYNCHRONIZE_ON_MUTEX( hashtable_mutex )
        LoggerMap::iterator it = loggerPtrs.find(name);
        return it != loggerPtrs.end();
    DCMTK_LOG4CPLUS_END_SYNCHRONIZE_ON_MUTEX;
}


void
Hierarchy::disable(const tstring& loglevelStr)
{
    if(disableValue != DISABLE_OVERRIDE) {
        disableValue = getLogLevelManager().fromString(loglevelStr);
    }
}


void
Hierarchy::disable(LogLevel ll)
{
    if(disableValue != DISABLE_OVERRIDE) {
        disableValue = ll;
    }
}


void
Hierarchy::disableAll()
{
    disable(FATAL_LOG_LEVEL);
}


void
Hierarchy::disableDebug()
{
    disable(DEBUG_LOG_LEVEL);
}


void
Hierarchy::disableInfo()
{
    disable(INFO_LOG_LEVEL);
}


void
Hierarchy::enableAll()
{
    disableValue = DISABLE_OFF;
}


Logger
Hierarchy::getInstance(const tstring& name)
{
    return getInstance(name, *defaultFactory);
}


Logger
Hierarchy::getInstance(const tstring& name, spi::LoggerFactory& factory)
{
    DCMTK_LOG4CPLUS_BEGIN_SYNCHRONIZE_ON_MUTEX( hashtable_mutex )
        return getInstanceImpl(name, factory);
    DCMTK_LOG4CPLUS_END_SYNCHRONIZE_ON_MUTEX;
}


LoggerList
Hierarchy::getCurrentLoggers()
{
    LoggerList ret;

    DCMTK_LOG4CPLUS_BEGIN_SYNCHRONIZE_ON_MUTEX( hashtable_mutex )
        initializeLoggerList(ret);
    DCMTK_LOG4CPLUS_END_SYNCHRONIZE_ON_MUTEX;

    return ret;
}


bool
Hierarchy::isDisabled(int level)
{
    return disableValue >= level;
}


Logger
Hierarchy::getRoot() const
{
    return root;
}


void
Hierarchy::resetConfiguration()
{
    getRoot().setLogLevel(DEBUG_LOG_LEVEL);
    disableValue = DISABLE_OFF;

    shutdown();

    LoggerList loggers = getCurrentLoggers();
    LoggerListIterator it = loggers.begin();
    while(it != loggers.end()) {
        (*it).setLogLevel(NOT_SET_LOG_LEVEL);
        (*it).setAdditivity(true);
        ++it;
    }

}


void
Hierarchy::setLoggerFactory(OFauto_ptr<spi::LoggerFactory> factory)
{
    defaultFactory = factory;
}


void
Hierarchy::shutdown()
{
    LoggerList loggers = getCurrentLoggers();

    // begin by closing nested appenders
    // then, remove all appenders
    root.closeNestedAppenders();
    root.removeAllAppenders();

    // repeat
    LoggerListIterator it = loggers.begin();
    while(it != loggers.end()) {
        (*it).closeNestedAppenders();
        (*it).removeAllAppenders();
        ++it;
    }
}



//////////////////////////////////////////////////////////////////////////////
// dcmtk::log4cplus::Hierarchy private methods
//////////////////////////////////////////////////////////////////////////////

Logger
Hierarchy::getInstanceImpl(const tstring& name, spi::LoggerFactory& factory)
{
    LoggerMap::iterator it = loggerPtrs.find(name);
     if(it != loggerPtrs.end()) {
         return (*it).second;
     }
     else {
         // Need to create a new logger
         Logger logger = factory.makeNewLoggerInstance(name, *this);
         bool inserted = loggerPtrs.insert(OFMake_pair(name, logger)).second;
         if(!inserted) {
             getLogLog().error(DCMTK_LOG4CPLUS_TEXT("Hierarchy::getInstanceImpl()- Insert failed"));
             //throw STD_NAMESPACE runtime_error("Hierarchy::getInstanceImpl()- Insert failed");
             abort();
         }

         ProvisionNodeMap::iterator it2 = provisionNodes.find(name);
         if(it2 != provisionNodes.end()) {
             updateChildren(it2->second, logger);
             bool deleted = (provisionNodes.erase(name) > 0);
             if(!deleted) {
                 getLogLog().error(DCMTK_LOG4CPLUS_TEXT("Hierarchy::getInstanceImpl()- Delete failed"));
                 //throw STD_NAMESPACE runtime_error("Hierarchy::getInstanceImpl()- Delete failed");
                 abort();
             }
         }
         updateParents(logger);

         return logger;
     }
}


void
Hierarchy::initializeLoggerList(LoggerList& list) const
{
    for(LoggerMap::const_iterator it=loggerPtrs.begin();
        it!= loggerPtrs.end();
        ++it)
    {
        list.push_back((*it).second);
    }
}


void
Hierarchy::updateParents(Logger logger)
{
    tstring name = logger.getName();
    size_t length = name.length();
    bool parentFound = false;

    // if name = "w.x.y.z", loop thourgh "w.x.y", "w.x" and "w", but not "w.x.y.z"
    for(size_t i=name.find_last_of(DCMTK_LOG4CPLUS_TEXT('.'), length-1);
        i != OFString_npos;
        i = name.find_last_of(DCMTK_LOG4CPLUS_TEXT('.'), i-1))
    {
        tstring substr = name.substr(0, i);

        LoggerMap::iterator it = loggerPtrs.find(substr);
        if(it != loggerPtrs.end()) {
            parentFound = true;
            logger.value->parent = it->second.value;
            break;  // no need to update the ancestors of the closest ancestor
        }
        else {
            ProvisionNodeMap::iterator it2 = provisionNodes.find(substr);
            if(it2 != provisionNodes.end()) {
                it2->second.push_back(logger);
            }
            else {
                ProvisionNode node;
                node.push_back(logger);
                OFPair<ProvisionNodeMap::iterator, bool> tmp =
                    provisionNodes.insert(OFMake_pair(substr, node));
                //bool inserted = provisionNodes.insert(STD_NAMESPACE make_pair(substr, node)).second;
                if(!tmp.second) {
                    getLogLog().error(DCMTK_LOG4CPLUS_TEXT("Hierarchy::updateParents()- Insert failed"));
                    //throw STD_NAMESPACE runtime_error("Hierarchy::updateParents()- Insert failed");
                    abort();
                }
            }
        } // end if Logger found
    } // end for loop

    if(!parentFound) {
        logger.value->parent = root.value;
    }
}


void
Hierarchy::updateChildren(ProvisionNode& pn, Logger logger)
{

    for(ProvisionNodeIterator it=pn.begin(); it!=pn.end(); ++it) {
        Logger& c = *it;
        // Unless this child already points to a correct (lower) parent,
        // make logger.parent point to c.parent and c.parent to logger.
        if( !startsWith(c.value->parent->getName(), logger.getName()) ) {
            logger.value->parent = c.value->parent;
            c.value->parent = logger.value;
        }
    }
}
