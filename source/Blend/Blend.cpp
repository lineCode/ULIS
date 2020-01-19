// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Blend.cpp
* @author       Clement Berthaud
* @brief        This file provides the definitions for the Blend entry point functions.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include "Blend/Blend.h"
#include "Data/Block.h"
#include "Maths/Geometry.h"
// Mono Mem Generic
#include "Blend/Generic/Mono/MEM/BlendMono_Separable_MEM_Generic.ipp"
#include "Blend/Generic/Mono/MEM/BlendMono_NonSeparable_MEM_Generic.ipp"
#include "Blend/Generic/Mono/MEM/BlendMono_Misc_MEM_Generic.ipp"
// Mono SSE Generic
#include "Blend/Generic/Mono/SSE4_2/BlendMono_Separable_SSE4_2_Generic.ipp"
#include "Blend/Generic/Mono/SSE4_2/BlendMono_NonSeparable_SSE4_2_Generic.ipp"
#include "Blend/Generic/Mono/SSE4_2/BlendMono_Misc_SSE4_2_Generic.ipp"
// Mono AVX Generic
#include "Blend/Generic/Mono/AVX2/BlendMono_Separable_AVX2_Generic.ipp"
#include "Blend/Generic/Mono/AVX2/BlendMono_NonSeparable_AVX2_Generic.ipp"
#include "Blend/Generic/Mono/AVX2/BlendMono_Misc_AVX2_Generic.ipp"

ULIS2_NAMESPACE_BEGIN
template< typename T >
void ULIS2_FORCEINLINE Blend_imp( FThreadPool&          iPool
                                , const FBlock*         iSource
                                , FBlock*               iBackdrop
                                , const FRect&          iSrcRoi
                                , const FRect&          iDstRoi
                                , const eBlendingMode   iBlendingMode
                                , const eAlphaMode      iAlphaMode
                                , const float           iOpacity
                                , const FPerf&          iPerf )
{
    switch( iPerf.UseMT() ) {
        case true:
            if( iPerf.UseAVX2() ) {
                switch( BlendingModeQualifier( iBlendingMode ) ) {
                    //case BMQ_SEPARABLE       : BlendMT_AVX_Standard<   T >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iBlendingMode, iAlphaMode, iOpacity, iPerf ); break;
                    //case BMQ_NONSEPARABLE            : BlendMT_AVX_HSL<        T >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iBlendingMode, iAlphaMode, iOpacity, iPerf ); break;
                    //case BMQ_MISC           : BlendMT_AVX_Misc<       T >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iBlendingMode, iAlphaMode, iOpacity, iPerf ); break;
                }
            } else if( iPerf.UseSSE4_2() ) {
                switch( BlendingModeQualifier( iBlendingMode ) ) {
                    //case BMQ_SEPARABLE       : BlendMT_SSE_Standard<   T >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iBlendingMode, iAlphaMode, iOpacity, iPerf ); break;
                    //case BMQ_NONSEPARABLE            : BlendMT_SSE_HSL<        T >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iBlendingMode, iAlphaMode, iOpacity, iPerf ); break;
                    //case BMQ_MISC           : BlendMT_SSE_Misc<       T >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iBlendingMode, iAlphaMode, iOpacity, iPerf ); break;
                }
            } else {
                switch( BlendingModeQualifier( iBlendingMode ) ) {
                    //case BMQ_SEPARABLE       : BlendMT_MEM_Standard<   T >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iBlendingMode, iAlphaMode, iOpacity, iPerf ); break;
                    //case BMQ_NONSEPARABLE            : BlendMT_MEM_HSL<        T >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iBlendingMode, iAlphaMode, iOpacity, iPerf ); break;
                    //case BMQ_MISC           : BlendMT_MEM_Mic<        T >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iBlendingMode, iAlphaMode, iOpacity, iPerf ); break;
                } }
            break;

        case false:
            if( iPerf.UseAVX2() ) {
                switch( BlendingModeQualifier( iBlendingMode ) ) {
                    case BMQ_SEPARABLE      : BlendMono_Separable_AVX2<     T >( iSource, iBackdrop, iSrcRoi, iDstRoi, iBlendingMode, iAlphaMode, iOpacity ); break;
                    case BMQ_NONSEPARABLE   : BlendMono_NonSeparable_AVX2<  T >( iSource, iBackdrop, iSrcRoi, iDstRoi, iBlendingMode, iAlphaMode, iOpacity ); break;
                    case BMQ_MISC           : BlendMono_Misc_AVX2<          T >( iSource, iBackdrop, iSrcRoi, iDstRoi, iBlendingMode, iAlphaMode, iOpacity ); break;
                }
            } else if( iPerf.UseSSE4_2() ) {
                switch( BlendingModeQualifier( iBlendingMode ) ) {
                    case BMQ_SEPARABLE    : BlendMono_Separable_SSE4_2<     T >( iSource, iBackdrop, iSrcRoi, iDstRoi, iBlendingMode, iAlphaMode, iOpacity ); break;
                    case BMQ_NONSEPARABLE : BlendMono_NonSeparable_SSE4_2<  T >( iSource, iBackdrop, iSrcRoi, iDstRoi, iBlendingMode, iAlphaMode, iOpacity ); break;
                    case BMQ_MISC         : BlendMono_Misc_SSE4_2<          T >( iSource, iBackdrop, iSrcRoi, iDstRoi, iBlendingMode, iAlphaMode, iOpacity ); break;
                }
            } else {
                switch( BlendingModeQualifier( iBlendingMode ) ) {
                    case BMQ_SEPARABLE      : BlendMono_Separable_MEM<      T >( iSource, iBackdrop, iSrcRoi, iDstRoi, iBlendingMode, iAlphaMode, iOpacity ); break;
                    case BMQ_NONSEPARABLE   : BlendMono_NonSeparable_MEM<   T >( iSource, iBackdrop, iSrcRoi, iDstRoi, iBlendingMode, iAlphaMode, iOpacity ); break;
                    case BMQ_MISC           : BlendMono_Misc_MEM<           T >( iSource, iBackdrop, iSrcRoi, iDstRoi, iBlendingMode, iAlphaMode, iOpacity ); break;
                } }
            break;
    }
}


void
Blend( FThreadPool&     iPool
     , const FBlock*    iSource
     , FBlock*          iBackdrop
     , const FPoint&    iDstPos
     , eBlendingMode    iBlendingMode
     , eAlphaMode       iAlphaMode
     , float            iOpacity
     , const FPerf&     iPerf
     , bool             iCallInvalidCB )
{
    BlendRect( iPool
         , iSource
         , iBackdrop
         , iSource->Rect()
         , iDstPos
         , iBlendingMode
         , iAlphaMode
         , iOpacity
         , iPerf
         , iCallInvalidCB );
}


void
BlendRect( FThreadPool&     iPool
         , const FBlock*    iSource
         , FBlock*          iBackdrop
         , const FRect&     iSrcRect
         , const FPoint&    iDstPos
         , eBlendingMode    iBlendingMode
         , eAlphaMode       iAlphaMode
         , float            iOpacity
         , const FPerf&     iPerf
         , bool             iCallInvalidCB )
{
    ULIS2_ASSERT( iSource,                                                      "Bad source"                        );
    ULIS2_ASSERT( iBackdrop,                                                    "Bad destination"                   );
    ULIS2_ASSERT( iSource != iBackdrop,                                         "Can not blend a block on itself"   );
    ULIS2_ASSERT( iSource->Model() == iBackdrop->Model(),                       "Models do not match"               );
    ULIS2_ASSERT( iSource->Type() == iBackdrop->Type(),                         "Types do not match"                );
    ULIS2_ASSERT( iSource->SamplesPerPixel() == iBackdrop->SamplesPerPixel(),   "Samples do not match"              );
    ULIS2_ASSERT( iSource->Reversed() == iBackdrop->Reversed(),                 "Layouts do match"                  );
    ULIS2_ASSERT( iSource->Swapped() == iBackdrop->Swapped(),                   "Layouts do not match"              );

    // Gather src rect and shift to destination
    FRect target_rect = iSrcRect & iSource->Rect();
    target_rect.x = iDstPos.x;
    target_rect.y = iDstPos.y;
    // Gather dst rect
    // Interset target with dst, target may be out of range
    FRect dst_roi = target_rect & iBackdrop->Rect();
    // Gather src rect and fit size to fix overflow
    FRect src_roi = dst_roi;
    src_roi.x = iSrcRect.x;
    src_roi.y = iSrcRect.y;

    // Check if this is a no-op
    if( src_roi.Area() <= 0 )
        return;

    float opacity = FMaths::Clamp( iOpacity, 0.f, 1.f );
    switch( iSource->Type() ) {
        case TYPE_UINT8     : Blend_imp< uint8   >( iPool, iSource, iBackdrop, src_roi, dst_roi, iBlendingMode, iAlphaMode, opacity, iPerf ); break;
        case TYPE_UINT16    : Blend_imp< uint16  >( iPool, iSource, iBackdrop, src_roi, dst_roi, iBlendingMode, iAlphaMode, opacity, iPerf ); break;
        case TYPE_UINT32    : Blend_imp< uint32  >( iPool, iSource, iBackdrop, src_roi, dst_roi, iBlendingMode, iAlphaMode, opacity, iPerf ); break;
        case TYPE_UFLOAT    : Blend_imp< ufloat  >( iPool, iSource, iBackdrop, src_roi, dst_roi, iBlendingMode, iAlphaMode, opacity, iPerf ); break;
        case TYPE_UDOUBLE   : Blend_imp< udouble >( iPool, iSource, iBackdrop, src_roi, dst_roi, iBlendingMode, iAlphaMode, opacity, iPerf ); break;
    }

    iBackdrop->Invalidate( dst_roi, iCallInvalidCB );
}

ULIS2_NAMESPACE_END

