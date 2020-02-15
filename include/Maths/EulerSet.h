// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         EulerSet.h
* @author       Clement Berthaud
* @brief        This file provides the FMaths class declaration.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Base/Core.h"
#include "Maths/EulerAngle.h"
#include <glm/vec3.hpp>

ULIS2_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
// FEulerSet
class FEulerSet
{

public:
    enum  eSet
    {
        kInstrinsicYXZ,
        kExtrinsicXYZ,
        kYawPitchRoll,
        kPrecessionNutationIntrinsicRotation,
        kAeronautic,
        kAstronomic,
    };

public:
    // Construction / Destruction
    ~FEulerSet();
    FEulerSet();
    FEulerSet( const  glm::vec3& iValues );
    FEulerSet( eSet iSet );
    FEulerSet( eSet iSet, const  glm::vec3& iValues );
    FEulerSet( eSet iSet, float iPhiValue, float iThetaValue, float iPsiValue );
    FEulerSet( FEulerAngle::eAxis iAxisPhi, float iValuePhi, FEulerAngle::eAxis iAxisTheta, float iValueTheta, FEulerAngle::eAxis iAxisPsi, float iValuePsi );
    FEulerSet( const  FEulerAngle&  iPhi, const  FEulerAngle&  iTheta, const  FEulerAngle&  iPsi );
    FEulerSet( const  FEulerSet&  iOther );
    FEulerSet& operator=( const  FEulerSet&  iOther );

public:
    // Corrupt Check API
    bool  IsCorrupt();

public:
    // Get / Set
    void  SetFrom( const  FEulerSet& iOther );
    void  SetEulerAngles( const  FEulerAngle& iPhi, const  FEulerAngle& iTheta, const  FEulerAngle& iPsi );
    void  SetAxes( eSet iSet );
    void  SetAxes( FEulerAngle::eAxis iAxisPhi, FEulerAngle::eAxis iAxisTheta, FEulerAngle::eAxis iAxisPsi );
    void  SetAxesValues( eSet iSet, const  glm::vec3& iValues );
    void  SetAxesValues( eSet iSet, float iValuePhi, float iValueTheta, float iValuePsi );
    void  SetAxesValues( FEulerAngle::eAxis iAxisPhi, float iValuePhi, FEulerAngle::eAxis iAxisTheta, float iValueTheta, FEulerAngle::eAxis iAxisPsi, float iValuePsi );
    void  SetValues( const  glm::vec3& iValues );
    void  SetValues( float iValuePhi, float iValueTheta, float iValuePsi );

    void  SetPhi( const  FEulerAngle&  iValue );
    void  SetTheta( const  FEulerAngle&  iValue );
    void  SetPsi( const  FEulerAngle&  iValue );

    void  SetPhiValue( float iValue );
    void  SetThetaValue( float iValue );
    void  SetPsiValue( float iValue );

    void  SetPhiAxis( FEulerAngle::eAxis  iAxis );
    void  SetThetaAxis( FEulerAngle::eAxis  iAxis );
    void  SetPsiAxis( FEulerAngle::eAxis  iAxis );

    const  FEulerAngle&  Phi();
    const  FEulerAngle&  Phi()  const;
    const  FEulerAngle&  Theta();
    const  FEulerAngle&  Theta()  const;
    const  FEulerAngle&  Psi();
    const  FEulerAngle&  Psi()  const;
    float  PhiValue()  const;
    float  ThetaValue()  const;
    float  PsiValue()  const;
    FEulerAngle::eAxis  PhiAxis()  const;
    FEulerAngle::eAxis  ThetaAxis()  const;
    FEulerAngle::eAxis  PsiAxis()  const;

private:
    // Data Members
    FEulerAngle mPhi;
    FEulerAngle mTheta;
    FEulerAngle mPsi;
};


ULIS2_NAMESPACE_END

