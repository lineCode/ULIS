// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS3
*__________________
*
* @file         Pixels.cpp
* @author       Clement Berthaud
* @brief        Pixels application for ULIS3.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include <ULIS3>
using namespace ::ul3;

int
main() {
    FPixelValue colorA = FPixelValue::FromRGBA8( 0, 0, 0, 255 );
    FPixelValue colorB = Conv( Conv( FPixelValue::FromRGBA8( 0, 0, 0, 255 ), ULIS3_FORMAT_HSVA8 ), ULIS3_FORMAT_RGBA8 );
    bool same = colorA == colorB;

    return  0;
}

