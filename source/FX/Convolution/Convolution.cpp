// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS
*__________________
*
* @file         Convolution.cpp
* @author       Clement Berthaud
* @brief        This file provides the definitions for the Convolution entry point functions.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include "FX/Convolution/Convolution.h"
//#include "FX/Convolution/KernelSSE.h"
#include "System/HostDeviceInfo.h"
#include "Conv/Conv.h"
#include "Image/RasterImage2D.h"
#include "Image/Pixel.h"
#include "Math/Geometry/Rectangle.h"
#include "Math/Geometry/Vector.h"
#include "Thread/ThreadPool.h"

ULIS_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
// Convolution
void
Convolution( FThreadPool*            iThreadPool
           , bool                    iBlocking
           , uint32                  iPerfIntent
           , const FHostDeviceInfo&  iHostDeviceInfo
           , bool                    iCallCB
           , FBlock*                 iDestination
           , const FKernel&          iKernel
           , const FRectI&            iArea
           , eExtrapolationMethod    iEdgeMode )
{
    // Assertions
    ULIS_ASSERT( iDestination,             "Bad source."                                           );
    ULIS_ASSERT( iThreadPool,              "Bad pool."                                             );
    ULIS_ASSERT( !iCallCB || iBlocking,    "Callback flag is specified on non-blocking operation." );

    // Fit region of interest
    FRectI roi = iArea & iDestination->Rect();

    // Check no-op
    if( roi.Area() <= 0 )
        return;

    // Invalid
    iDestination->Dirty( roi, iCallCB );
}

ULIS_NAMESPACE_END

