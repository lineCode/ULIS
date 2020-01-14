// Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         test.cpp
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
    FBlock block( 256, 256, ULIS2_FORMAT_RGBF );
    FColor color( ULIS2_FORMAT_LabAF );
    memset( block.DataPtr(), 1, 256 * 256 * 3 * 1 );
    color.SetLF( +62 / 255.f );
    color.SetaF( +81 / 128.f + 0.5f );
    color.SetbF( -58 / 128.f + 0.5f );
    color.SetAF( 1.f );
    FThreadPool pool;
    FPerf perf( true, true, true );
    Fill( pool, &block, color, perf );
    FPixelProxy prox = block.PixelProxy( 240, 0 );
    std::cout << (float)prox.RF() << std::endl;
    std::cout << (float)prox.GF() << std::endl;
    std::cout << (float)prox.BF() << std::endl;
    std::cout << (float)prox.AF() << std::endl;
    auto dummy = 0;
}

