// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         BlendMono_NonSeparable_CM_DEFAULT_SSE4_2_Generic.ipp
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
#include "Blend/Func/NonSeparableBlendFuncF.ipp"
#include "Color/ModelStructs.h"
#include "Conv/Conv.h"
#include "Maths/Geometry.h"

ULIS2_NAMESPACE_BEGIN

ULIS2_BLENDSPEC_TEMPLATE_SIG void BlendMono_NonSeparable_CM_DEFAULT_SSE4_2_Subpixel( ULIS2_BLENDSPEC_PARAMS_SIG ) {
}

ULIS2_BLENDSPEC_TEMPLATE_SIG void BlendMono_NonSeparable_CM_DEFAULT_SSE4_2( ULIS2_BLENDSPEC_PARAMS_SIG ) {
}

ULIS2_NAMESPACE_END

