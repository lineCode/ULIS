// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS3
*__________________
*
* @file         Format.h
* @author       Clement Berthaud
* @brief        This file provides core format definitions for the ULIS3 library.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Types.h"

/////////////////////////////////////////////////////
// Format Magic Number, Memory Layout and Properties
//
//          [ DYNAMIC    ] [ STATIC                   ]
//        32|        |  20|  16|            8|   4|   0
//          1098 7654 3210 9876     5432 1098 7654 3210
//          XXXX XXLP CCCC BBBB     ASRF MMMM NNNN TTTT
//
//    Example: RGBA8
//                            1     1000 0010 0011 0000
//          1111 1111 1111 1111     1001 1111 1111 1111 // Layout Mask
//          0000 0000 0000 1111     1111 1111 1111 1111 // Lo Mask
//          1111 1111 1111 0000     0000 0000 0000 0000 // Hi Mask
//
//          STATIC:
//          T: Type                 R: Reverse
//          N: Num Channels         S: Swap
//          M: Model                A: Alpha
//          F: Floating             B: Bytes per sample ( Depth )
//
//          DYNAMIC
//          C: Default Profile
//          P: Premultiplied
//          L: Linear ( Gamma Uncompressed )
//
//          X: Free space for dynamic extra info
//

/////////////////////////////////////////////////////
// Format Masks
#define ULIS3_FORMAT_MASK_LO        0x000FFFFF
#define ULIS3_FORMAT_MASK_HI        0xFFF00000
#define ULIS3_FORMAT_MASK_LAYOUT    0b11111111111111111001111111111111

/////////////////////////////////////////////////////
// Static Properties Format Macro Operators
// Static Format Properties: Write
#define ULIS3_W_TYPE( i )           ( i & 0xF )
#define ULIS3_W_CHANNELS( i )       ( ( i & 0xF ) << 4 )
#define ULIS3_W_MODEL( i )          ( ( i & 0xF ) << 8 )
#define ULIS3_W_FLOATING( i )       ( ( i & 1 ) << 12 )
#define ULIS3_W_REVERSE( i )        ( ( i & 1 ) << 13 )
#define ULIS3_W_SWAP( i )           ( ( i & 1 ) << 14 )
#define ULIS3_W_ALPHA( i )          ( ( i & 1 ) << 15 )
#define ULIS3_W_DEPTH( i )          ( ( i & 0xF ) << 16 )
// Static Format Properties: Erase
#define ULIS3_E_TYPE                ( ~0xF )
#define ULIS3_E_CHANNELS            ( ~( 0xF << 4 ) )
#define ULIS3_E_MODEL               ( ~( 0xF << 8 ) )
#define ULIS3_E_FLOATING            ( ~( 0x1 << 12 ) )
#define ULIS3_E_REVERSE             ( ~( 0x1 << 13 ) )
#define ULIS3_E_SWAP                ( ~( 0x1 << 14 ) )
#define ULIS3_E_ALPHA               ( ~( 0x1 << 15 ) )
#define ULIS3_E_DEPTH               ( ~( 0xF << 16 )
// Static Format Properties: Read
#define ULIS3_R_TYPE( i )           ( i & 0xF )
#define ULIS3_R_CHANNELS( i )       ( ( i >> 4 ) & 0xF )
#define ULIS3_R_MODEL( i )          ( ( i >> 8 ) & 0xF )
#define ULIS3_R_FLOATING( i )       ( ( i >> 12 ) & 0x1 )
#define ULIS3_R_REVERSE( i )        ( ( i >> 13 ) & 0x1 )
#define ULIS3_R_SWAP( i )           ( ( i >> 14 ) & 0x1 )
#define ULIS3_R_ALPHA( i )          ( ( i >> 15 ) & 0x1 )
#define ULIS3_R_DEPTH( i )          ( ( i >> 16 ) & 0xF )
#define ULIS3_R_RS( i )             ( ( i >> 13 ) & 0x3 )
#define ULIS3_R_EXTRA( i )          ( ( i >> 20 ) & 0xFFF )

/////////////////////////////////////////////////////
// Dynamic Properties Format Macro Operators
// Dynamic Format Properties: Write
#define ULIS3_W_PROFILE( i )        ( ( i & 0xF ) << 20 )
#define ULIS3_W_PREMULT( i )        ( ( i & 1 ) << 24 )
#define ULIS3_W_LINEAR( i )         ( ( i & 1 ) << 25 )
// Dynamic Format Properties: Erase
#define ULIS3_E_PROFILE             ( ~( 0xF << 20 ) )
#define ULIS3_E_PREMULT             ( ~( 0x1 << 24 ) )
#define ULIS3_E_LINEAR              ( ~( 0x1 << 25 ) )
// Dynamic Format Properties: Read
#define ULIS3_R_PROFILE( i )        ( ( i >> 20 ) & 0xF )
#define ULIS3_R_PREMULT( i )        ( ( i >> 24 ) & 0x1 )
#define ULIS3_R_LINEAR( i )         ( ( i >> 25 ) & 0x1 )

/////////////////////////////////////////////////////
// All ~680 formats.
#define ULIS3_FORMAT_G8                             ( ULIS3_W_TYPE( ULIS3_TYPE_UINT8    ) | ULIS3_W_CHANNELS( 1 ) | ULIS3_W_MODEL( ULIS3_CM_GREY )  |                                                                                           ULIS3_W_DEPTH( 1 ) | ULIS3_W_PROFILE( ULIS3_sGrey ) )
#define ULIS3_FORMAT_GA8                            ( ULIS3_W_TYPE( ULIS3_TYPE_UINT8    ) | ULIS3_W_CHANNELS( 1 ) | ULIS3_W_MODEL( ULIS3_CM_GREY )  | ULIS3_W_ALPHA( 1 ) |                                                                      ULIS3_W_DEPTH( 1 ) | ULIS3_W_PROFILE( ULIS3_sGrey ) )
#define ULIS3_FORMAT_AG8                            ( ULIS3_W_TYPE( ULIS3_TYPE_UINT8    ) | ULIS3_W_CHANNELS( 1 ) | ULIS3_W_MODEL( ULIS3_CM_GREY )  | ULIS3_W_ALPHA( 1 ) |                          ULIS3_W_SWAP( 1 ) |                         ULIS3_W_DEPTH( 1 ) | ULIS3_W_PROFILE( ULIS3_sGrey ) )
#define ULIS3_FORMAT_G16                            ( ULIS3_W_TYPE( ULIS3_TYPE_UINT16   ) | ULIS3_W_CHANNELS( 1 ) | ULIS3_W_MODEL( ULIS3_CM_GREY )  |                                                                                           ULIS3_W_DEPTH( 2 ) | ULIS3_W_PROFILE( ULIS3_sGrey ) )
#define ULIS3_FORMAT_GA16                           ( ULIS3_W_TYPE( ULIS3_TYPE_UINT16   ) | ULIS3_W_CHANNELS( 1 ) | ULIS3_W_MODEL( ULIS3_CM_GREY )  | ULIS3_W_ALPHA( 1 ) |                                                                      ULIS3_W_DEPTH( 2 ) | ULIS3_W_PROFILE( ULIS3_sGrey ) )
#define ULIS3_FORMAT_AG16                           ( ULIS3_W_TYPE( ULIS3_TYPE_UINT16   ) | ULIS3_W_CHANNELS( 1 ) | ULIS3_W_MODEL( ULIS3_CM_GREY )  | ULIS3_W_ALPHA( 1 ) |                          ULIS3_W_SWAP( 1 ) |                         ULIS3_W_DEPTH( 2 ) | ULIS3_W_PROFILE( ULIS3_sGrey ) )
#define ULIS3_FORMAT_G32                            ( ULIS3_W_TYPE( ULIS3_TYPE_UINT32   ) | ULIS3_W_CHANNELS( 1 ) | ULIS3_W_MODEL( ULIS3_CM_GREY )  |                                                                                           ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_sGrey ) )
#define ULIS3_FORMAT_GA32                           ( ULIS3_W_TYPE( ULIS3_TYPE_UINT32   ) | ULIS3_W_CHANNELS( 1 ) | ULIS3_W_MODEL( ULIS3_CM_GREY )  | ULIS3_W_ALPHA( 1 ) |                                                                      ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_sGrey ) )
#define ULIS3_FORMAT_AG32                           ( ULIS3_W_TYPE( ULIS3_TYPE_UINT32   ) | ULIS3_W_CHANNELS( 1 ) | ULIS3_W_MODEL( ULIS3_CM_GREY )  | ULIS3_W_ALPHA( 1 ) |                          ULIS3_W_SWAP( 1 ) |                         ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_sGrey ) )
#define ULIS3_FORMAT_GF                             ( ULIS3_W_TYPE( ULIS3_TYPE_UFLOAT   ) | ULIS3_W_CHANNELS( 1 ) | ULIS3_W_MODEL( ULIS3_CM_GREY )  |                                                                   ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_sGrey ) )
#define ULIS3_FORMAT_GAF                            ( ULIS3_W_TYPE( ULIS3_TYPE_UFLOAT   ) | ULIS3_W_CHANNELS( 1 ) | ULIS3_W_MODEL( ULIS3_CM_GREY )  | ULIS3_W_ALPHA( 1 ) |                                              ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_sGrey ) )
#define ULIS3_FORMAT_AGF                            ( ULIS3_W_TYPE( ULIS3_TYPE_UFLOAT   ) | ULIS3_W_CHANNELS( 1 ) | ULIS3_W_MODEL( ULIS3_CM_GREY )  | ULIS3_W_ALPHA( 1 ) |                          ULIS3_W_SWAP( 1 ) | ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_sGrey ) )
#define ULIS3_FORMAT_GD                             ( ULIS3_W_TYPE( ULIS3_TYPE_UDOUBLE  ) | ULIS3_W_CHANNELS( 1 ) | ULIS3_W_MODEL( ULIS3_CM_GREY )  |                                                                   ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 8 ) | ULIS3_W_PROFILE( ULIS3_sGrey ) )
#define ULIS3_FORMAT_GAD                            ( ULIS3_W_TYPE( ULIS3_TYPE_UDOUBLE  ) | ULIS3_W_CHANNELS( 1 ) | ULIS3_W_MODEL( ULIS3_CM_GREY )  | ULIS3_W_ALPHA( 1 ) |                                              ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 8 ) | ULIS3_W_PROFILE( ULIS3_sGrey ) )
#define ULIS3_FORMAT_AGD                            ( ULIS3_W_TYPE( ULIS3_TYPE_UDOUBLE  ) | ULIS3_W_CHANNELS( 1 ) | ULIS3_W_MODEL( ULIS3_CM_GREY )  | ULIS3_W_ALPHA( 1 ) |                          ULIS3_W_SWAP( 1 ) | ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 8 ) | ULIS3_W_PROFILE( ULIS3_sGrey ) )
#define ULIS3_FORMAT_RGB8                           ( ULIS3_W_TYPE( ULIS3_TYPE_UINT8    ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_RGB )   |                                                                                           ULIS3_W_DEPTH( 1 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_BGR8                           ( ULIS3_W_TYPE( ULIS3_TYPE_UINT8    ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_RGB )   |                       ULIS3_W_REVERSE( 1 ) |                                              ULIS3_W_DEPTH( 1 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_RGBA8                          ( ULIS3_W_TYPE( ULIS3_TYPE_UINT8    ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_RGB )   | ULIS3_W_ALPHA( 1 ) |                                                                      ULIS3_W_DEPTH( 1 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_ABGR8                          ( ULIS3_W_TYPE( ULIS3_TYPE_UINT8    ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_RGB )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |                                              ULIS3_W_DEPTH( 1 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_ARGB8                          ( ULIS3_W_TYPE( ULIS3_TYPE_UINT8    ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_RGB )   | ULIS3_W_ALPHA( 1 ) |                          ULIS3_W_SWAP( 1 ) |                         ULIS3_W_DEPTH( 1 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_BGRA8                          ( ULIS3_W_TYPE( ULIS3_TYPE_UINT8    ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_RGB )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |  ULIS3_W_SWAP( 1 ) |                         ULIS3_W_DEPTH( 1 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_RGB16                          ( ULIS3_W_TYPE( ULIS3_TYPE_UINT16   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_RGB )   |                                                                                           ULIS3_W_DEPTH( 2 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_BGR16                          ( ULIS3_W_TYPE( ULIS3_TYPE_UINT16   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_RGB )   |                       ULIS3_W_REVERSE( 1 ) |                                              ULIS3_W_DEPTH( 2 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_RGBA16                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT16   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_RGB )   | ULIS3_W_ALPHA( 1 ) |                                                                      ULIS3_W_DEPTH( 2 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_ABGR16                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT16   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_RGB )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |                                              ULIS3_W_DEPTH( 2 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_ARGB16                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT16   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_RGB )   | ULIS3_W_ALPHA( 1 ) |                          ULIS3_W_SWAP( 1 ) |                         ULIS3_W_DEPTH( 2 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_BGRA16                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT16   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_RGB )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |  ULIS3_W_SWAP( 1 ) |                         ULIS3_W_DEPTH( 2 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_RGB32                          ( ULIS3_W_TYPE( ULIS3_TYPE_UINT32   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_RGB )   |                                                                                           ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_BGR32                          ( ULIS3_W_TYPE( ULIS3_TYPE_UINT32   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_RGB )   |                       ULIS3_W_REVERSE( 1 ) |                                              ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_RGBA32                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT32   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_RGB )   | ULIS3_W_ALPHA( 1 ) |                                                                      ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_ABGR32                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT32   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_RGB )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |                                              ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_ARGB32                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT32   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_RGB )   | ULIS3_W_ALPHA( 1 ) |                          ULIS3_W_SWAP( 1 ) |                         ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_BGRA32                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT32   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_RGB )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |  ULIS3_W_SWAP( 1 ) |                         ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_RGBF                           ( ULIS3_W_TYPE( ULIS3_TYPE_UFLOAT   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_RGB )   |                                                                   ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_BGRF                           ( ULIS3_W_TYPE( ULIS3_TYPE_UFLOAT   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_RGB )   |                       ULIS3_W_REVERSE( 1 ) |                      ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_RGBAF                          ( ULIS3_W_TYPE( ULIS3_TYPE_UFLOAT   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_RGB )   | ULIS3_W_ALPHA( 1 ) |                                              ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_ABGRF                          ( ULIS3_W_TYPE( ULIS3_TYPE_UFLOAT   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_RGB )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |                      ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_ARGBF                          ( ULIS3_W_TYPE( ULIS3_TYPE_UFLOAT   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_RGB )   | ULIS3_W_ALPHA( 1 ) |                          ULIS3_W_SWAP( 1 ) | ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_BGRAF                          ( ULIS3_W_TYPE( ULIS3_TYPE_UFLOAT   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_RGB )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |  ULIS3_W_SWAP( 1 ) | ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_RGBD                           ( ULIS3_W_TYPE( ULIS3_TYPE_UDOUBLE  ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_RGB )   |                                                                   ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 8 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_BGRD                           ( ULIS3_W_TYPE( ULIS3_TYPE_UDOUBLE  ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_RGB )   |                       ULIS3_W_REVERSE( 1 ) |                      ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 8 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_RGBAD                          ( ULIS3_W_TYPE( ULIS3_TYPE_UDOUBLE  ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_RGB )   | ULIS3_W_ALPHA( 1 ) |                                              ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 8 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_ABGRD                          ( ULIS3_W_TYPE( ULIS3_TYPE_UDOUBLE  ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_RGB )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |                      ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 8 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_ARGBD                          ( ULIS3_W_TYPE( ULIS3_TYPE_UDOUBLE  ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_RGB )   | ULIS3_W_ALPHA( 1 ) |                          ULIS3_W_SWAP( 1 ) | ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 8 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_BGRAD                          ( ULIS3_W_TYPE( ULIS3_TYPE_UDOUBLE  ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_RGB )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |  ULIS3_W_SWAP( 1 ) | ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 8 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_HSV8                           ( ULIS3_W_TYPE( ULIS3_TYPE_UINT8    ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_HSV )   |                                                                                           ULIS3_W_DEPTH( 1 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_VSH8                           ( ULIS3_W_TYPE( ULIS3_TYPE_UINT8    ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_HSV )   |                       ULIS3_W_REVERSE( 1 ) |                                              ULIS3_W_DEPTH( 1 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_HSVA8                          ( ULIS3_W_TYPE( ULIS3_TYPE_UINT8    ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_HSV )   | ULIS3_W_ALPHA( 1 ) |                                                                      ULIS3_W_DEPTH( 1 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_AVSH8                          ( ULIS3_W_TYPE( ULIS3_TYPE_UINT8    ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_HSV )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |                                              ULIS3_W_DEPTH( 1 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_AHSV8                          ( ULIS3_W_TYPE( ULIS3_TYPE_UINT8    ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_HSV )   | ULIS3_W_ALPHA( 1 ) |                          ULIS3_W_SWAP( 1 ) |                         ULIS3_W_DEPTH( 1 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_VSHA8                          ( ULIS3_W_TYPE( ULIS3_TYPE_UINT8    ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_HSV )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |  ULIS3_W_SWAP( 1 ) |                         ULIS3_W_DEPTH( 1 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_HSV16                          ( ULIS3_W_TYPE( ULIS3_TYPE_UINT16   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_HSV )   |                                                                                           ULIS3_W_DEPTH( 2 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_VSH16                          ( ULIS3_W_TYPE( ULIS3_TYPE_UINT16   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_HSV )   |                       ULIS3_W_REVERSE( 1 ) |                                              ULIS3_W_DEPTH( 2 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_HSVA16                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT16   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_HSV )   | ULIS3_W_ALPHA( 1 ) |                                                                      ULIS3_W_DEPTH( 2 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_AVSH16                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT16   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_HSV )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |                                              ULIS3_W_DEPTH( 2 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_AHSV16                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT16   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_HSV )   | ULIS3_W_ALPHA( 1 ) |                          ULIS3_W_SWAP( 1 ) |                         ULIS3_W_DEPTH( 2 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_VSHA16                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT16   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_HSV )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |  ULIS3_W_SWAP( 1 ) |                         ULIS3_W_DEPTH( 2 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_HSV32                          ( ULIS3_W_TYPE( ULIS3_TYPE_UINT32   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_HSV )   |                                                                                           ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_VSH32                          ( ULIS3_W_TYPE( ULIS3_TYPE_UINT32   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_HSV )   |                       ULIS3_W_REVERSE( 1 ) |                                              ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_HSVA32                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT32   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_HSV )   | ULIS3_W_ALPHA( 1 ) |                                                                      ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_AVSH32                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT32   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_HSV )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |                                              ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_AHSV32                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT32   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_HSV )   | ULIS3_W_ALPHA( 1 ) |                          ULIS3_W_SWAP( 1 ) |                         ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_VSHA32                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT32   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_HSV )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |  ULIS3_W_SWAP( 1 ) |                         ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_HSVF                           ( ULIS3_W_TYPE( ULIS3_TYPE_UFLOAT   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_HSV )   |                                                                   ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_VSHF                           ( ULIS3_W_TYPE( ULIS3_TYPE_UFLOAT   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_HSV )   |                       ULIS3_W_REVERSE( 1 ) |                      ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_HSVAF                          ( ULIS3_W_TYPE( ULIS3_TYPE_UFLOAT   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_HSV )   | ULIS3_W_ALPHA( 1 ) |                                              ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_AVSHF                          ( ULIS3_W_TYPE( ULIS3_TYPE_UFLOAT   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_HSV )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |                      ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_AHSVF                          ( ULIS3_W_TYPE( ULIS3_TYPE_UFLOAT   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_HSV )   | ULIS3_W_ALPHA( 1 ) |                          ULIS3_W_SWAP( 1 ) | ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_VSHAF                          ( ULIS3_W_TYPE( ULIS3_TYPE_UFLOAT   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_HSV )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |  ULIS3_W_SWAP( 1 ) | ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_HSVD                           ( ULIS3_W_TYPE( ULIS3_TYPE_UDOUBLE  ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_HSV )   |                                                                   ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 8 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_VSHD                           ( ULIS3_W_TYPE( ULIS3_TYPE_UDOUBLE  ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_HSV )   |                       ULIS3_W_REVERSE( 1 ) |                      ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 8 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_HSVAD                          ( ULIS3_W_TYPE( ULIS3_TYPE_UDOUBLE  ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_HSV )   | ULIS3_W_ALPHA( 1 ) |                                              ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 8 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_AVSHD                          ( ULIS3_W_TYPE( ULIS3_TYPE_UDOUBLE  ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_HSV )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |                      ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 8 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_AHSVD                          ( ULIS3_W_TYPE( ULIS3_TYPE_UDOUBLE  ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_HSV )   | ULIS3_W_ALPHA( 1 ) |                          ULIS3_W_SWAP( 1 ) | ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 8 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_VSHAD                          ( ULIS3_W_TYPE( ULIS3_TYPE_UDOUBLE  ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_HSV )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |  ULIS3_W_SWAP( 1 ) | ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 8 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_HSL8                           ( ULIS3_W_TYPE( ULIS3_TYPE_UINT8    ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_HSL )   |                                                                                           ULIS3_W_DEPTH( 1 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_LSH8                           ( ULIS3_W_TYPE( ULIS3_TYPE_UINT8    ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_HSL )   |                       ULIS3_W_REVERSE( 1 ) |                                              ULIS3_W_DEPTH( 1 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_HSLA8                          ( ULIS3_W_TYPE( ULIS3_TYPE_UINT8    ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_HSL )   | ULIS3_W_ALPHA( 1 ) |                                                                      ULIS3_W_DEPTH( 1 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_ALSH8                          ( ULIS3_W_TYPE( ULIS3_TYPE_UINT8    ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_HSL )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |                                              ULIS3_W_DEPTH( 1 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_AHSL8                          ( ULIS3_W_TYPE( ULIS3_TYPE_UINT8    ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_HSL )   | ULIS3_W_ALPHA( 1 ) |                          ULIS3_W_SWAP( 1 ) |                         ULIS3_W_DEPTH( 1 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_LSHA8                          ( ULIS3_W_TYPE( ULIS3_TYPE_UINT8    ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_HSL )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |  ULIS3_W_SWAP( 1 ) |                         ULIS3_W_DEPTH( 1 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_HSL16                          ( ULIS3_W_TYPE( ULIS3_TYPE_UINT16   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_HSL )   |                                                                                           ULIS3_W_DEPTH( 2 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_LSH16                          ( ULIS3_W_TYPE( ULIS3_TYPE_UINT16   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_HSL )   |                       ULIS3_W_REVERSE( 1 ) |                                              ULIS3_W_DEPTH( 2 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_HSLA16                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT16   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_HSL )   | ULIS3_W_ALPHA( 1 ) |                                                                      ULIS3_W_DEPTH( 2 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_ALSH16                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT16   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_HSL )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |                                              ULIS3_W_DEPTH( 2 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_AHSL16                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT16   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_HSL )   | ULIS3_W_ALPHA( 1 ) |                          ULIS3_W_SWAP( 1 ) |                         ULIS3_W_DEPTH( 2 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_LSHA16                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT16   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_HSL )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |  ULIS3_W_SWAP( 1 ) |                         ULIS3_W_DEPTH( 2 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_HSL32                          ( ULIS3_W_TYPE( ULIS3_TYPE_UINT32   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_HSL )   |                                                                                           ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_LSH32                          ( ULIS3_W_TYPE( ULIS3_TYPE_UINT32   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_HSL )   |                       ULIS3_W_REVERSE( 1 ) |                                              ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_HSLA32                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT32   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_HSL )   | ULIS3_W_ALPHA( 1 ) |                                                                      ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_ALSH32                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT32   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_HSL )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |                                              ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_AHSL32                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT32   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_HSL )   | ULIS3_W_ALPHA( 1 ) |                          ULIS3_W_SWAP( 1 ) |                         ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_LSHA32                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT32   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_HSL )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |  ULIS3_W_SWAP( 1 ) |                         ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_HSLF                           ( ULIS3_W_TYPE( ULIS3_TYPE_UFLOAT   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_HSL )   |                                                                   ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_LSHF                           ( ULIS3_W_TYPE( ULIS3_TYPE_UFLOAT   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_HSL )   |                       ULIS3_W_REVERSE( 1 ) |                      ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_HSLAF                          ( ULIS3_W_TYPE( ULIS3_TYPE_UFLOAT   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_HSL )   | ULIS3_W_ALPHA( 1 ) |                                              ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_ALSHF                          ( ULIS3_W_TYPE( ULIS3_TYPE_UFLOAT   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_HSL )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |                      ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_AHSLF                          ( ULIS3_W_TYPE( ULIS3_TYPE_UFLOAT   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_HSL )   | ULIS3_W_ALPHA( 1 ) |                          ULIS3_W_SWAP( 1 ) | ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_LSHAF                          ( ULIS3_W_TYPE( ULIS3_TYPE_UFLOAT   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_HSL )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |  ULIS3_W_SWAP( 1 ) | ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_HSLD                           ( ULIS3_W_TYPE( ULIS3_TYPE_UDOUBLE  ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_HSL )   |                                                                   ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 8 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_LSHD                           ( ULIS3_W_TYPE( ULIS3_TYPE_UDOUBLE  ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_HSL )   |                       ULIS3_W_REVERSE( 1 ) |                      ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 8 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_HSLAD                          ( ULIS3_W_TYPE( ULIS3_TYPE_UDOUBLE  ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_HSL )   | ULIS3_W_ALPHA( 1 ) |                                              ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 8 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_ALSHD                          ( ULIS3_W_TYPE( ULIS3_TYPE_UDOUBLE  ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_HSL )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |                      ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 8 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_AHSLD                          ( ULIS3_W_TYPE( ULIS3_TYPE_UDOUBLE  ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_HSL )   | ULIS3_W_ALPHA( 1 ) |                          ULIS3_W_SWAP( 1 ) | ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 8 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_LSHAD                          ( ULIS3_W_TYPE( ULIS3_TYPE_UDOUBLE  ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_HSL )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |  ULIS3_W_SWAP( 1 ) | ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 8 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_CMY8                           ( ULIS3_W_TYPE( ULIS3_TYPE_UINT8    ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_CMY )   |                                                                                           ULIS3_W_DEPTH( 1 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_YMC8                           ( ULIS3_W_TYPE( ULIS3_TYPE_UINT8    ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_CMY )   |                       ULIS3_W_REVERSE( 1 ) |                                              ULIS3_W_DEPTH( 1 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_CMYA8                          ( ULIS3_W_TYPE( ULIS3_TYPE_UINT8    ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_CMY )   | ULIS3_W_ALPHA( 1 ) |                                                                      ULIS3_W_DEPTH( 1 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_AYMC8                          ( ULIS3_W_TYPE( ULIS3_TYPE_UINT8    ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_CMY )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |                                              ULIS3_W_DEPTH( 1 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_ACMY8                          ( ULIS3_W_TYPE( ULIS3_TYPE_UINT8    ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_CMY )   | ULIS3_W_ALPHA( 1 ) |                          ULIS3_W_SWAP( 1 ) |                         ULIS3_W_DEPTH( 1 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_YMCA8                          ( ULIS3_W_TYPE( ULIS3_TYPE_UINT8    ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_CMY )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |  ULIS3_W_SWAP( 1 ) |                         ULIS3_W_DEPTH( 1 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_CMY16                          ( ULIS3_W_TYPE( ULIS3_TYPE_UINT16   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_CMY )   |                                                                                           ULIS3_W_DEPTH( 2 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_YMC16                          ( ULIS3_W_TYPE( ULIS3_TYPE_UINT16   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_CMY )   |                       ULIS3_W_REVERSE( 1 ) |                                              ULIS3_W_DEPTH( 2 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_CMYA16                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT16   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_CMY )   | ULIS3_W_ALPHA( 1 ) |                                                                      ULIS3_W_DEPTH( 2 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_AYMC16                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT16   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_CMY )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |                                              ULIS3_W_DEPTH( 2 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_ACMY16                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT16   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_CMY )   | ULIS3_W_ALPHA( 1 ) |                          ULIS3_W_SWAP( 1 ) |                         ULIS3_W_DEPTH( 2 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_YMCA16                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT16   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_CMY )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |  ULIS3_W_SWAP( 1 ) |                         ULIS3_W_DEPTH( 2 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_CMY32                          ( ULIS3_W_TYPE( ULIS3_TYPE_UINT32   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_CMY )   |                                                                                           ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_YMC32                          ( ULIS3_W_TYPE( ULIS3_TYPE_UINT32   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_CMY )   |                       ULIS3_W_REVERSE( 1 ) |                                              ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_CMYA32                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT32   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_CMY )   | ULIS3_W_ALPHA( 1 ) |                                                                      ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_AYMC32                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT32   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_CMY )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |                                              ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_ACMY32                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT32   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_CMY )   | ULIS3_W_ALPHA( 1 ) |                          ULIS3_W_SWAP( 1 ) |                         ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_YMCA32                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT32   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_CMY )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |  ULIS3_W_SWAP( 1 ) |                         ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_CMYF                           ( ULIS3_W_TYPE( ULIS3_TYPE_UFLOAT   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_CMY )   |                                                                   ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_YMCF                           ( ULIS3_W_TYPE( ULIS3_TYPE_UFLOAT   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_CMY )   |                       ULIS3_W_REVERSE( 1 ) |                      ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_CMYAF                          ( ULIS3_W_TYPE( ULIS3_TYPE_UFLOAT   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_CMY )   | ULIS3_W_ALPHA( 1 ) |                                              ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_AYMCF                          ( ULIS3_W_TYPE( ULIS3_TYPE_UFLOAT   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_CMY )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |                      ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_ACMYF                          ( ULIS3_W_TYPE( ULIS3_TYPE_UFLOAT   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_CMY )   | ULIS3_W_ALPHA( 1 ) |                          ULIS3_W_SWAP( 1 ) | ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_YMCAF                          ( ULIS3_W_TYPE( ULIS3_TYPE_UFLOAT   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_CMY )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |  ULIS3_W_SWAP( 1 ) | ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_CMYD                           ( ULIS3_W_TYPE( ULIS3_TYPE_UDOUBLE  ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_CMY )   |                                                                   ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 8 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_YMCD                           ( ULIS3_W_TYPE( ULIS3_TYPE_UDOUBLE  ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_CMY )   |                       ULIS3_W_REVERSE( 1 ) |                      ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 8 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_CMYAD                          ( ULIS3_W_TYPE( ULIS3_TYPE_UDOUBLE  ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_CMY )   | ULIS3_W_ALPHA( 1 ) |                                              ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 8 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_AYMCD                          ( ULIS3_W_TYPE( ULIS3_TYPE_UDOUBLE  ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_CMY )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |                      ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 8 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_ACMYD                          ( ULIS3_W_TYPE( ULIS3_TYPE_UDOUBLE  ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_CMY )   | ULIS3_W_ALPHA( 1 ) |                          ULIS3_W_SWAP( 1 ) | ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 8 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_YMCAD                          ( ULIS3_W_TYPE( ULIS3_TYPE_UDOUBLE  ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_CMY )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |  ULIS3_W_SWAP( 1 ) | ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 8 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_CMYK8                          ( ULIS3_W_TYPE( ULIS3_TYPE_UINT8    ) | ULIS3_W_CHANNELS( 4 ) | ULIS3_W_MODEL( ULIS3_CM_CMYK )  |                                                                                           ULIS3_W_DEPTH( 1 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_KCMY8                          ( ULIS3_W_TYPE( ULIS3_TYPE_UINT8    ) | ULIS3_W_CHANNELS( 4 ) | ULIS3_W_MODEL( ULIS3_CM_CMYK )  |                                               ULIS3_W_SWAP( 1 ) |                         ULIS3_W_DEPTH( 1 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_KYMC8                          ( ULIS3_W_TYPE( ULIS3_TYPE_UINT8    ) | ULIS3_W_CHANNELS( 4 ) | ULIS3_W_MODEL( ULIS3_CM_CMYK )  |                       ULIS3_W_REVERSE( 1 ) |                                              ULIS3_W_DEPTH( 1 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_YMCK8                          ( ULIS3_W_TYPE( ULIS3_TYPE_UINT8    ) | ULIS3_W_CHANNELS( 4 ) | ULIS3_W_MODEL( ULIS3_CM_CMYK )  |                       ULIS3_W_REVERSE( 1 ) |  ULIS3_W_SWAP( 1 ) |                         ULIS3_W_DEPTH( 1 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_CMYKA8                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT8    ) | ULIS3_W_CHANNELS( 4 ) | ULIS3_W_MODEL( ULIS3_CM_CMYK )  | ULIS3_W_ALPHA( 1 ) |                                                                      ULIS3_W_DEPTH( 1 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_ACMYK8                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT8    ) | ULIS3_W_CHANNELS( 4 ) | ULIS3_W_MODEL( ULIS3_CM_CMYK )  | ULIS3_W_ALPHA( 1 ) |                          ULIS3_W_SWAP( 1 ) |                         ULIS3_W_DEPTH( 1 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_AKYMC8                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT8    ) | ULIS3_W_CHANNELS( 4 ) | ULIS3_W_MODEL( ULIS3_CM_CMYK )  | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |                                              ULIS3_W_DEPTH( 1 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_KYMCA8                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT8    ) | ULIS3_W_CHANNELS( 4 ) | ULIS3_W_MODEL( ULIS3_CM_CMYK )  | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |  ULIS3_W_SWAP( 1 ) |                         ULIS3_W_DEPTH( 1 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_CMYK16                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT16   ) | ULIS3_W_CHANNELS( 4 ) | ULIS3_W_MODEL( ULIS3_CM_CMYK )  |                                                                                           ULIS3_W_DEPTH( 2 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_KCMY16                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT16   ) | ULIS3_W_CHANNELS( 4 ) | ULIS3_W_MODEL( ULIS3_CM_CMYK )  |                                               ULIS3_W_SWAP( 1 ) |                         ULIS3_W_DEPTH( 2 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_KYMC16                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT16   ) | ULIS3_W_CHANNELS( 4 ) | ULIS3_W_MODEL( ULIS3_CM_CMYK )  |                       ULIS3_W_REVERSE( 1 ) |                                              ULIS3_W_DEPTH( 2 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_YMCK16                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT16   ) | ULIS3_W_CHANNELS( 4 ) | ULIS3_W_MODEL( ULIS3_CM_CMYK )  |                       ULIS3_W_REVERSE( 1 ) |  ULIS3_W_SWAP( 1 ) |                         ULIS3_W_DEPTH( 2 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_CMYKA16                        ( ULIS3_W_TYPE( ULIS3_TYPE_UINT16   ) | ULIS3_W_CHANNELS( 4 ) | ULIS3_W_MODEL( ULIS3_CM_CMYK )  | ULIS3_W_ALPHA( 1 ) |                                                                      ULIS3_W_DEPTH( 2 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_ACMYK16                        ( ULIS3_W_TYPE( ULIS3_TYPE_UINT16   ) | ULIS3_W_CHANNELS( 4 ) | ULIS3_W_MODEL( ULIS3_CM_CMYK )  | ULIS3_W_ALPHA( 1 ) |                          ULIS3_W_SWAP( 1 ) |                         ULIS3_W_DEPTH( 2 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_AKYMC16                        ( ULIS3_W_TYPE( ULIS3_TYPE_UINT16   ) | ULIS3_W_CHANNELS( 4 ) | ULIS3_W_MODEL( ULIS3_CM_CMYK )  | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |                                              ULIS3_W_DEPTH( 2 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_KYMCA16                        ( ULIS3_W_TYPE( ULIS3_TYPE_UINT16   ) | ULIS3_W_CHANNELS( 4 ) | ULIS3_W_MODEL( ULIS3_CM_CMYK )  | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |  ULIS3_W_SWAP( 1 ) |                         ULIS3_W_DEPTH( 2 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_CMYK32                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT32   ) | ULIS3_W_CHANNELS( 4 ) | ULIS3_W_MODEL( ULIS3_CM_CMYK )  |                                                                                           ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_KCMY32                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT32   ) | ULIS3_W_CHANNELS( 4 ) | ULIS3_W_MODEL( ULIS3_CM_CMYK )  |                                               ULIS3_W_SWAP( 1 ) |                         ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_KYMC32                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT32   ) | ULIS3_W_CHANNELS( 4 ) | ULIS3_W_MODEL( ULIS3_CM_CMYK )  |                       ULIS3_W_REVERSE( 1 ) |                                              ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_YMCK32                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT32   ) | ULIS3_W_CHANNELS( 4 ) | ULIS3_W_MODEL( ULIS3_CM_CMYK )  |                       ULIS3_W_REVERSE( 1 ) |  ULIS3_W_SWAP( 1 ) |                         ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_CMYKA32                        ( ULIS3_W_TYPE( ULIS3_TYPE_UINT32   ) | ULIS3_W_CHANNELS( 4 ) | ULIS3_W_MODEL( ULIS3_CM_CMYK )  | ULIS3_W_ALPHA( 1 ) |                                                                      ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_ACMYK32                        ( ULIS3_W_TYPE( ULIS3_TYPE_UINT32   ) | ULIS3_W_CHANNELS( 4 ) | ULIS3_W_MODEL( ULIS3_CM_CMYK )  | ULIS3_W_ALPHA( 1 ) |                          ULIS3_W_SWAP( 1 ) |                         ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_AKYMC32                        ( ULIS3_W_TYPE( ULIS3_TYPE_UINT32   ) | ULIS3_W_CHANNELS( 4 ) | ULIS3_W_MODEL( ULIS3_CM_CMYK )  | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |                                              ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_KYMCA32                        ( ULIS3_W_TYPE( ULIS3_TYPE_UINT32   ) | ULIS3_W_CHANNELS( 4 ) | ULIS3_W_MODEL( ULIS3_CM_CMYK )  | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |  ULIS3_W_SWAP( 1 ) |                         ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_CMYKF                          ( ULIS3_W_TYPE( ULIS3_TYPE_UFLOAT   ) | ULIS3_W_CHANNELS( 4 ) | ULIS3_W_MODEL( ULIS3_CM_CMYK )  |                                                                   ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_KCMYF                          ( ULIS3_W_TYPE( ULIS3_TYPE_UFLOAT   ) | ULIS3_W_CHANNELS( 4 ) | ULIS3_W_MODEL( ULIS3_CM_CMYK )  |                                               ULIS3_W_SWAP( 1 ) | ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_KYMCF                          ( ULIS3_W_TYPE( ULIS3_TYPE_UFLOAT   ) | ULIS3_W_CHANNELS( 4 ) | ULIS3_W_MODEL( ULIS3_CM_CMYK )  |                       ULIS3_W_REVERSE( 1 ) |                      ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_YMCKF                          ( ULIS3_W_TYPE( ULIS3_TYPE_UFLOAT   ) | ULIS3_W_CHANNELS( 4 ) | ULIS3_W_MODEL( ULIS3_CM_CMYK )  |                       ULIS3_W_REVERSE( 1 ) |  ULIS3_W_SWAP( 1 ) | ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_CMYKAF                         ( ULIS3_W_TYPE( ULIS3_TYPE_UFLOAT   ) | ULIS3_W_CHANNELS( 4 ) | ULIS3_W_MODEL( ULIS3_CM_CMYK )  | ULIS3_W_ALPHA( 1 ) |                                              ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_ACMYKF                         ( ULIS3_W_TYPE( ULIS3_TYPE_UFLOAT   ) | ULIS3_W_CHANNELS( 4 ) | ULIS3_W_MODEL( ULIS3_CM_CMYK )  | ULIS3_W_ALPHA( 1 ) |                          ULIS3_W_SWAP( 1 ) | ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_AKYMCF                         ( ULIS3_W_TYPE( ULIS3_TYPE_UFLOAT   ) | ULIS3_W_CHANNELS( 4 ) | ULIS3_W_MODEL( ULIS3_CM_CMYK )  | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |                      ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_KYMCAF                         ( ULIS3_W_TYPE( ULIS3_TYPE_UFLOAT   ) | ULIS3_W_CHANNELS( 4 ) | ULIS3_W_MODEL( ULIS3_CM_CMYK )  | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |  ULIS3_W_SWAP( 1 ) | ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_CMYKD                          ( ULIS3_W_TYPE( ULIS3_TYPE_UDOUBLE  ) | ULIS3_W_CHANNELS( 4 ) | ULIS3_W_MODEL( ULIS3_CM_CMYK )  |                                                                   ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 8 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_KCMYD                          ( ULIS3_W_TYPE( ULIS3_TYPE_UDOUBLE  ) | ULIS3_W_CHANNELS( 4 ) | ULIS3_W_MODEL( ULIS3_CM_CMYK )  |                                               ULIS3_W_SWAP( 1 ) | ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 8 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_KYMCD                          ( ULIS3_W_TYPE( ULIS3_TYPE_UDOUBLE  ) | ULIS3_W_CHANNELS( 4 ) | ULIS3_W_MODEL( ULIS3_CM_CMYK )  |                       ULIS3_W_REVERSE( 1 ) |                      ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 8 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_YMCKD                          ( ULIS3_W_TYPE( ULIS3_TYPE_UDOUBLE  ) | ULIS3_W_CHANNELS( 4 ) | ULIS3_W_MODEL( ULIS3_CM_CMYK )  |                       ULIS3_W_REVERSE( 1 ) |  ULIS3_W_SWAP( 1 ) | ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 8 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_CMYKAD                         ( ULIS3_W_TYPE( ULIS3_TYPE_UDOUBLE  ) | ULIS3_W_CHANNELS( 4 ) | ULIS3_W_MODEL( ULIS3_CM_CMYK )  | ULIS3_W_ALPHA( 1 ) |                                              ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 8 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_ACMYKD                         ( ULIS3_W_TYPE( ULIS3_TYPE_UDOUBLE  ) | ULIS3_W_CHANNELS( 4 ) | ULIS3_W_MODEL( ULIS3_CM_CMYK )  | ULIS3_W_ALPHA( 1 ) |                          ULIS3_W_SWAP( 1 ) | ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 8 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_AKYMCD                         ( ULIS3_W_TYPE( ULIS3_TYPE_UDOUBLE  ) | ULIS3_W_CHANNELS( 4 ) | ULIS3_W_MODEL( ULIS3_CM_CMYK )  | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |                      ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 8 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_KYMCAD                         ( ULIS3_W_TYPE( ULIS3_TYPE_UDOUBLE  ) | ULIS3_W_CHANNELS( 4 ) | ULIS3_W_MODEL( ULIS3_CM_CMYK )  | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |  ULIS3_W_SWAP( 1 ) | ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 8 ) | ULIS3_W_PROFILE( ULIS3_sRGB ) )
#define ULIS3_FORMAT_YUV8                           ( ULIS3_W_TYPE( ULIS3_TYPE_UINT8    ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_YUV )   |                                                                                           ULIS3_W_DEPTH( 1 ) | ULIS3_W_PROFILE( ULIS3_YUV ) )
#define ULIS3_FORMAT_VUY8                           ( ULIS3_W_TYPE( ULIS3_TYPE_UINT8    ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_YUV )   |                       ULIS3_W_REVERSE( 1 ) |                                              ULIS3_W_DEPTH( 1 ) | ULIS3_W_PROFILE( ULIS3_YUV ) )
#define ULIS3_FORMAT_YUVA8                          ( ULIS3_W_TYPE( ULIS3_TYPE_UINT8    ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_YUV )   | ULIS3_W_ALPHA( 1 ) |                                                                      ULIS3_W_DEPTH( 1 ) | ULIS3_W_PROFILE( ULIS3_YUV ) )
#define ULIS3_FORMAT_AVUY8                          ( ULIS3_W_TYPE( ULIS3_TYPE_UINT8    ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_YUV )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |                                              ULIS3_W_DEPTH( 1 ) | ULIS3_W_PROFILE( ULIS3_YUV ) )
#define ULIS3_FORMAT_AYUV8                          ( ULIS3_W_TYPE( ULIS3_TYPE_UINT8    ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_YUV )   | ULIS3_W_ALPHA( 1 ) |                          ULIS3_W_SWAP( 1 ) |                         ULIS3_W_DEPTH( 1 ) | ULIS3_W_PROFILE( ULIS3_YUV ) )
#define ULIS3_FORMAT_VUYA8                          ( ULIS3_W_TYPE( ULIS3_TYPE_UINT8    ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_YUV )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |  ULIS3_W_SWAP( 1 ) |                         ULIS3_W_DEPTH( 1 ) | ULIS3_W_PROFILE( ULIS3_YUV ) )
#define ULIS3_FORMAT_YUV16                          ( ULIS3_W_TYPE( ULIS3_TYPE_UINT16   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_YUV )   |                                                                                           ULIS3_W_DEPTH( 2 ) | ULIS3_W_PROFILE( ULIS3_YUV ) )
#define ULIS3_FORMAT_VUY16                          ( ULIS3_W_TYPE( ULIS3_TYPE_UINT16   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_YUV )   |                       ULIS3_W_REVERSE( 1 ) |                                              ULIS3_W_DEPTH( 2 ) | ULIS3_W_PROFILE( ULIS3_YUV ) )
#define ULIS3_FORMAT_YUVA16                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT16   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_YUV )   | ULIS3_W_ALPHA( 1 ) |                                                                      ULIS3_W_DEPTH( 2 ) | ULIS3_W_PROFILE( ULIS3_YUV ) )
#define ULIS3_FORMAT_AVUY16                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT16   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_YUV )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |                                              ULIS3_W_DEPTH( 2 ) | ULIS3_W_PROFILE( ULIS3_YUV ) )
#define ULIS3_FORMAT_AYUV16                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT16   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_YUV )   | ULIS3_W_ALPHA( 1 ) |                          ULIS3_W_SWAP( 1 ) |                         ULIS3_W_DEPTH( 2 ) | ULIS3_W_PROFILE( ULIS3_YUV ) )
#define ULIS3_FORMAT_VUYA16                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT16   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_YUV )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |  ULIS3_W_SWAP( 1 ) |                         ULIS3_W_DEPTH( 2 ) | ULIS3_W_PROFILE( ULIS3_YUV ) )
#define ULIS3_FORMAT_YUV32                          ( ULIS3_W_TYPE( ULIS3_TYPE_UINT32   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_YUV )   |                                                                                           ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_YUV ) )
#define ULIS3_FORMAT_VUY32                          ( ULIS3_W_TYPE( ULIS3_TYPE_UINT32   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_YUV )   |                       ULIS3_W_REVERSE( 1 ) |                                              ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_YUV ) )
#define ULIS3_FORMAT_YUVA32                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT32   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_YUV )   | ULIS3_W_ALPHA( 1 ) |                                                                      ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_YUV ) )
#define ULIS3_FORMAT_AVUY32                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT32   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_YUV )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |                                              ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_YUV ) )
#define ULIS3_FORMAT_AYUV32                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT32   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_YUV )   | ULIS3_W_ALPHA( 1 ) |                          ULIS3_W_SWAP( 1 ) |                         ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_YUV ) )
#define ULIS3_FORMAT_VUYA32                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT32   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_YUV )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |  ULIS3_W_SWAP( 1 ) |                         ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_YUV ) )
#define ULIS3_FORMAT_YUVF                           ( ULIS3_W_TYPE( ULIS3_TYPE_UFLOAT   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_YUV )   |                                                                   ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_YUV ) )
#define ULIS3_FORMAT_VUYF                           ( ULIS3_W_TYPE( ULIS3_TYPE_UFLOAT   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_YUV )   |                       ULIS3_W_REVERSE( 1 ) |                      ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_YUV ) )
#define ULIS3_FORMAT_YUVAF                          ( ULIS3_W_TYPE( ULIS3_TYPE_UFLOAT   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_YUV )   | ULIS3_W_ALPHA( 1 ) |                                              ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_YUV ) )
#define ULIS3_FORMAT_AVUYF                          ( ULIS3_W_TYPE( ULIS3_TYPE_UFLOAT   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_YUV )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |                      ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_YUV ) )
#define ULIS3_FORMAT_AYUVF                          ( ULIS3_W_TYPE( ULIS3_TYPE_UFLOAT   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_YUV )   | ULIS3_W_ALPHA( 1 ) |                          ULIS3_W_SWAP( 1 ) | ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_YUV ) )
#define ULIS3_FORMAT_VUYAF                          ( ULIS3_W_TYPE( ULIS3_TYPE_UFLOAT   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_YUV )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |  ULIS3_W_SWAP( 1 ) | ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_YUV ) )
#define ULIS3_FORMAT_YUVD                           ( ULIS3_W_TYPE( ULIS3_TYPE_UDOUBLE  ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_YUV )   |                                                                   ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 8 ) | ULIS3_W_PROFILE( ULIS3_YUV ) )
#define ULIS3_FORMAT_VUYD                           ( ULIS3_W_TYPE( ULIS3_TYPE_UDOUBLE  ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_YUV )   |                       ULIS3_W_REVERSE( 1 ) |                      ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 8 ) | ULIS3_W_PROFILE( ULIS3_YUV ) )
#define ULIS3_FORMAT_YUVAD                          ( ULIS3_W_TYPE( ULIS3_TYPE_UDOUBLE  ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_YUV )   | ULIS3_W_ALPHA( 1 ) |                                              ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 8 ) | ULIS3_W_PROFILE( ULIS3_YUV ) )
#define ULIS3_FORMAT_AVUYD                          ( ULIS3_W_TYPE( ULIS3_TYPE_UDOUBLE  ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_YUV )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |                      ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 8 ) | ULIS3_W_PROFILE( ULIS3_YUV ) )
#define ULIS3_FORMAT_AYUVD                          ( ULIS3_W_TYPE( ULIS3_TYPE_UDOUBLE  ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_YUV )   | ULIS3_W_ALPHA( 1 ) |                          ULIS3_W_SWAP( 1 ) | ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 8 ) | ULIS3_W_PROFILE( ULIS3_YUV ) )
#define ULIS3_FORMAT_VUYAD                          ( ULIS3_W_TYPE( ULIS3_TYPE_UDOUBLE  ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_YUV )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |  ULIS3_W_SWAP( 1 ) | ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 8 ) | ULIS3_W_PROFILE( ULIS3_YUV ) )
#define ULIS3_FORMAT_Lab8                           ( ULIS3_W_TYPE( ULIS3_TYPE_UINT8    ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_Lab )   |                                                                                           ULIS3_W_DEPTH( 1 ) | ULIS3_W_PROFILE( ULIS3_LabD65 ) )
#define ULIS3_FORMAT_baL8                           ( ULIS3_W_TYPE( ULIS3_TYPE_UINT8    ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_Lab )   |                       ULIS3_W_REVERSE( 1 ) |                                              ULIS3_W_DEPTH( 1 ) | ULIS3_W_PROFILE( ULIS3_LabD65 ) )
#define ULIS3_FORMAT_LabA8                          ( ULIS3_W_TYPE( ULIS3_TYPE_UINT8    ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_Lab )   | ULIS3_W_ALPHA( 1 ) |                                                                      ULIS3_W_DEPTH( 1 ) | ULIS3_W_PROFILE( ULIS3_LabD65 ) )
#define ULIS3_FORMAT_AbaL8                          ( ULIS3_W_TYPE( ULIS3_TYPE_UINT8    ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_Lab )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |                                              ULIS3_W_DEPTH( 1 ) | ULIS3_W_PROFILE( ULIS3_LabD65 ) )
#define ULIS3_FORMAT_ALab8                          ( ULIS3_W_TYPE( ULIS3_TYPE_UINT8    ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_Lab )   | ULIS3_W_ALPHA( 1 ) |                          ULIS3_W_SWAP( 1 ) |                         ULIS3_W_DEPTH( 1 ) | ULIS3_W_PROFILE( ULIS3_LabD65 ) )
#define ULIS3_FORMAT_baLA8                          ( ULIS3_W_TYPE( ULIS3_TYPE_UINT8    ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_Lab )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |  ULIS3_W_SWAP( 1 ) |                         ULIS3_W_DEPTH( 1 ) | ULIS3_W_PROFILE( ULIS3_LabD65 ) )
#define ULIS3_FORMAT_Lab16                          ( ULIS3_W_TYPE( ULIS3_TYPE_UINT16   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_Lab )   |                                                                                           ULIS3_W_DEPTH( 2 ) | ULIS3_W_PROFILE( ULIS3_LabD65 ) )
#define ULIS3_FORMAT_baL16                          ( ULIS3_W_TYPE( ULIS3_TYPE_UINT16   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_Lab )   |                       ULIS3_W_REVERSE( 1 ) |                                              ULIS3_W_DEPTH( 2 ) | ULIS3_W_PROFILE( ULIS3_LabD65 ) )
#define ULIS3_FORMAT_LabA16                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT16   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_Lab )   | ULIS3_W_ALPHA( 1 ) |                                                                      ULIS3_W_DEPTH( 2 ) | ULIS3_W_PROFILE( ULIS3_LabD65 ) )
#define ULIS3_FORMAT_AbaL16                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT16   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_Lab )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |                                              ULIS3_W_DEPTH( 2 ) | ULIS3_W_PROFILE( ULIS3_LabD65 ) )
#define ULIS3_FORMAT_ALab16                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT16   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_Lab )   | ULIS3_W_ALPHA( 1 ) |                          ULIS3_W_SWAP( 1 ) |                         ULIS3_W_DEPTH( 2 ) | ULIS3_W_PROFILE( ULIS3_LabD65 ) )
#define ULIS3_FORMAT_baLA16                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT16   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_Lab )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |  ULIS3_W_SWAP( 1 ) |                         ULIS3_W_DEPTH( 2 ) | ULIS3_W_PROFILE( ULIS3_LabD65 ) )
#define ULIS3_FORMAT_Lab32                          ( ULIS3_W_TYPE( ULIS3_TYPE_UINT32   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_Lab )   |                                                                                           ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_LabD65 ) )
#define ULIS3_FORMAT_baL32                          ( ULIS3_W_TYPE( ULIS3_TYPE_UINT32   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_Lab )   |                       ULIS3_W_REVERSE( 1 ) |                                              ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_LabD65 ) )
#define ULIS3_FORMAT_LabA32                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT32   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_Lab )   | ULIS3_W_ALPHA( 1 ) |                                                                      ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_LabD65 ) )
#define ULIS3_FORMAT_AbaL32                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT32   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_Lab )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |                                              ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_LabD65 ) )
#define ULIS3_FORMAT_ALab32                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT32   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_Lab )   | ULIS3_W_ALPHA( 1 ) |                          ULIS3_W_SWAP( 1 ) |                         ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_LabD65 ) )
#define ULIS3_FORMAT_baLA32                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT32   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_Lab )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |  ULIS3_W_SWAP( 1 ) |                         ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_LabD65 ) )
#define ULIS3_FORMAT_LabF                           ( ULIS3_W_TYPE( ULIS3_TYPE_UFLOAT   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_Lab )   |                                                                   ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_LabD65 ) )
#define ULIS3_FORMAT_baLF                           ( ULIS3_W_TYPE( ULIS3_TYPE_UFLOAT   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_Lab )   |                       ULIS3_W_REVERSE( 1 ) |                      ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_LabD65 ) )
#define ULIS3_FORMAT_LabAF                          ( ULIS3_W_TYPE( ULIS3_TYPE_UFLOAT   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_Lab )   | ULIS3_W_ALPHA( 1 ) |                                              ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_LabD65 ) )
#define ULIS3_FORMAT_AbaLF                          ( ULIS3_W_TYPE( ULIS3_TYPE_UFLOAT   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_Lab )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |                      ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_LabD65 ) )
#define ULIS3_FORMAT_ALabF                          ( ULIS3_W_TYPE( ULIS3_TYPE_UFLOAT   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_Lab )   | ULIS3_W_ALPHA( 1 ) |                          ULIS3_W_SWAP( 1 ) | ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_LabD65 ) )
#define ULIS3_FORMAT_baLAF                          ( ULIS3_W_TYPE( ULIS3_TYPE_UFLOAT   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_Lab )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |  ULIS3_W_SWAP( 1 ) | ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_LabD65 ) )
#define ULIS3_FORMAT_LabD                           ( ULIS3_W_TYPE( ULIS3_TYPE_UDOUBLE  ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_Lab )   |                                                                   ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 8 ) | ULIS3_W_PROFILE( ULIS3_LabD65 ) )
#define ULIS3_FORMAT_baLD                           ( ULIS3_W_TYPE( ULIS3_TYPE_UDOUBLE  ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_Lab )   |                       ULIS3_W_REVERSE( 1 ) |                      ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 8 ) | ULIS3_W_PROFILE( ULIS3_LabD65 ) )
#define ULIS3_FORMAT_LabAD                          ( ULIS3_W_TYPE( ULIS3_TYPE_UDOUBLE  ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_Lab )   | ULIS3_W_ALPHA( 1 ) |                                              ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 8 ) | ULIS3_W_PROFILE( ULIS3_LabD65 ) )
#define ULIS3_FORMAT_AbaLD                          ( ULIS3_W_TYPE( ULIS3_TYPE_UDOUBLE  ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_Lab )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |                      ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 8 ) | ULIS3_W_PROFILE( ULIS3_LabD65 ) )
#define ULIS3_FORMAT_ALabD                          ( ULIS3_W_TYPE( ULIS3_TYPE_UDOUBLE  ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_Lab )   | ULIS3_W_ALPHA( 1 ) |                          ULIS3_W_SWAP( 1 ) | ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 8 ) | ULIS3_W_PROFILE( ULIS3_LabD65 ) )
#define ULIS3_FORMAT_baLAD                          ( ULIS3_W_TYPE( ULIS3_TYPE_UDOUBLE  ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_Lab )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |  ULIS3_W_SWAP( 1 ) | ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 8 ) | ULIS3_W_PROFILE( ULIS3_LabD65 ) )
#define ULIS3_FORMAT_XYZ8                           ( ULIS3_W_TYPE( ULIS3_TYPE_UINT8    ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_XYZ )   |                                                                                           ULIS3_W_DEPTH( 1 ) | ULIS3_W_PROFILE( ULIS3_XYZ ) )
#define ULIS3_FORMAT_ZYX8                           ( ULIS3_W_TYPE( ULIS3_TYPE_UINT8    ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_XYZ )   |                       ULIS3_W_REVERSE( 1 ) |                                              ULIS3_W_DEPTH( 1 ) | ULIS3_W_PROFILE( ULIS3_XYZ ) )
#define ULIS3_FORMAT_XYZA8                          ( ULIS3_W_TYPE( ULIS3_TYPE_UINT8    ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_XYZ )   | ULIS3_W_ALPHA( 1 ) |                                                                      ULIS3_W_DEPTH( 1 ) | ULIS3_W_PROFILE( ULIS3_XYZ ) )
#define ULIS3_FORMAT_AZYX8                          ( ULIS3_W_TYPE( ULIS3_TYPE_UINT8    ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_XYZ )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |                                              ULIS3_W_DEPTH( 1 ) | ULIS3_W_PROFILE( ULIS3_XYZ ) )
#define ULIS3_FORMAT_AXYZ8                          ( ULIS3_W_TYPE( ULIS3_TYPE_UINT8    ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_XYZ )   | ULIS3_W_ALPHA( 1 ) |                          ULIS3_W_SWAP( 1 ) |                         ULIS3_W_DEPTH( 1 ) | ULIS3_W_PROFILE( ULIS3_XYZ ) )
#define ULIS3_FORMAT_ZYXA8                          ( ULIS3_W_TYPE( ULIS3_TYPE_UINT8    ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_XYZ )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |  ULIS3_W_SWAP( 1 ) |                         ULIS3_W_DEPTH( 1 ) | ULIS3_W_PROFILE( ULIS3_XYZ ) )
#define ULIS3_FORMAT_XYZ16                          ( ULIS3_W_TYPE( ULIS3_TYPE_UINT16   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_XYZ )   |                                                                                           ULIS3_W_DEPTH( 2 ) | ULIS3_W_PROFILE( ULIS3_XYZ ) )
#define ULIS3_FORMAT_ZYX16                          ( ULIS3_W_TYPE( ULIS3_TYPE_UINT16   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_XYZ )   |                       ULIS3_W_REVERSE( 1 ) |                                              ULIS3_W_DEPTH( 2 ) | ULIS3_W_PROFILE( ULIS3_XYZ ) )
#define ULIS3_FORMAT_XYZA16                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT16   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_XYZ )   | ULIS3_W_ALPHA( 1 ) |                                                                      ULIS3_W_DEPTH( 2 ) | ULIS3_W_PROFILE( ULIS3_XYZ ) )
#define ULIS3_FORMAT_AZYX16                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT16   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_XYZ )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |                                              ULIS3_W_DEPTH( 2 ) | ULIS3_W_PROFILE( ULIS3_XYZ ) )
#define ULIS3_FORMAT_AXYZ16                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT16   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_XYZ )   | ULIS3_W_ALPHA( 1 ) |                          ULIS3_W_SWAP( 1 ) |                         ULIS3_W_DEPTH( 2 ) | ULIS3_W_PROFILE( ULIS3_XYZ ) )
#define ULIS3_FORMAT_ZYXA16                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT16   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_XYZ )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |  ULIS3_W_SWAP( 1 ) |                         ULIS3_W_DEPTH( 2 ) | ULIS3_W_PROFILE( ULIS3_XYZ ) )
#define ULIS3_FORMAT_XYZ32                          ( ULIS3_W_TYPE( ULIS3_TYPE_UINT32   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_XYZ )   |                                                                                           ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_XYZ ) )
#define ULIS3_FORMAT_ZYX32                          ( ULIS3_W_TYPE( ULIS3_TYPE_UINT32   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_XYZ )   |                       ULIS3_W_REVERSE( 1 ) |                                              ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_XYZ ) )
#define ULIS3_FORMAT_XYZA32                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT32   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_XYZ )   | ULIS3_W_ALPHA( 1 ) |                                                                      ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_XYZ ) )
#define ULIS3_FORMAT_AZYX32                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT32   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_XYZ )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |                                              ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_XYZ ) )
#define ULIS3_FORMAT_AXYZ32                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT32   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_XYZ )   | ULIS3_W_ALPHA( 1 ) |                          ULIS3_W_SWAP( 1 ) |                         ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_XYZ ) )
#define ULIS3_FORMAT_ZYXA32                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT32   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_XYZ )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |  ULIS3_W_SWAP( 1 ) |                         ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_XYZ ) )
#define ULIS3_FORMAT_XYZF                           ( ULIS3_W_TYPE( ULIS3_TYPE_UFLOAT   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_XYZ )   |                                                                   ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_XYZ ) )
#define ULIS3_FORMAT_ZYXF                           ( ULIS3_W_TYPE( ULIS3_TYPE_UFLOAT   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_XYZ )   |                       ULIS3_W_REVERSE( 1 ) |                      ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_XYZ ) )
#define ULIS3_FORMAT_XYZAF                          ( ULIS3_W_TYPE( ULIS3_TYPE_UFLOAT   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_XYZ )   | ULIS3_W_ALPHA( 1 ) |                                              ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_XYZ ) )
#define ULIS3_FORMAT_AZYXF                          ( ULIS3_W_TYPE( ULIS3_TYPE_UFLOAT   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_XYZ )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |                      ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_XYZ ) )
#define ULIS3_FORMAT_AXYZF                          ( ULIS3_W_TYPE( ULIS3_TYPE_UFLOAT   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_XYZ )   | ULIS3_W_ALPHA( 1 ) |                          ULIS3_W_SWAP( 1 ) | ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_XYZ ) )
#define ULIS3_FORMAT_ZYXAF                          ( ULIS3_W_TYPE( ULIS3_TYPE_UFLOAT   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_XYZ )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |  ULIS3_W_SWAP( 1 ) | ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_XYZ ) )
#define ULIS3_FORMAT_XYZD                           ( ULIS3_W_TYPE( ULIS3_TYPE_UDOUBLE  ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_XYZ )   |                                                                   ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 8 ) | ULIS3_W_PROFILE( ULIS3_XYZ ) )
#define ULIS3_FORMAT_ZYXD                           ( ULIS3_W_TYPE( ULIS3_TYPE_UDOUBLE  ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_XYZ )   |                       ULIS3_W_REVERSE( 1 ) |                      ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 8 ) | ULIS3_W_PROFILE( ULIS3_XYZ ) )
#define ULIS3_FORMAT_XYZAD                          ( ULIS3_W_TYPE( ULIS3_TYPE_UDOUBLE  ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_XYZ )   | ULIS3_W_ALPHA( 1 ) |                                              ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 8 ) | ULIS3_W_PROFILE( ULIS3_XYZ ) )
#define ULIS3_FORMAT_AZYXD                          ( ULIS3_W_TYPE( ULIS3_TYPE_UDOUBLE  ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_XYZ )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |                      ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 8 ) | ULIS3_W_PROFILE( ULIS3_XYZ ) )
#define ULIS3_FORMAT_AXYZD                          ( ULIS3_W_TYPE( ULIS3_TYPE_UDOUBLE  ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_XYZ )   | ULIS3_W_ALPHA( 1 ) |                          ULIS3_W_SWAP( 1 ) | ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 8 ) | ULIS3_W_PROFILE( ULIS3_XYZ ) )
#define ULIS3_FORMAT_ZYXAD                          ( ULIS3_W_TYPE( ULIS3_TYPE_UDOUBLE  ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_XYZ )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |  ULIS3_W_SWAP( 1 ) | ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 8 ) | ULIS3_W_PROFILE( ULIS3_XYZ ) )
#define ULIS3_FORMAT_Yxy8                           ( ULIS3_W_TYPE( ULIS3_TYPE_UINT8    ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_Yxy )   |                                                                                           ULIS3_W_DEPTH( 1 ) | ULIS3_W_PROFILE( ULIS3_Yxy ) )
#define ULIS3_FORMAT_yxY8                           ( ULIS3_W_TYPE( ULIS3_TYPE_UINT8    ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_Yxy )   |                       ULIS3_W_REVERSE( 1 ) |                                              ULIS3_W_DEPTH( 1 ) | ULIS3_W_PROFILE( ULIS3_Yxy ) )
#define ULIS3_FORMAT_YxyA8                          ( ULIS3_W_TYPE( ULIS3_TYPE_UINT8    ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_Yxy )   | ULIS3_W_ALPHA( 1 ) |                                                                      ULIS3_W_DEPTH( 1 ) | ULIS3_W_PROFILE( ULIS3_Yxy ) )
#define ULIS3_FORMAT_AyxY8                          ( ULIS3_W_TYPE( ULIS3_TYPE_UINT8    ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_Yxy )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |                                              ULIS3_W_DEPTH( 1 ) | ULIS3_W_PROFILE( ULIS3_Yxy ) )
#define ULIS3_FORMAT_AYxy8                          ( ULIS3_W_TYPE( ULIS3_TYPE_UINT8    ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_Yxy )   | ULIS3_W_ALPHA( 1 ) |                          ULIS3_W_SWAP( 1 ) |                         ULIS3_W_DEPTH( 1 ) | ULIS3_W_PROFILE( ULIS3_Yxy ) )
#define ULIS3_FORMAT_yxYA8                          ( ULIS3_W_TYPE( ULIS3_TYPE_UINT8    ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_Yxy )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |  ULIS3_W_SWAP( 1 ) |                         ULIS3_W_DEPTH( 1 ) | ULIS3_W_PROFILE( ULIS3_Yxy ) )
#define ULIS3_FORMAT_Yxy16                          ( ULIS3_W_TYPE( ULIS3_TYPE_UINT16   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_Yxy )   |                                                                                           ULIS3_W_DEPTH( 2 ) | ULIS3_W_PROFILE( ULIS3_Yxy ) )
#define ULIS3_FORMAT_yxY16                          ( ULIS3_W_TYPE( ULIS3_TYPE_UINT16   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_Yxy )   |                       ULIS3_W_REVERSE( 1 ) |                                              ULIS3_W_DEPTH( 2 ) | ULIS3_W_PROFILE( ULIS3_Yxy ) )
#define ULIS3_FORMAT_YxyA16                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT16   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_Yxy )   | ULIS3_W_ALPHA( 1 ) |                                                                      ULIS3_W_DEPTH( 2 ) | ULIS3_W_PROFILE( ULIS3_Yxy ) )
#define ULIS3_FORMAT_AyxY16                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT16   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_Yxy )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |                                              ULIS3_W_DEPTH( 2 ) | ULIS3_W_PROFILE( ULIS3_Yxy ) )
#define ULIS3_FORMAT_AYxy16                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT16   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_Yxy )   | ULIS3_W_ALPHA( 1 ) |                          ULIS3_W_SWAP( 1 ) |                         ULIS3_W_DEPTH( 2 ) | ULIS3_W_PROFILE( ULIS3_Yxy ) )
#define ULIS3_FORMAT_yxYA16                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT16   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_Yxy )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |  ULIS3_W_SWAP( 1 ) |                         ULIS3_W_DEPTH( 2 ) | ULIS3_W_PROFILE( ULIS3_Yxy ) )
#define ULIS3_FORMAT_Yxy32                          ( ULIS3_W_TYPE( ULIS3_TYPE_UINT32   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_Yxy )   |                                                                                           ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_Yxy ) )
#define ULIS3_FORMAT_yxY32                          ( ULIS3_W_TYPE( ULIS3_TYPE_UINT32   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_Yxy )   |                       ULIS3_W_REVERSE( 1 ) |                                              ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_Yxy ) )
#define ULIS3_FORMAT_YxyA32                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT32   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_Yxy )   | ULIS3_W_ALPHA( 1 ) |                                                                      ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_Yxy ) )
#define ULIS3_FORMAT_AyxY32                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT32   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_Yxy )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |                                              ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_Yxy ) )
#define ULIS3_FORMAT_AYxy32                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT32   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_Yxy )   | ULIS3_W_ALPHA( 1 ) |                          ULIS3_W_SWAP( 1 ) |                         ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_Yxy ) )
#define ULIS3_FORMAT_yxYA32                         ( ULIS3_W_TYPE( ULIS3_TYPE_UINT32   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_Yxy )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |  ULIS3_W_SWAP( 1 ) |                         ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_Yxy ) )
#define ULIS3_FORMAT_YxyF                           ( ULIS3_W_TYPE( ULIS3_TYPE_UFLOAT   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_Yxy )   |                                                                   ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_Yxy ) )
#define ULIS3_FORMAT_yxYF                           ( ULIS3_W_TYPE( ULIS3_TYPE_UFLOAT   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_Yxy )   |                       ULIS3_W_REVERSE( 1 ) |                      ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_Yxy ) )
#define ULIS3_FORMAT_YxyAF                          ( ULIS3_W_TYPE( ULIS3_TYPE_UFLOAT   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_Yxy )   | ULIS3_W_ALPHA( 1 ) |                                              ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_Yxy ) )
#define ULIS3_FORMAT_AyxYF                          ( ULIS3_W_TYPE( ULIS3_TYPE_UFLOAT   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_Yxy )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |                      ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_Yxy ) )
#define ULIS3_FORMAT_AYxyF                          ( ULIS3_W_TYPE( ULIS3_TYPE_UFLOAT   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_Yxy )   | ULIS3_W_ALPHA( 1 ) |                          ULIS3_W_SWAP( 1 ) | ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_Yxy ) )
#define ULIS3_FORMAT_yxYAF                          ( ULIS3_W_TYPE( ULIS3_TYPE_UFLOAT   ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_Yxy )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |  ULIS3_W_SWAP( 1 ) | ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 4 ) | ULIS3_W_PROFILE( ULIS3_Yxy ) )
#define ULIS3_FORMAT_YxyD                           ( ULIS3_W_TYPE( ULIS3_TYPE_UDOUBLE  ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_Yxy )   |                                                                   ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 8 ) | ULIS3_W_PROFILE( ULIS3_Yxy ) )
#define ULIS3_FORMAT_yxYD                           ( ULIS3_W_TYPE( ULIS3_TYPE_UDOUBLE  ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_Yxy )   |                       ULIS3_W_REVERSE( 1 ) |                      ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 8 ) | ULIS3_W_PROFILE( ULIS3_Yxy ) )
#define ULIS3_FORMAT_YxyAD                          ( ULIS3_W_TYPE( ULIS3_TYPE_UDOUBLE  ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_Yxy )   | ULIS3_W_ALPHA( 1 ) |                                              ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 8 ) | ULIS3_W_PROFILE( ULIS3_Yxy ) )
#define ULIS3_FORMAT_AyxYD                          ( ULIS3_W_TYPE( ULIS3_TYPE_UDOUBLE  ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_Yxy )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |                      ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 8 ) | ULIS3_W_PROFILE( ULIS3_Yxy ) )
#define ULIS3_FORMAT_AYxyD                          ( ULIS3_W_TYPE( ULIS3_TYPE_UDOUBLE  ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_Yxy )   | ULIS3_W_ALPHA( 1 ) |                          ULIS3_W_SWAP( 1 ) | ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 8 ) | ULIS3_W_PROFILE( ULIS3_Yxy ) )
#define ULIS3_FORMAT_yxYAD                          ( ULIS3_W_TYPE( ULIS3_TYPE_UDOUBLE  ) | ULIS3_W_CHANNELS( 3 ) | ULIS3_W_MODEL( ULIS3_CM_Yxy )   | ULIS3_W_ALPHA( 1 ) |  ULIS3_W_REVERSE( 1 ) |  ULIS3_W_SWAP( 1 ) | ULIS3_W_FLOATING( 1 ) | ULIS3_W_DEPTH( 8 ) | ULIS3_W_PROFILE( ULIS3_Yxy ) )
#define ULIS3_FORMAT_Linear_G8                      ( ULIS3_FORMAT_G8       | ULIS3_W_LINEAR( 1 ) & ULIS3_E_PROFILE | ULIS3_W_PROFILE( ULIS3_LinearGrey ) )
#define ULIS3_FORMAT_Linear_GA8                     ( ULIS3_FORMAT_GA8      | ULIS3_W_LINEAR( 1 ) & ULIS3_E_PROFILE | ULIS3_W_PROFILE( ULIS3_LinearGrey ) )
#define ULIS3_FORMAT_Linear_AG8                     ( ULIS3_FORMAT_AG8      | ULIS3_W_LINEAR( 1 ) & ULIS3_E_PROFILE | ULIS3_W_PROFILE( ULIS3_LinearGrey ) )
#define ULIS3_FORMAT_Linear_G16                     ( ULIS3_FORMAT_G16      | ULIS3_W_LINEAR( 1 ) & ULIS3_E_PROFILE | ULIS3_W_PROFILE( ULIS3_LinearGrey ) )
#define ULIS3_FORMAT_Linear_GA16                    ( ULIS3_FORMAT_GA16     | ULIS3_W_LINEAR( 1 ) & ULIS3_E_PROFILE | ULIS3_W_PROFILE( ULIS3_LinearGrey ) )
#define ULIS3_FORMAT_Linear_AG16                    ( ULIS3_FORMAT_AG16     | ULIS3_W_LINEAR( 1 ) & ULIS3_E_PROFILE | ULIS3_W_PROFILE( ULIS3_LinearGrey ) )
#define ULIS3_FORMAT_Linear_G32                     ( ULIS3_FORMAT_G32      | ULIS3_W_LINEAR( 1 ) & ULIS3_E_PROFILE | ULIS3_W_PROFILE( ULIS3_LinearGrey ) )
#define ULIS3_FORMAT_Linear_GA32                    ( ULIS3_FORMAT_GA32     | ULIS3_W_LINEAR( 1 ) & ULIS3_E_PROFILE | ULIS3_W_PROFILE( ULIS3_LinearGrey ) )
#define ULIS3_FORMAT_Linear_AG32                    ( ULIS3_FORMAT_AG32     | ULIS3_W_LINEAR( 1 ) & ULIS3_E_PROFILE | ULIS3_W_PROFILE( ULIS3_LinearGrey ) )
#define ULIS3_FORMAT_Linear_GF                      ( ULIS3_FORMAT_GF       | ULIS3_W_LINEAR( 1 ) & ULIS3_E_PROFILE | ULIS3_W_PROFILE( ULIS3_LinearGrey ) )
#define ULIS3_FORMAT_Linear_GAF                     ( ULIS3_FORMAT_GAF      | ULIS3_W_LINEAR( 1 ) & ULIS3_E_PROFILE | ULIS3_W_PROFILE( ULIS3_LinearGrey ) )
#define ULIS3_FORMAT_Linear_AGF                     ( ULIS3_FORMAT_AGF      | ULIS3_W_LINEAR( 1 ) & ULIS3_E_PROFILE | ULIS3_W_PROFILE( ULIS3_LinearGrey ) )
#define ULIS3_FORMAT_Linear_GD                      ( ULIS3_FORMAT_GD       | ULIS3_W_LINEAR( 1 ) & ULIS3_E_PROFILE | ULIS3_W_PROFILE( ULIS3_LinearGrey ) )
#define ULIS3_FORMAT_Linear_GAD                     ( ULIS3_FORMAT_GAD      | ULIS3_W_LINEAR( 1 ) & ULIS3_E_PROFILE | ULIS3_W_PROFILE( ULIS3_LinearGrey ) )
#define ULIS3_FORMAT_Linear_AGD                     ( ULIS3_FORMAT_AGD      | ULIS3_W_LINEAR( 1 ) & ULIS3_E_PROFILE | ULIS3_W_PROFILE( ULIS3_LinearGrey ) )
#define ULIS3_FORMAT_Linear_RGB8                    ( ULIS3_FORMAT_RGB8     | ULIS3_W_LINEAR( 1 ) & ULIS3_E_PROFILE | ULIS3_W_PROFILE( ULIS3_LinearRGB ) )
#define ULIS3_FORMAT_Linear_BGR8                    ( ULIS3_FORMAT_BGR8     | ULIS3_W_LINEAR( 1 ) & ULIS3_E_PROFILE | ULIS3_W_PROFILE( ULIS3_LinearRGB ) )
#define ULIS3_FORMAT_Linear_RGBA8                   ( ULIS3_FORMAT_RGBA8    | ULIS3_W_LINEAR( 1 ) & ULIS3_E_PROFILE | ULIS3_W_PROFILE( ULIS3_LinearRGB ) )
#define ULIS3_FORMAT_Linear_ABGR8                   ( ULIS3_FORMAT_ABGR8    | ULIS3_W_LINEAR( 1 ) & ULIS3_E_PROFILE | ULIS3_W_PROFILE( ULIS3_LinearRGB ) )
#define ULIS3_FORMAT_Linear_ARGB8                   ( ULIS3_FORMAT_ARGB8    | ULIS3_W_LINEAR( 1 ) & ULIS3_E_PROFILE | ULIS3_W_PROFILE( ULIS3_LinearRGB ) )
#define ULIS3_FORMAT_Linear_BGRA8                   ( ULIS3_FORMAT_BGRA8    | ULIS3_W_LINEAR( 1 ) & ULIS3_E_PROFILE | ULIS3_W_PROFILE( ULIS3_LinearRGB ) )
#define ULIS3_FORMAT_Linear_RGB16                   ( ULIS3_FORMAT_RGB16    | ULIS3_W_LINEAR( 1 ) & ULIS3_E_PROFILE | ULIS3_W_PROFILE( ULIS3_LinearRGB ) )
#define ULIS3_FORMAT_Linear_BGR16                   ( ULIS3_FORMAT_BGR16    | ULIS3_W_LINEAR( 1 ) & ULIS3_E_PROFILE | ULIS3_W_PROFILE( ULIS3_LinearRGB ) )
#define ULIS3_FORMAT_Linear_RGBA16                  ( ULIS3_FORMAT_RGBA16   | ULIS3_W_LINEAR( 1 ) & ULIS3_E_PROFILE | ULIS3_W_PROFILE( ULIS3_LinearRGB ) )
#define ULIS3_FORMAT_Linear_ABGR16                  ( ULIS3_FORMAT_ABGR16   | ULIS3_W_LINEAR( 1 ) & ULIS3_E_PROFILE | ULIS3_W_PROFILE( ULIS3_LinearRGB ) )
#define ULIS3_FORMAT_Linear_ARGB16                  ( ULIS3_FORMAT_ARGB16   | ULIS3_W_LINEAR( 1 ) & ULIS3_E_PROFILE | ULIS3_W_PROFILE( ULIS3_LinearRGB ) )
#define ULIS3_FORMAT_Linear_BGRA16                  ( ULIS3_FORMAT_BGRA16   | ULIS3_W_LINEAR( 1 ) & ULIS3_E_PROFILE | ULIS3_W_PROFILE( ULIS3_LinearRGB ) )
#define ULIS3_FORMAT_Linear_RGB32                   ( ULIS3_FORMAT_RGB32    | ULIS3_W_LINEAR( 1 ) & ULIS3_E_PROFILE | ULIS3_W_PROFILE( ULIS3_LinearRGB ) )
#define ULIS3_FORMAT_Linear_BGR32                   ( ULIS3_FORMAT_BGR32    | ULIS3_W_LINEAR( 1 ) & ULIS3_E_PROFILE | ULIS3_W_PROFILE( ULIS3_LinearRGB ) )
#define ULIS3_FORMAT_Linear_RGBA32                  ( ULIS3_FORMAT_RGBA32   | ULIS3_W_LINEAR( 1 ) & ULIS3_E_PROFILE | ULIS3_W_PROFILE( ULIS3_LinearRGB ) )
#define ULIS3_FORMAT_Linear_ABGR32                  ( ULIS3_FORMAT_ABGR32   | ULIS3_W_LINEAR( 1 ) & ULIS3_E_PROFILE | ULIS3_W_PROFILE( ULIS3_LinearRGB ) )
#define ULIS3_FORMAT_Linear_ARGB32                  ( ULIS3_FORMAT_ARGB32   | ULIS3_W_LINEAR( 1 ) & ULIS3_E_PROFILE | ULIS3_W_PROFILE( ULIS3_LinearRGB ) )
#define ULIS3_FORMAT_Linear_BGRA32                  ( ULIS3_FORMAT_BGRA32   | ULIS3_W_LINEAR( 1 ) & ULIS3_E_PROFILE | ULIS3_W_PROFILE( ULIS3_LinearRGB ) )
#define ULIS3_FORMAT_Linear_RGBF                    ( ULIS3_FORMAT_RGBF     | ULIS3_W_LINEAR( 1 ) & ULIS3_E_PROFILE | ULIS3_W_PROFILE( ULIS3_LinearRGB ) )
#define ULIS3_FORMAT_Linear_BGRF                    ( ULIS3_FORMAT_BGRF     | ULIS3_W_LINEAR( 1 ) & ULIS3_E_PROFILE | ULIS3_W_PROFILE( ULIS3_LinearRGB ) )
#define ULIS3_FORMAT_Linear_RGBAF                   ( ULIS3_FORMAT_RGBAF    | ULIS3_W_LINEAR( 1 ) & ULIS3_E_PROFILE | ULIS3_W_PROFILE( ULIS3_LinearRGB ) )
#define ULIS3_FORMAT_Linear_ABGRF                   ( ULIS3_FORMAT_ABGRF    | ULIS3_W_LINEAR( 1 ) & ULIS3_E_PROFILE | ULIS3_W_PROFILE( ULIS3_LinearRGB ) )
#define ULIS3_FORMAT_Linear_ARGBF                   ( ULIS3_FORMAT_ARGBF    | ULIS3_W_LINEAR( 1 ) & ULIS3_E_PROFILE | ULIS3_W_PROFILE( ULIS3_LinearRGB ) )
#define ULIS3_FORMAT_Linear_BGRAF                   ( ULIS3_FORMAT_BGRAF    | ULIS3_W_LINEAR( 1 ) & ULIS3_E_PROFILE | ULIS3_W_PROFILE( ULIS3_LinearRGB ) )
#define ULIS3_FORMAT_Linear_RGBD                    ( ULIS3_FORMAT_RGBD     | ULIS3_W_LINEAR( 1 ) & ULIS3_E_PROFILE | ULIS3_W_PROFILE( ULIS3_LinearRGB ) )
#define ULIS3_FORMAT_Linear_BGRD                    ( ULIS3_FORMAT_BGRD     | ULIS3_W_LINEAR( 1 ) & ULIS3_E_PROFILE | ULIS3_W_PROFILE( ULIS3_LinearRGB ) )
#define ULIS3_FORMAT_Linear_RGBAD                   ( ULIS3_FORMAT_RGBAD    | ULIS3_W_LINEAR( 1 ) & ULIS3_E_PROFILE | ULIS3_W_PROFILE( ULIS3_LinearRGB ) )
#define ULIS3_FORMAT_Linear_ABGRD                   ( ULIS3_FORMAT_ABGRD    | ULIS3_W_LINEAR( 1 ) & ULIS3_E_PROFILE | ULIS3_W_PROFILE( ULIS3_LinearRGB ) )
#define ULIS3_FORMAT_Linear_ARGBD                   ( ULIS3_FORMAT_ARGBD    | ULIS3_W_LINEAR( 1 ) & ULIS3_E_PROFILE | ULIS3_W_PROFILE( ULIS3_LinearRGB ) )
#define ULIS3_FORMAT_Linear_BGRAD                   ( ULIS3_FORMAT_BGRAD    | ULIS3_W_LINEAR( 1 ) & ULIS3_E_PROFILE | ULIS3_W_PROFILE( ULIS3_LinearRGB ) )
#define ULIS3_FORMAT_G8_Premultiplied               ( ULIS3_FORMAT_G8               | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_GA8_Premultiplied              ( ULIS3_FORMAT_GA8              | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_AG8_Premultiplied              ( ULIS3_FORMAT_AG8              | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_G16_Premultiplied              ( ULIS3_FORMAT_G16              | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_GA16_Premultiplied             ( ULIS3_FORMAT_GA16             | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_AG16_Premultiplied             ( ULIS3_FORMAT_AG16             | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_G32_Premultiplied              ( ULIS3_FORMAT_G32              | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_GA32_Premultiplied             ( ULIS3_FORMAT_GA32             | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_AG32_Premultiplied             ( ULIS3_FORMAT_AG32             | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_GF_Premultiplied               ( ULIS3_FORMAT_GF               | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_GAF_Premultiplied              ( ULIS3_FORMAT_GAF              | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_AGF_Premultiplied              ( ULIS3_FORMAT_AGF              | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_GD_Premultiplied               ( ULIS3_FORMAT_GD               | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_GAD_Premultiplied              ( ULIS3_FORMAT_GAD              | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_AGD_Premultiplied              ( ULIS3_FORMAT_AGD              | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_RGB8_Premultiplied             ( ULIS3_FORMAT_RGB8             | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_BGR8_Premultiplied             ( ULIS3_FORMAT_BGR8             | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_RGBA8_Premultiplied            ( ULIS3_FORMAT_RGBA8            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_ABGR8_Premultiplied            ( ULIS3_FORMAT_ABGR8            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_ARGB8_Premultiplied            ( ULIS3_FORMAT_ARGB8            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_BGRA8_Premultiplied            ( ULIS3_FORMAT_BGRA8            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_RGB16_Premultiplied            ( ULIS3_FORMAT_RGB16            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_BGR16_Premultiplied            ( ULIS3_FORMAT_BGR16            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_RGBA16_Premultiplied           ( ULIS3_FORMAT_RGBA16           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_ABGR16_Premultiplied           ( ULIS3_FORMAT_ABGR16           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_ARGB16_Premultiplied           ( ULIS3_FORMAT_ARGB16           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_BGRA16_Premultiplied           ( ULIS3_FORMAT_BGRA16           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_RGB32_Premultiplied            ( ULIS3_FORMAT_RGB32            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_BGR32_Premultiplied            ( ULIS3_FORMAT_BGR32            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_RGBA32_Premultiplied           ( ULIS3_FORMAT_RGBA32           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_ABGR32_Premultiplied           ( ULIS3_FORMAT_ABGR32           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_ARGB32_Premultiplied           ( ULIS3_FORMAT_ARGB32           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_BGRA32_Premultiplied           ( ULIS3_FORMAT_BGRA32           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_RGBF_Premultiplied             ( ULIS3_FORMAT_RGBF             | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_BGRF_Premultiplied             ( ULIS3_FORMAT_BGRF             | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_RGBAF_Premultiplied            ( ULIS3_FORMAT_RGBAF            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_ABGRF_Premultiplied            ( ULIS3_FORMAT_ABGRF            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_ARGBF_Premultiplied            ( ULIS3_FORMAT_ARGBF            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_BGRAF_Premultiplied            ( ULIS3_FORMAT_BGRAF            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_RGBD_Premultiplied             ( ULIS3_FORMAT_RGBD             | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_BGRD_Premultiplied             ( ULIS3_FORMAT_BGRD             | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_RGBAD_Premultiplied            ( ULIS3_FORMAT_RGBAD            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_ABGRD_Premultiplied            ( ULIS3_FORMAT_ABGRD            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_ARGBD_Premultiplied            ( ULIS3_FORMAT_ARGBD            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_BGRAD_Premultiplied            ( ULIS3_FORMAT_BGRAD            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_HSV8_Premultiplied             ( ULIS3_FORMAT_HSV8             | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_VSH8_Premultiplied             ( ULIS3_FORMAT_VSH8             | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_HSVA8_Premultiplied            ( ULIS3_FORMAT_HSVA8            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_AVSH8_Premultiplied            ( ULIS3_FORMAT_AVSH8            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_AHSV8_Premultiplied            ( ULIS3_FORMAT_AHSV8            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_VSHA8_Premultiplied            ( ULIS3_FORMAT_VSHA8            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_HSV16_Premultiplied            ( ULIS3_FORMAT_HSV16            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_VSH16_Premultiplied            ( ULIS3_FORMAT_VSH16            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_HSVA16_Premultiplied           ( ULIS3_FORMAT_HSVA16           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_AVSH16_Premultiplied           ( ULIS3_FORMAT_AVSH16           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_AHSV16_Premultiplied           ( ULIS3_FORMAT_AHSV16           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_VSHA16_Premultiplied           ( ULIS3_FORMAT_VSHA16           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_HSV32_Premultiplied            ( ULIS3_FORMAT_HSV32            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_VSH32_Premultiplied            ( ULIS3_FORMAT_VSH32            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_HSVA32_Premultiplied           ( ULIS3_FORMAT_HSVA32           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_AVSH32_Premultiplied           ( ULIS3_FORMAT_AVSH32           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_AHSV32_Premultiplied           ( ULIS3_FORMAT_AHSV32           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_VSHA32_Premultiplied           ( ULIS3_FORMAT_VSHA32           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_HSVF_Premultiplied             ( ULIS3_FORMAT_HSVF             | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_VSHF_Premultiplied             ( ULIS3_FORMAT_VSHF             | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_HSVAF_Premultiplied            ( ULIS3_FORMAT_HSVAF            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_AVSHF_Premultiplied            ( ULIS3_FORMAT_AVSHF            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_AHSVF_Premultiplied            ( ULIS3_FORMAT_AHSVF            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_VSHAF_Premultiplied            ( ULIS3_FORMAT_VSHAF            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_HSVD_Premultiplied             ( ULIS3_FORMAT_HSVD             | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_VSHD_Premultiplied             ( ULIS3_FORMAT_VSHD             | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_HSVAD_Premultiplied            ( ULIS3_FORMAT_HSVAD            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_AVSHD_Premultiplied            ( ULIS3_FORMAT_AVSHD            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_AHSVD_Premultiplied            ( ULIS3_FORMAT_AHSVD            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_VSHAD_Premultiplied            ( ULIS3_FORMAT_VSHAD            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_HSL8_Premultiplied             ( ULIS3_FORMAT_HSL8             | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_LSH8_Premultiplied             ( ULIS3_FORMAT_LSH8             | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_HSLA8_Premultiplied            ( ULIS3_FORMAT_HSLA8            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_ALSH8_Premultiplied            ( ULIS3_FORMAT_ALSH8            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_AHSL8_Premultiplied            ( ULIS3_FORMAT_AHSL8            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_LSHA8_Premultiplied            ( ULIS3_FORMAT_LSHA8            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_HSL16_Premultiplied            ( ULIS3_FORMAT_HSL16            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_LSH16_Premultiplied            ( ULIS3_FORMAT_LSH16            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_HSLA16_Premultiplied           ( ULIS3_FORMAT_HSLA16           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_ALSH16_Premultiplied           ( ULIS3_FORMAT_ALSH16           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_AHSL16_Premultiplied           ( ULIS3_FORMAT_AHSL16           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_LSHA16_Premultiplied           ( ULIS3_FORMAT_LSHA16           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_HSL32_Premultiplied            ( ULIS3_FORMAT_HSL32            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_LSH32_Premultiplied            ( ULIS3_FORMAT_LSH32            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_HSLA32_Premultiplied           ( ULIS3_FORMAT_HSLA32           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_ALSH32_Premultiplied           ( ULIS3_FORMAT_ALSH32           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_AHSL32_Premultiplied           ( ULIS3_FORMAT_AHSL32           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_LSHA32_Premultiplied           ( ULIS3_FORMAT_LSHA32           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_HSLF_Premultiplied             ( ULIS3_FORMAT_HSLF             | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_LSHF_Premultiplied             ( ULIS3_FORMAT_LSHF             | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_HSLAF_Premultiplied            ( ULIS3_FORMAT_HSLAF            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_ALSHF_Premultiplied            ( ULIS3_FORMAT_ALSHF            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_AHSLF_Premultiplied            ( ULIS3_FORMAT_AHSLF            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_LSHAF_Premultiplied            ( ULIS3_FORMAT_LSHAF            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_HSLD_Premultiplied             ( ULIS3_FORMAT_HSLD             | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_LSHD_Premultiplied             ( ULIS3_FORMAT_LSHD             | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_HSLAD_Premultiplied            ( ULIS3_FORMAT_HSLAD            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_ALSHD_Premultiplied            ( ULIS3_FORMAT_ALSHD            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_AHSLD_Premultiplied            ( ULIS3_FORMAT_AHSLD            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_LSHAD_Premultiplied            ( ULIS3_FORMAT_LSHAD            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_CMY8_Premultiplied             ( ULIS3_FORMAT_CMY8             | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_YMC8_Premultiplied             ( ULIS3_FORMAT_YMC8             | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_CMYA8_Premultiplied            ( ULIS3_FORMAT_CMYA8            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_AYMC8_Premultiplied            ( ULIS3_FORMAT_AYMC8            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_ACMY8_Premultiplied            ( ULIS3_FORMAT_ACMY8            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_YMCA8_Premultiplied            ( ULIS3_FORMAT_YMCA8            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_CMY16_Premultiplied            ( ULIS3_FORMAT_CMY16            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_YMC16_Premultiplied            ( ULIS3_FORMAT_YMC16            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_CMYA16_Premultiplied           ( ULIS3_FORMAT_CMYA16           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_AYMC16_Premultiplied           ( ULIS3_FORMAT_AYMC16           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_ACMY16_Premultiplied           ( ULIS3_FORMAT_ACMY16           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_YMCA16_Premultiplied           ( ULIS3_FORMAT_YMCA16           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_CMY32_Premultiplied            ( ULIS3_FORMAT_CMY32            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_YMC32_Premultiplied            ( ULIS3_FORMAT_YMC32            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_CMYA32_Premultiplied           ( ULIS3_FORMAT_CMYA32           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_AYMC32_Premultiplied           ( ULIS3_FORMAT_AYMC32           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_ACMY32_Premultiplied           ( ULIS3_FORMAT_ACMY32           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_YMCA32_Premultiplied           ( ULIS3_FORMAT_YMCA32           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_CMYF_Premultiplied             ( ULIS3_FORMAT_CMYF             | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_YMCF_Premultiplied             ( ULIS3_FORMAT_YMCF             | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_CMYAF_Premultiplied            ( ULIS3_FORMAT_CMYAF            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_AYMCF_Premultiplied            ( ULIS3_FORMAT_AYMCF            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_ACMYF_Premultiplied            ( ULIS3_FORMAT_ACMYF            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_YMCAF_Premultiplied            ( ULIS3_FORMAT_YMCAF            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_CMYD_Premultiplied             ( ULIS3_FORMAT_CMYD             | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_YMCD_Premultiplied             ( ULIS3_FORMAT_YMCD             | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_CMYAD_Premultiplied            ( ULIS3_FORMAT_CMYAD            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_AYMCD_Premultiplied            ( ULIS3_FORMAT_AYMCD            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_ACMYD_Premultiplied            ( ULIS3_FORMAT_ACMYD            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_YMCAD_Premultiplied            ( ULIS3_FORMAT_YMCAD            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_CMYK8_Premultiplied            ( ULIS3_FORMAT_CMYK8            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_KCMY8_Premultiplied            ( ULIS3_FORMAT_KCMY8            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_KYMC8_Premultiplied            ( ULIS3_FORMAT_KYMC8            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_YMCK8_Premultiplied            ( ULIS3_FORMAT_YMCK8            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_CMYKA8_Premultiplied           ( ULIS3_FORMAT_CMYKA8           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_ACMYK8_Premultiplied           ( ULIS3_FORMAT_ACMYK8           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_AKYMC8_Premultiplied           ( ULIS3_FORMAT_AKYMC8           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_KYMCA8_Premultiplied           ( ULIS3_FORMAT_KYMCA8           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_CMYK16_Premultiplied           ( ULIS3_FORMAT_CMYK16           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_KCMY16_Premultiplied           ( ULIS3_FORMAT_KCMY16           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_KYMC16_Premultiplied           ( ULIS3_FORMAT_KYMC16           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_YMCK16_Premultiplied           ( ULIS3_FORMAT_YMCK16           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_CMYKA16_Premultiplied          ( ULIS3_FORMAT_CMYKA16          | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_ACMYK16_Premultiplied          ( ULIS3_FORMAT_ACMYK16          | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_AKYMC16_Premultiplied          ( ULIS3_FORMAT_AKYMC16          | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_KYMCA16_Premultiplied          ( ULIS3_FORMAT_KYMCA16          | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_CMYK32_Premultiplied           ( ULIS3_FORMAT_CMYK32           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_KCMY32_Premultiplied           ( ULIS3_FORMAT_KCMY32           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_KYMC32_Premultiplied           ( ULIS3_FORMAT_KYMC32           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_YMCK32_Premultiplied           ( ULIS3_FORMAT_YMCK32           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_CMYKA32_Premultiplied          ( ULIS3_FORMAT_CMYKA32          | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_ACMYK32_Premultiplied          ( ULIS3_FORMAT_ACMYK32          | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_AKYMC32_Premultiplied          ( ULIS3_FORMAT_AKYMC32          | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_KYMCA32_Premultiplied          ( ULIS3_FORMAT_KYMCA32          | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_CMYKF_Premultiplied            ( ULIS3_FORMAT_CMYKF            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_KCMYF_Premultiplied            ( ULIS3_FORMAT_KCMYF            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_KYMCF_Premultiplied            ( ULIS3_FORMAT_KYMCF            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_YMCKF_Premultiplied            ( ULIS3_FORMAT_YMCKF            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_CMYKAF_Premultiplied           ( ULIS3_FORMAT_CMYKAF           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_ACMYKF_Premultiplied           ( ULIS3_FORMAT_ACMYKF           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_AKYMCF_Premultiplied           ( ULIS3_FORMAT_AKYMCF           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_KYMCAF_Premultiplied           ( ULIS3_FORMAT_KYMCAF           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_CMYKD_Premultiplied            ( ULIS3_FORMAT_CMYKD            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_KCMYD_Premultiplied            ( ULIS3_FORMAT_KCMYD            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_KYMCD_Premultiplied            ( ULIS3_FORMAT_KYMCD            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_YMCKD_Premultiplied            ( ULIS3_FORMAT_YMCKD            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_CMYKAD_Premultiplied           ( ULIS3_FORMAT_CMYKAD           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_ACMYKD_Premultiplied           ( ULIS3_FORMAT_ACMYKD           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_AKYMCD_Premultiplied           ( ULIS3_FORMAT_AKYMCD           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_KYMCAD_Premultiplied           ( ULIS3_FORMAT_KYMCAD           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_YUV8_Premultiplied             ( ULIS3_FORMAT_YUV8             | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_VUY8_Premultiplied             ( ULIS3_FORMAT_VUY8             | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_YUVA8_Premultiplied            ( ULIS3_FORMAT_YUVA8            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_AVUY8_Premultiplied            ( ULIS3_FORMAT_AVUY8            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_AYUV8_Premultiplied            ( ULIS3_FORMAT_AYUV8            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_VUYA8_Premultiplied            ( ULIS3_FORMAT_VUYA8            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_YUV16_Premultiplied            ( ULIS3_FORMAT_YUV16            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_VUY16_Premultiplied            ( ULIS3_FORMAT_VUY16            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_YUVA16_Premultiplied           ( ULIS3_FORMAT_YUVA16           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_AVUY16_Premultiplied           ( ULIS3_FORMAT_AVUY16           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_AYUV16_Premultiplied           ( ULIS3_FORMAT_AYUV16           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_VUYA16_Premultiplied           ( ULIS3_FORMAT_VUYA16           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_YUV32_Premultiplied            ( ULIS3_FORMAT_YUV32            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_VUY32_Premultiplied            ( ULIS3_FORMAT_VUY32            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_YUVA32_Premultiplied           ( ULIS3_FORMAT_YUVA32           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_AVUY32_Premultiplied           ( ULIS3_FORMAT_AVUY32           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_AYUV32_Premultiplied           ( ULIS3_FORMAT_AYUV32           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_VUYA32_Premultiplied           ( ULIS3_FORMAT_VUYA32           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_YUVF_Premultiplied             ( ULIS3_FORMAT_YUVF             | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_VUYF_Premultiplied             ( ULIS3_FORMAT_VUYF             | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_YUVAF_Premultiplied            ( ULIS3_FORMAT_YUVAF            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_AVUYF_Premultiplied            ( ULIS3_FORMAT_AVUYF            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_AYUVF_Premultiplied            ( ULIS3_FORMAT_AYUVF            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_VUYAF_Premultiplied            ( ULIS3_FORMAT_VUYAF            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_YUVD_Premultiplied             ( ULIS3_FORMAT_YUVD             | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_VUYD_Premultiplied             ( ULIS3_FORMAT_VUYD             | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_YUVAD_Premultiplied            ( ULIS3_FORMAT_YUVAD            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_AVUYD_Premultiplied            ( ULIS3_FORMAT_AVUYD            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_AYUVD_Premultiplied            ( ULIS3_FORMAT_AYUVD            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_VUYAD_Premultiplied            ( ULIS3_FORMAT_VUYAD            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_Lab8_Premultiplied             ( ULIS3_FORMAT_Lab8             | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_baL8_Premultiplied             ( ULIS3_FORMAT_baL8             | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_LabA8_Premultiplied            ( ULIS3_FORMAT_LabA8            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_AbaL8_Premultiplied            ( ULIS3_FORMAT_AbaL8            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_ALab8_Premultiplied            ( ULIS3_FORMAT_ALab8            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_baLA8_Premultiplied            ( ULIS3_FORMAT_baLA8            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_Lab16_Premultiplied            ( ULIS3_FORMAT_Lab16            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_baL16_Premultiplied            ( ULIS3_FORMAT_baL16            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_LabA16_Premultiplied           ( ULIS3_FORMAT_LabA16           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_AbaL16_Premultiplied           ( ULIS3_FORMAT_AbaL16           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_ALab16_Premultiplied           ( ULIS3_FORMAT_ALab16           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_baLA16_Premultiplied           ( ULIS3_FORMAT_baLA16           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_Lab32_Premultiplied            ( ULIS3_FORMAT_Lab32            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_baL32_Premultiplied            ( ULIS3_FORMAT_baL32            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_LabA32_Premultiplied           ( ULIS3_FORMAT_LabA32           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_AbaL32_Premultiplied           ( ULIS3_FORMAT_AbaL32           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_ALab32_Premultiplied           ( ULIS3_FORMAT_ALab32           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_baLA32_Premultiplied           ( ULIS3_FORMAT_baLA32           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_LabF_Premultiplied             ( ULIS3_FORMAT_LabF             | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_baLF_Premultiplied             ( ULIS3_FORMAT_baLF             | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_LabAF_Premultiplied            ( ULIS3_FORMAT_LabAF            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_AbaLF_Premultiplied            ( ULIS3_FORMAT_AbaLF            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_ALabF_Premultiplied            ( ULIS3_FORMAT_ALabF            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_baLAF_Premultiplied            ( ULIS3_FORMAT_baLAF            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_LabD_Premultiplied             ( ULIS3_FORMAT_LabD             | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_baLD_Premultiplied             ( ULIS3_FORMAT_baLD             | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_LabAD_Premultiplied            ( ULIS3_FORMAT_LabAD            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_AbaLD_Premultiplied            ( ULIS3_FORMAT_AbaLD            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_ALabD_Premultiplied            ( ULIS3_FORMAT_ALabD            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_baLAD_Premultiplied            ( ULIS3_FORMAT_baLAD            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_XYZ8_Premultiplied             ( ULIS3_FORMAT_XYZ8             | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_ZYX8_Premultiplied             ( ULIS3_FORMAT_ZYX8             | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_XYZA8_Premultiplied            ( ULIS3_FORMAT_XYZA8            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_AZYX8_Premultiplied            ( ULIS3_FORMAT_AZYX8            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_AXYZ8_Premultiplied            ( ULIS3_FORMAT_AXYZ8            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_ZYXA8_Premultiplied            ( ULIS3_FORMAT_ZYXA8            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_XYZ16_Premultiplied            ( ULIS3_FORMAT_XYZ16            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_ZYX16_Premultiplied            ( ULIS3_FORMAT_ZYX16            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_XYZA16_Premultiplied           ( ULIS3_FORMAT_XYZA16           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_AZYX16_Premultiplied           ( ULIS3_FORMAT_AZYX16           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_AXYZ16_Premultiplied           ( ULIS3_FORMAT_AXYZ16           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_ZYXA16_Premultiplied           ( ULIS3_FORMAT_ZYXA16           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_XYZ32_Premultiplied            ( ULIS3_FORMAT_XYZ32            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_ZYX32_Premultiplied            ( ULIS3_FORMAT_ZYX32            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_XYZA32_Premultiplied           ( ULIS3_FORMAT_XYZA32           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_AZYX32_Premultiplied           ( ULIS3_FORMAT_AZYX32           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_AXYZ32_Premultiplied           ( ULIS3_FORMAT_AXYZ32           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_ZYXA32_Premultiplied           ( ULIS3_FORMAT_ZYXA32           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_XYZF_Premultiplied             ( ULIS3_FORMAT_XYZF             | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_ZYXF_Premultiplied             ( ULIS3_FORMAT_ZYXF             | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_XYZAF_Premultiplied            ( ULIS3_FORMAT_XYZAF            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_AZYXF_Premultiplied            ( ULIS3_FORMAT_AZYXF            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_AXYZF_Premultiplied            ( ULIS3_FORMAT_AXYZF            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_ZYXAF_Premultiplied            ( ULIS3_FORMAT_ZYXAF            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_XYZD_Premultiplied             ( ULIS3_FORMAT_XYZD             | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_ZYXD_Premultiplied             ( ULIS3_FORMAT_ZYXD             | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_XYZAD_Premultiplied            ( ULIS3_FORMAT_XYZAD            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_AZYXD_Premultiplied            ( ULIS3_FORMAT_AZYXD            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_AXYZD_Premultiplied            ( ULIS3_FORMAT_AXYZD            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_ZYXAD_Premultiplied            ( ULIS3_FORMAT_ZYXAD            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_Yxy8_Premultiplied             ( ULIS3_FORMAT_Yxy8             | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_yxY8_Premultiplied             ( ULIS3_FORMAT_yxY8             | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_YxyA8_Premultiplied            ( ULIS3_FORMAT_YxyA8            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_AyxY8_Premultiplied            ( ULIS3_FORMAT_AyxY8            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_AYxy8_Premultiplied            ( ULIS3_FORMAT_AYxy8            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_yxYA8_Premultiplied            ( ULIS3_FORMAT_yxYA8            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_Yxy16_Premultiplied            ( ULIS3_FORMAT_Yxy16            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_yxY16_Premultiplied            ( ULIS3_FORMAT_yxY16            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_YxyA16_Premultiplied           ( ULIS3_FORMAT_YxyA16           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_AyxY16_Premultiplied           ( ULIS3_FORMAT_AyxY16           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_AYxy16_Premultiplied           ( ULIS3_FORMAT_AYxy16           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_yxYA16_Premultiplied           ( ULIS3_FORMAT_yxYA16           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_Yxy32_Premultiplied            ( ULIS3_FORMAT_Yxy32            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_yxY32_Premultiplied            ( ULIS3_FORMAT_yxY32            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_YxyA32_Premultiplied           ( ULIS3_FORMAT_YxyA32           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_AyxY32_Premultiplied           ( ULIS3_FORMAT_AyxY32           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_AYxy32_Premultiplied           ( ULIS3_FORMAT_AYxy32           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_yxYA32_Premultiplied           ( ULIS3_FORMAT_yxYA32           | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_YxyF_Premultiplied             ( ULIS3_FORMAT_YxyF             | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_yxYF_Premultiplied             ( ULIS3_FORMAT_yxYF             | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_YxyAF_Premultiplied            ( ULIS3_FORMAT_YxyAF            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_AyxYF_Premultiplied            ( ULIS3_FORMAT_AyxYF            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_AYxyF_Premultiplied            ( ULIS3_FORMAT_AYxyF            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_yxYAF_Premultiplied            ( ULIS3_FORMAT_yxYAF            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_YxyD_Premultiplied             ( ULIS3_FORMAT_YxyD             | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_yxYD_Premultiplied             ( ULIS3_FORMAT_yxYD             | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_YxyAD_Premultiplied            ( ULIS3_FORMAT_YxyAD            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_AyxYD_Premultiplied            ( ULIS3_FORMAT_AyxYD            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_AYxyD_Premultiplied            ( ULIS3_FORMAT_AYxyD            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_yxYAD_Premultiplied            ( ULIS3_FORMAT_yxYAD            | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_Linear_G8_Premultiplied        ( ULIS3_FORMAT_Linear_G8        | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_Linear_GA8_Premultiplied       ( ULIS3_FORMAT_Linear_GA8       | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_Linear_AG8_Premultiplied       ( ULIS3_FORMAT_Linear_AG8       | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_Linear_G16_Premultiplied       ( ULIS3_FORMAT_Linear_G16       | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_Linear_GA16_Premultiplied      ( ULIS3_FORMAT_Linear_GA16      | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_Linear_AG16_Premultiplied      ( ULIS3_FORMAT_Linear_AG16      | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_Linear_G32_Premultiplied       ( ULIS3_FORMAT_Linear_G32       | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_Linear_GA32_Premultiplied      ( ULIS3_FORMAT_Linear_GA32      | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_Linear_AG32_Premultiplied      ( ULIS3_FORMAT_Linear_AG32      | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_Linear_GF_Premultiplied        ( ULIS3_FORMAT_Linear_GF        | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_Linear_GAF_Premultiplied       ( ULIS3_FORMAT_Linear_GAF       | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_Linear_AGF_Premultiplied       ( ULIS3_FORMAT_Linear_AGF       | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_Linear_GD_Premultiplied        ( ULIS3_FORMAT_Linear_GD        | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_Linear_GAD_Premultiplied       ( ULIS3_FORMAT_Linear_GAD       | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_Linear_AGD_Premultiplied       ( ULIS3_FORMAT_Linear_AGD       | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_Linear_RGB8_Premultiplied      ( ULIS3_FORMAT_Linear_RGB8      | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_Linear_BGR8_Premultiplied      ( ULIS3_FORMAT_Linear_BGR8      | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_Linear_RGBA8_Premultiplied     ( ULIS3_FORMAT_Linear_RGBA8     | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_Linear_ABGR8_Premultiplied     ( ULIS3_FORMAT_Linear_ABGR8     | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_Linear_ARGB8_Premultiplied     ( ULIS3_FORMAT_Linear_ARGB8     | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_Linear_BGRA8_Premultiplied     ( ULIS3_FORMAT_Linear_BGRA8     | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_Linear_RGB16_Premultiplied     ( ULIS3_FORMAT_Linear_RGB16     | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_Linear_BGR16_Premultiplied     ( ULIS3_FORMAT_Linear_BGR16     | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_Linear_RGBA16_Premultiplied    ( ULIS3_FORMAT_Linear_RGBA16    | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_Linear_ABGR16_Premultiplied    ( ULIS3_FORMAT_Linear_ABGR16    | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_Linear_ARGB16_Premultiplied    ( ULIS3_FORMAT_Linear_ARGB16    | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_Linear_BGRA16_Premultiplied    ( ULIS3_FORMAT_Linear_BGRA16    | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_Linear_RGB32_Premultiplied     ( ULIS3_FORMAT_Linear_RGB32     | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_Linear_BGR32_Premultiplied     ( ULIS3_FORMAT_Linear_BGR32     | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_Linear_RGBA32_Premultiplied    ( ULIS3_FORMAT_Linear_RGBA32    | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_Linear_ABGR32_Premultiplied    ( ULIS3_FORMAT_Linear_ABGR32    | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_Linear_ARGB32_Premultiplied    ( ULIS3_FORMAT_Linear_ARGB32    | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_Linear_BGRA32_Premultiplied    ( ULIS3_FORMAT_Linear_BGRA32    | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_Linear_RGBF_Premultiplied      ( ULIS3_FORMAT_Linear_RGBF      | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_Linear_BGRF_Premultiplied      ( ULIS3_FORMAT_Linear_BGRF      | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_Linear_RGBAF_Premultiplied     ( ULIS3_FORMAT_Linear_RGBAF     | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_Linear_ABGRF_Premultiplied     ( ULIS3_FORMAT_Linear_ABGRF     | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_Linear_ARGBF_Premultiplied     ( ULIS3_FORMAT_Linear_ARGBF     | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_Linear_BGRAF_Premultiplied     ( ULIS3_FORMAT_Linear_BGRAF     | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_Linear_RGBD_Premultiplied      ( ULIS3_FORMAT_Linear_RGBD      | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_Linear_BGRD_Premultiplied      ( ULIS3_FORMAT_Linear_BGRD      | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_Linear_RGBAD_Premultiplied     ( ULIS3_FORMAT_Linear_RGBAD     | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_Linear_ABGRD_Premultiplied     ( ULIS3_FORMAT_Linear_ABGRD     | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_Linear_ARGBD_Premultiplied     ( ULIS3_FORMAT_Linear_ARGBD     | ULIS3_W_PREMULT( 1 ) )
#define ULIS3_FORMAT_Linear_BGRAD_Premultiplied     ( ULIS3_FORMAT_Linear_BGRAD     | ULIS3_W_PREMULT( 1 ) )


ULIS3_NAMESPACE_BEGIN
static constexpr tFormat FMT_G8                             = ULIS3_FORMAT_G8;
static constexpr tFormat FMT_GA8                            = ULIS3_FORMAT_GA8;
static constexpr tFormat FMT_AG8                            = ULIS3_FORMAT_AG8;
static constexpr tFormat FMT_G16                            = ULIS3_FORMAT_G16;
static constexpr tFormat FMT_GA16                           = ULIS3_FORMAT_GA16;
static constexpr tFormat FMT_AG16                           = ULIS3_FORMAT_AG16;
static constexpr tFormat FMT_G32                            = ULIS3_FORMAT_G32;
static constexpr tFormat FMT_GA32                           = ULIS3_FORMAT_GA32;
static constexpr tFormat FMT_AG32                           = ULIS3_FORMAT_AG32;
static constexpr tFormat FMT_GF                             = ULIS3_FORMAT_GF;
static constexpr tFormat FMT_GAF                            = ULIS3_FORMAT_GAF;
static constexpr tFormat FMT_AGF                            = ULIS3_FORMAT_AGF;
static constexpr tFormat FMT_GD                             = ULIS3_FORMAT_GD;
static constexpr tFormat FMT_GAD                            = ULIS3_FORMAT_GAD;
static constexpr tFormat FMT_AGD                            = ULIS3_FORMAT_AGD;
static constexpr tFormat FMT_RGB8                           = ULIS3_FORMAT_RGB8;
static constexpr tFormat FMT_BGR8                           = ULIS3_FORMAT_BGR8;
static constexpr tFormat FMT_RGBA8                          = ULIS3_FORMAT_RGBA8;
static constexpr tFormat FMT_ABGR8                          = ULIS3_FORMAT_ABGR8;
static constexpr tFormat FMT_ARGB8                          = ULIS3_FORMAT_ARGB8;
static constexpr tFormat FMT_BGRA8                          = ULIS3_FORMAT_BGRA8;
static constexpr tFormat FMT_RGB16                          = ULIS3_FORMAT_RGB16;
static constexpr tFormat FMT_BGR16                          = ULIS3_FORMAT_BGR16;
static constexpr tFormat FMT_RGBA16                         = ULIS3_FORMAT_RGBA16;
static constexpr tFormat FMT_ABGR16                         = ULIS3_FORMAT_ABGR16;
static constexpr tFormat FMT_ARGB16                         = ULIS3_FORMAT_ARGB16;
static constexpr tFormat FMT_BGRA16                         = ULIS3_FORMAT_BGRA16;
static constexpr tFormat FMT_RGB32                          = ULIS3_FORMAT_RGB32;
static constexpr tFormat FMT_BGR32                          = ULIS3_FORMAT_BGR32;
static constexpr tFormat FMT_RGBA32                         = ULIS3_FORMAT_RGBA32;
static constexpr tFormat FMT_ABGR32                         = ULIS3_FORMAT_ABGR32;
static constexpr tFormat FMT_ARGB32                         = ULIS3_FORMAT_ARGB32;
static constexpr tFormat FMT_BGRA32                         = ULIS3_FORMAT_BGRA32;
static constexpr tFormat FMT_RGBF                           = ULIS3_FORMAT_RGBF;
static constexpr tFormat FMT_BGRF                           = ULIS3_FORMAT_BGRF;
static constexpr tFormat FMT_RGBAF                          = ULIS3_FORMAT_RGBAF;
static constexpr tFormat FMT_ABGRF                          = ULIS3_FORMAT_ABGRF;
static constexpr tFormat FMT_ARGBF                          = ULIS3_FORMAT_ARGBF;
static constexpr tFormat FMT_BGRAF                          = ULIS3_FORMAT_BGRAF;
static constexpr tFormat FMT_RGBD                           = ULIS3_FORMAT_RGBD;
static constexpr tFormat FMT_BGRD                           = ULIS3_FORMAT_BGRD;
static constexpr tFormat FMT_RGBAD                          = ULIS3_FORMAT_RGBAD;
static constexpr tFormat FMT_ABGRD                          = ULIS3_FORMAT_ABGRD;
static constexpr tFormat FMT_ARGBD                          = ULIS3_FORMAT_ARGBD;
static constexpr tFormat FMT_BGRAD                          = ULIS3_FORMAT_BGRAD;
static constexpr tFormat FMT_HSV8                           = ULIS3_FORMAT_HSV8;
static constexpr tFormat FMT_VSH8                           = ULIS3_FORMAT_VSH8;
static constexpr tFormat FMT_HSVA8                          = ULIS3_FORMAT_HSVA8;
static constexpr tFormat FMT_AVSH8                          = ULIS3_FORMAT_AVSH8;
static constexpr tFormat FMT_AHSV8                          = ULIS3_FORMAT_AHSV8;
static constexpr tFormat FMT_VSHA8                          = ULIS3_FORMAT_VSHA8;
static constexpr tFormat FMT_HSV16                          = ULIS3_FORMAT_HSV16;
static constexpr tFormat FMT_VSH16                          = ULIS3_FORMAT_VSH16;
static constexpr tFormat FMT_HSVA16                         = ULIS3_FORMAT_HSVA16;
static constexpr tFormat FMT_AVSH16                         = ULIS3_FORMAT_AVSH16;
static constexpr tFormat FMT_AHSV16                         = ULIS3_FORMAT_AHSV16;
static constexpr tFormat FMT_VSHA16                         = ULIS3_FORMAT_VSHA16;
static constexpr tFormat FMT_HSV32                          = ULIS3_FORMAT_HSV32;
static constexpr tFormat FMT_VSH32                          = ULIS3_FORMAT_VSH32;
static constexpr tFormat FMT_HSVA32                         = ULIS3_FORMAT_HSVA32;
static constexpr tFormat FMT_AVSH32                         = ULIS3_FORMAT_AVSH32;
static constexpr tFormat FMT_AHSV32                         = ULIS3_FORMAT_AHSV32;
static constexpr tFormat FMT_VSHA32                         = ULIS3_FORMAT_VSHA32;
static constexpr tFormat FMT_HSVF                           = ULIS3_FORMAT_HSVF;
static constexpr tFormat FMT_VSHF                           = ULIS3_FORMAT_VSHF;
static constexpr tFormat FMT_HSVAF                          = ULIS3_FORMAT_HSVAF;
static constexpr tFormat FMT_AVSHF                          = ULIS3_FORMAT_AVSHF;
static constexpr tFormat FMT_AHSVF                          = ULIS3_FORMAT_AHSVF;
static constexpr tFormat FMT_VSHAF                          = ULIS3_FORMAT_VSHAF;
static constexpr tFormat FMT_HSVD                           = ULIS3_FORMAT_HSVD;
static constexpr tFormat FMT_VSHD                           = ULIS3_FORMAT_VSHD;
static constexpr tFormat FMT_HSVAD                          = ULIS3_FORMAT_HSVAD;
static constexpr tFormat FMT_AVSHD                          = ULIS3_FORMAT_AVSHD;
static constexpr tFormat FMT_AHSVD                          = ULIS3_FORMAT_AHSVD;
static constexpr tFormat FMT_VSHAD                          = ULIS3_FORMAT_VSHAD;
static constexpr tFormat FMT_HSL8                           = ULIS3_FORMAT_HSL8;
static constexpr tFormat FMT_LSH8                           = ULIS3_FORMAT_LSH8;
static constexpr tFormat FMT_HSLA8                          = ULIS3_FORMAT_HSLA8;
static constexpr tFormat FMT_ALSH8                          = ULIS3_FORMAT_ALSH8;
static constexpr tFormat FMT_AHSL8                          = ULIS3_FORMAT_AHSL8;
static constexpr tFormat FMT_LSHA8                          = ULIS3_FORMAT_LSHA8;
static constexpr tFormat FMT_HSL16                          = ULIS3_FORMAT_HSL16;
static constexpr tFormat FMT_LSH16                          = ULIS3_FORMAT_LSH16;
static constexpr tFormat FMT_HSLA16                         = ULIS3_FORMAT_HSLA16;
static constexpr tFormat FMT_ALSH16                         = ULIS3_FORMAT_ALSH16;
static constexpr tFormat FMT_AHSL16                         = ULIS3_FORMAT_AHSL16;
static constexpr tFormat FMT_LSHA16                         = ULIS3_FORMAT_LSHA16;
static constexpr tFormat FMT_HSL32                          = ULIS3_FORMAT_HSL32;
static constexpr tFormat FMT_LSH32                          = ULIS3_FORMAT_LSH32;
static constexpr tFormat FMT_HSLA32                         = ULIS3_FORMAT_HSLA32;
static constexpr tFormat FMT_ALSH32                         = ULIS3_FORMAT_ALSH32;
static constexpr tFormat FMT_AHSL32                         = ULIS3_FORMAT_AHSL32;
static constexpr tFormat FMT_LSHA32                         = ULIS3_FORMAT_LSHA32;
static constexpr tFormat FMT_HSLF                           = ULIS3_FORMAT_HSLF;
static constexpr tFormat FMT_LSHF                           = ULIS3_FORMAT_LSHF;
static constexpr tFormat FMT_HSLAF                          = ULIS3_FORMAT_HSLAF;
static constexpr tFormat FMT_ALSHF                          = ULIS3_FORMAT_ALSHF;
static constexpr tFormat FMT_AHSLF                          = ULIS3_FORMAT_AHSLF;
static constexpr tFormat FMT_LSHAF                          = ULIS3_FORMAT_LSHAF;
static constexpr tFormat FMT_HSLD                           = ULIS3_FORMAT_HSLD;
static constexpr tFormat FMT_LSHD                           = ULIS3_FORMAT_LSHD;
static constexpr tFormat FMT_HSLAD                          = ULIS3_FORMAT_HSLAD;
static constexpr tFormat FMT_ALSHD                          = ULIS3_FORMAT_ALSHD;
static constexpr tFormat FMT_AHSLD                          = ULIS3_FORMAT_AHSLD;
static constexpr tFormat FMT_LSHAD                          = ULIS3_FORMAT_LSHAD;
static constexpr tFormat FMT_CMY8                           = ULIS3_FORMAT_CMY8;
static constexpr tFormat FMT_YMC8                           = ULIS3_FORMAT_YMC8;
static constexpr tFormat FMT_CMYA8                          = ULIS3_FORMAT_CMYA8;
static constexpr tFormat FMT_AYMC8                          = ULIS3_FORMAT_AYMC8;
static constexpr tFormat FMT_ACMY8                          = ULIS3_FORMAT_ACMY8;
static constexpr tFormat FMT_YMCA8                          = ULIS3_FORMAT_YMCA8;
static constexpr tFormat FMT_CMY16                          = ULIS3_FORMAT_CMY16;
static constexpr tFormat FMT_YMC16                          = ULIS3_FORMAT_YMC16;
static constexpr tFormat FMT_CMYA16                         = ULIS3_FORMAT_CMYA16;
static constexpr tFormat FMT_AYMC16                         = ULIS3_FORMAT_AYMC16;
static constexpr tFormat FMT_ACMY16                         = ULIS3_FORMAT_ACMY16;
static constexpr tFormat FMT_YMCA16                         = ULIS3_FORMAT_YMCA16;
static constexpr tFormat FMT_CMY32                          = ULIS3_FORMAT_CMY32;
static constexpr tFormat FMT_YMC32                          = ULIS3_FORMAT_YMC32;
static constexpr tFormat FMT_CMYA32                         = ULIS3_FORMAT_CMYA32;
static constexpr tFormat FMT_AYMC32                         = ULIS3_FORMAT_AYMC32;
static constexpr tFormat FMT_ACMY32                         = ULIS3_FORMAT_ACMY32;
static constexpr tFormat FMT_YMCA32                         = ULIS3_FORMAT_YMCA32;
static constexpr tFormat FMT_CMYF                           = ULIS3_FORMAT_CMYF;
static constexpr tFormat FMT_YMCF                           = ULIS3_FORMAT_YMCF;
static constexpr tFormat FMT_CMYAF                          = ULIS3_FORMAT_CMYAF;
static constexpr tFormat FMT_AYMCF                          = ULIS3_FORMAT_AYMCF;
static constexpr tFormat FMT_ACMYF                          = ULIS3_FORMAT_ACMYF;
static constexpr tFormat FMT_YMCAF                          = ULIS3_FORMAT_YMCAF;
static constexpr tFormat FMT_CMYD                           = ULIS3_FORMAT_CMYD;
static constexpr tFormat FMT_YMCD                           = ULIS3_FORMAT_YMCD;
static constexpr tFormat FMT_CMYAD                          = ULIS3_FORMAT_CMYAD;
static constexpr tFormat FMT_AYMCD                          = ULIS3_FORMAT_AYMCD;
static constexpr tFormat FMT_ACMYD                          = ULIS3_FORMAT_ACMYD;
static constexpr tFormat FMT_YMCAD                          = ULIS3_FORMAT_YMCAD;
static constexpr tFormat FMT_CMYK8                          = ULIS3_FORMAT_CMYK8;
static constexpr tFormat FMT_KCMY8                          = ULIS3_FORMAT_KCMY8;
static constexpr tFormat FMT_KYMC8                          = ULIS3_FORMAT_KYMC8;
static constexpr tFormat FMT_YMCK8                          = ULIS3_FORMAT_YMCK8;
static constexpr tFormat FMT_CMYKA8                         = ULIS3_FORMAT_CMYKA8;
static constexpr tFormat FMT_ACMYK8                         = ULIS3_FORMAT_ACMYK8;
static constexpr tFormat FMT_AKYMC8                         = ULIS3_FORMAT_AKYMC8;
static constexpr tFormat FMT_KYMCA8                         = ULIS3_FORMAT_KYMCA8;
static constexpr tFormat FMT_CMYK16                         = ULIS3_FORMAT_CMYK16;
static constexpr tFormat FMT_KCMY16                         = ULIS3_FORMAT_KCMY16;
static constexpr tFormat FMT_KYMC16                         = ULIS3_FORMAT_KYMC16;
static constexpr tFormat FMT_YMCK16                         = ULIS3_FORMAT_YMCK16;
static constexpr tFormat FMT_CMYKA16                        = ULIS3_FORMAT_CMYKA16;
static constexpr tFormat FMT_ACMYK16                        = ULIS3_FORMAT_ACMYK16;
static constexpr tFormat FMT_AKYMC16                        = ULIS3_FORMAT_AKYMC16;
static constexpr tFormat FMT_KYMCA16                        = ULIS3_FORMAT_KYMCA16;
static constexpr tFormat FMT_CMYK32                         = ULIS3_FORMAT_CMYK32;
static constexpr tFormat FMT_KCMY32                         = ULIS3_FORMAT_KCMY32;
static constexpr tFormat FMT_KYMC32                         = ULIS3_FORMAT_KYMC32;
static constexpr tFormat FMT_YMCK32                         = ULIS3_FORMAT_YMCK32;
static constexpr tFormat FMT_CMYKA32                        = ULIS3_FORMAT_CMYKA32;
static constexpr tFormat FMT_ACMYK32                        = ULIS3_FORMAT_ACMYK32;
static constexpr tFormat FMT_AKYMC32                        = ULIS3_FORMAT_AKYMC32;
static constexpr tFormat FMT_KYMCA32                        = ULIS3_FORMAT_KYMCA32;
static constexpr tFormat FMT_CMYKF                          = ULIS3_FORMAT_CMYKF;
static constexpr tFormat FMT_KCMYF                          = ULIS3_FORMAT_KCMYF;
static constexpr tFormat FMT_KYMCF                          = ULIS3_FORMAT_KYMCF;
static constexpr tFormat FMT_YMCKF                          = ULIS3_FORMAT_YMCKF;
static constexpr tFormat FMT_CMYKAF                         = ULIS3_FORMAT_CMYKAF;
static constexpr tFormat FMT_ACMYKF                         = ULIS3_FORMAT_ACMYKF;
static constexpr tFormat FMT_AKYMCF                         = ULIS3_FORMAT_AKYMCF;
static constexpr tFormat FMT_KYMCAF                         = ULIS3_FORMAT_KYMCAF;
static constexpr tFormat FMT_CMYKD                          = ULIS3_FORMAT_CMYKD;
static constexpr tFormat FMT_KCMYD                          = ULIS3_FORMAT_KCMYD;
static constexpr tFormat FMT_KYMCD                          = ULIS3_FORMAT_KYMCD;
static constexpr tFormat FMT_YMCKD                          = ULIS3_FORMAT_YMCKD;
static constexpr tFormat FMT_CMYKAD                         = ULIS3_FORMAT_CMYKAD;
static constexpr tFormat FMT_ACMYKD                         = ULIS3_FORMAT_ACMYKD;
static constexpr tFormat FMT_AKYMCD                         = ULIS3_FORMAT_AKYMCD;
static constexpr tFormat FMT_KYMCAD                         = ULIS3_FORMAT_KYMCAD;
static constexpr tFormat FMT_YUV8                           = ULIS3_FORMAT_YUV8;
static constexpr tFormat FMT_VUY8                           = ULIS3_FORMAT_VUY8;
static constexpr tFormat FMT_YUVA8                          = ULIS3_FORMAT_YUVA8;
static constexpr tFormat FMT_AVUY8                          = ULIS3_FORMAT_AVUY8;
static constexpr tFormat FMT_AYUV8                          = ULIS3_FORMAT_AYUV8;
static constexpr tFormat FMT_VUYA8                          = ULIS3_FORMAT_VUYA8;
static constexpr tFormat FMT_YUV16                          = ULIS3_FORMAT_YUV16;
static constexpr tFormat FMT_VUY16                          = ULIS3_FORMAT_VUY16;
static constexpr tFormat FMT_YUVA16                         = ULIS3_FORMAT_YUVA16;
static constexpr tFormat FMT_AVUY16                         = ULIS3_FORMAT_AVUY16;
static constexpr tFormat FMT_AYUV16                         = ULIS3_FORMAT_AYUV16;
static constexpr tFormat FMT_VUYA16                         = ULIS3_FORMAT_VUYA16;
static constexpr tFormat FMT_YUV32                          = ULIS3_FORMAT_YUV32;
static constexpr tFormat FMT_VUY32                          = ULIS3_FORMAT_VUY32;
static constexpr tFormat FMT_YUVA32                         = ULIS3_FORMAT_YUVA32;
static constexpr tFormat FMT_AVUY32                         = ULIS3_FORMAT_AVUY32;
static constexpr tFormat FMT_AYUV32                         = ULIS3_FORMAT_AYUV32;
static constexpr tFormat FMT_VUYA32                         = ULIS3_FORMAT_VUYA32;
static constexpr tFormat FMT_YUVF                           = ULIS3_FORMAT_YUVF;
static constexpr tFormat FMT_VUYF                           = ULIS3_FORMAT_VUYF;
static constexpr tFormat FMT_YUVAF                          = ULIS3_FORMAT_YUVAF;
static constexpr tFormat FMT_AVUYF                          = ULIS3_FORMAT_AVUYF;
static constexpr tFormat FMT_AYUVF                          = ULIS3_FORMAT_AYUVF;
static constexpr tFormat FMT_VUYAF                          = ULIS3_FORMAT_VUYAF;
static constexpr tFormat FMT_YUVD                           = ULIS3_FORMAT_YUVD;
static constexpr tFormat FMT_VUYD                           = ULIS3_FORMAT_VUYD;
static constexpr tFormat FMT_YUVAD                          = ULIS3_FORMAT_YUVAD;
static constexpr tFormat FMT_AVUYD                          = ULIS3_FORMAT_AVUYD;
static constexpr tFormat FMT_AYUVD                          = ULIS3_FORMAT_AYUVD;
static constexpr tFormat FMT_VUYAD                          = ULIS3_FORMAT_VUYAD;
static constexpr tFormat FMT_Lab8                           = ULIS3_FORMAT_Lab8;
static constexpr tFormat FMT_baL8                           = ULIS3_FORMAT_baL8;
static constexpr tFormat FMT_LabA8                          = ULIS3_FORMAT_LabA8;
static constexpr tFormat FMT_AbaL8                          = ULIS3_FORMAT_AbaL8;
static constexpr tFormat FMT_ALab8                          = ULIS3_FORMAT_ALab8;
static constexpr tFormat FMT_baLA8                          = ULIS3_FORMAT_baLA8;
static constexpr tFormat FMT_Lab16                          = ULIS3_FORMAT_Lab16;
static constexpr tFormat FMT_baL16                          = ULIS3_FORMAT_baL16;
static constexpr tFormat FMT_LabA16                         = ULIS3_FORMAT_LabA16;
static constexpr tFormat FMT_AbaL16                         = ULIS3_FORMAT_AbaL16;
static constexpr tFormat FMT_ALab16                         = ULIS3_FORMAT_ALab16;
static constexpr tFormat FMT_baLA16                         = ULIS3_FORMAT_baLA16;
static constexpr tFormat FMT_Lab32                          = ULIS3_FORMAT_Lab32;
static constexpr tFormat FMT_baL32                          = ULIS3_FORMAT_baL32;
static constexpr tFormat FMT_LabA32                         = ULIS3_FORMAT_LabA32;
static constexpr tFormat FMT_AbaL32                         = ULIS3_FORMAT_AbaL32;
static constexpr tFormat FMT_ALab32                         = ULIS3_FORMAT_ALab32;
static constexpr tFormat FMT_baLA32                         = ULIS3_FORMAT_baLA32;
static constexpr tFormat FMT_LabF                           = ULIS3_FORMAT_LabF;
static constexpr tFormat FMT_baLF                           = ULIS3_FORMAT_baLF;
static constexpr tFormat FMT_LabAF                          = ULIS3_FORMAT_LabAF;
static constexpr tFormat FMT_AbaLF                          = ULIS3_FORMAT_AbaLF;
static constexpr tFormat FMT_ALabF                          = ULIS3_FORMAT_ALabF;
static constexpr tFormat FMT_baLAF                          = ULIS3_FORMAT_baLAF;
static constexpr tFormat FMT_LabD                           = ULIS3_FORMAT_LabD;
static constexpr tFormat FMT_baLD                           = ULIS3_FORMAT_baLD;
static constexpr tFormat FMT_LabAD                          = ULIS3_FORMAT_LabAD;
static constexpr tFormat FMT_AbaLD                          = ULIS3_FORMAT_AbaLD;;
static constexpr tFormat FMT_ALabD                          = ULIS3_FORMAT_ALabD;
static constexpr tFormat FMT_baLAD                          = ULIS3_FORMAT_baLAD;
static constexpr tFormat FMT_XYZ8                           = ULIS3_FORMAT_XYZ8;
static constexpr tFormat FMT_ZYX8                           = ULIS3_FORMAT_ZYX8;
static constexpr tFormat FMT_XYZA8                          = ULIS3_FORMAT_XYZA8;
static constexpr tFormat FMT_AZYX8                          = ULIS3_FORMAT_AZYX8;
static constexpr tFormat FMT_AXYZ8                          = ULIS3_FORMAT_AXYZ8;
static constexpr tFormat FMT_ZYXA8                          = ULIS3_FORMAT_ZYXA8;
static constexpr tFormat FMT_XYZ16                          = ULIS3_FORMAT_XYZ16;
static constexpr tFormat FMT_ZYX16                          = ULIS3_FORMAT_ZYX16;
static constexpr tFormat FMT_XYZA16                         = ULIS3_FORMAT_XYZA16;
static constexpr tFormat FMT_AZYX16                         = ULIS3_FORMAT_AZYX16;
static constexpr tFormat FMT_AXYZ16                         = ULIS3_FORMAT_AXYZ16;
static constexpr tFormat FMT_ZYXA16                         = ULIS3_FORMAT_ZYXA16;
static constexpr tFormat FMT_XYZ32                          = ULIS3_FORMAT_XYZ32;
static constexpr tFormat FMT_ZYX32                          = ULIS3_FORMAT_ZYX32;
static constexpr tFormat FMT_XYZA32                         = ULIS3_FORMAT_XYZA32;
static constexpr tFormat FMT_AZYX32                         = ULIS3_FORMAT_AZYX32;
static constexpr tFormat FMT_AXYZ32                         = ULIS3_FORMAT_AXYZ32;
static constexpr tFormat FMT_ZYXA32                         = ULIS3_FORMAT_ZYXA32;
static constexpr tFormat FMT_XYZF                           = ULIS3_FORMAT_XYZF;
static constexpr tFormat FMT_ZYXF                           = ULIS3_FORMAT_ZYXF;
static constexpr tFormat FMT_XYZAF                          = ULIS3_FORMAT_XYZAF;
static constexpr tFormat FMT_AZYXF                          = ULIS3_FORMAT_AZYXF;
static constexpr tFormat FMT_AXYZF                          = ULIS3_FORMAT_AXYZF;
static constexpr tFormat FMT_ZYXAF                          = ULIS3_FORMAT_ZYXAF;
static constexpr tFormat FMT_XYZD                           = ULIS3_FORMAT_XYZD;
static constexpr tFormat FMT_ZYXD                           = ULIS3_FORMAT_ZYXD;
static constexpr tFormat FMT_XYZAD                          = ULIS3_FORMAT_XYZAD;
static constexpr tFormat FMT_AZYXD                          = ULIS3_FORMAT_AZYXD;
static constexpr tFormat FMT_AXYZD                          = ULIS3_FORMAT_AXYZD;
static constexpr tFormat FMT_ZYXAD                          = ULIS3_FORMAT_ZYXAD;
static constexpr tFormat FMT_Yxy8                           = ULIS3_FORMAT_Yxy8;
static constexpr tFormat FMT_yxY8                           = ULIS3_FORMAT_yxY8;
static constexpr tFormat FMT_YxyA8                          = ULIS3_FORMAT_YxyA8;
static constexpr tFormat FMT_AyxY8                          = ULIS3_FORMAT_AyxY8;
static constexpr tFormat FMT_AYxy8                          = ULIS3_FORMAT_AYxy8;
static constexpr tFormat FMT_yxYA8                          = ULIS3_FORMAT_yxYA8;
static constexpr tFormat FMT_Yxy16                          = ULIS3_FORMAT_Yxy16;
static constexpr tFormat FMT_yxY16                          = ULIS3_FORMAT_yxY16;
static constexpr tFormat FMT_YxyA16                         = ULIS3_FORMAT_YxyA16;
static constexpr tFormat FMT_AyxY16                         = ULIS3_FORMAT_AyxY16;
static constexpr tFormat FMT_AYxy16                         = ULIS3_FORMAT_AYxy16;
static constexpr tFormat FMT_yxYA16                         = ULIS3_FORMAT_yxYA16;
static constexpr tFormat FMT_Yxy32                          = ULIS3_FORMAT_Yxy32;
static constexpr tFormat FMT_yxY32                          = ULIS3_FORMAT_yxY32;
static constexpr tFormat FMT_YxyA32                         = ULIS3_FORMAT_YxyA32;
static constexpr tFormat FMT_AyxY32                         = ULIS3_FORMAT_AyxY32;
static constexpr tFormat FMT_AYxy32                         = ULIS3_FORMAT_AYxy32;
static constexpr tFormat FMT_yxYA32                         = ULIS3_FORMAT_yxYA32;
static constexpr tFormat FMT_YxyF                           = ULIS3_FORMAT_YxyF;
static constexpr tFormat FMT_yxYF                           = ULIS3_FORMAT_yxYF;
static constexpr tFormat FMT_YxyAF                          = ULIS3_FORMAT_YxyAF;
static constexpr tFormat FMT_AyxYF                          = ULIS3_FORMAT_AyxYF;
static constexpr tFormat FMT_AYxyF                          = ULIS3_FORMAT_AYxyF;
static constexpr tFormat FMT_yxYAF                          = ULIS3_FORMAT_yxYAF;
static constexpr tFormat FMT_YxyD                           = ULIS3_FORMAT_YxyD;
static constexpr tFormat FMT_yxYD                           = ULIS3_FORMAT_yxYD;
static constexpr tFormat FMT_YxyAD                          = ULIS3_FORMAT_YxyAD;
static constexpr tFormat FMT_AyxYD                          = ULIS3_FORMAT_AyxYD;
static constexpr tFormat FMT_AYxyD                          = ULIS3_FORMAT_AYxyD;
static constexpr tFormat FMT_yxYAD                          = ULIS3_FORMAT_yxYAD;
static constexpr tFormat FMT_Linear_G8                      = ULIS3_FORMAT_Linear_G8;
static constexpr tFormat FMT_Linear_GA8                     = ULIS3_FORMAT_Linear_GA8;
static constexpr tFormat FMT_Linear_AG8                     = ULIS3_FORMAT_Linear_AG8;
static constexpr tFormat FMT_Linear_G16                     = ULIS3_FORMAT_Linear_G16;
static constexpr tFormat FMT_Linear_GA16                    = ULIS3_FORMAT_Linear_GA16;
static constexpr tFormat FMT_Linear_AG16                    = ULIS3_FORMAT_Linear_AG16;
static constexpr tFormat FMT_Linear_G32                     = ULIS3_FORMAT_Linear_G32;
static constexpr tFormat FMT_Linear_GA32                    = ULIS3_FORMAT_Linear_GA32;
static constexpr tFormat FMT_Linear_AG32                    = ULIS3_FORMAT_Linear_AG32;
static constexpr tFormat FMT_Linear_GF                      = ULIS3_FORMAT_Linear_GF;
static constexpr tFormat FMT_Linear_GAF                     = ULIS3_FORMAT_Linear_GAF;
static constexpr tFormat FMT_Linear_AGF                     = ULIS3_FORMAT_Linear_AGF;
static constexpr tFormat FMT_Linear_GD                      = ULIS3_FORMAT_Linear_GD;
static constexpr tFormat FMT_Linear_GAD                     = ULIS3_FORMAT_Linear_GAD;
static constexpr tFormat FMT_Linear_AGD                     = ULIS3_FORMAT_Linear_AGD;
static constexpr tFormat FMT_Linear_RGB8                    = ULIS3_FORMAT_Linear_RGB8;
static constexpr tFormat FMT_Linear_BGR8                    = ULIS3_FORMAT_Linear_BGR8;
static constexpr tFormat FMT_Linear_RGBA8                   = ULIS3_FORMAT_Linear_RGBA8;
static constexpr tFormat FMT_Linear_ABGR8                   = ULIS3_FORMAT_Linear_ABGR8;
static constexpr tFormat FMT_Linear_ARGB8                   = ULIS3_FORMAT_Linear_ARGB8;
static constexpr tFormat FMT_Linear_BGRA8                   = ULIS3_FORMAT_Linear_BGRA8;
static constexpr tFormat FMT_Linear_RGB16                   = ULIS3_FORMAT_Linear_RGB16;
static constexpr tFormat FMT_Linear_BGR16                   = ULIS3_FORMAT_Linear_BGR16;
static constexpr tFormat FMT_Linear_RGBA16                  = ULIS3_FORMAT_Linear_RGBA16;
static constexpr tFormat FMT_Linear_ABGR16                  = ULIS3_FORMAT_Linear_ABGR16;
static constexpr tFormat FMT_Linear_ARGB16                  = ULIS3_FORMAT_Linear_ARGB16;
static constexpr tFormat FMT_Linear_BGRA16                  = ULIS3_FORMAT_Linear_BGRA16;
static constexpr tFormat FMT_Linear_RGB32                   = ULIS3_FORMAT_Linear_RGB32;
static constexpr tFormat FMT_Linear_BGR32                   = ULIS3_FORMAT_Linear_BGR32;
static constexpr tFormat FMT_Linear_RGBA32                  = ULIS3_FORMAT_Linear_RGBA32;
static constexpr tFormat FMT_Linear_ABGR32                  = ULIS3_FORMAT_Linear_ABGR32;
static constexpr tFormat FMT_Linear_ARGB32                  = ULIS3_FORMAT_Linear_ARGB32;
static constexpr tFormat FMT_Linear_BGRA32                  = ULIS3_FORMAT_Linear_BGRA32;
static constexpr tFormat FMT_Linear_RGBF                    = ULIS3_FORMAT_Linear_RGBF;
static constexpr tFormat FMT_Linear_BGRF                    = ULIS3_FORMAT_Linear_BGRF;
static constexpr tFormat FMT_Linear_RGBAF                   = ULIS3_FORMAT_Linear_RGBAF;
static constexpr tFormat FMT_Linear_ABGRF                   = ULIS3_FORMAT_Linear_ABGRF;
static constexpr tFormat FMT_Linear_ARGBF                   = ULIS3_FORMAT_Linear_ARGBF;
static constexpr tFormat FMT_Linear_BGRAF                   = ULIS3_FORMAT_Linear_BGRAF;
static constexpr tFormat FMT_Linear_RGBD                    = ULIS3_FORMAT_Linear_RGBD;
static constexpr tFormat FMT_Linear_BGRD                    = ULIS3_FORMAT_Linear_BGRD;
static constexpr tFormat FMT_Linear_RGBAD                   = ULIS3_FORMAT_Linear_RGBAD;
static constexpr tFormat FMT_Linear_ABGRD                   = ULIS3_FORMAT_Linear_ABGRD;
static constexpr tFormat FMT_Linear_ARGBD                   = ULIS3_FORMAT_Linear_ARGBD;
static constexpr tFormat FMT_Linear_BGRAD                   = ULIS3_FORMAT_Linear_BGRAD;
static constexpr tFormat FMT_G8_Premultiplied               = ULIS3_FORMAT_G8_Premultiplied;
static constexpr tFormat FMT_GA8_Premultiplied              = ULIS3_FORMAT_GA8_Premultiplied;
static constexpr tFormat FMT_AG8_Premultiplied              = ULIS3_FORMAT_AG8_Premultiplied;
static constexpr tFormat FMT_G16_Premultiplied              = ULIS3_FORMAT_G16_Premultiplied;
static constexpr tFormat FMT_GA16_Premultiplied             = ULIS3_FORMAT_GA16_Premultiplied;
static constexpr tFormat FMT_AG16_Premultiplied             = ULIS3_FORMAT_AG16_Premultiplied;
static constexpr tFormat FMT_G32_Premultiplied              = ULIS3_FORMAT_G32_Premultiplied;
static constexpr tFormat FMT_GA32_Premultiplied             = ULIS3_FORMAT_GA32_Premultiplied;
static constexpr tFormat FMT_AG32_Premultiplied             = ULIS3_FORMAT_AG32_Premultiplied;
static constexpr tFormat FMT_GF_Premultiplied               = ULIS3_FORMAT_GF_Premultiplied;
static constexpr tFormat FMT_GAF_Premultiplied              = ULIS3_FORMAT_GAF_Premultiplied;
static constexpr tFormat FMT_AGF_Premultiplied              = ULIS3_FORMAT_AGF_Premultiplied;
static constexpr tFormat FMT_GD_Premultiplied               = ULIS3_FORMAT_GD_Premultiplied;
static constexpr tFormat FMT_GAD_Premultiplied              = ULIS3_FORMAT_GAD_Premultiplied;
static constexpr tFormat FMT_AGD_Premultiplied              = ULIS3_FORMAT_AGD_Premultiplied;
static constexpr tFormat FMT_RGB8_Premultiplied             = ULIS3_FORMAT_RGB8_Premultiplied;
static constexpr tFormat FMT_BGR8_Premultiplied             = ULIS3_FORMAT_BGR8_Premultiplied;
static constexpr tFormat FMT_RGBA8_Premultiplied            = ULIS3_FORMAT_RGBA8_Premultiplied;
static constexpr tFormat FMT_ABGR8_Premultiplied            = ULIS3_FORMAT_ABGR8_Premultiplied;
static constexpr tFormat FMT_ARGB8_Premultiplied            = ULIS3_FORMAT_ARGB8_Premultiplied;
static constexpr tFormat FMT_BGRA8_Premultiplied            = ULIS3_FORMAT_BGRA8_Premultiplied;
static constexpr tFormat FMT_RGB16_Premultiplied            = ULIS3_FORMAT_RGB16_Premultiplied;
static constexpr tFormat FMT_BGR16_Premultiplied            = ULIS3_FORMAT_BGR16_Premultiplied;
static constexpr tFormat FMT_RGBA16_Premultiplied           = ULIS3_FORMAT_RGBA16_Premultiplied;
static constexpr tFormat FMT_ABGR16_Premultiplied           = ULIS3_FORMAT_ABGR16_Premultiplied;
static constexpr tFormat FMT_ARGB16_Premultiplied           = ULIS3_FORMAT_ARGB16_Premultiplied;
static constexpr tFormat FMT_BGRA16_Premultiplied           = ULIS3_FORMAT_BGRA16_Premultiplied;
static constexpr tFormat FMT_RGB32_Premultiplied            = ULIS3_FORMAT_RGB32_Premultiplied;
static constexpr tFormat FMT_BGR32_Premultiplied            = ULIS3_FORMAT_BGR32_Premultiplied;
static constexpr tFormat FMT_RGBA32_Premultiplied           = ULIS3_FORMAT_RGBA32_Premultiplied;
static constexpr tFormat FMT_ABGR32_Premultiplied           = ULIS3_FORMAT_ABGR32_Premultiplied;
static constexpr tFormat FMT_ARGB32_Premultiplied           = ULIS3_FORMAT_ARGB32_Premultiplied;
static constexpr tFormat FMT_BGRA32_Premultiplied           = ULIS3_FORMAT_BGRA32_Premultiplied;
static constexpr tFormat FMT_RGBF_Premultiplied             = ULIS3_FORMAT_RGBF_Premultiplied;
static constexpr tFormat FMT_BGRF_Premultiplied             = ULIS3_FORMAT_BGRF_Premultiplied;
static constexpr tFormat FMT_RGBAF_Premultiplied            = ULIS3_FORMAT_RGBAF_Premultiplied;
static constexpr tFormat FMT_ABGRF_Premultiplied            = ULIS3_FORMAT_ABGRF_Premultiplied;
static constexpr tFormat FMT_ARGBF_Premultiplied            = ULIS3_FORMAT_ARGBF_Premultiplied;
static constexpr tFormat FMT_BGRAF_Premultiplied            = ULIS3_FORMAT_BGRAF_Premultiplied;
static constexpr tFormat FMT_RGBD_Premultiplied             = ULIS3_FORMAT_RGBD_Premultiplied;
static constexpr tFormat FMT_BGRD_Premultiplied             = ULIS3_FORMAT_BGRD_Premultiplied;
static constexpr tFormat FMT_RGBAD_Premultiplied            = ULIS3_FORMAT_RGBAD_Premultiplied;
static constexpr tFormat FMT_ABGRD_Premultiplied            = ULIS3_FORMAT_ABGRD_Premultiplied;
static constexpr tFormat FMT_ARGBD_Premultiplied            = ULIS3_FORMAT_ARGBD_Premultiplied;
static constexpr tFormat FMT_BGRAD_Premultiplied            = ULIS3_FORMAT_BGRAD_Premultiplied;
static constexpr tFormat FMT_HSV8_Premultiplied             = ULIS3_FORMAT_HSV8_Premultiplied;
static constexpr tFormat FMT_VSH8_Premultiplied             = ULIS3_FORMAT_VSH8_Premultiplied;
static constexpr tFormat FMT_HSVA8_Premultiplied            = ULIS3_FORMAT_HSVA8_Premultiplied;
static constexpr tFormat FMT_AVSH8_Premultiplied            = ULIS3_FORMAT_AVSH8_Premultiplied;
static constexpr tFormat FMT_AHSV8_Premultiplied            = ULIS3_FORMAT_AHSV8_Premultiplied;
static constexpr tFormat FMT_VSHA8_Premultiplied            = ULIS3_FORMAT_VSHA8_Premultiplied;
static constexpr tFormat FMT_HSV16_Premultiplied            = ULIS3_FORMAT_HSV16_Premultiplied;
static constexpr tFormat FMT_VSH16_Premultiplied            = ULIS3_FORMAT_VSH16_Premultiplied;
static constexpr tFormat FMT_HSVA16_Premultiplied           = ULIS3_FORMAT_HSVA16_Premultiplied;
static constexpr tFormat FMT_AVSH16_Premultiplied           = ULIS3_FORMAT_AVSH16_Premultiplied;
static constexpr tFormat FMT_AHSV16_Premultiplied           = ULIS3_FORMAT_AHSV16_Premultiplied;
static constexpr tFormat FMT_VSHA16_Premultiplied           = ULIS3_FORMAT_VSHA16_Premultiplied;
static constexpr tFormat FMT_HSV32_Premultiplied            = ULIS3_FORMAT_HSV32_Premultiplied;
static constexpr tFormat FMT_VSH32_Premultiplied            = ULIS3_FORMAT_VSH32_Premultiplied;
static constexpr tFormat FMT_HSVA32_Premultiplied           = ULIS3_FORMAT_HSVA32_Premultiplied;
static constexpr tFormat FMT_AVSH32_Premultiplied           = ULIS3_FORMAT_AVSH32_Premultiplied;
static constexpr tFormat FMT_AHSV32_Premultiplied           = ULIS3_FORMAT_AHSV32_Premultiplied;
static constexpr tFormat FMT_VSHA32_Premultiplied           = ULIS3_FORMAT_VSHA32_Premultiplied;
static constexpr tFormat FMT_HSVF_Premultiplied             = ULIS3_FORMAT_HSVF_Premultiplied;
static constexpr tFormat FMT_VSHF_Premultiplied             = ULIS3_FORMAT_VSHF_Premultiplied;
static constexpr tFormat FMT_HSVAF_Premultiplied            = ULIS3_FORMAT_HSVAF_Premultiplied;
static constexpr tFormat FMT_AVSHF_Premultiplied            = ULIS3_FORMAT_AVSHF_Premultiplied;
static constexpr tFormat FMT_AHSVF_Premultiplied            = ULIS3_FORMAT_AHSVF_Premultiplied;
static constexpr tFormat FMT_VSHAF_Premultiplied            = ULIS3_FORMAT_VSHAF_Premultiplied;
static constexpr tFormat FMT_HSVD_Premultiplied             = ULIS3_FORMAT_HSVD_Premultiplied;
static constexpr tFormat FMT_VSHD_Premultiplied             = ULIS3_FORMAT_VSHD_Premultiplied;
static constexpr tFormat FMT_HSVAD_Premultiplied            = ULIS3_FORMAT_HSVAD_Premultiplied;
static constexpr tFormat FMT_AVSHD_Premultiplied            = ULIS3_FORMAT_AVSHD_Premultiplied;
static constexpr tFormat FMT_AHSVD_Premultiplied            = ULIS3_FORMAT_AHSVD_Premultiplied;
static constexpr tFormat FMT_VSHAD_Premultiplied            = ULIS3_FORMAT_VSHAD_Premultiplied;
static constexpr tFormat FMT_HSL8_Premultiplied             = ULIS3_FORMAT_HSL8_Premultiplied;
static constexpr tFormat FMT_LSH8_Premultiplied             = ULIS3_FORMAT_LSH8_Premultiplied;
static constexpr tFormat FMT_HSLA8_Premultiplied            = ULIS3_FORMAT_HSLA8_Premultiplied;
static constexpr tFormat FMT_ALSH8_Premultiplied            = ULIS3_FORMAT_ALSH8_Premultiplied;
static constexpr tFormat FMT_AHSL8_Premultiplied            = ULIS3_FORMAT_AHSL8_Premultiplied;
static constexpr tFormat FMT_LSHA8_Premultiplied            = ULIS3_FORMAT_LSHA8_Premultiplied;
static constexpr tFormat FMT_HSL16_Premultiplied            = ULIS3_FORMAT_HSL16_Premultiplied;
static constexpr tFormat FMT_LSH16_Premultiplied            = ULIS3_FORMAT_LSH16_Premultiplied;
static constexpr tFormat FMT_HSLA16_Premultiplied           = ULIS3_FORMAT_HSLA16_Premultiplied;
static constexpr tFormat FMT_ALSH16_Premultiplied           = ULIS3_FORMAT_ALSH16_Premultiplied;
static constexpr tFormat FMT_AHSL16_Premultiplied           = ULIS3_FORMAT_AHSL16_Premultiplied;
static constexpr tFormat FMT_LSHA16_Premultiplied           = ULIS3_FORMAT_LSHA16_Premultiplied;
static constexpr tFormat FMT_HSL32_Premultiplied            = ULIS3_FORMAT_HSL32_Premultiplied;
static constexpr tFormat FMT_LSH32_Premultiplied            = ULIS3_FORMAT_LSH32_Premultiplied;
static constexpr tFormat FMT_HSLA32_Premultiplied           = ULIS3_FORMAT_HSLA32_Premultiplied;
static constexpr tFormat FMT_ALSH32_Premultiplied           = ULIS3_FORMAT_ALSH32_Premultiplied;
static constexpr tFormat FMT_AHSL32_Premultiplied           = ULIS3_FORMAT_AHSL32_Premultiplied;
static constexpr tFormat FMT_LSHA32_Premultiplied           = ULIS3_FORMAT_LSHA32_Premultiplied;
static constexpr tFormat FMT_HSLF_Premultiplied             = ULIS3_FORMAT_HSLF_Premultiplied;
static constexpr tFormat FMT_LSHF_Premultiplied             = ULIS3_FORMAT_LSHF_Premultiplied;
static constexpr tFormat FMT_HSLAF_Premultiplied            = ULIS3_FORMAT_HSLAF_Premultiplied;
static constexpr tFormat FMT_ALSHF_Premultiplied            = ULIS3_FORMAT_ALSHF_Premultiplied;
static constexpr tFormat FMT_AHSLF_Premultiplied            = ULIS3_FORMAT_AHSLF_Premultiplied;
static constexpr tFormat FMT_LSHAF_Premultiplied            = ULIS3_FORMAT_LSHAF_Premultiplied;
static constexpr tFormat FMT_HSLD_Premultiplied             = ULIS3_FORMAT_HSLD_Premultiplied;
static constexpr tFormat FMT_LSHD_Premultiplied             = ULIS3_FORMAT_LSHD_Premultiplied;
static constexpr tFormat FMT_HSLAD_Premultiplied            = ULIS3_FORMAT_HSLAD_Premultiplied;
static constexpr tFormat FMT_ALSHD_Premultiplied            = ULIS3_FORMAT_ALSHD_Premultiplied;
static constexpr tFormat FMT_AHSLD_Premultiplied            = ULIS3_FORMAT_AHSLD_Premultiplied;
static constexpr tFormat FMT_LSHAD_Premultiplied            = ULIS3_FORMAT_LSHAD_Premultiplied;
static constexpr tFormat FMT_CMY8_Premultiplied             = ULIS3_FORMAT_CMY8_Premultiplied;
static constexpr tFormat FMT_YMC8_Premultiplied             = ULIS3_FORMAT_YMC8_Premultiplied;
static constexpr tFormat FMT_CMYA8_Premultiplied            = ULIS3_FORMAT_CMYA8_Premultiplied;
static constexpr tFormat FMT_AYMC8_Premultiplied            = ULIS3_FORMAT_AYMC8_Premultiplied;
static constexpr tFormat FMT_ACMY8_Premultiplied            = ULIS3_FORMAT_ACMY8_Premultiplied;
static constexpr tFormat FMT_YMCA8_Premultiplied            = ULIS3_FORMAT_YMCA8_Premultiplied;
static constexpr tFormat FMT_CMY16_Premultiplied            = ULIS3_FORMAT_CMY16_Premultiplied;
static constexpr tFormat FMT_YMC16_Premultiplied            = ULIS3_FORMAT_YMC16_Premultiplied;
static constexpr tFormat FMT_CMYA16_Premultiplied           = ULIS3_FORMAT_CMYA16_Premultiplied;
static constexpr tFormat FMT_AYMC16_Premultiplied           = ULIS3_FORMAT_AYMC16_Premultiplied;
static constexpr tFormat FMT_ACMY16_Premultiplied           = ULIS3_FORMAT_ACMY16_Premultiplied;
static constexpr tFormat FMT_YMCA16_Premultiplied           = ULIS3_FORMAT_YMCA16_Premultiplied;
static constexpr tFormat FMT_CMY32_Premultiplied            = ULIS3_FORMAT_CMY32_Premultiplied;
static constexpr tFormat FMT_YMC32_Premultiplied            = ULIS3_FORMAT_YMC32_Premultiplied;
static constexpr tFormat FMT_CMYA32_Premultiplied           = ULIS3_FORMAT_CMYA32_Premultiplied;
static constexpr tFormat FMT_AYMC32_Premultiplied           = ULIS3_FORMAT_AYMC32_Premultiplied;
static constexpr tFormat FMT_ACMY32_Premultiplied           = ULIS3_FORMAT_ACMY32_Premultiplied;
static constexpr tFormat FMT_YMCA32_Premultiplied           = ULIS3_FORMAT_YMCA32_Premultiplied;
static constexpr tFormat FMT_CMYF_Premultiplied             = ULIS3_FORMAT_CMYF_Premultiplied;
static constexpr tFormat FMT_YMCF_Premultiplied             = ULIS3_FORMAT_YMCF_Premultiplied;
static constexpr tFormat FMT_CMYAF_Premultiplied            = ULIS3_FORMAT_CMYAF_Premultiplied;
static constexpr tFormat FMT_AYMCF_Premultiplied            = ULIS3_FORMAT_AYMCF_Premultiplied;
static constexpr tFormat FMT_ACMYF_Premultiplied            = ULIS3_FORMAT_ACMYF_Premultiplied;
static constexpr tFormat FMT_YMCAF_Premultiplied            = ULIS3_FORMAT_YMCAF_Premultiplied;
static constexpr tFormat FMT_CMYD_Premultiplied             = ULIS3_FORMAT_CMYD_Premultiplied;
static constexpr tFormat FMT_YMCD_Premultiplied             = ULIS3_FORMAT_YMCD_Premultiplied;
static constexpr tFormat FMT_CMYAD_Premultiplied            = ULIS3_FORMAT_CMYAD_Premultiplied;
static constexpr tFormat FMT_AYMCD_Premultiplied            = ULIS3_FORMAT_AYMCD_Premultiplied;
static constexpr tFormat FMT_ACMYD_Premultiplied            = ULIS3_FORMAT_ACMYD_Premultiplied;
static constexpr tFormat FMT_YMCAD_Premultiplied            = ULIS3_FORMAT_YMCAD_Premultiplied;
static constexpr tFormat FMT_CMYK8_Premultiplied            = ULIS3_FORMAT_CMYK8_Premultiplied;
static constexpr tFormat FMT_KCMY8_Premultiplied            = ULIS3_FORMAT_KCMY8_Premultiplied;
static constexpr tFormat FMT_KYMC8_Premultiplied            = ULIS3_FORMAT_KYMC8_Premultiplied;
static constexpr tFormat FMT_YMCK8_Premultiplied            = ULIS3_FORMAT_YMCK8_Premultiplied;
static constexpr tFormat FMT_CMYKA8_Premultiplied           = ULIS3_FORMAT_CMYKA8_Premultiplied;
static constexpr tFormat FMT_ACMYK8_Premultiplied           = ULIS3_FORMAT_ACMYK8_Premultiplied;
static constexpr tFormat FMT_AKYMC8_Premultiplied           = ULIS3_FORMAT_AKYMC8_Premultiplied;
static constexpr tFormat FMT_KYMCA8_Premultiplied           = ULIS3_FORMAT_KYMCA8_Premultiplied;
static constexpr tFormat FMT_CMYK16_Premultiplied           = ULIS3_FORMAT_CMYK16_Premultiplied;
static constexpr tFormat FMT_KCMY16_Premultiplied           = ULIS3_FORMAT_KCMY16_Premultiplied;
static constexpr tFormat FMT_KYMC16_Premultiplied           = ULIS3_FORMAT_KYMC16_Premultiplied;
static constexpr tFormat FMT_YMCK16_Premultiplied           = ULIS3_FORMAT_YMCK16_Premultiplied;
static constexpr tFormat FMT_CMYKA16_Premultiplied          = ULIS3_FORMAT_CMYKA16_Premultiplied;
static constexpr tFormat FMT_ACMYK16_Premultiplied          = ULIS3_FORMAT_ACMYK16_Premultiplied;
static constexpr tFormat FMT_AKYMC16_Premultiplied          = ULIS3_FORMAT_AKYMC16_Premultiplied;
static constexpr tFormat FMT_KYMCA16_Premultiplied          = ULIS3_FORMAT_KYMCA16_Premultiplied;
static constexpr tFormat FMT_CMYK32_Premultiplied           = ULIS3_FORMAT_CMYK32_Premultiplied;
static constexpr tFormat FMT_KCMY32_Premultiplied           = ULIS3_FORMAT_KCMY32_Premultiplied;
static constexpr tFormat FMT_KYMC32_Premultiplied           = ULIS3_FORMAT_KYMC32_Premultiplied;
static constexpr tFormat FMT_YMCK32_Premultiplied           = ULIS3_FORMAT_YMCK32_Premultiplied;
static constexpr tFormat FMT_CMYKA32_Premultiplied          = ULIS3_FORMAT_CMYKA32_Premultiplied;
static constexpr tFormat FMT_ACMYK32_Premultiplied          = ULIS3_FORMAT_ACMYK32_Premultiplied;
static constexpr tFormat FMT_AKYMC32_Premultiplied          = ULIS3_FORMAT_AKYMC32_Premultiplied;
static constexpr tFormat FMT_KYMCA32_Premultiplied          = ULIS3_FORMAT_KYMCA32_Premultiplied;
static constexpr tFormat FMT_CMYKF_Premultiplied            = ULIS3_FORMAT_CMYKF_Premultiplied;
static constexpr tFormat FMT_KCMYF_Premultiplied            = ULIS3_FORMAT_KCMYF_Premultiplied;
static constexpr tFormat FMT_KYMCF_Premultiplied            = ULIS3_FORMAT_KYMCF_Premultiplied;
static constexpr tFormat FMT_YMCKF_Premultiplied            = ULIS3_FORMAT_YMCKF_Premultiplied;
static constexpr tFormat FMT_CMYKAF_Premultiplied           = ULIS3_FORMAT_CMYKAF_Premultiplied;
static constexpr tFormat FMT_ACMYKF_Premultiplied           = ULIS3_FORMAT_ACMYKF_Premultiplied;
static constexpr tFormat FMT_AKYMCF_Premultiplied           = ULIS3_FORMAT_AKYMCF_Premultiplied;
static constexpr tFormat FMT_KYMCAF_Premultiplied           = ULIS3_FORMAT_KYMCAF_Premultiplied;
static constexpr tFormat FMT_CMYKD_Premultiplied            = ULIS3_FORMAT_CMYKD_Premultiplied;
static constexpr tFormat FMT_KCMYD_Premultiplied            = ULIS3_FORMAT_KCMYD_Premultiplied;
static constexpr tFormat FMT_KYMCD_Premultiplied            = ULIS3_FORMAT_KYMCD_Premultiplied;
static constexpr tFormat FMT_YMCKD_Premultiplied            = ULIS3_FORMAT_YMCKD_Premultiplied;
static constexpr tFormat FMT_CMYKAD_Premultiplied           = ULIS3_FORMAT_CMYKAD_Premultiplied;
static constexpr tFormat FMT_ACMYKD_Premultiplied           = ULIS3_FORMAT_ACMYKD_Premultiplied;
static constexpr tFormat FMT_AKYMCD_Premultiplied           = ULIS3_FORMAT_AKYMCD_Premultiplied;
static constexpr tFormat FMT_KYMCAD_Premultiplied           = ULIS3_FORMAT_KYMCAD_Premultiplied;
static constexpr tFormat FMT_YUV8_Premultiplied             = ULIS3_FORMAT_YUV8_Premultiplied;
static constexpr tFormat FMT_VUY8_Premultiplied             = ULIS3_FORMAT_VUY8_Premultiplied;
static constexpr tFormat FMT_YUVA8_Premultiplied            = ULIS3_FORMAT_YUVA8_Premultiplied;
static constexpr tFormat FMT_AVUY8_Premultiplied            = ULIS3_FORMAT_AVUY8_Premultiplied;
static constexpr tFormat FMT_AYUV8_Premultiplied            = ULIS3_FORMAT_AYUV8_Premultiplied;
static constexpr tFormat FMT_VUYA8_Premultiplied            = ULIS3_FORMAT_VUYA8_Premultiplied;
static constexpr tFormat FMT_YUV16_Premultiplied            = ULIS3_FORMAT_YUV16_Premultiplied;
static constexpr tFormat FMT_VUY16_Premultiplied            = ULIS3_FORMAT_VUY16_Premultiplied;
static constexpr tFormat FMT_YUVA16_Premultiplied           = ULIS3_FORMAT_YUVA16_Premultiplied;
static constexpr tFormat FMT_AVUY16_Premultiplied           = ULIS3_FORMAT_AVUY16_Premultiplied;
static constexpr tFormat FMT_AYUV16_Premultiplied           = ULIS3_FORMAT_AYUV16_Premultiplied;
static constexpr tFormat FMT_VUYA16_Premultiplied           = ULIS3_FORMAT_VUYA16_Premultiplied;
static constexpr tFormat FMT_YUV32_Premultiplied            = ULIS3_FORMAT_YUV32_Premultiplied;
static constexpr tFormat FMT_VUY32_Premultiplied            = ULIS3_FORMAT_VUY32_Premultiplied;
static constexpr tFormat FMT_YUVA32_Premultiplied           = ULIS3_FORMAT_YUVA32_Premultiplied;
static constexpr tFormat FMT_AVUY32_Premultiplied           = ULIS3_FORMAT_AVUY32_Premultiplied;
static constexpr tFormat FMT_AYUV32_Premultiplied           = ULIS3_FORMAT_AYUV32_Premultiplied;
static constexpr tFormat FMT_VUYA32_Premultiplied           = ULIS3_FORMAT_VUYA32_Premultiplied;
static constexpr tFormat FMT_YUVF_Premultiplied             = ULIS3_FORMAT_YUVF_Premultiplied;
static constexpr tFormat FMT_VUYF_Premultiplied             = ULIS3_FORMAT_VUYF_Premultiplied;
static constexpr tFormat FMT_YUVAF_Premultiplied            = ULIS3_FORMAT_YUVAF_Premultiplied;
static constexpr tFormat FMT_AVUYF_Premultiplied            = ULIS3_FORMAT_AVUYF_Premultiplied;
static constexpr tFormat FMT_AYUVF_Premultiplied            = ULIS3_FORMAT_AYUVF_Premultiplied;
static constexpr tFormat FMT_VUYAF_Premultiplied            = ULIS3_FORMAT_VUYAF_Premultiplied;
static constexpr tFormat FMT_YUVD_Premultiplied             = ULIS3_FORMAT_YUVD_Premultiplied;
static constexpr tFormat FMT_VUYD_Premultiplied             = ULIS3_FORMAT_VUYD_Premultiplied;
static constexpr tFormat FMT_YUVAD_Premultiplied            = ULIS3_FORMAT_YUVAD_Premultiplied;
static constexpr tFormat FMT_AVUYD_Premultiplied            = ULIS3_FORMAT_AVUYD_Premultiplied;
static constexpr tFormat FMT_AYUVD_Premultiplied            = ULIS3_FORMAT_AYUVD_Premultiplied;
static constexpr tFormat FMT_VUYAD_Premultiplied            = ULIS3_FORMAT_VUYAD_Premultiplied;
static constexpr tFormat FMT_Lab8_Premultiplied             = ULIS3_FORMAT_Lab8_Premultiplied;
static constexpr tFormat FMT_baL8_Premultiplied             = ULIS3_FORMAT_baL8_Premultiplied;
static constexpr tFormat FMT_LabA8_Premultiplied            = ULIS3_FORMAT_LabA8_Premultiplied;
static constexpr tFormat FMT_AbaL8_Premultiplied            = ULIS3_FORMAT_AbaL8_Premultiplied;
static constexpr tFormat FMT_ALab8_Premultiplied            = ULIS3_FORMAT_ALab8_Premultiplied;
static constexpr tFormat FMT_baLA8_Premultiplied            = ULIS3_FORMAT_baLA8_Premultiplied;
static constexpr tFormat FMT_Lab16_Premultiplied            = ULIS3_FORMAT_Lab16_Premultiplied;
static constexpr tFormat FMT_baL16_Premultiplied            = ULIS3_FORMAT_baL16_Premultiplied;
static constexpr tFormat FMT_LabA16_Premultiplied           = ULIS3_FORMAT_LabA16_Premultiplied;
static constexpr tFormat FMT_AbaL16_Premultiplied           = ULIS3_FORMAT_AbaL16_Premultiplied;
static constexpr tFormat FMT_ALab16_Premultiplied           = ULIS3_FORMAT_ALab16_Premultiplied;
static constexpr tFormat FMT_baLA16_Premultiplied           = ULIS3_FORMAT_baLA16_Premultiplied;
static constexpr tFormat FMT_Lab32_Premultiplied            = ULIS3_FORMAT_Lab32_Premultiplied;
static constexpr tFormat FMT_baL32_Premultiplied            = ULIS3_FORMAT_baL32_Premultiplied;
static constexpr tFormat FMT_LabA32_Premultiplied           = ULIS3_FORMAT_LabA32_Premultiplied;
static constexpr tFormat FMT_AbaL32_Premultiplied           = ULIS3_FORMAT_AbaL32_Premultiplied;
static constexpr tFormat FMT_ALab32_Premultiplied           = ULIS3_FORMAT_ALab32_Premultiplied;
static constexpr tFormat FMT_baLA32_Premultiplied           = ULIS3_FORMAT_baLA32_Premultiplied;
static constexpr tFormat FMT_LabF_Premultiplied             = ULIS3_FORMAT_LabF_Premultiplied;
static constexpr tFormat FMT_baLF_Premultiplied             = ULIS3_FORMAT_baLF_Premultiplied;
static constexpr tFormat FMT_LabAF_Premultiplied            = ULIS3_FORMAT_LabAF_Premultiplied;
static constexpr tFormat FMT_AbaLF_Premultiplied            = ULIS3_FORMAT_AbaLF_Premultiplied;
static constexpr tFormat FMT_ALabF_Premultiplied            = ULIS3_FORMAT_ALabF_Premultiplied;
static constexpr tFormat FMT_baLAF_Premultiplied            = ULIS3_FORMAT_baLAF_Premultiplied;
static constexpr tFormat FMT_LabD_Premultiplied             = ULIS3_FORMAT_LabD_Premultiplied;
static constexpr tFormat FMT_baLD_Premultiplied             = ULIS3_FORMAT_baLD_Premultiplied;
static constexpr tFormat FMT_LabAD_Premultiplied            = ULIS3_FORMAT_LabAD_Premultiplied;
static constexpr tFormat FMT_AbaLD_Premultiplied            = ULIS3_FORMAT_AbaLD_Premultiplied;
static constexpr tFormat FMT_ALabD_Premultiplied            = ULIS3_FORMAT_ALabD_Premultiplied;
static constexpr tFormat FMT_baLAD_Premultiplied            = ULIS3_FORMAT_baLAD_Premultiplied;
static constexpr tFormat FMT_XYZ8_Premultiplied             = ULIS3_FORMAT_XYZ8_Premultiplied;
static constexpr tFormat FMT_ZYX8_Premultiplied             = ULIS3_FORMAT_ZYX8_Premultiplied;
static constexpr tFormat FMT_XYZA8_Premultiplied            = ULIS3_FORMAT_XYZA8_Premultiplied;
static constexpr tFormat FMT_AZYX8_Premultiplied            = ULIS3_FORMAT_AZYX8_Premultiplied;
static constexpr tFormat FMT_AXYZ8_Premultiplied            = ULIS3_FORMAT_AXYZ8_Premultiplied;
static constexpr tFormat FMT_ZYXA8_Premultiplied            = ULIS3_FORMAT_ZYXA8_Premultiplied;
static constexpr tFormat FMT_XYZ16_Premultiplied            = ULIS3_FORMAT_XYZ16_Premultiplied;
static constexpr tFormat FMT_ZYX16_Premultiplied            = ULIS3_FORMAT_ZYX16_Premultiplied;
static constexpr tFormat FMT_XYZA16_Premultiplied           = ULIS3_FORMAT_XYZA16_Premultiplied;
static constexpr tFormat FMT_AZYX16_Premultiplied           = ULIS3_FORMAT_AZYX16_Premultiplied;
static constexpr tFormat FMT_AXYZ16_Premultiplied           = ULIS3_FORMAT_AXYZ16_Premultiplied;
static constexpr tFormat FMT_ZYXA16_Premultiplied           = ULIS3_FORMAT_ZYXA16_Premultiplied;
static constexpr tFormat FMT_XYZ32_Premultiplied            = ULIS3_FORMAT_XYZ32_Premultiplied;
static constexpr tFormat FMT_ZYX32_Premultiplied            = ULIS3_FORMAT_ZYX32_Premultiplied;
static constexpr tFormat FMT_XYZA32_Premultiplied           = ULIS3_FORMAT_XYZA32_Premultiplied;
static constexpr tFormat FMT_AZYX32_Premultiplied           = ULIS3_FORMAT_AZYX32_Premultiplied;
static constexpr tFormat FMT_AXYZ32_Premultiplied           = ULIS3_FORMAT_AXYZ32_Premultiplied;
static constexpr tFormat FMT_ZYXA32_Premultiplied           = ULIS3_FORMAT_ZYXA32_Premultiplied;
static constexpr tFormat FMT_XYZF_Premultiplied             = ULIS3_FORMAT_XYZF_Premultiplied;
static constexpr tFormat FMT_ZYXF_Premultiplied             = ULIS3_FORMAT_ZYXF_Premultiplied;
static constexpr tFormat FMT_XYZAF_Premultiplied            = ULIS3_FORMAT_XYZAF_Premultiplied;
static constexpr tFormat FMT_AZYXF_Premultiplied            = ULIS3_FORMAT_AZYXF_Premultiplied;
static constexpr tFormat FMT_AXYZF_Premultiplied            = ULIS3_FORMAT_AXYZF_Premultiplied;
static constexpr tFormat FMT_ZYXAF_Premultiplied            = ULIS3_FORMAT_ZYXAF_Premultiplied;
static constexpr tFormat FMT_XYZD_Premultiplied             = ULIS3_FORMAT_XYZD_Premultiplied;
static constexpr tFormat FMT_ZYXD_Premultiplied             = ULIS3_FORMAT_ZYXD_Premultiplied;
static constexpr tFormat FMT_XYZAD_Premultiplied            = ULIS3_FORMAT_XYZAD_Premultiplied;
static constexpr tFormat FMT_AZYXD_Premultiplied            = ULIS3_FORMAT_AZYXD_Premultiplied;
static constexpr tFormat FMT_AXYZD_Premultiplied            = ULIS3_FORMAT_AXYZD_Premultiplied;
static constexpr tFormat FMT_ZYXAD_Premultiplied            = ULIS3_FORMAT_ZYXAD_Premultiplied;
static constexpr tFormat FMT_Yxy8_Premultiplied             = ULIS3_FORMAT_Yxy8_Premultiplied;
static constexpr tFormat FMT_yxY8_Premultiplied             = ULIS3_FORMAT_yxY8_Premultiplied;
static constexpr tFormat FMT_YxyA8_Premultiplied            = ULIS3_FORMAT_YxyA8_Premultiplied;
static constexpr tFormat FMT_AyxY8_Premultiplied            = ULIS3_FORMAT_AyxY8_Premultiplied;
static constexpr tFormat FMT_AYxy8_Premultiplied            = ULIS3_FORMAT_AYxy8_Premultiplied;
static constexpr tFormat FMT_yxYA8_Premultiplied            = ULIS3_FORMAT_yxYA8_Premultiplied;
static constexpr tFormat FMT_Yxy16_Premultiplied            = ULIS3_FORMAT_Yxy16_Premultiplied;
static constexpr tFormat FMT_yxY16_Premultiplied            = ULIS3_FORMAT_yxY16_Premultiplied;
static constexpr tFormat FMT_YxyA16_Premultiplied           = ULIS3_FORMAT_YxyA16_Premultiplied;
static constexpr tFormat FMT_AyxY16_Premultiplied           = ULIS3_FORMAT_AyxY16_Premultiplied;
static constexpr tFormat FMT_AYxy16_Premultiplied           = ULIS3_FORMAT_AYxy16_Premultiplied;
static constexpr tFormat FMT_yxYA16_Premultiplied           = ULIS3_FORMAT_yxYA16_Premultiplied;
static constexpr tFormat FMT_Yxy32_Premultiplied            = ULIS3_FORMAT_Yxy32_Premultiplied;
static constexpr tFormat FMT_yxY32_Premultiplied            = ULIS3_FORMAT_yxY32_Premultiplied;
static constexpr tFormat FMT_YxyA32_Premultiplied           = ULIS3_FORMAT_YxyA32_Premultiplied;
static constexpr tFormat FMT_AyxY32_Premultiplied           = ULIS3_FORMAT_AyxY32_Premultiplied;
static constexpr tFormat FMT_AYxy32_Premultiplied           = ULIS3_FORMAT_AYxy32_Premultiplied;
static constexpr tFormat FMT_yxYA32_Premultiplied           = ULIS3_FORMAT_yxYA32_Premultiplied;
static constexpr tFormat FMT_YxyF_Premultiplied             = ULIS3_FORMAT_YxyF_Premultiplied;
static constexpr tFormat FMT_yxYF_Premultiplied             = ULIS3_FORMAT_yxYF_Premultiplied;
static constexpr tFormat FMT_YxyAF_Premultiplied            = ULIS3_FORMAT_YxyAF_Premultiplied;
static constexpr tFormat FMT_AyxYF_Premultiplied            = ULIS3_FORMAT_AyxYF_Premultiplied;
static constexpr tFormat FMT_AYxyF_Premultiplied            = ULIS3_FORMAT_AYxyF_Premultiplied;
static constexpr tFormat FMT_yxYAF_Premultiplied            = ULIS3_FORMAT_yxYAF_Premultiplied;
static constexpr tFormat FMT_YxyD_Premultiplied             = ULIS3_FORMAT_YxyD_Premultiplied;
static constexpr tFormat FMT_yxYD_Premultiplied             = ULIS3_FORMAT_yxYD_Premultiplied;
static constexpr tFormat FMT_YxyAD_Premultiplied            = ULIS3_FORMAT_YxyAD_Premultiplied;
static constexpr tFormat FMT_AyxYD_Premultiplied            = ULIS3_FORMAT_AyxYD_Premultiplied;
static constexpr tFormat FMT_AYxyD_Premultiplied            = ULIS3_FORMAT_AYxyD_Premultiplied;
static constexpr tFormat FMT_yxYAD_Premultiplied            = ULIS3_FORMAT_yxYAD_Premultiplied;
static constexpr tFormat FMT_Linear_G8_Premultiplied        = ULIS3_FORMAT_Linear_G8_Premultiplied;
static constexpr tFormat FMT_Linear_GA8_Premultiplied       = ULIS3_FORMAT_Linear_GA8_Premultiplied;
static constexpr tFormat FMT_Linear_AG8_Premultiplied       = ULIS3_FORMAT_Linear_AG8_Premultiplied;
static constexpr tFormat FMT_Linear_G16_Premultiplied       = ULIS3_FORMAT_Linear_G16_Premultiplied;
static constexpr tFormat FMT_Linear_GA16_Premultiplied      = ULIS3_FORMAT_Linear_GA16_Premultiplied;
static constexpr tFormat FMT_Linear_AG16_Premultiplied      = ULIS3_FORMAT_Linear_AG16_Premultiplied;
static constexpr tFormat FMT_Linear_G32_Premultiplied       = ULIS3_FORMAT_Linear_G32_Premultiplied;
static constexpr tFormat FMT_Linear_GA32_Premultiplied      = ULIS3_FORMAT_Linear_GA32_Premultiplied;
static constexpr tFormat FMT_Linear_AG32_Premultiplied      = ULIS3_FORMAT_Linear_AG32_Premultiplied;
static constexpr tFormat FMT_Linear_GF_Premultiplied        = ULIS3_FORMAT_Linear_GF_Premultiplied;
static constexpr tFormat FMT_Linear_GAF_Premultiplied       = ULIS3_FORMAT_Linear_GAF_Premultiplied;
static constexpr tFormat FMT_Linear_AGF_Premultiplied       = ULIS3_FORMAT_Linear_AGF_Premultiplied;
static constexpr tFormat FMT_Linear_GD_Premultiplied        = ULIS3_FORMAT_Linear_GD_Premultiplied;
static constexpr tFormat FMT_Linear_GAD_Premultiplied       = ULIS3_FORMAT_Linear_GAD_Premultiplied;
static constexpr tFormat FMT_Linear_AGD_Premultiplied       = ULIS3_FORMAT_Linear_AGD_Premultiplied;
static constexpr tFormat FMT_Linear_RGB8_Premultiplied      = ULIS3_FORMAT_Linear_RGB8_Premultiplied;
static constexpr tFormat FMT_Linear_BGR8_Premultiplied      = ULIS3_FORMAT_Linear_BGR8_Premultiplied;
static constexpr tFormat FMT_Linear_RGBA8_Premultiplied     = ULIS3_FORMAT_Linear_RGBA8_Premultiplied;
static constexpr tFormat FMT_Linear_ABGR8_Premultiplied     = ULIS3_FORMAT_Linear_ABGR8_Premultiplied;
static constexpr tFormat FMT_Linear_ARGB8_Premultiplied     = ULIS3_FORMAT_Linear_ARGB8_Premultiplied;
static constexpr tFormat FMT_Linear_BGRA8_Premultiplied     = ULIS3_FORMAT_Linear_BGRA8_Premultiplied;
static constexpr tFormat FMT_Linear_RGB16_Premultiplied     = ULIS3_FORMAT_Linear_RGB16_Premultiplied;
static constexpr tFormat FMT_Linear_BGR16_Premultiplied     = ULIS3_FORMAT_Linear_BGR16_Premultiplied;
static constexpr tFormat FMT_Linear_RGBA16_Premultiplied    = ULIS3_FORMAT_Linear_RGBA16_Premultiplied;
static constexpr tFormat FMT_Linear_ABGR16_Premultiplied    = ULIS3_FORMAT_Linear_ABGR16_Premultiplied;
static constexpr tFormat FMT_Linear_ARGB16_Premultiplied    = ULIS3_FORMAT_Linear_ARGB16_Premultiplied;
static constexpr tFormat FMT_Linear_BGRA16_Premultiplied    = ULIS3_FORMAT_Linear_BGRA16_Premultiplied;
static constexpr tFormat FMT_Linear_RGB32_Premultiplied     = ULIS3_FORMAT_Linear_RGB32_Premultiplied;
static constexpr tFormat FMT_Linear_BGR32_Premultiplied     = ULIS3_FORMAT_Linear_BGR32_Premultiplied;
static constexpr tFormat FMT_Linear_RGBA32_Premultiplied    = ULIS3_FORMAT_Linear_RGBA32_Premultiplied;
static constexpr tFormat FMT_Linear_ABGR32_Premultiplied    = ULIS3_FORMAT_Linear_ABGR32_Premultiplied;
static constexpr tFormat FMT_Linear_ARGB32_Premultiplied    = ULIS3_FORMAT_Linear_ARGB32_Premultiplied;
static constexpr tFormat FMT_Linear_BGRA32_Premultiplied    = ULIS3_FORMAT_Linear_BGRA32_Premultiplied;
static constexpr tFormat FMT_Linear_RGBF_Premultiplied      = ULIS3_FORMAT_Linear_RGBF_Premultiplied;
static constexpr tFormat FMT_Linear_BGRF_Premultiplied      = ULIS3_FORMAT_Linear_BGRF_Premultiplied;
static constexpr tFormat FMT_Linear_RGBAF_Premultiplied     = ULIS3_FORMAT_Linear_RGBAF_Premultiplied;
static constexpr tFormat FMT_Linear_ABGRF_Premultiplied     = ULIS3_FORMAT_Linear_ABGRF_Premultiplied;
static constexpr tFormat FMT_Linear_ARGBF_Premultiplied     = ULIS3_FORMAT_Linear_ARGBF_Premultiplied;
static constexpr tFormat FMT_Linear_BGRAF_Premultiplied     = ULIS3_FORMAT_Linear_BGRAF_Premultiplied;
static constexpr tFormat FMT_Linear_RGBD_Premultiplied      = ULIS3_FORMAT_Linear_RGBD_Premultiplied;
static constexpr tFormat FMT_Linear_BGRD_Premultiplied      = ULIS3_FORMAT_Linear_BGRD_Premultiplied;
static constexpr tFormat FMT_Linear_RGBAD_Premultiplied     = ULIS3_FORMAT_Linear_RGBAD_Premultiplied;
static constexpr tFormat FMT_Linear_ABGRD_Premultiplied     = ULIS3_FORMAT_Linear_ABGRD_Premultiplied;
static constexpr tFormat FMT_Linear_ARGBD_Premultiplied     = ULIS3_FORMAT_Linear_ARGBD_Premultiplied;
static constexpr tFormat FMT_Linear_BGRAD_Premultiplied     = ULIS3_FORMAT_Linear_BGRAD_Premultiplied;
ULIS3_NAMESPACE_END

