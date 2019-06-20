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
#include <coal_core>

/*
#define ULIS_KEY_ML     ml // memory_layout
#define ULIS_KEY_AM     am // alpha_mode
#define ULIS_KEY_TP     tp // type
#define ULIS_KEY_CM     cm // color_model
#define ULIS_KEY_EM     em // endian_mode
#define ULIS_KEY_NM     nm // normal
#define ULIS_KEY_UL     ul // upper_limit
#define ULIS_KEY_LL     ll // lower_limit
#define ULIS_KEY_CL     cl // channel_layout
*/

ULIS_DECLSPEC( interleaved, uint8, RGB, RGBA, straight, default, default, default )

coalMakeConstexprArg( const__SS__ml_interleaved__tp_uint8__cm_RGB__cl_RGBA__am_straight__ul_default__ll_default__em_default, _SS__ml_interleaved__tp_uint8__cm_RGB__cl_RGBA__am_straight__ul_default__ll_default__em_default );
coal norm = ::ULIS::NormalizeSpecStr( const__SS__ml_interleaved__tp_uint8__cm_RGB__cl_RGBA__am_straight__ul_default__ll_default__em_default{} );

int main()
{
    std::cout << sizeof( ::ULIS::FSpec ) << std::endl;
    return 0;
}

