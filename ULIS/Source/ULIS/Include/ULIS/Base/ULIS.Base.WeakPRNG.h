/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Base.WeakPRNG.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once


#include "ULIS/Base/ULIS.Base.BaseTypes.h"


namespace ULIS {
/////////////////////////////////////////////////////
// Weak PRNG
static uint32 weakprngseed = 5323;
static inline void ResetPRNGSeed()
{
    weakprngseed = 5323;
}

static inline uint32 PRNG()
{
    weakprngseed = 8253729 * weakprngseed + 2396403;
    return weakprngseed % 65537;
}

} // ULIS

