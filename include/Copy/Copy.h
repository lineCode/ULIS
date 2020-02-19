// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Copy.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the Copy entry point functions.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Base/Core.h"
#include <glm/vec2.hpp>

ULIS2_NAMESPACE_BEGIN
/// @fn         void Copy( FThreadPool* iPool, bool iBlocking, const FPerf& iPerf, const FCPU& iCPU, const FBlock* iSrc, FBlock* iDst, const glm::uvec2& iDstPos, const FPerf& iPerf, bool iCallInvalidCB )
/// @brief      Copy src block into dst block according to specified pos
/// @param      iPool           The pool to process the image in.
/// @param      iBlocking       Weither the MT process should wait for completion or not
/// @param      iPerf           The Performance Options for this operation, see \e FPerf.
/// @param      iCPU            The CPU info for this runtime environment, see \e FCPU.
/// @param      iSrc            The sourc block to read;
/// @param      iDst            The destination block to write.
/// @param      iDstPos         The position in destination to write.
/// @param      iCallInvalidCB  Whether or not the function should call the invalid call back in the backdrop block after the operation finished.
ULIS2_API void Copy( FThreadPool*       iPool
                   , bool               iBlocking
                   , const FPerf&       iPerf
                   , const FCPU&        iCPU
                   , const FBlock*      iSrc
                   , FBlock*            iDst
                   , int                iDstX
                   , int                iDstY
                   , bool               iCallInvalidCB );

/// @fn         void CopyRect( FThreadPool* iPool, bool iBlocking, const FPerf& iPerf, const FCPU& iCPU, const FBlock* iSrc, FBlock* iDst, const FRect& iSrcRect, const FPoint& iDstPos, const FPerf& iPerf, bool iCallInvalidCB )
/// @brief      Copy src block into dst block according to specified pos
/// @param      iPool           The pool to process the image in.
/// @param      iBlocking       Weither the MT process should wait for completion or not
/// @param      iPerf           The Performance Options for this operation, see \e FPerf.
/// @param      iCPU            The CPU info for this runtime environment, see \e FCPU.
/// @param      iSrc            The sourc block to read;
/// @param      iDst            The destination block to write.
/// @param      iSrcRect        The rect to copy in source.
/// @param      iDstPos         The position in destination to write.
/// @param      iCallInvalidCB  Whether or not the function should call the invalid call back in the backdrop block after the operation finished.
ULIS2_API void CopyRect( FThreadPool*       iPool
                       , bool               iBlocking
                       , const FPerf&       iPerf
                       , const FCPU&        iCPU
                       , const FBlock*      iSrc
                       , FBlock*            iDst
                       , const FRect&       iSrcRect
                       , int                iDstX
                       , int                iDstY
                       , bool               iCallInvalidCB );

/// @fn         void CopyRaw( const FBlock* iSrc, FBlock* iDst, bool iCallInvalidCB = true )
/// @brief      Perform a raw complete copy of src block into dst block, good for small blocks.
/// @param      iSrc            The source block to read;
/// @param      iDst            The destination block to write.
/// @param      iCallInvalidCB  Whether or not the function should call the invalid call back in the backdrop block after the operation finished.
ULIS2_API void CopyRaw( const FBlock* iSrc
                      , FBlock*       iDst
                      , bool          iCallInvalidCB  = true );

ULIS2_NAMESPACE_END

