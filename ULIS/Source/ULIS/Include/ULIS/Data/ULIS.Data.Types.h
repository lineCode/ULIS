/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Data.Types.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once


#include "ULIS/Data/ULIS.Data.Block.h"


namespace ULIS {
/////////////////////////////////////////////////////
// Reg baking
/* we specify the name of the build reg */
#define ULIS_REG_BUILDER ulis_reg_builder
/* we create the reg with a first invalid entry (0) */
ULIS_CREATE_REG( ULIS_REG_BUILDER, 0 )

/////////////////////////////////////////////////////
// Types declspec
/* Actual types specializations */
ULIS_DECLSPEC( double,  LAB,    hasAlpha,   LABA,   typeLimits )
ULIS_DECLSPEC( float,   VEC,    noAlpha,    XYZW,   typeLimits )
ULIS_DECLSPEC( uint8,   RGB,    hasAlpha,   RGBA,   typeLimits )
ULIS_DECLSPEC( uint8,   RGB,    hasAlpha,   ARGB,   typeLimits )
ULIS_DECLSPEC( uint8,   RGB,    hasAlpha,   BGRA,   typeLimits )
ULIS_DECLSPEC( uint8,   RGB,    hasAlpha,   ABGR,   typeLimits )
ULIS_DECLSPEC( uint8,   RGB,    noAlpha,    RGB,    typeLimits )
ULIS_DECLSPEC( uint8,   RGB,    noAlpha,    BGR,    typeLimits )
ULIS_DECLSPEC( float,   RGB,    hasAlpha,   RGBA,   normalized )
ULIS_DECLSPEC( double,  RGB,    hasAlpha,   RGBA,   normalized )
ULIS_DECLSPEC( float,   RGB,    noAlpha,    RGB,   normalized )
ULIS_DECLSPEC( double,  RGB,    noAlpha,    RGB,   normalized )

/////////////////////////////////////////////////////
// Types assign
/* we assign the result reg */
ULIS_REG_TYPE ulis_types_reg = ULIS_ASSIGN_REG( ULIS_REG_BUILDER );
/* we specify the name of the result reg for easy usage */
#define ULIS_REG ::ULIS::ulis_types_reg

/////////////////////////////////////////////////////
// Reg Size
/* temp assign reg size ( workaround ) */
constexpr auto temp_reg_size = ulis_types_reg.Size();
/* Reg size macro for usage during preprocessor ( workaround ) */
#define ULIS_REG_SIZE 13

/////////////////////////////////////////////////////
// Mainstream typedefs
/* easy typedefs for the most common block types defined earlier */
typedef ::ULIS::FBlockuint8RGBhasAlphaRGBAtypeLimits FBlockRGBA8;
typedef ::ULIS::FBlockuint8RGBhasAlphaBGRAtypeLimits FBlockBGBA8;
typedef ::ULIS::FBlockuint8RGBhasAlphaARGBtypeLimits FBlockARGB8;
typedef ::ULIS::FBlockuint8RGBhasAlphaABGRtypeLimits FBlockABGR8;

} // namespace ULIS
