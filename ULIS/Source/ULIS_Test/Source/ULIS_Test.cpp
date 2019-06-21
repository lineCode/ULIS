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
#include <ULIS_core>

#define ULIS_REG_SWITCH_OP( z, n, data ) case n: return  ::ULIS::TBlockSpec< ::ULIS::ulis_types_reg[ n ] >:: data;

auto
BlockSpecOp( uint32_t i )
{
    switch( i )
    {
        BOOST_PP_REPEAT( ULIS_REG_SIZE, ULIS_REG_SWITCH_OP, _ss )
        default: return  "default";
    }
}


int main()
{
    for( int i = 0; i < ULIS_REG_SIZE; ++i )
        std::cout << BlockSpecOp( i ) << std::endl;

    return 0;
}

