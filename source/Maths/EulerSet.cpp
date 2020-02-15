// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         EulerSet.cpp
* @author       Clement Berthaud
* @brief        This file provides the FMaths class declaration.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include "Maths/EulerSet.h"

ULIS2_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
// FEulerSet
//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------- Construction / Destruction
FEulerSet::~FEulerSet()
{
}


FEulerSet::FEulerSet()
{
    SetAxesValues( eSet::kInstrinsicYXZ, 0.f, 0.f, 0.f );
}


FEulerSet::FEulerSet( const glm::vec3& iValues )
{
    SetAxesValues( eSet::kInstrinsicYXZ, iValues );
}


FEulerSet::FEulerSet( eSet iSet )
{
    SetAxesValues( iSet, 0.f, 0.f, 0.f );
}


FEulerSet::FEulerSet( eSet iSet, const  glm::vec3& iValues )
{
    SetAxesValues( iSet, iValues );
}


FEulerSet::FEulerSet( eSet iSet, float iPhiValue, float iThetaValue, float iPsiValue )
{
    SetAxesValues( iSet, iPhiValue, iThetaValue, iPsiValue );
}


FEulerSet::FEulerSet( FEulerAngle::eAxis iAxisPhi, float iValuePhi, FEulerAngle::eAxis iAxisTheta, float iValueTheta, FEulerAngle::eAxis iAxisPsi, float iValuePsi )
{
    SetAxesValues( iAxisPhi, iValuePhi, iAxisTheta, iValueTheta, iAxisPsi, iValuePsi );
}


FEulerSet::FEulerSet( const  FEulerAngle&  iPhi, const  FEulerAngle&  iTheta, const  FEulerAngle&  iPsi )
{
    SetEulerAngles( iPhi, iTheta, iPsi );
}


FEulerSet::FEulerSet( const  FEulerSet&  iOther )
{
    SetFrom( iOther );
}


FEulerSet&
FEulerSet::operator=( const  FEulerSet&  iOther )
{
    SetFrom( iOther );
    return  *this;
}


//----------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------- Corrupt Check API
bool
CheckRepeatedExtrinsic( const FEulerAngle& iA, const FEulerAngle& iB )
{
    return  iA.Axis() == iB.Axis() && iA.IsExtrinsic();
}

bool
CheckRepeatedIntrinsic( const FEulerAngle& iA, const FEulerAngle& iB )
{
    return  iA.Axis() == iB.Axis() && iA.IsIntrinsic();
}


bool
CheckRepeatedExtrinsic( const  FEulerSet& iSet )
{
    return  CheckRepeatedExtrinsic( iSet.Phi(), iSet.Theta() ) || CheckRepeatedExtrinsic( iSet.Theta(), iSet.Psi() ) || CheckRepeatedExtrinsic( iSet.Phi(), iSet.Psi() );
}


bool
CheckFollowupIntrinsic( const  FEulerSet& iSet )
{
    return  CheckRepeatedIntrinsic( iSet.Phi(), iSet.Theta() ) || CheckRepeatedIntrinsic( iSet.Theta(), iSet.Psi() );
}


bool
FEulerSet::IsCorrupt()
{
    return  CheckRepeatedExtrinsic( *this ) || CheckFollowupIntrinsic( *this );
}


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------ Get / Set


void
FEulerSet::SetFrom( const  FEulerSet& iOther )
{
    mPhi = iOther.mPhi;
    mTheta = iOther.mTheta;
    mPsi = iOther.mPsi;
}


void
FEulerSet::SetEulerAngles( const  FEulerAngle& iPhi, const  FEulerAngle& iTheta, const  FEulerAngle& iPsi )
{
    mPhi = iPhi;
    mTheta = iTheta;
    mPsi = iPsi;
}


void
FEulerSet::SetAxes( eSet iSet )
{
    switch( iSet )
    {
        case eSet::kInstrinsicYXZ:
        case eSet::kYawPitchRoll:
        case eSet::kAeronautic:
        {
            SetAxes( FEulerAngle::eAxis::kIntrinsicY, FEulerAngle::eAxis::kIntrinsicX, FEulerAngle::eAxis::kIntrinsicZ );
            break;
        }
        case eSet::kExtrinsicXYZ:
        {
            SetAxes( FEulerAngle::eAxis::kExtrinsicX, FEulerAngle::eAxis::kExtrinsicY, FEulerAngle::eAxis::kExtrinsicZ );
            break;
        }
        case eSet::kPrecessionNutationIntrinsicRotation:
        case eSet::kAstronomic:
        {
            SetAxes( FEulerAngle::eAxis::kExtrinsicY, FEulerAngle::eAxis::kExtrinsicX, FEulerAngle::eAxis::kIntrinsicZ );
            break;
        }
    }
}


void
FEulerSet::SetAxes( FEulerAngle::eAxis iAxisPhi, FEulerAngle::eAxis iAxisTheta, FEulerAngle::eAxis iAxisPsi )
{
    mPhi.SetAxis( iAxisPhi );
    mTheta.SetAxis( iAxisTheta );
    mPsi.SetAxis( iAxisPsi );
}


void
FEulerSet::SetAxesValues( eSet iSet, const  glm::vec3& iValues )
{
    SetAxes( iSet );
    SetValues( iValues );
}


void
FEulerSet::SetAxesValues( eSet iSet, float iValuePhi, float iValueTheta, float iValuePsi )
{
    SetAxes( iSet );
    SetValues( iValuePhi, iValueTheta, iValuePsi );
}


void
FEulerSet::SetAxesValues( FEulerAngle::eAxis iAxisPhi, float iValuePhi, FEulerAngle::eAxis iAxisTheta, float iValueTheta, FEulerAngle::eAxis iAxisPsi, float iValuePsi )
{
    SetAxes( iAxisPhi, iAxisTheta, iAxisPsi );
    SetValues( iValuePhi, iValueTheta, iValuePsi );
}


void
FEulerSet::SetValues( const  glm::vec3& iValues )
{
    SetValues( iValues.x, iValues.y, iValues.z );
}


void
FEulerSet::SetValues( float iValuePhi, float iValueTheta, float iValuePsi )
{
    mPhi.SetValue( iValuePhi );
    mTheta.SetValue( iValueTheta );
    mPsi.SetValue( iValuePsi );
}


void
FEulerSet::SetPhi( const  FEulerAngle&  iValue )
{
    mPhi = iValue;
}


void
FEulerSet::SetTheta( const  FEulerAngle&  iValue )
{
    mTheta = iValue;
}


void
FEulerSet::SetPsi( const  FEulerAngle&  iValue )
{
    mPsi = iValue;
}


void
FEulerSet::SetPhiValue( float iValue )
{
    mPhi.SetValue( iValue );
}


void
FEulerSet::SetThetaValue( float iValue )
{
    mTheta.SetValue( iValue );
}


void
FEulerSet::SetPsiValue( float iValue )
{
    mPsi.SetValue( iValue );
}


void
FEulerSet::SetPhiAxis( FEulerAngle::eAxis  iAxis )
{
    mPhi.SetAxis( iAxis );
}


void
FEulerSet::SetThetaAxis( FEulerAngle::eAxis  iAxis )
{
    mTheta.SetAxis( iAxis );
}


void
FEulerSet::SetPsiAxis( FEulerAngle::eAxis  iAxis )
{
    mPsi.SetAxis( iAxis );
}


const  FEulerAngle&
FEulerSet::Phi()
{
    return  mPhi;
}


const  FEulerAngle&
FEulerSet::Phi()  const
{
    return  mPhi;
}
const  FEulerAngle&
FEulerSet::Theta()
{
    return  mTheta;
}


const  FEulerAngle&
FEulerSet::Theta()  const
{
    return  mTheta;
}


const  FEulerAngle&
FEulerSet::Psi()
{
    return  mPsi;
}


const  FEulerAngle&
FEulerSet::Psi()  const
{
    return  mPsi;
}


float
FEulerSet::PhiValue()  const
{
    return  mPhi.Value();
}


float
FEulerSet::ThetaValue()  const
{
    return  mTheta.Value();
}


float
FEulerSet::PsiValue()  const
{
    return  mPsi.Value();
}


FEulerAngle::eAxis
FEulerSet::PhiAxis()  const
{
    return  mPhi.Axis();
}


FEulerAngle::eAxis
FEulerSet::ThetaAxis()  const
{
    return  mTheta.Axis();
}


FEulerAngle::eAxis
FEulerSet::PsiAxis()  const
{
    return  mPsi.Axis();
}

ULIS2_NAMESPACE_END

