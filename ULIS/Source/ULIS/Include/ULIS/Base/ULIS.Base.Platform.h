/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Base.Platform.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once

namespace ULIS {
/////////////////////////////////////////////////////
// Platform defines

//#define ULIS_ENABLE_FORCEINLINE
#ifdef ULIS_ENABLE_FORCEINLINE
    #if defined(__clang__)
    #define ULIS_FORCEINLINE inline __attribute__ ((always_inline))
    #elif defined(__GNUC__) || defined(__GNUG__)
    #define ULIS_FORCEINLINE inline __attribute__ ((always_inline))
    #elif defined(_MSC_VER)
    #define ULIS_FORCEINLINE __forceinline
    #else
    #define ULIS_FORCEINLINE inline
    #endif
#else // ULIS_ENABLE_FORCEINLINE
    #define ULIS_FORCEINLINE inline
#endif // ULIS_ENABLE_FORCEINLINE

} // namespace ULIS

