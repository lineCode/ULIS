// Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Swap.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the Swap entry point functions.
* @copyright    Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core.h"
#include "Perf.h"

ULIS2_NAMESPACE_BEGIN
class FThreadPool;

/// @fn         void Swap( FThreadPool& iPool, FBlock* iDst, const FPerf& iPerf = FPerf(), bool iCallInvalidCB = true )
/// @brief      swap specified channels together in dst block.
/// @details    The dst block will see its channels swapped.
/// @param      iPool           The pool to process the image in.
/// @param      iDst            The block destination to swap channels.
/// @param      iPerf           The Performance Options for this operation, see \e FPerf.
/// @param      iCallInvalidCB  Whether or not the function should call the invalid call back in the backdrop block after the operation finished.
ULIS2_API void Swap( FThreadPool&  iPool
                    , FBlock*       iDst
                    , uint8         iC1
                    , uint8         iC2
                    , const FPerf&  iPerf           = FPerf()
                    , bool          iCallInvalidCB  = true );

ULIS2_NAMESPACE_END

