// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS3
*__________________
*
* @file         Device.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the FDevice tools.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"

ULIS_NAMESPACE_BEGIN
class ULIS_API FDevice
{
public:
    /*! Constructor. */
    FDevice();

public:
    bool IsHardwareAMD() const;
    bool IsHardwareIntel() const;
    bool IsOSx64() const;
    bool HasOSAVX() const;
    bool HasOSAVX512() const;
    bool HasHardwarex64() const;
    bool HasHardwareMMX() const;
    bool HasHardwareABM() const;
    bool HasHardwareRDRAND() const;
    bool HasHardwareBMI1() const;
    bool HasHardwareBMI2() const;
    bool HasHardwareADX() const;
    bool HasHardwarePREFETCHWT1() const;
    bool HasHardwareMPX() const;
    bool HasHardwareSSE() const;
    bool HasHardwareSSE2() const;
    bool HasHardwareSSE3() const;
    bool HasHardwareSSSE3() const;
    bool HasHardwareSSE41() const;
    bool HasHardwareSSE42() const;
    bool HasHardwareSSE4a() const;
    bool HasHardwareAES() const;
    bool HasHardwareSHA() const;
    bool HasHardwareAVX() const;
    bool HasHardwareXOP() const;
    bool HasHardwareFMA3() const;
    bool HasHardwareFMA4() const;
    bool HasHardwareAVX2() const;
    bool HasHardwareAVX512_F() const;
    bool HasHardwareAVX512_PF() const;
    bool HasHardwareAVX512_ER() const;
    bool HasHardwareAVX512_CD() const;
    bool HasHardwareAVX512_VL() const;
    bool HasHardwareAVX512_BW() const;
    bool HasHardwareAVX512_DQ() const;
    bool HasHardwareAVX512_IFMA() const;
    bool HasHardwareAVX512_VBMI() const;
    uint32 MaxWorkers() const;
    uint32 L1CacheSize() const;
    uint32 L1CacheLineSize() const;

private:
    uint64 bField;
    uint32 mMaxWorkers;
    uint32 mL1CacheSize;
    uint32 mL1CacheLineSize;
};

ULIS_NAMESPACE_END

