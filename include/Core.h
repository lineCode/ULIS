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
// Typedefs
typedef  uint8_t                uint8;
typedef  uint16_t               uint16;
typedef  uint32_t               uint32;
typedef  uint64_t               uint64;
typedef  int8_t                 int8;
typedef  int16_t                int16;
typedef  int32_t                int32;
typedef  int64_t                int64;
typedef  unsigned int           uint;
typedef  uint8_t                tByte;
typedef  uint32_t               tFormat;
typedef  uint32_t               tSize;
typedef  uint32_t               tIndex;
typedef unsigned long long int  ullint;


// Fdecl
class FBlock;
class IBlock;
class IPixel;
class FPixelValue;
class FPixelProxy;
struct FRect;
struct FPoint;
class FThreadPool;

// Types
enum eType : uint8 {
      kUint8    = 0x0
    , kUint16   = 0x1
    , kUint32   = 0x2
    , kFloat    = 0x3
    , kDouble   = 0x4
};

// Models
enum eModelSig : uint8 {
      kAny
    , kGrey
    , kRGB
    , kHSV
    , kHSL
    , kCMY
    , kCMYK
    , kYUV
    , kLab
    , kXYZ
    , kYxy
};

// Macro for all types for template instanciation
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
template<> constexpr ULIS2_FORCEINLINE eType T42< uint8 >()           { return  eType::kUint8;    }
template<> constexpr ULIS2_FORCEINLINE eType T42< uint16 >()          { return  eType::kUint16;   }
template<> constexpr ULIS2_FORCEINLINE eType T42< uint32 >()          { return  eType::kUint32;   }
template<> constexpr ULIS2_FORCEINLINE eType T42< float >()           { return  eType::kFloat;    }
template<> constexpr ULIS2_FORCEINLINE eType T42< double >()          { return  eType::kDouble;   }


template< typename T >
static constexpr ULIS2_FORCEINLINE T _min( T iA, T iB ) {
    return  iA < iB ? iA : iB;
}

template< typename T >
static constexpr ULIS2_FORCEINLINE T _max( T iA, T iB ) {
    return  iA > iB ? iA : iB;
}

template< typename T >
static constexpr ULIS2_FORCEINLINE T _clamp( T iValue, T iMin, T iMax ) {
    return  _max( iMin, _min( iValue, iMax ) );
}


template< typename T1, typename T2 > constexpr T2 inline ConvType( T1 iValue ) { return (T2)iValue; }
template<> constexpr uint16   inline ConvType< uint8,  uint16 >( uint8 iValue  ) { return iValue * 0x101;                         }
template<> constexpr uint32   inline ConvType< uint8,  uint32 >( uint8 iValue  ) { return iValue * 0x1010101;                     }
template<> constexpr uint64   inline ConvType< uint8,  uint64 >( uint8 iValue  ) { return iValue * 0x10100000101;                 }
template<> constexpr uint32   inline ConvType< uint16, uint32 >( uint16 iValue ) { return iValue * 0x10001;                       }
template<> constexpr uint64   inline ConvType< uint16, uint64 >( uint16 iValue ) { return iValue * 0x1000100010001;               }
template<> constexpr uint64   inline ConvType< uint32, uint64 >( uint32 iValue ) { return iValue * 0x100000001;                   }
template<> constexpr uint8    inline ConvType< uint16, uint8  >( uint16 iValue ) { return ( iValue + 1 + ( iValue>>8 ) ) >> 8;    }
template<> constexpr uint8    inline ConvType< uint32, uint8  >( uint32 iValue ) { return iValue >> 24;                           }
template<> constexpr uint8    inline ConvType< uint64, uint8  >( uint64 iValue ) { return iValue >> 56;                           }
template<> constexpr uint16   inline ConvType< uint32, uint16 >( uint32 iValue ) { return ( iValue + 1 + ( iValue>>16 ) ) >> 16;  }
template<> constexpr uint16   inline ConvType< uint64, uint16 >( uint64 iValue ) { return iValue >> 48;                           }
template<> constexpr uint32   inline ConvType< uint64, uint32 >( uint64 iValue ) { return iValue >> 32;                           }
template<> constexpr float    inline ConvType< uint8,  float  >( uint8 iValue  ) { return iValue / (float)0xFF;                   }
template<> constexpr float    inline ConvType< uint16, float  >( uint16 iValue ) { return iValue / (float)0xFFFF;                 }
template<> constexpr float    inline ConvType< uint32, float  >( uint32 iValue ) { return iValue / (float)0xFFFFFFFF;             }
template<> constexpr float    inline ConvType< uint64, float  >( uint64 iValue ) { return iValue / (float)0xFFFFFFFFFFFFFFFF;     }
template<> constexpr double   inline ConvType< uint8,  double >( uint8 iValue  ) { return iValue / (double)0xFF;                  }
template<> constexpr double   inline ConvType< uint16, double >( uint16 iValue ) { return iValue / (double)0xFFFF;                }
template<> constexpr double   inline ConvType< uint32, double >( uint32 iValue ) { return iValue / (double)0xFFFFFFFF;            }
template<> constexpr double   inline ConvType< uint64, double >( uint64 iValue ) { return iValue / (double)0xFFFFFFFFFFFFFFFF;    }
template<> constexpr uint8    inline ConvType< float,  uint8  >( float iValue  ) { return uint8(  iValue * 0xFF               );  }
template<> constexpr uint16   inline ConvType< float,  uint16 >( float iValue  ) { return uint16( iValue * 0xFFFF             );  }
template<> constexpr uint32   inline ConvType< float,  uint32 >( float iValue  ) { return uint32( iValue * 0xFFFFFFFF         );  }
template<> constexpr uint64   inline ConvType< float,  uint64 >( float iValue  ) { return uint64( iValue * 0xFFFFFFFFFFFFFFFF );  }
template<> constexpr uint8    inline ConvType< double, uint8  >( double iValue ) { return uint8(  iValue * 0xFF               );  }
template<> constexpr uint16   inline ConvType< double, uint16 >( double iValue ) { return uint16( iValue * 0xFFFF             );  }
template<> constexpr uint32   inline ConvType< double, uint32 >( double iValue ) { return uint32( iValue * 0xFFFFFFFF         );  }
template<> constexpr uint64   inline ConvType< double, uint64 >( double iValue ) { return uint64( iValue * 0xFFFFFFFFFFFFFFFF );  }
template<> constexpr uint8    inline ConvType< int,  uint8  >( int iValue  ) { return _clamp( iValue, 0, (int)UINT8_MAX ); }
template<> constexpr uint16   inline ConvType< int,  uint16 >( int iValue  ) { return ConvType< uint8, uint16 >( (uint8)_clamp( iValue, 0, (int)UINT8_MAX ) ); }
template<> constexpr uint32   inline ConvType< int,  uint32 >( int iValue  ) { return ConvType< uint8, uint32 >( (uint8)_clamp( iValue, 0, (int)UINT8_MAX ) ); }
template<> constexpr float    inline ConvType< int,  float  >( int iValue  ) { return ConvType< uint8, float  >( (uint8)_clamp( iValue, 0, (int)UINT8_MAX ) ); }
template<> constexpr double   inline ConvType< int,  double >( int iValue  ) { return ConvType< uint8, double >( (uint8)_clamp( iValue, 0, (int)UINT8_MAX ) ); }

template< typename T > T constexpr inline MinType() { return T(0); }
template< typename T > T constexpr inline MaxType() { return T(1); }
template<> uint8  constexpr inline MaxType< uint8  >() { return UINT8_MAX;    }
template<> uint16 constexpr inline MaxType< uint16 >() { return UINT16_MAX;   }
template<> uint32 constexpr inline MaxType< uint32 >() { return UINT32_MAX;   }
template<> float  constexpr inline MaxType< float  >() { return 1.f;          }
template<> double constexpr inline MaxType< double >() { return 0.0;          }

constexpr uint8     operator "" _u8(  ullint i ) { return  (uint8)_clamp( i, (ullint)0, (ullint)UINT8_MAX ); }
constexpr uint16    operator "" _u16( ullint i ) { return  ConvType< uint8, uint16 >( (uint8)_clamp( i, (ullint)0, (ullint)UINT8_MAX ) ); }
constexpr uint32    operator "" _u32( ullint i ) { return  ConvType< uint8, uint32 >( (uint8)_clamp( i, (ullint)0, (ullint)UINT8_MAX ) ); }
constexpr uint64    operator "" _u64( ullint i ) { return  ConvType< uint8, uint64 >( (uint8)_clamp( i, (ullint)0, (ullint)UINT8_MAX ) ); }
constexpr float  fix8f() { return ( 128.0f / 255.0f ) - 0.5f; }
constexpr double fix8d() { return ( 128.0 / 255.0 ) - 0.5; }
struct __encodedlab_ab
{
    constexpr __encodedlab_ab( float i ) : m( i ) {}
    constexpr float operator-(){        return  _clamp( -m + 0.5f, 0.f, 1.f ); }
    constexpr float operator+(){        return  _clamp( +m + 0.5f, 0.f, 1.f ); }
    constexpr operator float() const {  return  _clamp( +m + 0.5f, 0.f, 1.f ); }
    float m;
};

constexpr float operator "" _L( ullint i) { return _clamp( i, (ullint)0, (ullint)100 ) / 100.f; }
constexpr __encodedlab_ab operator "" _a( ullint i) { return  __encodedlab_ab( _clamp( i, (ullint)0, (ullint)128 ) / 255.f ); }
constexpr __encodedlab_ab operator "" _b( ullint i) { return  __encodedlab_ab( _clamp( i, (ullint)0, (ullint)128 ) / 255.f ); }

ULIS2_NAMESPACE_END

/////////////////////////////////////////////////////
// Pixel format
//
//          DYNAMIC EXTRA INFO      FIXED FORMAT INFO
//          32   28   24   20       16        8    4  0
//          1098 7654 3210 9876     5432 1098 7654 3210
//          •••• •••• ••EE DDDD     ASRF MMMM CCCC TTTT
//    Example: RGBA8
//                                  1000 0010 0011 0001
//
//    B: Bytes per sample
//    C: Num Channels
//    M: Model
//    S: Swap
//    R: Reverse
//    A: Alpha
//    T: Type
//    F: Floating
//    E: Extra
//    •: free space for dynamic extra info
#define ULIS2_W_TYPE( i )       ( i )
#define ULIS2_W_CHANNELS( i )   ( i << 4 )
#define ULIS2_W_MODEL( i )      ( i << 8 )
#define ULIS2_W_FLOATING( i )   ( i << 12 )
#define ULIS2_W_REVERSE( i )    ( i << 13 )
#define ULIS2_W_SWAP( i )       ( i << 14 )
#define ULIS2_W_ALPHA( i )      ( i << 15 )
#define ULIS2_W_DEPTH( i )      ( i << 16 )
#define ULIS2_W_EXTRA( i )      ( i << 20 )

#define ULIS2_R_TYPE( i )       ( i & 0xF )
#define ULIS2_R_CHANNELS( i )   ( ( i >> 4 ) & 0xF )
#define ULIS2_R_MODEL( i )      ( ( i >> 8 ) & 0xF )
#define ULIS2_R_FLOATING( i )   ( ( i >> 12 ) & 0x1 )
#define ULIS2_R_REVERSE( i )    ( ( i >> 13 ) & 0x1 )
#define ULIS2_R_SWAP( i )       ( ( i >> 14 ) & 0x1 )
#define ULIS2_R_ALPHA( i )      ( ( i >> 15 ) & 0x1 )
#define ULIS2_R_DEPTH( i )      ( ( i >> 16 ) & 0xF )
#define ULIS2_R_RS( i )         ( ( i >> 13 ) & 0x3 )
#define ULIS2_R_EXTRA( i )      ( ( i >> 20 ) & 0x3 )

#define ULIS2_None          0
#define ULIS2_LinearGrey    1
#define ULIS2_sGrey         2
#define ULIS2_Grey2_2_D65   3
#define ULIS2_LinearRGB     4
#define ULIS2_sRGB          5
#define ULIS2_AdobeRGB      6
#define ULIS2_XYZD50        7
#define ULIS2_XYZD65        8
#define ULIS2_LabD50        9
#define ULIS2_LabD65        10
#define ULIS2_FORMAT_MASK_LO 0x000FFFFF
#define ULIS2_FORMAT_MASK_HI 0xFFF00000

/////////////////////////////////////////////////////
// All ~300 formats.
#define ULIS2_FORMAT_G8         ULIS2_W_TYPE( ::ul2::kUint8 ) | ULIS2_W_CHANNELS( 1 ) | ULIS2_W_MODEL( ::ul2::kGrey ) | ULIS2_W_DEPTH( 1 )
#define ULIS2_FORMAT_GA8        ULIS2_W_TYPE( ::ul2::kUint8 ) | ULIS2_W_CHANNELS( 1 ) | ULIS2_W_MODEL( ::ul2::kGrey ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_DEPTH( 1 )
#define ULIS2_FORMAT_AG8        ULIS2_W_TYPE( ::ul2::kUint8 ) | ULIS2_W_CHANNELS( 1 ) | ULIS2_W_MODEL( ::ul2::kGrey ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_DEPTH( 1 )
#define ULIS2_FORMAT_G16        ULIS2_W_TYPE( ::ul2::kUint16 ) | ULIS2_W_CHANNELS( 1 ) | ULIS2_W_MODEL( ::ul2::kGrey ) | ULIS2_W_DEPTH( 2 )
#define ULIS2_FORMAT_GA16       ULIS2_W_TYPE( ::ul2::kUint16 ) | ULIS2_W_CHANNELS( 1 ) | ULIS2_W_MODEL( ::ul2::kGrey ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_DEPTH( 2 )
#define ULIS2_FORMAT_AG16       ULIS2_W_TYPE( ::ul2::kUint16 ) | ULIS2_W_CHANNELS( 1 ) | ULIS2_W_MODEL( ::ul2::kGrey ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_DEPTH( 2 )
#define ULIS2_FORMAT_G32        ULIS2_W_TYPE( ::ul2::kUint32 ) | ULIS2_W_CHANNELS( 1 ) | ULIS2_W_MODEL( ::ul2::kGrey ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_GA32       ULIS2_W_TYPE( ::ul2::kUint32 ) | ULIS2_W_CHANNELS( 1 ) | ULIS2_W_MODEL( ::ul2::kGrey ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_AG32       ULIS2_W_TYPE( ::ul2::kUint32 ) | ULIS2_W_CHANNELS( 1 ) | ULIS2_W_MODEL( ::ul2::kGrey ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_GF         ULIS2_W_TYPE( ::ul2::kFloat ) | ULIS2_W_CHANNELS( 1 ) | ULIS2_W_MODEL( ::ul2::kGrey ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_GAF        ULIS2_W_TYPE( ::ul2::kFloat ) | ULIS2_W_CHANNELS( 1 ) | ULIS2_W_MODEL( ::ul2::kGrey ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_AGF        ULIS2_W_TYPE( ::ul2::kFloat ) | ULIS2_W_CHANNELS( 1 ) | ULIS2_W_MODEL( ::ul2::kGrey ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_GD         ULIS2_W_TYPE( ::ul2::kDouble ) | ULIS2_W_CHANNELS( 1 ) | ULIS2_W_MODEL( ::ul2::kGrey ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 8 )
#define ULIS2_FORMAT_GAD        ULIS2_W_TYPE( ::ul2::kDouble ) | ULIS2_W_CHANNELS( 1 ) | ULIS2_W_MODEL( ::ul2::kGrey ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 8 )
#define ULIS2_FORMAT_AGD        ULIS2_W_TYPE( ::ul2::kDouble ) | ULIS2_W_CHANNELS( 1 ) | ULIS2_W_MODEL( ::ul2::kGrey ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 8 )
#define ULIS2_FORMAT_RGB8       ULIS2_W_TYPE( ::ul2::kUint8 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kRGB ) | ULIS2_W_DEPTH( 1 )
#define ULIS2_FORMAT_BGR8       ULIS2_W_TYPE( ::ul2::kUint8 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kRGB ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_DEPTH( 1 )
#define ULIS2_FORMAT_RGBA8      ULIS2_W_TYPE( ::ul2::kUint8 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kRGB ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_DEPTH( 1 )
#define ULIS2_FORMAT_ABGR8      ULIS2_W_TYPE( ::ul2::kUint8 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kRGB ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_DEPTH( 1 )
#define ULIS2_FORMAT_ARGB8      ULIS2_W_TYPE( ::ul2::kUint8 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kRGB ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_DEPTH( 1 )
#define ULIS2_FORMAT_BGRA8      ULIS2_W_TYPE( ::ul2::kUint8 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kRGB ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_DEPTH( 1 )
#define ULIS2_FORMAT_RGB16      ULIS2_W_TYPE( ::ul2::kUint16 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kRGB ) | ULIS2_W_DEPTH( 2 )
#define ULIS2_FORMAT_BGR16      ULIS2_W_TYPE( ::ul2::kUint16 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kRGB ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_DEPTH( 2 )
#define ULIS2_FORMAT_RGBA16     ULIS2_W_TYPE( ::ul2::kUint16 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kRGB ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_DEPTH( 2 )
#define ULIS2_FORMAT_ABGR16     ULIS2_W_TYPE( ::ul2::kUint16 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kRGB ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_DEPTH( 2 )
#define ULIS2_FORMAT_ARGB16     ULIS2_W_TYPE( ::ul2::kUint16 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kRGB ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_DEPTH( 2 )
#define ULIS2_FORMAT_BGRA16     ULIS2_W_TYPE( ::ul2::kUint16 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kRGB ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_DEPTH( 2 )
#define ULIS2_FORMAT_RGB32      ULIS2_W_TYPE( ::ul2::kUint32 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kRGB ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_BGR32      ULIS2_W_TYPE( ::ul2::kUint32 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kRGB ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_RGBA32     ULIS2_W_TYPE( ::ul2::kUint32 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kRGB ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_ABGR32     ULIS2_W_TYPE( ::ul2::kUint32 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kRGB ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_ARGB32     ULIS2_W_TYPE( ::ul2::kUint32 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kRGB ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_BGRA32     ULIS2_W_TYPE( ::ul2::kUint32 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kRGB ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_RGBF       ULIS2_W_TYPE( ::ul2::kFloat ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kRGB ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_BGRF       ULIS2_W_TYPE( ::ul2::kFloat ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kRGB ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_RGBAF      ULIS2_W_TYPE( ::ul2::kFloat ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kRGB ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_ABGRF      ULIS2_W_TYPE( ::ul2::kFloat ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kRGB ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_ARGBF      ULIS2_W_TYPE( ::ul2::kFloat ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kRGB ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_BGRAF      ULIS2_W_TYPE( ::ul2::kFloat ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kRGB ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_RGBD       ULIS2_W_TYPE( ::ul2::kDouble ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kRGB ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 8 )
#define ULIS2_FORMAT_BGRD       ULIS2_W_TYPE( ::ul2::kDouble ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kRGB ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 8 )
#define ULIS2_FORMAT_RGBAD      ULIS2_W_TYPE( ::ul2::kDouble ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kRGB ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 8 )
#define ULIS2_FORMAT_ABGRD      ULIS2_W_TYPE( ::ul2::kDouble ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kRGB ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 8 )
#define ULIS2_FORMAT_ARGBD      ULIS2_W_TYPE( ::ul2::kDouble ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kRGB ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 8 )
#define ULIS2_FORMAT_BGRAD      ULIS2_W_TYPE( ::ul2::kDouble ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kRGB ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 8 )
#define ULIS2_FORMAT_HSV8       ULIS2_W_TYPE( ::ul2::kUint8 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kHSV ) | ULIS2_W_DEPTH( 1 )
#define ULIS2_FORMAT_VSH8       ULIS2_W_TYPE( ::ul2::kUint8 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kHSV ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_DEPTH( 1 )
#define ULIS2_FORMAT_HSVA8      ULIS2_W_TYPE( ::ul2::kUint8 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kHSV ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_DEPTH( 1 )
#define ULIS2_FORMAT_AVSH8      ULIS2_W_TYPE( ::ul2::kUint8 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kHSV ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_DEPTH( 1 )
#define ULIS2_FORMAT_AHSV8      ULIS2_W_TYPE( ::ul2::kUint8 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kHSV ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_DEPTH( 1 )
#define ULIS2_FORMAT_VSHA8      ULIS2_W_TYPE( ::ul2::kUint8 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kHSV ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_DEPTH( 1 )
#define ULIS2_FORMAT_HSV16      ULIS2_W_TYPE( ::ul2::kUint16 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kHSV ) | ULIS2_W_DEPTH( 2 )
#define ULIS2_FORMAT_VSH16      ULIS2_W_TYPE( ::ul2::kUint16 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kHSV ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_DEPTH( 2 )
#define ULIS2_FORMAT_HSVA16     ULIS2_W_TYPE( ::ul2::kUint16 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kHSV ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_DEPTH( 2 )
#define ULIS2_FORMAT_AVSH16     ULIS2_W_TYPE( ::ul2::kUint16 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kHSV ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_DEPTH( 2 )
#define ULIS2_FORMAT_AHSV16     ULIS2_W_TYPE( ::ul2::kUint16 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kHSV ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_DEPTH( 2 )
#define ULIS2_FORMAT_VSHA16     ULIS2_W_TYPE( ::ul2::kUint16 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kHSV ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_DEPTH( 2 )
#define ULIS2_FORMAT_HSV32      ULIS2_W_TYPE( ::ul2::kUint32 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kHSV ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_VSH32      ULIS2_W_TYPE( ::ul2::kUint32 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kHSV ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_HSVA32     ULIS2_W_TYPE( ::ul2::kUint32 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kHSV ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_AVSH32     ULIS2_W_TYPE( ::ul2::kUint32 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kHSV ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_AHSV32     ULIS2_W_TYPE( ::ul2::kUint32 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kHSV ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_VSHA32     ULIS2_W_TYPE( ::ul2::kUint32 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kHSV ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_HSVF       ULIS2_W_TYPE( ::ul2::kFloat ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kHSV ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_VSHF       ULIS2_W_TYPE( ::ul2::kFloat ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kHSV ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_HSVAF      ULIS2_W_TYPE( ::ul2::kFloat ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kHSV ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_AVSHF      ULIS2_W_TYPE( ::ul2::kFloat ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kHSV ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_AHSVF      ULIS2_W_TYPE( ::ul2::kFloat ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kHSV ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_VSHAF      ULIS2_W_TYPE( ::ul2::kFloat ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kHSV ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_HSVD       ULIS2_W_TYPE( ::ul2::kDouble ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kHSV ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 8 )
#define ULIS2_FORMAT_BVSH       ULIS2_W_TYPE( ::ul2::kDouble ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kHSV ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 8 )
#define ULIS2_FORMAT_HSVAD      ULIS2_W_TYPE( ::ul2::kDouble ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kHSV ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 8 )
#define ULIS2_FORMAT_AVSHD      ULIS2_W_TYPE( ::ul2::kDouble ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kHSV ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 8 )
#define ULIS2_FORMAT_AHSVD      ULIS2_W_TYPE( ::ul2::kDouble ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kHSV ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 8 )
#define ULIS2_FORMAT_VSHAD      ULIS2_W_TYPE( ::ul2::kDouble ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kHSV ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 8 )
#define ULIS2_FORMAT_HSL8       ULIS2_W_TYPE( ::ul2::kUint8 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kHSL ) | ULIS2_W_DEPTH( 1 )
#define ULIS2_FORMAT_LSH8       ULIS2_W_TYPE( ::ul2::kUint8 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kHSL ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_DEPTH( 1 )
#define ULIS2_FORMAT_HSLA8      ULIS2_W_TYPE( ::ul2::kUint8 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kHSL ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_DEPTH( 1 )
#define ULIS2_FORMAT_ALSH8      ULIS2_W_TYPE( ::ul2::kUint8 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kHSL ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_DEPTH( 1 )
#define ULIS2_FORMAT_AHSL8      ULIS2_W_TYPE( ::ul2::kUint8 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kHSL ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_DEPTH( 1 )
#define ULIS2_FORMAT_LSHA8      ULIS2_W_TYPE( ::ul2::kUint8 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kHSL ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_DEPTH( 1 )
#define ULIS2_FORMAT_HSL16      ULIS2_W_TYPE( ::ul2::kUint16 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kHSL ) | ULIS2_W_DEPTH( 2 )
#define ULIS2_FORMAT_LSH16      ULIS2_W_TYPE( ::ul2::kUint16 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kHSL ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_DEPTH( 2 )
#define ULIS2_FORMAT_HSLA16     ULIS2_W_TYPE( ::ul2::kUint16 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kHSL ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_DEPTH( 2 )
#define ULIS2_FORMAT_ALSH16     ULIS2_W_TYPE( ::ul2::kUint16 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kHSL ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_DEPTH( 2 )
#define ULIS2_FORMAT_AHSL16     ULIS2_W_TYPE( ::ul2::kUint16 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kHSL ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_DEPTH( 2 )
#define ULIS2_FORMAT_LSHA16     ULIS2_W_TYPE( ::ul2::kUint16 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kHSL ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_DEPTH( 2 )
#define ULIS2_FORMAT_HSL32      ULIS2_W_TYPE( ::ul2::kUint32 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kHSL ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_LSH32      ULIS2_W_TYPE( ::ul2::kUint32 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kHSL ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_HSLA32     ULIS2_W_TYPE( ::ul2::kUint32 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kHSL ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_ALSH32     ULIS2_W_TYPE( ::ul2::kUint32 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kHSL ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_AHSL32     ULIS2_W_TYPE( ::ul2::kUint32 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kHSL ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_LSHA32     ULIS2_W_TYPE( ::ul2::kUint32 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kHSL ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_HSLF       ULIS2_W_TYPE( ::ul2::kFloat ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kHSL ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_LSHF       ULIS2_W_TYPE( ::ul2::kFloat ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kHSL ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_HSLAF      ULIS2_W_TYPE( ::ul2::kFloat ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kHSL ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_ALSHF      ULIS2_W_TYPE( ::ul2::kFloat ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kHSL ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_AHSLF      ULIS2_W_TYPE( ::ul2::kFloat ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kHSL ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_LSHAF      ULIS2_W_TYPE( ::ul2::kFloat ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kHSL ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_HSLD       ULIS2_W_TYPE( ::ul2::kDouble ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kHSL ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 8 )
#define ULIS2_FORMAT_BLSH       ULIS2_W_TYPE( ::ul2::kDouble ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kHSL ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 8 )
#define ULIS2_FORMAT_HSLAD      ULIS2_W_TYPE( ::ul2::kDouble ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kHSL ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 8 )
#define ULIS2_FORMAT_ALSHD      ULIS2_W_TYPE( ::ul2::kDouble ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kHSL ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 8 )
#define ULIS2_FORMAT_AHSLD      ULIS2_W_TYPE( ::ul2::kDouble ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kHSL ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 8 )
#define ULIS2_FORMAT_LSHAD      ULIS2_W_TYPE( ::ul2::kDouble ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kHSL ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 8 )
#define ULIS2_FORMAT_CMY8       ULIS2_W_TYPE( ::ul2::kUint8 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kCMY ) | ULIS2_W_DEPTH( 1 )
#define ULIS2_FORMAT_YMC8       ULIS2_W_TYPE( ::ul2::kUint8 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kCMY ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_DEPTH( 1 )
#define ULIS2_FORMAT_CMYA8      ULIS2_W_TYPE( ::ul2::kUint8 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kCMY ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_DEPTH( 1 )
#define ULIS2_FORMAT_AYMC8      ULIS2_W_TYPE( ::ul2::kUint8 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kCMY ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_DEPTH( 1 )
#define ULIS2_FORMAT_ACMY8      ULIS2_W_TYPE( ::ul2::kUint8 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kCMY ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_DEPTH( 1 )
#define ULIS2_FORMAT_YMCA8      ULIS2_W_TYPE( ::ul2::kUint8 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kCMY ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_DEPTH( 1 )
#define ULIS2_FORMAT_CMY16      ULIS2_W_TYPE( ::ul2::kUint16 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kCMY ) | ULIS2_W_DEPTH( 2 )
#define ULIS2_FORMAT_YMC16      ULIS2_W_TYPE( ::ul2::kUint16 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kCMY ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_DEPTH( 2 )
#define ULIS2_FORMAT_CMYA16     ULIS2_W_TYPE( ::ul2::kUint16 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kCMY ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_DEPTH( 2 )
#define ULIS2_FORMAT_AYMC16     ULIS2_W_TYPE( ::ul2::kUint16 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kCMY ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_DEPTH( 2 )
#define ULIS2_FORMAT_ACMY16     ULIS2_W_TYPE( ::ul2::kUint16 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kCMY ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_DEPTH( 2 )
#define ULIS2_FORMAT_YMCA16     ULIS2_W_TYPE( ::ul2::kUint16 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kCMY ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_DEPTH( 2 )
#define ULIS2_FORMAT_CMY32      ULIS2_W_TYPE( ::ul2::kUint32 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kCMY ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_YMC32      ULIS2_W_TYPE( ::ul2::kUint32 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kCMY ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_CMYA32     ULIS2_W_TYPE( ::ul2::kUint32 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kCMY ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_AYMC32     ULIS2_W_TYPE( ::ul2::kUint32 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kCMY ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_ACMY32     ULIS2_W_TYPE( ::ul2::kUint32 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kCMY ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_YMCA32     ULIS2_W_TYPE( ::ul2::kUint32 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kCMY ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_CMYF       ULIS2_W_TYPE( ::ul2::kFloat ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kCMY ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_YMCF       ULIS2_W_TYPE( ::ul2::kFloat ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kCMY ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_CMYAF      ULIS2_W_TYPE( ::ul2::kFloat ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kCMY ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_AYMCF      ULIS2_W_TYPE( ::ul2::kFloat ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kCMY ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_ACMYF      ULIS2_W_TYPE( ::ul2::kFloat ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kCMY ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_YMCAF      ULIS2_W_TYPE( ::ul2::kFloat ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kCMY ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_CMYD       ULIS2_W_TYPE( ::ul2::kDouble ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kCMY ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 8 )
#define ULIS2_FORMAT_BYMC       ULIS2_W_TYPE( ::ul2::kDouble ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kCMY ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 8 )
#define ULIS2_FORMAT_CMYAD      ULIS2_W_TYPE( ::ul2::kDouble ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kCMY ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 8 )
#define ULIS2_FORMAT_AYMCD      ULIS2_W_TYPE( ::ul2::kDouble ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kCMY ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 8 )
#define ULIS2_FORMAT_ACMYD      ULIS2_W_TYPE( ::ul2::kDouble ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kCMY ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 8 )
#define ULIS2_FORMAT_YMCAD      ULIS2_W_TYPE( ::ul2::kDouble ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kCMY ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 8 )
#define ULIS2_FORMAT_CMYK8      ULIS2_W_TYPE( ::ul2::kUint8 ) | ULIS2_W_CHANNELS( 4 ) | ULIS2_W_MODEL( ::ul2::kCMYK ) | ULIS2_W_DEPTH( 1 )
#define ULIS2_FORMAT_KCMY8      ULIS2_W_TYPE( ::ul2::kUint8 ) | ULIS2_W_CHANNELS( 4 ) | ULIS2_W_MODEL( ::ul2::kCMYK ) | ULIS2_W_DEPTH( 1 ) | ULIS2_W_SWAP( 1 )
#define ULIS2_FORMAT_KYMC8      ULIS2_W_TYPE( ::ul2::kUint8 ) | ULIS2_W_CHANNELS( 4 ) | ULIS2_W_MODEL( ::ul2::kCMYK ) | ULIS2_W_DEPTH( 1 ) | ULIS2_W_REVERSE( 1 )
#define ULIS2_FORMAT_YMCK8      ULIS2_W_TYPE( ::ul2::kUint8 ) | ULIS2_W_CHANNELS( 4 ) | ULIS2_W_MODEL( ::ul2::kCMYK ) | ULIS2_W_DEPTH( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_SWAP( 1 )
#define ULIS2_FORMAT_CMYKA8     ULIS2_W_TYPE( ::ul2::kUint8 ) | ULIS2_W_CHANNELS( 4 ) | ULIS2_W_MODEL( ::ul2::kCMYK ) | ULIS2_W_DEPTH( 1 ) | ULIS2_W_ALPHA( 1 )
#define ULIS2_FORMAT_ACMYK8     ULIS2_W_TYPE( ::ul2::kUint8 ) | ULIS2_W_CHANNELS( 4 ) | ULIS2_W_MODEL( ::ul2::kCMYK ) | ULIS2_W_DEPTH( 1 ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_SWAP( 1 )
#define ULIS2_FORMAT_AKYMC8     ULIS2_W_TYPE( ::ul2::kUint8 ) | ULIS2_W_CHANNELS( 4 ) | ULIS2_W_MODEL( ::ul2::kCMYK ) | ULIS2_W_DEPTH( 1 ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 )
#define ULIS2_FORMAT_KYMCA8     ULIS2_W_TYPE( ::ul2::kUint8 ) | ULIS2_W_CHANNELS( 4 ) | ULIS2_W_MODEL( ::ul2::kCMYK ) | ULIS2_W_DEPTH( 1 ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_SWAP( 1 )
#define ULIS2_FORMAT_CMYK16     ULIS2_W_TYPE( ::ul2::kUint16 ) | ULIS2_W_CHANNELS( 4 ) | ULIS2_W_MODEL( ::ul2::kCMYK ) | ULIS2_W_DEPTH( 2 )
#define ULIS2_FORMAT_KCMY16     ULIS2_W_TYPE( ::ul2::kUint16 ) | ULIS2_W_CHANNELS( 4 ) | ULIS2_W_MODEL( ::ul2::kCMYK ) | ULIS2_W_DEPTH( 2 ) | ULIS2_W_SWAP( 1 )
#define ULIS2_FORMAT_KYMC16     ULIS2_W_TYPE( ::ul2::kUint16 ) | ULIS2_W_CHANNELS( 4 ) | ULIS2_W_MODEL( ::ul2::kCMYK ) | ULIS2_W_DEPTH( 2 ) | ULIS2_W_REVERSE( 1 )
#define ULIS2_FORMAT_YMCK16     ULIS2_W_TYPE( ::ul2::kUint16 ) | ULIS2_W_CHANNELS( 4 ) | ULIS2_W_MODEL( ::ul2::kCMYK ) | ULIS2_W_DEPTH( 2 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_SWAP( 1 )
#define ULIS2_FORMAT_CMYKA16    ULIS2_W_TYPE( ::ul2::kUint16 ) | ULIS2_W_CHANNELS( 4 ) | ULIS2_W_MODEL( ::ul2::kCMYK ) | ULIS2_W_DEPTH( 2 ) | ULIS2_W_ALPHA( 1 )
#define ULIS2_FORMAT_ACMYK16    ULIS2_W_TYPE( ::ul2::kUint16 ) | ULIS2_W_CHANNELS( 4 ) | ULIS2_W_MODEL( ::ul2::kCMYK ) | ULIS2_W_DEPTH( 2 ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_SWAP( 1 )
#define ULIS2_FORMAT_AKYMC16    ULIS2_W_TYPE( ::ul2::kUint16 ) | ULIS2_W_CHANNELS( 4 ) | ULIS2_W_MODEL( ::ul2::kCMYK ) | ULIS2_W_DEPTH( 2 ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 )
#define ULIS2_FORMAT_KYMCA16    ULIS2_W_TYPE( ::ul2::kUint16 ) | ULIS2_W_CHANNELS( 4 ) | ULIS2_W_MODEL( ::ul2::kCMYK ) | ULIS2_W_DEPTH( 2 ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_SWAP( 1 )
#define ULIS2_FORMAT_CMYK32     ULIS2_W_TYPE( ::ul2::kUint32 ) | ULIS2_W_CHANNELS( 4 ) | ULIS2_W_MODEL( ::ul2::kCMYK ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_KCMY32     ULIS2_W_TYPE( ::ul2::kUint32 ) | ULIS2_W_CHANNELS( 4 ) | ULIS2_W_MODEL( ::ul2::kCMYK ) | ULIS2_W_DEPTH( 4 ) | ULIS2_W_SWAP( 1 )
#define ULIS2_FORMAT_KYMC32     ULIS2_W_TYPE( ::ul2::kUint32 ) | ULIS2_W_CHANNELS( 4 ) | ULIS2_W_MODEL( ::ul2::kCMYK ) | ULIS2_W_DEPTH( 4 ) | ULIS2_W_REVERSE( 1 )
#define ULIS2_FORMAT_YMCK32     ULIS2_W_TYPE( ::ul2::kUint32 ) | ULIS2_W_CHANNELS( 4 ) | ULIS2_W_MODEL( ::ul2::kCMYK ) | ULIS2_W_DEPTH( 4 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_SWAP( 1 )
#define ULIS2_FORMAT_CMYKA32    ULIS2_W_TYPE( ::ul2::kUint32 ) | ULIS2_W_CHANNELS( 4 ) | ULIS2_W_MODEL( ::ul2::kCMYK ) | ULIS2_W_DEPTH( 4 ) | ULIS2_W_ALPHA( 1 )
#define ULIS2_FORMAT_ACMYK32    ULIS2_W_TYPE( ::ul2::kUint32 ) | ULIS2_W_CHANNELS( 4 ) | ULIS2_W_MODEL( ::ul2::kCMYK ) | ULIS2_W_DEPTH( 4 ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_SWAP( 1 )
#define ULIS2_FORMAT_AKYMC32    ULIS2_W_TYPE( ::ul2::kUint32 ) | ULIS2_W_CHANNELS( 4 ) | ULIS2_W_MODEL( ::ul2::kCMYK ) | ULIS2_W_DEPTH( 4 ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 )
#define ULIS2_FORMAT_KYMCA32    ULIS2_W_TYPE( ::ul2::kUint32 ) | ULIS2_W_CHANNELS( 4 ) | ULIS2_W_MODEL( ::ul2::kCMYK ) | ULIS2_W_DEPTH( 4 ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_SWAP( 1 )
#define ULIS2_FORMAT_CMYKF      ULIS2_W_TYPE( ::ul2::kFloat ) | ULIS2_W_CHANNELS( 4 ) | ULIS2_W_MODEL( ::ul2::kCMYK ) | ULIS2_W_DEPTH( 4 ) | ULIS2_W_FLOATING( 1 )
#define ULIS2_FORMAT_KCMYF      ULIS2_W_TYPE( ::ul2::kFloat ) | ULIS2_W_CHANNELS( 4 ) | ULIS2_W_MODEL( ::ul2::kCMYK ) | ULIS2_W_DEPTH( 4 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_FLOATING( 1 )
#define ULIS2_FORMAT_KYMCF      ULIS2_W_TYPE( ::ul2::kFloat ) | ULIS2_W_CHANNELS( 4 ) | ULIS2_W_MODEL( ::ul2::kCMYK ) | ULIS2_W_DEPTH( 4 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_FLOATING( 1 )
#define ULIS2_FORMAT_YMCKF      ULIS2_W_TYPE( ::ul2::kFloat ) | ULIS2_W_CHANNELS( 4 ) | ULIS2_W_MODEL( ::ul2::kCMYK ) | ULIS2_W_DEPTH( 4 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_FLOATING( 1 )
#define ULIS2_FORMAT_CMYKAF     ULIS2_W_TYPE( ::ul2::kFloat ) | ULIS2_W_CHANNELS( 4 ) | ULIS2_W_MODEL( ::ul2::kCMYK ) | ULIS2_W_DEPTH( 4 ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_FLOATING( 1 )
#define ULIS2_FORMAT_ACMYKF     ULIS2_W_TYPE( ::ul2::kFloat ) | ULIS2_W_CHANNELS( 4 ) | ULIS2_W_MODEL( ::ul2::kCMYK ) | ULIS2_W_DEPTH( 4 ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_FLOATING( 1 )
#define ULIS2_FORMAT_AKYMCF     ULIS2_W_TYPE( ::ul2::kFloat ) | ULIS2_W_CHANNELS( 4 ) | ULIS2_W_MODEL( ::ul2::kCMYK ) | ULIS2_W_DEPTH( 4 ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_FLOATING( 1 )
#define ULIS2_FORMAT_KYMCAF     ULIS2_W_TYPE( ::ul2::kFloat ) | ULIS2_W_CHANNELS( 4 ) | ULIS2_W_MODEL( ::ul2::kCMYK ) | ULIS2_W_DEPTH( 4 ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_FLOATING( 1 )
#define ULIS2_FORMAT_CMYKD      ULIS2_W_TYPE( ::ul2::kDouble ) | ULIS2_W_CHANNELS( 4 ) | ULIS2_W_MODEL( ::ul2::kCMYK ) | ULIS2_W_DEPTH( 8 ) | ULIS2_W_FLOATING( 1 )
#define ULIS2_FORMAT_KCMYD      ULIS2_W_TYPE( ::ul2::kDouble ) | ULIS2_W_CHANNELS( 4 ) | ULIS2_W_MODEL( ::ul2::kCMYK ) | ULIS2_W_DEPTH( 8 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_FLOATING( 1 )
#define ULIS2_FORMAT_KYMCD      ULIS2_W_TYPE( ::ul2::kDouble ) | ULIS2_W_CHANNELS( 4 ) | ULIS2_W_MODEL( ::ul2::kCMYK ) | ULIS2_W_DEPTH( 8 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_FLOATING( 1 )
#define ULIS2_FORMAT_YMCKD      ULIS2_W_TYPE( ::ul2::kDouble ) | ULIS2_W_CHANNELS( 4 ) | ULIS2_W_MODEL( ::ul2::kCMYK ) | ULIS2_W_DEPTH( 8 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_FLOATING( 1 )
#define ULIS2_FORMAT_CMYKAD     ULIS2_W_TYPE( ::ul2::kDouble ) | ULIS2_W_CHANNELS( 4 ) | ULIS2_W_MODEL( ::ul2::kCMYK ) | ULIS2_W_DEPTH( 8 ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_FLOATING( 1 )
#define ULIS2_FORMAT_ACMYKD     ULIS2_W_TYPE( ::ul2::kDouble ) | ULIS2_W_CHANNELS( 4 ) | ULIS2_W_MODEL( ::ul2::kCMYK ) | ULIS2_W_DEPTH( 8 ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_FLOATING( 1 )
#define ULIS2_FORMAT_AKYMCD     ULIS2_W_TYPE( ::ul2::kDouble ) | ULIS2_W_CHANNELS( 4 ) | ULIS2_W_MODEL( ::ul2::kCMYK ) | ULIS2_W_DEPTH( 8 ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_FLOATING( 1 )
#define ULIS2_FORMAT_KYMCAD     ULIS2_W_TYPE( ::ul2::kDouble ) | ULIS2_W_CHANNELS( 4 ) | ULIS2_W_MODEL( ::ul2::kCMYK ) | ULIS2_W_DEPTH( 8 ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_FLOATING( 1 )
#define ULIS2_FORMAT_YUV8       ULIS2_W_TYPE( ::ul2::kUint8 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kYUV ) | ULIS2_W_DEPTH( 1 )
#define ULIS2_FORMAT_VUY8       ULIS2_W_TYPE( ::ul2::kUint8 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kYUV ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_DEPTH( 1 )
#define ULIS2_FORMAT_YUVA8      ULIS2_W_TYPE( ::ul2::kUint8 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kYUV ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_DEPTH( 1 )
#define ULIS2_FORMAT_AVUY8      ULIS2_W_TYPE( ::ul2::kUint8 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kYUV ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_DEPTH( 1 )
#define ULIS2_FORMAT_AYUV8      ULIS2_W_TYPE( ::ul2::kUint8 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kYUV ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_DEPTH( 1 )
#define ULIS2_FORMAT_VUYA8      ULIS2_W_TYPE( ::ul2::kUint8 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kYUV ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_DEPTH( 1 )
#define ULIS2_FORMAT_YUV16      ULIS2_W_TYPE( ::ul2::kUint16 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kYUV ) | ULIS2_W_DEPTH( 2 )
#define ULIS2_FORMAT_VUY16      ULIS2_W_TYPE( ::ul2::kUint16 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kYUV ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_DEPTH( 2 )
#define ULIS2_FORMAT_YUVA16     ULIS2_W_TYPE( ::ul2::kUint16 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kYUV ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_DEPTH( 2 )
#define ULIS2_FORMAT_AVUY16     ULIS2_W_TYPE( ::ul2::kUint16 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kYUV ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_DEPTH( 2 )
#define ULIS2_FORMAT_AYUV16     ULIS2_W_TYPE( ::ul2::kUint16 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kYUV ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_DEPTH( 2 )
#define ULIS2_FORMAT_VUYA16     ULIS2_W_TYPE( ::ul2::kUint16 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kYUV ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_DEPTH( 2 )
#define ULIS2_FORMAT_YUV32      ULIS2_W_TYPE( ::ul2::kUint32 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kYUV ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_VUY32      ULIS2_W_TYPE( ::ul2::kUint32 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kYUV ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_YUVA32     ULIS2_W_TYPE( ::ul2::kUint32 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kYUV ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_AVUY32     ULIS2_W_TYPE( ::ul2::kUint32 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kYUV ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_AYUV32     ULIS2_W_TYPE( ::ul2::kUint32 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kYUV ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_VUYA32     ULIS2_W_TYPE( ::ul2::kUint32 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kYUV ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_YUVF       ULIS2_W_TYPE( ::ul2::kFloat ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kYUV ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_VUYF       ULIS2_W_TYPE( ::ul2::kFloat ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kYUV ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_YUVAF      ULIS2_W_TYPE( ::ul2::kFloat ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kYUV ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_AVUYF      ULIS2_W_TYPE( ::ul2::kFloat ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kYUV ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_AYUVF      ULIS2_W_TYPE( ::ul2::kFloat ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kYUV ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_VUYAF      ULIS2_W_TYPE( ::ul2::kFloat ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kYUV ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_YUVD       ULIS2_W_TYPE( ::ul2::kDouble ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kYUV ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 8 )
#define ULIS2_FORMAT_VUYD       ULIS2_W_TYPE( ::ul2::kDouble ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kYUV ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 8 )
#define ULIS2_FORMAT_YUVAD      ULIS2_W_TYPE( ::ul2::kDouble ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kYUV ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 8 )
#define ULIS2_FORMAT_AVUYD      ULIS2_W_TYPE( ::ul2::kDouble ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kYUV ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 8 )
#define ULIS2_FORMAT_AYUVD      ULIS2_W_TYPE( ::ul2::kDouble ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kYUV ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 8 )
#define ULIS2_FORMAT_VUYAD      ULIS2_W_TYPE( ::ul2::kDouble ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kYUV ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 8 )
#define ULIS2_FORMAT_Lab8       ULIS2_W_TYPE( ::ul2::kUint8 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kLab ) | ULIS2_W_DEPTH( 1 )
#define ULIS2_FORMAT_baL8       ULIS2_W_TYPE( ::ul2::kUint8 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kLab ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_DEPTH( 1 )
#define ULIS2_FORMAT_LabA8      ULIS2_W_TYPE( ::ul2::kUint8 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kLab ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_DEPTH( 1 )
#define ULIS2_FORMAT_AbaL8      ULIS2_W_TYPE( ::ul2::kUint8 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kLab ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_DEPTH( 1 )
#define ULIS2_FORMAT_ALab8      ULIS2_W_TYPE( ::ul2::kUint8 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kLab ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_DEPTH( 1 )
#define ULIS2_FORMAT_baLA8      ULIS2_W_TYPE( ::ul2::kUint8 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kLab ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_DEPTH( 1 )
#define ULIS2_FORMAT_Lab16      ULIS2_W_TYPE( ::ul2::kUint16 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kLab ) | ULIS2_W_DEPTH( 2 )
#define ULIS2_FORMAT_baL16      ULIS2_W_TYPE( ::ul2::kUint16 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kLab ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_DEPTH( 2 )
#define ULIS2_FORMAT_LabA16     ULIS2_W_TYPE( ::ul2::kUint16 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kLab ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_DEPTH( 2 )
#define ULIS2_FORMAT_AbaL16     ULIS2_W_TYPE( ::ul2::kUint16 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kLab ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_DEPTH( 2 )
#define ULIS2_FORMAT_ALab16     ULIS2_W_TYPE( ::ul2::kUint16 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kLab ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_DEPTH( 2 )
#define ULIS2_FORMAT_baLA16     ULIS2_W_TYPE( ::ul2::kUint16 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kLab ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_DEPTH( 2 )
#define ULIS2_FORMAT_Lab32      ULIS2_W_TYPE( ::ul2::kUint32 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kLab ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_baL32      ULIS2_W_TYPE( ::ul2::kUint32 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kLab ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_LabA32     ULIS2_W_TYPE( ::ul2::kUint32 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kLab ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_AbaL32     ULIS2_W_TYPE( ::ul2::kUint32 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kLab ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_ALab32     ULIS2_W_TYPE( ::ul2::kUint32 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kLab ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_baLA32     ULIS2_W_TYPE( ::ul2::kUint32 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kLab ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_LabF       ULIS2_W_TYPE( ::ul2::kFloat ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kLab ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_baLF       ULIS2_W_TYPE( ::ul2::kFloat ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kLab ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_LabAF      ULIS2_W_TYPE( ::ul2::kFloat ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kLab ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_AbaLF      ULIS2_W_TYPE( ::ul2::kFloat ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kLab ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_ALabF      ULIS2_W_TYPE( ::ul2::kFloat ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kLab ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_baLAF      ULIS2_W_TYPE( ::ul2::kFloat ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kLab ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_LabD       ULIS2_W_TYPE( ::ul2::kDouble ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kLab ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 8 )
#define ULIS2_FORMAT_baLD       ULIS2_W_TYPE( ::ul2::kDouble ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kLab ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 8 )
#define ULIS2_FORMAT_LabAD      ULIS2_W_TYPE( ::ul2::kDouble ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kLab ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 8 )
#define ULIS2_FORMAT_AbaLD      ULIS2_W_TYPE( ::ul2::kDouble ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kLab ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 8 )
#define ULIS2_FORMAT_ALabD      ULIS2_W_TYPE( ::ul2::kDouble ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kLab ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 8 )
#define ULIS2_FORMAT_baLAD      ULIS2_W_TYPE( ::ul2::kDouble ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kLab ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 8 )
#define ULIS2_FORMAT_XYZ8       ULIS2_W_TYPE( ::ul2::kUint8 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kXYZ ) | ULIS2_W_DEPTH( 1 )
#define ULIS2_FORMAT_ZYX8       ULIS2_W_TYPE( ::ul2::kUint8 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kXYZ ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_DEPTH( 1 )
#define ULIS2_FORMAT_XYZA8      ULIS2_W_TYPE( ::ul2::kUint8 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kXYZ ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_DEPTH( 1 )
#define ULIS2_FORMAT_AZYX8      ULIS2_W_TYPE( ::ul2::kUint8 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kXYZ ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_DEPTH( 1 )
#define ULIS2_FORMAT_AXYZ8      ULIS2_W_TYPE( ::ul2::kUint8 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kXYZ ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_DEPTH( 1 )
#define ULIS2_FORMAT_ZYXA8      ULIS2_W_TYPE( ::ul2::kUint8 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kXYZ ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_DEPTH( 1 )
#define ULIS2_FORMAT_XYZ16      ULIS2_W_TYPE( ::ul2::kUint16 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kXYZ ) | ULIS2_W_DEPTH( 2 )
#define ULIS2_FORMAT_ZYX16      ULIS2_W_TYPE( ::ul2::kUint16 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kXYZ ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_DEPTH( 2 )
#define ULIS2_FORMAT_XYZA16     ULIS2_W_TYPE( ::ul2::kUint16 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kXYZ ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_DEPTH( 2 )
#define ULIS2_FORMAT_AZYX16     ULIS2_W_TYPE( ::ul2::kUint16 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kXYZ ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_DEPTH( 2 )
#define ULIS2_FORMAT_AXYZ16     ULIS2_W_TYPE( ::ul2::kUint16 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kXYZ ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_DEPTH( 2 )
#define ULIS2_FORMAT_ZYXA16     ULIS2_W_TYPE( ::ul2::kUint16 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kXYZ ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_DEPTH( 2 )
#define ULIS2_FORMAT_XYZ32      ULIS2_W_TYPE( ::ul2::kUint32 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kXYZ ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_ZYX32      ULIS2_W_TYPE( ::ul2::kUint32 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kXYZ ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_XYZA32     ULIS2_W_TYPE( ::ul2::kUint32 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kXYZ ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_AZYX32     ULIS2_W_TYPE( ::ul2::kUint32 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kXYZ ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_AXYZ32     ULIS2_W_TYPE( ::ul2::kUint32 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kXYZ ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_ZYXA32     ULIS2_W_TYPE( ::ul2::kUint32 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kXYZ ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_XYZF       ULIS2_W_TYPE( ::ul2::kFloat ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kXYZ ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_ZYXF       ULIS2_W_TYPE( ::ul2::kFloat ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kXYZ ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_XYZAF      ULIS2_W_TYPE( ::ul2::kFloat ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kXYZ ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_AZYXF      ULIS2_W_TYPE( ::ul2::kFloat ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kXYZ ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_AXYZF      ULIS2_W_TYPE( ::ul2::kFloat ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kXYZ ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_ZYXAF      ULIS2_W_TYPE( ::ul2::kFloat ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kXYZ ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_XYZD       ULIS2_W_TYPE( ::ul2::kDouble ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kXYZ ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 8 )
#define ULIS2_FORMAT_ZYXD       ULIS2_W_TYPE( ::ul2::kDouble ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kXYZ ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 8 )
#define ULIS2_FORMAT_XYZAD      ULIS2_W_TYPE( ::ul2::kDouble ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kXYZ ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 8 )
#define ULIS2_FORMAT_AZYXD      ULIS2_W_TYPE( ::ul2::kDouble ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kXYZ ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 8 )
#define ULIS2_FORMAT_AXYZD      ULIS2_W_TYPE( ::ul2::kDouble ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kXYZ ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 8 )
#define ULIS2_FORMAT_ZYXAD      ULIS2_W_TYPE( ::ul2::kDouble ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kXYZ ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 8 )
#define ULIS2_FORMAT_Yxy8       ULIS2_W_TYPE( ::ul2::kUint8 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kYxy ) | ULIS2_W_DEPTH( 1 )
#define ULIS2_FORMAT_yxY8       ULIS2_W_TYPE( ::ul2::kUint8 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kYxy ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_DEPTH( 1 )
#define ULIS2_FORMAT_YxyA8      ULIS2_W_TYPE( ::ul2::kUint8 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kYxy ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_DEPTH( 1 )
#define ULIS2_FORMAT_AyxY8      ULIS2_W_TYPE( ::ul2::kUint8 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kYxy ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_DEPTH( 1 )
#define ULIS2_FORMAT_AYxy8      ULIS2_W_TYPE( ::ul2::kUint8 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kYxy ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_DEPTH( 1 )
#define ULIS2_FORMAT_yxYA8      ULIS2_W_TYPE( ::ul2::kUint8 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kYxy ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_DEPTH( 1 )
#define ULIS2_FORMAT_Yxy16      ULIS2_W_TYPE( ::ul2::kUint16 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kYxy ) | ULIS2_W_DEPTH( 2 )
#define ULIS2_FORMAT_yxY16      ULIS2_W_TYPE( ::ul2::kUint16 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kYxy ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_DEPTH( 2 )
#define ULIS2_FORMAT_YxyA16     ULIS2_W_TYPE( ::ul2::kUint16 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kYxy ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_DEPTH( 2 )
#define ULIS2_FORMAT_AyxY16     ULIS2_W_TYPE( ::ul2::kUint16 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kYxy ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_DEPTH( 2 )
#define ULIS2_FORMAT_AYxy16     ULIS2_W_TYPE( ::ul2::kUint16 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kYxy ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_DEPTH( 2 )
#define ULIS2_FORMAT_yxYA16     ULIS2_W_TYPE( ::ul2::kUint16 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kYxy ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_DEPTH( 2 )
#define ULIS2_FORMAT_Yxy32      ULIS2_W_TYPE( ::ul2::kUint32 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kYxy ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_yxY32      ULIS2_W_TYPE( ::ul2::kUint32 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kYxy ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_YxyA32     ULIS2_W_TYPE( ::ul2::kUint32 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kYxy ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_AyxY32     ULIS2_W_TYPE( ::ul2::kUint32 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kYxy ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_AYxy32     ULIS2_W_TYPE( ::ul2::kUint32 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kYxy ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_yxYA32     ULIS2_W_TYPE( ::ul2::kUint32 ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kYxy ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_YxyF       ULIS2_W_TYPE( ::ul2::kFloat ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kYxy ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_yxYF       ULIS2_W_TYPE( ::ul2::kFloat ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kYxy ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_YxyAF      ULIS2_W_TYPE( ::ul2::kFloat ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kYxy ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_AyxYF      ULIS2_W_TYPE( ::ul2::kFloat ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kYxy ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_AYxyF      ULIS2_W_TYPE( ::ul2::kFloat ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kYxy ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_yxYAF      ULIS2_W_TYPE( ::ul2::kFloat ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kYxy ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 4 )
#define ULIS2_FORMAT_YxyD       ULIS2_W_TYPE( ::ul2::kDouble ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kYxy ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 8 )
#define ULIS2_FORMAT_yxYD       ULIS2_W_TYPE( ::ul2::kDouble ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kYxy ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 8 )
#define ULIS2_FORMAT_YxyAD      ULIS2_W_TYPE( ::ul2::kDouble ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kYxy ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 8 )
#define ULIS2_FORMAT_AyxYD      ULIS2_W_TYPE( ::ul2::kDouble ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kYxy ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 8 )
#define ULIS2_FORMAT_AYxyD      ULIS2_W_TYPE( ::ul2::kDouble ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kYxy ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 8 )
#define ULIS2_FORMAT_yxYAD      ULIS2_W_TYPE( ::ul2::kDouble ) | ULIS2_W_CHANNELS( 3 ) | ULIS2_W_MODEL( ::ul2::kYxy ) | ULIS2_W_ALPHA( 1 ) | ULIS2_W_REVERSE( 1 ) | ULIS2_W_SWAP( 1 ) | ULIS2_W_FLOATING( 1 ) | ULIS2_W_DEPTH( 8 )

