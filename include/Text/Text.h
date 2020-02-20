// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Text.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the Text entry point functions.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Base/Core.h"
#include <glm/mat2x2.hpp>
#include <glm/vec2.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

ULIS2_NAMESPACE_BEGIN
/// @fn         void RenderText( FThreadPool* iPool, bool iBlocking, const FPerf& iPerf, const FCPU& iCPU, bool iAntialiasing, FBlock* iDst, const std::string& iText, const FFont& iFont, int iSize, const IPixel& iColor, const glm::mat2& iTransform, bool iCallInvalidCB )
/// @brief      Draw text in dst block with specified color size and transform.
/// @param      iPool           The pool to process the image in.
/// @param      iBlocking       Weither the MT process should wait for completion or not
/// @param      iPerf           The Performance Options for this operation, see \e FPerf.
/// @param      iCPU            The CPU info for this runtime environment, see \e FCPU.
/// @param      iAntialiasing   Wether the text should be rendered using antialiasing or not
/// @param      iDst            The block destination to fill.
/// @param      iText           The text to draw
/// @param      iFont           The font to use
/// @param      iSize           The text size
/// @param      iColor          The color to fill.
/// @param      iTransform      The text transform.
/// @param      iCallInvalidCB  Whether or not the function should call the invalid call back in the backdrop block after the operation finished.
ULIS2_API void RenderText( FThreadPool*         iPool
                         , bool                 iBlocking
                         , const FPerf&         iPerf
                         , const FCPU&          iCPU
                         , bool                 iAntialiasing
                         , FBlock*              iDst
                         , const std::string&   iText
                         , const FFont&         iFont
                         , int                  iSize
                         , const IPixel&        iColor
                         , const FTransform2D&  iTransform
                         , bool                 iCallInvalidCB );


/// @fn         FRect TextMetrics( const std::string& iText, const FFont& iFont, int iSize, const glm::mat2& iTransform )
/// @brief      Quickly precompute text metrics according to params for layout and placement.
/// @param      iText           The text to draw
/// @param      iFont           The font to use
/// @param      iSize           The text size
/// @param      iTransform      The text transform.
/// @return                     A rectangular area containing all the text.
ULIS2_API FRect TextMetrics( const std::string&     iText
                           , const FFont&           iFont
                           , int                    iSize
                           , const FTransform2D&    iTransform );

// Dispatch Typedefs ( implemented in dispatch.ipp but available from public API )
typedef void (*fpDispatchedTextFunc)( FThreadPool*, bool, const FPerf&, FBlock*, const std::string&, const FFont&, int, const tByte*, int, int, FT_Matrix& );
ULIS2_API fpDispatchedTextFunc QueryDispatchedTextFunctionForParameters( uint32 iFormat, bool iAntialiasing, const FPerf& iPerf, const FCPU& iCPU );

ULIS2_NAMESPACE_END

