/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Thread.Pool.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once

#include <iostream>
#include <deque>
#include <functional>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <random>
#include <atomic>

namespace ULIS {
/////////////////////////////////////////////////////
// FThreadPool
class FThreadPool
{
public:
    // Construction / Destruction
    FThreadPool( unsigned int iCount = std::thread::hardware_concurrency() );
    ~FThreadPool();

public:
    // Public API
    template<class F>                       void  ScheduleJob(F&& f);
    template<class F, typename ... Args >   void ScheduleJob( F&& f, Args&& ... args );
    void                                    WaitForCompletion();
    unsigned int                            GetProcessed() const { return processed; }
    unsigned int                            GetNumWorkers() const { return workers.size(); }
    void                                    SetNumWorkers( unsigned int );
    unsigned int                            GetMaxWorkers() const { return  std::thread::hardware_concurrency(); }

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


} // namespace ULIS

