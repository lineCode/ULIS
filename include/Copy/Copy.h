// Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Copy.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the Copy entry point functions.
* @copyright    Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Base/Core.h"
#include "Maths/Geometry.h"
#include "Base/Perf.h"

ULIS2_NAMESPACE_BEGIN
/// @fn         void Copy( FThreadPool& iPool, const FBlock* iSrc, FBlock* iDst, const FPoint& iDstPos, const FPerf& iPerf = FPerf(), bool iCallInvalidCB = true )
/// @brief      Copy src block into dst block according to specified pos
/// @param      iPool           The pool to process the image in.
/// @param      iSrc            The sourc block to read;
/// @param      iDst            The destination block to write.
/// @param      iDstPos         The position in destination to write.
/// @param      iPerf           The Performance Options for this operation, see \e FPerf.
/// @param      iCallInvalidCB  Whether or not the function should call the invalid call back in the backdrop block after the operation finished.
ULIS2_API void Copy( FThreadPool&   iPool
                    , const FBlock* iSrc
                    , FBlock*       iDst
                    , const FPoint& iDstPos         = FPoint()
                    , const FPerf&  iPerf           = FPerf()
                    , bool          iCallInvalidCB  = true );

/// @fn         void CopyRect( FThreadPool& iPool, const FBlock* iSrc, FBlock* iDst, const FRect& iSrcRect, const FPoint& iDstPos, const FPerf& iPerf = FPerf(), bool iCallInvalidCB = true )
/// @brief      Copy src block into dst block according to specified pos
/// @param      iPool           The pool to process the image in.
/// @param      iSrc            The sourc block to read;
/// @param      iDst            The destination block to write.
/// @param      iSrcRect        The rect to copy in source.
/// @param      iDstPos         The position in destination to write.
/// @param      iPerf           The Performance Options for this operation, see \e FPerf.
/// @param      iCallInvalidCB  Whether or not the function should call the invalid call back in the backdrop block after the operation finished.
ULIS2_API void CopyRect( FThreadPool&  iPool
                       , const FBlock* iSrc
                       , FBlock*       iDst
                       , const FRect&  iSrcRect
                       , const FPoint& iDstPos         = FPoint()
                       , const FPerf&  iPerf           = FPerf()
                       , bool          iCallInvalidCB  = true );

/// @fn         void CopyRaw( const FBlock* iSrc, FBlock* iDst, bool iCallInvalidCB = true )
/// @brief      Perform a raw complete copy of src block into dst block, good for small blocks.
/// @param      iSrc            The source block to read;
/// @param      iDst            The destination block to write.
/// @param      iCallInvalidCB  Whether or not the function should call the invalid call back in the backdrop block after the operation finished.
ULIS2_API void CopyRaw( const FBlock* iSrc
                      , FBlock*       iDst
                      , bool          iCallInvalidCB  = true );

ULIS2_NAMESPACE_END

