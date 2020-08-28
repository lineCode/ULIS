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
#include "Dispatch/Dispatch.h"

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
/////////////////////////////////////////////////////
// Typedefs
typedef void (*fpBlendInvocation)( std::shared_ptr< const FBlendArgs > iBlendParams );
typedef void (*fpBlendInvocationScheduler)( std::shared_ptr< const FBlendArgs > iBlendParams );

/////////////////////////////////////////////////////
// Implementors
#define ULIS_IMP_BLEND_INVOCATION_SELECTOR( TAG, MISC, MISCAA, SEP, SEPAA, NSEP, NSEPAA )   \
fpBlendInvocation TAG ( const FBlendArgs& iInfo ) {                                         \
    switch( BlendingModeQualifier( iInfo.blendingMode ) ) {                                 \
        case BMQ_MISC           : return  iInfo.subpixelFlag ? MISCAA   : MISC;             \
        case BMQ_SEPARABLE      : return  iInfo.subpixelFlag ? SEPAA    : SEP;              \
        case BMQ_NONSEPARABLE   : return  iInfo.subpixelFlag ? NSEPAA   : NSEP;             \
        default                 : return  nullptr;                                          \
    }                                                                                       \
}

#define ULIS_IMP_ALPHABLEND_INVOCATION_SELECTOR( TAG, SEP, SEPAA )  \
fpBlendInvocation TAG ( const FBlendArgs& iInfo ) {                 \
    return  iInfo.subpixelFlag ? SEPAA    : SEP;                    \
}

#define ULIS_IMP_TILEDBLEND_INVOCATION_SELECTOR( TAG, MISC, SEP, NSEP ) \
fpBlendInvocation TAG ( const FBlendArgs& iInfo ) {                     \
    switch( BlendingModeQualifier( iInfo.blendingMode ) ) {             \
        case BMQ_MISC           : return  MISC;                         \
        case BMQ_SEPARABLE      : return  SEP;                          \
        case BMQ_NONSEPARABLE   : return  NSEP;                         \
        default                 : return  nullptr;                      \
    }                                                                   \
}

/////////////////////////////////////////////////////
// Blend Invocation Selectors
template< typename T > ULIS_IMP_BLEND_INVOCATION_SELECTOR( SelectBlendInvocationMEMGeneric
    , &ScheduleBlendMT_Misc_MEM_Generic< T >                , &ScheduleBlendMT_Misc_MEM_Generic_Subpixel< T >
    , &ScheduleBlendMT_Separable_MEM_Generic< T >           , &ScheduleBlendMT_Separable_MEM_Generic_Subpixel< T >
    , &ScheduleBlendMT_NonSeparable_MEM_Generic< T >        , &ScheduleBlendMT_NonSeparable_MEM_Generic_Subpixel< T > )
#ifdef ULIS_COMPILETIME_AVX2_SUPPORT
ULIS_IMP_BLEND_INVOCATION_SELECTOR( SelectBlendInvocationAVXRGBA8
    , &ScheduleBlendMT_Misc_MEM_Generic< uint8 >            , &ScheduleBlendMT_Misc_MEM_Generic_Subpixel< uint8 >
    , &ScheduleBlendMT_Separable_AVX_RGBA8                  , &ScheduleBlendMT_Separable_AVX_RGBA8_Subpixel
    , &ScheduleBlendMT_NonSeparable_SSE_RGBA8               , &ScheduleBlendMT_NonSeparable_SSE_RGBA8_Subpixel )
#endif // ULIS_COMPILETIME_AVX2_SUPPORT
#ifdef ULIS_COMPILETIME_SSE42_SUPPORT
ULIS_IMP_BLEND_INVOCATION_SELECTOR( SelectBlendInvocationSSERGBA8
    , &ScheduleBlendMT_Misc_MEM_Generic< uint8 >            , &ScheduleBlendMT_Misc_MEM_Generic_Subpixel< uint8 >
    , &ScheduleBlendMT_Separable_SSE_RGBA8                  , &ScheduleBlendMT_Separable_SSE_RGBA8_Subpixel
    , &ScheduleBlendMT_NonSeparable_SSE_RGBA8               , &ScheduleBlendMT_NonSeparable_SSE_RGBA8_Subpixel )
#endif // ULIS_COMPILETIME_SSE42_SUPPORT
ULIS_IMP_BLEND_INVOCATION_SELECTOR( SelectBlendInvocationMEMRGBA8
    , &ScheduleBlendMT_Misc_MEM_Generic< uint8 >            , &ScheduleBlendMT_Misc_MEM_Generic_Subpixel< uint8 >
    , &ScheduleBlendMT_Separable_MEM_Generic< uint8 >       , &ScheduleBlendMT_Separable_MEM_Generic_Subpixel< uint8 >
    , &ScheduleBlendMT_NonSeparable_MEM_Generic< uint8 >    , &ScheduleBlendMT_NonSeparable_MEM_Generic_Subpixel< uint8 > )

/////////////////////////////////////////////////////
// AlphaBlend Invocation Selectors
template< typename T > ULIS_IMP_ALPHABLEND_INVOCATION_SELECTOR( SelectAlphaBlendInvocationMEMGeneric
    , &ScheduleAlphaBlendMT_Separable_MEM_Generic< T >      , &ScheduleAlphaBlendMT_Separable_MEM_Generic_Subpixel< T > )
#ifdef ULIS_COMPILETIME_AVX2_SUPPORT
ULIS_IMP_ALPHABLEND_INVOCATION_SELECTOR( SelectAlphaBlendInvocationAVXRGBA8
    , &ScheduleAlphaBlendMT_Separable_AVX_RGBA8             , &ScheduleAlphaBlendMT_Separable_AVX_RGBA8_Subpixel )
#endif // ULIS_COMPILETIME_AVX2_SUPPORT
#ifdef ULIS_COMPILETIME_SSE42_SUPPORT
ULIS_IMP_ALPHABLEND_INVOCATION_SELECTOR( SelectAlphaBlendInvocationSSERGBA8
    , &ScheduleAlphaBlendMT_Separable_SSE_RGBA8             , &ScheduleAlphaBlendMT_Separable_SSE_RGBA8_Subpixel )
#endif // ULIS_COMPILETIME_SSE42_SUPPORT
ULIS_IMP_ALPHABLEND_INVOCATION_SELECTOR( SelectAlphaBlendInvocationMEMRGBA8
    , &ScheduleAlphaBlendMT_Separable_MEM_Generic< uint8 >  , &ScheduleAlphaBlendMT_Separable_MEM_Generic_Subpixel< uint8 > )

/////////////////////////////////////////////////////
// TiledBlend Invocation Selectors
template< typename T > ULIS_IMP_TILEDBLEND_INVOCATION_SELECTOR( SelectTiledBlendInvocationMEMGeneric
    , &ScheduleTiledBlendMT_Misc_MEM_Generic< T >,      &ScheduleTiledBlendMT_Separable_MEM_Generic< T >, &ScheduleTiledBlendMT_NonSeparable_MEM_Generic< T > )
#ifdef ULIS_COMPILETIME_AVX2_SUPPORT
ULIS_IMP_TILEDBLEND_INVOCATION_SELECTOR( SelectTiledBlendInvocationAVXRGBA8
    , &ScheduleTiledBlendMT_Misc_MEM_Generic< uint8 >,  &ScheduleTiledBlendMT_NonSeparable_SSE_RGBA8, &ScheduleTiledBlendMT_NonSeparable_SSE_RGBA8 )
#endif // ULIS_COMPILETIME_AVX2_SUPPORT
#ifdef ULIS_COMPILETIME_SSE42_SUPPORT
ULIS_IMP_TILEDBLEND_INVOCATION_SELECTOR( SelectTiledBlendInvocationSSERGBA8
    , &ScheduleTiledBlendMT_Misc_MEM_Generic< uint8 >,  &ScheduleTiledBlendMT_Separable_SSE_RGBA8, &ScheduleTiledBlendMT_NonSeparable_SSE_RGBA8 )
#endif // ULIS_COMPILETIME_SSE42_SUPPORT
ULIS_IMP_TILEDBLEND_INVOCATION_SELECTOR( SelectTiledBlendInvocationMEMRGBA8
    , &ScheduleTiledBlendMT_Misc_MEM_Generic< uint8 >,  &ScheduleTiledBlendMT_Separable_MEM_Generic< uint8 >, &ScheduleTiledBlendMT_NonSeparable_MEM_Generic< uint8 > )

/////////////////////////////////////////////////////
// Blend Dispatcher
ULIS_BEGIN_OLDDISPATCHER_GENERIC( FBlendInvocationSelector, fpBlendInvocation, FBlendArgs, &SelectBlendInvocationMEMGeneric< T > )
    ULIS_DECL_OLDDISPATCH_SPEC( &OldDispatchTestIsUnorderedRGBA8, &SelectBlendInvocationAVXRGBA8, &SelectBlendInvocationSSERGBA8, &SelectBlendInvocationMEMRGBA8 )
ULIS_END_OLDDISPATCHER( FBlendInvocationSelector )

/////////////////////////////////////////////////////
// AlphaBlend Dispatcher
ULIS_BEGIN_OLDDISPATCHER_GENERIC( FAlphaBlendInvocationSelector, fpBlendInvocation, FBlendArgs, &SelectAlphaBlendInvocationMEMGeneric< T > )
    ULIS_DECL_OLDDISPATCH_SPEC( &OldDispatchTestIsUnorderedRGBA8, &SelectAlphaBlendInvocationAVXRGBA8, &SelectAlphaBlendInvocationSSERGBA8, &SelectAlphaBlendInvocationMEMRGBA8 )
ULIS_END_OLDDISPATCHER( FAlphaBlendInvocationSelector )

/////////////////////////////////////////////////////
// TiledBlend Dispatcher
ULIS_BEGIN_OLDDISPATCHER_GENERIC( FTiledBlendInvocationSelector, fpBlendInvocation, FBlendArgs, &SelectTiledBlendInvocationMEMGeneric< T > )
    ULIS_DECL_OLDDISPATCH_SPEC( &OldDispatchTestIsUnorderedRGBA8, &SelectTiledBlendInvocationAVXRGBA8, &SelectTiledBlendInvocationSSERGBA8, &SelectTiledBlendInvocationMEMRGBA8 )
ULIS_END_OLDDISPATCHER( FTiledBlendInvocationSelector )

// V2
/////////////////////////////////////////////////////
// Blend Dispatcher
ULIS_BEGIN_OLDDISPATCHER_GENERIC(
      FDispatchedBlendSeparableInvocationSchedulerSelector
    , fpBlendInvocationScheduler
    , FBlendArgs
    , &ScheduleBlendMT_Separable_MEM_Generic< T >
)
    ULIS_DECL_OLDDISPATCH_SPEC(
          &OldDispatchTestIsUnorderedRGBA8
        , &ScheduleBlendMT_Separable_AVX_RGBA8
        , &ScheduleBlendMT_Separable_SSE_RGBA8
        , &ScheduleBlendMT_Separable_MEM_Generic< uint8 >
    )
ULIS_END_OLDDISPATCHER( FDispatchedBlendSeparableInvocationSchedulerSelector )

ULIS_NAMESPACE_END

