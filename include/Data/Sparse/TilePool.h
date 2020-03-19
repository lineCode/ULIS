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
#include <list>
#include <forward_list>
#include <unordered_map>
#include <chrono>
#include <vector>

ULIS2_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
/// FTiledBlock
template< uint8 _MICRO
        , uint8 _MACRO >
class ULIS2_API FTilePool
{
public:
    // Construction / Destruction
    virtual ~FTilePool();
    FTilePool( tFormat iFormat
             , FColorProfile* iProfile
             , uint64 iRAMUsageCapTarget
             , uint64 iSWAPUsageCapTarget
             , uint32 iDesiredPoolWorkers
             , uint32 iTimeOutMS );

public:
    // Public API
    const FVec2I&           TileSize() const;
    uint32                  EmptyHash() const;
    const FBlock*           EmptyTile() const;
    tFormat                 TileFormat() const;
    const FFormatInfo&      TileFormatInfo() const;
    const FColorProfile*    TileColorProfile() const;
    uint64                  CurrentRAMUsage() const;
    uint64                  CurrentSwapUsage() const;
    uint64                  RAMUsageCapTarget() const;
    uint64                  SWAPUsageCapTarget() const;
    uint64                  CurrentTotalMemoryUsage() const;
    void                    SetRAMUsageCapTarget( uint64 iValue );
    void                    SetSWAPUsageCapTarget( uint64 iValue );
    long long               TimeOutMS() const;
    void                    SetTimeOutMS( uint32 iValue );

    size_t  NumTilesScheduledForClear() const;
    size_t  NumFreshTilesAvailableForQuery() const;
    size_t  NumDirtyHashedTilesCurrentlyInUse() const;
    size_t  NumCorrectlyHashedTilesCurrentlyInUse() const;
    size_t  NumRegisteredTiledBlocks() const;

public:
    // Core API
    void Tick();
    void PurgeAllNow();
    void AllocateNow( uint32 iNum );
    void ClearNow( uint32 iNum );
    FTileElement* QueryFreshTile();

    FTiledBlock< _MICRO, _MACRO >* CreateNewTiledBlock();
    void RequestTiledBlockDeletion( FTiledBlock< _MICRO, _MACRO >* iBlock );

private:
    // Tiles Info
    int                         mPixelDim;
    FVec2I                      mTileSize;
    tFormat                     mTileFormat;
    FColorProfile*              mTileColorProfile;

    // Empty Tile Stored Only Once
    FBlock*                     mEmptyTile;
    uint32                      mEmptyHash;

    // Memory Info
    uint64                      mSWAPUsageCapTarget;
    uint64                      mRAMUsageCapTarget;
    uint64                      mCurrentRAMUSage;
    uint32                      mBytesPerTile;

    // Time Info
    std::chrono::milliseconds   mTimeOutMS;
    bool                        mTickForbidden;

    // Size Info
    uint32 mNumTilesScheduledForClear;
    uint32 mNumFreshTilesAvailableForQuery;

    // Storage Containers
    std::forward_list< FBlock* >                mTilesScheduledForClear_slist;
    std::forward_list< FBlock* >                mFreshTilesAvailableForQuery_slist;
    std::list< FTileElement* >                  mDirtyHashedTilesCurrentlyInUse_dlist;
    std::unordered_map< uint32, FTileElement* > mCorrectlyHashedTilesCurrentlyInUse_umap;

    std::vector< FTiledBlock< _MICRO, _MACRO >* > mRegisteredTiledBlocks;

    // Thread Work Items
    FThreadPool*        mThreadPool;
    FHostDeviceInfo*    mHost;
};

ULIS2_NAMESPACE_END

#include "TilePool.ipp"

