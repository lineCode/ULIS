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

ULIS2_NAMESPACE_BEGIN
/// @fn         void ProfileConv( const IPixel& iSrc, IPixel& iDst, const FProfileRegistry& iProfileRegistry, uint32 iIntent = INTENT_PERCEPTUAL )
/// @brief      Conv a pixel from source to destination with color space and intent.
/// @param      iSrc                A const reference to the source Pixel.
/// @param      iDst                A reference to the destination Pixel.
/// @param      iProfileRegistry    A reference to the profile registry used as backup if input pixels do not have profiles associated with them.
/// @param      iIntent             The profile conversion intent.
ULIS2_API void ProfileConv( const IPixel& iSrc, IPixel& iDst, const FProfileRegistry& iProfileRegistry, uint32 iIntent = 0 /* INTENT_PERCEPTUAL */ );

/// @fn         void Conv( const IPixel& iSrc, IPixel& iDst )
/// @brief      Conv a pixel from source to destination with basic model conversion.
/// @param      iSrc                A const reference to the source Pixel.
/// @param      iDst                A reference to the destination Pixel.
ULIS2_API void Conv( const IPixel& iSrc, IPixel& iDst );

/// @fn         void Conv( const IPixel& iSrc, tFormat iDst )
/// @brief      Create a converted a pixel from source to destination format.
/// @param      iSrc                A const reference to the source Pixel.
/// @param      iDst                The destination format.
/// @return                         A new FPixelValue object with converted data.
ULIS2_API FPixelValue Conv( const IPixel& iSrc, tFormat iDst );


/// @fn         void Conv( FThreadPool* iPool, bool iBlocking, const FPerf& iPerf, const FCPU& iCPU, const FBlock* iSrc, FBlock* iDst, bool iCallInvalidCB )
/// @brief      Convert from source to destination
/// @details    The blocks must match in size.
/// @param      iPool           The pool to process the image in.
/// @param      iBlocking       Weither the MT process should wait for completion or not
/// @param      iPerf           The Performance Options for this operation, see \e FPerf.
/// @param      iCPU            The CPU info for this runtime environment, see \e FCPU.
/// @param      iSrc            The block source to convert.
/// @param      iDst            The block destination to write.
/// @param      iCallInvalidCB  Whether or not the function should call the invalid call back in the backdrop block after the operation finished.
ULIS2_API void Conv( FThreadPool*   iPool
                   , bool           iBlocking
                   , const FPerf&   iPerf
                   , const FCPU&    iCPU
                   , const FBlock*  iSrc
                   , FBlock*        iDst
                   , bool           iCallInvalidCB );

/// @fn         void XConv( FThreadPool* iPool, bool iBlocking, const FPerf& iPerf, const FCPU& iCPU, const FBlock* iSrc, tFormat iDst )
/// @brief      Convert from source to destination format. The X calling convention means a block is allocated and the called is responsible for dealloc.
/// @details    The result block will match in size.
/// @param      iPool           The pool to process the image in.
/// @param      iBlocking       Weither the MT process should wait for completion or not
/// @param      iPerf           The Performance Options for this operation, see \e FPerf.
/// @param      iCPU            The CPU info for this runtime environment, see \e FCPU.
/// @param      iSrc            The block source to convert.
/// @param      iDst            The destination format to create.
/// @param      iCallInvalidCB  Whether or not the function should call the invalid call back in the backdrop block after the operation finished.
/// @return                     A newly allocated block holding the result conversion.
ULIS2_API FBlock* XConv( FThreadPool*   iPool
                       , bool           iBlocking
                       , const FPerf&   iPerf
                       , const FCPU&    iCPU
                       , const FBlock*  iSrc
                       , tFormat        iDst );

ULIS2_NAMESPACE_END

