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
        float   f[4];
        uint8   u8[16];
        uint16  u16[8];
        uint32  u32[4];
        __m128  m128f;
        __m128i m128i;
    };
};

} // namespace ULIS
