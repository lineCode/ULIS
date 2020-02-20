// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Transform2D.h
* @author       Clement Berthaud
* @brief        This file provides the Transform2D class declaration.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Base/Core.h"
#include <glm/mat3x3.hpp>

ULIS2_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
// FTransform2D
ULIS2_API class FTransform2D
{
public:
    // Construction / Destruction
    FTransform2D();
    FTransform2D( const glm::mat3& iMat );

public:
    // Public API
    const std::string& ID() const; // Str From Blob
    const glm::mat3& Matrix() const;
    const glm::mat3& InverseMatrix() const;
    void DecomposeMatrix( float* iTx, float* iTy, float* iRotation, float* iScaleX, float* iScaleY, float* iSkewX, float* iSkewY ) const;

private:
    // Private API
    void UpdateID() const;
    void UpdateInverseMatrix() const;

private:
    // Private Data Members
    glm::mat3           mMatrix;
    mutable glm::mat3   mInverseMatrix;
    mutable std::string mID;
    mutable bool mDirtyID;
    mutable bool mDirtyInverseMatrix;
};

ULIS2_API glm::mat3 MakeIdentityMatrix();
ULIS2_API glm::mat3 MakeRotationMatrix( float iAngleRag );
ULIS2_API glm::mat3 MakeScaleMatrix( float iX, float iY );
ULIS2_API glm::mat3 MakeShearMatrix( float iX, float iY );
ULIS2_API glm::mat3 MakeTranslationMatrix( float iX, float iY );
ULIS2_API glm::mat3 ComposeMatrix( const glm::mat3& iA, const glm::mat3& iB );

ULIS2_NAMESPACE_END

