// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS
*__________________
*
* @file         Device_Windows.ipp
* @author       Clement Berthaud
* @brief        This file provides the definition for the FDevice tools.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "System/Device.h"
#include "System/DeviceHelpers.h"

#include <Windows.h>
#include <intrin.h>
#include <stdint.h>
#include <string>
#include <thread>

ULIS_NAMESPACE_BEGIN

namespace detail {
void
cpuid(int32_t out[4], int32_t x)
{
    __cpuidex(out, x, 0);
}

__int64
xgetbv( unsigned int x )
{
    return  _xgetbv(x);
}

typedef BOOL (WINAPI *LPFN_ISWOW64PROCESS) (HANDLE, PBOOL);
BOOL IsWow64()
{
    BOOL bIsWow64 = FALSE;

    LPFN_ISWOW64PROCESS fnIsWow64Process = (LPFN_ISWOW64PROCESS) GetProcAddress(
        GetModuleHandle(TEXT("kernel32")), "IsWow64Process");

    if( NULL != fnIsWow64Process )
    {
        if( !fnIsWow64Process( GetCurrentProcess(), &bIsWow64 ) )
        {
            printf( "Error Detecting Operating System.\n" );
            printf( "Defaulting to 32-bit OS.\n\n" );
            bIsWow64 = FALSE;
        }
    }
    return  bIsWow64;
}

bool
detect_OS_x64() {
#ifdef _M_X64
    return  true;
#else
    return  IsWow64() != 0;
#endif
}

bool
detect_OS_AVX() {
    //  Copied from: http://stackoverflow.com/a/22521619/922184
    bool avxSupported = false;

    int cpuInfo[4];
    cpuid(cpuInfo, 1);

    bool osUsesXSAVE_XRSTORE = (cpuInfo[2] & (1 << 27)) != 0;
    bool cpuAVXSuport = (cpuInfo[2] & (1 << 28)) != 0;

    if (osUsesXSAVE_XRSTORE && cpuAVXSuport)
    {
        uint64_t xcrFeatureMask = xgetbv(_XCR_XFEATURE_ENABLED_MASK);
        avxSupported = (xcrFeatureMask & 0x6) == 0x6;
    }

    return  avxSupported;
}

bool
detect_OS_AVX512() {
    if (!detect_OS_AVX())
        return  false;

    uint64_t xcrFeatureMask = xgetbv(_XCR_XFEATURE_ENABLED_MASK);
    return  (xcrFeatureMask & 0xe6) == 0xe6;
}

std::string
get_vendor_string() {
    int32_t CPUInfo[4];
    char name[13];

    cpuid(CPUInfo, 0);
    memcpy(name + 0, &CPUInfo[1], 4);
    memcpy(name + 4, &CPUInfo[3], 4);
    memcpy(name + 8, &CPUInfo[2], 4);
    name[12] = '\0';

    return  name;
}

} // namespace detail


FDevice::FDevice()
    : bField( 0 )
    , mMaxWorkers( std::thread::hardware_concurrency() )
    , mL1CacheSize( 65536 )
    , mL1CacheLineSize( 64 )
{

    bField =
          ULIS_W_HW_AMD( 0 )
        | ULIS_W_HW_INTEL( 0 )
        | ULIS_W_OS_X64( 1 )
        | ULIS_W_OS_AVX( 0 )
        | ULIS_W_OS_AVX512( 0 )
        | ULIS_W_HW_X64( 1 )
        | ULIS_W_HW_MMX( 0 )
        | ULIS_W_HW_ABM( 0 )
        | ULIS_W_HW_RDRAND( 0 )
        | ULIS_W_HW_BMI1( 0 )
        | ULIS_W_HW_BMI2( 0 )
        | ULIS_W_HW_ADX( 0 )
        | ULIS_W_HW_PREFETCHWT1( 0 )
        | ULIS_W_HW_MPX( 0 )
        | ULIS_W_HW_SSE( 0 )
        | ULIS_W_HW_SSE2( 0 )
        | ULIS_W_HW_SSE3( 0 )
        | ULIS_W_HW_SSSE3( 0 )
        | ULIS_W_HW_SSE41( 0 )
        | ULIS_W_HW_SSE42( 0 )
        | ULIS_W_HW_SSE4A( 0 )
        | ULIS_W_HW_AES( 0 )
        | ULIS_W_HW_SHA( 0 )
        | ULIS_W_HW_AVX( 0 )
        | ULIS_W_HW_XOP( 0 )
        | ULIS_W_HW_FMA3( 0 )
        | ULIS_W_HW_FMA4( 0 )
        | ULIS_W_HW_AVX2( 0 )
        | ULIS_W_HW_AVX512_F( 0 )
        | ULIS_W_HW_AVX512_PF( 0 )
        | ULIS_W_HW_AVX512_ER( 0 )
        | ULIS_W_HW_AVX512_CD( 0 )
        | ULIS_W_HW_AVX512_VL( 0 )
        | ULIS_W_HW_AVX512_BW( 0 )
        | ULIS_W_HW_AVX512_DQ( 0 )
        | ULIS_W_HW_AVX512_IFMA( 0 )
        | ULIS_W_HW_AVX512_VBMI( 0 );
}

ULIS_NAMESPACE_END

