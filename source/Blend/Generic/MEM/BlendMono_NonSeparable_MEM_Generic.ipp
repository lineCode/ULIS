// Copyright � 2018-2019 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         BlendMono_NonSeparable_MEM_Generic.ipp
* @author       Clement Berthaud
* @brief        This file provides the declaration for the generic Blend entry point functions.
* @copyright    Copyright � 2018-2019 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Base/Core.h"
#include "Maths/Geometry.h"
#include "Blend/Modes.h"
#include "Base/Perf.h"
#include "Color/ModelStructs.h"
#include "Blend/BlendHelpers.h"
#include "Blend/Generic/MEM/imp/BlendMono_NonSeparable_CM_DEFAULT_MEM_Generic.ipp"
#include "Blend/Generic/MEM/imp/BlendMono_NonSeparable_CM_Grey_MEM_Generic.ipp"
#include "Blend/Generic/MEM/imp/BlendMono_NonSeparable_CM_RGB_MEM_Generic.ipp"
#include "Blend/Generic/MEM/imp/BlendMono_NonSeparable_CM_CMYK_MEM_Generic.ipp"
#include "Blend/Generic/MEM/imp/BlendMono_NonSeparable_CM_Lab_MEM_Generic.ipp"

ULIS2_NAMESPACE_BEGIN
template< typename T >
void BlendMono_NonSeparable_MEM( const FBlock*      iSource
                               , FBlock*            iBackdrop
                               , const FRect&       iSrcRoi
                               , const FRect&       iDstRoi
                               , eBlendingMode      iBlendingMode
                               , const eAlphaMode   iAlphaMode
                               , const float        iOpacity )
{
    switch( iSource->Model() ) {
        case CM_ANY:    ULIS2_CRASH_DELIBERATE; return;
        case CM_GREY:   BlendMono_NonSeparable_CM_Grey_MEM<     T >( iSource, iBackdrop, iSrcRoi, iDstRoi, iBlendingMode, iAlphaMode, iOpacity ); break;
        case CM_RGB:    BlendMono_NonSeparable_CM_RGB_MEM<      T >( iSource, iBackdrop, iSrcRoi, iDstRoi, iBlendingMode, iAlphaMode, iOpacity ); break;
        case CM_CMYK:   BlendMono_NonSeparable_CM_CMYK_MEM<     T >( iSource, iBackdrop, iSrcRoi, iDstRoi, iBlendingMode, iAlphaMode, iOpacity ); break;
        case CM_Lab:    BlendMono_NonSeparable_CM_Lab_MEM<      T >( iSource, iBackdrop, iSrcRoi, iDstRoi, iBlendingMode, iAlphaMode, iOpacity ); break;
        default:        BlendMono_NonSeparable_CM_DEFAULT_MEM<  T >( iSource, iBackdrop, iSrcRoi, iDstRoi, iBlendingMode, iAlphaMode, iOpacity ); break;
    }
}


ULIS2_NAMESPACE_END
