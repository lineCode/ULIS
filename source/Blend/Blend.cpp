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
#include <glm/common.hpp>
// Mono Mem Generic
#include "Blend/Generic/Mono/MEM/BlendMono_Separable_MEM_Generic.ipp"
#include "Blend/Generic/Mono/MEM/BlendMono_NonSeparable_MEM_Generic.ipp"
#include "Blend/Generic/Mono/MEM/BlendMono_Misc_MEM_Generic.ipp"
// Mono SSE Generic
#include "Blend/Generic/Mono/SSE4_2/BlendMono_Separable_SSE4_2_Generic.ipp"
#include "Blend/Generic/Mono/SSE4_2/BlendMono_NonSeparable_SSE4_2_Generic.ipp"
#include "Blend/Generic/Mono/SSE4_2/BlendMono_Misc_SSE4_2_Generic.ipp"
// Mono AVX Generic
/*
#include "Blend/Generic/Mono/AVX2/BlendMono_Separable_AVX2_Generic.ipp"
#include "Blend/Generic/Mono/AVX2/BlendMono_NonSeparable_AVX2_Generic.ipp"
#include "Blend/Generic/Mono/AVX2/BlendMono_Misc_AVX2_Generic.ipp"
*/

ULIS2_NAMESPACE_BEGIN
template< typename T >
void ULIS2_FORCEINLINE Blend_imp( FThreadPool*          iPool
                                , bool                  iBlocking
                                , const FBlock*         iSource
                                , FBlock*               iBackdrop
                                , const glm::uvec2&     iSrcStart
                                , const glm::uvec2&     iDstStart
                                , const glm::uvec2&     iSrcRoiSize
                                , const glm::uvec2&     iDstRoiSize
                                , const glm::vec2&      iSubpixelComponent
                                , const eBlendingMode   iBlendingMode
                                , const eAlphaMode      iAlphaMode
                                , const float           iOpacity
                                , const FPerf&          iPerf )
{
    switch( iPerf.UseMT() ) {
        case true:
            if( iPerf.UseAVX2() ) {
                /*
                switch( BlendingModeQualifier( iBlendingMode ) ) {
                    case BMQ_SEPARABLE      : BlendMono_Separable_AVX2<         T >( iSource, iBackdrop, iSrcStart, iDstStart, iRoiSize, iSubpixelComponent, iBlendingMode, iAlphaMode, iOpacity ); break;
                    case BMQ_NONSEPARABLE   : BlendMono_NonSeparable_AVX2<      T >( iSource, iBackdrop, iSrcStart, iDstStart, iRoiSize, iSubpixelComponent, iBlendingMode, iAlphaMode, iOpacity ); break;
                    case BMQ_MISC           : BlendMono_Misc_AVX2<              T >( iSource, iBackdrop, iSrcStart, iDstStart, iRoiSize, iSubpixelComponent, iBlendingMode, iAlphaMode, iOpacity ); break;
                }
                */
            } else if( iPerf.UseSSE4_2() ) {
                /*
                switch( BlendingModeQualifier( iBlendingMode ) ) {
                    case BMQ_SEPARABLE      : BlendMono_Separable_SSE4_2<       T >( iSource, iBackdrop, iSrcStart, iDstStart, iSrcRoiSize, iDstRoiSize, iSubpixelComponent, iBlendingMode, iAlphaMode, iOpacity ); break;
                    case BMQ_NONSEPARABLE   : BlendMono_NonSeparable_SSE4_2<    T >( iSource, iBackdrop, iSrcStart, iDstStart, iSrcRoiSize, iDstRoiSize, iSubpixelComponent, iBlendingMode, iAlphaMode, iOpacity ); break;
                    case BMQ_MISC           : BlendMono_Misc_SSE4_2<            T >( iSource, iBackdrop, iSrcStart, iDstStart, iSrcRoiSize, iDstRoiSize, iSubpixelComponent, iBlendingMode, iAlphaMode, iOpacity ); break;
                }
                */
            } else {
                /*
                switch( BlendingModeQualifier( iBlendingMode ) ) {
                    case BMQ_SEPARABLE      : BlendMono_Separable_MEM<          T >( iSource, iBackdrop, iSrcStart, iDstStart, iSrcRoiSize, iRoiSize, iSubpixelComponent, iBlendingMode, iAlphaMode, iOpacity ); break;
                    case BMQ_NONSEPARABLE   : BlendMono_NonSeparable_MEM<       T >( iSource, iBackdrop, iSrcStart, iDstStart, iSrcRoiSize, iRoiSize, iSubpixelComponent, iBlendingMode, iAlphaMode, iOpacity ); break;
                    case BMQ_MISC           : BlendMono_Misc_MEM<               T >( iSource, iBackdrop, iSrcStart, iDstStart, iSrcRoiSize, iRoiSize, iSubpixelComponent, iBlendingMode, iAlphaMode, iOpacity ); break;
                }
                */
            }
            break;

        case false:
            if( iPerf.UseAVX2() ) {
                /*
                switch( BlendingModeQualifier( iBlendingMode ) ) {
                    case BMQ_SEPARABLE      : BlendMono_Separable_AVX2<         T >( iSource, iBackdrop, iSrcStart, iDstStart, iRoiSize, iSubpixelComponent, iBlendingMode, iAlphaMode, iOpacity ); break;
                    case BMQ_NONSEPARABLE   : BlendMono_NonSeparable_AVX2<      T >( iSource, iBackdrop, iSrcStart, iDstStart, iRoiSize, iSubpixelComponent, iBlendingMode, iAlphaMode, iOpacity ); break;
                    case BMQ_MISC           : BlendMono_Misc_AVX2<              T >( iSource, iBackdrop, iSrcStart, iDstStart, iRoiSize, iSubpixelComponent, iBlendingMode, iAlphaMode, iOpacity ); break;
                }
                */
            } else if( iPerf.UseSSE4_2() ) {
                /*
                switch( BlendingModeQualifier( iBlendingMode ) ) {
                    case BMQ_SEPARABLE      : BlendMono_Separable_SSE4_2<       T >( iSource, iBackdrop, iSrcStart, iDstStart, iSrcRoiSize, iDstRoiSize, iSubpixelComponent, iBlendingMode, iAlphaMode, iOpacity ); break;
                    case BMQ_NONSEPARABLE   : BlendMono_NonSeparable_SSE4_2<    T >( iSource, iBackdrop, iSrcStart, iDstStart, iSrcRoiSize, iDstRoiSize, iSubpixelComponent, iBlendingMode, iAlphaMode, iOpacity ); break;
                    case BMQ_MISC           : BlendMono_Misc_SSE4_2<            T >( iSource, iBackdrop, iSrcStart, iDstStart, iSrcRoiSize, iDstRoiSize, iSubpixelComponent, iBlendingMode, iAlphaMode, iOpacity ); break;
                }
                */
            } else {
                switch( BlendingModeQualifier( iBlendingMode ) ) {
                    case BMQ_SEPARABLE      : BlendMono_Separable_MEM<          T >( iSource, iBackdrop, iSrcStart, iDstStart, iSrcRoiSize, iDstRoiSize, iSubpixelComponent, iBlendingMode, iAlphaMode, iOpacity ); break;
                    case BMQ_NONSEPARABLE   : BlendMono_NonSeparable_MEM<       T >( iSource, iBackdrop, iSrcStart, iDstStart, iSrcRoiSize, iDstRoiSize, iSubpixelComponent, iBlendingMode, iAlphaMode, iOpacity ); break;
                    case BMQ_MISC           : BlendMono_Misc_MEM<               T >( iSource, iBackdrop, iSrcStart, iDstStart, iSrcRoiSize, iDstRoiSize, iSubpixelComponent, iBlendingMode, iAlphaMode, iOpacity ); break;
                }
            }
            break;
    }
}


void
Blend( FThreadPool*     iPool
     , bool             iBlocking
     , const FBlock*    iSource
     , FBlock*          iBackdrop
     , const glm::vec2& iDstPos
     , eBlendingMode    iBlendingMode
     , eAlphaMode       iAlphaMode
     , float            iOpacity
     , const FPerf&     iPerf
     , bool             iCallInvalidCB )
{
    BlendRect( iPool
             , iBlocking
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
BlendRect( FThreadPool*     iPool
         , bool             iBlocking
         , const FBlock*    iSource
         , FBlock*          iBackdrop
         , const FRect&     iSrcRect
         , const glm::vec2& iDstPos
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

    // Ensure the selected source rect actually fits in source dimensions.
    FRect src_roi = iSrcRect & iSource->Rect();
    
    // Compute coordinates of target rect in destination, with source rect dimension
    int target_xmin = static_cast< int >( FMaths::RoundToNegativeInfinity( iDstPos.x ) );
    int target_ymin = static_cast< int >( FMaths::RoundToNegativeInfinity( iDstPos.y ) );
    int target_xmax = static_cast< int >( FMaths::RoundToPositiveInfinity( iDstPos.x + src_roi.w ) );
    int target_ymax = static_cast< int >( FMaths::RoundToPositiveInfinity( iDstPos.y + src_roi.h ) );
    FRect dst_target = FRect::FromMinMax( target_xmin, target_ymin, target_xmax, target_ymax );

    // Ensure the selected target actually fits in destination
    FRect dst_fit = dst_target & iBackdrop->Rect();

    if( dst_fit.Area() <= 0 ) return;

    // Get potential overflow
    int fx = dst_target.x - dst_fit.x;
    int fy = dst_target.y - dst_fit.y;

    float opacity = FMaths::Clamp( iOpacity, 0.f, 1.f );
    //int fx = xmin < 0 ? xmin : 0;
    //int fy = ymin < 0 ? ymin : 0;
    glm::vec2   subpixel_component = glm::abs( FMaths::FloatingPart( iDstPos ) );
    glm::uvec2  src_start = glm::uvec2( src_roi.x - fx, src_roi.y - fy );
    glm::uvec2  dst_start = glm::uvec2( dst_fit.x, dst_fit.y );
    glm::uvec2  src_roi_size = glm::uvec2( src_roi.w, src_roi.w );
    glm::uvec2  dst_roi_size = glm::uvec2( dst_fit.w, dst_fit.w );

    switch( iSource->Type() ) {
        case TYPE_UINT8     : Blend_imp< uint8   >( iPool, iBlocking, iSource, iBackdrop, src_start, dst_start, src_roi_size, dst_roi_size, subpixel_component, iBlendingMode, iAlphaMode, opacity, iPerf ); break;
        case TYPE_UINT16    : Blend_imp< uint16  >( iPool, iBlocking, iSource, iBackdrop, src_start, dst_start, src_roi_size, dst_roi_size, subpixel_component, iBlendingMode, iAlphaMode, opacity, iPerf ); break;
        case TYPE_UINT32    : Blend_imp< uint32  >( iPool, iBlocking, iSource, iBackdrop, src_start, dst_start, src_roi_size, dst_roi_size, subpixel_component, iBlendingMode, iAlphaMode, opacity, iPerf ); break;
        case TYPE_UFLOAT    : Blend_imp< ufloat  >( iPool, iBlocking, iSource, iBackdrop, src_start, dst_start, src_roi_size, dst_roi_size, subpixel_component, iBlendingMode, iAlphaMode, opacity, iPerf ); break;
        case TYPE_UDOUBLE   : Blend_imp< udouble >( iPool, iBlocking, iSource, iBackdrop, src_start, dst_start, src_roi_size, dst_roi_size, subpixel_component, iBlendingMode, iAlphaMode, opacity, iPerf ); break;
    }

    iBackdrop->Invalidate( dst_fit, iCallInvalidCB );
}

ULIS2_NAMESPACE_END

