// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Format.h
* @author       Clement Berthaud
* @brief        This file provides core format definitions for the ULIS2 library.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
/////////////////////////////////////////////////////
// Pixel format
//
//          DYNAMIC EXTRA INFO      FIXED FORMAT INFO
//          32   28   24   20       16        8    4  0
//          1098 7654 3210 9876     5432 1098 7654 3210
//          •••• •••• ••EE DDDD     ASRF MMMM CCCC TTTT
//    Example: RGBA8
//                            1     1000 0010 0011 0000
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

#define ULIS2_E_TYPE        ( ~0xF )
#define ULIS2_E_CHANNELS    ( ~( 0xF << 4 ) )
#define ULIS2_E_MODEL       ( ~( 0xF << 8 ) )
#define ULIS2_E_FLOATING    ( ~( 0x1 << 12 ) )
#define ULIS2_E_REVERSE     ( ~( 0x1 << 13 ) )
#define ULIS2_E_SWAP        ( ~( 0x1 << 14 ) )
#define ULIS2_E_ALPHA       ( ~( 0x1 << 15 ) )
#define ULIS2_E_DEPTH       ( ~( 0xF << 16 )
#define ULIS2_E_EXTRA       ( ~( 0x3 << 20 )

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

#define ULIS2_MAX_CHANNELS  5
