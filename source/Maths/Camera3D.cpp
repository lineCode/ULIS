// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Camera3D.cpp
* @author       Clement Berthaud
* @brief        This file provides the FMaths class declaration.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include "Maths/Camera3D.h"
#include "Maths/Maths.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/vector_angle.hpp>


ULIS2_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
// FCamera
//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------- Construction / Destruction
FCamera::FCamera()
    : tPrivateFTransformation3DSuperClass()
{
    mFov                            = FMaths::DegToRadF( 45.f );
    mNear                           = 10.f;
    mFar                            = 500.f;
    mViewportWidth                  = 500.f;
    mViewportHeight                 = 500.f;

    mCachedHalfFov                  = mFov / 2.f;
    mCachedViewportHalfWidth        = mViewportWidth / 2.f;
    mCachedViewportHalfHeight       = mViewportHeight / 2.f;
    mCachedViewportRatio            = mViewportWidth / mViewportHeight;

    mProjectionMode                 = eProjectionMode::kPerspective;
    mCachedProjectionMatrix         = glm::identity< glm::mat4 >();
    mCachedInverseProjectionMatrix  = glm::identity< glm::mat4 >();
    mCachedProjectionViewMatrix     = glm::identity< glm::mat4 >();
    mProjectionMatrixInvalid        = false;
    mInverseProjectionMatrixInvalid = false;
    mProjectionViewMatrixInvalid    = false;
}


//----------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------- Public API Setters
void
FCamera::SetFov( float iValue )
{
    mFov = iValue;
    mCachedHalfFov = mFov / 2.f;
    InvalidProjectionMatrix();
}


void
FCamera::SetNear( float iValue )
{
    mNear = iValue;
    InvalidProjectionMatrix();
}


void
FCamera::SetFar( float iValue )
{
    mFar = iValue;
    InvalidProjectionMatrix();
}


void
FCamera::SetViewportSize( float iWidth, float iHeight )
{
    mViewportWidth  = iWidth;
    mViewportHeight = iHeight;
    mCachedViewportHalfWidth = mViewportWidth / 2.f;
    mCachedViewportHalfHeight = mViewportHeight / 2.f;
    mCachedViewportRatio = mViewportWidth / mViewportHeight;
    InvalidProjectionMatrix();
}


void
FCamera::SetProjectionMode( eProjectionMode iValue )
{
    mProjectionMode = iValue;
    InvalidProjectionMatrix();
}


//----------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------- Public API Getters
FTransformation3D&
FCamera::Transformation()
{
    return  *this;
}


const FTransformation3D&
FCamera::Transformation()  const
{
    return  *this;
}


FCamera::eProjectionMode
FCamera::ProjectionMode()  const
{
    return  mProjectionMode;
}


float
FCamera::Fov()  const
{
    return  mFov;
}


float
FCamera::Near()  const
{
    return  mNear;
}


float
FCamera::Far()  const
{
    return  mFar;
}


float
FCamera::ViewportWidth()  const
{
    return  mViewportWidth;
}


float
FCamera::ViewportHeight()  const
{
    return  mViewportHeight;
}


float
FCamera::ViewportRatio()  const
{
    return  mCachedViewportRatio;
}


//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------- Advanced Computation Getters
float
FCamera::GetFocalDistortionDepth()  const
{
    return  1.f / tan( mCachedHalfFov ) * ( mCachedViewportHalfHeight );
}


void
FCamera::GetWorldFrustrumPoints( glm::vec3* oNearTopLeft, glm::vec3* oNearTopRight, glm::vec3* oNearBotRight, glm::vec3* oNearBotLeft
                               , glm::vec3* oFarTopLeft,  glm::vec3* oFarTopRight,  glm::vec3* oFarBotRight,  glm::vec3* oFarBotLeft )  const
{
    glm::vec3 forward       = Forward();
    glm::vec3 right         = Right();
    glm::vec3 up            = Up();

    glm::vec3 pos           = Translation();
    glm::vec3 nearCenter    = pos + ( forward * mNear );
    glm::vec3 farCenter     = pos + ( forward * mFar );

    float factor            = tan( mCachedHalfFov );
    float hnear             = factor * mNear;
    float wnear             = hnear * mCachedViewportRatio;
    float hfar              = factor * mFar;
    float wfar              = hfar * mCachedViewportRatio;

    *oNearTopLeft           = nearCenter - right * wnear + up * hnear;
    *oNearTopRight          = nearCenter + right * wnear + up * hnear;
    *oNearBotRight          = nearCenter + right * wnear - up * hnear;
    *oNearBotLeft           = nearCenter - right * wnear - up * hnear;

    *oFarTopLeft            = farCenter - right * wfar + up * hfar;
    *oFarTopRight           = farCenter + right * wfar + up * hfar;
    *oFarBotRight           = farCenter + right * wfar - up * hfar;
    *oFarBotLeft            = farCenter - right * wfar - up * hfar;
}


void
FCamera::GetViewFrustrumPoints( glm::vec3* oNearTopLeft, glm::vec3* oNearTopRight, glm::vec3* oNearBotRight, glm::vec3* oNearBotLeft
                              , glm::vec3* oFarTopLeft,  glm::vec3* oFarTopRight,  glm::vec3* oFarBotRight,  glm::vec3* oFarBotLeft )  const
{
    glm::vec3 forward       = glm::vec3( 0, 0, 1 );
    glm::vec3 right         = glm::vec3( 1, 0, 0 );
    glm::vec3 up            = glm::vec3( 0, 1, 0 );

    glm::vec3 pos           = glm::vec3( 0, 0, 0 );
    glm::vec3 nearCenter    = pos + ( forward * mNear );
    glm::vec3 farCenter     = pos + ( forward * mFar );

    float factor            = tan( mCachedHalfFov );
    float hnear             = factor * mNear;
    float wnear             = hnear * mCachedViewportRatio;
    float hfar              = factor * mFar;
    float wfar              = hfar * mCachedViewportRatio;

    *oNearTopLeft           = nearCenter - right * wnear + up * hnear;
    *oNearTopRight          = nearCenter + right * wnear + up * hnear;
    *oNearBotRight          = nearCenter + right * wnear - up * hnear;
    *oNearBotLeft           = nearCenter - right * wnear - up * hnear;

    *oFarTopLeft            = farCenter - right * wfar + up * hfar;
    *oFarTopRight           = farCenter + right * wfar + up * hfar;
    *oFarBotRight           = farCenter + right * wfar - up * hfar;
    *oFarBotLeft            = farCenter - right * wfar - up * hfar;
}


//----------------------------------------------------------------------------------------------
//---------------------------------------------------------------------- Intermediate Matrix API
const glm::mat4&
FCamera::ProjectionMatrix()  const
{
    UpdateProjectionMatrix();
    return  mCachedProjectionMatrix;
}


const  glm::mat4&
FCamera::InverseProjectionMatrix()  const
{
    UpdateInverseProjectionMatrix();
    return  mCachedInverseProjectionMatrix;
}


const  glm::mat4&
FCamera::ProjectionViewMatrix()  const
{
    UpdateProjectionViewMatrix();
    return  mCachedProjectionViewMatrix;
}


//----------------------------------------------------------------------------------------------
//--------------------------------------------------------------- Public Matrix Cache Management
void
FCamera::UpdateProjectionMatrix()  const
{
    if( !mProjectionMatrixInvalid )
        return;

    if( mProjectionMode == eProjectionMode::kPerspective )
    {
        // Perspective
        mCachedProjectionMatrix = glm::perspectiveRH( mFov, ViewportRatio(), mNear, mFar );
    }
    else // if( mProjectionMode == eProjectionMode::kOrthographic )
    {
        // Orthographic
        mCachedProjectionMatrix = glm::ortho( -mCachedViewportHalfWidth
                                            ,  mCachedViewportHalfWidth
                                            , -mCachedViewportHalfHeight
                                            ,  mCachedViewportHalfHeight
                                            , 0.f, mFar );
    }

    mProjectionMatrixInvalid = false;
}


void
FCamera::UpdateInverseProjectionMatrix()  const
{
    if( !mInverseProjectionMatrixInvalid )
        return;

    UpdateProjectionMatrix();
    mCachedInverseProjectionMatrix = glm::inverse( mCachedProjectionMatrix );
    mInverseProjectionMatrixInvalid = false;
}


void
FCamera::UpdateProjectionViewMatrix()  const
{
    if( !mProjectionViewMatrixInvalid )
        return;

    mCachedProjectionViewMatrix = ProjectionMatrix() * tPrivateFTransformation3DSuperClass::InverseMatrix();

    mProjectionViewMatrixInvalid = false;
}


//----------------------------------------------------------------------------------------------
//------------------------------------------------------ Protected Matrix Cache Management
void
FCamera::InvalidProjectionMatrix()  const
{
    mProjectionMatrixInvalid = true;
    mInverseProjectionMatrixInvalid = true;
    mProjectionViewMatrixInvalid = true;
}


//virtual
void
FCamera::InvalidMatrix()  const
{
    tPrivateFTransformation3DSuperClass::InvalidMatrix();
    mProjectionViewMatrixInvalid = true;
    mInverseProjectionMatrixInvalid = true;
}

ULIS2_NAMESPACE_END

