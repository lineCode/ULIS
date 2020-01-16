// Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Pixel.cpp
* @author       Clement Berthaud
* @brief        This file provides the definition for the Pixel classes.
* @copyright    Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include "Pixel.h"
#include "ColorProfile.h"
#include "Maths.h"

ULIS2_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
// IPixel
//--------------------------------------------------------------------------------------
//----------------------------------------------------------- Construction / Destruction
IPixel::~IPixel()
{
}


IPixel::IPixel( tFormat iFormat, FColorProfile* iProfile )
    : mData( nullptr )
    , mFormat( iFormat )
    , mProfile( iProfile )
{
    if( mProfile )
        ULIS2_ERROR( mProfile->IsModelSupported( Model() ), "Bad ColorProfile" );
}


//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------- Public API
tByte*
IPixel::Ptr()
{
    return  mData;
}


void
IPixel::AssignProfile( FColorProfile* iProfile )
{
    mProfile = iProfile;

    if( mProfile )
        ULIS2_ERROR( mProfile->IsModelSupported( Model() ), "Bad ColorProfile" );
}


const tByte*
IPixel::Ptr() const
{
    return  mData;
}


uint8
IPixel::BytesPerSample() const
{
    return  ULIS2_R_DEPTH( mFormat );
}


uint8
IPixel::Depth() const
{
    return  BytesPerSample() * NumSamples();
}


tFormat
IPixel::Format() const
{
    return  mFormat;
}


eColorModel
IPixel::Model() const
{
    return  static_cast< eColorModel >( ULIS2_R_MODEL( mFormat ) );
}


eType
IPixel::Type() const
{
    return  static_cast< eType >( ULIS2_R_TYPE( mFormat ) );
}


bool
IPixel::HasAlpha() const
{
    return  static_cast< bool >( ULIS2_R_ALPHA( mFormat ) );
}


bool
IPixel::Swapped() const
{
    return  static_cast< bool >( ULIS2_R_SWAP( mFormat ) );
}


bool
IPixel::Reversed() const
{
    return  static_cast< bool >( ULIS2_R_REVERSE( mFormat ) );
}


uint8
IPixel::NumSamples() const
{
    return  NumColorChannels() + static_cast< uint8 >( HasAlpha() );
}


uint8
IPixel::NumColorChannels() const
{
    return  static_cast< uint8 >( ULIS2_R_CHANNELS( mFormat ) );
}


FColorProfile*
IPixel::Profile() const
{
    return  mProfile;
}


uint8
IPixel::RedirectedIndex( uint8 iIndex ) const
{
    int max_sample = NumSamples() - 1;
    int index = iIndex;
    uint8 code = ULIS2_R_RS( mFormat );
    switch( code )
    {
        case 1:     return  ( max_sample - index );
        case 2:     return  ( index + 1 ) > max_sample ? 0 : index + 1;
        case 3:     return  ( max_sample - index ) - 1 < 0 ? max_sample : ( max_sample - index ) - 1;
        default:    return  index;
    }
}


uint8
IPixel::AlphaIndex() const
{
    ULIS2_ASSERT( HasAlpha(), "Bad Call" );
    uint8 max_sample = NumSamples() - 1;
    uint8 code = ULIS2_R_RS( mFormat );
    switch( code )
    {
        case 1:     return  0;
        case 2:     return  0;
        case 3:     return  max_sample;
        default:    return  max_sample;
    }
}


//--------------------------------------------------------------------------------------
//------------------------------------------------------------------ Generic Accesss API
tByte*
IPixel::SamplePtr( uint8 iIndex )
{
    ULIS2_ASSERT( iIndex < NumSamples(), "Index out of range" );
    return  ( tByte* )( Ptr() + ( (uint64)iIndex * BytesPerSample() ) );
}


template< typename T >
T*
IPixel::SamplePtrT( uint8 iIndex )
{
    ULIS2_ASSERT( Type() == eTypeFromT< T >(), "Bad type" )
    return  ( T* )( SamplePtr( iIndex ) );
}


const tByte*
IPixel::SamplePtr( uint8 iIndex ) const
{
    ULIS2_ASSERT( iIndex < NumSamples(), "Index out of range" );
    return  ( tByte* )( Ptr() + ( (uint64)iIndex * BytesPerSample() ) );
}


template< typename T >
const T*
IPixel::SamplePtrT( uint8 iIndex ) const
{
    ULIS2_ASSERT( Type() == eTypeFromT< T >(), "Bad type" )
    return  ( T* )( SamplePtr( iIndex ) );
}


template< typename T >
T
IPixel::GetValueRaw( uint8 iIndex ) const
{
    return  *SamplePtrT< T >( iIndex );
}


template< typename T >
void
IPixel::SetValueRaw( uint8 iIndex, T iValue )
{
    *SamplePtrT< T >( iIndex ) = iValue;
}


template< typename T > T&
IPixel::GetRefRaw( uint8 iIndex )
{
    return  (*SamplePtrT< T >( iIndex ));
}


template< typename T >
const T&
IPixel::GetConstRefRaw( uint8 iIndex ) const
{
    return  (*SamplePtrT< T >( iIndex ));
}


template< typename T >
T
IPixel::GetValue( uint8 iIndex ) const
{
    return  GetValueRaw< T >( RedirectedIndex( iIndex ) );
}


template< typename T >
T&
IPixel::GetRef( uint8 iIndex )
{
    return  GetRefRaw< T >( RedirectedIndex( iIndex ) );
}


template< typename T >
const T&
IPixel::GetConstRef( uint8 iIndex ) const
{
    return  GetConstRefRaw< T >( RedirectedIndex( iIndex ) );
}


template< typename T >
void
IPixel::SetValue( uint8 iIndex, T iValue )
{
    SetValueRaw< T >( RedirectedIndex( iIndex ), iValue );
}


//--------------------------------------------------------------------------------------
//-------------------------------------------------------------------- Model Accesss API



/////////////////////////////////////////////////////
// FPixelValue
//--------------------------------------------------------------------------------------
//----------------------------------------------------------- Construction / Destruction
FPixelValue::~FPixelValue()
{
    delete [] mData;
}


FPixelValue::FPixelValue( uint32 iFormat, FColorProfile* iProfile )
    : tParent( iFormat, iProfile )
{
    mData = new tByte[ Depth() ];
    memset( mData, 0, Depth() );
}


FPixelValue::FPixelValue( const tByte* iData, tFormat iFormat, FColorProfile* iProfile )
    : tParent( iFormat, iProfile )
{
    mData = new tByte[ Depth() ];
    memcpy( mData, iData, Depth() );
}


FPixelValue::FPixelValue( const FPixelProxy& iProxy )
    : tParent( iProxy.Format(), iProxy.Profile() )
{
    mData = new tByte[ Depth() ];
    memcpy( mData, iProxy.Ptr(), Depth() );
}

/////////////////////////////////////////////////////
// FPixelValue
//--------------------------------------------------------------------------------------
//----------------------------------------------------------- Construction / Destruction
FPixelProxy::~FPixelProxy()
{
}


FPixelProxy::FPixelProxy( tByte* iData, tFormat iFormat, FColorProfile* iProfile )
    : tParent( iFormat, iProfile )
{
    ULIS2_ASSERT( iData, "Bad data provided." );
    mData = iData;
}


FPixelProxy::FPixelProxy( const tByte* iData, tFormat iFormat, FColorProfile* iProfile )
    : tParent( iFormat, iProfile )
{
    ULIS2_ASSERT( iData, "Bad data provided." );
    mData = const_cast< tByte* >( iData );
}


/////////////////////////////////////////////////////
// Template Instanciations
#define X_DO_A( i ) template i* IPixel::SamplePtrT< i >( uint8 );
#define X_DO_B( i ) template const i* IPixel::SamplePtrT< i >( uint8 ) const;
#define X_DO_C( i ) template i IPixel::GetValueRaw< i >( uint8 ) const;
#define X_DO_D( i ) template i& IPixel::GetRefRaw< i >( uint8 );
#define X_DO_E( i ) template const i& IPixel::GetConstRefRaw< i >( uint8 ) const;
#define X_DO_F( i ) template i IPixel::GetValue< i >( uint8 ) const;
#define X_DO_G( i ) template i& IPixel::GetRef< i >( uint8 );
#define X_DO_H( i ) template const i& IPixel::GetConstRef< i >( uint8 ) const;
#define X_DO_I( i ) template void IPixel::SetValueRaw< i >( uint8, i iValue );
#define X_DO_J( i ) template void IPixel::SetValue< i >( uint8, i iValue );
ULIS2_FOR_ALL_TYPES_DO( X_DO_A )
ULIS2_FOR_ALL_TYPES_DO( X_DO_B )
ULIS2_FOR_ALL_TYPES_DO( X_DO_C )
ULIS2_FOR_ALL_TYPES_DO( X_DO_D )
ULIS2_FOR_ALL_TYPES_DO( X_DO_E )
ULIS2_FOR_ALL_TYPES_DO( X_DO_F )
ULIS2_FOR_ALL_TYPES_DO( X_DO_G )
ULIS2_FOR_ALL_TYPES_DO( X_DO_H )
ULIS2_FOR_ALL_TYPES_DO( X_DO_I )
ULIS2_FOR_ALL_TYPES_DO( X_DO_J )
#undef X_DO_A
#undef X_DO_B
#undef X_DO_C
#undef X_DO_D
#undef X_DO_E
#undef X_DO_F
#undef X_DO_G
#undef X_DO_H
#undef X_DO_I
#undef X_DO_J


ULIS2_NAMESPACE_END

