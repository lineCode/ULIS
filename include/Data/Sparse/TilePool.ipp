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
#include "Base/HostDeviceInfo.h"
#include "Clear/Clear.h"
#include "Data/Block.h"
#include "Data/Sparse/Tile.h"
#include "Thread/ThreadPool.h"

#include <algorithm>
#include <thread>

ULIS2_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
/// TTilePool
//--------------------------------------------------------------------------------------
//----------------------------------------------------------- Construction / Destruction
template< uint8 _MICRO, uint8 _MACRO > TTilePool< _MICRO, _MACRO >::~TTilePool() {
    bRequestWorkersTerminationAtomic.store( true );
    mThreadDeallocatorAllocatorCleanerBackgroundWorker->join();
    mThreadHasherGarbageCollectorBackgroundWorker->join();
    delete  mThreadDeallocatorAllocatorCleanerBackgroundWorker;
    delete  mThreadHasherGarbageCollectorBackgroundWorker;

    mThreadPool->WaitForCompletion();
    PurgeAllNow();

    delete  mThreadPool;
    delete  mHost;
    delete  mEmptyTile;
}

template< uint8 _MICRO, uint8 _MACRO > TTilePool< _MICRO, _MACRO >::TTilePool( tFormat        iFormat
                               , FColorProfile* iProfile )
    : mTileSize                                             ( scPixelDim, scPixelDim                                                                                        )
    , mTileFormat                                           ( iFormat                                                                                                       )
    , mTileColorProfile                                     ( iProfile                                                                                                      )
    , mEmptyTile                                            ( new FBlock( mTileSize.x, mTileSize.y, mTileFormat, mTileColorProfile )                                        )
    , mThreadPool                                           ( new FThreadPool( FThreadPool::MaxWorkers() )                                                                  )
    , mHost                                                 ( new FHostDeviceInfo( FHostDeviceInfo::Detect() )                                                              )
    , mBytesPerTile                                         ( mEmptyTile->BytesTotal()                                                                                      )
    , mSWAPUsageCapTargetAtomic                             ( 0                                                                                                             )
    , mRAMUsageCapTargetAtomic                              ( 0                                                                                                             )
    , mCurrentRAMUsageAtomic                                ( 0                                                                                                             )
    , mTilesScheduledForClear                               ( std::forward_list< FBlock* >()                                                                                )
    , mFreshTilesAvailableForQuery                          ( std::forward_list< FBlock* >()                                                                                )
    , mDirtyHashedTilesCurrentlyInUse                       ( std::list< FTileElement* >()                                                                                  )
    , mCorrectlyHashedTilesCurrentlyInUse                   ( std::unordered_map< uint32, FTileElement* >()                                                                 )
    , mRegisteredTiledBlocks                                ( std::list< tTiledBlock* >()                                                                                   )
    , mMutexTilesScheduledForClearLock                      ()
    , mMutexFreshTilesAvailableForQueryLock                 ()
    , mMutexDirtyHashedTilesCurrentlyInUseLock              ()
    , mMutexCorrectlyHashedTilesCurrentlyInUseLock          ()
    , mMutexRegisteredTiledBlocksLock                       ()
    , mNumTilesScheduledForClearAtomic                      ( 0                                                                                                             )
    , mNumFreshTilesAvailableForQueryAtomic                 ( 0                                                                                                             )
    , bRequestWorkersTerminationAtomic                      ( false                                                                                                         )
    , mThreadDeallocatorAllocatorCleanerBackgroundWorker    ( new std::thread( &TTilePool< _MICRO, _MACRO >::ThreadedDeallocatorAllocatorCleanerBackgroundWorker, this )    )
    , mThreadHasherGarbageCollectorBackgroundWorker         ( new std::thread( &TTilePool< _MICRO, _MACRO >::ThreadedHasherGarbageCollectorBackgroundWorker, this )         )
{
    ClearRaw( mEmptyTile, ULIS2_NOCB );
    mEmptyCRC32Hash = mEmptyTile->CRC32();
}

//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------- Public API
template< uint8 _MICRO, uint8 _MACRO > const FVec2I&        TTilePool< _MICRO, _MACRO >::TileSize()                                 const   { return  mTileSize;                                          }
template< uint8 _MICRO, uint8 _MACRO > uint32               TTilePool< _MICRO, _MACRO >::EmptyCRC32Hash()                           const   { return  mEmptyHash;                                         }
template< uint8 _MICRO, uint8 _MACRO > const FBlock*        TTilePool< _MICRO, _MACRO >::EmptyTile()                                const   { return  mEmptyTile;                                         }
template< uint8 _MICRO, uint8 _MACRO > tFormat              TTilePool< _MICRO, _MACRO >::TileFormat()                               const   { return  mTileFormat;                                        }
template< uint8 _MICRO, uint8 _MACRO > const FFormatInfo&   TTilePool< _MICRO, _MACRO >::TileFormatInfo()                           const   { return  mEmptyTile->FormatInfo();                           }
template< uint8 _MICRO, uint8 _MACRO > const FColorProfile* TTilePool< _MICRO, _MACRO >::TileColorProfile()                         const   { return  mTileColorProfile;                                  }
template< uint8 _MICRO, uint8 _MACRO > uint64               TTilePool< _MICRO, _MACRO >::CurrentRAMUsage()                          const   { return  mCurrentRAMUsageAtomic.load();                      }
template< uint8 _MICRO, uint8 _MACRO > uint64               TTilePool< _MICRO, _MACRO >::CurrentSwapUsage()                         const   { return  0;                                                  }
template< uint8 _MICRO, uint8 _MACRO > uint64               TTilePool< _MICRO, _MACRO >::RAMUsageCapTarget()                        const   { return  mRAMUsageCapTargetAtomic.load();                    }
template< uint8 _MICRO, uint8 _MACRO > uint64               TTilePool< _MICRO, _MACRO >::SWAPUsageCapTarget()                       const   { return  mSWAPUsageCapTargetAtomic.load();                   }
template< uint8 _MICRO, uint8 _MACRO > uint64               TTilePool< _MICRO, _MACRO >::CurrentTotalMemoryUsage()                  const   { return  CurrentRAMUsage();                                  }
template< uint8 _MICRO, uint8 _MACRO > size_t               TTilePool< _MICRO, _MACRO >::NumTilesScheduledForClear()                const   { return  mNumTilesScheduledForClearAtomic.load();            }
template< uint8 _MICRO, uint8 _MACRO > size_t               TTilePool< _MICRO, _MACRO >::NumFreshTilesAvailableForQuery()           const   { return  mNumFreshTilesAvailableForQueryAtomic.load();       }
template< uint8 _MICRO, uint8 _MACRO > void                 TTilePool< _MICRO, _MACRO >::SetRAMUsageCapTarget( uint64 iValue )              { mRAMUsageCapTargetAtomic.store( iValue );                   }
template< uint8 _MICRO, uint8 _MACRO > void                 TTilePool< _MICRO, _MACRO >::SetSWAPUsageCapTarget( uint64 iValue )             { mSWAPUsageCapTargetAtomic.store( iValue );                  }

template< uint8 _MICRO, uint8 _MACRO > size_t TTilePool< _MICRO, _MACRO >::NumDirtyHashedTilesCurrentlyInUse() {
    mMutexDirtyHashedTilesCurrentlyInUseLock.lock();
    auto size = mDirtyHashedTilesCurrentlyInUse.size();
    mMutexDirtyHashedTilesCurrentlyInUseLock.unlock();
    return  size;
}

template< uint8 _MICRO, uint8 _MACRO > size_t TTilePool< _MICRO, _MACRO >::NumCorrectlyHashedTilesCurrentlyInUse() {
    mMutexCorrectlyHashedTilesCurrentlyInUseLock.lock();
    auto size = mCorrectlyHashedTilesCurrentlyInUse.size();
    mMutexCorrectlyHashedTilesCurrentlyInUseLock.unlock();
    return  size;
}

template< uint8 _MICRO, uint8 _MACRO > size_t TTilePool< _MICRO, _MACRO >::NumRegisteredTiledBlocks() {
    mMutexRegisteredTiledBlocksLock.lock();
    auto size = mRegisteredTiledBlocks.size();
    mMutexRegisteredTiledBlocksLock.unlock();
    return  size;
}

template< uint8 _MICRO, uint8 _MACRO > typename TTilePool< _MICRO, _MACRO >::tTiledBlock* TTilePool< _MICRO, _MACRO >::CreateNewTiledBlock() {
    mMutexRegisteredTiledBlocksLock.lock();
    mRegisteredTiledBlocks.emplace_back( new TTiledBlock< _MICRO, _MACRO >( this ) );
    mMutexRegisteredTiledBlocksLock.unlock();
    return  mRegisteredTiledBlocks.back();
}

template< uint8 _MICRO, uint8 _MACRO > void TTilePool< _MICRO, _MACRO >::RequestTiledBlockDeletion( tTiledBlock* iBlock ) {
    mMutexRegisteredTiledBlocksLock.lock();
    auto it = std::find( mRegisteredTiledBlocks.begin(), mRegisteredTiledBlocks.end(), iBlock );
    ULIS2_ASSERT( it != mRegisteredTiledBlocks.end(), "Bad TiledBlock Deletion Request, this tiledblock is not in this pool or has already been deleted !" );
    if( it != mRegisteredTiledBlocks.end() ) {
        delete it;
        mRegisteredTiledBlocks.erase( it );
    }
    mMutexRegisteredTiledBlocksLock.unlock();
}

//--------------------------------------------------------------------------------------
//----------------------------------------------------------------------------- Core API
template< uint8 _MICRO, uint8 _MACRO >
void
TTilePool< _MICRO, _MACRO >::PurgeAllNow() {
    mMutexTilesScheduledForClearLock.lock();
    mMutexFreshTilesAvailableForQueryLock.lock();
    mMutexDirtyHashedTilesCurrentlyInUseLock.lock();
    mMutexCorrectlyHashedTilesCurrentlyInUseLock.lock();
    mMutexRegisteredTiledBlocksLock.lock();

    // Purge Scheduled For Clear
    for( auto& it : mTilesScheduledForClear )
        delete it;

    for( auto& it : mFreshTilesAvailableForQuery )
        delete it;

    for( auto& it : mDirtyHashedTilesCurrentlyInUse ) {
        delete it->mBlock;
        delete it;
    }

    for( auto& it : mCorrectlyHashedTilesCurrentlyInUse ) {
        delete it.second->mBlock;
        delete it.second;
    }

    for( auto it : mRegisteredTiledBlocks ) {
        delete it;
    }

    mTilesScheduledForClear.clear();
    mFreshTilesAvailableForQuery.clear();
    mDirtyHashedTilesCurrentlyInUse.clear();
    mCorrectlyHashedTilesCurrentlyInUse.clear();
    mRegisteredTiledBlocks.clear();
    mCurrentRAMUsageAtomic = 0;
    SetRAMUsageCapTarget( 0 );
    SetSWAPUsageCapTarget( 0 );
    mNumTilesScheduledForClearAtomic = 0;
    mNumTilesScheduledForClearAtomic = 0;

    mMutexTilesScheduledForClearLock.unlock();
    mMutexFreshTilesAvailableForQueryLock.unlock();
    mMutexDirtyHashedTilesCurrentlyInUseLock.unlock();
    mMutexCorrectlyHashedTilesCurrentlyInUseLock.unlock();
    mMutexRegisteredTiledBlocksLock.unlock();
}

template< uint8 _MICRO, uint8 _MACRO >
void
TTilePool< _MICRO, _MACRO >::AllocateNow( uint32 iNum ) {
    mMutexTilesScheduledForClearLock.lock();
    for( uint32 i = 0; i < iNum; ++i ) {
        mTilesScheduledForClear.emplace_front( new FBlock( mTileSize.x, mTileSize.y, mTileFormat, mTileColorProfile ) );
        ++mNumTilesScheduledForClearAtomic;
        mCurrentRAMUsageAtomic.fetch_add( mBytesPerTile );
    }
    mMutexTilesScheduledForClearLock.unlock();
}

template< uint8 _MICRO, uint8 _MACRO >
void
TTilePool< _MICRO, _MACRO >::ClearNow( uint32 iNum ) {
    uint32 currentNumTilesScheduledForClear = mNumTilesScheduledForClearAtomic.load();
    if( iNum > currentNumTilesScheduledForClear )
        AllocateNow( iNum - currentNumTilesScheduledForClear + 1 );

    mMutexTilesScheduledForClearLock.lock();
    mMutexFreshTilesAvailableForQueryLock.lock();
    for( uint32 i = 0; i < iNum; ++i ) {
        auto block = mTilesScheduledForClear.front();
        mTilesScheduledForClear.pop_front();
        --mNumTilesScheduledForClearAtomic;
        ClearRaw( block );
        mFreshTilesAvailableForQuery.emplace_front( block );
        ++mNumFreshTilesAvailableForQueryAtomic;
    }
    mMutexTilesScheduledForClearLock.unlock();
    mMutexFreshTilesAvailableForQueryLock.unlock();
}

template< uint8 _MICRO, uint8 _MACRO >
FTileElement*
TTilePool< _MICRO, _MACRO >::QueryFreshTile() {
    if( mNumFreshTilesAvailableForQueryAtomic.load() == 0 )
        ClearNow( 1 );

    mMutexFreshTilesAvailableForQueryLock.lock();
    FBlock* block = mFreshTilesAvailableForQuery.front();
    mFreshTilesAvailableForQuery.pop_front();
    --mNumFreshTilesAvailableForQueryAtomic;
    FTileElement* tile = new FTileElement( block );
    mDirtyHashedTilesCurrentlyInUse.push_back( tile );
    return  tile;
}

template< uint8 _MICRO, uint8 _MACRO >
FTileElement*
TTilePool< _MICRO, _MACRO >::PerformRedundantHashMergeReturnCorrect( FTileElement* iElem ) {
    return  nullptr;
}

template< uint8 _MICRO, uint8 _MACRO >
FTileElement*
TTilePool< _MICRO, _MACRO >::PerformDataCopyForImminentMutableChangeIfNeeded( FTileElement* iElem ) {
    return  nullptr;
}

//--------------------------------------------------------------------------------------
//------------------------------------------------------------------ Private Workers API
template< uint8 _MICRO, uint8 _MACRO > void TTilePool< _MICRO, _MACRO >::ThreadedDeallocatorAllocatorCleanerBackgroundWorker() {
    for(;;) {
        if( bRequestWorkersTerminationAtomic.load() ) return;

        // Dealloc in blocks scheduled for clear if we overflow the RAM usage cap target.
        if( mCurrentRAMUsageAtomic.load() > mRAMUsageCapTargetAtomic.load() ) {
            if( mNumTilesScheduledForClearAtomic.load() ) {
                mMutexTilesScheduledForClearLock.lock();
                auto block = mTilesScheduledForClear.front();
                mTilesScheduledForClear.pop_front();
                mMutexTilesScheduledForClearLock.unlock();
                --mNumTilesScheduledForClearAtomic;
                delete  block;
                mCurrentRAMUsageAtomic.fetch_sub( mBytesPerTile );
            }
        }

        // Dealloc in blocks scheduled available for query if we overflow the RAM usage cap target, and if scheduled for clear is already empty
        if( mCurrentRAMUsageAtomic.load() > mRAMUsageCapTargetAtomic.load() ) {
            if( mNumFreshTilesAvailableForQueryAtomic.load() && mNumTilesScheduledForClearAtomic.load() == 0 ) {
                mMutexFreshTilesAvailableForQueryLock.lock();
                auto block = mFreshTilesAvailableForQuery.front();
                mFreshTilesAvailableForQuery.pop_front();
                mMutexFreshTilesAvailableForQueryLock.unlock();
                --mNumFreshTilesAvailableForQueryAtomic;
                delete  block;
                mCurrentRAMUsageAtomic.fetch_sub( mBytesPerTile );
            }
        }

        // Alloc in blocks scheduled for clear if we underflow the RAM usage cap target.
        if( mCurrentRAMUsageAtomic.load() < mRAMUsageCapTargetAtomic.load() )
            AllocateNow( 1 );

        // Clear blocks in schdeduled for clear if there are some, then transfer them to available for query
        if( mNumTilesScheduledForClearAtomic.load() ) {
            mMutexTilesScheduledForClearLock.lock();
            auto block = mTilesScheduledForClear.front();
            mTilesScheduledForClear.pop_front();
            mMutexTilesScheduledForClearLock.unlock();
            --mNumTilesScheduledForClearAtomic;
            ClearRaw( block );
            mMutexFreshTilesAvailableForQueryLock.lock();
            mFreshTilesAvailableForQuery.emplace_front( block );
            mMutexFreshTilesAvailableForQueryLock.unlock();
            ++mNumFreshTilesAvailableForQueryAtomic;
        }
    }
}

template< uint8 _MICRO, uint8 _MACRO > void TTilePool< _MICRO, _MACRO >::ThreadedHasherGarbageCollectorBackgroundWorker() {
    for(;;) {
        if( bRequestWorkersTerminationAtomic.load() ) return;

        { // Garbage-Collect dirty tiles we refcount 0 or compute hash for others tiles that are actually dirty.
            mMutexFreshTilesAvailableForQueryLock.lock();
            std::list< FTileElement* >::iterator& it = mDirtyHashedTilesCurrentlyInUse.begin();
            mMutexFreshTilesAvailableForQueryLock.unlock();
            while( true ) {
                mMutexFreshTilesAvailableForQueryLock.lock();
                std::list< FTileElement* >::iterator& end = mDirtyHashedTilesCurrentlyInUse.end();
                mMutexFreshTilesAvailableForQueryLock.unlock();
                if( it == end )
                    break;

                FTileElement* tile = *it;
                if( tile->mRefCount.load() == 0 ) {
                    mMutexFreshTilesAvailableForQueryLock.lock();
                    it = std::prev( mDirtyHashedTilesCurrentlyInUse.erase( it ) );
                    mMutexFreshTilesAvailableForQueryLock.unlock();

                    mMutexTilesScheduledForClearLock.lock();
                    mTilesScheduledForClear.push_front( tile->mBlock );
                    mMutexTilesScheduledForClearLock.unlock();
                    ++mNumTilesScheduledForClearAtomic;

                    delete  tile;
                } else {
                    if( tile->mDirty.load() ) {
                        tile->mHash = tile->mBlock->CRC32();
                        tile->mDirty.store( false );
                    }
                }

                mMutexFreshTilesAvailableForQueryLock.lock();
                it = std::next( it );
                mMutexFreshTilesAvailableForQueryLock.unlock();
            }
        }
    }
}

ULIS2_NAMESPACE_END

