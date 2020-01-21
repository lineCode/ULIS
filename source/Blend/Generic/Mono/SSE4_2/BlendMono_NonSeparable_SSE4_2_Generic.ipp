// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         BlendMono_NonSeparable_SSE4_2_Generic.ipp
* @author       Clement Berthaud
* @brief        This file provides the declaration for the generic Blend entry point functions.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Base/Core.h"
#include "Blend/BlendHelpers.h"
#include "Blend/Modes.h"
#include "Blend/Func/AlphaFuncF.ipp"
#include "Color/ModelStructs.h"
#include "Maths/Geometry.h"
// Mono Non Separable Mem Generic
#include "Blend/Generic/Mono/SSE4_2/BlendMono_NonSeparable_CM_DEFAULT_SSE4_2_Generic.ipp"
#include "Blend/Generic/Mono/SSE4_2/BlendMono_NonSeparable_CM_Grey_SSE4_2_Generic.ipp"
#include "Blend/Generic/Mono/SSE4_2/BlendMono_NonSeparable_CM_RGB_SSE4_2_Generic.ipp"
#include "Blend/Generic/Mono/SSE4_2/BlendMono_NonSeparable_CM_CMYK_SSE4_2_Generic.ipp"
#include "Blend/Generic/Mono/SSE4_2/BlendMono_NonSeparable_CM_Lab_SSE4_2_Generic.ipp"

ULIS2_NAMESPACE_BEGIN
template< typename T >
void BlendMono_NonSeparable_SSE4_2( const FBlock*       iSource
                                  , FBlock*             iBackdrop
                                  , const glm::uvec2&   iSrcStart
                                  , const glm::uvec2&   iDstStart
                                  , const glm::uvec2&   iRoiSize
                                  , const glm::vec2&    iSubpixelComponent
                                  , eBlendingMode       iBlendingMode
                                  , const eAlphaMode    iAlphaMode
                                  , const float         iOpacity )
{
}

ULIS2_NAMESPACE_END

