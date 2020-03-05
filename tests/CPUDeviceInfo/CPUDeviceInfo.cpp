// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         CPUDeviceInfo.cpp
* @author       Clement Berthaud
* @brief        CPUDeviceInfo application for ULIS2.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include <ULIS2>

int
main() {
    ::ul2::FHostDeviceInfo deviceInfo = ::ul2::FHostDeviceInfo::Detect();
    std::cout << "Vendor_AMD        :" << deviceInfo.Vendor_AMD         << std::endl;
    std::cout << "Vendor_Intel      :" << deviceInfo.Vendor_Intel       << std::endl;
    std::cout << "OS_x64            :" << deviceInfo.OS_x64             << std::endl;
    std::cout << "OS_AVX            :" << deviceInfo.OS_AVX             << std::endl;
    std::cout << "OS_AVX512         :" << deviceInfo.OS_AVX512          << std::endl;
    std::cout << "HW_MMX            :" << deviceInfo.HW_MMX             << std::endl;
    std::cout << "HW_x64            :" << deviceInfo.HW_x64             << std::endl;
    std::cout << "HW_ABM            :" << deviceInfo.HW_ABM             << std::endl;
    std::cout << "HW_RDRAND         :" << deviceInfo.HW_RDRAND          << std::endl;
    std::cout << "HW_BMI1           :" << deviceInfo.HW_BMI1            << std::endl;
    std::cout << "HW_BMI2           :" << deviceInfo.HW_BMI2            << std::endl;
    std::cout << "HW_ADX            :" << deviceInfo.HW_ADX             << std::endl;
    std::cout << "HW_PREFETCHWT1    :" << deviceInfo.HW_PREFETCHWT1     << std::endl;
    std::cout << "HW_MPX            :" << deviceInfo.HW_MPX             << std::endl;
    std::cout << "HW_SSE            :" << deviceInfo.HW_SSE             << std::endl;
    std::cout << "HW_SSE2           :" << deviceInfo.HW_SSE2            << std::endl;
    std::cout << "HW_SSE3           :" << deviceInfo.HW_SSE3            << std::endl;
    std::cout << "HW_SSSE3          :" << deviceInfo.HW_SSSE3           << std::endl;
    std::cout << "HW_SSE41          :" << deviceInfo.HW_SSE41           << std::endl;
    std::cout << "HW_SSE42          :" << deviceInfo.HW_SSE42           << std::endl;
    std::cout << "HW_SSE4a          :" << deviceInfo.HW_SSE4a           << std::endl;
    std::cout << "HW_AES            :" << deviceInfo.HW_AES             << std::endl;
    std::cout << "HW_SHA            :" << deviceInfo.HW_SHA             << std::endl;
    std::cout << "HW_AVX            :" << deviceInfo.HW_AVX             << std::endl;
    std::cout << "HW_XOP            :" << deviceInfo.HW_XOP             << std::endl;
    std::cout << "HW_FMA3           :" << deviceInfo.HW_FMA3            << std::endl;
    std::cout << "HW_FMA4           :" << deviceInfo.HW_FMA4            << std::endl;
    std::cout << "HW_AVX2           :" << deviceInfo.HW_AVX2            << std::endl;
    std::cout << "HW_AVX512_F       :" << deviceInfo.HW_AVX512_F        << std::endl;
    std::cout << "HW_AVX512_PF      :" << deviceInfo.HW_AVX512_PF       << std::endl;
    std::cout << "HW_AVX512_ER      :" << deviceInfo.HW_AVX512_ER       << std::endl;
    std::cout << "HW_AVX512_CD      :" << deviceInfo.HW_AVX512_CD       << std::endl;
    std::cout << "HW_AVX512_VL      :" << deviceInfo.HW_AVX512_VL       << std::endl;
    std::cout << "HW_AVX512_BW      :" << deviceInfo.HW_AVX512_BW       << std::endl;
    std::cout << "HW_AVX512_DQ      :" << deviceInfo.HW_AVX512_DQ       << std::endl;
    std::cout << "HW_AVX512_IFMA    :" << deviceInfo.HW_AVX512_IFMA     << std::endl;
    std::cout << "HW_AVX512_VBMI    :" << deviceInfo.HW_AVX512_VBMI     << std::endl;
    char dummy;
    std::cin >> dummy;
    return  0;
}

