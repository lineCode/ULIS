// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         TilePool.ippp
* @author       Clement Berthaud
* @brief        This file provides the definition for the TilePool class.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Data/Sparse/TilePool.h"
#include "Data/Sparse/Tile.h"
#include "Base/HostDeviceInfo.h"
#include "Data/Block.h"
#include "Thread/ThreadPool.h"
#include "Clear/Clear.h"
#include <thread>
#include <algorithm>

ULIS2_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
/// FTilePool
//--------------------------------------------------------------------------------------
//----------------------------------------------------------- Construction / Destruction
template< uint8 _MICRO, uint8 _MACRO > FTilePool< _MICRO, _MACRO >::~FTilePool() {
    PurgeAllNow();
    mThreadPool->WaitForCompletion();
    delete  mThreadPool;
    delete  mHost;
    delete  mEmptyTile;
}

template< uint8 _MICRO, uint8 _MACRO > FTilePool< _MICRO, _MACRO >::FTilePool( tFormat iFormat
                                                                             , FColorProfile* iProfile
                                                                             , uint64 iRAMUsageCapTarget
                                                                             , uint64 iSWAPUsageCapTarget
                                                                             , uint32 iDesiredPoolWorkers
                                                                             , uint32 iTimeOutMS )
    : mPixelDim                                 ( pow( 2, _MICRO )      )
    , mTileSize                                 ( mPixelDim, mPixelDim  )
    , mTileFormat                               ( iFormat               )
    , mEmptyTile                                ( nullptr               )
    , mEmptyHash                                ( 0                     )
    , mSWAPUsageCapTarget                       ( iSWAPUsageCapTarget   )
    , mRAMUsageCapTarget                        ( iRAMUsageCapTarget    )
    , mTileColorProfile                         ( iProfile              )
    , mTilesScheduledForClear_slist             ()
    , mFreshTilesAvailableForQuery_slist        ()
    , mDirtyHashedTilesCurrentlyInUse_dlist     ()
    , mCorrectlyHashedTilesCurrentlyInUse_umap  ()
    , mThreadPool                               ( nullptr               )
    , mHost                                     ( nullptr               )
    , mTimeOutMS                                ( iTimeOutMS            )
    , mBytesPerTile                                      ( 0                     )
    , mCurrentRAMUSage                          ( 0                     )
    , mTickForbidden                            ( false                 )
    , mNumTilesScheduledForClear                ( 0                     )
    , mNumFreshTilesAvailableForQuery           ( 0                     )
{
    mThreadPool = new FThreadPool( iDesiredPoolWorkers );
    mHost = new FHostDeviceInfo( FHostDeviceInfo::Detect() );

    mEmptyTile = new FBlock( mPixelDim, mPixelDim, iFormat, iProfile );
    ClearRaw( mEmptyTile, ULIS2_NOCB );
    mEmptyHash = mEmptyTile->CRC32();
    mBytesPerTile = mEmptyTile->BytesTotal();
}

//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------- Public API
template< uint8 _MICRO, uint8 _MACRO > const FVec2I&        FTilePool< _MICRO, _MACRO >::TileSize()                                 const   { return  mTileSize;                                        }
template< uint8 _MICRO, uint8 _MACRO > uint32               FTilePool< _MICRO, _MACRO >::EmptyHash()                                const   { return  mEmptyHash;                                       }
template< uint8 _MICRO, uint8 _MACRO > const FBlock*        FTilePool< _MICRO, _MACRO >::EmptyTile()                                const   { return  mEmptyTile;                                       }
template< uint8 _MICRO, uint8 _MACRO > tFormat              FTilePool< _MICRO, _MACRO >::TileFormat()                               const   { return  mTileFormat;                                      }
template< uint8 _MICRO, uint8 _MACRO > const FFormatInfo&   FTilePool< _MICRO, _MACRO >::TileFormatInfo()                           const   { return  mEmptyTile->FormatInfo();                         }
template< uint8 _MICRO, uint8 _MACRO > const FColorProfile* FTilePool< _MICRO, _MACRO >::TileColorProfile()                         const   { return  mTileColorProfile;                                }
template< uint8 _MICRO, uint8 _MACRO > uint64               FTilePool< _MICRO, _MACRO >::CurrentRAMUsage()                          const   { return  mCurrentRAMUSage;                                 }
template< uint8 _MICRO, uint8 _MACRO > uint64               FTilePool< _MICRO, _MACRO >::CurrentSwapUsage()                         const   { return  0;                                                }
template< uint8 _MICRO, uint8 _MACRO > uint64               FTilePool< _MICRO, _MACRO >::RAMUsageCapTarget()                        const   { return  mRAMUsageCapTarget;                               }
template< uint8 _MICRO, uint8 _MACRO > uint64               FTilePool< _MICRO, _MACRO >::SWAPUsageCapTarget()                       const   { return  mSWAPUsageCapTarget;                              }
template< uint8 _MICRO, uint8 _MACRO > uint64               FTilePool< _MICRO, _MACRO >::CurrentTotalMemoryUsage()                  const   { return  mCurrentRAMUSage;                                 }
template< uint8 _MICRO, uint8 _MACRO > long long            FTilePool< _MICRO, _MACRO >::TimeOutMS()                                const   { return  mTimeOutMS.count();                               }
template< uint8 _MICRO, uint8 _MACRO > void                 FTilePool< _MICRO, _MACRO >::SetRAMUsageCapTarget( uint64 iValue )              { mRAMUsageCapTarget  = iValue;                             }
template< uint8 _MICRO, uint8 _MACRO > void                 FTilePool< _MICRO, _MACRO >::SetSWAPUsageCapTarget( uint64 iValue )             { mSWAPUsageCapTarget = iValue;                             }
template< uint8 _MICRO, uint8 _MACRO > void                 FTilePool< _MICRO, _MACRO >::SetTimeOutMS( uint32 iValue )                      { mTimeOutMS = std::chrono::milliseconds( iValue );         }
template< uint8 _MICRO, uint8 _MACRO > size_t               FTilePool< _MICRO, _MACRO >::NumTilesScheduledForClear()                const   { return  mNumTilesScheduledForClear;                       }
template< uint8 _MICRO, uint8 _MACRO > size_t               FTilePool< _MICRO, _MACRO >::NumFreshTilesAvailableForQuery()           const   { return  mNumFreshTilesAvailableForQuery;                  }
template< uint8 _MICRO, uint8 _MACRO > size_t               FTilePool< _MICRO, _MACRO >::NumDirtyHashedTilesCurrentlyInUse()        const   { return  mDirtyHashedTilesCurrentlyInUse_dlist.size();     }
template< uint8 _MICRO, uint8 _MACRO > size_t               FTilePool< _MICRO, _MACRO >::NumCorrectlyHashedTilesCurrentlyInUse()    const   { return  mCorrectlyHashedTilesCurrentlyInUse_umap.size();  }
template< uint8 _MICRO, uint8 _MACRO > size_t               FTilePool< _MICRO, _MACRO >::NumRegisteredTiledBlocks()                 const   { return  mRegisteredTiledBlocks.size();                    }
//----------------------------------------------------------------------------- Core API
template< uint8 _MICRO, uint8 _MACRO >
void
FTilePool< _MICRO, _MACRO >::Tick() {
    if( mTickForbidden )
        return;

    int     num_task = 4;
    auto    micro_delta = mTimeOutMS / num_task;
    auto    span_del1   = micro_delta * 1;
    auto    span_del2   = micro_delta * 2;
    auto    span_new    = micro_delta * 3;
    auto    span_clear  = micro_delta * 4;
    std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();

    { // Del
        while( !( mTilesScheduledForClear_slist.empty() ) ) {
            if( mCurrentRAMUSage > mRAMUsageCapTarget ) {
                auto ptr = mTilesScheduledForClear_slist.front();
                mTilesScheduledForClear_slist.pop_front();
                --mNumTilesScheduledForClear;
                delete  ptr;
                mCurrentRAMUSage -= mBytesPerTile;
            }

            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>( std::chrono::steady_clock::now() - start_time );
            if( elapsed > span_del1 )
                break;
        }

        while( !( mFreshTilesAvailableForQuery_slist.empty() ) ) {
            if( mCurrentRAMUSage > mRAMUsageCapTarget ) {
                auto ptr = mFreshTilesAvailableForQuery_slist.front();
                mFreshTilesAvailableForQuery_slist.pop_front();
                --mNumFreshTilesAvailableForQuery;
                delete  ptr;
                mCurrentRAMUSage -= mBytesPerTile;
            }

            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>( std::chrono::steady_clock::now() - start_time );
            if( elapsed > span_del2 )
                break;
        }
    }

    { // Alloc
        while( true ) {
            if( mCurrentRAMUSage < mRAMUsageCapTarget ) {
                mTilesScheduledForClear_slist.emplace_front( new FBlock( mTileSize.x, mTileSize.y, mTileFormat, mTileColorProfile ) );
                ++mNumTilesScheduledForClear;
                mCurrentRAMUSage += mBytesPerTile;
            }

            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>( std::chrono::steady_clock::now() - start_time );
            if( elapsed > span_new )
                break;
        }
    }

    { // Clear
        while( !( mTilesScheduledForClear_slist.empty() ) ) {
            auto ptr = mTilesScheduledForClear_slist.front();
            mTilesScheduledForClear_slist.pop_front();
            --mNumTilesScheduledForClear;
            Clear( mThreadPool, ULIS2_BLOCKING, 0, *mHost, ULIS2_NOCB, ptr, ptr->Rect() );

            mFreshTilesAvailableForQuery_slist.emplace_front( ptr );
            ++mNumFreshTilesAvailableForQuery;
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>( std::chrono::steady_clock::now() - start_time );
            if( elapsed > span_clear )
                break;
        }
    }
}


template< uint8 _MICRO, uint8 _MACRO >
void
FTilePool< _MICRO, _MACRO >::PurgeAllNow() {
    mTickForbidden = true;
    // Purge Scheduled For Clear
    for( auto it : mTilesScheduledForClear_slist            ) delete it;
    for( auto it : mFreshTilesAvailableForQuery_slist       ) delete it;

    for( auto it : mDirtyHashedTilesCurrentlyInUse_dlist    ) {
        delete it->mBlock;
        delete it;
    }

    for( auto it : mCorrectlyHashedTilesCurrentlyInUse_umap ) {
        delete it.second->mBlock;
        delete it.second;
    }

    for( auto it : mRegisteredTiledBlocks ) {
        delete it;
    }

    mTilesScheduledForClear_slist.clear();
    mFreshTilesAvailableForQuery_slist.clear();
    mDirtyHashedTilesCurrentlyInUse_dlist.clear();
    mCorrectlyHashedTilesCurrentlyInUse_umap.clear();
    mRegisteredTiledBlocks.clear();
    mCurrentRAMUSage = 0;
    SetRAMUsageCapTarget( 0 );
    SetSWAPUsageCapTarget( 0 );
    mNumTilesScheduledForClear = 0;
    mNumFreshTilesAvailableForQuery = 0;
    mTickForbidden = false;
}

template< uint8 _MICRO, uint8 _MACRO >
void
FTilePool< _MICRO, _MACRO >::AllocateNow( uint32 iNum ) {
    mTickForbidden = true;
    for( uint32 i = 0; i < iNum; ++i ) {
        mTilesScheduledForClear_slist.emplace_front( new FBlock( mTileSize.x, mTileSize.y, mTileFormat, mTileColorProfile ) );
        ++mNumTilesScheduledForClear;
        mCurrentRAMUSage += mBytesPerTile;
    }
    mTickForbidden = false;
}

template< uint8 _MICRO, uint8 _MACRO >
void
FTilePool< _MICRO, _MACRO >::ClearNow( uint32 iNum ) {
    mTickForbidden = true;

    if( iNum > mNumTilesScheduledForClear )
        AllocateNow( iNum - mNumTilesScheduledForClear + 1 );

    for( uint32 i = 0; i < iNum; ++i ) {
        auto ptr = mTilesScheduledForClear_slist.front();
        mTilesScheduledForClear_slist.pop_front();
        --mNumTilesScheduledForClear;
        Clear( mThreadPool, ULIS2_BLOCKING, 0, *mHost, ULIS2_NOCB, ptr, ptr->Rect() );
        mFreshTilesAvailableForQuery_slist.emplace_front( ptr );
        ++mNumFreshTilesAvailableForQuery;
    }

    mTickForbidden = false;
}

template< uint8 _MICRO, uint8 _MACRO >
FTileElement*
FTilePool< _MICRO, _MACRO >::QueryFreshTile() {
    mTickForbidden = true;
    if( !mNumFreshTilesAvailableForQuery )
        ClearNow( 1 );
    auto ptr = mTilesScheduledForClear_slist.front();
    mTilesScheduledForClear_slist.pop_front();
    --mNumTilesScheduledForClear;
    FTileElement* te = new FTileElement( ptr, 1 );
    mDirtyHashedTilesCurrentlyInUse_dlist.push_back( te );
    mTickForbidden = false;
    return  te;
}

template< uint8 _MICRO, uint8 _MACRO >
FTiledBlock< _MICRO, _MACRO >*
FTilePool< _MICRO, _MACRO >::CreateNewTiledBlock() {
    mRegisteredTiledBlocks.emplace_back( new FTiledBlock< _MICRO, _MACRO >( this ) );
    return  mRegisteredTiledBlocks.back();
}

template< uint8 _MICRO, uint8 _MACRO >
void
FTilePool< _MICRO, _MACRO >::RequestTiledBlockDeletion( FTiledBlock< _MICRO, _MACRO >* iBlock ) {
    auto it = std::find( mRegisteredTiledBlocks.begin(), mRegisteredTiledBlocks.end(), iBlock );
    if( it != mRegisteredTiledBlocks.end() )
        mRegisteredTiledBlocks.erase( it );
}

ULIS2_NAMESPACE_END

