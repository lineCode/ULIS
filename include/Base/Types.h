// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Types.h
* @author       Clement Berthaud
* @brief        This file provides core types definitions for the ULIS2 library.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Base/CoreInternal.h"
#include <cstdint>

ULIS2_NAMESPACE_BEGIN
// Typedefs
typedef  uint8_t    uint8;
typedef  uint16_t   uint16;
typedef  uint32_t   uint32;
typedef  uint64_t   uint64;
typedef  int8_t     int8;
typedef  int16_t    int16;
typedef  int32_t    int32;
typedef  int64_t    int64;
typedef  float      ufloat;
typedef  double     udouble;
typedef  uint8_t    tByte;
typedef  uint32_t   tFormat;
typedef  uint32_t   tSize;
typedef  uint32_t   tIndex;

// Types
enum eType {
      TYPE_UINT8     = 0x0
    , TYPE_UINT16    = 0x1
    , TYPE_UINT32    = 0x2
    , TYPE_UFLOAT    = 0x3
    , TYPE_UDOUBLE   = 0x4
    , TYPE_INVALID
};

// Models
enum eColorModel {
      CM_ANY
    , CM_GREY
    , CM_RGB
    , CM_HSV
    , CM_HSL
    , CM_CMY
    , CM_CMYK
    , CM_YUV
    , CM_Lab
    , CM_XYZ
    , CM_Yxy
};

// Macro for all types for template instanciation
#define ULIS2_FOR_ALL_TYPES_DO( X, _E0, _E1, _E2, _E3 )     \
    X( uint8,   _E0, _E1, _E2, _E3 )                        \
    X( uint16,  _E0, _E1, _E2, _E3 )                        \
    X( uint32,  _E0, _E1, _E2, _E3 )                        \
    X( ufloat,  _E0, _E1, _E2, _E3 )                        \
    X( udouble, _E0, _E1, _E2, _E3 )

// Macro for all types for combination template instanciation
#define ULIS2_FOR_ALL_TYPES_COMBINATIONS_DO( X )    \
    X( uint8,   uint8    )                          \
    X( uint8,   uint16   )                          \
    X( uint8,   uint32   )                          \
    X( uint8,   ufloat   )                          \
    X( uint8,   udouble  )                          \
    X( uint16,  uint8   )                           \
    X( uint16,  uint16  )                           \
    X( uint16,  uint32  )                           \
    X( uint16,  ufloat  )                           \
    X( uint16,  udouble )                           \
    X( uint32,  uint8   )                           \
    X( uint32,  uint16  )                           \
    X( uint32,  uint32  )                           \
    X( uint32,  ufloat  )                           \
    X( uint32,  udouble )                           \
    X( ufloat,  uint8   )                           \
    X( ufloat,  uint16  )                           \
    X( ufloat,  uint32  )                           \
    X( ufloat,  ufloat  )                           \
    X( ufloat,  udouble )                           \
    X( udouble, uint8   )                           \
    X( udouble, uint16  )                           \
    X( udouble, uint32  )                           \
    X( udouble, ufloat  )                           \
    X( udouble, udouble )

ULIS2_NAMESPACE_END

