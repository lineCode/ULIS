/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Base.Types.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once

#include <stdint.h>

namespace ULIS {

/////////////////////////////////////////////////////
// Defines
#define RESTRICT    __restrict
#define FORCEINLINE __forceinline

/////////////////////////////////////////////////////
// Fundamental Typedefs
typedef uint8_t     uint8;
typedef uint16_t    uint16;
typedef uint32_t    uint32;
typedef uint64_t    uint64;
typedef int8_t      int8;
typedef int16_t     int16;
typedef int32_t     int32;
typedef int64_t     int64;
typedef uint32      typefield;
typedef uint8       typefieldId;
typedef bool        typefieldBit;
typedef const char* cstr;

} // namespace ULIS
