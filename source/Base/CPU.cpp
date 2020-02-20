// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         CPU.cpp
* @author       Clement Berthaud
* @brief        This file provides the definition for the FCPU struct.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include "Base/CPU.h"
#include "cpu_x86.h"

ULIS2_NAMESPACE_BEGIN
ULIS2_API const FCPU gCpuInfo = FCPU();

/////////////////////////////////////////////////////
/// FCPU
FCPU::FCPU()
{
    ::FeatureDetector::cpu_x86 tmp;
    tmp.detect_host();
    info.Vendor_AMD         = tmp.Vendor_AMD    ;
    info.Vendor_Intel       = tmp.Vendor_Intel  ;
    info.OS_x64             = tmp.OS_x64        ;
    info.OS_AVX             = tmp.OS_AVX        ;
    info.OS_AVX512          = tmp.OS_AVX512     ;
    info.HW_MMX             = tmp.HW_MMX        ;
    info.HW_x64             = tmp.HW_x64        ;
    info.HW_ABM             = tmp.HW_ABM        ;
    info.HW_RDRAND          = tmp.HW_RDRAND     ;
    info.HW_BMI1            = tmp.HW_BMI1       ;
    info.HW_BMI2            = tmp.HW_BMI2       ;
    info.HW_ADX             = tmp.HW_ADX        ;
    info.HW_PREFETCHWT1     = tmp.HW_PREFETCHWT1;
    info.HW_MPX             = tmp.HW_MPX        ;
    info.HW_SSE             = tmp.HW_SSE        ;
    info.HW_SSE2            = tmp.HW_SSE2       ;
    info.HW_SSE3            = tmp.HW_SSE3       ;
    info.HW_SSSE3           = tmp.HW_SSSE3      ;
    info.HW_SSE41           = tmp.HW_SSE41      ;
    info.HW_SSE42           = tmp.HW_SSE42      ;
    info.HW_SSE4a           = tmp.HW_SSE4a      ;
    info.HW_AES             = tmp.HW_AES        ;
    info.HW_SHA             = tmp.HW_SHA        ;
    info.HW_AVX             = tmp.HW_AVX        ;
    info.HW_XOP             = tmp.HW_XOP        ;
    info.HW_FMA3            = tmp.HW_FMA3       ;
    info.HW_FMA4            = tmp.HW_FMA4       ;
    info.HW_AVX2            = tmp.HW_AVX2       ;
    info.HW_AVX512_F        = tmp.HW_AVX512_F   ;
    info.HW_AVX512_PF       = tmp.HW_AVX512_PF  ;
    info.HW_AVX512_ER       = tmp.HW_AVX512_ER  ;
    info.HW_AVX512_CD       = tmp.HW_AVX512_CD  ;
    info.HW_AVX512_VL       = tmp.HW_AVX512_VL  ;
    info.HW_AVX512_BW       = tmp.HW_AVX512_BW  ;
    info.HW_AVX512_DQ       = tmp.HW_AVX512_DQ  ;
    info.HW_AVX512_IFMA     = tmp.HW_AVX512_IFMA;
    info.HW_AVX512_VBMI     = tmp.HW_AVX512_VBMI;
}

ULIS2_NAMESPACE_END

