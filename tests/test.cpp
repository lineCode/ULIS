// Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Test.cpp
* @author       Clement Berthaud
* @brief        Test application for ULIS2.
* @copyright    Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include <ULIS2>
using namespace ::ul2;

int
main()
{
    FProfileRegistry reg;
    FPixel src( ULIS2_FORMAT_RGBA8 );
    FPixel dst( ULIS2_FORMAT_GAD );
    src.SetR8( 255 );
    src.SetG8( 255 );
    src.SetB8( 255 );
    src.SetA8( 127 );
    Conv( src, dst );
    auto _g = dst.GreyD();
    auto _a = dst.AD();
    std::cout << "G:" << _g << std::endl;
    std::cout << "A:" << _a << std::endl;

    auto dummy = 0;
}

