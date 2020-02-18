// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Transformation3D.h
* @author       Clement Berthaud
* @brief        This file provides the FMaths class declaration.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Base/Core.h"
#include "Maths/EulerSet.h"
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>

ULIS2_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
// FAxisAngle
struct FAxisAngle
{
    float angle;
    glm::vec3 axis;

    FAxisAngle()
        : angle( 0 )
        , axis( glm::vec3() )
    {}
};

/////////////////////////////////////////////////////
// FTransformation3D
class FTransformation3D
{
public:
    // Construction / Destruction
    FTransformation3D();

public:
    // Pivot setter
    void  ResetPivot();
    void  SetPivot( const  glm::vec3& iValues );
    void  SetPivot( float iX, float iY, float iZ );
    void  SetPivotX( float iValue );
    void  SetPivotY( float iValue );
    void  SetPivotZ( float iValue );

    void  MovePivot( const  glm::vec3& iDelta );
    void  MovePivot( float iDeltaX, float iDeltaY, float iDeltaZ );
    void  MovePivotX( float iDelta );
    void  MovePivotY( float iDelta );
    void  MovePivotZ( float iDelta );
    void  MovePivotRight( float iDelta );
    void  MovePivotUp( float iDelta );
    void  MovePivotForward( float iDelta );

    // Translation setter
    void  ResetTranslation();
    void  SetTranslation( const  glm::vec3& iValues );
    void  SetTranslation( float iX, float iY, float iZ );
    void  SetTranslationX( float iValue );
    void  SetTranslationY( float iValue );
    void  SetTranslationZ( float iValue );

    void  Translate( const  glm::vec3& iDelta );
    void  Translate( float iDeltaX, float iDeltaY, float iDeltaZ );
    void  TranslateX( float iDelta );
    void  TranslateY( float iDelta );
    void  TranslateZ( float iDelta );
    void  Move( const  glm::vec3& iDelta );
    void  Move( float iDeltaRight, float iDeltaUp, float iDeltaForward );
    void  MoveRight( float iDelta );
    void  MoveUp( float iDelta );
    void  MoveForward( float iDelta );

    // Rotation setter
    void  ResetRotation();
    void  SetRotation( const FAxisAngle& iAxisAngle );
    void  SetRotation( float iAngleRad, const  glm::vec3& iAxis );
    void  SetRotation( float iAngleRad, float iAxisX, float iAxisY, float iAxisZ );
    void  SetRotation( const  FEulerSet& iEulerSet );
    void  SetRotation( const  FEulerAngle& iEulerAngle );
    void  SetRotation( const  glm::quat& iQuat );

    void  Rotate( const FAxisAngle& iAxisAngle );
    void  Rotate( float iAngleRad, const  glm::vec3& iAxis );
    void  Rotate( float iAngleRad, float iAxisX, float iAxisY, float iAxisZ );
    void  Rotate( const  FEulerSet& iEulerSet );
    void  Rotate( const  FEulerAngle& iEulerAngle );
    void  Rotate( const  glm::quat& iQuat );

    void  RotateX( float iValue );
    void  RotateY( float iValue );
    void  RotateZ( float iValue );
    void  Yaw( float iValue );
    void  Pitch( float iValue );
    void  Roll( float iValue );
    void  Precess( float iValue );
    void  Nutate( float iValue );

    // Scale setter
    void  ResetScale();
    void  SetScale( const  glm::vec3& iValues );
    void  SetScale( float iX, float iY, float iZ );
    void  SetScaleUniform( float iValue );
    void  SetScaleX( float iValue );
    void  SetScaleY( float iValue );
    void  SetScaleZ( float iValue );

    void  Stretch( const  glm::vec3& iValues );
    void  Stretch( float iX, float iY, float iZ );
    void  StretchUniform( float iValue );
    void  StretchX( float iValue );
    void  StretchY( float iValue );
    void  StretchZ( float iValue );

    void  DeltaScale( const  glm::vec3& iValues );
    void  DeltaScale( float iX, float iY, float iZ );
    void  DeltaScaleUniform( float iValue );
    void  DeltaScaleX( float iValue );
    void  DeltaScaleY( float iValue );
    void  DeltaScaleZ( float iValue );

public:
    // Pivot Getter
    glm::vec3  Pivot()  const;
    float  PivotX()  const;
    float  PivotY()  const;
    float  PivotZ()  const;

    // Translation Getter
    glm::vec3  Translation()  const;
    float  TranslationX()  const;
    float  TranslationY()  const;
    float  TranslationZ()  const;

    // Rotation Getter
    FAxisAngle  RotationAsAxisAngle()  const;
    FEulerSet   RotationAsEulerSet()  const;
    glm::quat   RotationAsQuaternion()  const;

    // Scale Getter
    glm::vec3  Scale()  const;
    float  ScaleX()  const;
    float  ScaleY()  const;
    float  ScaleZ()  const;

public:
    // Advanced Positioning
    void  TargetLocal( const  glm::vec3& iTarget ); // From local, reset up
    void  Target( const  glm::vec3& iTarget ); // From external, reset up

public:
    // Frame of ref API
    glm::vec3  Right()  const;      // Intrinsic expressed in external basis
    glm::vec3  Up()  const;         // Intrinsic expressed in external basis
    glm::vec3  Forward()  const;    // Intrinsic expressed in external basis
    glm::vec3  IntrinsicXAxis()  const; // Same as X( 1, 0, 0 ), expressed in local basis
    glm::vec3  IntrinsicYAxis()  const; // Same as Y( 0, 1, 0 ), expressed in local basis
    glm::vec3  IntrinsicZAxis()  const; // Same as Z( 0, 0, 1 ), expressed in local basis
    glm::vec3  ExtrinsicXAxis()  const; // Same as Right, expressed in local basis
    glm::vec3  ExtrinsicYAxis()  const; // Same as Up, expressed in local basis
    glm::vec3  ExtrinsicZAxis()  const; // Same as Forward, expressed in local basis
    glm::vec3  VectorForAxis( FEulerAngle::eAxis iAxis )  const;

public:
    // Conversion API
    glm::vec4  ToLocal( const  glm::vec4& iHPoint )  const;         // from external to local
    glm::vec4  FromLocal( const  glm::vec4& iHPoint )  const;       // from local to external
    glm::vec3  PointToLocal( const  glm::vec3& iPoint )  const;     // from external to local
    glm::vec3  PointFromLocal( const  glm::vec3& iPoint )  const;   // from local to external
    glm::vec3  VecToLocal( const  glm::vec3& iVec )  const;         // from external to local
    glm::vec3  VecFromLocal( const  glm::vec3& iVec )  const;       // from local to external

public:
    // Intermediate Matrix API
    const glm::mat4& PivotMatrix()          const;
    const glm::mat4& TranslationMatrix()    const;
    const glm::mat4& ScaleMatrix()          const;
    const glm::mat4& RotationMatrix()       const;

    const glm::mat4& Matrix()               const;
    const glm::mat4& InverseMatrix()        const;

    glm::mat4 InversePivotMatrix()          const;
    glm::mat4 InverseTranslationMatrix()    const;
    glm::mat4 InverseScaleMatrix()          const;
    glm::mat4 InverseRotationMatrix()       const;

public:
    // Public Matrix Cache Management
    void  UpdateMatrix()                    const;
    void  UpdateInverseMatrix()             const;

protected:
    // Protected Matrix Cache Management
    virtual  void  InvalidMatrix()  const;
    void  SanitizeScaleMatrix()  const;

private:
    // Private Data Members
    mutable glm::mat4 mPivotMatrix;
    mutable glm::mat4 mTranslationMatrix;
    mutable glm::mat4 mScaleMatrix;
    mutable glm::mat4 mRotationMatrix;
    mutable glm::mat4 mCachedMatrix;
    mutable glm::mat4 mCachedInverseMatrix;
    mutable bool mMatrixInvalid;
    mutable bool mInverseMatrixInvalid;
};

ULIS2_NAMESPACE_END

