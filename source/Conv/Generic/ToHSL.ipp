// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS3
*__________________
*
* @file         ToHSL.ipp
* @author       Clement Berthaud
* @brief        This file provides the definition for model conversion functions.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"
#include "Conv/ConvBuffer.h"
#include "Conv/ConvHelpers.h"
#include "Data/Color.h"
#include "Data/Format.h"
#include "Data/Pixel.h"
#include "Data/Sample.h"
#include "Maths/Maths.h"
#include <cmath>

ULIS3_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
// To HSL
//--------------------------------------------------------------------------------------
//---------------------------------------------------------------------------- From Grey
template< typename T, typename U >
void
ConvBufferGreyToHSL( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen )
{
    FColor temp( ULIS3_FORMAT_RGBAF );
    while( iLen-- )
    {
        ConvBufferGreyToRGB< T, ufloat >( iSrcFormat, iSrc, temp.FormatInfo(), temp.Bits(), 1 );
        ConvBufferRGBToHSL< ufloat, U >( temp.FormatInfo(), temp.Bits(), iDstFormat, iDst, 1 );
        iSrc += iSrcFormat.BPP;
        iDst += iDstFormat.BPP;
    }
}

//--------------------------------------------------------------------------------------
//----------------------------------------------------------------------------- From RGB
template< typename T, typename U >
void
ConvBufferRGBToHSL( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen )
{
    while( iLen-- )
    {
        ufloat r = ConvType< T, ufloat >( U2_DREF_SRC( 0 ) );
        ufloat g = ConvType< T, ufloat >( U2_DREF_SRC( 1 ) );
        ufloat b = ConvType< T, ufloat >( U2_DREF_SRC( 2 ) );
        float cmin = FMaths::Min3( r, g, b );
        float cmax = FMaths::Max3( r, g, b );
        float delta = cmax - cmin;
        float deltaAdd = cmax + cmin;
        float h = 0.f;
        float s = 0.f;
        float l = 0.f;
        l = ( deltaAdd ) / 2.0f;
        if ( delta < FMaths::kEpsilonf ){
            h = s = 0.f;
        } else {
            s = ( l < 0.5f ) ? delta / deltaAdd : delta / ( 2.0f - deltaAdd );
            float deltaR = ( ( ( cmax - r ) / 6.0f ) + ( delta / 2.0f ) ) / delta;
            float deltaG = ( ( ( cmax - g ) / 6.0f ) + ( delta / 2.0f ) ) / delta;
            float deltaB = ( ( ( cmax - b ) / 6.0f ) + ( delta / 2.0f ) ) / delta;
                 if( fabs( r - cmax ) < FMaths::kEpsilonf )   h = deltaB - deltaG;
            else if( fabs( g - cmax ) < FMaths::kEpsilonf )   h = ( 1.0f / 3.0f ) + deltaR - deltaB;
            else if( fabs( b - cmax ) < FMaths::kEpsilonf )   h = ( 2.0f / 3.0f ) + deltaG - deltaR;

            if( h < 0.0 ) h += 1.0;
            if( h > 1.0 ) h -= 1.0;
        }

        U2_DREF_DST( 0 ) = ConvType< ufloat, U >( h );
        U2_DREF_DST( 1 ) = ConvType< ufloat, U >( s );
        U2_DREF_DST( 2 ) = ConvType< ufloat, U >( l );
        U2_FWD_ALPHA;
        iSrc += iSrcFormat.BPP;
        iDst += iDstFormat.BPP;
    }
}

//--------------------------------------------------------------------------------------
//----------------------------------------------------------------------------- From HSV
template< typename T, typename U >
void
ConvBufferHSVToHSL( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen )
{
    FColor temp( ULIS3_FORMAT_RGBAF );
    while( iLen-- )
    {
        ConvBufferHSVToRGB< T, ufloat >( iSrcFormat, iSrc, temp.FormatInfo(), temp.Bits(), 1 );
        ConvBufferRGBToHSL< ufloat, U >( temp.FormatInfo(), temp.Bits(), iDstFormat, iDst, 1 );
        iSrc += iSrcFormat.BPP;
        iDst += iDstFormat.BPP;
    }
}

//--------------------------------------------------------------------------------------
//----------------------------------------------------------------------------- From HSL
template< typename T, typename U >
void
ConvBufferHSLToHSL( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen )
{
    while( iLen-- )
    {
        U2_DREF_DST( 0 ) = ConvType< T, U >( U2_DREF_SRC( 0 ) );
        U2_DREF_DST( 1 ) = ConvType< T, U >( U2_DREF_SRC( 1 ) );
        U2_DREF_DST( 2 ) = ConvType< T, U >( U2_DREF_SRC( 2 ) );
        U2_FWD_ALPHA;
        iSrc += iSrcFormat.BPP;
        iDst += iDstFormat.BPP;
    }
}

//--------------------------------------------------------------------------------------
//----------------------------------------------------------------------------- From CMY
template< typename T, typename U >
void
ConvBufferCMYToHSL( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen )
{
    FColor temp( ULIS3_FORMAT_RGBAF );
    while( iLen-- )
    {
        ConvBufferCMYToRGB< T, ufloat >( iSrcFormat, iSrc, temp.FormatInfo(), temp.Bits(), 1 );
        ConvBufferRGBToHSL< ufloat, U >( temp.FormatInfo(), temp.Bits(), iDstFormat, iDst, 1 );
        iSrc += iSrcFormat.BPP;
        iDst += iDstFormat.BPP;
    }
}

//--------------------------------------------------------------------------------------
//---------------------------------------------------------------------------- From CMYK
template< typename T, typename U >
void
ConvBufferCMYKToHSL( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen )
{
    FColor temp( ULIS3_FORMAT_RGBAF );
    while( iLen-- )
    {
        ConvBufferCMYKToRGB< T, ufloat >( iSrcFormat, iSrc, temp.FormatInfo(), temp.Bits(), 1 );
        ConvBufferRGBToHSL< ufloat, U >( temp.FormatInfo(), temp.Bits(), iDstFormat, iDst, 1 );
        iSrc += iSrcFormat.BPP;
        iDst += iDstFormat.BPP;
    }
}

//--------------------------------------------------------------------------------------
//----------------------------------------------------------------------------- From YUV
template< typename T, typename U >
void
ConvBufferYUVToHSL( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen )
{
    FColor temp( ULIS3_FORMAT_RGBAF );
    while( iLen-- )
    {
        ConvBufferYUVToRGB< T, ufloat >( iSrcFormat, iSrc, temp.FormatInfo(), temp.Bits(), 1 );
        ConvBufferRGBToHSL< ufloat, U >( temp.FormatInfo(), temp.Bits(), iDstFormat, iDst, 1 );
        iSrc += iSrcFormat.BPP;
        iDst += iDstFormat.BPP;
    }
}

//--------------------------------------------------------------------------------------
//----------------------------------------------------------------------------- From Lab
template< typename T, typename U >
void
ConvBufferLabToHSL( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen )
{
    FColor temp( ULIS3_FORMAT_RGBAF );
    while( iLen-- )
    {
        ConvBufferLabToRGB< T, ufloat >( iSrcFormat, iSrc, temp.FormatInfo(), temp.Bits(), 1 );
        ConvBufferRGBToHSL< ufloat, U >( temp.FormatInfo(), temp.Bits(), iDstFormat, iDst, 1 );
        iSrc += iSrcFormat.BPP;
        iDst += iDstFormat.BPP;
    }
}

//--------------------------------------------------------------------------------------
//----------------------------------------------------------------------------- From XYZ
template< typename T, typename U >
void
ConvBufferXYZToHSL( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen )
{
    FColor temp( ULIS3_FORMAT_RGBAF );
    while( iLen-- )
    {
        ConvBufferXYZToRGB< T, ufloat >( iSrcFormat, iSrc, temp.FormatInfo(), temp.Bits(), 1 );
        ConvBufferRGBToHSL< ufloat, U >( temp.FormatInfo(), temp.Bits(), iDstFormat, iDst, 1 );
        iSrc += iSrcFormat.BPP;
        iDst += iDstFormat.BPP;
    }
}

//--------------------------------------------------------------------------------------
//----------------------------------------------------------------------------- From Yxy
template< typename T, typename U >
void
ConvBufferYxyToHSL( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen )
{
    FColor temp( ULIS3_FORMAT_RGBAF );
    while( iLen-- )
    {
        ConvBufferYxyToRGB< T, ufloat >( iSrcFormat, iSrc, temp.FormatInfo(), temp.Bits(), 1 );
        ConvBufferRGBToHSL< ufloat, U >( temp.FormatInfo(), temp.Bits(), iDstFormat, iDst, 1 );
        iSrc += iSrcFormat.BPP;
        iDst += iDstFormat.BPP;
    }
}

ULIS3_NAMESPACE_END

