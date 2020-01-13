// Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Fill.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the Fill entry point functions.
* @copyright    Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core.h"
#include "Perf.h"

ULIS2_NAMESPACE_BEGIN
class FThreadPool;

/// @fn         void Fill( FBlock* iDst, const FColor& iColor, FThreadPool& iPool, const FPerf& iPerf = FPerf(), bool iCallInvalidCB = true )
/// @brief      Fill dst block with specified color.
/// @details    The dst block will be filled entirely with a solid color.
/// @param      iDst            The block destination to fill.
/// @param      iColor          The color to fill.
/// @param      iPool           The pool to process the image in.
/// @param      iPerf           The Performance Options for this operation, see \e FPerf.
/// @param      iCallInvalidCB  Whether or not the function should call the invalid call back in the backdrop block after the operation finished.
ULIS2_API void Fill( FBlock*        iDst
                   , const IPixel&  iColor
                   , FThreadPool&   iPool
                   , const FPerf&   iPerf           = FPerf()
                   , bool           iCallInvalidCB  = true );

/// @fn         void Fill( FBlock* iDst, const FColor& iColor, const FRect& iRect, FThreadPool& iPool, const FPerf& iPerf = FPerf(), bool iCallInvalidCB = true )
/// @brief      Fill dst block rect with specified color.
/// @details    The dst block will be filled in a rect with a solid color.
/// @param      iDst            The block destination to fill.
/// @param      iColor          The color to fill.
/// @param      iPool           The pool to process the image in.
/// @param      iPerf           The Performance Options for this operation, see \e FPerf.
/// @param      iCallInvalidCB  Whether or not the function should call the invalid call back in the backdrop block after the operation finished.
ULIS2_API void FillRect( FBlock*        iDst
                       , const IPixel&  iColor
                       , const FRect&   iRect
                       , FThreadPool&   iPool
                       , const FPerf&   iPerf           = FPerf()
                       , bool           iCallInvalidCB  = true );

ULIS2_NAMESPACE_END

