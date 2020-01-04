// Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         ParallelFor.h
* @author       Clement Berthaud
* @brief        This file provides the declarations for the ParallelFor utilities.
* @copyright    Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core.h"
#include "Perf.h"
#include "ThreadPool.h"
#include <functional>

ULIS2_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
// ParallelFor
inline  void  ParallelFor_Imp( FThreadPool& iPool, int32 iNum, std::function< void( int32 ) >& iFun, const FPerf& iPerformanceOptions = FPerf() )
{
    if( iPerformanceOptions.desired_workers > 1 && iPool.GetNumWorkers() > 1 )
    {
        for( int i = 0; i < iNum; ++i )
            iPool.ScheduleJob( iFun, i );
        iPool.WaitForCompletion();
    }
    else
    {
        for( int i = 0; i < iNum; ++i )
        {
            iFun( i );
        }
    }
}


inline  void  ParallelForPool( FThreadPool& iPool, int32 iNum, std::function< void( int32 ) > iFun, const FPerf& iPerformanceOptions = FPerf() )
{
    ParallelFor_Imp( iPool, iNum, iFun, iPerformanceOptions );
}

ULIS2_NAMESPACE_END

