// Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Blend.cpp
* @author       Clement Berthaud
* @brief        This file provides the definitions for the Blend entry point functions.
* @copyright    Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include "Blend.h"

ULIS2_NAMESPACE_BEGIN
void Blend( const FBlock*   iSource
           , FBlock*        iBackdrop
           , int            iX
           , int            iY
           , eBlendingMode  iBlendingMode
           , eAlphaMode     iAlphaMode
           , float          iOpacity
           , const FPerf&   iPerf
           , bool           iCallInvalidCB )
{
}


void Blend( FBlock*         iSource
          , FBlock*         iBackdrop
          , const FRect&    iArea
          , eBlendingMode   iBlendingMode
          , eAlphaMode      iAlphaMode
          , float           iOpacity
          , const FPerf&    iPerf
          , bool            iCallInvalidCB )
{
}


ULIS2_NAMESPACE_END

