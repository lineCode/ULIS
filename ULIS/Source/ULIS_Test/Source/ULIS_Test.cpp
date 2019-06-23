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

auto
BlockSpec( uint32_t i )
{
    switch( i )
    {
        #define ULIS_REG_SWITCH_OP( z, n, data ) case n: return  ::ULIS::TBlockSpec< ::ULIS::ulis_types_reg[ n ] >:: data;
        ULIS_REPEAT( ULIS_REG_SIZE, ULIS_REG_SWITCH_OP, _nf )
        #undef ULIS_REG_SWITCH_OP
        default: return  ::ULIS::FSpec{};
    }
}

int main()
{
    for( int i = 0; i < ULIS_REG_SIZE; ++i )
    {
        auto spec = BlockSpec( i );
        std::cout << spec._ss << std::endl;
    }

    return 0;
}

