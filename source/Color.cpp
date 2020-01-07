// Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Color.cpp
* @author       Clement Berthaud
* @brief        This file provides the definition for the FColor class.
* @copyright    Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include "Color.h"
#include "Maths.h"
#include <cstdlib>
#include <cmath>

ULIS2_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
// FColor
//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------- Construction
FColor::FColor()
{
    SetRGB( 0, 0, 0 );
}


FColor::FColor( int r, int g, int b, int alpha )
{
    SetRGB( r, g, b, alpha );
}


FColor::FColor( eColorModel iMode )
    : mMode( iMode )
{
    mRepr.rgb = { 0, 0, 0, 0, 0 };
}


FColor::FColor( uint32 rgbHexValue )
{
    SetRGBHexValue( rgbHexValue );
}


//--------------------------------------------------------------------------------------
//----------------------------------------------------------------- Comparison Operators


bool
FColor::operator==( const  FColor& Other )  const
{
    return mMode == Other.mMode &&
        mRepr.array[0] == Other.mRepr.array[0] &&
        mRepr.array[1] == Other.mRepr.array[1] &&
        mRepr.array[2] == Other.mRepr.array[2] &&
        mRepr.array[3] == Other.mRepr.array[3] &&
        mRepr.array[4] == Other.mRepr.array[4];
}


bool
FColor::operator!=( const  FColor& Other )  const
{
    return !operator==( Other );
}


//--------------------------------------------------------------------------------------
//-------------------------------------------------------------- Instance Conversion API



FColor
FColor::ToGrey()  const
{
    if( mMode == eColorModel::kG )
        return  *this;

    if( mMode != eColorModel::kRGB )
        return  ToRGB().ToGrey();

    FColor out;
    int r = Red();
    int g = Green();
    int b = Blue();
    int grey = ( r + g + b ) / 3;

    out.SetGrey( grey, Alpha() );
    return  out;
}


FColor
FColor::ToRGB()  const
{
    if( mMode == eColorModel::kRGB )
        return  *this;

    FColor out;
    switch( mMode )
    {
        case eColorModel::kG:
        {
            int grey = Grey();
            out.SetRGB( grey, grey, grey, Alpha() );
            break;
        }

        case eColorModel::kHSL:
        {
            float h = HSLHueF() * 360;
            float s = HSLSaturationF();
            float l = LightnessF();
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
            out.SetRGBF( r + m, g + m, b + m, AlphaF() );
            break;
        }


        case eColorModel::kHSV:
        {
            float h = HSVHueF();
            float s = HSVSaturationF();
            float v = ValueF();
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

            out.SetRGBF( r, g, b, AlphaF() );
            break;
        }


        case eColorModel::kCMYK:
        {
            float c = CyanF();
            float m = MagentaF();
            float y = YellowF();
            float k = KeyF();
            float r = 1.f - ( c * ( 1.f - k ) + k );
            float g = 1.f - ( m * ( 1.f - k ) + k );
            float b = 1.f - ( y * ( 1.f - k ) + k );
            out.SetRGBF( r, g, b, AlphaF() );
            break;
        }


        default:
        {
            break;
        }
    }

    return  out;
}


FColor
FColor::ToHSL()  const
{
    if( mMode == eColorModel::kHSL )
        return  *this;

    if( mMode != eColorModel::kRGB )
        return  ToRGB().ToHSL();

    FColor out;
    float r = RedF();
    float g = GreenF();
    float b = BlueF();
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

    out.SetHSLF( h, s, l, AlphaF() );
    return  out;
}


FColor
FColor::ToHSV()  const
{
    if( mMode == eColorModel::kHSV )
        return  *this;

    if( mMode != eColorModel::kRGB )
        return  ToRGB().ToHSV();

    FColor out;
    float r = RedF();
    float g = GreenF();
    float b = BlueF();
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

    out.SetHSVF( h, s, v, AlphaF() );
    return  out;
}


FColor
FColor::ToCMYK()  const
{
    if( mMode == eColorModel::kCMYK )
        return  *this;

    if( mMode != eColorModel::kRGB )
        return  ToRGB().ToCMYK();

    FColor out;
    float r = RedF();
    float g = GreenF();
    float b = BlueF();
    float ik = FMaths::Max3( r, g, b );
    float k = 1.f - ik;

    if( ik == 0 )
        ik = 1; //Division by 0 countermeasure, doesn't affect the result

    float c = ( ( 1.f - r ) - k ) / ( ik );
    float m = ( ( 1.f - g ) - k ) / ( ik );
    float y = ( ( 1.f - b ) - k ) / ( ik );
    out.SetCMYKF( c, m, y, k, AlphaF() );
    return  out;
}


FColor
FColor::ToModel( eColorModel iModel )  const
{
    if( mMode == iModel )
        return  *this;

    switch( iModel )
    {
        case eColorModel::kG:      return  ToGrey();
        case eColorModel::kRGB:    return  ToRGB();
        case eColorModel::kHSL:    return  ToHSL();
        case eColorModel::kHSV:    return  ToHSV();
        case eColorModel::kCMYK:   return  ToCMYK();
        default: return  FColor( eColorModel::kInvalid );
    }
}


//--------------------------------------------------------------------------------------
//-------------------------------------------------------------------- Static Makers API


//static
FColor
FColor::FromRGBHexValue( uint32 rgbHexValue, int alpha )
{
    FColor out;
    out.SetRGBHexValue( rgbHexValue, alpha );
    return out;
}


//static
FColor
FColor::FromGrey( int g, int alpha )
{
    FColor out;
    out.SetGrey( g, alpha );
    return out;
}


//static
FColor
FColor::FromRGB( int r, int g, int b, int alpha )
{
    FColor out;
    out.SetRGB( r, g, b, alpha );
    return out;
}


//static
FColor
FColor::FromHSL( int h, int s, int l, int alpha )
{
    FColor out;
    out.SetHSL( h, s, l, alpha );
    return out;
}


//static
FColor
FColor::FromHSV( int h, int s, int v, int alpha )
{
    FColor out;
    out.SetHSV( h, s, v, alpha );
    return out;
}


//static
FColor
FColor::FromCMYK( int c, int m, int y, int k, int alpha )
{
    FColor out;
    out.SetCMYK( c, m, y, k );
    return out;
}


//static
FColor
FColor::FromGreyF( float g, float alpha )
{
    FColor out;
    out.SetGreyF( g, alpha );
    return  out;
}


//static
FColor
FColor::FromRGBF( float r, float g, float b, float alpha )
{
    FColor out;
    out.SetRGBF( r, g, b, alpha );
    return  out;
}


//static
FColor
FColor::FromHSLF( float h, float s, float l, float alpha )
{
    FColor out;
    out.SetHSLF( h, s, l, alpha );
    return  out;
}


//static
FColor
FColor::FromHSVF( float h, float s, float v, float alpha )
{
    FColor out;
    out.SetHSVF( h, s, v, alpha );
    return  out;
}


//static
FColor
FColor::FromCMYKF( float c, float m, float y, float k, float alpha )
{
    FColor out;
    out.SetCMYKF( c, m, y, k, alpha );
    return  out;
}


//static
bool
FColor::IsSimilar( const FColor& A, const FColor& B, int threshold )
{
    FColor Argb = A.ToRGB();
    FColor Brgb = B.ToRGB();
    int AR = Argb.Red();
    int AG = Argb.Green();
    int AB = Argb.Blue();
    int Aalpha = Argb.Alpha();
    int BR = Brgb.Red();
    int BG = Brgb.Green();
    int BB = Brgb.Blue();
    int Balpha = Brgb.Alpha();
    return  ( fabs( AR - BR ) <= threshold ) &&
            ( fabs( AG - BG ) <= threshold ) &&
            ( fabs( AB - BB ) <= threshold ) &&
            ( fabs( Aalpha - Balpha ) <= threshold );
}

//--------------------------------------------------------------------------------------
//------------------------------------------ Instance Representation Access API, Getters


eColorModel
FColor::Mode()  const
{
    return  mMode;
}


int
FColor::Alpha()  const
{
    return  mRepr.rgb.alpha >> 8;
}


float
FColor::AlphaF()  const
{
    return  mRepr.rgb.alpha / float( UINT16_MAX );
}


// Hex
uint32
FColor::RGBHexValue()  const
{
    if( mMode != eColorModel::kRGB )
    {
        FColor rgb = this->ToRGB();
        int r = rgb.Red();
        int g = rgb.Green();
        int b = rgb.Blue();
        uint32 out = ( uint32( r ) << 16 ) + ( uint32( g ) << 8 ) + ( uint32( b ) << 0 );
        return  out;
    }

    int r = mRepr.rgb.r;
    int g = mRepr.rgb.g;
    int b = mRepr.rgb.b;
    uint32 out = ( uint32( r ) << 16 ) + ( uint32( g ) << 8 ) + ( uint32( b ) << 0 );
    return  out;
}

 // Grey
int
FColor::Grey()  const
{
    if( mMode != eColorModel::kG )
        return  ToGrey().Grey();
    return  mRepr.grey.g >> 8;
}


float
FColor::GreyF()  const
{
    if( mMode != eColorModel::kG )
        return  ToGrey().GreyF();
    return  mRepr.grey.g / float( UINT16_MAX );
}


// RGB
int
FColor::Red()  const
{
    if( mMode != eColorModel::kRGB )
        return  ToRGB().Red();
    return  mRepr.rgb.r >> 8;
}


int
FColor::Green()  const
{
    if( mMode != eColorModel::kRGB )
        return  ToRGB().Green();
    return  mRepr.rgb.g >> 8;
}


int
FColor::Blue()  const
{
    if( mMode != eColorModel::kRGB )
        return  ToRGB().Blue();
    return  mRepr.rgb.b >> 8;
}


float
FColor::RedF()  const
{
    if( mMode != eColorModel::kRGB )
        return  ToRGB().RedF();
    return  mRepr.rgb.r / float( UINT16_MAX );
}


float
FColor::GreenF()  const
{
    if( mMode != eColorModel::kRGB )
        return  ToRGB().GreenF();
    return  mRepr.rgb.g / float( UINT16_MAX );
}


float
FColor::BlueF()  const
{
    if( mMode != eColorModel::kRGB )
        return  ToRGB().BlueF();
    return  mRepr.rgb.b / float( UINT16_MAX );
}


// HSV Alias
int
FColor::Hue()  const
{
    return  HSVHue();
}


int
FColor::Saturation()  const
{
    return  HSVSaturation();
}


float
FColor::HueF()  const
{
    return  HSVHueF();
}


float
FColor::SaturationF()  const
{
    return  HSVSaturationF();
}


// HSL
int
FColor::HSLHue()  const
{
    if( mMode != eColorModel::kHSL )
        return  ToHSL().HSLHue();
    return  mRepr.hsl.h / 100;
}


int
FColor::HSLSaturation()  const
{
    if( mMode != eColorModel::kHSL )
        return  ToHSL().HSLSaturation();
    return  mRepr.hsl.s >> 8;
}


int
FColor::Lightness()  const
{
    if( mMode != eColorModel::kHSL )
        return  ToHSL().Lightness();
    return  mRepr.hsl.l >> 8;
}


float
FColor::HSLHueF()  const
{
    if( mMode != eColorModel::kHSL )
        return  ToHSL().HSLHueF();
    return  mRepr.hsl.h / 36000.f ;
}


float
FColor::HSLSaturationF()  const
{
    if( mMode != eColorModel::kHSL )
        return  ToHSL().HSLSaturationF();
    return  mRepr.hsl.s / float( UINT16_MAX );
}


float
FColor::LightnessF()  const
{
    if( mMode != eColorModel::kHSL )
        return  ToHSL().LightnessF();
    return  mRepr.hsl.l / float( UINT16_MAX );
}


// HSV
int
FColor::HSVHue()  const
{
    if( mMode != eColorModel::kHSV )
        return  ToHSV().HSVHue();
    return  mRepr.hsv.h / 100;
}


int
FColor::HSVSaturation()  const
{
    if( mMode != eColorModel::kHSV )
        return  ToHSV().HSVSaturation();
    return  mRepr.hsv.s >> 8;
}


int
FColor::Value()  const
{
    if( mMode != eColorModel::kHSV )
        return  ToHSV().Value();
    return  mRepr.hsv.v >> 8;
}


float
FColor::HSVHueF()  const
{
    if( mMode != eColorModel::kHSV )
        return  ToHSV().HSVHueF();
    return  mRepr.hsv.h / 36000.f ;
}


float
FColor::HSVSaturationF()  const
{
    if( mMode != eColorModel::kHSV )
        return  ToHSV().HSVSaturationF();
    return  mRepr.hsv.s / float( UINT16_MAX );
}


float
FColor::ValueF()  const
{
    if( mMode != eColorModel::kHSV )
        return  ToHSV().ValueF();
    return  mRepr.hsv.v / float( UINT16_MAX );
}


// CMYK
int
FColor::Cyan()  const
{
    if( mMode != eColorModel::kCMYK )
        return  ToCMYK().Cyan();
    return  mRepr.cmyk.c >> 8;
}


int
FColor::Magenta()  const
{
    if( mMode != eColorModel::kCMYK )
        return  ToCMYK().Magenta();
    return  mRepr.cmyk.m >> 8;
}


int
FColor::Yellow()  const
{
    if( mMode != eColorModel::kCMYK )
        return  ToCMYK().Yellow();
    return  mRepr.cmyk.y >> 8;
}


int
FColor::Key()  const
{
    if( mMode != eColorModel::kCMYK )
        return  ToCMYK().Black();
    return  mRepr.cmyk.k >> 8;
}


int
FColor::Black()  const
{
    return  Key();
}


float
FColor::CyanF()  const
{
    if( mMode != eColorModel::kCMYK )
        return  ToCMYK().CyanF();
    return  mRepr.cmyk.c / float( UINT16_MAX );
}


float
FColor::MagentaF()  const
{
    if( mMode != eColorModel::kCMYK )
        return  ToCMYK().MagentaF();
    return  mRepr.cmyk.m / float( UINT16_MAX );
}


float
FColor::YellowF()  const
{
    if( mMode != eColorModel::kCMYK )
        return  ToCMYK().YellowF();
    return  mRepr.cmyk.y / float( UINT16_MAX );
}


float
FColor::KeyF()  const
{
    if( mMode != eColorModel::kCMYK )
        return  ToCMYK().KeyF();
    return  mRepr.cmyk.k / float( UINT16_MAX );
}


float
FColor::BlackF()  const
{
    return  KeyF();
}


//--------------------------------------------------------------------------------------
//------------------------------------------ Instance Representation Access API, Setters


void
FColor::SetAlpha( int value )
{
    mRepr.rgb.alpha = 0x101 * FMaths::Clamp( value, 0, 0xff );
}

void
FColor::SetAlphaF( float value )
{
    mRepr.rgb.alpha = uint16( floor( FMaths::Clamp( value, 0.f, 1.f ) * float( UINT16_MAX ) ) );
}


void
FColor::SetGrey( int g )
{
    if( mMode != eColorModel::kG )
        SetGrey( g, Alpha() );
    else
        mRepr.grey.g = 0x101 * FMaths::Clamp( g, 0, 0xff );
}


void
FColor::SetGreyF( float g )
{
    if( mMode != eColorModel::kG )
        SetGreyF( g, AlphaF() );
    else
        mRepr.grey.g = uint16( floor( FMaths::Clamp( g, 0.f, 1.f ) * float( UINT16_MAX ) ) );
}


void
FColor::SetRed( int value )
{
    if( mMode != eColorModel::kRGB )
        SetRGB( value, Green(), Blue(), Alpha() );
    else
        mRepr.rgb.r = 0x101 * FMaths::Clamp( value, 0, 0xff );
}


void
FColor::SetGreen( int value )
{
    if( mMode != eColorModel::kRGB )
        SetRGB( Red(), value, Blue(), Alpha() );
    else
        mRepr.rgb.g = 0x101 * FMaths::Clamp( value, 0, 0xff );
}


void
FColor::SetBlue( int value )
{
    if( mMode != eColorModel::kRGB )
        SetRGB( Red(), Green(), value, Alpha() );
    else
        mRepr.rgb.b = 0x101 * FMaths::Clamp( value, 0, 0xff );
}


void
FColor::SetRedF( float value )
{
    if( mMode != eColorModel::kRGB )
        SetRGBF( value, GreenF(), BlueF(), AlphaF() );
    else
        mRepr.rgb.r = uint16( floor( FMaths::Clamp( value, 0.f, 1.f ) * float( UINT16_MAX ) ) );
}


void
FColor::SetGreenF( float value )
{
    if( mMode != eColorModel::kRGB )
        SetRGBF( RedF(), value, BlueF(), AlphaF() );
    else
        mRepr.rgb.g = uint16( floor( FMaths::Clamp( value, 0.f, 1.f ) * float( UINT16_MAX ) ) );
}


void
FColor::SetBlueF( float value )
{
    if( mMode != eColorModel::kRGB )
        SetRGBF( RedF(), GreenF(), value, AlphaF() );
    else
        mRepr.rgb.b = uint16( floor( FMaths::Clamp( value, 0.f, 1.f ) * float( UINT16_MAX ) ) );
}


void
FColor::SetRGBHexValue( uint32 rgbHexValue, int alpha )
{
    uint32 rmask = 0x00ff0000;
    uint32 gmask = 0x0000ff00;
    uint32 bmask = 0x000000ff;
    int r = static_cast< int >( uint32( rgbHexValue & rmask ) >> 16 );
    int g = static_cast< int >( uint32( rgbHexValue & gmask ) >> 8 );
    int b = static_cast< int >( uint32( rgbHexValue & bmask ) >> 0 );
    SetRGB( r, g, b, alpha );
}



void
FColor::SetGrey( int g, int alpha )
{
    mMode = eColorModel::kG;
    mRepr.grey.alpha = 0x101 * FMaths::Clamp( alpha, 0, 0xff );
    mRepr.grey.g     = 0x101 * FMaths::Clamp( g, 0, 0xff );
    mRepr.grey._0    = 0;
    mRepr.grey._1    = 0;
    mRepr.grey._     = 0;
}


void
FColor::SetRGB( int r, int g, int b, int alpha )
{
    mMode = eColorModel::kRGB;
    mRepr.rgb.alpha = 0x101 * FMaths::Clamp( alpha, 0, 0xff );
    mRepr.rgb.r     = 0x101 * FMaths::Clamp( r, 0, 0xff );
    mRepr.rgb.g     = 0x101 * FMaths::Clamp( g, 0, 0xff );
    mRepr.rgb.b     = 0x101 * FMaths::Clamp( b, 0, 0xff );
    mRepr.rgb._     = 0;
}


void
FColor::SetHSL( int h, int s, int l, int alpha )
{
    while( h < 0 ) { h += 360; }
    mMode = eColorModel::kHSL;
    mRepr.hsl.alpha = 0x101 * FMaths::Clamp( alpha, 0, 0xff );
    mRepr.hsl.h     = ( h % 360 ) * 100;
    mRepr.hsl.s     = 0x101 * FMaths::Clamp( s, 0, 0xff );
    mRepr.hsl.l     = 0x101 * FMaths::Clamp( l, 0, 0xff );
    mRepr.hsl._     = 0;
}


void
FColor::SetHSV( int h, int s, int v, int alpha )
{
    while( h < 0 ) { h += 360; }
    mMode = eColorModel::kHSV;
    mRepr.hsv.alpha = 0x101 * FMaths::Clamp( alpha, 0, 0xff );
    mRepr.hsv.h     = ( h % 360 ) * 100;
    mRepr.hsv.s     = 0x101 * FMaths::Clamp( s, 0, 0xff );
    mRepr.hsv.v     = 0x101 * FMaths::Clamp( v, 0, 0xff );
    mRepr.hsv._     = 0;
}


void
FColor::SetCMYK( int c, int m, int y, int k, int alpha )
{
    mMode = eColorModel::kCMYK;
    mRepr.cmyk.alpha = 0x101 * FMaths::Clamp( alpha, 0, 0xff );
    mRepr.cmyk.c     = 0x101 * FMaths::Clamp( c, 0, 0xff );
    mRepr.cmyk.m     = 0x101 * FMaths::Clamp( m, 0, 0xff );
    mRepr.cmyk.y     = 0x101 * FMaths::Clamp( y, 0, 0xff );
    mRepr.cmyk.k     = 0x101 * FMaths::Clamp( k, 0, 0xff );
}


void
FColor::SetGreyF( float g, float alpha )
{
    mMode = eColorModel::kG;
    mRepr.grey.alpha = uint16( floor( FMaths::Clamp( alpha, 0.f, 1.f ) * float( UINT16_MAX ) ) );
    mRepr.grey.g     = uint16( floor( FMaths::Clamp( g, 0.f, 1.f ) * float( UINT16_MAX ) ) );
    mRepr.grey._0    = 0;
    mRepr.grey._1    = 0;
    mRepr.grey._     = 0;
}


void
FColor::SetRGBF( float r, float g, float b, float alpha )
{
    mMode = eColorModel::kRGB;
    mRepr.rgb.alpha = uint16( floor( FMaths::Clamp( alpha, 0.f, 1.f ) * float( UINT16_MAX ) ) );
    mRepr.rgb.r     = uint16( floor( FMaths::Clamp( r, 0.f, 1.f ) * float( UINT16_MAX ) ) );
    mRepr.rgb.g     = uint16( floor( FMaths::Clamp( g, 0.f, 1.f ) * float( UINT16_MAX ) ) );
    mRepr.rgb.b     = uint16( floor( FMaths::Clamp( b, 0.f, 1.f ) * float( UINT16_MAX ) ) );
    mRepr.rgb._     = 0;
}


void
FColor::SetHSLF( float h, float s, float l, float alpha )
{
    mMode = eColorModel::kHSL;
    mRepr.hsl.alpha = uint16( floor( FMaths::Clamp( alpha, 0.f, 1.f ) * float( UINT16_MAX ) ) );
    mRepr.hsl.h     = uint16( floor( FMaths::Clamp( h, 0.f, 1.f ) * 36000 ) );
    mRepr.hsl.s     = uint16( floor( FMaths::Clamp( s, 0.f, 1.f ) * float( UINT16_MAX ) ) );
    mRepr.hsl.l     = uint16( floor( FMaths::Clamp( l, 0.f, 1.f ) * float( UINT16_MAX ) ) );
    mRepr.hsl._     = 0;
}


void
FColor::SetHSVF( float h, float s, float v, float alpha )
{
    mMode = eColorModel::kHSV;
    mRepr.hsv.alpha = uint16( floor( FMaths::Clamp( alpha, 0.f, 1.f ) * float( UINT16_MAX ) ) );
    mRepr.hsv.h     = uint16( floor( FMaths::Clamp( h, 0.f, 1.f ) * 36000 ) );
    mRepr.hsv.s     = uint16( floor( FMaths::Clamp( s, 0.f, 1.f ) * float( UINT16_MAX ) ) );
    mRepr.hsv.v     = uint16( floor( FMaths::Clamp( v, 0.f, 1.f ) * float( UINT16_MAX ) ) );
    mRepr.hsv._     = 0;
}


void
FColor::SetCMYKF( float c, float m, float y, float k, float alpha )
{
    mMode = eColorModel::kCMYK;
    mRepr.cmyk.alpha = uint16( floor( FMaths::Clamp( alpha, 0.f, 1.f ) * float( UINT16_MAX ) ) );
    mRepr.cmyk.c     = uint16( floor( FMaths::Clamp( c, 0.f, 1.f ) * float( UINT16_MAX ) ) );
    mRepr.cmyk.m     = uint16( floor( FMaths::Clamp( m, 0.f, 1.f ) * float( UINT16_MAX ) ) );
    mRepr.cmyk.y     = uint16( floor( FMaths::Clamp( y, 0.f, 1.f ) * float( UINT16_MAX ) ) );
    mRepr.cmyk.k     = uint16( floor( FMaths::Clamp( k, 0.f, 1.f ) * float( UINT16_MAX ) ) );
}

ULIS2_NAMESPACE_END

