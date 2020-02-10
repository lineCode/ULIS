// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Methods.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the resampling methods enums.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Base/Core.h"

ULIS2_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
// eResamplingMethod
enum eResamplingMethod
{
      INTERP_NN
    , INTERP_BILINEAR
    , INTERP_BICUBIC
    , INTERP_AREA
};

static const char* kwResamplingMethod[] =
{
      "NearestNeighbour"
    , "Bilinear"
    , "Bicubic"
    , "Area"
};

ULIS2_NAMESPACE_END

