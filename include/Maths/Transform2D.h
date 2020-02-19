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

    std::string ID() const; // Str From Blob

private:
    // Private Data Members
    glm::mat3 mMatrix;
};

ULIS2_API glm::mat3 MakeIdentityMatrix();
ULIS2_API glm::mat3 MakeRotationMatrix( float iAngleRag );
ULIS2_API glm::mat3 MakeScaleMatrix( float iX, float iY );
ULIS2_API glm::mat3 MakeShearMatrix( float iX, float iY );
ULIS2_API glm::mat3 MakeTranslationMatrix( float iX, float iY );
ULIS2_API glm::mat3 ComposeMatrix( const glm::mat3& iA, const glm::mat3& iB );

ULIS2_NAMESPACE_END

