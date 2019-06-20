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

ULIS_DECLSPEC( interleaved, uint8, RGB, RGBA, straight, default, default, default )

int main()
{
    std::cout << sizeof( ::ULIS::FSpec ) << std::endl;
    return 0;
}

