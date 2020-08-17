// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS
*__________________
*
* @file         Blend.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the Blend entry point functions.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"
#include "Blend/Modes.h"

ULIS_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
// Blend
ULIS_API void Blend( FThreadPool*              iThreadPool
                    , bool                      iBlocking
                    , uint32                    iPerfIntent
                    , const FHostDeviceInfo&    iHostDeviceInfo
                    , bool                      iCallCB
                    , const FBlock*             iSource
                    , FBlock*                   iBackdrop
                    , const FRectI&              iSourceRect
                    , const FVec2F&             iPosition
                    , bool                      iSubpixelFlag
                    , eBlendingMode             iBlendingMode
                    , eAlphaMode                iAlphaMode
                    , float                     iOpacityValue );

/////////////////////////////////////////////////////
// AlphaBlend
ULIS_API void AlphaBlend( FThreadPool*             iThreadPool
                         , bool                     iBlocking
                         , uint32                   iPerfIntent
                         , const FHostDeviceInfo&   iHostDeviceInfo
                         , bool                     iCallCB
                         , const FBlock*            iSource
                         , FBlock*                  iBackdrop
                         , const FRectI&             iSourceRect
                         , const FVec2F&            iPosition
                         , bool                     iSubpixelFlag
                         , float                    iOpacityValue );

/////////////////////////////////////////////////////
// BlendTiled
ULIS_API void BlendTiled( FThreadPool*             iThreadPool
                         , bool                     iBlocking
                         , uint32                   iPerfIntent
                         , const FHostDeviceInfo&   iHostDeviceInfo
                         , bool                     iCallCB
                         , const FBlock*            iSource
                         , FBlock*                  iBackdrop
                         , const FRectI&             iSourceRect
                         , const FRectI&             iDestRect
                         , const FVec2I&            iShift
                         , eBlendingMode            iBlendingMode
                         , eAlphaMode               iAlphaMode
                         , float                    iOpacityValue );

/////////////////////////////////////////////////////
// BlendColor
ULIS_API void BlendColor( FThreadPool*             iThreadPool
                         , uint32                   iPerfIntent
                         , const FHostDeviceInfo&   iHostDeviceInfo
                         , bool                     iCallCB
                         , const FColor&       iColor
                         , FBlock*                  iBackdrop
                         , const FRectI&             iDestRect
                         , eBlendingMode            iBlendingMode
                         , eAlphaMode               iAlphaMode
                         , float                    iOpacityValue );

/////////////////////////////////////////////////////
// Blend PRNG for pseudo random modes like Dissolve
ULIS_API void ResetBlendPRNGSeed();
ULIS_API void SetBlendPRNGSeed( uint32 iVal );
ULIS_API uint32 GetBlendPRNGSeed();
ULIS_API uint32 GenerateBlendPRNG();

ULIS_NAMESPACE_END

