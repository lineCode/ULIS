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
#include "Base/Perf.h"
#include "Thread/ThreadPool.h"
#include <functional>

ULIS2_NAMESPACE_BEGIN
class FThreadPool;
/////////////////////////////////////////////////////
// ParallelFor
#define ULIS2_PF_CALL [&]( int32 iLine )
ULIS2_API void ParallelFor( FThreadPool& iPool, int32 iNum, const FPerf& iPerf, const std::function< void( int32 ) >& iFun );

ULIS2_NAMESPACE_END

