// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Texture.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the FBlock class.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Base/Core.h"
//#include <CL/cl.hpp>

ULIS2_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
/// @class      FTexture
/// @brief      The FTexture class provides a mean of storing and manipulating digital images in various formats on the GPU.
/// @details    FTexture differs from FBlock because FTexture resides in accelerator device memory, while FBlock stays on host CPU.
class ULIS2_API FTexture
{
};

ULIS2_NAMESPACE_END

