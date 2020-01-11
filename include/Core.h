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

#ifdef ULIS2_MSVC
    #define _CRT_SECURE_NO_WARNINGS 1
#endif // ULIS2_MSVC

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
// Export utility macros
#ifdef ULIS2_WIN
    #ifdef ULIS2_BUILD_SHARED
        #define ULIS2_API __declspec( dllexport )
    #elif defined ULIS2_DYNAMIC_LIBRARY
        #define ULIS2_API __declspec( dllimport )
    #else
        #define ULIS2_API
    #endif
#else
    #define ULIS2_API
#endif

/////////////////////////////////////////////////////
// Erors
#pragma warning(disable : 4251)     // Shut down dll interface warnings.
#pragma warning(disable : 26812)    // Shut non-class enum warnings.

/////////////////////////////////////////////////////
// Includes
#include <iostream>
#include <cstring>
#include <cstdint>

/////////////////////////////////////////////////////
// Define Namespaces
#define ULIS2_NAMESPACE_NAME        ULIS2
#define ULIS2_SHORT_NAMESPACE_NAME  ul2
#define ULIS2_NAMESPACE_BEGIN       namespace ULIS2_NAMESPACE_NAME {
#define ULIS2_NAMESPACE_END         }
#define ULIS2_FDECL_CLASS( i )      ULIS2_NAMESPACE_BEGIN class i ; ULIS2_NAMESPACE_END
#define ULIS2_FDECL_STRUCT( i )     ULIS2_NAMESPACE_BEGIN struct i ; ULIS2_NAMESPACE_END

/////////////////////////////////////////////////////
// Namespace alias
namespace ULIS2_NAMESPACE_NAME {}
namespace ULIS2_SHORT_NAMESPACE_NAME = ULIS2_NAMESPACE_NAME;

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
// Assert Behaviours
#ifdef ULIS2_DEBUG
    #define ULIS2_ASSERT( cond, log )  if( !( cond ) ) { std::cout << __FILE__ << " " << __FUNCTION__ << " " << __LINE__ << " " << "Assertion failed:" << log << std::endl; ULIS2_CRASH; }
#else
    #define ULIS2_ASSERT( cond, log )
#endif

#define ULIS2_WARNING( cond, log )  if( !( cond ) ) { std::cout << __FILE__ << " " << __FUNCTION__ << " " << __LINE__ << " " <<  "Warning: " << log << std::endl; }
#define ULIS2_ERROR( cond, log )  if( !( cond ) ) { std::cout << __FILE__ << " " << __FUNCTION__ << " " << __LINE__ << " " << "Error: " << log << std::endl; ULIS2_CRASH; }

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
typedef  uint32_t       tIndex;

// Forward Declarations
class FBlock;
struct FRect;

// Callback Typedefs
typedef void (*fpInvalidateFunction)( const FBlock* /* block */, void* /* info */, const FRect& /* rect */ );
typedef void (*fpCleanupFunction)( tByte* /* data */, void* /* info */ );
struct ULIS2_API FOnInvalid
{
    FOnInvalid()
        : execute( nullptr )
        , info( nullptr )
    {
    }

    FOnInvalid( fpInvalidateFunction iInvalidateFunction, void* iInvalidateInfo = nullptr )
        : execute( nullptr )
        , info( nullptr )
    {
    }

    void ExecuteIfBound( const FBlock* iBlock, const FRect& iRect ) const
    {
        if( execute )
            execute( iBlock, info, iRect );
    }

    fpInvalidateFunction    execute;
    void*                   info;
};


struct ULIS2_API FOnCleanup
{
    FOnCleanup()
        : execute( nullptr )
        , info( nullptr )
    {
    }

    FOnCleanup( fpCleanupFunction iCleanupFunction, void* iCleanupInfo = nullptr )
        : execute( nullptr )
        , info( nullptr )
    {
    }

    void ExecuteIfBound( tByte* iData ) const
    {
        if( execute )
            execute( iData, info );
    }

    fpCleanupFunction       execute;
    void*                   info;
};


// Models
enum eModelSig : uint8 {
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


#define GREY_G      0
#define GREY_A      1
#define RGB_R       0
#define RGB_G       1
#define RGB_B       2
#define RGB_A       3

// Type
enum eType : uint8 {
      kUint8    = 0x0
    , kUint16   = 0x1
    , kUint32   = 0x2
    , kFloat    = 0x3
    , kDouble   = 0x4
};

#define ULIS2_FOR_ALL_TYPES_DO( X ) \
    X( int8 )                       \
    X( int16 )                      \
    X( int32 )                      \
    X( int64 )                      \
    X( uint8 )                      \
    X( uint16 )                     \
    X( uint32 )                     \
    X( uint64 )                     \
    X( float )                      \
    X( double )

template< typename T > ULIS2_FORCEINLINE eType T42(void)    { return  eType::kUint8;    }
template<> ULIS2_FORCEINLINE eType T42< uint8 >()           { return  eType::kUint8;    }
template<> ULIS2_FORCEINLINE eType T42< uint16 >()          { return  eType::kUint16;   }
template<> ULIS2_FORCEINLINE eType T42< uint32 >()          { return  eType::kUint32;   }
template<> ULIS2_FORCEINLINE eType T42< float >()           { return  eType::kFloat;    }
template<> ULIS2_FORCEINLINE eType T42< double >()          { return  eType::kDouble;   }

ULIS2_NAMESPACE_END

//                         •   •   •   d   f   u32 u16 u8
#define ULIS2_TYPE_DEPTH 0b00000000000010000100010000100001
//                         •   •   •   |8  |4  |4  |2  |1
//                         •   •   •   |20 |16 |12 |8  |4
#define ULIS2_TYPE_DEPTH_MASK   0xF
#define ULIS2_TYPE_DEPTH_SHIFT  4

/////////////////////////////////////////////////////
// Pixel format
//
//          DYNAMIC EXTRA INFO      FIXED FORMAT INFO
//          32   28   24   20       16        8    4  0
//          1098 7654 3210 9876     543 21098 7654 3210
//          •••• •••• •••• ••••     ASR MMMMM CCCC TTTT
//    Example: RGBA8
//                                  100 00010 0011 0001
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

#define ULIS2_R_TYPE( i )       ( i & 0xF )
#define ULIS2_R_CHANNELS( i )   ( ( i >> 4 ) & 0x07 )
#define ULIS2_R_MODEL( i )      ( ( i >> 8 ) & 0x1F )
#define ULIS2_R_REVERSE( i )    ( ( i >> 13 ) & 0x1 )
#define ULIS2_R_SWAP( i )       ( ( i >> 14 ) & 0x1 )
#define ULIS2_R_RS( i )         ( ( i >> 13 ) & 0x3 )
#define ULIS2_R_ALPHA( i )      ( ( i >> 15 ) & 0x1 )

#define ULIS2_FORMAT_MASK_LO 0x0000FFFF
#define ULIS2_FORMAT_MASK_HI 0xFFFF0000

#define ULIS2_FORMAT_RGB8       ULIS2_W_TYPE( kUint8 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( kRGB )
#define ULIS2_FORMAT_BGR8       ULIS2_W_TYPE( kUint8 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( kRGB ) | ULIS2_W_REVERSE( true )
#define ULIS2_FORMAT_RGBA8      ULIS2_W_TYPE( kUint8 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( kRGB ) | ULIS2_W_ALPHA( true )
#define ULIS2_FORMAT_ABGR8      ULIS2_W_TYPE( kUint8 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( kRGB ) | ULIS2_W_ALPHA( true ) | ULIS2_W_REVERSE( true )
#define ULIS2_FORMAT_ARGB8      ULIS2_W_TYPE( kUint8 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( kRGB ) | ULIS2_W_ALPHA( true ) | ULIS2_W_SWAP( true )
#define ULIS2_FORMAT_BGRA8      ULIS2_W_TYPE( kUint8 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( kRGB ) | ULIS2_W_ALPHA( true ) | ULIS2_W_REVERSE( true ) | ULIS2_W_SWAP( true )
#define ULIS2_FORMAT_RGB16      ULIS2_W_TYPE( kUint16 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( kRGB )
#define ULIS2_FORMAT_BGR16      ULIS2_W_TYPE( kUint16 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( kRGB ) | ULIS2_W_REVERSE( true )
#define ULIS2_FORMAT_RGBA16     ULIS2_W_TYPE( kUint16 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( kRGB ) | ULIS2_W_ALPHA( true )
#define ULIS2_FORMAT_ABGR16     ULIS2_W_TYPE( kUint16 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( kRGB ) | ULIS2_W_ALPHA( true ) | ULIS2_W_REVERSE( true )
#define ULIS2_FORMAT_ARGB16     ULIS2_W_TYPE( kUint16 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( kRGB ) | ULIS2_W_ALPHA( true ) | ULIS2_W_SWAP( true )
#define ULIS2_FORMAT_BGRA16     ULIS2_W_TYPE( kUint16 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( kRGB ) | ULIS2_W_ALPHA( true ) | ULIS2_W_REVERSE( true ) | ULIS2_W_SWAP( true )
#define ULIS2_FORMAT_RGB32      ULIS2_W_TYPE( kUint32 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( kRGB )
#define ULIS2_FORMAT_BGR32      ULIS2_W_TYPE( kUint32 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( kRGB ) | ULIS2_W_REVERSE( true )
#define ULIS2_FORMAT_RGBA32     ULIS2_W_TYPE( kUint32 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( kRGB ) | ULIS2_W_ALPHA( true )
#define ULIS2_FORMAT_ABGR32     ULIS2_W_TYPE( kUint32 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( kRGB ) | ULIS2_W_ALPHA( true ) | ULIS2_W_REVERSE( true )
#define ULIS2_FORMAT_ARGB32     ULIS2_W_TYPE( kUint32 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( kRGB ) | ULIS2_W_ALPHA( true ) | ULIS2_W_SWAP( true )
#define ULIS2_FORMAT_BGRA32     ULIS2_W_TYPE( kUint32 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( kRGB ) | ULIS2_W_ALPHA( true ) | ULIS2_W_REVERSE( true ) | ULIS2_W_SWAP( true )
#define ULIS2_FORMAT_RGBF       ULIS2_W_TYPE( kFloat ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( kRGB )
#define ULIS2_FORMAT_BGRF       ULIS2_W_TYPE( kFloat ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( kRGB ) | ULIS2_W_REVERSE( true )
#define ULIS2_FORMAT_RGBAF      ULIS2_W_TYPE( kFloat ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( kRGB ) | ULIS2_W_ALPHA( true )
#define ULIS2_FORMAT_ABGRF      ULIS2_W_TYPE( kFloat ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( kRGB ) | ULIS2_W_ALPHA( true ) | ULIS2_W_REVERSE( true )
#define ULIS2_FORMAT_ARGBF      ULIS2_W_TYPE( kFloat ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( kRGB ) | ULIS2_W_ALPHA( true ) | ULIS2_W_SWAP( true )
#define ULIS2_FORMAT_BGRAF      ULIS2_W_TYPE( kFloat ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( kRGB ) | ULIS2_W_ALPHA( true ) | ULIS2_W_REVERSE( true ) | ULIS2_W_SWAP( true )
#define ULIS2_FORMAT_RGBD       ULIS2_W_TYPE( kDouble ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( kRGB )
#define ULIS2_FORMAT_BGRD       ULIS2_W_TYPE( kDouble ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( kRGB ) | ULIS2_W_REVERSE( true )
#define ULIS2_FORMAT_RGBAD      ULIS2_W_TYPE( kDouble ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( kRGB ) | ULIS2_W_ALPHA( true )
#define ULIS2_FORMAT_ABGRD      ULIS2_W_TYPE( kDouble ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( kRGB ) | ULIS2_W_ALPHA( true ) | ULIS2_W_REVERSE( true )
#define ULIS2_FORMAT_ARGBD      ULIS2_W_TYPE( kDouble ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( kRGB ) | ULIS2_W_ALPHA( true ) | ULIS2_W_SWAP( true )
#define ULIS2_FORMAT_BGRAD      ULIS2_W_TYPE( kDouble ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( kRGB ) | ULIS2_W_ALPHA( true ) | ULIS2_W_REVERSE( true ) | ULIS2_W_SWAP( true )

