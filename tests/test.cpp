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
    FPixel src( ULIS2_FORMAT_LabAD);
    FPixel dst( ULIS2_FORMAT_RGBAF  );
    src.SetLD( 0.262745 );
    src.SetaD( 0.84375 );
    src.SetbD( 0.9765625 );
    src.SetAD( 1.0 );
    Conv( src, dst );

    std::cout << "0:" << dst.RF() << std::endl;
    std::cout << "1:" << dst.GF() << std::endl;
    std::cout << "2:" << dst.BF() << std::endl;
    std::cout << "3:" << dst.AF() << std::endl;

    auto dummy = 0;
}

