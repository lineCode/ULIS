// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         EulerAngle.h
* @author       Clement Berthaud
* @brief        This file provides the FMaths class declaration.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Base/Core.h"

ULIS2_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
// FEulerAngle
class FEulerAngle
{
public:
    enum  eAxis
    {
        kIntrinsicX,
        kIntrinsicY,
        kIntrinsicZ,
        kExtrinsicX,
        kExtrinsicY,
        kExtrinsicZ,
    };

public:
    // Construction / Destruction
    ~FEulerAngle();
    FEulerAngle();
    FEulerAngle( eAxis iAxis, float iValue );
    FEulerAngle( const  FEulerAngle&  iOther );
    FEulerAngle& operator=( const  FEulerAngle&  iOther );

public:
    // Check API
    static  bool  IsIntrinsic( eAxis iAxis );
    static  bool  IsExtrinsic( eAxis iAxis );
    bool IsIntrinsic() const;
    bool IsExtrinsic() const;

public:
    // Get / Set
    void  SetValue( float iValue );
    void  SetAxis( eAxis iAxis );

    float Value()  const;
    eAxis Axis()  const;

private:
    // Data Members
    float  mValue; // rad
    eAxis  mAxis;
};


ULIS2_NAMESPACE_END

