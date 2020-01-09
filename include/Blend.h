// Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Blend.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the Blend entry point functions.
* @copyright    Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core.h"
#include "Perf.h"
#include "Modes.h"

ULIS2_NAMESPACE_BEGIN
/// @fn         void Blend( const FBlock* iSource, FBlock* iBackdrop, eBlendingMode iMode, int ix = 0, int iy = 0, float iOpacity = 1.f, const FPerf& iPerf = FPerf(), bool iCallInvalidCB = true )
/// @brief      Blend two block together.
/// @details    The source block will be blended on the backdrop block, according to the specified parameters.
///             Warning ! Both blocks should be the same underlying format in order for the function to succeed, else the function will fail and crash.
/// @param      iSource         The pointer to the source \e FBlock ( remains untouched ).
/// @param      iBackdrop       The pointer to the backdrop \e FBlock ( receives the blend ).
/// @param      iX              x coordinate of the position to blend in the back block.
/// @param      iY              y coordinate of the position to blend in the back block.
/// @param      iBlendingMode   The blending mode ( see \e eBlendingMode ).
/// @param      iAlphaMode      The alpha mode ( see \e eAlphaMode ).
/// @param      iOpacity        The opacity used to perform the blend, beetween 0.0f and 1.0f.
/// @param      iPerf           The Performance Options for this operation, see \e FPerf.
/// @param      iCallInvalidCB  Whether or not the function should call the invalid call back in the backdrop block after the operation finished.
ULIS2_API void Blend( const FBlock*     iSource
                    , FBlock*           iBackdrop
                    , int               iX = 0
                    , int               iY = 0
                    , eBlendingMode     iBlendingMode   = eBlendingMode::kNormal
                    , eAlphaMode        iAlphaMode      = eAlphaMode::kNormal
                    , float             iOpacity        = 1.f
                    , const FPerf&      iPerf           = FPerf()
                    , bool              iCallInvalidCB  = true );


/// @fn         void Blend( const FBlock* iSource, FBlock* iBackdrop, eBlendingMode iMode, const FRect& iArea, float iOpacity = 1.f, const FPerf& iPerf = FPerf(), bool iCallInvalidCB = true )
/// @details    The source block will be blended on the backdrop block, according to the specified parameters.
///             Warning ! Both blocks should be the same underlying format in order for the function to succeed, else the function will fail and crash.
/// @param      iSource         The pointer to the source \e FBlock ( remains untouched ).
/// @param      iBackdrop       The pointer to the backdrop \e FBlock ( receives the blend ).
/// @param      iRect           The area to blend in the back block.
/// @param      iBlendingMode   The blending mode ( see \e eBlendingMode ).
/// @param      iAlphaMode      The alpha mode ( see \e eAlphaMode ).
/// @param      iOpacity        The opacity used to perform the blend, beetween 0 and 1.
/// @param      iPerf           The Performance Options for this operation, see \e FPerf.
/// @param      iCallInvalidCB  Whether or not the function should call the invalid call back in the back block after the operation finished.
ULIS2_API void Blend( FBlock*           iSource
                    , FBlock*           iBackdrop
                    , const FRect&      iRect
                    , eBlendingMode     iBlendingMode   = eBlendingMode::kNormal
                    , eAlphaMode        iAlphaMode      = eAlphaMode::kNormal
                    , float             iOpacity        = 1.f
                    , const FPerf&      iPerf           = FPerf()
                    , bool              iCallInvalidCB  = true );

ULIS2_NAMESPACE_END

