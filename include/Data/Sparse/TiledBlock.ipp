// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         TiledBlock.ipp
* @author       Clement Berthaud
* @brief        This file provides the definition for the FTiledBlock class.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"
#include "Data/Sparse/TiledBlock.h"


#define ULIS2_SPARSE_MASK_X 0x00000000FFFFFFFF
#define ULIS2_SPARSE_MASK_Y 0xFFFFFFFF00000000

ULIS2_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
/// FTiledBlock
//--------------------------------------------------------------------------------------
//----------------------------------------------------------- Construction / Destruction
template< uint8 _MICRO, uint8 _MACRO > FTiledBlock< _MICRO, _MACRO >::~FTiledBlock() {
    for( auto i : mMap )
        delete  i.second;
    mMap.clear();
}


template< uint8 _MICRO, uint8 _MACRO > FTiledBlock< _MICRO, _MACRO >::FTiledBlock( tPool* iPool )
    : mPool( iPool )
{
    static_assert( _MICRO > 0, "_MICRO template argument cannot be 0" );
    static_assert( _MACRO > 0, "_MACRO template argument cannot be 0" );
}

//--------------------------------------------------------------------------------------
//----------------------------------------------------------------------------- Core API
template< uint8 _MICRO, uint8 _MACRO >
size_t
FTiledBlock< _MICRO, _MACRO >::NumRootEntries() const {
    return  mMap.size();
}


template< uint8 _MICRO, uint8 _MACRO >
void
FTiledBlock< _MICRO, _MACRO >::Purge() {
    for( auto i : mMap )
        delete  i.second;
    mMap.clear();
}


template< uint8 _MICRO, uint8 _MACRO >
void
FTiledBlock< _MICRO, _MACRO >::GatherRootEntries( std::vector< tRootChunk* >* oVector ) {
    oVector->clear();
    oVector->reserve( mMap.size() );
    for( auto i : mMap )
        oVector->push_back( oVector );
}


template< uint8 _MICRO, uint8 _MACRO >
void
FTiledBlock< _MICRO, _MACRO >::GatherLeafEntries( std::vector< tRootChunk* >* oVector ) {
    /*
    oVector->clear();
    oVector->reserve( mMap.size() );
    for( auto i : mMap )
        i.second->GatherMicroDataChunks( oVector );*/
}


template< uint8 _MICRO, uint8 _MACRO >
bool
FTiledBlock< _MICRO, _MACRO >::IsValidPixelCoordRange( int64 iValue )  const {
    return  iValue > pixel_min_coord && iValue < pixel_max_coord; 
}


template< uint8 _MICRO, uint8 _MACRO >
FVec2I32
FTiledBlock< _MICRO, _MACRO >::ChunkCoordinatesFromPixelCoordinates( const FVec2I64& iPos ) const {
    ULIS2_ASSERT( IsInValidVoxelCoordRange( iPos.x ) && IsInValidVoxelCoordRange( iPos.y ), "Bad coordinates" );
    int32 X = static_cast< int32 >( FMaths::RoundToNegativeInfinity( iX / static_cast< float >( macro_chunk_size_as_pixels ) ) );
    int32 Y = static_cast< int32 >( FMaths::RoundToNegativeInfinity( iY / static_cast< float >( macro_chunk_size_as_pixels ) ) );
    return  FVec2I32( X, Y );
}


template< uint8 _MICRO, uint8 _MACRO >
FVec2I64
FTiledBlock< _MICRO, _MACRO >::PixelCoordinatesFromChunkCoordinates( const FVec2I32& iPos ) const {
    int64 X = static_cast< int64 >( iPos.x * macro_chunk_size_as_pixels );
    int64 Y = static_cast< int64 >( iPos.y * macro_chunk_size_as_pixels );
    return  FVec2I64( X, Y );
}


template< uint8 _MICRO, uint8 _MACRO >
uint64
FTiledBlock< _MICRO, _MACRO >::KeyFromChunkCoordinates( const FVec2I32& iPos ) const {
    return  static_cast< uint64 >( iX ) | ( static_cast< uint64 >( iY ) << 32 );
}


template< uint8 _MICRO, uint8 _MACRO >
uint64
FTiledBlock< _MICRO, _MACRO >::KeyFromPixelCoordinates( const FVec2I64& iPos ) const {
    FVec2I32 pos = ChunkCoordinatesFromPixelCoordinates( iPos );
    return  KeyFromChunkCoordinates( pos );
}


template< uint8 _MICRO, uint8 _MACRO >
FVec2I32
FTiledBlock< _MICRO, _MACRO >::ChunkCoordinatesFromKey( uint64 iKey ) const {
    int32 X = static_cast< int32 >( iKey & ULIS2_SPARSE_MASK_X );
    int32 Y = static_cast< int32 >( ( iKey & ULIS2_SPARSE_MASK_Y ) >> 32 );
    return  FVec2I32( X, Y );
}


template< uint8 _MICRO, uint8 _MACRO >
FVec2I32
FTiledBlock< _MICRO, _MACRO >::PixelCoordinatesFromKey( uint64 iKey ) const {
    FVec2I32 pos = ChunkCoordinatesFromKey( iKey );
    return  PixelCoordinatesFromChunkCoordinates( pos );
}

//--------------------------------------------------------------------------------------
//-------------------------------------------------------------------------- Private API
template< uint8 _MICRO, uint8 _MACRO >
void
FTiledBlock< _MICRO, _MACRO >::CreateRootEntryAtPixelSector( const FVec2I64& iPos ) {
    CreateRootEntryAtChunkSector( ChunkCoordinatesFromPixelCoordinates( iPos ) );
}

template< uint8 _MICRO, uint8 _MACRO >
void
FTiledBlock< _MICRO, _MACRO >::CreateRootEntryAtChunkSector( const FVec2I32& iPos ) {
    uint64 key = KeyFromChunkCoordinates( iPos );
    auto it = mMap.find( key );

    if( it != mMap.end() )
        return; // Root Chunk Entry Already Exists.

    tRootChunk* tmp = new tRootChunk();
    mMap[ key ] = tmp;
}

ULIS2_NAMESPACE_END
