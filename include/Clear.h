// Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Clear.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the Clear entry point functions.
* @copyright    Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core.h"
#include "Perf.h"

ULIS2_NAMESPACE_BEGIN
class FThreadPool;

/// @fn         void Clear( FBlock* iDst, FThreadPool& iPool, const FPerf& iPerf = FPerf(), bool iCallInvalidCB = true )
/// @brief      Clear dst block with zero.
/// @details    The dst block will be clear entirely.
/// @param      iDst            The block destination to fill.
/// @param      iPool           The pool to process the image in.
/// @param      iPerf           The Performance Options for this operation, see \e FPerf.
/// @param      iCallInvalidCB  Whether or not the function should call the invalid call back in the backdrop block after the operation finished.
ULIS2_API void Clear( FBlock*       iDst
                    , FThreadPool&  iPool
                    , const FPerf&  iPerf           = FPerf()
                    , bool          iCallInvalidCB  = true );

/// @fn         void Clear( FBlock* iDst, const FRect& iRect, FThreadPool& iPool, const FPerf& iPerf = FPerf(), bool iCallInvalidCB = true )
/// @brief      Clear dst block rect with zero.
/// @details    The dst block will be clear in a rect.
/// @param      iDst            The block destination to fill.
/// @param      iPool           The pool to process the image in.
/// @param      iPerf           The Performance Options for this operation, see \e FPerf.
/// @param      iCallInvalidCB  Whether or not the function should call the invalid call back in the backdrop block after the operation finished.
ULIS2_API void ClearRect( FBlock*       iDst
                        , const FRect&  iRect
                        , FThreadPool&  iPool
                        , const FPerf&  iPerf           = FPerf()
                        , bool          iCallInvalidCB  = true );

ULIS2_NAMESPACE_END

