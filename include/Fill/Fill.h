// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Fill.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the Fill entry point functions.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Base/Core.h"
#include "Base/Perf.h"

ULIS2_NAMESPACE_BEGIN
class FThreadPool;

/// @fn         void Fill( FThreadPool& iPool, FBlock* iDst, const FColor& iColor, const FPerf& iPerf = FPerf(), bool iCallInvalidCB = true )
/// @brief      Fill dst block with specified color.
/// @details    The dst block will be filled entirely with a solid color.
/// @param      iPool           The pool to process the image in.
/// @param      iDst            The block destination to fill.
/// @param      iColor          The color to fill.
/// @param      iPerf           The Performance Options for this operation, see \e FPerf.
/// @param      iCallInvalidCB  Whether or not the function should call the invalid call back in the backdrop block after the operation finished.
ULIS2_API void Fill( FThreadPool&   iPool
                   , FBlock*        iDst
                   , const IPixel&  iColor
                   , const FPerf&   iPerf           = FPerf()
                   , bool           iCallInvalidCB  = true );

/// @fn         void Fill( FThreadPool& iPool, FBlock* iDst, const FColor& iColor, const FRect& iRect, const FPerf& iPerf = FPerf(), bool iCallInvalidCB = true )
/// @brief      Fill dst block rect with specified color.
/// @details    The dst block will be filled in a rect with a solid color.
/// @param      iPool           The pool to process the image in.
/// @param      iDst            The block destination to fill.
/// @param      iColor          The color to fill.
/// @param      iPerf           The Performance Options for this operation, see \e FPerf.
/// @param      iCallInvalidCB  Whether or not the function should call the invalid call back in the backdrop block after the operation finished.
ULIS2_API void FillRect( FThreadPool&   iPool
                       , FBlock*        iDst
                       , const IPixel&  iColor
                       , const FRect&   iRect
                       , const FPerf&   iPerf           = FPerf()
                       , bool           iCallInvalidCB  = true );

ULIS2_NAMESPACE_END

