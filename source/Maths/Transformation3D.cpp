// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Transformation3D.cpp
* @author       Clement Berthaud
* @brief        This file provides the FMaths class declaration.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include "Maths/Transformation3D.h"
#include "Maths/Maths.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/vector_angle.hpp>


ULIS2_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
// FTransformation3D
//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------- Construction / Destruction
FTransformation3D::FTransformation3D()
{
    mPivotMatrix            = glm::identity< glm::mat4 >();
    mTranslationMatrix      = glm::identity< glm::mat4 >();
    mScaleMatrix            = glm::identity< glm::mat4 >();
    mRotationMatrix         = glm::identity< glm::mat4 >();
    mCachedMatrix           = glm::identity< glm::mat4 >();
    mCachedInverseMatrix    = glm::identity< glm::mat4 >();
    mMatrixInvalid          = false;
    mInverseMatrixInvalid   = false;
}


//----------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------- Pivot setter


void
FTransformation3D::ResetPivot()
{
    mPivotMatrix = glm::identity< glm::mat4 >();
    InvalidMatrix();
}


void
FTransformation3D::SetPivot( const  glm::vec3& iValues )
{
    // glm::mat4 is column-major order
    // mat4                                     •
    // 00 10 20 30                              .
    // 01 11 21 31  mat4                        .
    // 02 12 22 32      0       1       2       3
    // 03 13 23 33      vec4    vec4    vec4    vec4
    //                  x | 0   x | 0   x | 0   x | 0   •
    //                  y | 1   y | 1   y | 1   y | 1   •
    //                  z | 2   z | 2   z | 2   z | 2   •
    //                  w | 3   w | 3   w | 3   w | 3

    // pivot acts as a translation matrix
    // 1 0 0 x
    // 0 1 0 y
    // 0 0 1 z
    // 0 0 0 1  This is the look of a column-major pure translation matrix

    // Notice the minus, Pivot corresponds to an inverted translation.
    mPivotMatrix[3].x = -iValues.x;
    mPivotMatrix[3].y = -iValues.y;
    mPivotMatrix[3].z = -iValues.z;
    InvalidMatrix();
}


void
FTransformation3D::SetPivot( float iX, float iY, float iZ )
{
    mPivotMatrix[3].x = -iX;
    mPivotMatrix[3].y = -iY;
    mPivotMatrix[3].z = -iZ;
    InvalidMatrix();
    InvalidMatrix();
}


void
FTransformation3D::SetPivotX( float iValue )
{
    mPivotMatrix[3].x = -iValue;
    InvalidMatrix();
}


void
FTransformation3D::SetPivotY( float iValue )
{
    mPivotMatrix[3].y = -iValue;
    InvalidMatrix();
}


void
FTransformation3D::SetPivotZ( float iValue )
{
    mPivotMatrix[3].z = -iValue;
    InvalidMatrix();
}


void
FTransformation3D::MovePivot( const  glm::vec3& iDelta )
{
    mPivotMatrix[3].x += -iDelta.x;
    mPivotMatrix[3].y += -iDelta.y;
    mPivotMatrix[3].z += -iDelta.z;
    InvalidMatrix();
}


void
FTransformation3D::MovePivot( float iDeltaX, float iDeltaY, float iDeltaZ )
{
    mPivotMatrix[3].x += -iDeltaX;
    mPivotMatrix[3].y += -iDeltaY;
    mPivotMatrix[3].z += -iDeltaZ;
    InvalidMatrix();
}


void
FTransformation3D::MovePivotX( float iDelta )
{
    mPivotMatrix[3].x += -iDelta;
    InvalidMatrix();
}


void
FTransformation3D::MovePivotY( float iDelta )
{
    mPivotMatrix[3].y += -iDelta;
    InvalidMatrix();
}


void
FTransformation3D::MovePivotZ( float iDelta )
{
    mPivotMatrix[3].z += -iDelta;
    InvalidMatrix();
}


void
FTransformation3D::MovePivotRight( float iDelta )
{
    MovePivot( Right() * iDelta );
    InvalidMatrix();
}


void
FTransformation3D::MovePivotUp( float iDelta )
{
    MovePivot( Up() * iDelta );
    InvalidMatrix();
}


void
FTransformation3D::MovePivotForward( float iDelta )
{
    MovePivot( Forward() * iDelta );
    InvalidMatrix();
}


//----------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------- Translation setter


void
FTransformation3D::ResetTranslation()
{
    mTranslationMatrix = glm::identity< glm::mat4 >();
    InvalidMatrix();
}


void
FTransformation3D::SetTranslation( const  glm::vec3& iValues )
{
    // glm::mat4 is column-major order
    // mat4                                     •
    // 00 10 20 30                              .
    // 01 11 21 31  mat4                        .
    // 02 12 22 32      0       1       2       3
    // 03 13 23 33      vec4    vec4    vec4    vec4
    //                  x | 0   x | 0   x | 0   x | 0   •
    //                  y | 1   y | 1   y | 1   y | 1   •
    //                  z | 2   z | 2   z | 2   z | 2   •
    //                  w | 3   w | 3   w | 3   w | 3

    // pivot acts as a translation matrix
    // 1 0 0 x
    // 0 1 0 y
    // 0 0 1 z
    // 0 0 0 1  This is the look of a column-major pure translation matrix

    mTranslationMatrix[3].x = iValues.x;
    mTranslationMatrix[3].y = iValues.y;
    mTranslationMatrix[3].z = iValues.z;
    InvalidMatrix();
}


void
FTransformation3D::SetTranslation( float iX, float iY, float iZ )
{
    mTranslationMatrix[3].x = iX;
    mTranslationMatrix[3].y = iY;
    mTranslationMatrix[3].z = iZ;
    InvalidMatrix();
}


void
FTransformation3D::SetTranslationX( float iValue )
{
    mTranslationMatrix[3].x = iValue;
    InvalidMatrix();
}


void
FTransformation3D::SetTranslationY( float iValue )
{
    mTranslationMatrix[3].y = iValue;
    InvalidMatrix();
}


void
FTransformation3D::SetTranslationZ( float iValue )
{
    mTranslationMatrix[3].z = iValue;
    InvalidMatrix();
}


void
FTransformation3D::Translate( const  glm::vec3& iDelta )
{
    mTranslationMatrix[3].x += iDelta.x;
    mTranslationMatrix[3].y += iDelta.y;
    mTranslationMatrix[3].z += iDelta.z;
    InvalidMatrix();
}


void
FTransformation3D::Translate( float iDeltaX, float iDeltaY, float iDeltaZ )
{
    mTranslationMatrix[3].x += iDeltaX;
    mTranslationMatrix[3].y += iDeltaY;
    mTranslationMatrix[3].z += iDeltaZ;
    InvalidMatrix();
}


void
FTransformation3D::TranslateX( float iDelta )
{
    mTranslationMatrix[3].x += iDelta;
    InvalidMatrix();
}


void
FTransformation3D::TranslateY( float iDelta )
{
    mTranslationMatrix[3].y += iDelta;
    InvalidMatrix();
}


void
FTransformation3D::TranslateZ( float iDelta )
{
    mTranslationMatrix[3].z += iDelta;
    InvalidMatrix();
}


void
FTransformation3D::Move( const  glm::vec3& iDelta )
{
    MoveRight( iDelta.x );
    MoveUp( iDelta.y );
    MoveForward( iDelta.z );
}


void
FTransformation3D::Move( float iDeltaRight, float iDeltaUp, float iDeltaForward )
{
    MoveRight( iDeltaRight );
    MoveUp( iDeltaUp );
    MoveForward( iDeltaForward );
}


void
FTransformation3D::MoveRight( float iDelta )
{
    Translate( Right() * iDelta );
    // No need to call InvalidMatrix here
}


void
FTransformation3D::MoveUp( float iDelta )
{
    Translate( Up() * iDelta );
    // No need to call InvalidMatrix here
}


void
FTransformation3D::MoveForward( float iDelta )
{
    Translate( Forward() * iDelta );
    // No need to call InvalidMatrix here
}


//----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------  Rotation setter


void
FTransformation3D::ResetRotation()
{
    mRotationMatrix = glm::identity< glm::mat4 >();
    InvalidMatrix();
}


void
FTransformation3D::SetRotation( const FAxisAngle& iAxisAngle )
{
    mRotationMatrix = glm::rotate( glm::identity< glm::mat4 >(), iAxisAngle.angle, iAxisAngle.axis );
    InvalidMatrix();
}


void
FTransformation3D::SetRotation( float iAngleRad, const  glm::vec3& iAxis )
{
    mRotationMatrix = glm::rotate( glm::identity< glm::mat4 >(), iAngleRad, iAxis );
    InvalidMatrix();
}


void
FTransformation3D::SetRotation( float iAngleRad, float iAxisX, float iAxisY, float iAxisZ )
{
    mRotationMatrix = glm::rotate( glm::identity< glm::mat4 >(), iAngleRad, glm::vec3( iAxisX, iAxisY, iAxisZ ) );
    InvalidMatrix();
}


void
FTransformation3D::SetRotation( const  FEulerSet& iEulerSet )
{
    ResetRotation();
    Rotate( iEulerSet );
    // No need to call InvalidMatrix here
}


void
FTransformation3D::SetRotation( const  FEulerAngle& iEulerAngle )
{
    ResetRotation();
    Rotate( iEulerAngle );
    // No need to call InvalidMatrix here
}


void
FTransformation3D::SetRotation( const  glm::quat& iQuat )
{
    mRotationMatrix = glm::toMat4( iQuat );
    InvalidMatrix();
}


void
FTransformation3D::Rotate( const FAxisAngle& iAxisAngle )
{
    mRotationMatrix = glm::rotate( mRotationMatrix, iAxisAngle.angle, iAxisAngle.axis );
    InvalidMatrix();
}


void
FTransformation3D::Rotate( float iAngleRad, const  glm::vec3& iAxis )
{
    mRotationMatrix = glm::rotate( mRotationMatrix, iAngleRad, iAxis );
    InvalidMatrix();
}


void
FTransformation3D::Rotate( float iAngleRad, float iAxisX, float iAxisY, float iAxisZ )
{
    mRotationMatrix = glm::rotate( mRotationMatrix, iAngleRad, glm::vec3( iAxisX, iAxisY, iAxisZ ) );
    InvalidMatrix();
}


void
FTransformation3D::Rotate( const  FEulerSet& iEulerSet )
{
    const  FEulerAngle&  phi = iEulerSet.Phi();
    glm::vec3  phiAxisVector    = VectorForAxis( phi.Axis() );
    float  phiValue     = phi.Value();
    Rotate( phiValue, phiAxisVector );

    const  FEulerAngle&  theta = iEulerSet.Theta();
    glm::vec3  thetaAxisVector  = VectorForAxis( theta.Axis() );
    float  thetaValue   = theta.Value();
    Rotate( thetaValue, thetaAxisVector );

    const  FEulerAngle&  psi = iEulerSet.Psi();
    glm::vec3  psiAxisVector    = VectorForAxis( psi.Axis() );
    float  psiValue     = psi.Value();
    Rotate( psiValue, psiAxisVector );
    // No need to call InvalidMatrix here
}


void
FTransformation3D::Rotate( const  FEulerAngle& iEulerAngle )
{
    glm::vec3  axis = VectorForAxis( iEulerAngle.Axis() );
    float  angle = iEulerAngle.Value();
    Rotate( angle, axis );
    // No need to call InvalidMatrix here
}


void
FTransformation3D::Rotate( const  glm::quat& iQuat )
{
    mRotationMatrix = mRotationMatrix * glm::toMat4( iQuat );
    InvalidMatrix();
}


void
FTransformation3D::RotateX( float iValue )
{
    mRotationMatrix = glm::rotate( mRotationMatrix, iValue, ExtrinsicXAxis() );
    InvalidMatrix();
}


void
FTransformation3D::RotateY( float iValue )
{
    mRotationMatrix = glm::rotate( mRotationMatrix, iValue, ExtrinsicYAxis() );
    InvalidMatrix();
}


void
FTransformation3D::RotateZ( float iValue )
{
    mRotationMatrix = glm::rotate( mRotationMatrix, iValue, ExtrinsicZAxis() );
    InvalidMatrix();
}


void
FTransformation3D::Yaw( float iValue )
{
    mRotationMatrix = glm::rotate( mRotationMatrix, iValue, IntrinsicYAxis() );
    InvalidMatrix();
}


void
FTransformation3D::Pitch( float iValue )
{
    mRotationMatrix = glm::rotate( mRotationMatrix, iValue, IntrinsicXAxis() );
    InvalidMatrix();
}


void
FTransformation3D::Roll( float iValue )
{
    mRotationMatrix = glm::rotate( mRotationMatrix, iValue, IntrinsicZAxis() );
    InvalidMatrix();
}


void
FTransformation3D::Precess( float iValue )
{
    mRotationMatrix = glm::rotate( mRotationMatrix, iValue, ExtrinsicYAxis() );
    InvalidMatrix();
}


void
FTransformation3D::Nutate( float iValue )
{
    mRotationMatrix = glm::rotate( mRotationMatrix, iValue, IntrinsicXAxis() );
    InvalidMatrix();
}


//----------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------- Scale setter


void
FTransformation3D::ResetScale()
{
    mScaleMatrix = glm::identity< glm::mat4 >();
    InvalidMatrix();
}


void
FTransformation3D::SetScale( const  glm::vec3& iValues )
{
    // glm::mat4 is column-major order
    // mat4
    // 00 10 20 30
    // 01 11 21 31  mat4
    // 02 12 22 32      0       1       2       3
    // 03 13 23 33      vec4    vec4    vec4    vec4
    //                 [x • 0]  x | 0   x | 0   x | 0
    //                  y | 1  [y • 1]  y | 1   y | 1
    //                  z | 2   z | 2  [z • 2]  z | 2
    //                  w | 3   w | 3   w | 3   w | 3

    // This is the look of a column-major pure scale matrix
    // x 0 0 0
    // 0 y 0 0
    // 0 0 z 0
    // 0 0 0 1
    mScaleMatrix[0].x = iValues.x;
    mScaleMatrix[1].y = iValues.y;
    mScaleMatrix[2].z = iValues.z;
    InvalidMatrix();
}


void
FTransformation3D::SetScale( float iX, float iY, float iZ )
{
    mScaleMatrix[0].x = iX;
    mScaleMatrix[1].y = iY;
    mScaleMatrix[2].z = iZ;
    InvalidMatrix();
}


void
FTransformation3D::SetScaleUniform( float iValue )
{
    SetScale( iValue, iValue, iValue );
}


void
FTransformation3D::SetScaleX( float iValue )
{
    mScaleMatrix[0].x = iValue;
    InvalidMatrix();
}


void
FTransformation3D::SetScaleY( float iValue )
{
    mScaleMatrix[1].y = iValue;
    InvalidMatrix();
}


void
FTransformation3D::SetScaleZ( float iValue )
{
    mScaleMatrix[2].z = iValue;
    InvalidMatrix();
}


void
FTransformation3D::Stretch( const  glm::vec3& iValues )
{
    mScaleMatrix[0].x *= iValues.x;
    mScaleMatrix[1].y *= iValues.y;
    mScaleMatrix[2].z *= iValues.z;
    InvalidMatrix();
}


void
FTransformation3D::Stretch( float iX, float iY, float iZ )
{
    mScaleMatrix[0].x *= iX;
    mScaleMatrix[1].y *= iY;
    mScaleMatrix[2].z *= iZ;
    InvalidMatrix();
}


void
FTransformation3D::StretchUniform( float iValue )
{
    Stretch( iValue, iValue, iValue );
}


void
FTransformation3D::StretchX( float iValue )
{
    mScaleMatrix[0].x *= iValue;
    InvalidMatrix();
}


void
FTransformation3D::StretchY( float iValue )
{
    mScaleMatrix[1].y *= iValue;
    InvalidMatrix();
}


void
FTransformation3D::StretchZ( float iValue )
{
    mScaleMatrix[2].z *= iValue;
    InvalidMatrix();
}


void
FTransformation3D::DeltaScale( const  glm::vec3& iValues )
{
    mScaleMatrix[0].x += iValues.x;
    mScaleMatrix[1].y += iValues.y;
    mScaleMatrix[2].z += iValues.z;
    InvalidMatrix();
}


void
FTransformation3D::DeltaScale( float iX, float iY, float iZ )
{
    mScaleMatrix[0].x += iX;
    mScaleMatrix[1].y += iY;
    mScaleMatrix[2].z += iZ;
    InvalidMatrix();
}


void
FTransformation3D::DeltaScaleUniform( float iValue )
{
    DeltaScale( iValue, iValue, iValue );
}


void
FTransformation3D::DeltaScaleX( float iValue )
{
    mScaleMatrix[0].x += iValue;
    InvalidMatrix();
}


void
FTransformation3D::DeltaScaleY( float iValue )
{
    mScaleMatrix[1].y += iValue;
    InvalidMatrix();
}


void
FTransformation3D::DeltaScaleZ( float iValue )
{
    mScaleMatrix[2].z += iValue;
    InvalidMatrix();
}


//----------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------- Pivot Getter


glm::vec3
FTransformation3D::Pivot()  const
{
    // glm::mat4 is column-major order
    // mat4                                     •
    // 00 10 20 30                              .
    // 01 11 21 31  mat4                        .
    // 02 12 22 32      0       1       2       3
    // 03 13 23 33      vec4    vec4    vec4    vec4
    //                  x | 0   x | 0   x | 0   x | 0   •
    //                  y | 1   y | 1   y | 1   y | 1   •
    //                  z | 2   z | 2   z | 2   z | 2   •
    //                  w | 3   w | 3   w | 3   w | 3

    // pivot acts as a translation matrix
    // 1 0 0 x
    // 0 1 0 y
    // 0 0 1 z
    // 0 0 0 1  This is the look of a column-major pure translation matrix

    // Notice the minus, and the cast from vec4 to vec3
    return  -mPivotMatrix[3];
}


float
FTransformation3D::PivotX()  const
{
    return  -mPivotMatrix[3].x;
}


float
FTransformation3D::PivotY()  const
{
    return  -mPivotMatrix[3].y;
}


float
FTransformation3D::PivotZ()  const
{
    return  -mPivotMatrix[3].z;
}


//----------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------- Translation Getter


glm::vec3
FTransformation3D::Translation()  const
{
    // glm::mat4 is column-major order
    // mat4                                     •
    // 00 10 20 30                              .
    // 01 11 21 31  mat4                        .
    // 02 12 22 32      0       1       2       3
    // 03 13 23 33      vec4    vec4    vec4    vec4
    //                  x | 0   x | 0   x | 0   x | 0   •
    //                  y | 1   y | 1   y | 1   y | 1   •
    //                  z | 2   z | 2   z | 2   z | 2   •
    //                  w | 3   w | 3   w | 3   w | 3

    // This is the look of a column-major pure translation matrix
    // 1 0 0 x
    // 0 1 0 y
    // 0 0 1 z
    // 0 0 0 1

    // Notice the cast from vec4 to vec3
    return  mTranslationMatrix[3];
}


float
FTransformation3D::TranslationX()  const
{
    return  mTranslationMatrix[3].x;
}


float
FTransformation3D::TranslationY()  const
{
    return  mTranslationMatrix[3].y;
}


float
FTransformation3D::TranslationZ()  const
{
    return  mTranslationMatrix[3].z;
}


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------ Rotation Getter


FAxisAngle
FTransformation3D::RotationAsAxisAngle()  const
{
    // link:[http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToAngle/index.htm]
    FAxisAngle result;

    double angle,x,y,z; // variables for result
    double epsilon = 0.01; // margin to allow for rounding errors
    double epsilon2 = 0.1; // margin to distinguish between 0 and 180 degrees
    const glm::mat4& m = mRotationMatrix;

    // optional check that input is pure rotation, 'isRotationMatrix' is defined at:
    // https://www.euclideanspace.com/maths/algebra/matrix/orthogonal/rotation/
    // assert isRotationMatrix(m) : "not valid rotation matrix" ;// for debugging
    if(   ( abs( m[0][1] - m[1][0] ) < epsilon )
       && ( abs( m[0][2] - m[2][0] ) < epsilon )
       && ( abs( m[1][2] - m[2][1] ) < epsilon ) )
    {
        // singularity found
        // first check for identity matrix which must have +1 for all terms
        //  in leading diagonaland zero in other terms
        if (   ( abs( m[0][1] + m[1][0] ) < epsilon2 )
            && ( abs( m[0][2] + m[2][0] ) < epsilon2 )
            && ( abs( m[1][2] + m[2][1] ) < epsilon2 )
            && ( abs( m[0][0] + m[1][1] + m[2][2] - 3 ) < epsilon2 ) )
        {
            // this singularity is identity matrix so angle = 0
            // zero angle, arbitrary axis
            result.axis = glm::vec3( 0, 1, 0 );
            result.angle = 0.f;
            return  result;
        }

        // otherwise this singularity is angle = 180
        angle = 3.14159265359f;
        double xx = ( m[0][0] +1 ) / 2;
        double yy = ( m[1][1] +1 ) / 2;
        double zz = ( m[2][2] +1 ) / 2;
        double xy = ( m[0][1] + m[1][0] ) / 4;
        double xz = ( m[0][2] + m[2][0] ) / 4;
        double yz = ( m[1][2] + m[2][1] ) / 4;

        if( ( xx > yy ) && ( xx > zz ) ) // m[0][0] is the largest diagonal term
        {
            if( xx < epsilon )
            {
                x = 0;
                y = 0.7071;
                z = 0.7071;
            }
            else
            {
                x = sqrt(xx);
                y = xy/x;
                z = xz/x;
            }
        }
        else if(yy > zz) // m[1][1] is the largest diagonal term
        {
            if (yy< epsilon)
            {
                x = 0.7071;
                y = 0;
                z = 0.7071;
            }
            else
            {
                y = sqrt(yy);
                x = xy/y;
                z = yz/y;
            }
        }
        else // m[2][2] is the largest diagonal term so base result on this
        {
            if(zz< epsilon)
            {
                x = 0.7071;
                y = 0.7071;
                z = 0;
            }
            else
            {
                z = sqrt(zz);
                x = xz/z;
                y = yz/z;
            }
        }

        // return 180 deg rotation
        result.axis = glm::vec3( x, y, z );
        result.angle = static_cast< float >( angle );
        return  result;
    }
    // as we have reached here there are no singularities so we can handle normally
    double s = sqrt(  ( m[2][1] - m[1][2] ) * ( m[2][1] - m[1][2] )
                    + ( m[0][2] - m[2][0] ) * ( m[0][2] - m[2][0] )
                    + ( m[1][0] - m[0][1] ) * ( m[1][0] - m[0][1] ) ); // used to normalise
    if( abs(s) < 0.001) s=1;
        // prevent divide by zero, should not happen if matrix is orthogonal and should be
        // caught by singularity test above, but I've left it in just in case
    angle = acos( ( m[0][0] + m[1][1] + m[2][2] - 1 ) / 2 );
    x = ( m[2][1] - m[1][2] ) / s;
    y = ( m[0][2] - m[2][0] ) / s;
    z = ( m[1][0] - m[0][1] ) / s;

    result.axis = glm::vec3( x, y, z );
    result.angle = static_cast< float >( angle );
    return  result;
}


FEulerSet
FTransformation3D::RotationAsEulerSet()  const
{
    glm::vec3 current_forward    = Forward();
    glm::vec2 forward_projection = glm::normalize( glm::vec2( current_forward.x, current_forward.z ) );
    float yaw = glm::orientedAngle( forward_projection, glm::vec2( 0, 1 ) );
    glm::vec3 tmp_forward = glm::vec3( forward_projection.x, 0, forward_projection.y );
    float pitch = -FMaths::Sign( current_forward.y ) * glm::orientedAngle( tmp_forward, current_forward, glm::cross( tmp_forward, current_forward ) );
    FTransformation3D tmp;
    tmp.Yaw( yaw );
    tmp.Pitch( pitch );
    glm::vec3 current_right = Right();
    glm::vec3 tmp_right = tmp.Right();
    float roll = FMaths::Sign( current_right.y ) * glm::orientedAngle( current_right, tmp_right, glm::cross( current_right, tmp_right ) );
    return  FEulerSet( FEulerSet::eSet::kInstrinsicYXZ, yaw, pitch, roll );
}


glm::quat
FTransformation3D::RotationAsQuaternion()  const
{
    return  glm::quat( mRotationMatrix );
}


//----------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------- Scale Getter


glm::vec3
FTransformation3D::Scale()  const
{
    // glm::mat4 is column-major order
    // mat4
    // 00 10 20 30
    // 01 11 21 31  mat4
    // 02 12 22 32      0       1       2       3
    // 03 13 23 33      vec4    vec4    vec4    vec4
    //                 [x • 0]  x | 0   x | 0   x | 0
    //                  y | 1  [y • 1]  y | 1   y | 1
    //                  z | 2   z | 2  [z • 2]  z | 2
    //                  w | 3   w | 3   w | 3   w | 3

    // This is the look of a column-major pure scale matrix
    // x 0 0 0
    // 0 y 0 0
    // 0 0 z 0
    // 0 0 0 1

    auto x = mScaleMatrix[0].x;
    auto y = mScaleMatrix[1].y;
    auto z = mScaleMatrix[2].z;
    return  glm::vec3( x, y, z );
}


float
FTransformation3D::ScaleX()  const
{
    return  mScaleMatrix[0].x;
}


float
FTransformation3D::ScaleY()  const
{
    return  mScaleMatrix[1].y;
}


float
FTransformation3D::ScaleZ()  const
{
    return  mScaleMatrix[2].z;
}


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------------- Advanced Positioning


void
FTransformation3D::TargetLocal( const  glm::vec3& iTarget )
{
    // This version resets the up vector to align with axis
    glm::vec3 target = iTarget;
    if( target == glm::vec3( 0, 0, 0 ) )
        target = Forward();

    mRotationMatrix = glm::lookAt( glm::vec3( 0, 0, 0 ), target, glm::vec3( 0, 1, 0 ) );
    InvalidMatrix();
}


void
FTransformation3D::Target( const  glm::vec3& iTarget )
{
    glm::vec3 diff = iTarget - Translation();
    glm::vec3 current_forward = glm::normalize( diff );
    glm::vec2 forward_projection = glm::normalize( glm::vec2( current_forward.x, current_forward.z ) );
    glm::vec3 tmp_forward = glm::vec3( forward_projection.x, 0, forward_projection.y );
    float yaw = glm::orientedAngle( forward_projection, glm::vec2( 0, 1 ) );
    float pitch = FMaths::Sign( current_forward.y ) * glm::orientedAngle( tmp_forward, current_forward, glm::cross( tmp_forward, current_forward ) );
    FEulerSet set( FEulerSet::eSet::kInstrinsicYXZ, yaw + FMaths::kPIf, pitch, 0 );
    SetRotation( set );
}


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------ Referential API


glm::vec3
FTransformation3D::Right()  const
{
    // Notice the cast to glm::vec3
    return  mRotationMatrix[0];
}


glm::vec3
FTransformation3D::Up()  const
{
    // Notice the cast to glm::vec3
    return  mRotationMatrix[1];
}


glm::vec3
FTransformation3D::Forward()  const
{
    // Notice the cast to glm::vec3
    return  -mRotationMatrix[2];
}


glm::vec3
FTransformation3D::IntrinsicXAxis()  const
{
    return  glm::vec3( 1, 0, 0 );
}


glm::vec3
FTransformation3D::IntrinsicYAxis()  const
{
    return  glm::vec3( 0, 1, 0 );
}


glm::vec3
FTransformation3D::IntrinsicZAxis()  const
{
    return  glm::vec3( 0, 0, 1 );
}


glm::vec3
FTransformation3D::ExtrinsicXAxis()  const
{
    // Notice the vector is affected by rotation and scale so we normalize it.
    return  glm::normalize( glm::vec3( InverseMatrix() * glm::vec4( 1, 0, 0, 0 ) ) );
}


glm::vec3
FTransformation3D::ExtrinsicYAxis()  const
{
    // Notice the vector is affected by rotation and scale so we normalize it.
    return  glm::normalize( glm::vec3( InverseMatrix() * glm::vec4( 0, 1, 0, 0 ) ) );
}


glm::vec3
FTransformation3D::ExtrinsicZAxis()  const
{
    // Notice the vector is affected by rotation and scale so we normalize it.
    return  glm::normalize( glm::vec3( InverseMatrix() * glm::vec4( 0, 0, 1, 0 ) ) );
}


glm::vec3
FTransformation3D::VectorForAxis( FEulerAngle::eAxis iAxis )  const
{
    switch( iAxis )
    {
        case FEulerAngle::eAxis::kIntrinsicX:
            return  IntrinsicXAxis();

        case FEulerAngle::eAxis::kIntrinsicY:
            return  IntrinsicYAxis();

        case FEulerAngle::eAxis::kIntrinsicZ:
            return  IntrinsicZAxis();

        case FEulerAngle::eAxis::kExtrinsicX:
            return  ExtrinsicXAxis();

        case FEulerAngle::eAxis::kExtrinsicY:
            return  ExtrinsicYAxis();

        case FEulerAngle::eAxis::kExtrinsicZ:
            return  ExtrinsicZAxis();

        default:
            ULIS2_CRASH_DELIBERATE;
            return  glm::vec3( 0, 0, 0 );
    }
}


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------- Conversion API


glm::vec4
FTransformation3D::ToLocal( const  glm::vec4& iHPoint )  const
{
    return  Matrix() * iHPoint;
}


glm::vec4
FTransformation3D::FromLocal( const  glm::vec4& iHPoint )  const
{
    return  InverseMatrix() * iHPoint;
}


glm::vec3
FTransformation3D::PointToLocal( const  glm::vec3& iPoint )  const
{
    return  Matrix() * glm::vec4( iPoint, 1.f );
}


glm::vec3
FTransformation3D::PointFromLocal( const  glm::vec3& iPoint )  const
{
    return  InverseMatrix() * glm::vec4( iPoint, 1.f );
}


glm::vec3
FTransformation3D::VecToLocal( const  glm::vec3& iVec )  const
{
    return  Matrix() * glm::vec4( iVec, 0.f );
}


glm::vec3
FTransformation3D::VecFromLocal( const  glm::vec3& iVec )  const
{
    return  InverseMatrix() * glm::vec4( iVec, 0.f );
}


//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------- Matrix API


const glm::mat4&
FTransformation3D::PivotMatrix()  const
{
    return  mPivotMatrix;
}


const glm::mat4&
FTransformation3D::TranslationMatrix()  const
{
    return  mTranslationMatrix;
}


const glm::mat4&
FTransformation3D::ScaleMatrix()  const
{
    return  mScaleMatrix;
}


const glm::mat4&
FTransformation3D::RotationMatrix()  const
{
    return  mRotationMatrix;
}


const glm::mat4&
FTransformation3D::Matrix()  const
{
    UpdateMatrix();
    return  mCachedMatrix;
}


const glm::mat4&
FTransformation3D::InverseMatrix()  const
{
    UpdateInverseMatrix();
    return  mCachedInverseMatrix;
}


glm::mat4
FTransformation3D::InversePivotMatrix()  const
{
    return  glm::inverse( mPivotMatrix );
}


glm::mat4
FTransformation3D::InverseTranslationMatrix()  const
{
    return  glm::inverse( mTranslationMatrix );
}


glm::mat4
FTransformation3D::InverseScaleMatrix()  const
{
    return  glm::inverse( mScaleMatrix );
}


glm::mat4
FTransformation3D::InverseRotationMatrix()  const
{
    return  glm::inverse( mRotationMatrix );
}


//----------------------------------------------------------------------------------------------
//---------------------------------------------------------------------- Protected Matrix Update


void
FTransformation3D::InvalidMatrix()  const
{
    mMatrixInvalid = true;
    mInverseMatrixInvalid = true;
}


void
FTransformation3D::SanitizeScaleMatrix()  const
{
    if( mScaleMatrix[0].x == 0.f )
        mScaleMatrix[0].x = FMaths::kEpsilonf;
    if( mScaleMatrix[1].y == 0.f )
        mScaleMatrix[1].y = FMaths::kEpsilonf;
    if( mScaleMatrix[2].z == 0.f )
        mScaleMatrix[2].z = FMaths::kEpsilonf;
}


void
FTransformation3D::UpdateMatrix()  const
{
    if( !mMatrixInvalid )
        return;

    SanitizeScaleMatrix();
    mCachedMatrix = mTranslationMatrix * mRotationMatrix * mScaleMatrix * mPivotMatrix;
    mMatrixInvalid = false;
}


void
FTransformation3D::UpdateInverseMatrix()  const
{
    if( !mInverseMatrixInvalid )
        return;

    UpdateMatrix();
    mCachedInverseMatrix = glm::inverse( mCachedMatrix );
    mInverseMatrixInvalid = false;
}

ULIS2_NAMESPACE_END

