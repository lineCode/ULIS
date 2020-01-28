// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Clear.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the Clear entry point functions.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Base/Core.h"

ULIS2_NAMESPACE_BEGIN
class FThreadPool;

/// @fn         void Clear( FThreadPool* iPool, bool iBlocking, const FPerf& iPerf, const FCPU& iCPU, bool iBlocking, const FPerf& iPerf, const FCPU& iCPU, FBlock* iDst, bool iCallInvalidCB )
/// @brief      Clear dst block with zero.
/// @details    The dst block will be clear entirely.
/// @param      iPool           The pool to process the image in.
/// @param      iBlocking       Weither the MT process should wait for completion or not
/// @param      iPerf           The Performance Options for this operation, see \e FPerf.
/// @param      iCPU            The CPU info for this runtime environment, see \e FCPU.
/// @param      iDst            The block destination to fill.
/// @param      iCallInvalidCB  Whether or not the function should call the invalid call back in the backdrop block after the operation finished.
ULIS2_API void Clear( FThreadPool*  iPool
                    , bool          iBlocking
                    , const FPerf&  iPerf
                    , const FCPU&   iCPU
                    , FBlock*       iDst
                    , bool          iCallInvalidCB );

/// @fn         void Clear( FThreadPool* iPool, bool iBlocking, const FPerf& iPerf, const FCPU& iCPU, bool iBlocking, const FPerf& iPerf, const FCPU& iCPU, FBlock* iDst, const FRect& iRect, bool iCallInvalidCB )
/// @brief      Clear dst block rect with zero.
/// @details    The dst block will be clear in a rect.
/// @param      iPool           The pool to process the image in.
/// @param      iBlocking       Weither the MT process should wait for completion or not
/// @param      iPerf           The Performance Options for this operation, see \e FPerf.
/// @param      iCPU            The CPU info for this runtime environment, see \e FCPU.
/// @param      iDst            The block destination to fill.
/// @param      iCallInvalidCB  Whether or not the function should call the invalid call back in the backdrop block after the operation finished.
ULIS2_API void ClearRect( FThreadPool*  iPool
                        , bool          iBlocking
                        , const FPerf&  iPerf
                        , const FCPU&   iCPU
                        , FBlock*       iDst
                        , const FRect&  iRect
                        , bool          iCallInvalidCB );

/// @fn         void ClearRaw( FBlock* iDst, bool iCallInvalidCB )
/// @brief      Perform a raw complete clear of dst block, good for small blocks.
/// @param      iSrc            The source block to clear;
/// @param      iCallInvalidCB  Whether or not the function should call the invalid call back in the backdrop block after the operation finished.
ULIS2_API void ClearRaw( FBlock*    iSrc
                       , bool       iCallInvalidCB );

ULIS2_NAMESPACE_END

