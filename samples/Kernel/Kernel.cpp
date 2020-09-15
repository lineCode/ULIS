// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS3
*__________________
*
* @file         Kernel.cpp
* @author       Clement Berthaud
* @brief        Kernel application for ULIS3.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include <ULIS3>
using namespace ::ul3;

int
main() {

    FKernel A( FVec2I( 3, 3 )
                , { 0,  1, 0
                  , 1, -4, 5
                  , 0,  1, 0 } );
    FKernel B = A.FlippedX();

    FStructuringElement C( FVec2I( 3, 3 )
                         , { MP_ANY, MP_ANY, MP_ANY
                           , MP_ANY, MP_ONE, MP_ONE
                           , MP_ANY, MP_ONE, MP_ZERO } );
    FStructuringElement E = C.Rotated90CCW();
    FStructuringElement D = E;


    for( int j = 0; j < D.Height(); ++j ) {
        for( int i = 0; i < D.Width(); ++i ) {
            std::cout << static_cast< int >( D.At( i, j ) ) << ", ";
        }
        std::cout << std::endl;
    }

    return  0;
}

