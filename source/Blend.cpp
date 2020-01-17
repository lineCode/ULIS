// Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Blend.cpp
* @author       Clement Berthaud
* @brief        This file provides the definitions for the Blend entry point functions.
* @copyright    Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include "Blend.h"
#include "Block.h"
#include "Geometry.h"
#include "BlendGeneric.h"

ULIS2_NAMESPACE_BEGIN
template< typename T >
void ULIS2_FORCEINLINE Blend_imp( FThreadPool&  iPool
                                , const FBlock* iSource
                                , FBlock*       iBackdrop
                                , const FRect&  iSrcRoi
                                , const FRect&  iDstRoi
                                , eBlendingMode iBlendingMode
                                , eAlphaMode    iAlphaMode
                                , float         iOpacity
                                , const FPerf&  iPerf )
{
    switch( iPerf.UseMT() ) {
        case true:
            if( iPerf.UseAVX2() ) {
                switch( BlendingModeQualifier( iBlendingMode ) ) {
                    //case BMQ_STANDARD       : BlendMT_AVX_Standard<   T >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iBlendingMode, iAlphaMode, iOpacity, iPerf ); break;
                    //case BMQ_HSL            : BlendMT_AVX_HSL<        T >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iBlendingMode, iAlphaMode, iOpacity, iPerf ); break;
                    //case BMQ_MISC           : BlendMT_AVX_Misc<       T >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iBlendingMode, iAlphaMode, iOpacity, iPerf ); break;
                }
            } else if( iPerf.UseSSE4_2() ) {
                switch( BlendingModeQualifier( iBlendingMode ) ) {
                    //case BMQ_STANDARD       : BlendMT_SSE_Standard<   T >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iBlendingMode, iAlphaMode, iOpacity, iPerf ); break;
                    //case BMQ_HSL            : BlendMT_SSE_HSL<        T >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iBlendingMode, iAlphaMode, iOpacity, iPerf ); break;
                    //case BMQ_MISC           : BlendMT_SSE_Misc<       T >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iBlendingMode, iAlphaMode, iOpacity, iPerf ); break;
                }
            } else {
                switch( BlendingModeQualifier( iBlendingMode ) ) {
                    //case BMQ_STANDARD       : BlendMT_MEM_Standard<   T >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iBlendingMode, iAlphaMode, iOpacity, iPerf ); break;
                    //case BMQ_HSL            : BlendMT_MEM_HSL<        T >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iBlendingMode, iAlphaMode, iOpacity, iPerf ); break;
                    //case BMQ_MISC           : BlendMT_MEM_Mic<        T >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iBlendingMode, iAlphaMode, iOpacity, iPerf ); break;
                } }
            break;

        case false:
            if( iPerf.UseAVX2() ) {
                switch( BlendingModeQualifier( iBlendingMode ) ) {
                    //case BMQ_STANDARD       : BlendMono_AVX_Standard<   T >( iSource, iBackdrop, iSrcRoi, iDstRoi, iBlendingMode, iAlphaMode, iOpacity ); break;
                    //case BMQ_HSL            : BlendMono_AVX_HSL<        T >( iSource, iBackdrop, iSrcRoi, iDstRoi, iBlendingMode, iAlphaMode, iOpacity ); break;
                    //case BMQ_MISC           : BlendMono_AVX_Misc<       T >( iSource, iBackdrop, iSrcRoi, iDstRoi, iBlendingMode, iAlphaMode, iOpacity ); break;
                }
            } else if( iPerf.UseSSE4_2() ) {
                switch( BlendingModeQualifier( iBlendingMode ) ) {
                    //case BMQ_STANDARD       : BlendMono_SSE_Standard<   T >( iSource, iBackdrop, iSrcRoi, iDstRoi, iBlendingMode, iAlphaMode, iOpacity ); break;
                    //case BMQ_HSL            : BlendMono_SSE_HSL<        T >( iSource, iBackdrop, iSrcRoi, iDstRoi, iBlendingMode, iAlphaMode, iOpacity ); break;
                    //case BMQ_MISC           : BlendMono_SSE_Misc<       T >( iSource, iBackdrop, iSrcRoi, iDstRoi, iBlendingMode, iAlphaMode, iOpacity ); break;
                }
            } else {
                switch( BlendingModeQualifier( iBlendingMode ) ) {
                    case BMQ_STANDARD       : BlendMono_MEM_Standard<   T >( iSource, iBackdrop, iSrcRoi, iDstRoi, iBlendingMode, iAlphaMode, iOpacity ); break;
                    case BMQ_HSL            : BlendMono_MEM_HSL<        T >( iSource, iBackdrop, iSrcRoi, iDstRoi, iBlendingMode, iAlphaMode, iOpacity ); break;
                    case BMQ_MISC           : BlendMono_MEM_Misc<       T >( iSource, iBackdrop, iSrcRoi, iDstRoi, iBlendingMode, iAlphaMode, iOpacity ); break;
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
    ULIS2_ASSERT( iSource->Model() == iBackdrop->Model(),                       "Models do not match" );
    ULIS2_ASSERT( iSource->Type() == iBackdrop->Type(),                         "Types do not match" );
    ULIS2_ASSERT( iSource->SamplesPerPixel() == iBackdrop->SamplesPerPixel(),   "Samples do not match" );
    ULIS2_ASSERT( iSource->Reversed() == iBackdrop->Reversed(),                 "Layouts do match" );
    ULIS2_ASSERT( iSource->Swapped() == iBackdrop->Swapped(),                   "Layouts do not match" );
    ULIS2_ASSERT( iSource,                                                      "Bad source" );
    ULIS2_ASSERT( iBackdrop,                                                    "Bad destination" );
    ULIS2_ASSERT( iSource != iBackdrop,                                         "Can not blend a block on itself" );

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


/*
template< typename T, eBlendingMode _BM >
void ULIS2_FORCEINLINE Blend_select_AM( FThreadPool&    iPool
                                      , const FBlock*   iSource
                                      , FBlock*         iBackdrop
                                      , const FRect&    iSrcRoi
                                      , const FRect&    iDstRoi
                                      , eAlphaMode      iAlphaMode
                                      , float           iOpacity
                                      , const FPerf&    iPerf )
{
    switch( iAlphaMode ) {
        case AM_NORMAL  :   Blend_imp< T, _BM, AM_NORMAL    >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iOpacity, iPerf ); break;
        case AM_ERASE   :   Blend_imp< T, _BM, AM_ERASE     >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iOpacity, iPerf ); break;
        case AM_TOP     :   Blend_imp< T, _BM, AM_TOP       >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iOpacity, iPerf ); break;
        case AM_BACK    :   Blend_imp< T, _BM, AM_BACK      >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iOpacity, iPerf ); break;
        case AM_SUB     :   Blend_imp< T, _BM, AM_SUB       >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iOpacity, iPerf ); break;
        case AM_ADD     :   Blend_imp< T, _BM, AM_ADD       >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iOpacity, iPerf ); break;
        case AM_MUL     :   Blend_imp< T, _BM, AM_MUL       >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iOpacity, iPerf ); break;
        case AM_MIN     :   Blend_imp< T, _BM, AM_MIN       >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iOpacity, iPerf ); break;
        case AM_MAX     :   Blend_imp< T, _BM, AM_MAX       >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iOpacity, iPerf ); break;
        case AM_INVMAX  :   Blend_imp< T, _BM, AM_INVMAX    >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iOpacity, iPerf ); break;
    }
}


template< typename T >
void ULIS2_FORCEINLINE Blend_select_BM( FThreadPool&    iPool
                                      , const FBlock*   iSource
                                      , FBlock*         iBackdrop
                                      , const FRect&    iSrcRoi
                                      , const FRect&    iDstRoi
                                      , eBlendingMode   iBlendingMode
                                      , eAlphaMode      iAlphaMode
                                      , float           iOpacity
                                      , const FPerf&    iPerf )
{
    switch( iBlendingMode ) {
        case BM_NORMAL          :   Blend_select_AM< T, BM_NORMAL       >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case BM_TOP             :   Blend_select_AM< T, BM_TOP          >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case BM_BACK            :   Blend_select_AM< T, BM_BACK         >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case BM_BEHIND          :   Blend_select_AM< T, BM_BEHIND       >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case BM_DISSOLVE        :   Blend_select_AM< T, BM_DISSOLVE     >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case BM_DARKEN          :   Blend_select_AM< T, BM_DARKEN       >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case BM_MULTIPY         :   Blend_select_AM< T, BM_MULTIPY      >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case BM_COLORBURN       :   Blend_select_AM< T, BM_COLORBURN    >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case BM_LINEARBURN      :   Blend_select_AM< T, BM_LINEARBURN   >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case BM_DARKERCOLOR     :   Blend_select_AM< T, BM_DARKERCOLOR  >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case BM_LIGHTEN         :   Blend_select_AM< T, BM_LIGHTEN      >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case BM_SCREEN          :   Blend_select_AM< T, BM_SCREEN       >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case BM_COLORDODGE      :   Blend_select_AM< T, BM_COLORDODGE   >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case BM_LINEARDODGE     :   Blend_select_AM< T, BM_LINEARDODGE  >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case BM_LIGHTERCOLOR    :   Blend_select_AM< T, BM_LIGHTERCOLOR >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case BM_OVERLAY         :   Blend_select_AM< T, BM_OVERLAY      >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case BM_SOFTLIGHT       :   Blend_select_AM< T, BM_SOFTLIGHT    >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case BM_HARDLIGHT       :   Blend_select_AM< T, BM_HARDLIGHT    >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case BM_VIVIDLIGHT      :   Blend_select_AM< T, BM_VIVIDLIGHT   >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case BM_LINEARLIGHT     :   Blend_select_AM< T, BM_LINEARLIGHT  >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case BM_PINLIGHT        :   Blend_select_AM< T, BM_PINLIGHT     >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case BM_HARDMIX         :   Blend_select_AM< T, BM_HARDMIX      >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case BM_DIFFERENCE      :   Blend_select_AM< T, BM_DIFFERENCE   >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case BM_EXCLUSION       :   Blend_select_AM< T, BM_EXCLUSION    >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case BM_SUBSTRACT       :   Blend_select_AM< T, BM_SUBSTRACT    >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case BM_DIVIDE          :   Blend_select_AM< T, BM_DIVIDE       >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case BM_HUE             :   Blend_select_AM< T, BM_HUE          >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case BM_SATURATION      :   Blend_select_AM< T, BM_SATURATION   >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case BM_COLOR           :   Blend_select_AM< T, BM_COLOR        >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case BM_LUMINOSITY      :   Blend_select_AM< T, BM_LUMINOSITY   >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
    }
}
*/