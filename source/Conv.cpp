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
#include "ModelSupport.h"
#include "ColorProfile.h"
#include "ProfileRegistry.h"
#include <limits>

ULIS2_NAMESPACE_BEGIN
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


template< typename T1, typename T2 > T2 inline ConvType( T1 iValue ) { return (T2)iValue; }
template<> uint16   inline ConvType< uint8,  uint16 >( uint8 iValue  ) { return iValue * 0x101;                         }
template<> uint32   inline ConvType< uint8,  uint32 >( uint8 iValue  ) { return iValue * 0x1010101;                     }
template<> uint64   inline ConvType< uint8,  uint64 >( uint8 iValue  ) { return iValue * 0x10100000101;                 }
template<> uint32   inline ConvType< uint16, uint32 >( uint16 iValue ) { return iValue * 0x10001;                       }
template<> uint64   inline ConvType< uint16, uint64 >( uint16 iValue ) { return iValue * 0x1000100010001;               }
template<> uint64   inline ConvType< uint32, uint64 >( uint32 iValue ) { return iValue * 0x100000001;                   }
template<> uint8    inline ConvType< uint16, uint8  >( uint16 iValue ) { return ( iValue + 1 + ( iValue>>8 ) ) >> 8;    }
template<> uint8    inline ConvType< uint32, uint8  >( uint32 iValue ) { return iValue >> 24;                           }
template<> uint8    inline ConvType< uint64, uint8  >( uint64 iValue ) { return iValue >> 56;                           }
template<> uint16   inline ConvType< uint32, uint16 >( uint32 iValue ) { return ( iValue + 1 + ( iValue>>16 ) ) >> 16;  }
template<> uint16   inline ConvType< uint64, uint16 >( uint64 iValue ) { return iValue >> 48;                           }
template<> uint32   inline ConvType< uint64, uint32 >( uint64 iValue ) { return iValue >> 32;                           }
template<> float    inline ConvType< uint8,  float  >( uint8 iValue  ) { return iValue / (float)0xFF;                   }
template<> float    inline ConvType< uint16, float  >( uint16 iValue ) { return iValue / (float)0xFFFF;                 }
template<> float    inline ConvType< uint32, float  >( uint32 iValue ) { return iValue / (float)0xFFFFFFFF;             }
template<> float    inline ConvType< uint64, float  >( uint64 iValue ) { return iValue / (float)0xFFFFFFFFFFFFFFFF;     }
template<> double   inline ConvType< uint8,  double >( uint8 iValue  ) { return iValue / (double)0xFF;                  }
template<> double   inline ConvType< uint16, double >( uint16 iValue ) { return iValue / (double)0xFFFF;                }
template<> double   inline ConvType< uint32, double >( uint32 iValue ) { return iValue / (double)0xFFFFFFFF;            }
template<> double   inline ConvType< uint64, double >( uint64 iValue ) { return iValue / (double)0xFFFFFFFFFFFFFFFF;    }
template<> uint8    inline ConvType< float,  uint8  >( float iValue  ) { return uint8(  iValue * 0xFF               );  }
template<> uint16   inline ConvType< float,  uint16 >( float iValue  ) { return uint16( iValue * 0xFFFF             );  }
template<> uint32   inline ConvType< float,  uint32 >( float iValue  ) { return uint32( iValue * 0xFFFFFFFF         );  }
template<> uint64   inline ConvType< float,  uint64 >( float iValue  ) { return uint64( iValue * 0xFFFFFFFFFFFFFFFF );  }
template<> uint8    inline ConvType< double, uint8  >( double iValue ) { return uint8(  iValue * 0xFF               );  }
template<> uint16   inline ConvType< double, uint16 >( double iValue ) { return uint16( iValue * 0xFFFF             );  }
template<> uint32   inline ConvType< double, uint32 >( double iValue ) { return uint32( iValue * 0xFFFFFFFF         );  }
template<> uint64   inline ConvType< double, uint64 >( double iValue ) { return uint64( iValue * 0xFFFFFFFFFFFFFFFF );  }


template< typename T1, typename T2 >
void
ToGrey( const IPixel& iSrc, IPixel& iDst )
{
    switch( iSrc.Model() )
    {
        case eModelSig::kAny:
        {
            ULIS2_CRASH_DELIBERATE;
            return;
        }

        case eModelSig::kGrey:
        {
            iDst.SetGrey< T2 >( ConvType< T1, T2 >( iSrc.G< T1 >() ) );
            iDst.SetA< T2 >( ConvType< T1, T2 >( iSrc.A< T1 >() ) );
            return;
        }

        case eModelSig::kRGB:
        {
            float r = ConvType< T1, float >( iSrc.R< T1 >() );
            float g = ConvType< T1, float >( iSrc.G< T1 >() );
            float b = ConvType< T1, float >( iSrc.B< T1 >() );
            float _grey = ( r + g + b ) / 3.0f;
            iDst.SetGrey< T2 >( ConvType< float, T2 >( _grey ) );
            iDst.SetA< T2 >( ConvType< T1, T2 >( iSrc.A< T1 >() ) );
            return;
        }

        case eModelSig::kHSV:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToGrey< float, T2 >( temp, iDst );
            return;
        }

        case eModelSig::kHSL:
        {
            float _grey = ConvType< T1, float >( iSrc.Lightness< T1 >() );
            iDst.SetGrey< T2 >( ConvType< float, T2 >( _grey ) );
            iDst.SetA< T2 >( ConvType< T1, T2 >( iSrc.A< T1 >() ) );
            return;
        }

        case eModelSig::kCMY:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToGrey< float, T2 >( temp, iDst );
            return;
        }

        case eModelSig::kCMYK:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToGrey< float, T2 >( temp, iDst );
            return;
        }

        case eModelSig::kYUV:
        {
            float _grey = ConvType< T1, float >( iSrc.Luma< T1 >() );
            iDst.SetGrey< T2 >( ConvType< float, T2 >( _grey ) );
            iDst.SetA< T2 >( ConvType< T1, T2 >( iSrc.A< T1 >() ) );
            return;
        }

        case eModelSig::kLab:
        {
            float _grey = ConvType< T1, float >( iSrc.Luma< T1 >() );
            iDst.SetGrey< T2 >( ConvType< float, T2 >( _grey ) );
            iDst.SetA< T2 >( ConvType< T1, T2 >( iSrc.A< T1 >() ) );
            return;
        }

        case eModelSig::kXYZ:
        {
            float _grey = ConvType< T1, float >( iSrc.Y< T1 >() );
            iDst.SetGrey< T2 >( ConvType< float, T2 >( _grey ) );
            iDst.SetA< T2 >( ConvType< T1, T2 >( iSrc.A< T1 >() ) );
            return;
        }

        case eModelSig::kYxy:
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
        case eModelSig::kAny:
        {
            ULIS2_CRASH_DELIBERATE;
            return;
        }

        case eModelSig::kGrey:
        {
            T2 _grey    = ConvType< T1, T2 >( iSrc.Grey< T1 >() );
            iDst.SetR< T2 >( _grey );
            iDst.SetG< T2 >( _grey );
            iDst.SetB< T2 >( _grey );
            iDst.SetA< T2 >( ConvType< T1, T2 >( iSrc.A< T1 >() ) );
            return;
        }

        case eModelSig::kRGB:
        {
            iDst.SetR< T2 >( ConvType< T1, T2 >( iSrc.R< T1 >() ) );
            iDst.SetG< T2 >( ConvType< T1, T2 >( iSrc.G< T1 >() ) );
            iDst.SetB< T2 >( ConvType< T1, T2 >( iSrc.B< T1 >() ) );
            iDst.SetA< T2 >( ConvType< T1, T2 >( iSrc.A< T1 >() ) );
            return;
        }

        case eModelSig::kHSV:
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

        case eModelSig::kHSL:
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

        case eModelSig::kCMY:
        {
            T2 max = std::numeric_limits< T2 >::max();
            iDst.SetCyan< T2 >(     max - ConvType< T1, T2 >( iSrc.R< T1 >() ) );
            iDst.SetMagenta< T2 >(  max - ConvType< T1, T2 >( iSrc.G< T1 >() ) );
            iDst.SetYellow< T2 >(   max - ConvType< T1, T2 >( iSrc.B< T1 >() ) );
            iDst.SetAlpha< T2 >( ConvType< T1, T2 >( iSrc.A< T1 >() ) );
            return;
        }

        case eModelSig::kCMYK:
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

        case eModelSig::kYUV:
        {
            float y = ConvType< T1, float >( iSrc.Luma< T1 >() );
            float u = ConvType< T1, float >( iSrc.U< T1 >() );
            float v = ConvType< T1, float >( iSrc.V< T1 >() );
            float r = y + 1.14f * v;
            float g = y - 0.395f * u - 0.581f * v;
            float b = y + 2.033f * u;
            iDst.SetR< T2 >( ConvType< float, T2 >( r ) );
            iDst.SetG< T2 >( ConvType< float, T2 >( g ) );
            iDst.SetB< T2 >( ConvType< float, T2 >( b ) );
            iDst.SetA< T2 >( ConvType< T1, T2 >( iSrc.A< T1 >() ) );
            return;
        }

        case eModelSig::kLab:
        {
            cmsCIELab Lab;
            cmsCIEXYZ XYZ;
            cmsCIEXYZ D65 = { 95.047f, 100.00f, 108.883f };
            Lab.L = ConvType< T1, double >( iSrc.L< T1 >() );
            Lab.a = ConvType< T1, double >( iSrc.a< T1 >() );
            Lab.b = ConvType< T1, double >( iSrc.b< T1 >() );
            cmsLab2XYZ( &D65, &XYZ, &Lab );
            FPixel temp( ULIS2_FORMAT_XYZAD );
            temp.SetXD( XYZ.X );
            temp.SetYD( XYZ.Y );
            temp.SetZD( XYZ.Z );
            temp.SetAD( ConvType< T1, double >( iSrc.A< T1 >() ) );
            ToRGB< double, T2 >( temp, iDst );
            return;
        }

        case eModelSig::kXYZ:
        {
            // Note: this is sRGB under D65
            float x = ConvType< T1, float >( iSrc.X< T1 >() );
            float y = ConvType< T1, float >( iSrc.Y< T1 >() );
            float z = ConvType< T1, float >( iSrc.Z< T1 >() );
            float r =  3.2404542f * x - 1.5371385f * y - 0.4985314f * z;
            float g = -0.9692660f * x + 1.8760108f * y + 0.0415560f * z;
            float b =  0.0556434f * x - 0.2040259f * y + 1.0572252f * z;
            iDst.SetR< T2 >( ConvType< float, T2 >( r ) );
            iDst.SetG< T2 >( ConvType< float, T2 >( g ) );
            iDst.SetB< T2 >( ConvType< float, T2 >( b ) );
            iDst.SetA< T2 >( ConvType< T1, T2 >( iSrc.A< T1 >() ) );
            return;
        }

        case eModelSig::kYxy:
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
        case eModelSig::kAny:
        {
            ULIS2_CRASH_DELIBERATE;
            return;
        }

        case eModelSig::kGrey:
        {
            iDst.SetHue< T2 >( T2(0) );
            iDst.SetSaturation< T2 >( T2(0) );
            iDst.SetValue< T2 >( ConvType< T1, T2 >( iSrc.G< T1 >() ) );
            iDst.SetAlpha< T2 >( ConvType< T1, T2 >( iSrc.A< T1 >() ) );
            return;
        }

        case eModelSig::kRGB:
        {
            float r = ConvType< T2, float >( iSrc.R< T2 >() );
            float g = ConvType< T2, float >( iSrc.G< T2 >() );
            float b = ConvType< T2, float >( iSrc.B< T2 >() );
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

        case eModelSig::kHSV:
        {
            iDst.SetHue< T2 >( ConvType< T1, T2 >( iSrc.Hue< T1 >() ) );
            iDst.SetSaturation< T2 >( ConvType< T1, T2 >( iSrc.Saturation< T1 >() ) );
            iDst.SetValue< T2 >( ConvType< T1, T2 >( iSrc.Value< T1 >() ) );
            iDst.SetA< T2 >( ConvType< T1, T2 >( iSrc.A< T1 >() ) );
            return;
        }

        case eModelSig::kHSL:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToHSV< float, T2 >( temp, iDst );
            return;
        }

        case eModelSig::kCMY:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToHSV< float, T2 >( temp, iDst );
            return;
        }

        case eModelSig::kCMYK:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToHSV< float, T2 >( temp, iDst );
            return;
        }

        case eModelSig::kYUV:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToHSV< float, T2 >( temp, iDst );
            return;
        }

        case eModelSig::kLab:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToHSV< float, T2 >( temp, iDst );
            return;

        }

        case eModelSig::kXYZ:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToHSV< float, T2 >( temp, iDst );
            return;
        }

        case eModelSig::kYxy:
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
        case eModelSig::kAny:
        {
            ULIS2_CRASH_DELIBERATE;
            return;
        }

        case eModelSig::kGrey:
        {
            iDst.SetHue< T2 >( T2(0) );
            iDst.SetSaturation< T2 >( T2(0) );
            iDst.SetLightness< T2 >( ConvType< T1, T2 >( iSrc.G< T1 >() ) );
            iDst.SetAlpha< T2 >( ConvType< T1, T2 >( iSrc.A< T1 >() ) );
            return;
        }

        case eModelSig::kRGB:
        {
            float r = ConvType< T2, float >( iSrc.R< T2 >() );
            float g = ConvType< T2, float >( iSrc.G< T2 >() );
            float b = ConvType< T2, float >( iSrc.B< T2 >() );
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

        case eModelSig::kHSV:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToHSL< float, T2 >( temp, iDst );
            return;
        }

        case eModelSig::kHSL:
        {
            iDst.SetHue< T2 >( ConvType< T1, T2 >( iSrc.Hue< T1 >() ) );
            iDst.SetSaturation< T2 >( ConvType< T1, T2 >( iSrc.Saturation< T1 >() ) );
            iDst.SetLightness< T2 >( ConvType< T1, T2 >( iSrc.Lightness< T1 >() ) );
            iDst.SetA< T2 >( ConvType< T1, T2 >( iSrc.A< T1 >() ) );
            return;
        }

        case eModelSig::kCMY:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToHSL< float, T2 >( temp, iDst );
            return;
        }

        case eModelSig::kCMYK:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToHSL< float, T2 >( temp, iDst );
            return;
        }

        case eModelSig::kYUV:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToHSL< float, T2 >( temp, iDst );
            return;
        }

        case eModelSig::kLab:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToHSL< float, T2 >( temp, iDst );
            return;

        }

        case eModelSig::kXYZ:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToHSL< float, T2 >( temp, iDst );
            return;
        }

        case eModelSig::kYxy:
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
        case eModelSig::kAny:
        {
            ULIS2_CRASH_DELIBERATE;
            return;
        }

        case eModelSig::kGrey:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToCMY< float, T2 >( temp, iDst );
            return;
        }

        case eModelSig::kRGB:
        {
            T2 max = std::numeric_limits< T2 >::max();
            iDst.SetCyan< T2 >(     max - ConvType< T1, T2 >( iSrc.Cyan< T1 >() ) );
            iDst.SetMagenta< T2 >(  max - ConvType< T1, T2 >( iSrc.Magenta< T1 >() ) );
            iDst.SetYellow< T2 >(   max - ConvType< T1, T2 >( iSrc.Yellow< T1 >() ) );
            iDst.SetA< T2 >(        max - ConvType< T1, T2 >( iSrc.A< T1 >() ) );
            return;
        }

        case eModelSig::kHSV:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToCMY< float, T2 >( temp, iDst );
            return;
        }

        case eModelSig::kHSL:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToCMY< float, T2 >( temp, iDst );
            return;
        }

        case eModelSig::kCMY:
        {
            iDst.SetCyan< T2 >( ConvType< T1, T2 >( iSrc.Cyan< T1 >() ) );
            iDst.SetMagenta< T2 >( ConvType< T1, T2 >( iSrc.Magenta< T1 >() ) );
            iDst.SetYellow< T2 >( ConvType< T1, T2 >( iSrc.Yellow< T1 >() ) );
            iDst.SetA< T2 >( ConvType< T1, T2 >( iSrc.A< T1 >() ) );
            return;
        }

        case eModelSig::kCMYK:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToCMY< float, T2 >( temp, iDst );
            return;
        }

        case eModelSig::kYUV:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToCMY< float, T2 >( temp, iDst );
            return;
        }

        case eModelSig::kLab:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToCMY< float, T2 >( temp, iDst );
            return;

        }

        case eModelSig::kXYZ:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToCMY< float, T2 >( temp, iDst );
            return;
        }

        case eModelSig::kYxy:
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
        case eModelSig::kAny:
        {
            ULIS2_CRASH_DELIBERATE;
            return;
        }

        case eModelSig::kGrey:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToCMY< float, T2 >( temp, iDst );
            return;
        }

        case eModelSig::kRGB:
        {
            float r = ConvType< T2, float >( iSrc.R< T2 >() );
            float g = ConvType< T2, float >( iSrc.G< T2 >() );
            float b = ConvType< T2, float >( iSrc.B< T2 >() );
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

        case eModelSig::kHSV:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToCMYK< float, T2 >( temp, iDst );
            return;
        }

        case eModelSig::kHSL:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToCMYK< float, T2 >( temp, iDst );
            return;
        }

        case eModelSig::kCMY:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToCMYK< float, T2 >( temp, iDst );
            return;
        }

        case eModelSig::kCMYK:
        {
            iDst.SetCyan< T2 >( ConvType< T1, T2 >( iSrc.Cyan< T1 >() ) );
            iDst.SetMagenta< T2 >( ConvType< T1, T2 >( iSrc.Magenta< T1 >() ) );
            iDst.SetYellow< T2 >( ConvType< T1, T2 >( iSrc.Yellow< T1 >() ) );
            iDst.SetKey< T2 >( ConvType< T1, T2 >( iSrc.Key< T1 >() ) );
            iDst.SetA< T2 >( ConvType< T1, T2 >( iSrc.A< T1 >() ) );
            return;
        }

        case eModelSig::kYUV:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToCMYK< float, T2 >( temp, iDst );
            return;
        }

        case eModelSig::kLab:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToCMYK< float, T2 >( temp, iDst );
            return;

        }

        case eModelSig::kXYZ:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToCMYK< float, T2 >( temp, iDst );
            return;
        }

        case eModelSig::kYxy:
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
        case eModelSig::kAny:
        {
            ULIS2_CRASH_DELIBERATE;
            return;
        }

        case eModelSig::kGrey:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToYUV< float, T2 >( temp, iDst );
            return;
        }

        case eModelSig::kRGB:
        {
            float r = ConvType< T1, float >( iSrc.R< T1 >() );
            float g = ConvType< T1, float >( iSrc.G< T1 >() );
            float b = ConvType< T1, float >( iSrc.B< T1 >() );
            float y = 0.299f * r + 0.587f * g + 0.114f * b;
            float u = 0.492f * ( b - y );
            float v = 0.877f * ( r - y );
            iDst.SetLuma< T2 >( ConvType< float, T2 >( y ) );
            iDst.SetU< T2 >( ConvType< float, T2 >( u ) );
            iDst.SetV< T2 >( ConvType< float, T2 >( v ) );
            iDst.SetA< T2 >( ConvType< T1, T2 >( iSrc.A< T1 >() ) );
            return;
        }

        case eModelSig::kHSV:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToYUV< float, T2 >( temp, iDst );
            return;
        }

        case eModelSig::kHSL:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToYUV< float, T2 >( temp, iDst );
            return;
        }

        case eModelSig::kCMY:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToYUV< float, T2 >( temp, iDst );
            return;
        }

        case eModelSig::kCMYK:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToYUV< float, T2 >( temp, iDst );
            return;
        }

        case eModelSig::kYUV:
        {
            iDst.SetLuma< T2 >( ConvType< T1, T2 >( iSrc.Luma< T1 >() ) );
            iDst.SetU< T2 >( ConvType< T1, T2 >( iSrc.U< T1 >() ) );
            iDst.SetV< T2 >( ConvType< T1, T2 >( iSrc.V< T1 >() ) );
            iDst.SetA< T2 >( ConvType< T1, T2 >( iSrc.A< T1 >() ) );
            return;
        }

        case eModelSig::kLab:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToYUV< float, T2 >( temp, iDst );
            return;

        }

        case eModelSig::kXYZ:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToYUV< float, T2 >( temp, iDst );
            return;
        }

        case eModelSig::kYxy:
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
        case eModelSig::kAny:
        {
            ULIS2_CRASH_DELIBERATE;
            return;
        }

        case eModelSig::kGrey:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToLab< float, T2 >( temp, iDst );
            return;
        }

        case eModelSig::kRGB:
        {
            FPixel temp( ULIS2_FORMAT_XYZAF );
            ToXYZ< T1, float >( iSrc, temp );
            ToLab< float, T2 >( temp, iDst );
            return;
        }

        case eModelSig::kHSV:
        {
            FPixel temp( ULIS2_FORMAT_XYZAF );
            ToXYZ< T1, float >( iSrc, temp );
            ToLab< float, T2 >( temp, iDst );
            return;
        }

        case eModelSig::kHSL:
        {
            FPixel temp( ULIS2_FORMAT_XYZAF );
            ToXYZ< T1, float >( iSrc, temp );
            ToLab< float, T2 >( temp, iDst );
            return;
        }

        case eModelSig::kCMY:
        {
            FPixel temp( ULIS2_FORMAT_XYZAF );
            ToXYZ< T1, float >( iSrc, temp );
            ToLab< float, T2 >( temp, iDst );
            return;
        }

        case eModelSig::kCMYK:
        {
            FPixel temp( ULIS2_FORMAT_XYZAF );
            ToXYZ< T1, float >( iSrc, temp );
            ToLab< float, T2 >( temp, iDst );
            return;
        }

        case eModelSig::kYUV:
        {
            FPixel temp( ULIS2_FORMAT_XYZAF );
            ToXYZ< T1, float >( iSrc, temp );
            ToLab< float, T2 >( temp, iDst );
            return;
        }

        case eModelSig::kLab:
        {
            iDst.SetL< T2 >( ConvType< T1, T2 >( iSrc.L< T1 >() ) );
            iDst.Seta< T2 >( ConvType< T1, T2 >( iSrc.a< T1 >() ) );
            iDst.Setb< T2 >( ConvType< T1, T2 >( iSrc.b< T1 >() ) );
            iDst.SetA< T2 >( ConvType< T1, T2 >( iSrc.A< T1 >() ) );
            return;
        }

        case eModelSig::kXYZ:
        {
            cmsCIELab Lab;
            cmsCIEXYZ XYZ;
            cmsCIEXYZ D65 = { 95.047f, 100.00f, 108.883f };
            Lab.L = ConvType< T1, double >( iSrc.L< T1 >() );
            Lab.a = ConvType< T1, double >( iSrc.a< T1 >() );
            Lab.b = ConvType< T1, double >( iSrc.b< T1 >() );
            cmsLab2XYZ( &D65, &XYZ, &Lab );
            iDst.SetX< T2 >( ConvType< double, T2 >( XYZ.X ) );
            iDst.SetY< T2 >( ConvType< double, T2 >( XYZ.Y ) );
            iDst.SetZ< T2 >( ConvType< double, T2 >( XYZ.Z ) );
            iDst.SetA< T2 >( ConvType< T1, T2 >( iSrc.A< T1 >() ) );
            return;
        }

        case eModelSig::kYxy:
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
        case eModelSig::kAny:
        {
            ULIS2_CRASH_DELIBERATE;
            return;
        }

        case eModelSig::kGrey:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToXYZ< float, T2 >( temp, iDst );
            return;
        }

        case eModelSig::kRGB:
        {
            // Note: this is sRGB under D65
            float r = ConvType< T1, float >( iSrc.R< T1 >() );
            float g = ConvType< T1, float >( iSrc.G< T1 >() );
            float b = ConvType< T1, float >( iSrc.B< T1 >() );
            float x = 0.4124f * r + 0.3576f * g + 0.1805f * b;
            float y = 0.2126f * r + 0.7152f * g + 0.0722f * b;
            float z = 0.0193f * r + 0.1192f * g + 0.9505f * b;
            iDst.SetX< T2 >( ConvType< float, T2 >( r ) );
            iDst.SetY< T2 >( ConvType< float, T2 >( g ) );
            iDst.SetZ< T2 >( ConvType< float, T2 >( b ) );
            iDst.SetA< T2 >( ConvType< T1, T2 >( iSrc.A< T1 >() ) );
            return;
        }

        case eModelSig::kHSV:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToXYZ< float, T2 >( temp, iDst );
            return;
        }

        case eModelSig::kHSL:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToXYZ< float, T2 >( temp, iDst );
            return;
        }

        case eModelSig::kCMY:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToXYZ< float, T2 >( temp, iDst );
            return;
        }

        case eModelSig::kCMYK:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToXYZ< float, T2 >( temp, iDst );
            return;
        }

        case eModelSig::kYUV:
        {
            FPixel temp( ULIS2_FORMAT_RGBAF );
            ToRGB< T1, float >( iSrc, temp );
            ToXYZ< float, T2 >( temp, iDst );
            return;
        }

        case eModelSig::kLab:
        {
            cmsCIELab Lab;
            cmsCIEXYZ XYZ;
            cmsCIEXYZ D65 = { 95.047f, 100.00f, 108.883f };
            Lab.L = ConvType< T1, double >( iSrc.L< T1 >() );
            Lab.a = ConvType< T1, double >( iSrc.a< T1 >() );
            Lab.b = ConvType< T1, double >( iSrc.b< T1 >() );
            cmsLab2XYZ( &D65, &XYZ, &Lab );
            iDst.SetX< T2 >( ConvType< double, T2 >( XYZ.X ) );
            iDst.SetY< T2 >( ConvType< double, T2 >( XYZ.Y ) );
            iDst.SetZ< T2 >( ConvType< double, T2 >( XYZ.Z ) );
            iDst.SetA< T2 >( ConvType< T1, T2 >( iSrc.A< T1 >() ) );
            return;
        }

        case eModelSig::kXYZ:
        {
            iDst.SetX< T2 >( ConvType< T1, T2 >( iSrc.X< T1 >() ) );
            iDst.SetY< T2 >( ConvType< T1, T2 >( iSrc.Y< T1 >() ) );
            iDst.SetZ< T2 >( ConvType< T1, T2 >( iSrc.Z< T1 >() ) );
            iDst.SetA< T2 >( ConvType< T1, T2 >( iSrc.A< T1 >() ) );
            return;
        }

        case eModelSig::kYxy:
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
        case eModelSig::kAny:
        {
            ULIS2_CRASH_DELIBERATE;
            return;
        }

        case eModelSig::kGrey:
        {
            FPixel temp( ULIS2_FORMAT_XYZF );
            ToXYZ< T1, float >( iSrc, temp );
            ToYxy< float, T2 >( temp, iDst );
            return;
        }

        case eModelSig::kRGB:
        {
            FPixel temp( ULIS2_FORMAT_XYZF );
            ToXYZ< T1, float >( iSrc, temp );
            ToYxy< float, T2 >( temp, iDst );
            return;
        }

        case eModelSig::kHSV:
        {
            FPixel temp( ULIS2_FORMAT_XYZF );
            ToXYZ< T1, float >( iSrc, temp );
            ToYxy< float, T2 >( temp, iDst );
            return;
        }

        case eModelSig::kHSL:
        {
            FPixel temp( ULIS2_FORMAT_XYZF );
            ToXYZ< T1, float >( iSrc, temp );
            ToYxy< float, T2 >( temp, iDst );
            return;
        }

        case eModelSig::kCMY:
        {
            FPixel temp( ULIS2_FORMAT_XYZF );
            ToXYZ< T1, float >( iSrc, temp );
            ToYxy< float, T2 >( temp, iDst );
            return;
        }

        case eModelSig::kCMYK:
        {
            FPixel temp( ULIS2_FORMAT_XYZF );
            ToXYZ< T1, float >( iSrc, temp );
            ToYxy< float, T2 >( temp, iDst );
            return;
        }

        case eModelSig::kYUV:
        {
            FPixel temp( ULIS2_FORMAT_XYZF );
            ToXYZ< T1, float >( iSrc, temp );
            ToYxy< float, T2 >( temp, iDst );
            return;
        }

        case eModelSig::kLab:
        {
            FPixel temp( ULIS2_FORMAT_XYZF );
            ToXYZ< T1, float >( iSrc, temp );
            ToYxy< float, T2 >( temp, iDst );
            return;
        }

        case eModelSig::kXYZ:
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

        case eModelSig::kYxy:
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
        case eModelSig::kAny:   ULIS2_CRASH_DELIBERATE;             return;
        case eModelSig::kGrey:  ToGrey< T1, T2 >( iSrc, iDst );     return;
        case eModelSig::kRGB:   ToRGB< T1, T2 >( iSrc, iDst );      return;
        case eModelSig::kHSV:   ToHSV< T1, T2 >( iSrc, iDst );      return;
        case eModelSig::kHSL:   ToHSL< T1, T2 >( iSrc, iDst );      return;
        case eModelSig::kCMY:   ToCMY< T1, T2 >( iSrc, iDst );      return;
        case eModelSig::kCMYK:  ToCMYK< T1, T2 >( iSrc, iDst );     return;
        case eModelSig::kYUV:   ToYUV< T1, T2 >( iSrc, iDst );      return;
        case eModelSig::kLab:   ToLab< T1, T2 >( iSrc, iDst );      return;
        case eModelSig::kXYZ:   ToXYZ< T1, T2 >( iSrc, iDst );      return;
        case eModelSig::kYxy:   ToYxy< T1, T2 >( iSrc, iDst );      return;
    }
}


void Conv( const IPixel& iSrc, IPixel& iDst )
{
    switch( iSrc.Type() ) {
        case eType::kUint8: switch( iDst.Type() ) {
                case eType::kUint8:     Conv_imp< uint8, uint8 >( iSrc, iDst );     return;
                case eType::kUint16:    Conv_imp< uint8, uint16 >( iSrc, iDst );    return;
                case eType::kUint32:    Conv_imp< uint8, uint32 >( iSrc, iDst );    return;
                case eType::kFloat:     Conv_imp< uint8, float >( iSrc, iDst );     return;
                case eType::kDouble:    Conv_imp< uint8, double >( iSrc, iDst );    return; }
        case eType::kUint16: switch( iDst.Type() ) {
                case eType::kUint8:     Conv_imp< uint16, uint8 >( iSrc, iDst );    return;
                case eType::kUint16:    Conv_imp< uint16, uint16 >( iSrc, iDst );   return;
                case eType::kUint32:    Conv_imp< uint16, uint32 >( iSrc, iDst );   return;
                case eType::kFloat:     Conv_imp< uint16, float >( iSrc, iDst );    return;
                case eType::kDouble:    Conv_imp< uint16, double >( iSrc, iDst );   return; }
        case eType::kUint32: switch( iDst.Type() ) {
                case eType::kUint8:     Conv_imp< uint32, uint8 >( iSrc, iDst );    return;
                case eType::kUint16:    Conv_imp< uint32, uint16 >( iSrc, iDst );   return;
                case eType::kUint32:    Conv_imp< uint32, uint32 >( iSrc, iDst );   return;
                case eType::kFloat:     Conv_imp< uint32, float >( iSrc, iDst );    return;
                case eType::kDouble:    Conv_imp< uint32, double >( iSrc, iDst );   return; }
        case eType::kFloat: switch( iDst.Type() ) {
                case eType::kUint8:     Conv_imp< float, uint8 >( iSrc, iDst );     return;
                case eType::kUint16:    Conv_imp< float, uint16 >( iSrc, iDst );    return;
                case eType::kUint32:    Conv_imp< float, uint32 >( iSrc, iDst );    return;
                case eType::kFloat:     Conv_imp< float, float >( iSrc, iDst );     return;
                case eType::kDouble:    Conv_imp< float, double >( iSrc, iDst );    return; }
        case eType::kDouble: switch( iDst.Type() ) {
                case eType::kUint8:     Conv_imp< double, uint8 >( iSrc, iDst );     return;
                case eType::kUint16:    Conv_imp< double, uint16 >( iSrc, iDst );    return;
                case eType::kUint32:    Conv_imp< double, uint32 >( iSrc, iDst );    return;
                case eType::kFloat:     Conv_imp< double, float >( iSrc, iDst );     return;
                case eType::kDouble:    Conv_imp< double, double >( iSrc, iDst );    return; }
    }
}

ULIS2_NAMESPACE_END

