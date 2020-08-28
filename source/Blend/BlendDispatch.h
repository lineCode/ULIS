// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS
*__________________
*
* @file         BlendDispatch.h
* @author       Clement Berthaud
* @brief        This file provides the dispatch mechanism for Blend invocations.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"
#include "Blend/Modes.h"
#include "Blend/BlendArgs.h"
#include "Dispatch/Dispatcher.h"

// Include MEM Generic Implementation
#include "Blend/Generic/BlendMT_Separable_MEM_Generic.h"
#include "Blend/Generic/BlendMT_NonSeparable_MEM_Generic.h"
#include "Blend/Generic/BlendMT_Misc_MEM_Generic.h"
#include "Blend/Generic/AlphaBlendMT_MEM_Generic.h"
#include "Blend/Generic/TiledBlendMT_Separable_MEM_Generic.h"
#include "Blend/Generic/TiledBlendMT_NonSeparable_MEM_Generic.h"
#include "Blend/Generic/TiledBlendMT_Misc_MEM_Generic.h"

// Include SSE RGBA8 Implementation
#ifdef ULIS_COMPILETIME_SSE42_SUPPORT
#include "Blend/RGBA8/BlendMT_Separable_SSE_RGBA8.h"
#include "Blend/RGBA8/BlendMT_NonSeparable_SSE_RGBA8.h"
#include "Blend/RGBA8/AlphaBlendMT_SSE_RGBA8.h"
#include "Blend/RGBA8/TiledBlendMT_Separable_SSE_RGBA8.h"
#include "Blend/RGBA8/TiledBlendMT_NonSeparable_SSE_RGBA8.h"
#endif // ULIS_COMPILETIME_SSE42_SUPPORT

// Include AVX RGBA8 Implementation
#ifdef ULIS_COMPILETIME_AVX2_SUPPORT
#include "Blend/RGBA8/BlendMT_Separable_AVX_RGBA8.h"
#include "Blend/RGBA8/AlphaBlendMT_AVX_RGBA8.h"
#endif // ULIS_COMPILETIME_AVX2_SUPPORT

ULIS_NAMESPACE_BEGIN
typedef void (*fpBlendInvocationScheduler)( std::shared_ptr< const FBlendArgs > iBlendParams );

// V2
/////////////////////////////////////////////////////
// Blend Dispatcher
ULIS_BEGIN_DISPATCHER_GENERIC(
      FDispatchedBlendSeparableInvocationSchedulerSelector
    , fpBlendInvocationScheduler
    , &ScheduleBlendMT_Separable_MEM_Generic< T >
)
    ULIS_DECL_DISPATCH_SPEC(
          &OldDispatchTestIsUnorderedRGBA8
        , &ScheduleBlendMT_Separable_AVX_RGBA8
        , &ScheduleBlendMT_Separable_SSE_RGBA8
        , &ScheduleBlendMT_Separable_MEM_Generic< uint8 >
    )
ULIS_END_DISPATCHER( FDispatchedBlendSeparableInvocationSchedulerSelector )

ULIS_NAMESPACE_END

