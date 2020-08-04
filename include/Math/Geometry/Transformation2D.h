// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS3
*__________________
*
* @file         Transformation2D.h
* @author       Clement Berthaud
* @brief        This file provides the Transformation2D class declaration.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"
#include "Math/Geometry/Rectangle.h"
#include "Math/Geometry/Vector.h"
#include "Math/Geometry/Matrix.h"

ULIS_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
// Transformation2D
class ULIS_API Transformation2D
{
public:
    class FTransform2D_imp;

public:
    // Construction / Destruction
    ~Transformation2D();
    Transformation2D();
    Transformation2D( const Transformation2D& iOther );
    Transformation2D( Transformation2D&& iOther );
    Transformation2D& operator=( const Transformation2D& iOther );

public:
    // Public API
    const FTransform2D_imp& GetImp() const;
    const uint8* Bits() const;
    Transformation2D Inverse() const;

private:
    // Private API
    Transformation2D( FTransform2D_imp* iVal );

public:
    // Static API
    static Transformation2D MakeFromMatrix( float iM00, float iM10, float iM20, float iM01, float iM11, float iM21, float iM02, float iM12, float iM22 );
    static Transformation2D MakeIdentityTransform();
    static Transformation2D MakeRotationTransform( float iAngleRag );
    static Transformation2D MakeScaleTransform( float iX, float iY );
    static Transformation2D MakeShearTransform( float iX, float iY );
    static Transformation2D MakeTranslationTransform( float iX, float iY );
    static Transformation2D ComposeTransforms( const Transformation2D& iA, const Transformation2D& iB );
    static void DecomposeTransform( const Transformation2D& iTransform, float* oTx, float* oTy, float* oRotation, float* oScaleX, float* oScaleY, float* oSkewX, float* oSkewY );
    static Transformation2D GetPerspectiveTransform( const FVec2F iSrc[], const FVec2F iDst[] );
    static FVec2F DoHomographyTransform( const FVec2F& iPoint, const Transformation2D& iTransform );

private:
    // Private Data Members
    FMat3F mMatrix;
};

ULIS_NAMESPACE_END

