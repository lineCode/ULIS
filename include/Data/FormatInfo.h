// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         FormatInfo.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the FormatInfo utilities.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Base/Core.h"

ULIS2_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
/// @class      FFormatInfo
struct ULIS2_API FFormatInfo
{
    ~FFormatInfo();
    FFormatInfo( tFormat iFMT );
    tFormat FMT;
    uint8   BPC;
    uint8   NCC;
    uint8   HEA;
    uint8   COD;
    uint8   SPP;
    uint8   BPP;
    uint8*  IDT;
    uint8   AID;
};

ULIS2_NAMESPACE_END

