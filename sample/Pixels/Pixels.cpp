// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS3
*__________________
*
* @file         Pixels.cpp
* @author       Clement Berthaud
* @brief        Pixels application for ULIS3.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include <ULIS3>
using namespace ::ul3;

FColor GetOneColor() {
    FColor aa = FColor::FromRGBA8( 255, 0, 0 );
    return  aa;
}

int
main() {

    {
        FColor colorA( ULIS_FORMAT_RGBA8, { 0, 0, 0, 0 } );
        FColor colorB = Conv( FColor::FromRGBA8( 0, 0, 0, 255 ), ULIS_FORMAT_HSVA8 );
        colorA = colorB;
        FColor colorC = GetOneColor();
        auto dummy = 0;
    }

    return  0;
}

