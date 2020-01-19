// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         PRNG.h
* @author       Clement Berthaud
* @brief        This file provides declaration for weak PRNG functions.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Base/Core.h"

ULIS2_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
// PRNG
/// @fn         ResetWeakPRNGSeed()
/// @brief      Reset the PRNG seed.
ULIS2_API void ResetWeakPRNGSeed();


/// @fn         GenerateWeakPRNG()
/// @brief      Reset the PRNG seed.
/// @return     An uint32 representing a pseudo random number beetween 0 and 65537.
ULIS2_API uint32 GenerateWeakPRNG();

ULIS2_NAMESPACE_END

