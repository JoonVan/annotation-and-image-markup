/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

//#include <cassert>
#define INCLUDE_CASSERT
//#include <exception>
//#include <stdexcept>
//#include <errno.h>
#define INCLUDE_CERRNO
#define INCLUDE_CSTDLIB

#include "dcmtk/ofstd/ofstdinc.h"

#include "dcmtk/oflog/config.h"

#ifndef DCMTK_LOG4CPLUS_SINGLE_THREADED

#if defined(DCMTK_LOG4CPLUS_USE_PTHREADS)
#  include <sched.h>
#  include <signal.h>
#elif defined (DCMTK_LOG4CPLUS_USE_WIN32_THREADS) && ! defined (_WIN32_WCE)
#  include <process.h>
#endif

#include "dcmtk/oflog/helpers/threads.h"
#include "dcmtk/oflog/streams.h"
#include "dcmtk/oflog/ndc.h"
#include "dcmtk/oflog/helpers/loglog.h"
#include "dcmtk/oflog/helpers/strhelp.h"
#include "dcmtk/oflog/helpers/timehelp.h"
#include "dcmtk/oflog/helpers/syncprims.h"


namespace dcmtk { namespace log4cplus { namespace thread {


struct ThreadStart
{
#  ifdef DCMTK_LOG4CPLUS_USE_PTHREADS
static void* threadStartFuncWorker(void *);
#  elif defined(DCMTK_LOG4CPLUS_USE_WIN32_THREADS)
static unsigned threadStartFuncWorker(void *);
#  endif
};


} } } // namespace dcmtk { namespace log4cplus { namespace thread {


namespace
{

#  ifdef DCMTK_LOG4CPLUS_USE_PTHREADS
extern "C" void * threadStartFunc(void * param)
#  elif defined(DCMTK_LOG4CPLUS_USE_WIN32_THREADS)
static unsigned WINAPI threadStartFunc(void * param)
#  endif
{
    return dcmtk::log4cplus::thread::ThreadStart::threadStartFuncWorker (param);
}

} // namespace


namespace dcmtk { namespace log4cplus { namespace thread {


///////////////////////////////////////////////////////////////////////////////
// public methods
///////////////////////////////////////////////////////////////////////////////

DCMTK_LOG4CPLUS_MUTEX_PTR_DECLARE
createNewMutex()
{
#if defined(DCMTK_LOG4CPLUS_USE_PTHREADS)
    ::pthread_mutex_t* m = new ::pthread_mutex_t;
    ::pthread_mutex_init(m, NULL);
#elif defined(DCMTK_LOG4CPLUS_USE_WIN32_THREADS)
    ::CRITICAL_SECTION* m = new ::CRITICAL_SECTION;
    ::InitializeCriticalSection(m);
#endif
    return m;
}


void
deleteMutex(DCMTK_LOG4CPLUS_MUTEX_PTR_DECLARE m)
{
#if defined(DCMTK_LOG4CPLUS_USE_PTHREADS)
    ::pthread_mutex_destroy(m);
#elif defined(DCMTK_LOG4CPLUS_USE_WIN32_THREADS)
    ::DeleteCriticalSection(m);
#endif
    delete m;
}



#if defined(DCMTK_LOG4CPLUS_USE_PTHREADS)
pthread_key_t*
createPthreadKey(void (*cleanupfunc)(void *))
{
    ::pthread_key_t* key = new ::pthread_key_t;
    ::pthread_key_create(key, cleanupfunc);
    return key;
}
#endif


#ifndef DCMTK_LOG4CPLUS_SINGLE_THREADED
void
blockAllSignals()
{
#if defined (DCMTK_LOG4CPLUS_USE_PTHREADS)
    // Block all signals.
    ::sigset_t signal_set;
#if defined (_DARWIN_C_SOURCE) || defined (__OpenBSD__)
    sigfillset (&signal_set);
#else
    ::sigfillset (&signal_set);
#endif // _DARWIN_C_SOURCE || __OpenBSD__
    ::pthread_sigmask (SIG_BLOCK, &signal_set, 0);
#endif
}
#endif // DCMTK_LOG4CPLUS_SINGLE_THREADED


tstring
getCurrentThreadName()
{
    tostringstream tmp;
    tmp << DCMTK_LOG4CPLUS_GET_CURRENT_THREAD;
    OFSTRINGSTREAM_GETOFSTRING(tmp, str)
    return str;
}


#if defined(DCMTK_LOG4CPLUS_USE_PTHREADS)
void*
ThreadStart::threadStartFuncWorker(void * arg)
#elif defined(DCMTK_LOG4CPLUS_USE_WIN32_THREADS)
unsigned
ThreadStart::threadStartFuncWorker(void * arg)
#endif
{
    blockAllSignals ();
    helpers::SharedObjectPtr<helpers::LogLog> loglog
        = helpers::LogLog::getLogLog();
    if (! arg)
        loglog->error(DCMTK_LOG4CPLUS_TEXT("threadStartFunc()- arg is NULL"));
    else
    {
        AbstractThread * ptr = OFstatic_cast(AbstractThread*, arg);
        AbstractThreadPtr thread(ptr);

        // Decrease reference count increased by AbstractThread::start().
        ptr->removeReference ();

        try
        {
            thread->run();
        }
        catch(...)
        {
            loglog->warn(DCMTK_LOG4CPLUS_TEXT("threadStartFunc()- run() terminated with an exception."));
        }
        thread->running = false;
        getNDC().remove();
    }

    return 0;
}



///////////////////////////////////////////////////////////////////////////////
// AbstractThread ctor and dtor
///////////////////////////////////////////////////////////////////////////////

AbstractThread::AbstractThread()
    : running(false)
#if defined(DCMTK_LOG4CPLUS_USE_WIN32_THREADS)
    , handle (INVALID_HANDLE_VALUE)
#endif
{
}



AbstractThread::~AbstractThread()
{
#if defined(DCMTK_LOG4CPLUS_USE_WIN32_THREADS)
    if (handle != INVALID_HANDLE_VALUE)
        ::CloseHandle (handle);
#endif
}



///////////////////////////////////////////////////////////////////////////////
// AbstractThread public methods
///////////////////////////////////////////////////////////////////////////////

void
AbstractThread::start()
{
    running = true;

    // Increase reference count here. It will be lowered by the running
    // thread itself.
    addReference ();

#if defined(DCMTK_LOG4CPLUS_USE_PTHREADS)
    if (::pthread_create(&handle, NULL, threadStartFunc, this) )
    {
        removeReference ();
        helpers::SharedObjectPtr<helpers::LogLog> loglog
            = helpers::LogLog::getLogLog();
        loglog->error( DCMTK_LOG4CPLUS_TEXT("Thread creation was not successful") );
        //throw STD_NAMESPACE runtime_error("Thread creation was not successful");
        abort();
    }
#elif defined(DCMTK_LOG4CPLUS_USE_WIN32_THREADS)
    if (handle != INVALID_HANDLE_VALUE)
    {
        ::CloseHandle (handle);
        handle = INVALID_HANDLE_VALUE;
    }
    HANDLE h;
#if defined (_WIN32_WCE)
    h = ::CreateThread  (0, 0, threadStartFunc, this, 0, &thread_id);
#else
    h = OFreinterpret_cast(HANDLE,
        ::_beginthreadex (0, 0, threadStartFunc, this, 0, &thread_id));
#endif
    if (! h)
    {
        removeReference ();
        helpers::SharedObjectPtr<helpers::LogLog> loglog
            = helpers::LogLog::getLogLog();
        loglog->error( DCMTK_LOG4CPLUS_TEXT("Thread creation was not successful") );
        //throw STD_NAMESPACE runtime_error("Thread creation was not successful");
        abort();
    }
    handle = h;
#endif
}


DCMTK_LOG4CPLUS_THREAD_KEY_TYPE
AbstractThread::getThreadId () const
{
#if defined(DCMTK_LOG4CPLUS_USE_PTHREADS)
    return handle;
#elif defined(DCMTK_LOG4CPLUS_USE_WIN32_THREADS)
    return thread_id;
#endif
}


DCMTK_LOG4CPLUS_THREAD_HANDLE_TYPE
AbstractThread::getThreadHandle () const
{
    return handle;
}


void
AbstractThread::join () const
{
#if defined(DCMTK_LOG4CPLUS_USE_PTHREADS)
    ::pthread_join (handle, 0);
#elif defined(DCMTK_LOG4CPLUS_USE_WIN32_THREADS)
    ::WaitForSingleObject (handle, INFINITE);
#endif
}


} } } // namespace dcmtk { namespace log4cplus { namespace thread {

#endif // DCMTK_LOG4CPLUS_SINGLE_THREADED