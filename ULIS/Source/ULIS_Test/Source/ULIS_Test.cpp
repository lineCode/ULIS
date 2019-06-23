/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS_Test.cpp
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#include <ULIS_core>


int main()
{
    //::ULIS::PrintSpecs();

    auto spec = ULIS_GETSPEC( ::ULIS::FBlockRGBA8::TypeId() );
    std::cout << spec._ss << std::endl;

    ::ULIS::IBlock* block = new ::ULIS::FBlockRGBA8( 200, 200 );
    delete  block;

    return 0;
}

