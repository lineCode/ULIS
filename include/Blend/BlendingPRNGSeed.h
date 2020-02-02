// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         BlendingPRNGSeed.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the Blending PRNG Seed.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Base/Core.h"

ULIS2_NAMESPACE_BEGIN
// Per process global
// each dll / exe will have its own in case of static link
ULIS2_API extern uint32 gBlendingPRNGSeed;
ULIS2_API void SetDetermisticBlendingPRNGSeed( uint32 iValue );

ULIS2_NAMESPACE_END

