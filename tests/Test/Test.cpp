// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Test.cpp
* @author       Clement Berthaud
* @brief        Test application for ULIS2.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include <ULIS2>
using namespace ::ul2;

FVec2F TransformPerspective( const FVec2F& iPoint, const glm::mat3& iMat ) {
    return  FVec2F( ( iPoint.x * iMat[0][0] + iPoint.y * iMat[0][1] + iMat[0][2] ) / ( iPoint.x * iMat[2][0] + iPoint.y * iMat[2][1] + iMat[2][2] )
                  , ( iPoint.x * iMat[1][0] + iPoint.y * iMat[1][1] + iMat[1][2] ) / ( iPoint.x * iMat[2][0] + iPoint.y * iMat[2][1] + iMat[2][2] ) );
}

int
main() {
    FVec2F A[4] = { { 0, 0 }, { 200, 0 }, { 200, 200 }, { 0, 200 } };
    FVec2F B[4] = { { 10, 10 }, { 100, 50 }, { 100, 150 }, { 10, 190 } };
    auto mat = GetPerspectiveMatrix( A, B );

    FVec2F C[4];
    C[0] = TransformPerspective( A[0], mat );
    C[1] = TransformPerspective( A[1], mat );
    C[2] = TransformPerspective( A[2], mat );
    C[3] = TransformPerspective( A[3], mat );

    auto dummy = 0;
    return  0;
}

