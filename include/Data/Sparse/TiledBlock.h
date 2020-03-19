// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         TiledBlock.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the FTiledBlock class.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"
#include "Data/Sparse/Tile.h"
#include "Data/Sparse/Chunk.h"
#include "Maths/Geometry.h"
#include <unordered_map>

ULIS2_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
/// FTiledBlock
template< uint8 _MICRO
        , uint8 _MACRO >
class ULIS2_API FTiledBlock
{
    typedef TRootChunk< _MICRO, _MACRO, _MACRO >        tRootChunk;
    typedef std::unordered_map< uint64, tRootChunk* >   tMap;
    typedef FTilePool< _MICRO, _MACRO >                 tPool;
public:
    // Construction / Destruction
    ~FTiledBlock();
    FTiledBlock( tPool* iPool );

public:
    // Core API
    size_t      NumRootEntries() const;
    void        Purge();
    void        GatherRootEntries( std::vector< tRootChunk* >* oVector );
    void        GatherLeafEntries( std::vector< tRootChunk* >* oVector );
    bool        IsValidPixelCoordRange( int64 iValue )  const;
    FVec2I32    ChunkCoordinatesFromPixelCoordinates( const FVec2I64& iPos ) const;
    FVec2I64    PixelCoordinatesFromChunkCoordinates( const FVec2I32& iPos ) const;
    uint64      KeyFromChunkCoordinates( const FVec2I32& iPos ) const;
    uint64      KeyFromPixelCoordinates( const FVec2I64& iPos ) const;
    FVec2I32    ChunkCoordinatesFromKey( uint64 iKey ) const;
    FVec2I32    PixelCoordinatesFromKey( uint64 iKey ) const;

private:
    // Private API
    void CreateRootEntryAtPixelSector( const FVec2I64& iPos );
    void CreateRootEntryAtChunkSector( const FVec2I32& iPos );

private:
    // Private Data Members
    tMap mMap;
    tPool* mPool;

    static constexpr uint8  micro_threshold                     = _MICRO;
    static constexpr uint8  macro_threshold                     = _MACRO;
    static constexpr uint16 micro_chunk_size_as_pixels          = ::smath::pow( 2, micro_threshold );
    static constexpr uint16 macro_chunk_size_as_micro_chunks    = ::smath::pow( 2, macro_threshold );
    static constexpr uint32 macro_chunk_size_as_pixels          = micro_chunk_size_as_pixels * macro_chunk_size_as_micro_chunks;
    static constexpr int32 macro_chunk_min_coord                = std::numeric_limits< int32 >::min();
    static constexpr int32 macro_chunk_max_coord                = std::numeric_limits< int32 >::max();
    static constexpr int64 pixel_min_coord                      = static_cast< int64 >( macro_chunk_min_coord ) * static_cast< int64 >( macro_chunk_size_as_micro_chunks );
    static constexpr int64 pixel_max_coord                      = static_cast< int64 >( macro_chunk_max_coord ) * static_cast< int64 >( macro_chunk_size_as_micro_chunks );
};

ULIS2_NAMESPACE_END

#include "TiledBlock.ipp"
