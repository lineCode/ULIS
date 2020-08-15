// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS
*__________________
*
* @file         Filter.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the Filter entry point functions.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"
#include <functional>

ULIS_NAMESPACE_BEGIN

typedef void (*fpFilterOPFunc)( const FRasterImage2D* iBlock, const uint8* iPtr );
typedef void (*fpFilterOPInPlaceFunc)( FRasterImage2D* iBlock, uint8* iPtr );
typedef void (*fpFilterOPInto)( const FRasterImage2D* iSrcBlock, const uint8* iSrcPtr, FRasterImage2D* iDstBlock, uint8* iDstPtr );

ULIS_API void Filter( FThreadPool*             iThreadPool
                     , bool                     iBlocking
                     , uint32                   iPerfIntent
                     , const FHostDeviceInfo&   iHostDeviceInfo
                     , bool                     iCallCB
                     , const FRasterImage2D*            iSource
                     , std::function< void( const FRasterImage2D* iBlock, const uint8* iPtr ) > iFunc );

ULIS_API void FilterInPlace( FThreadPool*              iThreadPool
                            , bool                      iBlocking
                            , uint32                    iPerfIntent
                            , const FHostDeviceInfo&    iHostDeviceInfo
                            , bool                      iCallCB
                            , FRasterImage2D*                   iSource
                            , std::function< void( FRasterImage2D* iBlock, uint8* iPtr ) > iFunc );

ULIS_API void FilterInto( FThreadPool*             iThreadPool
                         , bool                     iBlocking
                         , uint32                   iPerfIntent
                         , const FHostDeviceInfo&   iHostDeviceInfo
                         , bool                     iCallCB
                         , const FRasterImage2D*            iSource
                         , FRasterImage2D*                  iDestination
                         , std::function< void( const FRasterImage2D* iSrcBlock, const uint8* iSrcPtr, FRasterImage2D* iDstBlock, uint8* iDstPtr ) > iFunc );
ULIS_NAMESPACE_END

