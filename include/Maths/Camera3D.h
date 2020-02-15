// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Camera3D.h
* @author       Clement Berthaud
* @brief        This file provides the FMaths class declaration.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Base/Core.h"
#include "Maths/Transformation3D.h"

ULIS2_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
// FCamera
class FCamera
    : private FTransformation3D
{
private:
    // Private typedefs
    typedef FTransformation3D tPrivateFTransformation3DSuperClass;

public:
    // Enums
enum class eProjectionMode
{
      kPerspective
    , kOrthographic
};

public:
    // Construction / Destruction
    FCamera();

public:
    // Public API Setters
    void  SetFov( float iValue );
    void  SetNear( float iValue );
    void  SetFar( float iValue );
    void  SetViewportSize( float iWidth, float iHeight );
    void  SetProjectionMode( eProjectionMode iValue );

public:
    // Public API Getters
    FTransformation3D&          Transformation();
    const FTransformation3D&    Transformation()    const;
    eProjectionMode             ProjectionMode()    const;
    float                       Fov()               const;
    float                       Near()              const;
    float                       Far()               const;
    float                       ViewportWidth()     const;
    float                       ViewportHeight()    const;
    float                       ViewportRatio()     const;

public:
    // Advanced Computation Getters
    // Explanation: For the "Focal Distortion Depth", an image located at this depth will
    // appear at "true" resolution: that is without scale due to the perpspective,
    // assuming the image does face the camera though.
    // You can use this depth and apply a 0.5f factor to get a 2x enlargement.
    // You can use this depth and apply a 2.0f factor to get a 0.5x reduction.
    // This point depends solely on the fov, not on near / far, nor viewport ratio.
    // It is obtained this way:
    // for pt ( x, y, z )
    // for it to remain on the same projection axis for any z
    // then y = tan( fov / 2 ) * z
    // hence z = y / tan( fov / 2 )
    float  GetFocalDistortionDepth()  const;
    void  GetWorldFrustrumPoints( glm::vec3* oNearTopLeft, glm::vec3* oNearTopRight, glm::vec3* oNearBotRight, glm::vec3* oNearBotLeft
                                , glm::vec3* oFarTopLeft,  glm::vec3* oFarTopRight,  glm::vec3* oFarBotRight,  glm::vec3* oFarBotLeft )  const;
    void  GetViewFrustrumPoints(  glm::vec3* oNearTopLeft, glm::vec3* oNearTopRight, glm::vec3* oNearBotRight, glm::vec3* oNearBotLeft
                                , glm::vec3* oFarTopLeft,  glm::vec3* oFarTopRight,  glm::vec3* oFarBotRight,  glm::vec3* oFarBotLeft )  const;

public:
    // Intermediate Matrix API
    const  glm::mat4&  ProjectionMatrix()  const;
    const  glm::mat4&  InverseProjectionMatrix()  const;
    const  glm::mat4&  ProjectionViewMatrix()  const;

public:
    // Public Matrix Cache Management
    void  UpdateProjectionMatrix()  const;
    void  UpdateInverseProjectionMatrix()  const;
    void  UpdateProjectionViewMatrix()  const;

protected:
    // Protected Matrix Cache Management
    void  InvalidProjectionMatrix()  const;
    virtual  void  InvalidMatrix()  const  override;

private:
    // Private Data Members
    float               mFov;
    float               mNear;
    float               mFar;
    float               mViewportWidth;
    float               mViewportHeight;

    float               mCachedHalfFov;
    float               mCachedViewportHalfWidth;
    float               mCachedViewportHalfHeight;
    float               mCachedViewportRatio;

    eProjectionMode     mProjectionMode;
    mutable glm::mat4   mCachedProjectionMatrix;
    mutable glm::mat4   mCachedInverseProjectionMatrix;
    mutable glm::mat4   mCachedProjectionViewMatrix;
    mutable bool        mProjectionMatrixInvalid;
    mutable bool        mInverseProjectionMatrixInvalid;
    mutable bool        mProjectionViewMatrixInvalid;
};

ULIS2_NAMESPACE_END

