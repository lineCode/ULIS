/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Color.CColor.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once

#include "ULIS/Data/ULIS.Data.Spec.h"

namespace ULIS {

/////////////////////////////////////////////////////
// Supported CColor Models
enum class eCColorModel : int
{
    kInvalid,
    kG,
    kRGB,
    kHSL,
    kHSV,
    kCMYK,
};

/////////////////////////////////////////////////////
// Model Correspondance
static e_cm  ColorModelFromCColorModel( eCColorModel iValue )
{
    switch( iValue )
    {
        case eCColorModel::kInvalid:    return  e_cm::kG;
        case eCColorModel::kG:          return  e_cm::kG;
        case eCColorModel::kRGB:        return  e_cm::kRGB;
        case eCColorModel::kHSL:        return  e_cm::kHSL;
        case eCColorModel::kHSV:        return  e_cm::kHSV;
        case eCColorModel::kCMYK:       return  e_cm::kCMYK;
    }
}

static eCColorModel  CColorModelFromColorModel( e_cm iValue )
{
    switch( iValue )
    {
        case e_cm::kG:      return  eCColorModel::kG;
        case e_cm::kRGB:    return  eCColorModel::kRGB;
        case e_cm::kHSL:    return  eCColorModel::kHSL;
        case e_cm::kHSV:    return  eCColorModel::kHSV;
        case e_cm::kCMYK:   return  eCColorModel::kCMYK;
        default:            return  eCColorModel::kInvalid;
    }
}

/////////////////////////////////////////////////////
// CColor
class  CColor
{
public:
    // Enums
    

public:
    // Construction
    CColor();
    CColor( int r, int g, int b, int alpha = 255 );
    CColor( eCColorModel );
    CColor( uint32 rgbHexValue );

public:
    // Comparison Operators
    bool  operator==( const  CColor& Other )  const;
    bool  operator!=( const  CColor& Other )  const;

public:
    // Instance Conversion API
    CColor  ToRGB()  const;
    CColor  ToHSL()  const;
    CColor  ToHSV()  const;
    CColor  ToCMYK()  const;

public:
    // Static Makers API
    static  CColor  FromRGBHexValue( uint32 rgbHexValue, int alpha = 255 );
    static  CColor  FromRGB( int r, int g, int b, int alpha = 255 );
    static  CColor  FromHSL( int h, int s, int l, int alpha = 255 );
    static  CColor  FromHSV( int h, int s, int v, int alpha = 255 );
    static  CColor  FromCMYK( int c, int m, int y, int k, int alpha = 255 );

    static  CColor  FromRGBF( float r, float g, float b, float alpha = 1.f );
    static  CColor  FromHSLF( float h, float s, float l, float alpha = 1.f );
    static  CColor  FromHSVF( float h, float s, float v, float alpha = 1.f );
    static  CColor  FromCMYKF( float c, float m, float y, float k, float alpha = 1.f );

    static bool IsSimilar( const CColor& A, const CColor& B, int threshold = 1 );

public:
    // Instance Representation Access API, Getters
    eCColorModel    Mode()  const  { return  mMode; }
    int             Alpha()             const;
    float           AlphaF()            const;

    // Hex
    uint32  RGBHexValue()       const;

    // RGB
    int     Red()               const;
    int     Green()             const;
    int     Blue()              const;
    float   RedF()              const;
    float   GreenF()            const;
    float   BlueF()             const;

    // HSV Alias
    int     Hue()               const;
    int     Saturation()        const;
    float   HueF()              const;
    float   SaturationF()       const;

    // HSL
    int     HSLHue()            const;
    int     HSLSaturation()     const;
    int     Lightness()         const;
    float   HSLHueF()           const;
    float   HSLSaturationF()    const;
    float   LightnessF()        const;

    // HSV
    int     HSVHue()            const;
    int     HSVSaturation()     const;
    int     Value()             const;
    float   HSVHueF()           const;
    float   HSVSaturationF()    const;
    float   ValueF()            const;

    // CMYK
    int     Cyan()              const;
    int     Magenta()           const;
    int     Yellow()            const;
    int     Key()               const;
    int     Black()             const;
    float   CyanF()             const;
    float   MagentaF()          const;
    float   YellowF()           const;
    float   KeyF()              const;
    float   BlackF()            const;

public:
    // Instance Representation Access API, Setters
    void  SetAlpha( int );
    void  SetAlphaF( float );

    void  SetRed( int );
    void  SetGreen( int );
    void  SetBlue( int );
    void  SetRedF( float );
    void  SetGreenF( float );
    void  SetBlueF( float );

    void  SetRGBHexValue( uint32 rgbHexValue, int alpha = 255 );
    void  SetRGB( int r, int g, int b, int alpha = 255 );
    void  SetHSL( int h, int s, int l, int alpha = 255 );
    void  SetHSV( int h, int s, int v, int alpha = 255 );
    void  SetCMYK( int c, int m, int y, int k, int alpha = 255 );
    void  SetRGBF( float r, float g, float b, float alpha = 1.f );
    void  SetHSLF( float h, float s, float l, float alpha = 1.f );
    void  SetHSVF( float h, float s, float v, float alpha = 1.f );
    void  SetCMYKF( float c, float m, float y, float k, float alpha = 1.f );

private:
    // Private Data Members
    eCColorModel  mMode;
    union { // Union with pad '_', internal repr
        struct { uint16 alpha, r, g, b, _; } rgb;
        struct { uint16 alpha, h, s, l, _; } hsl;
        struct { uint16 alpha, h, s, v, _; } hsv;
        struct { uint16 alpha, c, m, y, k; } cmyk;
        uint16 array[5];
    } mRepr;
};

} // namespace ULIS
