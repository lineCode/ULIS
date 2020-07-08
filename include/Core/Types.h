// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS3
*__________________
*
* @file         Types.h
* @author       Clement Berthaud
* @brief        This file provides core types definitions for the ULIS3 library.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Platform.h"
#include <cstdint>
#include <cstring>
#include <memory>

ULIS3_NAMESPACE_BEGIN
// Domain Range Typdefs
typedef  uint8_t    uint8;      ///< Used for the smallest adressable type, unsigned 8bit images domain range values and main type for image bits memory storage.
typedef  uint16_t   uint16;     ///< Used for unsigned 16bit images domain range values.
typedef  uint32_t   uint32;     ///< Used for unsigned 32bit images domain range values and sizes such as width and height.
typedef  uint64_t   uint64;     ///< Used for unsigned 64bit images domain range values and whole buffer sizes that might overflow 32bit range.
typedef  int8_t     int8;       ///< Used for signed 8bit images domain range values.
typedef  int16_t    int16;      ///< Used for signed 16bit images domain range values.
typedef  int32_t    int32;      ///< Used for signed 32bit images domain range values.
typedef  int64_t    int64;      ///< Used for signed 64bit images domain range values.
typedef  float      ufloat;     ///< Used for float images domain range values, indicates normalized range [0;1]
typedef  double     udouble;    ///< Used for double images domain range values, indicates normalized range [0;1]

// Semantic Typedefs
typedef  uint32_t   tFormat;    ///< Used for formats magic numbers, it might get changed to 64bit in the future.

// Perf codes
#define ULIS3_PERF_MT           0x1
#define ULIS3_PERF_SSE42        0x2
#define ULIS3_PERF_AVX2         0x4

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

// Profile codes
#define ULIS3_None                  0
#define ULIS3_LinearGrey            1
#define ULIS3_sGrey                 2
#define ULIS3_Grey2_2_D65           3
#define ULIS3_LinearRGB             4
#define ULIS3_sRGB                  5
#define ULIS3_AdobeRGB              6
#define ULIS3_YUV                   7
#define ULIS3_XYZ                   8
#define ULIS3_LabD50                9
#define ULIS3_LabD65                10
#define ULIS3_Yxy                   11

// Channels codes
#define ULIS3_MAX_CHANNELS          5
#define ULIS3_CHANNEL_1_BIT         1
#define ULIS3_CHANNEL_2_BIT         2
#define ULIS3_CHANNEL_3_BIT         4
#define ULIS3_CHANNEL_4_BIT         8
#define ULIS3_CHANNEL_5_BIT         16

// Named booleans literals
#define ULIS3_BLOCKING              1
#define ULIS3_NONBLOCKING           0
#define ULIS3_CALLCB                1
#define ULIS3_NOCB                  0
#define ULIS3_AA                    1
#define ULIS3_NOAA                  0
#define ULIS3_PREMULTIPLIED         1
#define ULIS3_UNPREMULTIPLIED       0
#define ULIS3_GAMMA_COMPRESSED      1
#define ULIS3_GAMMA_UNCOMPRESSED    0

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

// Extrapolation Method
enum eExtrapolationMethod {
      EM_TRANSPARENT
    , EM_CONSTANT
    , EM_EXTEND
    , EM_WRAP
    , EM_MIRROR
};

ULIS3_NAMESPACE_END

