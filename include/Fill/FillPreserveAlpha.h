// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS3
*__________________
*
* @file         FillPreserveAlpha.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for FillPreserveAlpha Fill entry point functions.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"

ULIS_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
// FillPreserveAlpha
ULIS_API void FillPreserveAlpha( FThreadPool* iThreadPool
                                , bool iBlocking
                                , uint32 iPerfIntent
                                , const FHostDeviceInfo& iHostDeviceInfo
                                , bool iCallCB
                                , FRasterImage2D* iDestination
                                , const ISample& iColor
                                , const FRectI& iArea );

ULIS_NAMESPACE_END

