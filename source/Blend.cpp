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
void Blend_mtd_sse_imp( FThreadPool&   iPool
                      , const FBlock*  iSource
                      , FBlock*        iBackdrop
                      , const FRect&   iRoi
                      , const FPoint&  iShift
                      , eBlendingMode  iBlendingMode
                      , eAlphaMode     iAlphaMode
                      , float          iOpacity
                      , const FPerf&   iPerf )
{
}

void Blend_mono_sse_imp( FThreadPool&   iPool
                       , const FBlock*  iSource
                       , FBlock*        iBackdrop
                       , const FRect&   iRoi
                       , const FPoint&  iShift
                       , eBlendingMode  iBlendingMode
                       , eAlphaMode     iAlphaMode
                       , float          iOpacity
                       , const FPerf&   iPerf )
{
    const tSize bpp  = iSource->BytesPerPixel();
    const tSize w    = iSource->Width();
    const tSize h    = iSource->Height();
    const tSize num  = iRoi.Area();
    const tByte* src = iSource->DataPtr();
    const tByte* bdp = iBackdrop->DataPtr();
    for( uint32 i = 0; i < num; ++i )
    {
        /*
        memcpy( dst, iSrc, bpp );
        dst += bpp;
        */
    }
}


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
    ULIS2_ASSERT( iSource->Model() == iBackdrop->Model(), "Models do not match" );
    ULIS2_ASSERT( iSource->Type() == iBackdrop->Type(), "Types do not match" );
    ULIS2_ASSERT( iSource->SamplesPerPixel() == iBackdrop->SamplesPerPixel(), "Samples do not match" );
    FRect dst_rect = iSourceRect;
    dst_rect.x = iDstX;
    dst_rect.y = iDstY;
    FPoint shift( -iDstX, -iDstY );
    FRect back_rect = iBackdrop->Rect();
    FRect roi = dst_rect & back_rect;

    if( roi.Area() <= 0 )
        return;

    if( iPerf.useMT )
        Blend_mtd_sse_imp( iPool, iSource, iBackdrop, roi, shift, iBlendingMode, iAlphaMode, iOpacity, iPerf );
    else
        Blend_mono_sse_imp( iPool, iSource, iBackdrop, roi, shift, iBlendingMode, iAlphaMode, iOpacity, iPerf );

    iBackdrop->Invalidate( FRect(), iCallInvalidCB );
}

ULIS2_NAMESPACE_END

