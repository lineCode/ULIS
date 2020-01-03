// Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Core.h
* @author       Clement Berthaud
* @brief        This file provides core definitions for the ULIS2 library.
* @copyright    Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include <functional>
#include <string>
#include <cstring>
#include <stdint.h>

/////////////////////////////////////////////////////
// Detect Build Configuration
#ifdef NDEBUG
    #define ULIS2_RELEASE
#else // !NDEBUG
    #define ULIS2_DEBUG
#endif // !NDEBUG

/////////////////////////////////////////////////////
// Detect Compiler
#if defined(__clang__)
    #define ULIS2_CLANG
#elif defined(__GNUC__) || defined(__GNUG__)
    #define ULIS2_GCC
#elif defined(_MSC_VER)
    #define ULIS2_MSVC
#else
    #define ULIS2_UNKNOWN_COMPILER
#endif

/////////////////////////////////////////////////////
// Detect Platform
#ifdef _WIN32
    #define ULIS2_WIN
   #ifdef _WIN64
      #define ULIS2_WIN64
   #else
      #define ULIS2_WIN32
   #endif
#elif __APPLE__
    #include "TargetConditionals.h"
    #if TARGET_IPHONE_SIMULATOR
         #define ULIS2_IOS_SIMULATOR
    #elif TARGET_OS_IPHONE
        #define ULIS2_IOS_DEVICE
    #elif TARGET_OS_MAC
        #define ULIS2_MACOS
    #else
        #error "Unknown Apple platform"
    #endif
#elif __linux__
    #define ULIS2_LINUX
#elif __unix__
    #define ULIS2_UNIX
#elif defined(_POSIX_VERSION)
    #define ULIS2_POSIX
#else
    #error "Unknown Platform"
#endif

/////////////////////////////////////////////////////
// Force Inline Utility
#define ULIS2_ENABLE_FORCEINLINE
#ifdef ULIS2_ENABLE_FORCEINLINE
    #if defined(__clang__)
    #define ULIS2_FORCEINLINE inline __attribute__ ((always_inline))
    #elif defined(__GNUC__) || defined(__GNUG__)
    #define ULIS2_FORCEINLINE inline __attribute__ ((always_inline))
    #elif defined(_MSC_VER)
    #define ULIS2_FORCEINLINE __forceinline
    #else
    #define ULIS2_FORCEINLINE inline
    #endif
#else // ULIS2_ENABLE_FORCEINLINE
    #define ULIS2_FORCEINLINE inline
#endif // ULIS2_ENABLE_FORCEINLINE


/////////////////////////////////////////////////////
// Define Namespaces
#define ULIS2_NAMESPACE_NAME     ULIS2
#define ULIS2_NAMESPACE_BEGIN    namespace ULIS2_NAMESPACE_NAME {
#define ULIS2_NAMESPACE_END      }
#define ULIS2_FDECL( i ) ULIS2_NAMESPACE_BEGIN class i ; ULIS2_NAMESPACE_END

/////////////////////////////////////////////////////
// Namespace alias
namespace ULIS2_NAMESPACE_NAME {}
namespace ul2 = ULIS2_NAMESPACE_NAME;

/////////////////////////////////////////////////////
// Version Specification
#define ULIS2_VERSION_MAJOR      0
#define ULIS2_VERSION_MINOR      2
#define ULIS2_VERSION_MAJOR_STR  "0"
#define ULIS2_VERSION_MINOR_STR  "2"

/////////////////////////////////////////////////////
// Crash Behaviours
#define ULIS2_CRASH              *((int*)0) = 0
#define ULIS2_CRASH_DELIBERATE   ULIS2_CRASH
#define ULIS2_CRASH_TODO         ULIS2_CRASH
#define ULIS2_CRASH_CHECK        ULIS2_CRASH

/////////////////////////////////////////////////////
// glm FORCE extensions, before any glm related includes
#define GLM_FORCE_SSE42
#define GLM_FORCE_SSE41
#define GLM_FORCE_SSSE3
#define GLM_FORCE_SSE3
#define GLM_FORCE_SSE2
#define GLM_FORCE_SSE
#define GLM_FORCE_INTRINSICS

/////////////////////////////////////////////////////
// Typedefs and enums
ULIS2_NAMESPACE_BEGIN

typedef  uint8_t        uint8;
typedef  uint16_t       uint16;
typedef  uint32_t       uint32;
typedef  uint64_t       uint64;
typedef  int8_t         int8;
typedef  int16_t        int16;
typedef  int32_t        int32;
typedef  int64_t        int64;
typedef  unsigned int   uint;
typedef  uint8_t        tByte;
typedef  uint32_t       tFormat;
typedef  uint32_t       tSize;

// Forward Declarations
class FBlock;
struct FRect;

// Callback Typedefs
typedef std::function< void( FBlock*, const FRect& ) > FOnInvalid;
typedef std::function< void( tByte* ) > FOnCleanup;

// Models
enum class eModel : uint8 {
      kAny
    , kGrey
    , kRGB
    , kCMY
    , kCMYK
    , kYCbCr
    , kYUV
    , kXYZ
    , kLab
    , kYUVK
    , kHSV
    , kHSL
    , kYxy
};

// Types
enum class eType : uint8 {
      kUint8    = 0x1
    , kUint16   = 0x2
    , kUint32   = 0x4
    , kFloat    = 0x8
    , kDouble   = 0x10
};

//                         •   •   •   d   f   u32 u16 u8
#define ULIS2_TYPE_DEPTH 0b00000000000010000100010000100001
//                         •   •   •   |8  |4  |4  |2  |1
#define ULIS2_TYPE_DEPTH_MASK   0xF
#define ULIS2_TYPE_DEPTH_SHIFT  4

ULIS2_NAMESPACE_END

/////////////////////////////////////////////////////
// Pixel format
//
//          DYNAMIC EXTRA INFO      FIXED FORMAT INFO
//          32   28   24   20       16        8    4  0
//          1098 7654 3210 9876     543 21098 7654 3210
//          •••• •••• •••• ••••     ASR MMMMM CCCC TTTT
//
//    B: Bytes per sample
//    C: Num Channels
//    M: Model
//    S: Swap
//    R: Reverse
//    A: Alpha
//    T: Type
//    •: free space for dynamic extra info

#define ULIS2_W_TYPE( i )       ( i )
#define ULIS2_W_CHANNELS( i )   ( i << 4 )
#define ULIS2_W_MODEL( i )      ( i << 8 )
#define ULIS2_W_REVERSE( i )    ( i << 13 )
#define ULIS2_W_SWAP( i )       ( i << 14 )
#define ULIS2_W_ALPHA( i )      ( i << 15 )

#define ULIS2_R_TYPE( i )       ( i & 0x07 )
#define ULIS2_R_CHANNELS( i )   ( ( i >> 4 ) & 0x07 )
#define ULIS2_R_MODEL( i )      ( ( i >> 8 ) & 0x1F )
#define ULIS2_R_REVERSE( i )    ( ( i >> 13 ) & 0x1 )
#define ULIS2_R_SWAP( i )       ( ( i >> 14 ) & 0x1 )
#define ULIS2_R_ALPHA( i )      ( ( i >> 15 ) & 0x1 )

#define ULIS2_FORMAT_MASK_LO 0x0000FFFF
#define ULIS2_FORMAT_MASK_HI 0xFFFF0000
