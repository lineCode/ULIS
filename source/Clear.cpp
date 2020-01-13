// Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Clear.cpp
* @author       Clement Berthaud
* @brief        This file provides the definitions for the Clear entry point functions.
* @copyright    Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include "Clear.h"
#include "Fill.h"
#include "Block.h"
#include "Geometry.h"

ULIS2_NAMESPACE_BEGIN
void Clear( FThreadPool&     iPool
          , FBlock*          iDst
          , const FPerf&     iPerf
          , bool             iCallInvalidCB )
{
    ClearRect( iPool, iDst, iDst->Rect(), iPerf, iCallInvalidCB );
}


void ClearRect( FThreadPool&     iPool
              , FBlock*          iDst
              , const FRect&     iRect
              , const FPerf&     iPerf
              , bool             iCallInvalidCB )
{
    FPixel clear( iDst->Format() );
    FillRect( iPool, iDst, clear, iRect, iPerf, iCallInvalidCB );
}

ULIS2_NAMESPACE_END

