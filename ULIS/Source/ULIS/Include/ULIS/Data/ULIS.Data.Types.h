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


#define ULIS_REG_BUILDER ulis_reg_builder
ULIS_CREATE_REG( ULIS_REG_BUILDER, 0 )
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
ULIS_REG_TYPE ulis_types_reg = ULIS_ASSIGN_REG( ULIS_REG_BUILDER );
#define ULIS_REG ::ULIS::ulis_types_reg
constexpr auto temp_reg_size = ulis_types_reg.Size();
#define ULIS_REG_SIZE 13


} // namespace ULIS

