// Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Pixel.cpp
* @author       Clement Berthaud
* @brief        This file provides the definition for the FPixel class.
* @copyright    Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include "Pixel.h"

ULIS2_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
// FPixel
//--------------------------------------------------------------------------------------
//----------------------------------------------------------- Construction / Destruction
FPixel::~FPixel()
{
}


FPixel::FPixel( tFormat iFormat )
    : mData( nullptr )
    , mFormat( iFormat )
{
}


FPixel::FPixel( tByte* iData, tFormat iFormat )
    : mData( iData )
    , mFormat( iFormat )
{
}


//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------- Public API
tByte*
FPixel::Ptr()
{
    return  mData;
}


const tByte*
FPixel::Ptr() const
{
    return  mData;
}


tSize
FPixel::BytesPerSample() const
{
    return  ( ( ULIS2_TYPE_DEPTH >> ULIS2_R_TYPE( mFormat ) ) & ULIS2_TYPE_DEPTH_MASK );
}


tSize
FPixel::Depth() const
{
    return  BytesPerSample() * SamplesPerPixel();
}


tFormat
FPixel::Format() const
{
    return  mFormat;
}


eModelSig
FPixel::Model() const
{
    return  static_cast< eModelSig >( ULIS2_R_MODEL( mFormat ) );
}


eType
FPixel::Type() const
{
    return  static_cast< eType >( ULIS2_R_TYPE( mFormat ) );
}


bool
FPixel::HasAlpha() const
{
    return  static_cast< bool >( ULIS2_R_ALPHA( mFormat ) );
}


bool
FPixel::Swapped() const
{
    return  static_cast< bool >( ULIS2_R_SWAP( mFormat ) );
}


bool
FPixel::Reversed() const
{
    return  static_cast< bool >( ULIS2_R_REVERSE( mFormat ) );
}


uint8
FPixel::SamplesPerPixel() const
{
    return  NumColorChannels() + static_cast< uint8 >( HasAlpha() );
}


uint8
FPixel::NumColorChannels() const
{
    return  static_cast< uint8 >( ULIS2_R_CHANNELS( mFormat ) );
}


ULIS2_NAMESPACE_END

