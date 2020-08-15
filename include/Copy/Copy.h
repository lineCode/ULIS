// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS
*__________________
*
* @file         Copy.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the Copy entry point functions.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"

ULIS_NAMESPACE_BEGIN

ULIS_API void Copy( FThreadPool*           iThreadPool
                   , bool                   iBlocking
                   , uint32                 iPerfIntent
                   , const FHostDeviceInfo& iHostDeviceInfo
                   , bool                   iCallCB
                   , const FRasterImage2D*          iSource
                   , FRasterImage2D*                iDestination
                   , const FRectI&           iArea
                   , const FVec2I&          iPos );

ULIS_API FRasterImage2D* XCopy( FThreadPool*           iThreadPool
                       , bool                   iBlocking
                       , uint32                 iPerfIntent
                       , const FHostDeviceInfo& iHostDeviceInfo
                       , bool                   iCallCB
                       , const FRasterImage2D*          iSource
                       , const FRectI&           iArea );

ULIS_API void CopyRaw( const FRasterImage2D* iSrc, FRasterImage2D* iDst, bool iCallCB );
ULIS_API FRasterImage2D* XCopyRaw( const FRasterImage2D* iSrc, bool iCallCB );

ULIS_NAMESPACE_END

