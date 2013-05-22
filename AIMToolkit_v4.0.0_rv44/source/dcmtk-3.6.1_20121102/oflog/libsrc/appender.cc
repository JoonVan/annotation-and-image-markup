/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "dcmtk/oflog/appender.h"
#include "dcmtk/oflog/layout.h"
#include "dcmtk/oflog/helpers/loglog.h"
#include "dcmtk/oflog/helpers/pointer.h"
#include "dcmtk/oflog/helpers/strhelp.h"
#include "dcmtk/oflog/spi/factory.h"
#include "dcmtk/oflog/spi/logevent.h"

using namespace dcmtk::log4cplus;
using namespace dcmtk::log4cplus::helpers;
using namespace dcmtk::log4cplus::spi;



///////////////////////////////////////////////////////////////////////////////
// dcmtk::log4cplus::ErrorHandler dtor
///////////////////////////////////////////////////////////////////////////////

ErrorHandler::~ErrorHandler()
{
}



///////////////////////////////////////////////////////////////////////////////
// dcmtk::log4cplus::OnlyOnceErrorHandler public methods
///////////////////////////////////////////////////////////////////////////////

void
OnlyOnceErrorHandler::error(const tstring& err)
{
    if(firstTime) {
        getLogLog().error(err);
        firstTime = false;
    }
}



void
OnlyOnceErrorHandler::reset()
{
    firstTime = true;
}



///////////////////////////////////////////////////////////////////////////////
// dcmtk::log4cplus::Appender ctors
///////////////////////////////////////////////////////////////////////////////

Appender::Appender()
 : layout(new SimpleLayout()),
   name( DCMTK_LOG4CPLUS_TEXT("") ),
   threshold(NOT_SET_LOG_LEVEL),
   errorHandler(new OnlyOnceErrorHandler()),
   closed(false)
{
}



Appender::Appender(const helpers::Properties properties)
 : layout(new SimpleLayout()),
   name( DCMTK_LOG4CPLUS_TEXT("") ),
   threshold(NOT_SET_LOG_LEVEL),
   errorHandler(new OnlyOnceErrorHandler()),
   closed(false)
{
    if(properties.exists( DCMTK_LOG4CPLUS_TEXT("layout") )) {
        tstring factoryName = properties.getProperty( DCMTK_LOG4CPLUS_TEXT("layout") );
        LayoutFactory* factory = getLayoutFactoryRegistry().get(factoryName);
        if(factory == 0) {
            getLogLog().error(  DCMTK_LOG4CPLUS_TEXT("Cannot find LayoutFactory: \"")
                              + factoryName
                              + DCMTK_LOG4CPLUS_TEXT("\"") );
            return;
        }

        Properties layoutProperties =
                properties.getPropertySubset( DCMTK_LOG4CPLUS_TEXT("layout.") );
        try {
            tstring error;
            OFauto_ptr<Layout> newLayout(factory->createObject(layoutProperties, error));
            if(newLayout.get() == 0) {
                getLogLog().error(  DCMTK_LOG4CPLUS_TEXT("Failed to create appender: ")
                                  + factoryName + " " + error);
            }
            else {
                layout = newLayout;
            }
        }
        catch(...) {
            getLogLog().error(  DCMTK_LOG4CPLUS_TEXT("Exception caught while creating Layout"));
            return;
        }

    }

    // Support for appender.Threshold in properties configuration file
    if(properties.exists(DCMTK_LOG4CPLUS_TEXT("Threshold"))) {
        tstring tmp = properties.getProperty(DCMTK_LOG4CPLUS_TEXT("Threshold"));
        tmp = toUpper(tmp);
        threshold = getLogLevelManager().fromString(tmp);
    }

    // Configure the filters
    Properties filterProps = properties.getPropertySubset( DCMTK_LOG4CPLUS_TEXT("filters.") );
    int filterCount = 0;
    FilterPtr filterChain;
    tstring filterName, factoryName;
    while( filterProps.exists(filterName = convertIntegerToString(++filterCount)) ) {
        factoryName = filterProps.getProperty(filterName);
        FilterFactory* factory = getFilterFactoryRegistry().get(factoryName);

        if(factory == 0) {
            tstring err = DCMTK_LOG4CPLUS_TEXT("Appender::ctor()- Cannot find FilterFactory: ");
            getLogLog().error(err + factoryName);
            continue;
        }
        tstring error;
        FilterPtr tmp_filter = factory->createObject
                      (filterProps.getPropertySubset(filterName + DCMTK_LOG4CPLUS_TEXT(".")), error);
        if(tmp_filter.get() == 0) {
            tstring err = DCMTK_LOG4CPLUS_TEXT("Appender::ctor()- Failed to create filter: ");
            getLogLog().error(err + filterName + " " + error);
        }
        if(filterChain.get() == 0) {
            filterChain = tmp_filter;
        }
        else {
            filterChain->appendFilter(tmp_filter);
        }
    }
    setFilter(filterChain);
}


Appender::~Appender()
{ }



///////////////////////////////////////////////////////////////////////////////
// dcmtk::log4cplus::Appender public methods
///////////////////////////////////////////////////////////////////////////////

void
Appender::destructorImpl()
{
    getLogLog().debug(  DCMTK_LOG4CPLUS_TEXT("Destroying appender named [")
                      + name
                      + DCMTK_LOG4CPLUS_TEXT("]."));

    // An appender might be closed then destroyed. There is no
    // point in closing twice.
    if(closed) {
        return;
    }

    close();
    closed = true;
}



void
Appender::doAppend(const InternalLoggingEvent& event)
{
    DCMTK_LOG4CPLUS_BEGIN_SYNCHRONIZE_ON_MUTEX( access_mutex )
        if(closed) {
            getLogLog().error(  DCMTK_LOG4CPLUS_TEXT("Attempted to append to closed appender named [")
                              + name
                              + DCMTK_LOG4CPLUS_TEXT("]."));
            return;
        }

        if(!isAsSevereAsThreshold(event.getLogLevel())) {
            return;
        }

        if(checkFilter(filter.get(), event) == DENY) {
            return;
        }

        append(event);
    DCMTK_LOG4CPLUS_END_SYNCHRONIZE_ON_MUTEX;
}



tstring
Appender::getName()
{
    return name;
}



void
Appender::setName(const tstring& name_)
{
    this->name = name_;
}


ErrorHandler*
Appender::getErrorHandler()
{
    return errorHandler.get();
}



void
Appender::setErrorHandler(OFauto_ptr<ErrorHandler> eh)
{
    if(eh.get() == NULL) {
        // We do not throw exception here since the cause is probably a
        // bad config file.
        getLogLog().warn(DCMTK_LOG4CPLUS_TEXT("You have tried to set a null error-handler."));
        return;
    }
    DCMTK_LOG4CPLUS_BEGIN_SYNCHRONIZE_ON_MUTEX( access_mutex )
        this->errorHandler = eh;
    DCMTK_LOG4CPLUS_END_SYNCHRONIZE_ON_MUTEX;
}



void
Appender::setLayout(OFauto_ptr<Layout> lo)
{
    DCMTK_LOG4CPLUS_BEGIN_SYNCHRONIZE_ON_MUTEX( access_mutex )
        this->layout = lo;
    DCMTK_LOG4CPLUS_END_SYNCHRONIZE_ON_MUTEX;
}



Layout*
Appender::getLayout()
{
    return layout.get();
}


