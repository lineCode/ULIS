// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Transform.cpp
* @author       Clement Berthaud
* @brief        This file provides the definition for the transform entry point functions.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include "Transform/Transform.h"
#include "Data/Block.h"
// Dispatch
#include "Transform/Dispatch/Dispatch.ipp"

ULIS2_NAMESPACE_BEGIN

void Transform( const FTransformInfo& iTransformParams ) {
    // Assertions
    ULIS2_ASSERT( iTransformParams.source,                                                      "Bad source."                                                       );
    ULIS2_ASSERT( iTransformParams.destination,                                                 "Bad destination."                                                  );
    ULIS2_ASSERT( !iTransformParams.perfInfo.intent.UseMT() || iTransformParams.perfInfo.pool,  "Multithreading flag is specified but no thread pool is provided."  );
    ULIS2_ASSERT( !iTransformParams.perfInfo.callCB || iTransformParams.perfInfo.blocking,      "Callback flag is specified on non-blocking operation."             );
    ULIS2_ASSERT( iTransformParams.source->Format() == iTransformParams.destination->Format(),  "Formats do not match"                                              );
    ULIS2_ASSERT( iTransformParams.transform,                                                   "Not transform provided"                                            );
    ULIS2_WARNING( iTransformParams.source != iTransformParams.destination,                     "Copying a block on itself is dangerous."                           );
}

FRect TransformMetrics( const FTransformMetricsInfo& iTransformMetricsParams ) {
    ULIS2_ASSERT( iTransformMetricsParams.transform,                                            "Not transform provided"                                            );

    FRect transformed = iTransformMetricsParams.sourceRect.Transformed( *iTransformMetricsParams.transform );
    transformed.FitInPositiveRange();
}

ULIS2_NAMESPACE_END

