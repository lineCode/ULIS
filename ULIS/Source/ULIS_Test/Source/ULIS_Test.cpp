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
#include <ULIS_Core>
#include <cstring>

using namespace ::ULIS;

/*
static constexpr const char layout[] = "B8G8R8A8";
static constexpr const char model[] =  "RGBA";
static constexpr const int count = ::ULIS::ct_strlen( model );
static constexpr const std::array< uint8, count > arr = ::ULIS::make_index_from_string( layout, model );
*/

template< uint32 H >
class xxx
{
};

int main()
{
    xxx< CONST_STR( "RGB" ).Hash() > xi;

    constexpr const char* od = CONST_STR( "lol" ).s;
    constexpr uint64 id = ParseID( CONST_STR( "o" ) );

    TBlock< Block_plannar_premultiplied_uint8_32_R8G8B8A8_R0G1B2A3_integral > block;
    constexpr auto a = CONST_STR( "00" );
    int b = a.Size();

    static_assert( CONST_STR( "RGB" ).Substring< 2 >().Len() == 2, "..." );
    static_assert( CONST_STR( "RGB" ).Substring< 2 >() == CONST_STR( "RG" ), "..." );

    std::cout<< CONST_STR( "RGB" ) << std::endl;
    std::cout<< CONST_STR( "RGB" ).Substring< 2 >() << std::endl;
    getchar();
    return 0;
}

