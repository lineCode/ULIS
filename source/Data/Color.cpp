// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS3
*__________________
*
* @file         Pixel.cpp
* @author       Clement Berthaud
* @brief        This file provides the definition for the FColor classes.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include "Data/Color.h"
#include "Data/Pixel.h"

ULIS_NAMESPACE_BEGIN

namespace detail {

template< typename T >
struct TColorInitializer {
    template< typename U >
    static
    ULIS_FORCEINLINE
    void
    Run( FColor* oColor, const std::initializer_list< U > iValues ) {
        ULIS_ASSERT( iValues.size() < oColor->NumSamples(), "Bad input values" );
    }
};

template<>
struct TColorInitializer< uint8 > {
    template< typename U >
    static
    ULIS_FORCEINLINE
    void
    Run( FColor* oColor, const std::initializer_list< U > iValues ) {
        ULIS_ASSERT( iValues.size() < oColor->NumSamples(), "Bad input values" );
        for( int i = 0; i < iValues.size(); ++i )
            oColor->SetChannel8( i, ConvType< U, uint8 >( *( iValues.begin() + i ) ) );
    }
};

template<>
struct TColorInitializer< uint16 > {
    template< typename U >
    static
    ULIS_FORCEINLINE
    void
    Run( FColor* oColor, const std::initializer_list< U > iValues ) {
        ULIS_ASSERT( iValues.size() < oColor->NumSamples(), "Bad input values" );
        for( int i = 0; i < iValues.size(); ++i )
            oColor->SetChannel16( i, ConvType< U, uint16 >( *( iValues.begin() + i ) ) );
    }
};

template<>
struct TColorInitializer< uint32 > {
    template< typename U >
    static
    ULIS_FORCEINLINE
    void
    Run( FColor* oColor, const std::initializer_list< U > iValues ) {
        ULIS_ASSERT( iValues.size() < oColor->NumSamples(), "Bad input values" );
        for( int i = 0; i < iValues.size(); ++i )
            oColor->SetChannel32( i, ConvType< U, uint32 >( *( iValues.begin() + i ) ) );
    }
};

template<>
struct TColorInitializer< ufloat > {
    template< typename U >
    static
    ULIS_FORCEINLINE
    void
    Run( FColor* oColor, const std::initializer_list< U > iValues ) {
        ULIS_ASSERT( iValues.size() < oColor->NumSamples(), "Bad input values" );
        for( int i = 0; i < iValues.size(); ++i )
            oColor->SetChannelF( i, ConvType< U, ufloat >( *( iValues.begin() + i ) ) );
    }
};

template<>
struct TColorInitializer< udouble > {
    template< typename U >
    static
    ULIS_FORCEINLINE
    void
    Run( FColor* oColor, const std::initializer_list< U > iValues ) {
        ULIS_ASSERT( iValues.size() < oColor->NumSamples(), "Bad input values" );
        for( int i = 0; i < iValues.size(); ++i )
            oColor->SetChannelD( i, ConvType< U, udouble >( *( iValues.begin() + i ) ) );
    }
};

} // namespace detail

FColor::~FColor()
{
    if( mSignal )
        delete [] mSignal;
}

FColor::FColor()
    : ISample( new uint8[ BytesPerPixel() ], eFormat::Format_RGBA8 )
{
    memset( mSignal, 0, BytesPerPixel() );
}

FColor::FColor( eFormat iFormat, const FColorSpace* iColorSpace )
    : ISample( new uint8[ BytesPerPixel() ], iFormat, iColorSpace )
{
    memset( mSignal, 0, BytesPerPixel() );
}

FColor::FColor( const uint8* iData, eFormat iFormat, const FColorSpace* iColorSpace )
    : ISample( new uint8[ BytesPerPixel() ], iFormat, iColorSpace )
{
    memcpy( mSignal, iData, BytesPerPixel() );
}

FColor::FColor( const FPixel& iPixel )
    : ISample( new uint8[ BytesPerPixel() ], iPixel.Format(), iPixel.ColorSpace() )
{
    memcpy( mSignal, iPixel.Bits(), BytesPerPixel() );
}

FColor::FColor( const FColor& iValue )
    : ISample( new uint8[ BytesPerPixel() ], iValue.Format(), iValue.ColorSpace() )
{
    memcpy( mSignal, iValue.Bits(), BytesPerPixel() );
}


FColor::FColor( FColor&& iValue )
    : ISample( iValue.mSignal, iValue.Format(), iValue.ColorSpace() )
{
    iValue.mSignal = nullptr;
}

FColor&
FColor::operator=( const FColor& iOther ) {
    if( mSignal )
        delete [] mSignal;

    ReinterpretFormat( iOther.Format() );
    AssignColorSpace( iOther.ColorSpace() );
    mSignal = new uint8[ BytesPerPixel() ];
    memcpy( mSignal, iOther.Bits(), BytesPerPixel() );

    return  *this;
}


template< typename T >
FColor::FColor( eFormat iFormat, std::initializer_list< T > iValues, const FColorSpace* iColorSpace )
    : ISample( new uint8[ BytesPerPixel() ], iFormat, iColorSpace )
{
    #define TMP_CALL( iTypeID, iType, iE2, iE3 ) detail::TColorInitializer< iType >::Run< T >( this, iValues ); break;
    ULIS_SWITCH_FOR_ALL_DO( Type(), ULIS_FOR_ALL_TYPES_ID_DO, TMP_CALL, 0, 0, 0 )
    #undef TMP_CALL
}

//--------------------------------------------------------------------------------------
//------------------------------------------------------------ Named static constructors
//static
FColor
FColor::RGB( uint8 iR, uint8 iG, uint8 iB, uint8 iA )
{
    return  FColor( eFormat::Format_RGBA8, { iR, iG, iB, iA } );
}

//static
FColor
FColor::GreyA8( uint8 iGrey, uint8 iA )
{
    return  FColor( eFormat::Format_GA8, { iGrey, iA } );
}

//static
FColor
FColor::GreyA16( uint16 iGrey, uint16 iA )
{
    return  FColor( eFormat::Format_GA16, { iGrey, iA } );
}

//static
FColor
FColor::GreyA32( uint32 iGrey, uint32 iA )
{
    return  FColor( eFormat::Format_GA32, { iGrey, iA } );
}

//static
FColor
FColor::GreyAF( float iGrey, float iA )
{
    return  FColor( eFormat::Format_GAF, { iGrey, iA } );
}

//static
FColor
FColor::GreyAD( double iGrey, double iA )
{
    return  FColor( eFormat::Format_GAD, { iGrey, iA } );
}

//static
FColor
FColor::RGBA8( uint8 iR, uint8 iG, uint8 iB, uint8 iA )
{
    return  FColor( eFormat::Format_RGBA8, { iR, iG, iB, iA } );
}

//static
FColor
FColor::RGBA16( uint16 iR, uint16 iG, uint16 iB, uint16 iA )
{
    return  FColor( eFormat::Format_RGBA16, { iR, iG, iB, iA } );
}

//static
FColor
FColor::RGBA32( uint32 iR, uint32 iG, uint32 iB, uint32 iA )
{
    return  FColor( eFormat::Format_RGBA32, { iR, iG, iB, iA } );
}

//static
FColor
FColor::RGBAF( float iR, float iG, float iB, float iA )
{
    return  FColor( eFormat::Format_RGBAF, { iR, iG, iB, iA } );
}

//static
FColor
FColor::RGBAD( double iR, double iG, double iB, double iA )
{
    return  FColor( eFormat::Format_RGBAD, { iR, iG, iB, iA } );
}

//static
FColor
FColor::HSVA8( uint8 iH, uint8 iS, uint8 iV, uint8 iA )
{
    return  FColor( eFormat::Format_HSVA8, { iH, iS, iV, iA } );
}

//static
FColor
FColor::HSVA16( uint16 iH, uint16 iS, uint16 iV, uint16 iA )
{
    return  FColor( eFormat::Format_HSVA16, { iH, iS, iV, iA } );
}

//static
FColor
FColor::HSVA32( uint32 iH, uint32 iS, uint32 iV, uint32 iA )
{
    return  FColor( eFormat::Format_HSVA32, { iH, iS, iV, iA } );
}

//static
FColor
FColor::HSVAF( float iH, float iS, float iV, float iA )
{
    return  FColor( eFormat::Format_HSVAF, { iH, iS, iV, iA } );
}

//static
FColor
FColor::HSVAD( double iH, double iS, double iV, double iA )
{
    return  FColor( eFormat::Format_HSVAD, { iH, iS, iV, iA } );
}

//static
FColor
FColor::HSLA8( uint8 iH, uint8 iS, uint8 iL, uint8 iA )
{
    return  FColor( eFormat::Format_HSLA8, { iH, iS, iL, iA } );
}

//static
FColor
FColor::HSLA16( uint16 iH, uint16 iS, uint16 iL, uint16 iA )
{
    return  FColor( eFormat::Format_HSLA16, { iH, iS, iL, iA } );
}

//static
FColor
FColor::HSLA32( uint32 iH, uint32 iS, uint32 iL, uint32 iA )
{
    return  FColor( eFormat::Format_HSLA32, { iH, iS, iL, iA } );
}

//static
FColor
FColor::HSLAF( float iH, float iS, float iL, float iA )
{
    return  FColor( eFormat::Format_HSLAF, { iH, iS, iL, iA } );
}

//static
FColor
FColor::HSLAD( double iH, double iS, double iL, double iA )
{
    return  FColor( eFormat::Format_HSLAD, { iH, iS, iL, iA } );
}

//static
FColor
FColor::CMYA8( uint8 iC, uint8 iM, uint8 iY, uint8 iA )
{
    return  FColor( eFormat::Format_CMYA8, { iC, iM, iY, iA } );
}

//static
FColor
FColor::CMYA16( uint16 iC, uint16 iM, uint16 iY, uint16 iA )
{
    return  FColor( eFormat::Format_CMYA16, { iC, iM, iY, iA } );
}

//static
FColor
FColor::CMYA32( uint32 iC, uint32 iM, uint32 iY, uint32 iA )
{
    return  FColor( eFormat::Format_CMYA32, { iC, iM, iY, iA } );
}

//static
FColor
FColor::CMYAF( float iC, float iM, float iY, float iA )
{
    return  FColor( eFormat::Format_CMYAF, { iC, iM, iY, iA } );
}

//static
FColor
FColor::CMYAD( double iC, double iM, double iY, double iA )
{
    return  FColor( eFormat::Format_CMYAD, { iC, iM, iY, iA } );
}

//static
FColor
FColor::CMYKA8( uint8 iC, uint8 iM, uint8 iY, uint8 iK, uint8 iA )
{
    return  FColor( eFormat::Format_CMYKA8, { iC, iM, iY, iK, iA } );
}

//static
FColor
FColor::CMYKA16( uint16 iC, uint16 iM, uint16 iY, uint16 iK, uint16 iA )
{
    return  FColor( eFormat::Format_CMYKA16, { iC, iM, iY, iK, iA } );
}

//static
FColor
FColor::CMYKA32( uint32 iC, uint32 iM, uint32 iY, uint32 iK, uint32 iA )
{
    return  FColor( eFormat::Format_CMYKA32, { iC, iM, iY, iK, iA } );
}

//static
FColor
FColor::CMYKAF( float iC, float iM, float iY, float iK, float iA )
{
    return  FColor( eFormat::Format_CMYKAF, { iC, iM, iY, iK, iA } );
}

//static
FColor
FColor::CMYKAD( double iC, double iM, double iY, double iK, double iA )
{
    return  FColor( eFormat::Format_CMYKAD, { iC, iM, iY, iK, iA } );
}

//static
FColor
FColor::YUVA8( uint8 iY, uint8 iU, uint8 iV, uint8 iA )
{
    return  FColor( eFormat::Format_YUVA8, { iY, iU, iV, iA } );
}

//static
FColor
FColor::YUVA16( uint16 iY, uint16 iU, uint16 iV, uint16 iA )
{
    return  FColor( eFormat::Format_YUVA16, { iY, iU, iV, iA } );
}

//static
FColor
FColor::YUVA32( uint32 iY, uint32 iU, uint32 iV, uint32 iA )
{
    return  FColor( eFormat::Format_YUVA32, { iY, iU, iV, iA } );
}

//static
FColor
FColor::YUVAF( float iY, float iU, float iV, float iA )
{
    return  FColor( eFormat::Format_YUVAF, { iY, iU, iV, iA } );
}

//static
FColor
FColor::YUVAD( double iY, double iU, double iV, double iA )
{
    return  FColor( eFormat::Format_YUVAD, { iY, iU, iV, iA } );
}

//static
FColor
FColor::LabA8( uint8 iL, uint8 ia, uint8 ib, uint8 iA )
{
    return  FColor( eFormat::Format_LabA8, { iL, ia, ib, iA } );
}

//static
FColor
FColor::LabA16( uint16 iL, uint16 ia, uint16 ib, uint16 iA )
{
    return  FColor( eFormat::Format_LabA16, { iL, ia, ib, iA } );
}

//static
FColor
FColor::LabA32( uint32 iL, uint32 ia, uint32 ib, uint32 iA )
{
    return  FColor( eFormat::Format_LabA32, { iL, ia, ib, iA } );
}

//static
FColor
FColor::LabAF( float iL, float ia, float ib, float iA )
{
    return  FColor( eFormat::Format_LabAF, { iL, ia, ib, iA } );
}

//static
FColor
FColor::LabAD( double iL, double ia, double ib, double iA )
{
    return  FColor( eFormat::Format_LabAD, { iL, ia, ib, iA } );
}

//static
FColor
FColor::XYZA8( uint8 iX, uint8 iY, uint8 iZ, uint8 iA )
{
    return  FColor( eFormat::Format_XYZA8, { iX, iY, iZ, iA } );
}

//static
FColor
FColor::XYZA16( uint16 iX, uint16 iY, uint16 iZ, uint16 iA )
{
    return  FColor( eFormat::Format_XYZA16, { iX, iY, iZ, iA } );
}

//static
FColor
FColor::XYZA32( uint32 iX, uint32 iY, uint32 iZ, uint32 iA )
{
    return  FColor( eFormat::Format_XYZA32, { iX, iY, iZ, iA } );
}

//static
FColor
FColor::XYZAF( float iX, float iY, float iZ, float iA )
{
    return  FColor( eFormat::Format_XYZAF, { iX, iY, iZ, iA } );
}

//static
FColor
FColor::XYZAD( double iX, double iY, double iZ, double iA )
{
    return  FColor( eFormat::Format_XYZAD, { iX, iY, iZ, iA } );
}

//static
FColor
FColor::YxyA8( uint8 iY, uint8 ix, uint8 iy, uint8 iA )
{
    return  FColor( eFormat::Format_YxyA8, { iY, ix, iy, iA } );
}

//static
FColor
FColor::YxyA16( uint16 iY, uint16 ix, uint16 iy, uint16 iA )
{
    return  FColor( eFormat::Format_YxyA16, { iY, ix, iy, iA } );
}

//static
FColor
FColor::YxyA32( uint32 iY, uint32 ix, uint32 iy, uint32 iA )
{
    return  FColor( eFormat::Format_YxyA32, { iY, ix, iy, iA } );
}

//static
FColor
FColor::YxyAF( float iY, float ix, float iy, float iA )
{
    return  FColor( eFormat::Format_YxyAF, { iY, ix, iy, iA } );
}

//static
FColor
FColor::YxyAD( double iY, double ix, double iy, double iA )
{
    return  FColor( eFormat::Format_YxyAD, { iY, ix, iy, iA } );
}

template ULIS_API FColor::FColor( eFormat, std::initializer_list< int >, const FColorSpace* );
template ULIS_API FColor::FColor( eFormat, std::initializer_list< uint8 >, const FColorSpace* );
template ULIS_API FColor::FColor( eFormat, std::initializer_list< uint16 >, const FColorSpace* );
template ULIS_API FColor::FColor( eFormat, std::initializer_list< uint32 >, const FColorSpace* );
template ULIS_API FColor::FColor( eFormat, std::initializer_list< ufloat >, const FColorSpace* );
template ULIS_API FColor::FColor( eFormat, std::initializer_list< udouble >, const FColorSpace* );

ULIS_NAMESPACE_END

