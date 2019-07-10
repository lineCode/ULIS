/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Thread.Pool.cpp
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once

#include "ULIS/Thread/ULIS.Thread.Pool.h"

namespace ULIS {
/////////////////////////////////////////////////////
// FThreadPool
//--------------------------------------------------------------------------------------
//----------------------------------------------------------- Construction / Destruction
FThreadPool::FThreadPool(unsigned int n)
    : busy( 0 )
    , stop( false )
    , processed( 0 )
{
    for( unsigned int i = 0; i < n; ++i )
        workers.emplace_back( std::bind( &FThreadPool::ThreadProcess, this ) );
}

FThreadPool::~FThreadPool()
{
    // set stop-condition
    std::unique_lock< std::mutex > latch( queue_mutex );
    stop = true;
    cv_task.notify_all();
    latch.unlock();

    // all threads terminate, then we're done.
    for( auto& t : workers )
        t.join();
}

//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------- Public API
template<class F>
void FThreadPool::ScheduleJob( F&& f )
{
    std::unique_lock< std::mutex > lock( queue_mutex );
    tasks.emplace_back( std::forward< F >( f ) );
    cv_task.notify_one();
}

template<class F, typename ... Args >
void FThreadPool::ScheduleJob( F&& f, Args&& ... args )
{
    std::unique_lock< std::mutex > lock( queue_mutex );
    tasks.emplace_back( std::bind( std::forward< F >( f ), std::forward< Args >( args ) ... ) );
    cv_task.notify_one();
}


void FThreadPool::WaitForCompletion()
{
    std::unique_lock< std::mutex > lock( queue_mutex );
    cv_finished.wait( lock, [ this ](){ return tasks.empty() && ( busy == 0 ); } );
}


void FThreadPool::SetNumWorkers( unsigned int iValue )
{
    WaitForCompletion();
    workers.clear();
    for( unsigned int i = 0; i < iValue; ++i )
        workers.emplace_back( std::bind( &FThreadPool::ThreadProcess, this ) );
}


//--------------------------------------------------------------------------------------
//-------------------------------------------------------------------------- Private API
void FThreadPool::ThreadProcess()
{
    while( true )
    {
        std::unique_lock< std::mutex > latch( queue_mutex );
        cv_task.wait( latch, [ this ](){ return stop || !tasks.empty(); } );
        if( !tasks.empty() )
        {
            // got work. set busy.
            ++busy;

            // pull from queue
            auto fn = tasks.front();
            tasks.pop_front();

            // release lock. run async
            latch.unlock();

            // run function outside context
            fn();
            ++processed;

            latch.lock();
            --busy;
            cv_finished.notify_one();
        }
        else if( stop )
        {
            break;
        }
    }
}


} // namespace ULIS
