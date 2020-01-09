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
#include "ColorProfile.h"
#include "Geometry.h"

ULIS2_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
// Default Cleanup Behaviour
void OnCleanup_FreeMemory( tByte* iData, void* iInfo )
{
    delete [] iData;
}

void OnCleanup_DoNothing( tByte* iData, void* iInfo )
{
}

/////////////////////////////////////////////////////
// FBlock
//--------------------------------------------------------------------------------------
//----------------------------------------------------------- Construction / Destruction
FBlock::~FBlock()
{
    mOnCleanup.ExecuteIfBound( mData );
}


FBlock::FBlock( tSize iWidth
              , tSize iHeight
              , tFormat iFormat
              , const FOnInvalid& iOnInvalid
              , const FOnCleanup& iOnCleanup )
    : mData( nullptr )
    , mWidth( iWidth )
    , mHeight( iHeight )
    , mFormat( iFormat )
    , mOnInvalid( iOnInvalid )
    , mOnCleanup( iOnCleanup )
    , mProfile( nullptr )
{
    ULIS2_ASSERT( iWidth  > 0, "Width must be greater than zero" );
    ULIS2_ASSERT( iHeight > 0, "Height must be greater than zero" );
    mData = new tByte[ BytesTotal() ];
}


FBlock::FBlock( tSize iWidth
              , tSize iHeight
              , tFormat iFormat
              , FColorProfile* iProfile
              , const FOnInvalid& iOnInvalid
              , const FOnCleanup& iOnCleanup )
    : mData( nullptr )
    , mWidth( iWidth )
    , mHeight( iHeight )
    , mFormat( iFormat )
    , mOnInvalid( iOnInvalid )
    , mOnCleanup( iOnCleanup )
    , mProfile( iProfile )
{
    ULIS2_ASSERT( iWidth  > 0, "Width must be greater than zero" );
    ULIS2_ASSERT( iHeight > 0, "Height must be greater than zero" );

    if( mProfile )
        ULIS2_ERROR( mProfile->ModelSupported( Model() ), "Bad ColorProfile" );

    mData = new tByte[ BytesTotal() ];
}


FBlock::FBlock( tByte* iData
              , tSize iWidth
              , tSize iHeight
              , tFormat iFormat
              , const FOnInvalid& iOnInvalid
              , const FOnCleanup& iOnCleanup )
    : mData( nullptr )
    , mWidth( iWidth )
    , mHeight( iHeight )
    , mFormat( iFormat )
    , mOnInvalid( iOnInvalid )
    , mOnCleanup( iOnCleanup )
    , mProfile( nullptr )
{
    ULIS2_ASSERT( iWidth  > 0, "Width must be greater than zero" );
    ULIS2_ASSERT( iHeight > 0, "Height must be greater than zero" );
}


FBlock::FBlock( tByte* iData
              , tSize iWidth
              , tSize iHeight
              , tFormat iFormat
              , FColorProfile* iProfile
              , const FOnInvalid& iOnInvalid
              , const FOnCleanup& iOnCleanup )
    : mData( nullptr )
    , mWidth( iWidth )
    , mHeight( iHeight )
    , mFormat( iFormat )
    , mOnInvalid( iOnInvalid )
    , mOnCleanup( iOnCleanup )
    , mProfile( iProfile )
{
    ULIS2_ASSERT( iWidth  > 0, "Width must be greater than zero" );
    ULIS2_ASSERT( iHeight > 0, "Height must be greater than zero" );

    if( mProfile )
        ULIS2_ERROR( mProfile->ModelSupported( Model() ), "Bad ColorProfile" );
}



//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------- Public API
tByte*
FBlock::DataPtr()
{
    return  mData;
}


tByte*
FBlock::PixelPtr( tIndex iX, tIndex iY )
{
    ULIS2_ASSERT( iX >= 0 && iX < mWidth, "Index out of range" );
    ULIS2_ASSERT( iY >= 0 && iY < mHeight, "Index out of range" );
    return  DataPtr() + ( uint64( iX ) * uint64( BytesPerPixel() ) + uint64( iY ) * uint64( BytesPerScanLine() ) );
}


tByte*
FBlock::ScanlinePtr( tIndex iRow )
{
    ULIS2_ASSERT( iRow >= 0 && iRow < mHeight, "Index out of range" );
    return  DataPtr() + ( uint64( iRow ) * uint64( BytesPerScanLine() ) );
}


const tByte*
FBlock::DataPtr() const
{
    return  mData;
}


void
FBlock::AssignProfile( FColorProfile* iProfile )
{
    mProfile = iProfile;

    if( mProfile )
        ULIS2_ERROR( mProfile->ModelSupported( Model() ), "Bad ColorProfile" );
}


const tByte*
FBlock::PixelPtr( tIndex iX, tIndex iY ) const
{
    ULIS2_ASSERT( iX >= 0 && iX < mWidth, "Index out of range" );
    ULIS2_ASSERT( iY >= 0 && iY < mHeight, "Index out of range" );
    return  DataPtr() + (uint64( iX ) * uint64( BytesPerPixel() ) + uint64( iY ) * uint64( BytesPerScanLine() ) );
}



const tByte*
FBlock::ScanlinePtr( tIndex iRow ) const
{
    ULIS2_ASSERT( iRow >= 0 && iRow < mHeight, "Index out of range" );
    return  DataPtr() + (uint64( iRow ) * uint64( BytesPerScanLine() ) );
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


eModelSig
FBlock::Model() const
{
    return  static_cast< eModelSig >( ULIS2_R_MODEL( mFormat ) );
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


FColorProfile*
FBlock::Profile() const
{
    return  mProfile;
}


void
FBlock::Invalidate() const
{
    Invalidate( FRect( 0, 0, Width(), Height() ) );
}


void
FBlock::Invalidate( const FRect& iRect ) const
{
    ULIS2_ASSERT( iRect.x >= 0 && iRect.x < mWidth, "Index out of range" );
    ULIS2_ASSERT( iRect.y >= 0 && iRect.y < mHeight, "Index out of range" );
    ULIS2_ASSERT( iRect.x + iRect.w >= 1 && iRect.x + iRect.w <= mWidth, "Index out of range" );
    ULIS2_ASSERT( iRect.y + iRect.h >= 1 && iRect.y + iRect.h <= mHeight, "Index out of range" );
    mOnInvalid.ExecuteIfBound( this, iRect );
}


FPixelValue
FBlock::PixelValue( tIndex iX, tIndex iY ) const
{
    return  FPixelValue( PixelPtr( iX, iY ), Format(), Profile() );
}


FPixelProxy
FBlock::PixelProxy( tIndex iX, tIndex iY )
{
    return  FPixelProxy( PixelPtr( iX, iY ), Format(), Profile() );
}


FColor
FBlock::PixelColor( tIndex iX, tIndex iY ) const
{
    return  FColor();
}


ULIS2_NAMESPACE_END

