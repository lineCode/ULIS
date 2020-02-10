// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Transform.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the transform entry point functions.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Base/Core.h"
#include "Transform/Methods.h"
#include <glm/mat3x3.hpp>

ULIS2_NAMESPACE_BEGIN
ULIS2_API void Transform( FThreadPool*      iPool
                        , bool              iBlocking
                        , const FPerf&      iPerf
                        , const FCPU&       iCPU
                        , const FBlock*     iSrc
                        , FBlock*           iDst
                        , const  glm::mat3& iMat
                        , eResamplingMethod iInterpolationType
                        , bool              iCallInvalidCB );

// Transform Typedefs ( implemented in dispatch.ipp but available from public API )
typedef void (*fpDispatchedTransformFunc)( FThreadPool*, bool, const FPerf&, const FBlock*, FBlock*, const glm::mat3& );
ULIS2_API fpDispatchedTransformFunc QueryDispatchedTransformFunctionForParameters( uint32 iFormat, eResamplingMethod iInterpolationType, const FPerf& iPerf, const FCPU& iCPU );

ULIS2_NAMESPACE_END

