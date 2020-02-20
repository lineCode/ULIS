// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Blend.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the Blend entry point functions.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Base/Core.h"
#include "Blend/BlendingPRNGSeed.h"
#include "Blend/Modes.h"
#include "Maths/Geometry.h"
#include <memory>

ULIS2_NAMESPACE_BEGIN
/// @fn         void Blend( FThreadPool* iPool, bool iBlocking, const FPerf& iPerf, const FCPU& iCPU, const FBlock* iSource, FBlock* iBackdrop, const glm::ivec2& DstPos, eBlendingMode iBlendingMode, eAlphaMode iAlphaMode, float iOpacity, bool iCallInvalidCB )
/// @brief      Blend two block together.
/// @details    The source block will be blended on the backdrop block, according to the specified parameters.
///             Warning ! Both blocks should be the same underlying format in order for the function to succeed, else the function will fail and crash.
/// @param      iPool           The pool to process the image in.
/// @param      iBlocking       Weither the MT process should wait for completion or not
/// @param      iPerf           The Performance Options for this operation, see \e FPerf.
/// @param      iCPU            The CPU info for this runtime environment, see \e FCPU.
/// @param      iSubpixel       Weither the blend process should use subpixel.
/// @param      iSource         The pointer to the source \e FBlock ( remains untouched ).
/// @param      iBackdrop       The pointer to the backdrop \e FBlock ( receives the blend ).
/// @param      iDstPos         The position in destination to write.
/// @param      iBlendingMode   The blending mode ( see \e eBlendingMode ).
/// @param      iAlphaMode      The alpha mode ( see \e eAlphaMode ).
/// @param      iOpacity        The opacity used to perform the blend, beetween 0.0f and 1.0f.
/// @param      iCallInvalidCB  Whether or not the function should call the invalid call back in the backdrop block after the operation finished.
ULIS2_API void Blend( FThreadPool*      iPool
                    , bool              iBlocking
                    , const FPerf&      iPerf
                    , const FCPU&       iCPU
                    , bool              iSubpixel
                    , const FBlock*     iSource
                    , FBlock*           iBackdrop
                    , float             iDstX
                    , float             iDstY
                    , eBlendingMode     iBlendingMode
                    , eAlphaMode        iAlphaMode
                    , float             iOpacity
                    , bool              iCallInvalidCB );

/// @fn         void BlendSubpixelRect( FThreadPool* iPool, bool iBlocking, const FPerf& iPerf, const FCPU& iCPU, const FBlock* iSource, FBlock* iBackdrop, const FRect& iSrcRect, const glm::vec2& iDstPos, eBlendingMode iBlendingMode, eAlphaMode iAlphaMode, float iOpacity, bool iCallInvalidCB )
/// @details    The source block will be blended on the backdrop block, according to the specified parameters.
///             Warning ! Both blocks should be the same underlying format in order for the function to succeed, else the function will fail and crash.
/// @param      iPool           The pool to process the image in
/// @param      iBlocking       Weither the MT process should wait for completion or not
/// @param      iPerf           The Performance Options for this operation, see \e FPerf.
/// @param      iCPU            The CPU info for this runtime environment, see \e FCPU.
/// @param      iSubpixel       Weither the blend process should use subpixel.
/// @param      iSource         The pointer to the source \e FBlock ( remains untouched ).
/// @param      iBackdrop       The pointer to the backdrop \e FBlock ( receives the blend ).
/// @param      iSrcRect        The area to blend in the back block.
/// @param      iDstPos         The position in destination to write.
/// @param      iBlendingMode   The blending mode ( see \e eBlendingMode ).
/// @param      iAlphaMode      The alpha mode ( see \e eAlphaMode ).
/// @param      iOpacity        The opacity used to perform the blend, beetween 0 and 1.
/// @param      iCallInvalidCB  Whether or not the function should call the invalid call back in the back block after the operation finished.
ULIS2_API void BlendRect( FThreadPool*      iPool
                        , bool              iBlocking
                        , const FPerf&      iPerf
                        , const FCPU&       iCPU
                        , bool              iSubpixel
                        , const FBlock*     iSource
                        , FBlock*           iBackdrop
                        , const FRect&      iSrcRect
                        , int32             iSrcShiftX
                        , int32             iSrcShiftY
                        , float             iDstX
                        , float             iDstY
                        , int32             iDstCoverageW
                        , int32             iDstCoverageH
                        , eBlendingMode     iBlendingMode
                        , eAlphaMode        iAlphaMode
                        , float             iOpacity
                        , bool              iCallInvalidCB );


ULIS2_API struct FBlendInfo {
    const FBlock*   source;
    FBlock*         backdrop;
    FRect           sourceRect;
    FVec2I          tilingTranslation;
    FVec2F          backdropPosition;
    FVec2I          backdropCoverage;
    bool            subpixelFlag;
    eBlendingMode   blendingMode;
    eAlphaMode      alphaMode;
    float           opacityValue;

    // Internal
    FRect           _backdropWorkingRect;
};

ULIS2_API void BlendRect( const FPerfParams&, const FBlendInfo& );

// Dispatch Typedefs ( implemented in dispatch.ipp but available from public API )
typedef void (*fpDispatchedBlendFunc)( const FFormatInfo& iFormatInfo, const FPerfParams& iPerfParams, std::shared_ptr< const FBlendInfo > iBlendParams );
ULIS2_API fpDispatchedBlendFunc QueryDispatchedBlendFunctionForParameters( const FFormatInfo& iFormatInfo, const FPerfParams& iPerfParams, const FBlendInfo& iBlendParams );

ULIS2_NAMESPACE_END

