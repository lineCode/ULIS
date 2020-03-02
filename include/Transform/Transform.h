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
#include "Core/Core.h"
#include "Transform/Methods.h"
#include "Maths/Geometry.h"
#include <glm/mat3x3.hpp>

ULIS2_NAMESPACE_BEGIN
struct ULIS2_API FTransformInfo {
    const FBlock*       source;
    FBlock*             destination;
    const FTransform2D* transform;
    eResamplingMethod   interpolationType;
    FPerfInfo           perfInfo;
};


struct ULIS2_API FTransformMetricsInfo {
    FRect               sourceRect;
    const FTransform2D* transform;
    eResamplingMethod   interpolationType;
};

ULIS2_API void Transform( const FTransformInfo& );
ULIS2_API FRect TransformMetrics( const FTransformMetricsInfo& );

// Transform Typedefs ( implemented in dispatch.ipp but available from public API )
typedef void (*fpDispatchedTransformFunc)( FThreadPool*, bool, const FPerf&, const FBlock*, FBlock*, const glm::mat3& );
ULIS2_API fpDispatchedTransformFunc QueryDispatchedTransformFunctionForParameters( uint32 iFormat, eResamplingMethod iInterpolationType, const FPerf& iPerf, const FCPU& iCPU );

ULIS2_NAMESPACE_END

