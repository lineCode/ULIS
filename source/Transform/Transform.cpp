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
#include "Base/HostDeviceInfo.h"
#include "Data/Block.h"
#include "Maths/Geometry.h"
#include "Maths/Maths.h"
#include "Maths/Transform2D.h"
#include "Transform/Dispatch/TransformInfo.h"
#include "Transform/Dispatch/Dispatch.ipp"

#include <glm/matrix.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>
#include <glm/ext/matrix_transform.hpp>

ULIS2_NAMESPACE_BEGIN
void TransformAffine( FThreadPool*            iThreadPool
                    , bool                    iBlocking
                    , uint32                  iPerfIntent
                    , const FHostDeviceInfo&  iHostDeviceInfo
                    , bool                    iCallCB
                    , const FBlock*           iSource
                    , FBlock*                 iDestination
                    , const FRect&            iSourceRect
                    , const FTransform2D&     iTransform
                    , eResamplingMethod       iMethod )
{
    // Assertions
    ULIS2_ASSERT( iSource,                                      "Bad source."                                           );
    ULIS2_ASSERT( iDestination,                                 "Bad destination."                                      );
    ULIS2_ASSERT( iSource->Format() == iDestination->Format(),  "Formats do not match."                                 );
    ULIS2_ASSERT( iThreadPool,                                  "Bad pool."                                             );
    ULIS2_ASSERT( !iCallCB || iBlocking,                        "Callback flag is specified on non-blocking operation." );

    FRect src_fit = iSourceRect & iSource->Rect();
    FRect trans = TransformAffineMetrics( src_fit, iTransform, iMethod );
    FRect dst_fit = trans & iDestination->Rect();

    if( !dst_fit.Area() )
        return;

    std::shared_ptr< _FTransformInfoPrivate > forwardTransformParams = std::make_shared< _FTransformInfoPrivate >();
    _FTransformInfoPrivate& alias = *forwardTransformParams;
    alias.pool              = iThreadPool;
    alias.blocking          = iBlocking;
    alias.hostDeviceInfo    = &iHostDeviceInfo;
    alias.perfIntent        = iPerfIntent;
    alias.source            = iSource;
    alias.destination       = iDestination;
    alias.src_roi           = src_fit;
    alias.dst_roi           = dst_fit;
    alias.method            = iMethod;
    alias.inverseTransform  = glm::inverse( iTransform.Matrix() );

    // Query dispatched method
    fpDispatchedTransformFunc fptr = QueryDispatchedTransformAffineFunctionForParameters( alias );
    ULIS2_ASSERT( fptr, "No dispatch function found." );
    fptr( forwardTransformParams );

    // Invalid
    iDestination->Invalidate( dst_fit, iCallCB );
}

FRect TransformAffineMetrics( const FRect&          iSourceRect
                            , const FTransform2D&   iTransform
                            , eResamplingMethod     iMethod )
{
    FRect trans = iSourceRect.Transformed( iTransform );
    if( iMethod > INTERP_NN ) {
        float tx, ty, r, sx, sy, skx, sky;
        DecomposeMatrix( iTransform.Matrix(), &tx, &ty, &r, &sx, &sy, &skx, &sky );
        trans.x -= static_cast< int >( ceil( sx ) );
        trans.y -= static_cast< int >( ceil( sy ) );
        trans.w += static_cast< int >( ceil( sx ) );
        trans.h += static_cast< int >( ceil( sy ) );
    }
    return  trans;
}

ULIS2_NAMESPACE_END

