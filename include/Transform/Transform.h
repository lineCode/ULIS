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

ULIS2_NAMESPACE_BEGIN
ULIS2_API void Transform( FThreadPool*              iThreadPool
                        , bool                      iBlocking
                        , uint32                    iPerfIntent
                        , const FHostDeviceInfo&    iHostDeviceInfo
                        , bool                      iCallCB
                        , const FBlock*             iSource
                        , FBlock*                   iDestination
                        , const FRect&              iSourceRect
                        , const FTransform2D&       iTransform
                        , eResamplingMethod         iMethod );

ULIS2_API FRect TransformMetrics( const FRect&          iSourceRect
                                , const FTransform2D&   iTransform
                                , eResamplingMethod     iMethod );

ULIS2_NAMESPACE_END

