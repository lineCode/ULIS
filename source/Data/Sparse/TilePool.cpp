// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         TilePool.cpp
* @author       Clement Berthaud
* @brief        This file provides the definition for the TilePool class.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include "Data/Sparse/TilePool.h"
#include "Data/Sparse/Tile.h"
#include "Base/CRC32.h"
#include "Base/HostDeviceInfo.h"
#include "Data/Block.h"
#include "Thread/ThreadPool.h"
#include "Clear/Clear.h"
#include <thread>

ULIS2_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
/// FTilePool
//--------------------------------------------------------------------------------------
//----------------------------------------------------------- Construction / Destruction
FTilePool::~FTilePool() {
    PurgeAllNow();
    mThreadPool->WaitForCompletion();
    delete  mThreadPool;
    delete  mHost;
    delete  mEmptyTile;
}

FTilePool::FTilePool( int iWidth
                    , int iHeight
                    , tFormat iFormat
                    , FColorProfile* iProfile
                    , uint64 iRAMUsageCapTarget
                    , uint64 iSWAPUsageCapTarget
                    , uint32 iDesiredPoolWorkers
                    , uint32 iTimeOutMS )
    : mTileSize                                 ( iWidth, iHeight       )
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

    mEmptyTile = new FBlock( iWidth, iHeight, iFormat, iProfile );
    ClearRaw( mEmptyTile, ULIS2_NOCB );
    mEmptyHash = mEmptyTile->CRC32();
    mBytesPerTile = mEmptyTile->BytesTotal();
}

//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------- Public API
const FVec2I&           FTilePool::TileSize()                               const   { return  mTileSize;                                        }
uint32                  FTilePool::EmptyHash()                              const   { return  mEmptyHash;                                       }
const FBlock*           FTilePool::EmptyTile()                              const   { return  mEmptyTile;                                       }
tFormat                 FTilePool::TileFormat()                             const   { return  mTileFormat;                                      }
const FFormatInfo&      FTilePool::TileFormatInfo()                         const   { return  mEmptyTile->FormatInfo();                         }
const FColorProfile*    FTilePool::TileColorProfile()                       const   { return  mTileColorProfile;                                }
uint64                  FTilePool::CurrentRAMUsage()                        const   { return  mCurrentRAMUSage;                                 }
uint64                  FTilePool::CurrentSwapUsage()                       const   { return  0;                                                }
uint64                  FTilePool::RAMUsageCapTarget()                      const   { return  mRAMUsageCapTarget;                               }
uint64                  FTilePool::SWAPUsageCapTarget()                     const   { return  mSWAPUsageCapTarget;                              }
uint64                  FTilePool::CurrentTotalMemoryUsage()                const   { return  mCurrentRAMUSage;                                 }
long long               FTilePool::TimeOutMS()                              const   { return  mTimeOutMS.count();                               }
void                    FTilePool::SetRAMUsageCapTarget( uint64 iValue )            { mRAMUsageCapTarget  = iValue;                             }
void                    FTilePool::SetSWAPUsageCapTarget( uint64 iValue )           { mSWAPUsageCapTarget = iValue;                             }
void                    FTilePool::SetTimeOutMS( uint32 iValue )                    { mTimeOutMS = std::chrono::milliseconds( iValue );         }
size_t                  FTilePool::NumTilesScheduledForClear()              const   { return  mNumTilesScheduledForClear;                       }
size_t                  FTilePool::NumFreshTilesAvailableForQuery()         const   { return  mNumFreshTilesAvailableForQuery;                  }
size_t                  FTilePool::NumDirtyHashedTilesCurrentlyInUse()      const   { return  mDirtyHashedTilesCurrentlyInUse_dlist.size();     }
size_t                  FTilePool::NumCorrectlyHashedTilesCurrentlyInUse()  const   { return  mCorrectlyHashedTilesCurrentlyInUse_umap.size();  }
//--------------------------------------------------------------------------------------
//----------------------------------------------------------------------------- Core API
void
FTilePool::Tick() {
    if( mTickForbidden )
        return;

    int     num_task = 4;
    auto    micro_delta = mTimeOutMS / num_task;
    auto    span_del1   = micro_delta * 1;
    auto    span_del2   = micro_delta * 2;
    auto    span_new    = micro_delta * 3;
    auto    span_clear  = micro_delta * 4;
    std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();

    std::cout << "Current RAM: " << mCurrentRAMUSage    << std::endl;
    std::cout << "Target  RAM: " << mRAMUsageCapTarget  << std::endl;

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


void
FTilePool::PurgeAllNow() {
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

    mTilesScheduledForClear_slist.clear();
    mFreshTilesAvailableForQuery_slist.clear();
    mDirtyHashedTilesCurrentlyInUse_dlist.clear();
    mCorrectlyHashedTilesCurrentlyInUse_umap.clear();
    mCurrentRAMUSage = 0;
    SetRAMUsageCapTarget( 0 );
    SetSWAPUsageCapTarget( 0 );
    mNumTilesScheduledForClear = 0;
    mNumFreshTilesAvailableForQuery = 0;
    mTickForbidden = false;
}

void
FTilePool::AllocateNow( uint32 iNum ) {
    mTickForbidden = true;
    for( uint32 i = 0; i < iNum; ++i ) {
        mTilesScheduledForClear_slist.emplace_front( new FBlock( mTileSize.x, mTileSize.y, mTileFormat, mTileColorProfile ) );
        ++mNumTilesScheduledForClear;
        mCurrentRAMUSage += mBytesPerTile;
    }
    mTickForbidden = false;
}

void
FTilePool::ClearNow( uint32 iNum ) {
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

FTileElement*
FTilePool::QueryFreshTile() {
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

ULIS2_NAMESPACE_END

