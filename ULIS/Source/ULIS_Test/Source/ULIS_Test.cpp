/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS_Test.cpp
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#include <iostream>
#include <boost/preprocessor/repetition/repeat.hpp>
#include "ULIS/ULIS.Spec.h"

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
ULIS_DECLSPEC( float,   RGB,    noAlpha,    RGB,    normalized )
ULIS_DECLSPEC( double,  RGB,    noAlpha,    RGB,    normalized )
ULIS_REG ulis_types_reg = ULIS_ASSIGN_REG( ULIS_REG_BUILDER );


constexpr int TEMP_REG_SIZE = ulis_types_reg.Size();
#define ULIS_REG_SIZE 13
#define ULIS_REG_SWITCH( z, n, data ) case n: return  ::ULIS::TBlockSpec< ulis_types_reg[ n ] >:: data;

auto
GetBlockSpecStr( uint32_t i )
{
    switch( i )
    {
        BOOST_PP_REPEAT( ULIS_REG_SIZE, ULIS_REG_SWITCH, _ss )
        default: return  "default";
    }
}

int main()
{
    for( int i = 0; i < ULIS_REG_SIZE; ++i )
        std::cout << GetBlockSpecStr( i ) << std::endl;

    return 0;
}

