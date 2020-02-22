// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         ParallelFor.h
* @author       Clement Berthaud
* @brief        This file provides the declarations for the ParallelFor utilities.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Base/Core.h"
#include "Thread/ThreadPool.h"

#define ULIS2_MACRO_INLINE_PARALLEL_FOR( _PERF, _POOL, _BLOCKING, _MAX, _FUNC, ... )    \
    if( _PERF.UseMT() && _POOL->GetNumWorkers() > 1 )                                   \
    {                                                                                   \
        for( int pLINE = 0; pLINE < _MAX; ++pLINE )                                     \
            _POOL->ScheduleJob( _FUNC, __VA_ARGS__ );                                   \
        if( _BLOCKING )                                                                 \
            _POOL->WaitForCompletion();                                                 \
    }                                                                                   \
    else                                                                                \
    {                                                                                   \
        for( int pLINE = 0; pLINE < _MAX; ++pLINE )                                     \
            _FUNC( __VA_ARGS__ );                                                       \
    }
