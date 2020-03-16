// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         TilePool.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the TilePool class.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"
#include "Maths/Geometry.h"
#include <vector>
#include <queue>
#include <list>
#include <forward_list>
#include <unordered_map>

ULIS2_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
/// FWorkingTileEntry
class FWorkTileEntry {
public:
    ~FWorkTileEntry();
    FWorkTileEntry( FBlock* iTile );

public:
    const std::vector< FBlock** >& Pointers() const;
    void RegisterPointer( FBlock** iPointer );
    void UnregisterPointer( FBlock** iPointer );
    void EmptyAndNullifyPointers();
    uint32 CRC32() const;

    mutable uint32                      mCachedCRC32;
    FBlock*                             mTile;
    std::vector< FBlock** >             mPointers;
};
/////////////////////////////////////////////////////
/// FTiledBlock
class ULIS2_API FTilePool
{
public:
    // Construction / Destruction
    virtual ~FTilePool();
    FTilePool( int iWidth
             , int iHeight
             , tFormat iFormat
             , FColorProfile* iProfile = nullptr );

private:
    // Private Data Members
    FVec2F          mTileSize;
    tFormat         mTileFormat;
    FColorProfile*  mTileColorProfile;
    FBlock*         mEmptyTile;

    std::forward_list< FBlock* > mJunkTiles;                // Where tiles are stored before deletion.
    std::forward_list< FBlock* > mDirtyTiles;               // Where tiles are stored after allocation / or scheduled for recycling.
    std::forward_list< FBlock* > mFreshTiles;               // Where tiles are stored for fast use, essentialy ready to use.
    std::unordered_map< uint32, FBlock* > mWorkTiles;       // Where tiles are stored for work and display in images.
};

ULIS2_NAMESPACE_END

