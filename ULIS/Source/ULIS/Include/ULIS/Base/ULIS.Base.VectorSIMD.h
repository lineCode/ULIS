/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Base.VectorSIMD.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once

#include <immintrin.h>
#include "ULIS/Base/ULIS.Base.BaseTypes.h"

namespace ULIS {
/////////////////////////////////////////////////////
// FVectorSIMD128
struct alignas( 16 ) FVectorSIMD128
{
    union {
        uint8   u8[16];
        uint16  u16[8];
        __m128i m128i;
    };
};

/////////////////////////////////////////////////////
// FDualVectorSIMD128
struct alignas( 16 ) FDualVectorSIMD128
{
    FVectorSIMD128 lo;
    FVectorSIMD128 hi;
};

} // namespace ULIS
