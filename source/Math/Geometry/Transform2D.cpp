// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS3
*__________________
*
* @file         Transform2D.cpp
* @author       Clement Berthaud
* @brief        This file provides the Transform2D class definition.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include "Math/Geometry/Transformation2D.h"
#include "Math/Geometry/Transform2D_Private.h"
ULIS_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
// Transformation2D
//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------- Construction / Destruction
Transformation2D::~Transformation2D() {
    if( mImp )
        delete  mImp;
}

Transformation2D::Transformation2D()
    : mImp( new FTransform2D_imp() )
{
}

Transformation2D::Transformation2D( const Transformation2D& iOther )
    : mImp( new FTransform2D_imp( *iOther.mImp ) )
{
}

Transformation2D::Transformation2D( Transformation2D&& iOther )
{
    mImp = iOther.mImp;
    iOther.mImp = nullptr;
}

Transformation2D&
Transformation2D::operator=( const Transformation2D& iOther ) {
    *mImp = *iOther.mImp;
    return  *this;
}

//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------- Public API
const Transformation2D::FTransform2D_imp&
Transformation2D::GetImp() const {
    return  *mImp;
}

const uint8*
Transformation2D::Bits() const {
    return  mImp->Bits();
}

Transformation2D
Transformation2D::Inverse() const {
    return  Transformation2D( new FTransform2D_imp( glm::inverse( mImp->Matrix() ) ) );
}

//----------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------- Private API
Transformation2D::Transformation2D( FTransform2D_imp* iVal )
    : mImp( iVal )
{
}

//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------- Static API
//static
Transformation2D
Transformation2D::MakeFromMatrix( float iM00, float iM10, float iM20, float iM01, float iM11, float iM21, float iM02, float iM12, float iM22 ) {
    return  Transformation2D( new FTransform2D_imp( glm::mat3( iM00, iM10, iM20, iM01, iM11, iM21, iM02, iM12, iM22 ) ) );
}

//static
Transformation2D
Transformation2D::MakeIdentityTransform() {
    return  Transformation2D( new FTransform2D_imp( MakeIdentityMatrix() ) );
}

//static
Transformation2D
Transformation2D::MakeRotationTransform( float iAngleRag ) {
    return  Transformation2D( new FTransform2D_imp( MakeRotationMatrix( iAngleRag ) ) );
}

//static
Transformation2D
Transformation2D::MakeScaleTransform( float iX, float iY ) {
    return  Transformation2D( new FTransform2D_imp( MakeScaleMatrix( iX, iY ) ) );
}

//static
Transformation2D
Transformation2D::MakeShearTransform( float iX, float iY ) {
    return  Transformation2D( new FTransform2D_imp( MakeShearMatrix( iX, iY ) ) );
}

//static
Transformation2D
Transformation2D::MakeTranslationTransform( float iX, float iY ) {
    return  Transformation2D( new FTransform2D_imp( MakeTranslationMatrix( iX, iY ) ) );
}

//static
Transformation2D
Transformation2D::ComposeTransforms( const Transformation2D& iA, const Transformation2D& iB ) {
    return  Transformation2D( new FTransform2D_imp( ComposeMatrix( iA.GetImp().Matrix(), iB.GetImp().Matrix() ) ) );
}

//static
void
Transformation2D::DecomposeTransform( const Transformation2D& iTransform, float* oTx, float* oTy, float* oRotation, float* oScaleX, float* oScaleY, float* oSkewX, float* oSkewY ) {
    DecomposeMatrix( iTransform.GetImp().Matrix(), oTx, oTy, oRotation, oScaleX, oScaleY, oSkewX, oSkewY );
}

//static
Transformation2D
Transformation2D::GetPerspectiveTransform( const FVec2F iSrc[], const FVec2F iDst[] ) {
    return  Transformation2D( new FTransform2D_imp( GetPerspectiveMatrix( iSrc, iDst ) ) );
}

//static
FVec2F
Transformation2D::DoHomographyTransform( const FVec2F& iPoint, const Transformation2D& iTransform ) {
    return  HomographyTransform( iPoint, iTransform.GetImp().Matrix() );
}

ULIS_NAMESPACE_END

