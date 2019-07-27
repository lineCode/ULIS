/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS_Test.cpp
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#include <ULIS_CORE>

int main()
{
    ::ULIS::uint8 res =::ULIS::ConvType< ::ULIS::uint16, ::ULIS::uint8 >( (::ULIS::uint16)65025 );
    std::cout << (int)res << std::endl;
    return 0;
}
