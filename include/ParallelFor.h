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

namespace std { template< typename T > class function; }
ULIS2_NAMESPACE_BEGIN
class FThreadPool;
/////////////////////////////////////////////////////
// ParallelFor
ULIS2_API void ParallelFor( FThreadPool& iPool, int32 iNum, std::function< void( int32 ) >& iFun, const FPerf& iPerf = FPerf() );

ULIS2_NAMESPACE_END

