// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS3
*__________________
*
* @file         ToGrey.ipp
* @author       Clement Berthaud
* @brief        This file provides the definition for model conversion functions.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"
#include "Conv/ConvBuffer.h"
#include "Conv/ConvHelpers.h"
#include "Data/Format.h"
#include "Data/Pixel.h"

ULIS3_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
// To Grey
//--------------------------------------------------------------------------------------
//---------------------------------------------------------------------------- From Grey
template< typename T1, typename T2 > void ConvBufferGreyToGrey( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen ) {
    while( iLen-- ) {
        U2_DREF_DST( 0 ) = ConvType< T1, T2 >( U2_DREF_SRC( 0 ) );
        U2_FWD_ALPHA;
        iSrc += iSrcFormat->BPP;
        iDst += iDstFormat->BPP;
    }
}

//--------------------------------------------------------------------------------------
//----------------------------------------------------------------------------- From RGB
template< typename T1, typename T2 > void ConvBufferRGBToGrey( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen ) {
    while( iLen-- ) {
        ufloat r = ConvType< T1, ufloat >( U2_DREF_SRC( 0 ) );
        ufloat g = ConvType< T1, ufloat >( U2_DREF_SRC( 1 ) );
        ufloat b = ConvType< T1, ufloat >( U2_DREF_SRC( 2 ) );
        ufloat grey = 0.3f * r + 0.59f * g + 0.11f * b;
        U2_DREF_DST( 0 ) = ConvType< ufloat, T2 >( grey );
        U2_FWD_ALPHA;
        iSrc += iSrcFormat->BPP;
        iDst += iDstFormat->BPP;
    }
}

//--------------------------------------------------------------------------------------
//----------------------------------------------------------------------------- From HSV
template< typename T1, typename T2 > void ConvBufferHSVToGrey( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen ) {
    FColor temp( ULIS3_FORMAT_RGBAF );
    while( iLen-- ) {
        ConvBufferHSVToRGB< T1, ufloat >( iSrcFormat, iSrc, temp.FormatInfo(), temp.Bits(), 1 );
        ConvBufferRGBToGrey< ufloat, T2 >( temp.FormatInfo(), temp.Bits(), iDstFormat, iDst, 1 );
        iSrc += iSrcFormat->BPP;
        iDst += iDstFormat->BPP;
    }
}

//--------------------------------------------------------------------------------------
//----------------------------------------------------------------------------- From HSL
template< typename T1, typename T2 > void ConvBufferHSLToGrey( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen ) {
    FColor temp( ULIS3_FORMAT_RGBAF );
    while( iLen-- ) {
        ConvBufferHSLToRGB< T1, ufloat >( iSrcFormat, iSrc, temp.FormatInfo(), temp.Bits(), 1 );
        ConvBufferRGBToGrey< ufloat, T2 >( temp.FormatInfo(), temp.Bits(), iDstFormat, iDst, 1 );
        iSrc += iSrcFormat->BPP;
        iDst += iDstFormat->BPP;
    }
}

//--------------------------------------------------------------------------------------
//----------------------------------------------------------------------------- From CMY
template< typename T1, typename T2 > void ConvBufferCMYToGrey( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen ) {
    FColor temp( ULIS3_FORMAT_RGBAF );
    while( iLen-- ) {
        ConvBufferCMYToRGB< T1, ufloat >( iSrcFormat, iSrc, temp.FormatInfo(), temp.Bits(), 1 );
        ConvBufferRGBToGrey< ufloat, T2 >( temp.FormatInfo(), temp.Bits(), iDstFormat, iDst, 1 );
        iSrc += iSrcFormat->BPP;
        iDst += iDstFormat->BPP;
    }
}

//--------------------------------------------------------------------------------------
//---------------------------------------------------------------------------- From CMYK
template< typename T1, typename T2 > void ConvBufferCMYKToGrey( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen ) {
    FColor temp( ULIS3_FORMAT_RGBAF );
    while( iLen-- ) {
        ConvBufferCMYKToRGB< T1, ufloat >( iSrcFormat, iSrc, temp.FormatInfo(), temp.Bits(), 1 );
        ConvBufferRGBToGrey< ufloat, T2 >( temp.FormatInfo(), temp.Bits(), iDstFormat, iDst, 1 );
        iSrc += iSrcFormat->BPP;
        iDst += iDstFormat->BPP;
    }
}

//--------------------------------------------------------------------------------------
//----------------------------------------------------------------------------- From YUV
template< typename T1, typename T2 > void ConvBufferYUVToGrey( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen ) {
    FColor temp( ULIS3_FORMAT_RGBAF );
    while( iLen-- ) {
        ConvBufferYUVToRGB< T1, ufloat >( iSrcFormat, iSrc, temp.FormatInfo(), temp.Bits(), 1 );
        ConvBufferRGBToGrey< ufloat, T2 >( temp.FormatInfo(), temp.Bits(), iDstFormat, iDst, 1 );
        iSrc += iSrcFormat->BPP;
        iDst += iDstFormat->BPP;
    }
}

//--------------------------------------------------------------------------------------
//----------------------------------------------------------------------------- From Lab
template< typename T1, typename T2 > void ConvBufferLabToGrey( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen ) {
    FColor temp( ULIS3_FORMAT_RGBAF );
    while( iLen-- ) {
        ConvBufferLabToRGB< T1, ufloat >( iSrcFormat, iSrc, temp.FormatInfo(), temp.Bits(), 1 );
        ConvBufferRGBToGrey< ufloat, T2 >( temp.FormatInfo(), temp.Bits(), iDstFormat, iDst, 1 );
        iSrc += iSrcFormat->BPP;
        iDst += iDstFormat->BPP;
    }
}

//--------------------------------------------------------------------------------------
//----------------------------------------------------------------------------- From XYZ
template< typename T1, typename T2 > void ConvBufferXYZToGrey( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen ) {
    FColor temp( ULIS3_FORMAT_RGBAF );
    while( iLen-- ) {
        ConvBufferXYZToRGB< T1, ufloat >( iSrcFormat, iSrc, temp.FormatInfo(), temp.Bits(), 1 );
        ConvBufferRGBToGrey< ufloat, T2 >( temp.FormatInfo(), temp.Bits(), iDstFormat, iDst, 1 );
        iSrc += iSrcFormat->BPP;
        iDst += iDstFormat->BPP;
    }
}

//--------------------------------------------------------------------------------------
//----------------------------------------------------------------------------- From Yxy
template< typename T1, typename T2 > void ConvBufferYxyToGrey( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen ) {
    FColor temp( ULIS3_FORMAT_RGBAF );
    while( iLen-- ) {
        ConvBufferYxyToRGB< T1, ufloat >( iSrcFormat, iSrc, temp.FormatInfo(), temp.Bits(), 1 );
        ConvBufferRGBToGrey< ufloat, T2 >( temp.FormatInfo(), temp.Bits(), iDstFormat, iDst, 1 );
        iSrc += iSrcFormat->BPP;
        iDst += iDstFormat->BPP;
    }
}

ULIS3_NAMESPACE_END

