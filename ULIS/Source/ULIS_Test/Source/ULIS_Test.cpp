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
#include "ULIS/ULIS.Spec.h"

#define ULIS_REG_BUILDER ulis_reg_builder
ULIS_CREATE_REG( ULIS_REG_BUILDER, 0 )
ULIS_DECLSPEC( uint8,   hasAlpha,   RGB,    RGBA,   typeLimits )
ULIS_DECLSPEC( uint8,   hasAlpha,   RGB,    ARGB,   typeLimits )
ULIS_DECLSPEC( uint8,   hasAlpha,   RGB,    BGRA,   typeLimits )
ULIS_DECLSPEC( uint8,   hasAlpha,   RGB,    ABGR,   typeLimits )
ULIS_DECLSPEC( uint8,   noAlpha,    RGB,    RGB,    typeLimits )
ULIS_DECLSPEC( uint8,   noAlpha,    RGB,    BGR,    typeLimits )
ULIS_DECLSPEC( float,   hasAlpha,   RGB,    RGBA,   normalized )
ULIS_DECLSPEC( double,  hasAlpha,   RGB,    RGBA,   normalized )
ULIS_DECLSPEC( float,   noAlpha,    RGB,    RGB,    normalized )
ULIS_DECLSPEC( double,  noAlpha,    RGB,    RGB,    normalized )
ULIS_REG ulis_reg_result = ULIS_ASSIGN_REG( ULIS_REG_BUILDER );

int main()
{
    std::cout << sizeof( ::ULIS::FSpec ) << std::endl;
    return 0;
}

