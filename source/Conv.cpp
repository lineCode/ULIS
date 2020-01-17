// Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Conv.cpp
* @author       Clement Berthaud
* @brief        This file provides the definitions for the Conv entry point functions.
* @copyright    Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include "Conv.h"
#include "Pixel.h"
#include "Maths.h"
#include "Illuminants.h"
#include "Models.h"
#include "ColorProfile.h"
#include "ProfileRegistry.h"
#include "lcms2.h"
#include <limits>

ULIS2_NAMESPACE_BEGIN
float srgb2linear( float iValue )
{
    if( iValue <= 0.0f )
        return  0.0f;
    else if( iValue >= 1.0f )
        return  1.0f;
    else if( iValue < 0.04045f )
        return  iValue / 12.92f;
    else
        return  powf( ( iValue + 0.055f) / 1.055f, 2.4f );
}


float linear2srgb( float iValue )
{
    if( iValue <= 0.0f )
        return  0.0f;
    else if( iValue >= 1.0f )
        return  1.0f;
    else if( iValue < 0.0031308f )
        return  iValue * 12.92f;
    else
        return  powf( iValue, 1.0f / 2.4f ) * 1.055f - 0.055f;
}


void
ProfileConv( const IPixel& iSrc, IPixel& iDst, const FProfileRegistry& iProfileRegistry, uint32 iIntent )
{
    tFormat src_ul2_format = iSrc.Format();
    tFormat dst_ul2_format = iDst.Format();
    tFormat src_lcms2_format = F42( src_ul2_format );
    tFormat dst_lcms2_format = F42( dst_ul2_format );
    FColorProfile* src_profile = iSrc.Profile();
    FColorProfile* dst_profile = iDst.Profile();
    if( src_profile == nullptr ) src_profile = iProfileRegistry.GetDefaultProfileForModel( iSrc.Model() );
    if( dst_profile == nullptr ) dst_profile = iProfileRegistry.GetDefaultProfileForModel( iDst.Model() );

    cmsHPROFILE hInProfile  = src_profile->ProfileHandle();
    cmsHPROFILE hOutProfile = dst_profile->ProfileHandle();
    cmsHTRANSFORM hTransform;
    hTransform = cmsCreateTransform( hInProfile
                                   , src_lcms2_format
                                   , hOutProfile
                                   , dst_lcms2_format
                                   , INTENT_PERCEPTUAL, 0 );
    cmsDoTransform( hTransform, iSrc.Ptr(), iDst.Ptr(), 1 );
    cmsDeleteTransform( hTransform );
}

// TODO: maybe use such linearized table and bit shifting to find the index with one indirection rather than a multi switch approach
// This could be used to retrieve the instanciated function pointer and avoid search too !
// typedef void (*fpConversionFunction)( const IPixel& /* src */, IPixel& /* dst */ );
// fpConversionFunction table[5][5][10][10];

template< typename T1, typename T2 >
void
ToGrey( const IPixel& iSrc, IPixel& iDst )
{
    switch( iSrc.Model() )
    {
        case CM_ANY:
        {
            ULIS2_CRASH_DELIBERATE;
            return;
        }

        case CM_GREY:
        {
            iDst.SetGrey< T2 >( ConvType< T1, T2 >( iSrc.G< T1 >() ) );
            iDst.SetA< T2 >( ConvType< T1, T2 >( iSrc.A< T1 >() ) );
            return;
        }

        case CM_RGB:
        {
            float r = ConvType< T1, float >( iSrc.R< T1 >() );
            float g = ConvType< T1, float >( iSrc.G< T1 >() );
            float b = ConvType< T1, float >( iSrc.B< T1 >() );
            float _grey = ( r + g + b ) / 3.0f;
            iDst.SetGrey< T2 >( ConvType< float, T2 >( _grey ) );
            iDst.SetA< T2 >( ConvType< T1, T2 >( iSrc.A< T1 >() ) );
            return;
        }

        case CM_HSV:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToGrey< float, T2 >( temp, iDst );
            return;
        }

        case CM_HSL:
        {
            float _grey = ConvType< T1, float >( iSrc.Lightness< T1 >() );
            iDst.SetGrey< T2 >( ConvType< float, T2 >( _grey ) );
            iDst.SetA< T2 >( ConvType< T1, T2 >( iSrc.A< T1 >() ) );
            return;
        }

        case CM_CMY:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToGrey< float, T2 >( temp, iDst );
            return;
        }

        case CM_CMYK:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToGrey< float, T2 >( temp, iDst );
            return;
        }

        case CM_YUV:
        {
            float _grey = ConvType< T1, float >( iSrc.Luma< T1 >() );
            iDst.SetGrey< T2 >( ConvType< float, T2 >( _grey ) );
            iDst.SetA< T2 >( ConvType< T1, T2 >( iSrc.A< T1 >() ) );
            return;
        }

        case CM_Lab:
        {
            float _grey = ConvType< T1, float >( iSrc.Luma< T1 >() );
            iDst.SetGrey< T2 >( ConvType< float, T2 >( _grey ) );
            iDst.SetA< T2 >( ConvType< T1, T2 >( iSrc.A< T1 >() ) );
            return;
        }

        case CM_XYZ:
        {
            float _grey = ConvType< T1, float >( iSrc.Y< T1 >() );
            iDst.SetGrey< T2 >( ConvType< float, T2 >( _grey ) );
            iDst.SetA< T2 >( ConvType< T1, T2 >( iSrc.A< T1 >() ) );
            return;
        }

        case CM_Yxy:
        {
            float _grey = ConvType< T1, float >( iSrc.Luma< T1 >() );
            iDst.SetGrey< T2 >( ConvType< float, T2 >( _grey ) );
            iDst.SetA< T2 >( ConvType< T1, T2 >( iSrc.A< T1 >() ) );
            return;
        }
    }
}


template< typename T1, typename T2 >
void
ToRGB( const IPixel& iSrc, IPixel& iDst )
{
    switch( iSrc.Model() )
    {
        case CM_ANY:
        {
            ULIS2_CRASH_DELIBERATE;
            return;
        }

        case CM_GREY:
        {
            T2 _grey    = ConvType< T1, T2 >( iSrc.Grey< T1 >() );
            iDst.SetR< T2 >( _grey );
            iDst.SetG< T2 >( _grey );
            iDst.SetB< T2 >( _grey );
            iDst.SetA< T2 >( ConvType< T1, T2 >( iSrc.A< T1 >() ) );
            return;
        }

        case CM_RGB:
        {
            iDst.SetR< T2 >( ConvType< T1, T2 >( iSrc.R< T1 >() ) );
            iDst.SetG< T2 >( ConvType< T1, T2 >( iSrc.G< T1 >() ) );
            iDst.SetB< T2 >( ConvType< T1, T2 >( iSrc.B< T1 >() ) );
            iDst.SetA< T2 >( ConvType< T1, T2 >( iSrc.A< T1 >() ) );
            return;
        }

        case CM_HSV:
        {
            T1 _H = iSrc.Hue< T1 >();
            T1 _S = iSrc.Saturation< T1 >();
            T1 _V = iSrc.Value< T1 >();
            float h = ConvType< T1, float >( _H );
            float s = ConvType< T1, float >( _S );
            float v = ConvType< T1, float >( _V );
            float r, g, b;
            r = g = b = 0.f;
            float var_h = 0.f;
            float var_i = 0.f;
            float var_1 = 0.f;
            float var_2 = 0.f;
            float var_3 = 0.f;
            if ( s == 0 )
            {
               r = v;
               g = v;
               b = v;
            }
            else
            {
               var_h = h * 6;
               if ( var_h == 6 ) var_h = 0 ;
               var_i = var_h;
               var_1 = v * ( 1 - s );
               var_2 = v * ( 1 - s * ( var_h - var_i ) );
               var_3 = v * ( 1 - s * ( 1 - ( var_h - var_i ) ) );

               if      ( var_i == 0 ) { r = v     ; g = var_3 ; b = var_1 ; }
               else if ( var_i == 1 ) { r = var_2 ; g = v     ; b = var_1 ; }
               else if ( var_i == 2 ) { r = var_1 ; g = v     ; b = var_3 ; }
               else if ( var_i == 3 ) { r = var_1 ; g = var_2 ; b = v     ; }
               else if ( var_i == 4 ) { r = var_3 ; g = var_1 ; b = v     ; }
               else                   { r = v     ; g = var_1 ; b = var_2 ; }
            }
            iDst.SetR< T2 >( ConvType< float, T2 >( r ) );
            iDst.SetG< T2 >( ConvType< float, T2 >( g ) );
            iDst.SetB< T2 >( ConvType< float, T2 >( b ) );
            iDst.SetA< T2 >( ConvType< T1, T2 >( iSrc.A< T1 >() ) );
            return;
        }

        case CM_HSL:
        {
            T1 _H = iSrc.Hue< T1 >();
            T1 _S = iSrc.Saturation< T1 >();
            T1 _L = iSrc.Lightness< T1 >();
            float h = ConvType< T1, float >( _H ) * 360;
            float s = ConvType< T1, float >( _S );
            float l = ConvType< T1, float >( _L );
            float r, g, b;
            r = g = b = 0.f;
            float var_h = h / 60;
            if ( var_h == 6 ) var_h = 0;
            int var_i = int( var_h );
            float C = ( 1.f - fabs( 2.f * l - 1.f ) ) * s;
            float X = float( C * ( 1 - fabs( fmod( var_h, 2 ) - 1 ) ) );
            float m = l - C / 2;
            if      ( var_i == 0 ) { r = C; g = X; b = 0; }
            else if ( var_i == 1 ) { r = X; g = C; b = 0; }
            else if ( var_i == 2 ) { r = 0; g = C; b = X; }
            else if ( var_i == 3 ) { r = 0; g = X; b = C; }
            else if ( var_i == 4 ) { r = X; g = 0; b = C; }
            else                   { r = C; g = 0; b = X; }
            iDst.SetR< T2 >( ConvType< float, T2 >( r + m ) );
            iDst.SetG< T2 >( ConvType< float, T2 >( g + m ) );
            iDst.SetB< T2 >( ConvType< float, T2 >( b + m ) );
            iDst.SetA< T2 >( ConvType< T1, T2 >( iSrc.A< T1 >() ) );
            return;
        }

        case CM_CMY:
        {
            T2 max = MaxType< T2 >();
            iDst.SetCyan< T2 >(     max - ConvType< T1, T2 >( iSrc.R< T1 >() ) );
            iDst.SetMagenta< T2 >(  max - ConvType< T1, T2 >( iSrc.G< T1 >() ) );
            iDst.SetYellow< T2 >(   max - ConvType< T1, T2 >( iSrc.B< T1 >() ) );
            iDst.SetAlpha< T2 >( ConvType< T1, T2 >( iSrc.A< T1 >() ) );
            return;
        }

        case CM_CMYK:
        {
            float c = ConvType< T1, float >( iSrc.Cyan< T1 >() );
            float m = ConvType< T1, float >( iSrc.Magenta< T1 >() );
            float y = ConvType< T1, float >( iSrc.Yellow< T1 >() );
            float k = ConvType< T1, float >( iSrc.Key< T1 >() );
            float r = 1.f - ( c * ( 1.f - k ) + k );
            float g = 1.f - ( m * ( 1.f - k ) + k );
            float b = 1.f - ( y * ( 1.f - k ) + k );
            iDst.SetR< T2 >( ConvType< float, T2 >( r ) );
            iDst.SetG< T2 >( ConvType< float, T2 >( g ) );
            iDst.SetB< T2 >( ConvType< float, T2 >( b ) );
            iDst.SetA< T2 >( ConvType< T1, T2 >( iSrc.A< T1 >() ) );
            return;
        }

        case CM_YUV:
        {
            float y = ConvType< T1, float >( iSrc.Luma< T1 >() );
            float u = ConvType< T1, float >( iSrc.U< T1 >() );
            float v = ConvType< T1, float >( iSrc.V< T1 >() );
            float r = linear2srgb( y + 1.14f * v );
            float g = linear2srgb( y - 0.395f * u - 0.581f * v );
            float b = linear2srgb( y + 2.033f * u );
            iDst.SetR< T2 >( ConvType< float, T2 >( r ) );
            iDst.SetG< T2 >( ConvType< float, T2 >( g ) );
            iDst.SetB< T2 >( ConvType< float, T2 >( b ) );
            iDst.SetA< T2 >( ConvType< T1, T2 >( iSrc.A< T1 >() ) );
            return;
        }

        case CM_Lab:
        {
            cmsCIELab Lab;
            cmsCIEXYZ XYZ;
            cmsCIEXYZ D65 = { 95.047f, 100.00f, 108.883f };
            Lab.L = ConvType< T1, double >( iSrc.L< T1 >() ) * 100.0;
            Lab.a = ( ConvType< T1, double >( iSrc.a< T1 >() ) - 0.5 ) * 255.0;
            Lab.b = ( ConvType< T1, double >( iSrc.b< T1 >() ) - 0.5 ) * 255.0;
            cmsLab2XYZ( &D65, &XYZ, &Lab );
            FPixel temp( ULIS2_FORMAT_XYZAD );
            temp.SetXD( XYZ.X / 100.0 );
            temp.SetYD( XYZ.Y / 100.0 );
            temp.SetZD( XYZ.Z / 100.0 );
            temp.SetAD( ConvType< T1, double >( iSrc.A< T1 >() ) );
            ToRGB< double, T2 >( temp, iDst );
            return;
        }

        case CM_XYZ:
        {
            // Note: this is sRGB under D65
            float x = ConvType< T1, float >( iSrc.X< T1 >() );
            float y = ConvType< T1, float >( iSrc.Y< T1 >() );
            float z = ConvType< T1, float >( iSrc.Z< T1 >() );
            float r = linear2srgb( +3.2404542f * x - 1.5371385f * y - 0.4985314f * z );
            float g = linear2srgb( -0.9692660f * x + 1.8760108f * y + 0.0415560f * z );
            float b = linear2srgb( +0.0556434f * x - 0.2040259f * y + 1.0572252f * z );
            iDst.SetR< T2 >( ConvType< float, T2 >( r ) );
            iDst.SetG< T2 >( ConvType< float, T2 >( g ) );
            iDst.SetB< T2 >( ConvType< float, T2 >( b ) );
            iDst.SetA< T2 >( ConvType< T1, T2 >( iSrc.A< T1 >() ) );
            return;
        }

        case CM_Yxy:
        {
            cmsCIExyY xyY;
            cmsCIEXYZ XYZ;
            xyY.x = ConvType< T1, double >( iSrc.x< T1 >() );
            xyY.y = ConvType< T1, double >( iSrc.y< T1 >() );
            xyY.Y = ConvType< T1, double >( iSrc.Luma< T1 >() );
            cmsxyY2XYZ( &XYZ, &xyY );
            FPixel temp( ULIS2_FORMAT_XYZAD );
            temp.SetXD( XYZ.X );
            temp.SetYD( XYZ.Y );
            temp.SetZD( XYZ.Z );
            temp.SetAD( ConvType< T1, double >( iSrc.A< T1 >() ) );
            ToRGB< double, T2 >( temp, iDst );
            return;
        }
    }
}


template< typename T1, typename T2 >
void
ToHSV( const IPixel& iSrc, IPixel& iDst )
{
    switch( iSrc.Model() )
    {
        case CM_ANY:
        {
            ULIS2_CRASH_DELIBERATE;
            return;
        }

        case CM_GREY:
        {
            iDst.SetHue< T2 >( T2(0) );
            iDst.SetSaturation< T2 >( T2(0) );
            iDst.SetValue< T2 >( ConvType< T1, T2 >( iSrc.G< T1 >() ) );
            iDst.SetAlpha< T2 >( ConvType< T1, T2 >( iSrc.A< T1 >() ) );
            return;
        }

        case CM_RGB:
        {
            float r = ConvType< T1, float >( iSrc.R< T1 >() );
            float g = ConvType< T1, float >( iSrc.G< T1 >() );
            float b = ConvType< T1, float >( iSrc.B< T1 >() );
            float cmin = FMaths::Min3( r, g, b );
            float cmax = FMaths::Max3( r, g, b );
            float delta = cmax - cmin;
            float h = 0.0;
            float s = 0.0;
            float v = 0.0;
            v = cmax;
            if ( delta < FMaths::kEpsilonf ){
                h = 0.0;
                s = 0.0;
            }
            else
            {
                s = (delta / cmax );

                float deltaR = ( ( ( cmax - r ) / 6.0f ) + ( delta / 2.0f ) ) / delta;
                float deltaG = ( ( ( cmax - g ) / 6.0f ) + ( delta / 2.0f ) ) / delta;
                float deltaB = ( ( ( cmax - b ) / 6.0f ) + ( delta / 2.0f ) ) / delta;

                if( fabs( r - cmax ) < FMaths::kEpsilonf )        h = deltaB - deltaG;
                else if( fabs( g - cmax ) < FMaths::kEpsilonf )   h = ( 1.0f / 3.0f ) + deltaR - deltaB;
                else if( fabs( b - cmax ) < FMaths::kEpsilonf )   h = ( 2.0f / 3.0f ) + deltaG - deltaR;

                if( h < 0.0f ) h += 1.0f;

                if( h > 1.0f ) h -= 1.0f;
            }

            iDst.SetHue< T2 >( ConvType< float, T2 >( h ) );
            iDst.SetSaturation< T2 >( ConvType< float, T2 >( s ) );
            iDst.SetValue< T2 >( ConvType< float, T2 >( v ) );
            iDst.SetAlpha< T2 >( ConvType< T1, T2 >( iSrc.A< T1 >() ) );
            return;
        }

        case CM_HSV:
        {
            iDst.SetHue< T2 >( ConvType< T1, T2 >( iSrc.Hue< T1 >() ) );
            iDst.SetSaturation< T2 >( ConvType< T1, T2 >( iSrc.Saturation< T1 >() ) );
            iDst.SetValue< T2 >( ConvType< T1, T2 >( iSrc.Value< T1 >() ) );
            iDst.SetA< T2 >( ConvType< T1, T2 >( iSrc.A< T1 >() ) );
            return;
        }

        case CM_HSL:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToHSV< float, T2 >( temp, iDst );
            return;
        }

        case CM_CMY:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToHSV< float, T2 >( temp, iDst );
            return;
        }

        case CM_CMYK:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToHSV< float, T2 >( temp, iDst );
            return;
        }

        case CM_YUV:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToHSV< float, T2 >( temp, iDst );
            return;
        }

        case CM_Lab:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToHSV< float, T2 >( temp, iDst );
            return;

        }

        case CM_XYZ:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToHSV< float, T2 >( temp, iDst );
            return;
        }

        case CM_Yxy:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToHSV< float, T2 >( temp, iDst );
            return;
        }
    }
}


template< typename T1, typename T2 >
void
ToHSL( const IPixel& iSrc, IPixel& iDst )
{
    switch( iSrc.Model() )
    {
        case CM_ANY:
        {
            ULIS2_CRASH_DELIBERATE;
            return;
        }

        case CM_GREY:
        {
            iDst.SetHue< T2 >( T2(0) );
            iDst.SetSaturation< T2 >( T2(0) );
            iDst.SetLightness< T2 >( ConvType< T1, T2 >( iSrc.G< T1 >() ) );
            iDst.SetAlpha< T2 >( ConvType< T1, T2 >( iSrc.A< T1 >() ) );
            return;
        }

        case CM_RGB:
        {
            float r = ConvType< T1, float >( iSrc.R< T1 >() );
            float g = ConvType< T1, float >( iSrc.G< T1 >() );
            float b = ConvType< T1, float >( iSrc.B< T1 >() );
            float cmin = FMaths::Min3( r, g, b );
            float cmax = FMaths::Max3( r, g, b );
            float delta = cmax - cmin;
            float deltaAdd = cmax + cmin;
            float h = 0.0;
            float s = 0.0;
            float l = 0.0;
            l = ( deltaAdd ) / 2.0f;
            if ( delta < FMaths::kEpsilonf ){
                h = 0.0;
                s = 0.0;
            }
            else
            {
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

            iDst.SetHue< T2 >( ConvType< float, T2 >( h ) );
            iDst.SetSaturation< T2 >( ConvType< float, T2 >( s ) );
            iDst.SetLightness< T2 >( ConvType< float, T2 >( l ) );
            iDst.SetAlpha< T2 >( ConvType< T1, T2 >( iSrc.A< T1 >() ) );
            return;
        }

        case CM_HSV:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToHSL< float, T2 >( temp, iDst );
            return;
        }

        case CM_HSL:
        {
            iDst.SetHue< T2 >( ConvType< T1, T2 >( iSrc.Hue< T1 >() ) );
            iDst.SetSaturation< T2 >( ConvType< T1, T2 >( iSrc.Saturation< T1 >() ) );
            iDst.SetLightness< T2 >( ConvType< T1, T2 >( iSrc.Lightness< T1 >() ) );
            iDst.SetA< T2 >( ConvType< T1, T2 >( iSrc.A< T1 >() ) );
            return;
        }

        case CM_CMY:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToHSL< float, T2 >( temp, iDst );
            return;
        }

        case CM_CMYK:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToHSL< float, T2 >( temp, iDst );
            return;
        }

        case CM_YUV:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToHSL< float, T2 >( temp, iDst );
            return;
        }

        case CM_Lab:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToHSL< float, T2 >( temp, iDst );
            return;

        }

        case CM_XYZ:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToHSL< float, T2 >( temp, iDst );
            return;
        }

        case CM_Yxy:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToHSL< float, T2 >( temp, iDst );
            return;
        }
    }
}


template< typename T1, typename T2 >
void
ToCMY( const IPixel& iSrc, IPixel& iDst )
{
    switch( iSrc.Model() )
    {
        case CM_ANY:
        {
            ULIS2_CRASH_DELIBERATE;
            return;
        }

        case CM_GREY:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToCMY< float, T2 >( temp, iDst );
            return;
        }

        case CM_RGB:
        {
            T2 max = MaxType< T2 >();
            iDst.SetCyan< T2 >(     max - ConvType< T1, T2 >( iSrc.Cyan< T1 >() ) );
            iDst.SetMagenta< T2 >(  max - ConvType< T1, T2 >( iSrc.Magenta< T1 >() ) );
            iDst.SetYellow< T2 >(   max - ConvType< T1, T2 >( iSrc.Yellow< T1 >() ) );
            iDst.SetA< T2 >(        max - ConvType< T1, T2 >( iSrc.A< T1 >() ) );
            return;
        }

        case CM_HSV:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToCMY< float, T2 >( temp, iDst );
            return;
        }

        case CM_HSL:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToCMY< float, T2 >( temp, iDst );
            return;
        }

        case CM_CMY:
        {
            iDst.SetCyan< T2 >( ConvType< T1, T2 >( iSrc.Cyan< T1 >() ) );
            iDst.SetMagenta< T2 >( ConvType< T1, T2 >( iSrc.Magenta< T1 >() ) );
            iDst.SetYellow< T2 >( ConvType< T1, T2 >( iSrc.Yellow< T1 >() ) );
            iDst.SetA< T2 >( ConvType< T1, T2 >( iSrc.A< T1 >() ) );
            return;
        }

        case CM_CMYK:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToCMY< float, T2 >( temp, iDst );
            return;
        }

        case CM_YUV:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToCMY< float, T2 >( temp, iDst );
            return;
        }

        case CM_Lab:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToCMY< float, T2 >( temp, iDst );
            return;

        }

        case CM_XYZ:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToCMY< float, T2 >( temp, iDst );
            return;
        }

        case CM_Yxy:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToCMY< float, T2 >( temp, iDst );
            return;
        }
    }
}


template< typename T1, typename T2 >
void
ToCMYK( const IPixel& iSrc, IPixel& iDst )
{
    switch( iSrc.Model() )
    {
        case CM_ANY:
        {
            ULIS2_CRASH_DELIBERATE;
            return;
        }

        case CM_GREY:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToCMY< float, T2 >( temp, iDst );
            return;
        }

        case CM_RGB:
        {
            float r = ConvType< T1, float >( iSrc.R< T1 >() );
            float g = ConvType< T1, float >( iSrc.G< T1 >() );
            float b = ConvType< T1, float >( iSrc.B< T1 >() );
            float ik = FMaths::Max3( r, g, b );
            float k = 1.f - ik;

            if( ik == 0 )
                ik = 1; // Division by 0 countermeasure, doesn't affect the result

            float c = ( ( 1.f - r ) - k ) / ( ik );
            float m = ( ( 1.f - g ) - k ) / ( ik );
            float y = ( ( 1.f - b ) - k ) / ( ik );

            iDst.SetCyan< T2 >( ConvType< float, T2 >( c ) );
            iDst.SetMagenta< T2 >( ConvType< float, T2 >( m ) );
            iDst.SetYellow< T2 >( ConvType< float, T2 >( y ) );
            iDst.SetKey< T2 >( ConvType< float, T2 >( k ) );
            iDst.SetA< T2 >( ConvType< T1, T2 >( iSrc.A< T1 >() ) );
            return;
        }

        case CM_HSV:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToCMYK< float, T2 >( temp, iDst );
            return;
        }

        case CM_HSL:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToCMYK< float, T2 >( temp, iDst );
            return;
        }

        case CM_CMY:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToCMYK< float, T2 >( temp, iDst );
            return;
        }

        case CM_CMYK:
        {
            iDst.SetCyan< T2 >( ConvType< T1, T2 >( iSrc.Cyan< T1 >() ) );
            iDst.SetMagenta< T2 >( ConvType< T1, T2 >( iSrc.Magenta< T1 >() ) );
            iDst.SetYellow< T2 >( ConvType< T1, T2 >( iSrc.Yellow< T1 >() ) );
            iDst.SetKey< T2 >( ConvType< T1, T2 >( iSrc.Key< T1 >() ) );
            iDst.SetA< T2 >( ConvType< T1, T2 >( iSrc.A< T1 >() ) );
            return;
        }

        case CM_YUV:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToCMYK< float, T2 >( temp, iDst );
            return;
        }

        case CM_Lab:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToCMYK< float, T2 >( temp, iDst );
            return;

        }

        case CM_XYZ:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToCMYK< float, T2 >( temp, iDst );
            return;
        }

        case CM_Yxy:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToCMYK< float, T2 >( temp, iDst );
            return;
        }
    }
}


template< typename T1, typename T2 >
void
ToYUV( const IPixel& iSrc, IPixel& iDst )
{
    switch( iSrc.Model() )
    {
        case CM_ANY:
        {
            ULIS2_CRASH_DELIBERATE;
            return;
        }

        case CM_GREY:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToYUV< float, T2 >( temp, iDst );
            return;
        }

        case CM_RGB:
        {
            float r = srgb2linear( ConvType< T1, float >( iSrc.R< T1 >() ) );
            float g = srgb2linear( ConvType< T1, float >( iSrc.G< T1 >() ) );
            float b = srgb2linear( ConvType< T1, float >( iSrc.B< T1 >() ) );
            float y = 0.299f * r + 0.587f * g + 0.114f * b;
            float u = 0.492f * ( b - y );
            float v = 0.877f * ( r - y );
            iDst.SetLuma< T2 >( ConvType< float, T2 >( y ) );
            iDst.SetU< T2 >( ConvType< float, T2 >( u ) );
            iDst.SetV< T2 >( ConvType< float, T2 >( v ) );
            iDst.SetA< T2 >( ConvType< T1, T2 >( iSrc.A< T1 >() ) );
            return;
        }

        case CM_HSV:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToYUV< float, T2 >( temp, iDst );
            return;
        }

        case CM_HSL:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToYUV< float, T2 >( temp, iDst );
            return;
        }

        case CM_CMY:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToYUV< float, T2 >( temp, iDst );
            return;
        }

        case CM_CMYK:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToYUV< float, T2 >( temp, iDst );
            return;
        }

        case CM_YUV:
        {
            iDst.SetLuma< T2 >( ConvType< T1, T2 >( iSrc.Luma< T1 >() ) );
            iDst.SetU< T2 >( ConvType< T1, T2 >( iSrc.U< T1 >() ) );
            iDst.SetV< T2 >( ConvType< T1, T2 >( iSrc.V< T1 >() ) );
            iDst.SetA< T2 >( ConvType< T1, T2 >( iSrc.A< T1 >() ) );
            return;
        }

        case CM_Lab:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToYUV< float, T2 >( temp, iDst );
            return;

        }

        case CM_XYZ:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToYUV< float, T2 >( temp, iDst );
            return;
        }

        case CM_Yxy:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToYUV< float, T2 >( temp, iDst );
            return;
        }
    }
}


template< typename T1, typename T2 >
void
ToLab( const IPixel& iSrc, IPixel& iDst )
{
    switch( iSrc.Model() )
    {
        case CM_ANY:
        {
            ULIS2_CRASH_DELIBERATE;
            return;
        }

        case CM_GREY:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToLab< float, T2 >( temp, iDst );
            return;
        }

        case CM_RGB:
        {
            FPixel temp( ULIS2_FORMAT_XYZAF );
            ToXYZ< T1, float >( iSrc, temp );
            ToLab< float, T2 >( temp, iDst );
            return;
        }

        case CM_HSV:
        {
            FPixel temp( ULIS2_FORMAT_XYZAF );
            ToXYZ< T1, float >( iSrc, temp );
            ToLab< float, T2 >( temp, iDst );
            return;
        }

        case CM_HSL:
        {
            FPixel temp( ULIS2_FORMAT_XYZAF );
            ToXYZ< T1, float >( iSrc, temp );
            ToLab< float, T2 >( temp, iDst );
            return;
        }

        case CM_CMY:
        {
            FPixel temp( ULIS2_FORMAT_XYZAF );
            ToXYZ< T1, float >( iSrc, temp );
            ToLab< float, T2 >( temp, iDst );
            return;
        }

        case CM_CMYK:
        {
            FPixel temp( ULIS2_FORMAT_XYZAF );
            ToXYZ< T1, float >( iSrc, temp );
            ToLab< float, T2 >( temp, iDst );
            return;
        }

        case CM_YUV:
        {
            FPixel temp( ULIS2_FORMAT_XYZAF );
            ToXYZ< T1, float >( iSrc, temp );
            ToLab< float, T2 >( temp, iDst );
            return;
        }

        case CM_Lab:
        {
            iDst.SetL< T2 >( ConvType< T1, T2 >( iSrc.L< T1 >() ) );
            iDst.Seta< T2 >( ConvType< T1, T2 >( iSrc.a< T1 >() ) );
            iDst.Setb< T2 >( ConvType< T1, T2 >( iSrc.b< T1 >() ) );
            iDst.SetA< T2 >( ConvType< T1, T2 >( iSrc.A< T1 >() ) );
            return;
        }

        case CM_XYZ:
        {
            cmsCIELab Lab;
            cmsCIEXYZ XYZ;
            cmsCIEXYZ D65 = { 95.047f, 100.00f, 108.883f };
            // Note: * 100 to keep lab in range [0;255], [-128;+127]
            XYZ.X = ConvType< T1, double >( iSrc.X< T1 >() ) * 100.0;
            XYZ.Y = ConvType< T1, double >( iSrc.Y< T1 >() ) * 100.0;
            XYZ.Z = ConvType< T1, double >( iSrc.Z< T1 >() ) * 100.0;
            cmsXYZ2Lab( &D65, &Lab, &XYZ );
            // Note: / 100 & / 255 + 0.5 to keep lab in range [0;1]
            iDst.SetL< T2 >( ConvType< double, T2 >( Lab.L / 100.0 ) );
            iDst.Seta< T2 >( ConvType< double, T2 >( Lab.a / 255.0 + 0.5 ) );
            iDst.Setb< T2 >( ConvType< double, T2 >( Lab.b / 255.0 + 0.5 ) );
            iDst.SetA< T2 >( ConvType< T1, T2 >( iSrc.A< T1 >() ) );
            return;
        }

        case CM_Yxy:
        {
            FPixel temp( ULIS2_FORMAT_XYZAF );
            ToXYZ< T1, float >( iSrc, temp );
            ToLab< float, T2 >( temp, iDst );
            return;
        }
    }
}


template< typename T1, typename T2 >
void
ToXYZ( const IPixel& iSrc, IPixel& iDst )
{
    switch( iSrc.Model() )
    {
        case CM_ANY:
        {
            ULIS2_CRASH_DELIBERATE;
            return;
        }

        case CM_GREY:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToXYZ< float, T2 >( temp, iDst );
            return;
        }

        case CM_RGB:
        {
            // Note: this is sRGB under D65
            float r = srgb2linear( ConvType< T1, float >( iSrc.R< T1 >() ) );
            float g = srgb2linear( ConvType< T1, float >( iSrc.G< T1 >() ) );
            float b = srgb2linear( ConvType< T1, float >( iSrc.B< T1 >() ) );
            float x = 0.4124f * r + 0.3576f * g + 0.1805f * b;
            float y = 0.2126f * r + 0.7152f * g + 0.0722f * b;
            float z = 0.0193f * r + 0.1192f * g + 0.9505f * b;
            iDst.SetX< T2 >( ConvType< float, T2 >( x ) );
            iDst.SetY< T2 >( ConvType< float, T2 >( y ) );
            iDst.SetZ< T2 >( ConvType< float, T2 >( z ) );
            iDst.SetA< T2 >( ConvType< T1, T2 >( iSrc.A< T1 >() ) );
            return;
        }

        case CM_HSV:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToXYZ< float, T2 >( temp, iDst );
            return;
        }

        case CM_HSL:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToXYZ< float, T2 >( temp, iDst );
            return;
        }

        case CM_CMY:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToXYZ< float, T2 >( temp, iDst );
            return;
        }

        case CM_CMYK:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToXYZ< float, T2 >( temp, iDst );
            return;
        }

        case CM_YUV:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToXYZ< float, T2 >( temp, iDst );
            return;
        }

        case CM_Lab:
        {
            cmsCIELab Lab;
            cmsCIEXYZ XYZ;
            cmsCIEXYZ D65 = { 95.047f, 100.00f, 108.883f };
            Lab.L = ConvType< T1, double >( iSrc.L< T1 >() ) * 100.0;
            Lab.a = ( ConvType< T1, double >( iSrc.a< T1 >() ) - 0.5 ) * 255.0;
            Lab.b = ( ConvType< T1, double >( iSrc.b< T1 >() ) - 0.5 ) * 255.0;
            cmsLab2XYZ( &D65, &XYZ, &Lab );
            iDst.SetX< T2 >( ConvType< double, T2 >( XYZ.X ) );
            iDst.SetY< T2 >( ConvType< double, T2 >( XYZ.Y ) );
            iDst.SetZ< T2 >( ConvType< double, T2 >( XYZ.Z ) );
            iDst.SetA< T2 >( ConvType< T1, T2 >( iSrc.A< T1 >() ) );
            return;
        }

        case CM_XYZ:
        {
            iDst.SetX< T2 >( ConvType< T1, T2 >( iSrc.X< T1 >() ) );
            iDst.SetY< T2 >( ConvType< T1, T2 >( iSrc.Y< T1 >() ) );
            iDst.SetZ< T2 >( ConvType< T1, T2 >( iSrc.Z< T1 >() ) );
            iDst.SetA< T2 >( ConvType< T1, T2 >( iSrc.A< T1 >() ) );
            return;
        }

        case CM_Yxy:
        {
            cmsCIExyY xyY;
            cmsCIEXYZ XYZ;
            xyY.x = ConvType< T1, double >( iSrc.x< T1 >() );
            xyY.y = ConvType< T1, double >( iSrc.y< T1 >() );
            xyY.Y = ConvType< T1, double >( iSrc.Luma< T1 >() );
            cmsxyY2XYZ( &XYZ, &xyY );
            iDst.SetX< T2 >( ConvType< double, T2 >( XYZ.X ) );
            iDst.SetY< T2 >( ConvType< double, T2 >( XYZ.Y ) );
            iDst.SetZ< T2 >( ConvType< double, T2 >( XYZ.Z ) );
            iDst.SetA< T2 >( ConvType< T1, T2 >( iSrc.A< T1 >() ) );
            return;
        }
    }
}


template< typename T1, typename T2 >
void
ToYxy( const IPixel& iSrc, IPixel& iDst )
{
    switch( iSrc.Model() )
    {
        case CM_ANY:
        {
            ULIS2_CRASH_DELIBERATE;
            return;
        }

        case CM_GREY:
        {
            FPixel temp( ULIS2_FORMAT_XYZF );
            ToXYZ< T1, float >( iSrc, temp );
            ToYxy< float, T2 >( temp, iDst );
            return;
        }

        case CM_RGB:
        {
            FPixel temp( ULIS2_FORMAT_XYZF );
            ToXYZ< T1, float >( iSrc, temp );
            ToYxy< float, T2 >( temp, iDst );
            return;
        }

        case CM_HSV:
        {
            FPixel temp( ULIS2_FORMAT_XYZF );
            ToXYZ< T1, float >( iSrc, temp );
            ToYxy< float, T2 >( temp, iDst );
            return;
        }

        case CM_HSL:
        {
            FPixel temp( ULIS2_FORMAT_XYZF );
            ToXYZ< T1, float >( iSrc, temp );
            ToYxy< float, T2 >( temp, iDst );
            return;
        }

        case CM_CMY:
        {
            FPixel temp( ULIS2_FORMAT_XYZF );
            ToXYZ< T1, float >( iSrc, temp );
            ToYxy< float, T2 >( temp, iDst );
            return;
        }

        case CM_CMYK:
        {
            FPixel temp( ULIS2_FORMAT_XYZF );
            ToXYZ< T1, float >( iSrc, temp );
            ToYxy< float, T2 >( temp, iDst );
            return;
        }

        case CM_YUV:
        {
            FPixel temp( ULIS2_FORMAT_XYZF );
            ToXYZ< T1, float >( iSrc, temp );
            ToYxy< float, T2 >( temp, iDst );
            return;
        }

        case CM_Lab:
        {
            FPixel temp( ULIS2_FORMAT_XYZF );
            ToXYZ< T1, float >( iSrc, temp );
            ToYxy< float, T2 >( temp, iDst );
            return;
        }

        case CM_XYZ:
        {
            cmsCIEXYZ XYZ;
            cmsCIExyY xyY;
            XYZ.Y = ConvType< T1, double >( iSrc.X< T1 >() );
            XYZ.X = ConvType< T1, double >( iSrc.Y< T1 >() );
            XYZ.Y = ConvType< T1, double >( iSrc.Z< T1 >() );
            cmsXYZ2xyY( &xyY, &XYZ );
            iDst.SetLuma< T2 >( ConvType< double, T2 >( xyY.Y ) );
            iDst.Setx< T2 >( ConvType< double, T2 >( xyY.x ) );
            iDst.Sety< T2 >( ConvType< double, T2 >( xyY.y ) );
            iDst.SetA< T2 >( ConvType< T1, T2 >( iSrc.A< T1 >() ) );
            return;
        }

        case CM_Yxy:
        {
            iDst.SetLuma< T2 >( ConvType< T1, T2 >( iSrc.Luma< T1 >() ) );
            iDst.Setx< T2 >( ConvType< T1, T2 >( iSrc.x< T1 >() ) );
            iDst.Sety< T2 >( ConvType< T1, T2 >( iSrc.y< T1 >() ) );
            iDst.SetA< T2 >( ConvType< T1, T2 >( iSrc.A< T1 >() ) );
            return;
        }
    }
}


template< typename T1, typename T2 >
void Conv_imp( const IPixel& iSrc, IPixel& iDst )
{
    switch( iDst.Model() )
    {
        case CM_ANY:    ULIS2_CRASH_DELIBERATE;         return;
        case CM_GREY:   ToGrey< T1, T2 >( iSrc, iDst ); return;
        case CM_RGB:    ToRGB< T1, T2 >( iSrc, iDst );  return;
        case CM_HSV:    ToHSV< T1, T2 >( iSrc, iDst );  return;
        case CM_HSL:    ToHSL< T1, T2 >( iSrc, iDst );  return;
        case CM_CMY:    ToCMY< T1, T2 >( iSrc, iDst );  return;
        case CM_CMYK:   ToCMYK< T1, T2 >( iSrc, iDst ); return;
        case CM_YUV:    ToYUV< T1, T2 >( iSrc, iDst );  return;
        case CM_Lab:    ToLab< T1, T2 >( iSrc, iDst );  return;
        case CM_XYZ:    ToXYZ< T1, T2 >( iSrc, iDst );  return;
        case CM_Yxy:    ToYxy< T1, T2 >( iSrc, iDst );  return;
    }
}


void Conv( const IPixel& iSrc, IPixel& iDst )
{
    switch( iSrc.Type() ) {
        case TYPE_UINT8: switch( iDst.Type() ) {
                case TYPE_UINT8:        Conv_imp< uint8, uint8 >( iSrc, iDst );     return;
                case TYPE_UINT16:       Conv_imp< uint8, uint16 >( iSrc, iDst );    return;
                case TYPE_UINT32:       Conv_imp< uint8, uint32 >( iSrc, iDst );    return;
                case TYPE_UFLOAT:       Conv_imp< uint8, ufloat >( iSrc, iDst );    return;
                case TYPE_UDOUBLE:      Conv_imp< uint8, udouble >( iSrc, iDst );   return; }
        case TYPE_UINT16: switch( iDst.Type() ) {
                case TYPE_UINT8:        Conv_imp< uint16, uint8 >( iSrc, iDst );    return;
                case TYPE_UINT16:       Conv_imp< uint16, uint16 >( iSrc, iDst );   return;
                case TYPE_UINT32:       Conv_imp< uint16, uint32 >( iSrc, iDst );   return;
                case TYPE_UFLOAT:       Conv_imp< uint16, ufloat >( iSrc, iDst );   return;
                case TYPE_UDOUBLE:      Conv_imp< uint16, udouble >( iSrc, iDst );  return; }
        case TYPE_UINT32: switch( iDst.Type() ) {
                case TYPE_UINT8:        Conv_imp< uint32, uint8 >( iSrc, iDst );    return;
                case TYPE_UINT16:       Conv_imp< uint32, uint16 >( iSrc, iDst );   return;
                case TYPE_UINT32:       Conv_imp< uint32, uint32 >( iSrc, iDst );   return;
                case TYPE_UFLOAT:       Conv_imp< uint32, ufloat >( iSrc, iDst );   return;
                case TYPE_UDOUBLE:      Conv_imp< uint32, udouble >( iSrc, iDst );  return; }
        case TYPE_UFLOAT: switch( iDst.Type() ) {
                case TYPE_UINT8:        Conv_imp< ufloat, uint8 >( iSrc, iDst );    return;
                case TYPE_UINT16:       Conv_imp< ufloat, uint16 >( iSrc, iDst );   return;
                case TYPE_UINT32:       Conv_imp< ufloat, uint32 >( iSrc, iDst );   return;
                case TYPE_UFLOAT:       Conv_imp< ufloat, ufloat >( iSrc, iDst );   return;
                case TYPE_UDOUBLE:      Conv_imp< ufloat, udouble >( iSrc, iDst );  return; }
        case TYPE_UDOUBLE: switch( iDst.Type() ) {
                case TYPE_UINT8:        Conv_imp< udouble, uint8 >( iSrc, iDst );   return;
                case TYPE_UINT16:       Conv_imp< udouble, uint16 >( iSrc, iDst );  return;
                case TYPE_UINT32:       Conv_imp< udouble, uint32 >( iSrc, iDst );  return;
                case TYPE_UFLOAT:       Conv_imp< udouble, ufloat >( iSrc, iDst );  return;
                case TYPE_UDOUBLE:      Conv_imp< udouble, udouble >( iSrc, iDst ); return; }
    }
}

ULIS2_NAMESPACE_END

