// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         EulerAngle.cpp
* @author       Clement Berthaud
* @brief        This file provides the FMaths class declaration.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include "Maths/EulerAngle.h"

ULIS2_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
// FEulerAngle
//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------- Construction / Destruction
FEulerAngle::~FEulerAngle()
{
}


FEulerAngle::FEulerAngle() :
    mValue( 0.f ),
    mAxis( kIntrinsicX )
{
}


FEulerAngle::FEulerAngle( eAxis iAxis, float iValue ) :
    mValue( iValue ),
    mAxis( iAxis )
{
}


FEulerAngle::FEulerAngle( const  FEulerAngle  &iOther ) :
    mValue( iOther.mValue ),
    mAxis( iOther.mAxis )
{
}


FEulerAngle&
FEulerAngle::operator=( const FEulerAngle&  iOther )
{
    mValue = iOther.mValue;
    mAxis = iOther.mAxis;
    return  *this;
}


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------ Check API
//static
bool
FEulerAngle::IsIntrinsic( eAxis iAxis )
{
    return  iAxis < kExtrinsicX;
}


//static
bool
FEulerAngle::IsExtrinsic( eAxis iAxis )
{
    return  iAxis >= kExtrinsicX;
}


bool
FEulerAngle::IsIntrinsic() const
{
    return  IsIntrinsic( mAxis );
}


bool
FEulerAngle::IsExtrinsic() const
{
    return  IsExtrinsic( mAxis );
}


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------ Get / Set


void
FEulerAngle::SetValue( float iValue )
{
    mValue = iValue;
}


void
FEulerAngle::SetAxis( eAxis iAxis )
{
    mAxis = iAxis;
}


float
FEulerAngle::Value()  const
{
    return  mValue;
}


FEulerAngle::eAxis
FEulerAngle::Axis()  const
{
    return  mAxis;
}

ULIS2_NAMESPACE_END

