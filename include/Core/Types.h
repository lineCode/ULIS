// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS3
*__________________
*
* @file         Types.h
* @author       Clement Berthaud
* @brief        This file provides core types definitions for the ULIS3 library.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Platform.h"

ULIS3_NAMESPACE_BEGIN
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

// Perf codes
#define ULIS3_PERF_MT           0x1
#define ULIS3_PERF_TSPEC        0x2
#define ULIS3_PERF_SSE42        0x4
#define ULIS3_PERF_AVX2         0x8
#define ULIS3_PERF_GPU          0x10

// Type codes
#define ULIS3_TYPE_UINT8    0x0
#define ULIS3_TYPE_UINT16   0x1
#define ULIS3_TYPE_UINT32   0x2
#define ULIS3_TYPE_UFLOAT   0x3
#define ULIS3_TYPE_UDOUBLE  0x4

// Model codes
#define ULIS3_CM_ANY    0
#define ULIS3_CM_GREY   1
#define ULIS3_CM_RGB    2
#define ULIS3_CM_HSV    3
#define ULIS3_CM_HSL    4
#define ULIS3_CM_CMY    5
#define ULIS3_CM_CMYK   6
#define ULIS3_CM_YUV    7
#define ULIS3_CM_Lab    8
#define ULIS3_CM_XYZ    9
#define ULIS3_CM_Yxy    10

/////////////////////////////////////////////////////
// Named booleans literals
#define ULIS3_BLOCKING      true
#define ULIS3_NONBLOCKING   false
#define ULIS3_CALLCB        true
#define ULIS3_NOCB          false
#define ULIS3_AA            true
#define ULIS3_NOAA          false

// Perf enum
enum ePerf {
      PERF_MT
    , PERF_TSPEC
    , PERF_SSE42
    , PERF_AVX2
    , PERF_GPU
};

// Type enum
enum eType {
      TYPE_UINT8     = ULIS3_TYPE_UINT8
    , TYPE_UINT16    = ULIS3_TYPE_UINT16
    , TYPE_UINT32    = ULIS3_TYPE_UINT32
    , TYPE_UFLOAT    = ULIS3_TYPE_UFLOAT
    , TYPE_UDOUBLE   = ULIS3_TYPE_UDOUBLE
};

// Model enum
enum eColorModel {
      CM_GREY   = ULIS3_CM_GREY
    , CM_RGB    = ULIS3_CM_RGB
    , CM_HSV    = ULIS3_CM_HSV
    , CM_HSL    = ULIS3_CM_HSL
    , CM_CMY    = ULIS3_CM_CMY
    , CM_CMYK   = ULIS3_CM_CMYK
    , CM_YUV    = ULIS3_CM_YUV
    , CM_Lab    = ULIS3_CM_Lab
    , CM_XYZ    = ULIS3_CM_XYZ
    , CM_Yxy    = ULIS3_CM_Yxy
};

// Macro for all types for template instanciation
#define ULIS3_FOR_ALL_TYPES_DO( X, _E0, _E1, _E2, _E3 )     \
    X( uint8,   _E0, _E1, _E2, _E3 )                        \
    X( uint16,  _E0, _E1, _E2, _E3 )                        \
    X( uint32,  _E0, _E1, _E2, _E3 )                        \
    X( ufloat,  _E0, _E1, _E2, _E3 )                        \
    X( udouble, _E0, _E1, _E2, _E3 )

// Macro for all types for combination template instanciation
#define ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X )    \
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

ULIS3_NAMESPACE_END

