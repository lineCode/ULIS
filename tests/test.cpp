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
    FPixel src( ULIS2_FORMAT_RGB8);
    FPixel dst( ULIS2_FORMAT_RGBAF );
    src.SetR8( 255 );
    src.SetG8( 255 );
    src.SetB8( 255 );
    Conv( src, dst );
    std::cout << "0:" << (int)dst.RF() << std::endl;
    std::cout << "1:" << (int)dst.GF() << std::endl;
    std::cout << "2:" << (int)dst.BF() << std::endl;
    std::cout << "3:" << (int)dst.AF() << std::endl;

    auto dummy = 0;
}

