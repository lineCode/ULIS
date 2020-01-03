// Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Block.cpp
* @author       Clement Berthaud
* @brief        This file provides the definition for the FBlock class.
* @copyright    Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include "Block.h"

ULIS2_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
// Default Cleanup Behaviour
void Cleanup_FreeMemory_imp( tByte* iData )
{
    delete [] iData;
}


void Cleanup_DoNothing_imp( tByte* iData )
{
}

FOnCleanup OnCleanup_FreeMemory = Cleanup_FreeMemory_imp;
FOnCleanup OnCleanup_DoNothing  = Cleanup_DoNothing_imp;

/////////////////////////////////////////////////////
// FBlock
//--------------------------------------------------------------------------------------
//----------------------------------------------------------- Construction / Destruction
FBlock::~FBlock()
{
    mOnCleanup( mData );
}


FBlock::FBlock( tSize iWidth, tSize iHeight, tFormat iFormat, const FOnInvalid& iOnInvalid, const FOnCleanup& iOnCleanup )
    : mData( nullptr )
    , mWidth( iWidth )
    , mHeight( iHeight )
    , mFormat( iFormat )
    , mOnInvalid( iOnInvalid )
    , mOnCleanup( iOnCleanup )
{
    mData = new tByte[ BytesTotal() ];
}


FBlock::FBlock( tByte* iData, tSize iWidth, tSize iHeight, tFormat iFormat, const FOnInvalid& iOnInvalid, const FOnCleanup& iOnCleanup )
    : mData( iData )
    , mWidth( iWidth )
    , mHeight( iHeight )
    , mFormat( iFormat )
    , mOnInvalid( iOnInvalid )
    , mOnCleanup( iOnCleanup )
{
}


//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------- Public API
tByte*
FBlock::DataPtr()
{
    return  mData;
}


const tByte*
FBlock::DataPtr() const
{
    return  mData;
}


tByte*
FBlock::PixelPtr( int iX, int iY )
{
    return  DataPtr() + ( iX * BytesPerPixel() + iY * BytesPerScanLine() );
}


const tByte*
FBlock::PixelPtr( int iX, int iY ) const
{
    return  DataPtr() + ( iX * BytesPerPixel() + iY * BytesPerScanLine() );
}


tByte*
FBlock::ScanlinePtr( int iRow )
{
    return  DataPtr() + ( iRow * BytesPerScanLine() );
}


const tByte*
FBlock::ScanlinePtr( int iRow ) const
{
    return  DataPtr() + ( iRow * BytesPerScanLine() );
}


tSize
FBlock::Width() const
{
    return  mWidth;
}


tSize
FBlock::Height() const
{
    return  mHeight;
}


tSize
FBlock::BytesPerSample() const
{
    return  ( ( ULIS2_TYPE_DEPTH >> ULIS2_R_TYPE( mFormat ) ) & ULIS2_TYPE_DEPTH_MASK );
}


tSize
FBlock::BytesPerPixel() const
{
    return  BytesPerSample() * SamplesPerPixel();
}


tSize
FBlock::BytesPerScanLine() const
{
    return  BytesPerPixel() * mWidth;
}


tSize
FBlock::BytesTotal() const
{
    return  BytesPerScanLine() * mHeight;
}


tFormat
FBlock::Format() const
{
    return  mFormat;
}


eModel
FBlock::Model() const
{
    return  static_cast< eModel >( ULIS2_R_MODEL( mFormat ) );
}


eType
FBlock::Type() const
{
    return  static_cast< eType >( ULIS2_R_TYPE( mFormat ) );
}


bool
FBlock::HasAlpha() const
{
    return  static_cast< bool >( ULIS2_R_ALPHA( mFormat ) );
}


bool
FBlock::Swapped() const
{
    return  static_cast< bool >( ULIS2_R_SWAP( mFormat ) );
}


bool
FBlock::Reversed() const
{
    return  static_cast< bool >( ULIS2_R_REVERSE( mFormat ) );
}


uint8
FBlock::SamplesPerPixel() const
{
    return  NumColorChannels() + static_cast< uint8 >( HasAlpha() );
}


uint8
FBlock::NumColorChannels() const
{
    return  static_cast< uint8 >( ULIS2_R_CHANNELS( mFormat ) );
}


ULIS2_NAMESPACE_END

