// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS3
*__________________
*
* @file         CatmullRom.h
* @author       Clement Berthaud
* @brief        This file provides the CatmullRom methods implementation.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"
#include "Maths/Geometry.h"
#include "Maths/Maths.h"
#include <cmath>
#include <vector>

ULIS3_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
// CatmullRom Functions
static constexpr float sCatmullRomKnotParametricConstant_Uniform     = 0.0f;
static constexpr float sCatmullRomKnotParametricConstant_Centripetal = 0.5f;
static constexpr float sCatmullRomKnotParametricConstant_Chordal     = 1.f;

struct ULIS3_API FCatmullRomLUTElement {
    FVec2F point;
    float length;
    float param;
};

struct ULIS3_API FCatmullRomControlPoint {
    FVec2F point;
    FVec2F ctrlCW;
    FVec2F ctrlCCW;
};

template< class T >
float NextKnot(float t, const T& p0, const T& p1, float alpha ) {
    float a = pow((p1.x-p0.x), 2.0f) + pow((p1.y-p0.y), 2.0f);
    float b = pow(a, alpha * 0.5f);
    return (b + t);
}

template< class T >
void
CatmullRomPoints( const T& iP0
                , const T& iP1
                , const T& iP2
                , const T& iP3
                , uint32 iNumPoints
                , std::vector< T >* oOut
                , float iKnotParameter = sCatmullRomKnotParametricConstant_Centripetal )
{
    oOut->clear();

    // TODO: using epsilon and shifting inputs slightly makes it easy to handle the special case when two successive control points are equal
    // in the definition of a cubic hermite spline, the point is to extract tangent from the derivative at each control point.
    // CatmullRom is just a name for a particular way to chose tangents, and you cannot extract tangent from two points with same value
    // since their delta is 0. By examining the calculations you can see it can result in division by zero.
    // So we shift inputs in such a way no two successive control points Pi are equals.
    static constexpr float epsilon = 10E-3;
    T P0 = iP0;
    T P1 = P0 == iP1 ? iP1 + FVec2F( epsilon, 0.0f ) : iP1;
    T P2 = P1 == iP2 ? iP2 + FVec2F( 0.0f, epsilon ) : iP2;
    T P3 = P2 == iP3 ? iP3 - FVec2F( epsilon, 0.0f ) : iP3;

    float t0 = 0.0f;
    float t1 = NextKnot( t0, P0, P1, iKnotParameter );
    float t2 = NextKnot( t1, P1, P2, iKnotParameter );
    float t3 = NextKnot( t2, P2, P3, iKnotParameter );
    float t1mt0 = ( t1 - t0 );
    float t2mt1 = ( t2 - t1 );
    float t3mt2 = ( t3 - t2 );
    float t2mt0 = ( t2 - t0 );
    float t3mt1 = ( t3 - t1 );

    for( float t = t1; t < t2; t += ( ( t2 - t1 ) / (float)iNumPoints ) ) {
        T A1 = P0 * ( t1 - t ) / t1mt0 + P1 * ( t - t0 ) / t1mt0;
        T A2 = P1 * ( t2 - t ) / t2mt1 + P2 * ( t - t1 ) / t2mt1;
        T A3 = P2 * ( t3 - t ) / t3mt2 + P3 * ( t - t2 ) / t3mt2;
        T B1 = A1 * ( t2 - t ) / t2mt0 + A2 * ( t - t0 ) / t2mt0;
        T B2 = A2 * ( t3 - t ) / t3mt1 + A3 * ( t - t1 ) / t3mt1;
        T C  = B1 * ( t2 - t ) / t2mt1 + B2 * ( t - t1 ) / t2mt1;
        oOut->push_back( C );
    }
}

ULIS3_NAMESPACE_END

