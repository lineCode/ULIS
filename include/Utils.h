/**
*
*   ULIS2
*__________________
*
* @file         Utils.h
* @author       Clement Berthaud
* @brief        This file provides core utils definitions for the ULIS2 library.
* @copyright    Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Types.h"

ULIS2_NAMESPACE_BEGIN
// eTypeFromT
template< typename T > ULIS2_FORCEINLINE eType eTypeFromT(void)         { return  TYPE_INVALID; }
template<> constexpr ULIS2_FORCEINLINE eType eTypeFromT< uint8 >()      { return  TYPE_UINT8;   }
template<> constexpr ULIS2_FORCEINLINE eType eTypeFromT< uint16 >()     { return  TYPE_UINT16;  }
template<> constexpr ULIS2_FORCEINLINE eType eTypeFromT< uint32 >()     { return  TYPE_UINT32;  }
template<> constexpr ULIS2_FORCEINLINE eType eTypeFromT< ufloat >()     { return  TYPE_UFLOAT;  }
template<> constexpr ULIS2_FORCEINLINE eType eTypeFromT< udouble >()    { return  TYPE_UDOUBLE; }

// _min _max _clamp
template< typename T > static constexpr ULIS2_FORCEINLINE T _min( T iA, T iB ) { return  iA < iB ? iA : iB; }
template< typename T > static constexpr ULIS2_FORCEINLINE T _max( T iA, T iB ) { return  iA > iB ? iA : iB; }
template< typename T > static constexpr ULIS2_FORCEINLINE T _clamp( T iValue, T iMin, T iMax ) { return  _max( iMin, _min( iValue, iMax ) ); }

// ConvType
template< typename T1, typename T2 > constexpr T2 inline ConvType( T1 iValue ) { return (T2)iValue; }
template<> constexpr uint16     inline ConvType< uint8,  uint16  >( uint8 iValue  )  { return iValue * 0x101;                                                           }
template<> constexpr uint32     inline ConvType< uint8,  uint32  >( uint8 iValue  )  { return iValue * 0x1010101;                                                       }
template<> constexpr uint32     inline ConvType< uint16, uint32  >( uint16 iValue )  { return iValue * 0x10001;                                                         }
template<> constexpr uint8      inline ConvType< uint16, uint8   >( uint16 iValue )  { return ( iValue + 1 + ( iValue>>8 ) ) >> 8;                                      }
template<> constexpr uint8      inline ConvType< uint32, uint8   >( uint32 iValue )  { return iValue >> 24;                                                             }
template<> constexpr uint16     inline ConvType< uint32, uint16  >( uint32 iValue )  { return ( iValue + 1 + ( iValue>>16 ) ) >> 16;                                    }
template<> constexpr ufloat     inline ConvType< uint8,  ufloat  >( uint8 iValue  )  { return iValue / (ufloat)0xFF;                                                    }
template<> constexpr ufloat     inline ConvType< uint16, ufloat  >( uint16 iValue )  { return iValue / (ufloat)0xFFFF;                                                  }
template<> constexpr ufloat     inline ConvType< uint32, ufloat  >( uint32 iValue )  { return iValue / (ufloat)0xFFFFFFFF;                                              }
template<> constexpr udouble    inline ConvType< uint8,  udouble >( uint8 iValue  )  { return iValue / (udouble)0xFF;                                                   }
template<> constexpr udouble    inline ConvType< uint16, udouble >( uint16 iValue )  { return iValue / (udouble)0xFFFF;                                                 }
template<> constexpr udouble    inline ConvType< uint32, udouble >( uint32 iValue )  { return iValue / (udouble)0xFFFFFFFF;                                             }
template<> constexpr uint8      inline ConvType< ufloat,  uint8  >( ufloat iValue  ) { return uint8(  iValue * 0xFF       );                                            }
template<> constexpr uint16     inline ConvType< ufloat,  uint16 >( ufloat iValue  ) { return uint16( iValue * 0xFFFF     );                                            }
template<> constexpr uint32     inline ConvType< ufloat,  uint32 >( ufloat iValue  ) { return uint32( iValue * 0xFFFFFFFF );                                            }
template<> constexpr uint8      inline ConvType< udouble, uint8  >( udouble iValue ) { return uint8(  iValue * 0xFF       );                                            }
template<> constexpr uint16     inline ConvType< udouble, uint16 >( udouble iValue ) { return uint16( iValue * 0xFFFF     );                                            }
template<> constexpr uint32     inline ConvType< udouble, uint32 >( udouble iValue ) { return uint32( iValue * 0xFFFFFFFF );                                            }
template<> constexpr uint8      inline ConvType< int,  uint8     >( int iValue  )    { return _clamp( iValue, 0, (int)UINT8_MAX );                                      }
template<> constexpr uint16     inline ConvType< int,  uint16    >( int iValue  )    { return ConvType< uint8, uint16 >(  (uint8)_clamp( iValue, 0, (int)UINT8_MAX ) ); }
template<> constexpr uint32     inline ConvType< int,  uint32    >( int iValue  )    { return ConvType< uint8, uint32 >(  (uint8)_clamp( iValue, 0, (int)UINT8_MAX ) ); }
template<> constexpr ufloat     inline ConvType< int,  ufloat    >( int iValue  )    { return ConvType< uint8, ufloat  >( (uint8)_clamp( iValue, 0, (int)UINT8_MAX ) ); }
template<> constexpr udouble    inline ConvType< int,  udouble   >( int iValue  )    { return ConvType< uint8, udouble >( (uint8)_clamp( iValue, 0, (int)UINT8_MAX ) ); }

// MinType MaxType
template< typename T > T constexpr inline MinType() { return T(0); }
template< typename T > T constexpr inline MaxType() { return T(1); }
template<> uint8    constexpr inline MaxType< uint8   >() { return UINT8_MAX;    }
template<> uint16   constexpr inline MaxType< uint16  >() { return UINT16_MAX;   }
template<> uint32   constexpr inline MaxType< uint32  >() { return UINT32_MAX;   }
template<> ufloat   constexpr inline MaxType< ufloat  >() { return 1.f;          }
template<> udouble  constexpr inline MaxType< udouble >() { return 0.0;          }

// User define literal oprators
constexpr uint8     operator "" _u8(  unsigned long long int i ) { return  (uint8)_clamp( i, (unsigned long long int)0, (unsigned long long int)UINT8_MAX ); }
constexpr uint16    operator "" _u16( unsigned long long int i ) { return  ConvType< uint8, uint16 >( (uint8)_clamp( i, (unsigned long long int)0, (unsigned long long int)UINT8_MAX ) ); }
constexpr uint32    operator "" _u32( unsigned long long int i ) { return  ConvType< uint8, uint32 >( (uint8)_clamp( i, (unsigned long long int)0, (unsigned long long int)UINT8_MAX ) ); }

struct __encodedlab_ab
{
    constexpr __encodedlab_ab( udouble i ) : m( i ) {}
    constexpr udouble operator-(){        return  _clamp( -m + 0.5, 0.0, 1.0 ); }
    constexpr udouble operator+(){        return  _clamp( +m + 0.5, 0.0, 1.0 ); }
    constexpr operator udouble() const {  return  _clamp( +m + 0.5, 0.0, 1.0 ); }
    udouble m;
};

constexpr udouble operator "" _L( unsigned long long int i) { return _clamp( i, (unsigned long long int)0, (unsigned long long int)100 ) / 100.0; }
constexpr __encodedlab_ab operator "" _a( unsigned long long int i) { return  __encodedlab_ab( _clamp( i, (unsigned long long int)0, (unsigned long long int)128 ) / 255.0 ); }
constexpr __encodedlab_ab operator "" _b( unsigned long long int i) { return  __encodedlab_ab( _clamp( i, (unsigned long long int)0, (unsigned long long int)128 ) / 255.0 ); }
constexpr ufloat    fix8f() { return ( 128.0f / 255.0f ) - 0.5f; }
constexpr udouble   fix8d() { return ( 128.0 / 255.0 ) - 0.5; }

ULIS2_NAMESPACE_END

