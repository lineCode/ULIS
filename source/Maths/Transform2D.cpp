// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Transform2D.cpp
* @author       Clement Berthaud
* @brief        This file provides the Transform2D class definition.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include "Maths/Transform2D.h"
#include "Maths/Maths.h"
#include <glm/gtx/matrix_transform_2d.hpp>
#include <glm/mat2x2.hpp>
#include <glm/vec2.hpp>

ULIS2_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
// FTransform2D
//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------- Construction / Destruction
FTransform2D::FTransform2D()
    : mMatrix( 1.f )
{
}

ULIS2_NAMESPACE_END

