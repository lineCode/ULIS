// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         CPU.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the FCPU struct.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Base/Core.h"

ULIS2_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
// FCPUInfo
struct ULIS2_API FCPUInfo
{
    bool Vendor_AMD;
    bool Vendor_Intel;
    bool OS_x64;
    bool OS_AVX;
    bool OS_AVX512;
    bool HW_MMX;
    bool HW_x64;
    bool HW_ABM;
    bool HW_RDRAND;
    bool HW_BMI1;
    bool HW_BMI2;
    bool HW_ADX;
    bool HW_PREFETCHWT1;
    bool HW_MPX;
    bool HW_SSE;
    bool HW_SSE2;
    bool HW_SSE3;
    bool HW_SSSE3;
    bool HW_SSE41;
    bool HW_SSE42;
    bool HW_SSE4a;
    bool HW_AES;
    bool HW_SHA;
    bool HW_AVX;
    bool HW_XOP;
    bool HW_FMA3;
    bool HW_FMA4;
    bool HW_AVX2;
    bool HW_AVX512_F;
    bool HW_AVX512_PF;
    bool HW_AVX512_ER;
    bool HW_AVX512_CD;
    bool HW_AVX512_VL;
    bool HW_AVX512_BW;
    bool HW_AVX512_DQ;
    bool HW_AVX512_IFMA;
    bool HW_AVX512_VBMI;
};

/////////////////////////////////////////////////////
/// @struct     FCPU
/// @brief      The FCPU struct provides a small wrapper around the FeatureDetector interface.
struct ULIS2_API FCPU
{
public:
    // Construction
    /// @fn         FCPU()
    /// @brief      Default Constructor.
    /// @details    Initializes members by calling the appropriate functions in FeatureDetector.
    FCPU();

public:
    // Public Data Members
    FCPUInfo info;    ///< public member info of type FCPUInfo, all fields should be initialized by constructor.
};

ULIS2_API extern const FCPU gCpuInfo;

ULIS2_NAMESPACE_END

