// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Perf.cpp
* @author       Clement Berthaud
* @brief        This file provides the definition for the FPerf struct.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Base/Perf.h"

ULIS2_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
// FPerf
//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------- Construction
FPerf::FPerf( uint32 iFlags )
    : flags( iFlags )
{}


//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------ Getters
uint32
FPerf::Flags() const
{
    return  flags;
}

bool
FPerf::UseMT() const
{
    return  flags & UPERF_MT_BIT;
}


bool
FPerf::UseTSPEC() const
{
    return  flags & UPERF_TSPEC_BIT;
}


bool
FPerf::UseSSE4_2() const
{
    return  flags & UPERF_SSE4_2_BIT;
}


bool
FPerf::UseAVX2() const
{
    return  flags & UPERF_AVX2_BIT;
}


bool
FPerf::UseGPU() const
{
    return  flags & UPERF_GPU_BIT;
}

ULIS2_NAMESPACE_END

