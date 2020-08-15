// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS
*__________________
*
* @file         Device.cpp
* @author       Clement Berthaud
* @brief        This file provides the definition for the FDevice tools.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "System/Device.h"
/////////////////////////////////////////////////////
// Device info bit field "bField" in base 64
//
//   64|      60|  56|  52|  48|      44|  40|  36|  32|      28|  24|  20|  16|      12|   8|   4|   0
//          •••• •••• •••• ••••     •••• •••• •••• ••••     •••• •••• •••• ••••     •••• •••• •••• ••••
//          /+98 7654 3210 zyxw     vuts rqpo nmlk jihg     fedc baZY XWVU TSRQ     PONM LKJI HGFE DCBA
//
//          bit index caption:
//          A: Is Hardware AMD;
//          B: Is Hardware Intel;
//          C: Is OS x64;
//          D: Has OS AVX;
//          E: Has OS AVX512;
//          F: Has Hardware x64;
//          G: Has Hardware MMX;
//          H: Has Hardware ABM;
//          I: Has Hardware RDRAND;
//          J: Has Hardware BMI1;
//          K: Has Hardware BMI2;
//          L: Has Hardware ADX;
//          M: Has Hardware PREFETCHWT1;
//          N: Has Hardware MPX;
//          O: Has Hardware SSE;
//          P: Has Hardware SSE2;
//          Q: Has Hardware SSE3;
//          R: Has Hardware SSSE3;
//          S: Has Hardware SSE41;
//          T: Has Hardware SSE42;
//          U: Has Hardware SSE4a;
//          V: Has Hardware AES;
//          W: Has Hardware SHA;
//          X: Has Hardware AVX;
//          Y: Has Hardware XOP;
//          Z: Has Hardware FMA3;
//          a: Has Hardware FMA4;
//          b: Has Hardware AVX2;
//          c: Has Hardware AVX512_F;
//          d: Has Hardware AVX512_PF;
//          e: Has Hardware AVX512_ER;
//          f: Has Hardware AVX512_CD;
//          g: Has Hardware AVX512_VL;
//          h: Has Hardware AVX512_BW;
//          i: Has Hardware AVX512_DQ;
//          j: Has Hardware AVX512_IFMA;
//          k: Has Hardware AVX512_VBMI;
//          0: __reserved__
//          1: __reserved__
//          2: __reserved__
//          3: __reserved__
//          4: __reserved__
//          5: __reserved__
//          6: __reserved__
//          7: __reserved__
//          8: __reserved__
//          9: __reserved__
//          +: __reserved__
//          /: __reserved__

#if defined(ULIS_WIN)
#include "System/Device_Windows.ipp"
#elif defined(ULIS_MACOS)
#include "System/Device_macOS.ipp"
#elif defined(ULIS_LINUX)
#include "System/Device_Linux.ipp"
#else
#include "System/Device_Generic.ipp"
#endif

