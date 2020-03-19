// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Chunk.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the TTiledBlock class.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"
#include "Data/Block.h"
#include "Maths/Geometry.h"
#include <static_math/static_math.h>

ULIS2_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
// Enums
//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------- eChunkType
enum class eChunkType : uint8
{
      kData
    , kRoot
    , kQuadree
};

//----------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------- eScale
enum eMicro {
    MICRO_8   = 3,
    MICRO_16  = 4,
    MICRO_32  = 5,
    MICRO_64  = 6,
    MICRO_128 = 7,
    MICRO_256 = 8,
};

enum eMacro {
    MACRO_2   = 1,
    MACRO_4   = 2,
    MACRO_8   = 3,
    MACRO_16  = 4,
    MACRO_32  = 5,
    MACRO_64  = 6,
    MACRO_128 = 7,
    MACRO_256 = 8,
};


/////////////////////////////////////////////////////
/// TAbstractChunk
template< uint8 _MICRO
        , uint8 _MACRO
        , uint8 _LOCAL >
class ULIS2_API TAbstractChunk
{
    typedef  TAbstractChunk< _MICRO, _MACRO, _LOCAL >   tSelf;
    typedef TTilePool< _MICRO, _MACRO >                 tTilePool;

public:
    // Construction / Destruction
    virtual ~TAbstractChunk() {}
    TAbstractChunk() {}

public:
    // Public API
    virtual  eChunkType  Type()  const = 0;
    virtual  const FBlock* QueryTileAtPixelCoordinates( const tTilePool* iPool, const FVec2I64& iPos ) = 0;

protected:
    // Protected Data Members
    static constexpr uint8  micro_threshold                     = _MICRO;
    static constexpr uint8  macro_threshold                     = _MACRO;
    static constexpr uint8  local_threshold                     = _LOCAL;
    static constexpr uint8  sub_threshold                       = _LOCAL - 1;
    static constexpr uint16 micro_chunk_size_as_pixels          = ::smath::pow( 2, micro_threshold );
    static constexpr uint16 local_chunk_size_as_micro_chunks    = ::smath::pow( 2, local_threshold );
    static constexpr uint32 local_chunk_size_as_pixels          = micro_chunk_size_as_pixels * local_chunk_size_as_micro_chunks;
    static constexpr uint32 local_chunk_halfsize_as_pixels      = local_chunk_size_as_pixels / 2;
    static constexpr bool   bed                                 = _LOCAL == 1;
};

/////////////////////////////////////////////////////
/// TRootChunk
template< uint8 _MICRO
        , uint8 _MACRO
        , uint8 _LOCAL >
class ULIS2_API TRootChunk : public TAbstractChunk< _MICRO, _MACRO, _LOCAL >
{
    typedef  TAbstractChunk<    _MICRO, _MACRO, _LOCAL >    tSuperClass;
    typedef  TRootChunk<        _MICRO, _MACRO, _LOCAL >    tSelf;
    typedef  TAbstractChunk<    _MICRO, _MACRO, _LOCAL >    tChild;
    typedef TTilePool< _MICRO, _MACRO >                 tTilePool;

public:
    // Construction / Destruction
    virtual ~TRootChunk() {}
    TRootChunk()
        : mChild( nullptr )
    {}

public:
    // Public API
    virtual  eChunkType  Type()  const override { return  eChunkType::kRoot; }
    virtual  const FBlock* QueryTileAtPixelCoordinates( const tTilePool* iPool, const FVec2I64& iPos ) override {
        return  mChild ? iPool->EmptyTile() : mChild->QueryTileAtPixelCoordinates( iPool, iPos );
    }

private:
    // Private Data Members
    tChild* mChild;
};


/////////////////////////////////////////////////////
/// TDataChunk
template< uint8 _MICRO
        , uint8 _MACRO
        , uint8 _LOCAL >
class ULIS2_API TDataChunk : public TAbstractChunk< _MICRO, _MACRO, _LOCAL >
{
    typedef  TAbstractChunk<    _MICRO, _MACRO, _LOCAL >    tSuperClass;
    typedef  TDataChunk<        _MICRO, _MACRO, _LOCAL >    tSelf;
    typedef TTilePool< _MICRO, _MACRO >                 tTilePool;

public:
    // Construction / Destruction
    virtual ~TDataChunk() {}
    TDataChunk()
        : mPtr( nullptr )
    {}

public:
    // Public API
    virtual  eChunkType  Type()  const override { return  eChunkType::kData; }
    virtual  const FBlock* QueryTileAtPixelCoordinates( const tTilePool* iPool, const FVec2I64& iPos ) override {
        return  mPtr->mBlock;
    }

private:
    // Private Data Members
    FTileElement* mPtr;
};

/////////////////////////////////////////////////////
/// TQuadtreeChunk
template< uint8 _MICRO
        , uint8 _MACRO
        , uint8 _LOCAL >
class ULIS2_API TQuadtreeChunk : public TAbstractChunk< _MICRO, _MACRO, _LOCAL >
{
    typedef  TAbstractChunk<    _MICRO, _MACRO, _LOCAL >                        tSuperClass;
    typedef  TQuadtreeChunk<    _MICRO, _MACRO, _LOCAL >                        tSelf;
    typedef  TAbstractChunk<    _MICRO, _MACRO, tSuperClass::sub_threshold >    tSubAbstractChunk;
    typedef  TQuadtreeChunk<    _MICRO, _MACRO, tSuperClass::sub_threshold >    tSubQuadtreeChunk;
    typedef TTilePool< _MICRO, _MACRO >                 tTilePool;

public:
    // Construction / Destruction
    virtual ~TQuadtreeChunk() {}
    TQuadtreeChunk()
        : mQuad( { nullptr, nullptr, nullptr, nullptr } )
    {
    }

private:
    // Coordinates API
    FVec2I64  SubChunkCoordinatesFromLocalPixelCoordinates( const FVec2I64& iPos )  const { return  iPos / local_chunk_halfsize_as_pixels; }
    FVec2I64  LocalPixelCoordinatesFromSubChunkCoordinates( const FVec2I64& iPos )  const { return  iPos * local_chunk_halfsize_as_pixels; }

    uint8 IndexFromSubChunkCoordinates( const FVec2I64& iPos )  const {
        return  iPos.y * 2  + iX;
    }

    FVec2I64 SubChunkCoordinatesFromIndex( uint8 iIndex )  const {
        return  FVec2I64( iIndex & 0x1, ( iIndex & 0x2 ) >> 1 );
    }

public:
    // Public API
    virtual  eChunkType  Type()  const override { return  eChunkType::kRoot; }
    virtual  const FBlock* QueryTileAtPixelCoordinates( const tTilePool* iPool, const FVec2I64& iPos ) override {
        uint8 index = IndexFromSubChunkCoordinates( SubChunkCoordinatesFromLocalPixelCoordinates( iPos ) );
        return  mQuad[index] == nullptr ? iPool->EmptyTile() : mQuad[index]->QueryTileAtPixelCoordinates( iPool, iPos % local_chunk_halfsize_as_pixels );
    }

private:
    // Private Data Members
    tSubAbstractChunk* mQuad[4];
};

ULIS2_NAMESPACE_END

