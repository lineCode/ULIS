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
// FTransformation2D
//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------- Construction / Destruction
FTransformation2D::~FTransformation2D() {
    if( mImp )
        delete  mImp;
}

FTransformation2D::FTransformation2D()
    : mImp( new FTransform2D_imp() )
{
}

FTransformation2D::FTransformation2D( const FTransformation2D& iOther )
    : mImp( new FTransform2D_imp( *iOther.mImp ) )
{
}

FTransformation2D::FTransformation2D( FTransformation2D&& iOther )
{
    mImp = iOther.mImp;
    iOther.mImp = nullptr;
}

FTransformation2D&
FTransformation2D::operator=( const FTransformation2D& iOther ) {
    *mImp = *iOther.mImp;
    return  *this;
}

//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------- Public API
const FTransformation2D::FTransform2D_imp&
FTransformation2D::GetImp() const {
    return  *mImp;
}

const uint8*
FTransformation2D::Bits() const {
    return  mImp->Bits();
}

FTransformation2D
FTransformation2D::Inverse() const {
    return  FTransformation2D( new FTransform2D_imp( glm::inverse( mImp->Matrix() ) ) );
}

//----------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------- Private API
FTransformation2D::FTransformation2D( FTransform2D_imp* iVal )
    : mImp( iVal )
{
}

//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------- Static API
//static
FTransformation2D
FTransformation2D::MakeFromMatrix( float iM00, float iM10, float iM20, float iM01, float iM11, float iM21, float iM02, float iM12, float iM22 ) {
    return  FTransformation2D( new FTransform2D_imp( glm::mat3( iM00, iM10, iM20, iM01, iM11, iM21, iM02, iM12, iM22 ) ) );
}

//static
FTransformation2D
FTransformation2D::MakeIdentityTransform() {
    return  FTransformation2D( new FTransform2D_imp( MakeIdentityMatrix() ) );
}

//static
FTransformation2D
FTransformation2D::MakeRotationTransform( float iAngleRag ) {
    return  FTransformation2D( new FTransform2D_imp( MakeRotationMatrix( iAngleRag ) ) );
}

//static
FTransformation2D
FTransformation2D::MakeScaleTransform( float iX, float iY ) {
    return  FTransformation2D( new FTransform2D_imp( MakeScaleMatrix( iX, iY ) ) );
}

//static
FTransformation2D
FTransformation2D::MakeShearTransform( float iX, float iY ) {
    return  FTransformation2D( new FTransform2D_imp( MakeShearMatrix( iX, iY ) ) );
}

//static
FTransformation2D
FTransformation2D::MakeTranslationTransform( float iX, float iY ) {
    return  FTransformation2D( new FTransform2D_imp( MakeTranslationMatrix( iX, iY ) ) );
}

//static
FTransformation2D
FTransformation2D::ComposeTransforms( const FTransformation2D& iA, const FTransformation2D& iB ) {
    return  FTransformation2D( new FTransform2D_imp( ComposeMatrix( iA.GetImp().Matrix(), iB.GetImp().Matrix() ) ) );
}

//static
void
FTransformation2D::DecomposeTransform( const FTransformation2D& iTransform, float* oTx, float* oTy, float* oRotation, float* oScaleX, float* oScaleY, float* oSkewX, float* oSkewY ) {
    DecomposeMatrix( iTransform.GetImp().Matrix(), oTx, oTy, oRotation, oScaleX, oScaleY, oSkewX, oSkewY );
}

//static
FTransformation2D
FTransformation2D::GetPerspectiveTransform( const FVec2F iSrc[], const FVec2F iDst[] ) {
    return  FTransformation2D( new FTransform2D_imp( GetPerspectiveMatrix( iSrc, iDst ) ) );
}

//static
FVec2F
FTransformation2D::DoHomographyTransform( const FVec2F& iPoint, const FTransformation2D& iTransform ) {
    return  HomographyTransform( iPoint, iTransform.GetImp().Matrix() );
}

ULIS_NAMESPACE_END

