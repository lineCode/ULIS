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
          , int             iDstX
          , int             iDstY
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
         , iDstX
         , iDstY
         , iBlendingMode
         , iAlphaMode
         , iOpacity
         , iPerf
         , iCallInvalidCB );
}


void Blend( FThreadPool&    iPool
          , const FBlock*   iSource
          , FBlock*         iBackdrop
          , const FRect&    iSourceRect
          , int             iDstX
          , int             iDstY
          , eBlendingMode   iBlendingMode
          , eAlphaMode      iAlphaMode
          , float           iOpacity
          , const FPerf&    iPerf
          , bool            iCallInvalidCB )
{
    FRect dst_rect = iSourceRect;
    dst_rect.x = iDstX;
    dst_rect.y = iDstY;
    FRect back_rect = iBackdrop->Rect();
    FRect roi = dst_rect & back_rect;

    if( roi.Area() <= 0 )
        return;

    iBackdrop->Invalidate( FRect(), iCallInvalidCB );
}


ULIS2_NAMESPACE_END

