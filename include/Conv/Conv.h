// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Conv.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the Conv entry point functions.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Base/Core.h"
#include "Base/Perf.h"

ULIS2_NAMESPACE_BEGIN
ULIS2_API struct FConvInfo {
    const FBlock*   source;
    FBlock*         destination;
    FPerfInfo       perfInfo;
};

ULIS2_API struct FXConvInfo {
    const FBlock*   source;
    tFormat         destinationFormat;
    FPerfInfo       perfInfo;
};

//ULIS2_API void ProfileConv( const IPixel& iSrc, IPixel& iDst, const FProfileRegistry& iProfileRegistry, uint32 iIntent = 0 /* INTENT_PERCEPTUAL */ );
ULIS2_API void Conv( const IPixel& iSrc, IPixel& iDst );
ULIS2_API FPixelValue Conv( const IPixel& iSrc, tFormat iDst );

ULIS2_API void Conv( FThreadPool*   iPool
                   , bool           iBlocking
                   , const FPerf&   iPerf
                   , const FCPU&    iCPU
                   , const FBlock*  iSrc
                   , FBlock*        iDst
                   , bool           iCallInvalidCB );

ULIS2_API FBlock* XConv( FThreadPool*   iPool
                       , bool           iBlocking
                       , const FPerf&   iPerf
                       , const FCPU&    iCPU
                       , const FBlock*  iSrc
                       , tFormat        iDst );

ULIS2_API void Conv( const FConvInfo& );
ULIS2_API FBlock* XConv( const FXConvInfo& );

ULIS2_NAMESPACE_END

