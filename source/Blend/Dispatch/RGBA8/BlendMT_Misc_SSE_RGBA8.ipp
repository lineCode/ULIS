// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         BlendMT_Misc_SSE_RGBA8.ipp
* @author       Clement Berthaud
* @brief        This file provides the declaration for the RGBA8 Blend entry point functions.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Base/Core.h"
#include "Base/Helpers.ipp"
#include "Blend/BlendingPRNGSeed.h"
#include "Blend/Modes.h"
#include "Maths/Geometry.h"
#include "Thread/ParallelFor.h"

ULIS2_NAMESPACE_BEGIN
void
InvokeBlendMTProcessScanline_Misc_SSE_RGBA8_Subpixel( int32               iLINE
                                                    , const tByte*        iSRC
                                                    , tByte*              iBDP
                                                    , uint8*              iXIDT
                                                    , uint8               iBPC
                                                    , uint8               iNCC
                                                    , uint8               iHEA
                                                    , uint8               iSPP
                                                    , uint8               iBPP
                                                    , uint8               iAID
                                                    , tSize                iSRC_BPS
                                                    , const FRect&        iSrcROI
                                                    , const FRect&        iBdpROI
                                                    , const glm::vec2&    iSubpixelComponent
                                                    , eBlendingMode       iBlendingMode
                                                    , eAlphaMode          iAlphaMode
                                                    , ufloat              iOpacity )
{
}

void
BlendMT_Misc_SSE_RGBA8_Subpixel( FThreadPool*     iPool
                               , bool             iBlocking
                               , const FPerf&     iPerf
                               , const FBlock*    iSource
                               , FBlock*          iBackdrop
                               , const FRect&     iSrcROI
                               , const FRect&     iBdpROI
                               , const glm::vec2& iSubpixelComponent
                               , eBlendingMode    iBlendingMode
                               , eAlphaMode       iAlphaMode
                               , ufloat           iOpacity )
{
}

void
InvokeBlendMTProcessScanline_Misc_SSE_RGBA8( int32            iLINE
                                           , const tByte*     iSRC
                                           , tByte*           iBDP
                                           , uint8*           iXIDT
                                           , uint8            iBCP
                                           , uint8            iNCC
                                           , uint8            iHEA
                                           , uint8            iSPP
                                           , uint8            iBPP
                                           , uint8            iAID
                                           , tSize            iSRC_BPS
                                           , const FRect&     iSrcROI
                                           , const FRect&     iBdpROI
                                           , const glm::vec2& iSubpixelComponent
                                           , eBlendingMode    iBlendingMode
                                           , eAlphaMode       iAlphaMode
                                           , ufloat           iOpacity )
{
}

void
BlendMT_Misc_SSE_RGBA8( FThreadPool*      iPool
                      , bool              iBlocking
                      , const FPerf&      iPerf
                      , const FBlock*     iSource
                      , FBlock*           iBackdrop
                      , const FRect&      iSrcROI
                      , const FRect&      iBdpROI
                      , const glm::vec2&  iSubpixelComponent
                      , eBlendingMode     iBlendingMode
                      , eAlphaMode        iAlphaMode
                      , ufloat            iOpacity )
{
}

ULIS2_NAMESPACE_END

