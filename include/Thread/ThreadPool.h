// Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         ThreadPool.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the FThreadPool class.
* @copyright    Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Base/Core.h"
#include "Base/Perf.h"
#include <iostream>
#include <deque>
#include <functional>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <random>
#include <atomic>

ULIS2_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
// FThreadPool
class ULIS2_API FThreadPool
{
public:
    // Construction / Destruction
    FThreadPool( unsigned int iCount = std::thread::hardware_concurrency() );
    ~FThreadPool();

public:
    // Public API
    template<class F>
    void ScheduleJob( F&& f )
    {
        std::unique_lock< std::mutex > lock( queue_mutex );
        tasks.push_back( std::forward< F >( f ) );
        cv_task.notify_one();
    }

    template<class F, typename ... Args >
    void ScheduleJob( F&& f, Args&& ... args )
    {
        std::unique_lock< std::mutex > lock( queue_mutex );
        tasks.push_back( std::bind( std::forward< F >( f ), args ... ) );
        cv_task.notify_one();
    }


    void            WaitForCompletion();
    unsigned int    GetProcessed() const { return  processed; }
    unsigned int    GetNumWorkers() const { return  unsigned int( workers.size() ); }
    void            SetNumWorkers( unsigned int );
    unsigned int    GetMaxWorkers() const { return  std::thread::hardware_concurrency(); }

private:
    // Private API
    void ThreadProcess();

private:
    // Private Data
    unsigned int                        busy;
    bool                                stop;
    std::atomic_uint                    processed;
    std::vector< std::thread >          workers;
    std::deque< std::function<void()> > tasks;
    std::mutex                          queue_mutex;
    std::condition_variable             cv_task;
    std::condition_variable             cv_finished;
};

ULIS2_NAMESPACE_END

