// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         ParallelFor.cpp
* @author       Clement Berthaud
* @brief        This file provides the definitions for the ParallelFor utilities.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include "Thread/ParallelFor.h"
#include "Base/Perf.h"
#include "Thread/ThreadPool.h"

ULIS2_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
// ParallelFor
void ParallelFor( FThreadPool& iPool, bool iBlocking, const FPerf& iPerf, int32 iNum, const std::function< void( int32 ) >& iFun )
{
    if( iPerf.UseMT() && iPool.GetNumWorkers() > 1 )
    {
        for( int i = 0; i < iNum; ++i )
            iPool.ScheduleJob( iFun, i );

        if( iBlocking )
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

ULIS2_NAMESPACE_END

