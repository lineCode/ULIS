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
    ::ULIS::PrintSpecs();
    ::ULIS::IBlock* block = new ::ULIS::FBlockRGBA8( 200, 200 );
    std::cout << block->Name() << std::endl;
    std::cout << block->MaxI() << std::endl;
    delete  block;
    return 0;
}

