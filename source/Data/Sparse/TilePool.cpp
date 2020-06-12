// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS3
*__________________
*
* @file         TilePool.cpp
* @author       Clement Berthaud
* @brief        This file provides the definition for the TilePool class.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Data/Sparse/TilePool.h"
#include "Data/Sparse/TilePool_Private.h"

ULIS3_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
/// TTilePool
//static
ITilePool*
ITilePool::XCreateTilePool( tFormat iFormat, FColorProfile* iProfile, eMicro iMicro, eMacro iMacro ) {
    return  new  TTilePool< 1, 5 >( iFormat, iProfile );
    return  nullptr;
}

//static
void
ITilePool::XDeleteTilePool( ITilePool* iTilePool ) {
    delete  iTilePool;
}
ULIS3_NAMESPACE_END
