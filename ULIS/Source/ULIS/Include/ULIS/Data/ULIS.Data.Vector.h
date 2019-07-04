/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Data.Vector.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once

#include <immintrin.h>
#include "ULIS/Data/ULIS.Data.Types.h"

namespace ULIS {
/////////////////////////////////////////////////////
// FVectorSIMD
struct alignas( 16 ) FVectorSIMD128
{
    union {
        float   f[4];
        uint8   u8[16];
        uint16  u16[8];
        uint32  u32[4];
        __m128  vecf;
        __m128i veci;
    };
};

} // namespace ULIS
