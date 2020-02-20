// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Perf.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the FPerf struct.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Base/Core.h"

ULIS2_NAMESPACE_BEGIN

#define UPERF_MT_BIT        0x1
#define UPERF_TSPEC_BIT     0x2
#define UPERF_SSE4_2_BIT    0x4
#define UPERF_AVX2_BIT      0x8
#define UPERF_GPU_BIT       0xF
#define UPERF_LOWEST        0x0
#define UPERF_BEST_CPU      UPERF_MT_BIT | UPERF_TSPEC_BIT | UPERF_SSE4_2_BIT | UPERF_AVX2_BIT
#define UPERF_BEST_GPU      UPERF_BEST_CPU | UPERF_GPU_BIT
enum ePerf {
      Perf_MT       = UPERF_MT_BIT
    , Perf_TSPEC    = UPERF_TSPEC_BIT
    , Perf_SSE4_2   = UPERF_SSE4_2_BIT
    , Perf_AVX2     = UPERF_AVX2_BIT
    , Perf_GPU      = UPERF_GPU_BIT
    , Perf_Lowest   = UPERF_LOWEST
    , Perf_Best_CPU = UPERF_BEST_CPU
    , Perf_Best_GPU = UPERF_GPU_BIT
};

/////////////////////////////////////////////////////
/// @struct     FPerf
/// @brief      The FPerf class is used for holding performance options.
/// @details    Used for specification and forwarding of options in multi threaded / SSE pipelines.
///             These flags are juste hints, they can be overriden in some pipelines.
class ULIS2_API FPerf
{
public:
    // Construction
    /// @fn         FPerf( uint32 iFlags = UPERF_MAXCPU_PERF )
    /// @brief      Default Constructor.
    /// @details    Initializes members with default values
    FPerf( uint32 iFlags = Perf_Best_CPU );

public:
    // Getters
    uint32 Flags()      const;
    bool UseMT()        const;
    bool UseTSPEC()     const;
    bool UseSSE4_2()    const;
    bool UseAVX2()      const;
    bool UseGPU()       const;

private:
    // Private Data Members
    uint32 flags;
};

ULIS2_API struct FPerfParams {
    FThreadPool*    pool;
    FPerf           intent;
    bool            blocking;
    bool            callCB;
};

ULIS2_NAMESPACE_END

