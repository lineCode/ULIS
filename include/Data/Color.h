// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS3
*__________________
*
* @file         Color.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the FColor class.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"
#include "Data/Sample.h"

ULIS_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
/// @class      FColor
/// @brief      The FColor class provides a mean of storing and manipulating
///             colors in various formats.
/// @details    A FColor allocates its own storage space and is responsible for
///             its memory.
///
///             \sa ISample
///             \sa FPixel
class ULIS_API FColor final
    : public ISample
{
public:
    /*! Override destructor from pure virtual parent, manages lifetime of internal buffer. */
    ~FColor();

    /*! Default constructor, with default Format eFormat::Format_RGBA8 */
    FColor();

    /*! Constructor, from format and optional colorspace. */
    FColor( eFormat iFormat, const FColorSpace* iColorSpace = nullptr );

    /*! Constructor, from external data, format and optional colorspace. */
    FColor( const uint8* iData, eFormat iFormat, const FColorSpace* iColorSpace = nullptr );

    /*! Constructor, from pixel. */
    FColor( const FPixel& iPixel );

    /*! Copy Constructor */
    FColor( const FColor& iValue );

    /*! Move Constructor. */
    FColor( FColor&& iValue );

    /*! Assignment Operator. */
    FColor& operator=( const FColor& iOther );

    /*! Initializer list constructor */
    template< typename T >
    FColor( eFormat iFormat, std::initializer_list< T > iValues, const FColorSpace* iColorSpace = nullptr );

    static FColor RGB( uint8 iR, uint8 iG, uint8 iB, uint8  iA = UINT8_MAX  );
    static FColor GreyA8(   uint8  iGrey,   uint8  iA = UINT8_MAX  );
    static FColor GreyA16(  uint16 iGrey,   uint16 iA = UINT16_MAX );
    static FColor GreyA32(  uint32 iGrey,   uint32 iA = UINT32_MAX );
    static FColor GreyAF(   float  iGrey,   float  iA = 1.f        );
    static FColor GreyAD(   double iGrey,   double iA = 1.0        );
    static FColor RGBA8(    uint8  iR,  uint8  iG,  uint8  iB,  uint8  iA = UINT8_MAX  );
    static FColor RGBA16(   uint16 iR,  uint16 iG,  uint16 iB,  uint16 iA = UINT16_MAX );
    static FColor RGBA32(   uint32 iR,  uint32 iG,  uint32 iB,  uint32 iA = UINT32_MAX );
    static FColor RGBAF(    float  iR,  float  iG,  float  iB,  float  iA = 1.f        );
    static FColor RGBAD(    double iR,  double iG,  double iB,  double iA = 1.0        );
    static FColor HSVA8(    uint8  iH,  uint8  iS,  uint8  iV,  uint8  iA = UINT8_MAX  );
    static FColor HSVA16(   uint16 iH,  uint16 iS,  uint16 iV,  uint16 iA = UINT16_MAX );
    static FColor HSVA32(   uint32 iH,  uint32 iS,  uint32 iV,  uint32 iA = UINT32_MAX );
    static FColor HSVAF(    float  iH,  float  iS,  float  iV,  float  iA = 1.f        );
    static FColor HSVAD(    double iH,  double iS,  double iV,  double iA = 1.0        );
    static FColor HSLA8(    uint8  iH,  uint8  iS,  uint8  iL,  uint8  iA = UINT8_MAX  );
    static FColor HSLA16(   uint16 iH,  uint16 iS,  uint16 iL,  uint16 iA = UINT16_MAX );
    static FColor HSLA32(   uint32 iH,  uint32 iS,  uint32 iL,  uint32 iA = UINT32_MAX );
    static FColor HSLAF(    float  iH,  float  iS,  float  iL,  float  iA = 1.f        );
    static FColor HSLAD(    double iH,  double iS,  double iL,  double iA = 1.0        );
    static FColor CMYA8(    uint8  iC,  uint8  iM,  uint8  iY,  uint8  iA = UINT8_MAX  );
    static FColor CMYA16(   uint16 iC,  uint16 iM,  uint16 iY,  uint16 iA = UINT16_MAX );
    static FColor CMYA32(   uint32 iC,  uint32 iM,  uint32 iY,  uint32 iA = UINT32_MAX );
    static FColor CMYAF(    float  iC,  float  iM,  float  iY,  float  iA = 1.f        );
    static FColor CMYAD(    double iC,  double iM,  double iY,  double iA = 1.0        );
    static FColor CMYKA8(   uint8  iC,  uint8  iM,  uint8  iY,  uint8  iK,  uint8  iA = UINT8_MAX  );
    static FColor CMYKA16(  uint16 iC,  uint16 iM,  uint16 iY,  uint16 iK,  uint16 iA = UINT16_MAX );
    static FColor CMYKA32(  uint32 iC,  uint32 iM,  uint32 iY,  uint32 iK,  uint32 iA = UINT32_MAX );
    static FColor CMYKAF(   float  iC,  float  iM,  float  iY,  float  iK,  float  iA = 1.f        );
    static FColor CMYKAD(   double iC,  double iM,  double iY,  double iK,  double iA = 1.0        );
    static FColor YUVA8(    uint8  iY,  uint8  iU,  uint8  iV,  uint8  iA = UINT8_MAX  );
    static FColor YUVA16(   uint16 iY,  uint16 iU,  uint16 iV,  uint16 iA = UINT16_MAX );
    static FColor YUVA32(   uint32 iY,  uint32 iU,  uint32 iV,  uint32 iA = UINT32_MAX );
    static FColor YUVAF(    float  iY,  float  iU,  float  iV,  float  iA = 1.f        );
    static FColor YUVAD(    double iY,  double iU,  double iV,  double iA = 1.0        );
    static FColor LabA8(    uint8  iL,  uint8  ia,  uint8  ib,  uint8  iA = UINT8_MAX  );
    static FColor LabA16(   uint16 iL,  uint16 ia,  uint16 ib,  uint16 iA = UINT16_MAX );
    static FColor LabA32(   uint32 iL,  uint32 ia,  uint32 ib,  uint32 iA = UINT32_MAX );
    static FColor LabAF(    float  iL,  float  ia,  float  ib,  float  iA = 1.f        );
    static FColor LabAD(    double iL,  double ia,  double ib,  double iA = 1.0        );
    static FColor XYZA8(    uint8  iX,  uint8  iY,  uint8  iZ,  uint8  iA = UINT8_MAX  );
    static FColor XYZA16(   uint16 iX,  uint16 iY,  uint16 iZ,  uint16 iA = UINT16_MAX );
    static FColor XYZA32(   uint32 iX,  uint32 iY,  uint32 iZ,  uint32 iA = UINT32_MAX );
    static FColor XYZAF(    float  iX,  float  iY,  float  iZ,  float  iA = 1.f        );
    static FColor XYZAD(    double iX,  double iY,  double iZ,  double iA = 1.0        );
    static FColor YxyA8(    uint8  iY,  uint8  ix,  uint8  iy,  uint8  iA = UINT8_MAX  );
    static FColor YxyA16(   uint16 iY,  uint16 ix,  uint16 iy,  uint16 iA = UINT16_MAX );
    static FColor YxyA32(   uint32 iY,  uint32 ix,  uint32 iy,  uint32 iA = UINT32_MAX );
    static FColor YxyAF(    float  iY,  float  ix,  float  iy,  float  iA = 1.f        );
    static FColor YxyAD(    double iY,  double ix,  double iy,  double iA = 1.0        );
};

extern template FColor::FColor( eFormat, std::initializer_list< int >, const FColorSpace* );
extern template FColor::FColor( eFormat, std::initializer_list< uint8 >, const FColorSpace* );
extern template FColor::FColor( eFormat, std::initializer_list< uint16 >, const FColorSpace* );
extern template FColor::FColor( eFormat, std::initializer_list< uint32 >, const FColorSpace* );
extern template FColor::FColor( eFormat, std::initializer_list< ufloat >, const FColorSpace* );
extern template FColor::FColor( eFormat, std::initializer_list< udouble >, const FColorSpace* );

ULIS_NAMESPACE_END

