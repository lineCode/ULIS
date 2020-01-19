// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         srgb2linear.h
* @author       Clement Berthaud
* @brief        This file provides the declarations for the srgb2linear functions.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Base/Core.h"

ULIS2_NAMESPACE_BEGIN
ULIS2_API ufloat    srgb2linear( ufloat iValue );
ULIS2_API ufloat    linear2srgb( ufloat iValue );
ULIS2_API uint8     fast_srgb2linearU8( uint8 iValue );
ULIS2_API uint8     fast_linear2srgbU8( uint8 iValue );
ULIS2_API ufloat    fast_srgb2linearF( uint8 iValue );
ULIS2_API ufloat    fast_linear2srgbF( uint8 iValue );
ULIS2_NAMESPACE_END

