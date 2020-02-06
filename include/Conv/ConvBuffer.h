// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         ConvBuffer.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the ConvBuffer entry point functions.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Base/Core.h"

ULIS2_NAMESPACE_BEGIN

ULIS2_API void ConvBuffer( tFormat iSrcFormat, const tByte* iSrc, tSize iSrcBytes, tFormat iDstFormat, tByte* iDst, tSize iDstBytes );

ULIS2_NAMESPACE_END

/*
ULIS2_API void ProfileConvBuffer( FColorProfile* iSrcProfile, tFormat iSrcFormat, const tByte* iSrc, tSize iSrcBytes
                                , FColorProfile* iDstProfile, tFormat iDstFormat,       tByte* iDst, tSize iDstBytes, uint32 iIntent = 0 );
*/