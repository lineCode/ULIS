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
#include "System/Device.h"
#include "System/DeviceHelpers.h"

#if defined( ULIS_WIN )
#include "System/Device_Windows.ipp"
#elif defined( ULIS_MACOS )
#include "System/Device_macOS.ipp"
#elif defined( ULIS_LINUX )
#include "System/Device_Linux.ipp"
#else
#include "System/Device_Generic.ipp"
#endif

ULIS_NAMESPACE_BEGIN
bool    FDevice::IsHardwareAMD() const {            return  ULIS_R_HW_AMD(          bField ); }
bool    FDevice::IsHardwareIntel() const {          return  ULIS_R_HW_INTEL(        bField ); }
bool    FDevice::IsOSx64() const {                  return  ULIS_R_OS_X64(          bField ); }
bool    FDevice::HasOSAVX() const {                 return  ULIS_R_OS_AVX(          bField ); }
bool    FDevice::HasOSAVX512() const {              return  ULIS_R_OS_AVX512(       bField ); }
bool    FDevice::HasHardwarex64() const {           return  ULIS_R_HW_X64(          bField ); }
bool    FDevice::HasHardwareMMX() const {           return  ULIS_R_HW_MMX(          bField ); }
bool    FDevice::HasHardwareABM() const {           return  ULIS_R_HW_ABM(          bField ); }
bool    FDevice::HasHardwareRDRAND() const {        return  ULIS_R_HW_RDRAND(       bField ); }
bool    FDevice::HasHardwareBMI1() const {          return  ULIS_R_HW_BMI1(         bField ); }
bool    FDevice::HasHardwareBMI2() const {          return  ULIS_R_HW_BMI2(         bField ); }
bool    FDevice::HasHardwareADX() const {           return  ULIS_R_HW_ADX(          bField ); }
bool    FDevice::HasHardwarePREFETCHWT1() const {   return  ULIS_R_HW_PREFETCHWT1(  bField ); }
bool    FDevice::HasHardwareMPX() const {           return  ULIS_R_HW_MPX(          bField ); }
bool    FDevice::HasHardwareSSE() const {           return  ULIS_R_HW_SSE(          bField ); }
bool    FDevice::HasHardwareSSE2() const {          return  ULIS_R_HW_SSE2(         bField ); }
bool    FDevice::HasHardwareSSE3() const {          return  ULIS_R_HW_SSE3(         bField ); }
bool    FDevice::HasHardwareSSSE3() const {         return  ULIS_R_HW_SSSE3(        bField ); }
bool    FDevice::HasHardwareSSE41() const {         return  ULIS_R_HW_SSE41(        bField ); }
bool    FDevice::HasHardwareSSE42() const {         return  ULIS_R_HW_SSE42(        bField ); }
bool    FDevice::HasHardwareSSE4a() const {         return  ULIS_R_HW_SSE4A(        bField ); }
bool    FDevice::HasHardwareAES() const {           return  ULIS_R_HW_AES(          bField ); }
bool    FDevice::HasHardwareSHA() const {           return  ULIS_R_HW_SHA(          bField ); }
bool    FDevice::HasHardwareAVX() const {           return  ULIS_R_HW_AVX(          bField ); }
bool    FDevice::HasHardwareXOP() const {           return  ULIS_R_HW_XOP(          bField ); }
bool    FDevice::HasHardwareFMA3() const {          return  ULIS_R_HW_FMA3(         bField ); }
bool    FDevice::HasHardwareFMA4() const {          return  ULIS_R_HW_FMA4(         bField ); }
bool    FDevice::HasHardwareAVX2() const {          return  ULIS_R_HW_AVX2(         bField ); }
bool    FDevice::HasHardwareAVX512_F() const {      return  ULIS_R_HW_AVX512_F(     bField ); }
bool    FDevice::HasHardwareAVX512_PF() const {     return  ULIS_R_HW_AVX512_PF(    bField ); }
bool    FDevice::HasHardwareAVX512_ER() const {     return  ULIS_R_HW_AVX512_ER(    bField ); }
bool    FDevice::HasHardwareAVX512_CD() const {     return  ULIS_R_HW_AVX512_CD(    bField ); }
bool    FDevice::HasHardwareAVX512_VL() const {     return  ULIS_R_HW_AVX512_VL(    bField ); }
bool    FDevice::HasHardwareAVX512_BW() const {     return  ULIS_R_HW_AVX512_BW(    bField ); }
bool    FDevice::HasHardwareAVX512_DQ() const {     return  ULIS_R_HW_AVX512_DQ(    bField ); }
bool    FDevice::HasHardwareAVX512_IFMA() const {   return  ULIS_R_HW_AVX512_IFMA(  bField ); }
bool    FDevice::HasHardwareAVX512_VBMI() const {   return  ULIS_R_HW_AVX512_VBMI(  bField ); }
uint32  FDevice::MaxWorkers() const {               return  mMaxWorkers; }
uint32  FDevice::L1CacheSize() const {              return  mL1CacheSize; }
uint32  FDevice::L1CacheLineSize() const {          return  mL1CacheLineSize; }
ULIS_NAMESPACE_END

