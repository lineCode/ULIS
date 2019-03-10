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
#include <ULISBlock>
#include <ULISBlock2>
#include <cstring>

using namespace ::ULIS;

static constexpr const char layout[] = "B8G8R8A8";
static constexpr const char model[] =  "RGBA";
static constexpr const int count = ::ULIS::ct_strlen( model );
static constexpr const std::array< uint8, count > arr = ::ULIS2::make_index_from_string( layout, model );

int main()
{
    ::ULIS2::TBlock< ::ULIS2::Block_plannar_premultiplied_uint8_32_R8G8B8A8_R0G1B2A3_integral > block;
    
    constexpr auto a = make_const_char_array( "ok" );

    std::cout<< "layout: " << layout << std::endl;
    std::cout<< "model: " << model << std::endl;
    for( int i = 0; i < arr.size(); ++i )
        std::cout << model[i] << ": " << (int)arr[i] << "; ";
    static_assert( ::ULIS::ct_substring< 5 >( "jambon", 0 )[0] == 'j', "..." );
    std::cout << std::endl;
    std::cout << ct_strlen( a ) << std::endl;
    std::cout << strlen( a ) << std::endl;

    getchar();
    return 0;
}

