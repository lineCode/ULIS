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
void Blend( FThreadPool&    iPool
          , const FBlock*   iSource
          , FBlock*         iBackdrop
          , const FPoint&   iDstPos
          , eBlendingMode   iBlendingMode
          , eAlphaMode      iAlphaMode
          , float           iOpacity
          , const FPerf&    iPerf
          , bool            iCallInvalidCB )
{
    Blend( iPool
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


void Blend( FThreadPool&    iPool
          , const FBlock*   iSource
          , FBlock*         iBackdrop
          , const FRect&    iSrcRect
          , const FPoint&   iDstPos
          , eBlendingMode   iBlendingMode
          , eAlphaMode      iAlphaMode
          , float           iOpacity
          , const FPerf&    iPerf
          , bool            iCallInvalidCB )
{
    ULIS2_ASSERT( iSource->Model() == iBackdrop->Model(),                       "Models do not match" );
    ULIS2_ASSERT( iSource->Type() == iBackdrop->Type(),                         "Types do not match" );
    ULIS2_ASSERT( iSource->SamplesPerPixel() == iBackdrop->SamplesPerPixel(),   "Samples do not match" );

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

    iBackdrop->Invalidate( FRect(), iCallInvalidCB );
}

ULIS2_NAMESPACE_END

