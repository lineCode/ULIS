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

ULIS2_NAMESPACE_BEGIN
template< typename T, eBlendingMode _BM, eAlphaMode _AM >
void
Blend_T_BM_AM_imp( FThreadPool&     iPool
                 , const FBlock*    iSource
                 , FBlock*          iBackdrop
                 , const FRect&     iSrcRoi
                 , const FRect&     iDstRoi
                 , float            iOpacity
                 , const FPerf&     iPerf )
{
}


template< typename T, eBlendingMode _BM >
void
Blend_T_BM_imp( FThreadPool&    iPool
              , const FBlock*   iSource
              , FBlock*         iBackdrop
              , const FRect&    iSrcRoi
              , const FRect&    iDstRoi
              , eAlphaMode      iAlphaMode
              , float           iOpacity
              , const FPerf&    iPerf )
{
    switch( iAlphaMode ) {
        case eAlphaMode::kNormal:   Blend_T_BM_AM_imp< T, _BM, eAlphaMode::kNormal  >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iOpacity, iPerf ); break;
        case eAlphaMode::kErase:    Blend_T_BM_AM_imp< T, _BM, eAlphaMode::kErase   >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iOpacity, iPerf ); break;
        case eAlphaMode::kTop:      Blend_T_BM_AM_imp< T, _BM, eAlphaMode::kTop     >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iOpacity, iPerf ); break;
        case eAlphaMode::kBack:     Blend_T_BM_AM_imp< T, _BM, eAlphaMode::kBack    >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iOpacity, iPerf ); break;
        case eAlphaMode::kSub:      Blend_T_BM_AM_imp< T, _BM, eAlphaMode::kSub     >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iOpacity, iPerf ); break;
        case eAlphaMode::kAdd:      Blend_T_BM_AM_imp< T, _BM, eAlphaMode::kAdd     >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iOpacity, iPerf ); break;
        case eAlphaMode::kMul:      Blend_T_BM_AM_imp< T, _BM, eAlphaMode::kMul     >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iOpacity, iPerf ); break;
        case eAlphaMode::kMin:      Blend_T_BM_AM_imp< T, _BM, eAlphaMode::kMin     >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iOpacity, iPerf ); break;
        case eAlphaMode::kMax:      Blend_T_BM_AM_imp< T, _BM, eAlphaMode::kMax     >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iOpacity, iPerf ); break;
        case eAlphaMode::kInvMax:   Blend_T_BM_AM_imp< T, _BM, eAlphaMode::kInvMax  >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iOpacity, iPerf ); break;
    }
}


template< typename T >
void
Blend_T_imp( FThreadPool&   iPool
           , const FBlock*  iSource
           , FBlock*        iBackdrop
           , const FRect&   iSrcRoi
           , const FRect&   iDstRoi
           , eBlendingMode  iBlendingMode
           , eAlphaMode     iAlphaMode
           , float          iOpacity
           , const FPerf&   iPerf )
{
    switch( iBlendingMode )
    {
        case eBlendingMode::kNormal:        Blend_T_BM_imp< T, eBlendingMode::kNormal       >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case eBlendingMode::kErase:         Blend_T_BM_imp< T, eBlendingMode::kErase        >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case eBlendingMode::kBehind:        Blend_T_BM_imp< T, eBlendingMode::kBehind       >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case eBlendingMode::kDissolve:      Blend_T_BM_imp< T, eBlendingMode::kDissolve     >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case eBlendingMode::kDarken:        Blend_T_BM_imp< T, eBlendingMode::kDarken       >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case eBlendingMode::kMultiply:      Blend_T_BM_imp< T, eBlendingMode::kMultiply     >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case eBlendingMode::kColorBurn:     Blend_T_BM_imp< T, eBlendingMode::kColorBurn    >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case eBlendingMode::kLinearBurn:    Blend_T_BM_imp< T, eBlendingMode::kLinearBurn   >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case eBlendingMode::kDarkerColor:   Blend_T_BM_imp< T, eBlendingMode::kDarkerColor  >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case eBlendingMode::kLighten:       Blend_T_BM_imp< T, eBlendingMode::kLighten      >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case eBlendingMode::kScreen:        Blend_T_BM_imp< T, eBlendingMode::kScreen       >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case eBlendingMode::kColorDodge:    Blend_T_BM_imp< T, eBlendingMode::kColorDodge   >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case eBlendingMode::kLinearDodge:   Blend_T_BM_imp< T, eBlendingMode::kLinearDodge  >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case eBlendingMode::kLighterColor:  Blend_T_BM_imp< T, eBlendingMode::kLighterColor >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case eBlendingMode::kOverlay:       Blend_T_BM_imp< T, eBlendingMode::kOverlay      >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case eBlendingMode::kSoftLight:     Blend_T_BM_imp< T, eBlendingMode::kSoftLight    >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case eBlendingMode::kHardLight:     Blend_T_BM_imp< T, eBlendingMode::kHardLight    >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case eBlendingMode::kVividLight:    Blend_T_BM_imp< T, eBlendingMode::kVividLight   >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case eBlendingMode::kLinearLight:   Blend_T_BM_imp< T, eBlendingMode::kLinearLight  >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case eBlendingMode::kPinLight:      Blend_T_BM_imp< T, eBlendingMode::kPinLight     >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case eBlendingMode::kHardMix:       Blend_T_BM_imp< T, eBlendingMode::kHardMix      >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case eBlendingMode::kDifference:    Blend_T_BM_imp< T, eBlendingMode::kDifference   >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case eBlendingMode::kExclusion:     Blend_T_BM_imp< T, eBlendingMode::kExclusion    >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case eBlendingMode::kSubstract:     Blend_T_BM_imp< T, eBlendingMode::kSubstract    >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case eBlendingMode::kDivide:        Blend_T_BM_imp< T, eBlendingMode::kDivide       >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case eBlendingMode::kHue:           Blend_T_BM_imp< T, eBlendingMode::kHue          >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case eBlendingMode::kSaturation:    Blend_T_BM_imp< T, eBlendingMode::kSaturation   >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case eBlendingMode::kColor:         Blend_T_BM_imp< T, eBlendingMode::kColor        >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case eBlendingMode::kLuminosity:    Blend_T_BM_imp< T, eBlendingMode::kLuminosity   >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
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
    ULIS2_ASSERT( iSource,                                                      "Bad source" );
    ULIS2_ASSERT( iBackdrop,                                                    "Bad destination" );
    ULIS2_ASSERT( iSource != iBackdrop,                                         "Destination and source cannot be the same" );

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

    switch( iSource->Type() ) {
        case eType::kUint8:     Blend_T_imp< uint8  >( iPool, iSource, iBackdrop, src_roi, dst_roi, iBlendingMode, iAlphaMode, iOpacity, iPerf ); break;
        case eType::kUint16:    Blend_T_imp< uint16 >( iPool, iSource, iBackdrop, src_roi, dst_roi, iBlendingMode, iAlphaMode, iOpacity, iPerf ); break;
        case eType::kUint32:    Blend_T_imp< uint32 >( iPool, iSource, iBackdrop, src_roi, dst_roi, iBlendingMode, iAlphaMode, iOpacity, iPerf ); break;
        case eType::kFloat:     Blend_T_imp< float  >( iPool, iSource, iBackdrop, src_roi, dst_roi, iBlendingMode, iAlphaMode, iOpacity, iPerf ); break;
        case eType::kDouble:    Blend_T_imp< double >( iPool, iSource, iBackdrop, src_roi, dst_roi, iBlendingMode, iAlphaMode, iOpacity, iPerf ); break;
    }

    iBackdrop->Invalidate( dst_roi, iCallInvalidCB );
}

ULIS2_NAMESPACE_END

