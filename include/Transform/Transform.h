// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS
*__________________
*
* @file         Transform.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the transform entry point functions.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"
#include "Transform/Methods.h"
#include "Math/Interpolation/Bezier.h"
#include <vector>

ULIS_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
// TransformAffine
ULIS_API void TransformAffine( FThreadPool*              iThreadPool
                              , bool                      iBlocking
                              , uint32                    iPerfIntent
                              , const FHostDeviceInfo&    iHostDeviceInfo
                              , bool                      iCallCB
                              , const FBlock*             iSource
                              , FBlock*                   iDestination
                              , const FRectI&              iSourceRect
                              , const FTransformation2D&       iTransform
                              , eResamplingMethod         iMethod );

/////////////////////////////////////////////////////
// TransformAffineTiled
ULIS_API void TransformAffineTiled( FThreadPool*              iThreadPool
                                   , bool                      iBlocking
                                   , uint32                    iPerfIntent
                                   , const FHostDeviceInfo&    iHostDeviceInfo
                                   , bool                      iCallCB
                                   , const FBlock*             iSource
                                   , FBlock*                   iDestination
                                   , const FRectI&              iSourceRect
                                   , const FRectI&              iDestRect
                                   , const FTransformation2D&       iTransform
                                   , eResamplingMethod         iMethod );

/////////////////////////////////////////////////////
// TransformPerspective
ULIS_API void TransformPerspective( FThreadPool*              iThreadPool
                                   , bool                      iBlocking
                                   , uint32                    iPerfIntent
                                   , const FHostDeviceInfo&    iHostDeviceInfo
                                   , bool                      iCallCB
                                   , const FBlock*             iSource
                                   , FBlock*                   iDestination
                                   , const FRectI&              iSourceRect
                                   , const FTransformation2D&       iTransform
                                   , eResamplingMethod         iMethod );

/////////////////////////////////////////////////////
// TransformBezier
ULIS_API void TransformBezier( FThreadPool*                                    iThreadPool
                              , bool                                            iBlocking
                              , uint32                                          iPerfIntent
                              , const FHostDeviceInfo&                          iHostDeviceInfo
                              , bool                                            iCallCB
                              , const FBlock*                                   iSource
                              , FBlock*                                         iDestination
                              , const FRectI&                                    iSourceRect
                              , const std::vector< FCubicBezierControlPoint >&  iControlPoints
                              , float                                           iThreshold
                              , int                                             iPlotSize
                              , eResamplingMethod                               iMethod );

/////////////////////////////////////////////////////
// Resize
ULIS_API void Resize( FThreadPool*             iThreadPool
                     , bool                     iBlocking
                     , uint32                   iPerfIntent
                     , const FHostDeviceInfo&   iHostDeviceInfo
                     , bool                     iCallCB
                     , const FBlock*            iSource
                     , FBlock*                  iDestination
                     , const FRectI&             iSourceRect
                     , const FVec2F&            iSize
                     , const FVec2F&            iPos
                     , eResamplingMethod        iMethod );

/////////////////////////////////////////////////////
// XResize
ULIS_API FBlock* XResize( FThreadPool*             iThreadPool
                         , bool                     iBlocking
                         , uint32                   iPerfIntent
                         , const FHostDeviceInfo&   iHostDeviceInfo
                         , bool                     iCallCB
                         , const FBlock*            iSource
                         , const FRectI&             iSourceRect
                         , const FVec2F&            iSize
                         , eResamplingMethod        iMethod );

/////////////////////////////////////////////////////
// XTransformAffine
ULIS_API FBlock* XTransformAffine( FThreadPool*            iThreadPool
                                  , bool                    iBlocking
                                  , uint32                  iPerfIntent
                                  , const FHostDeviceInfo&  iHostDeviceInfo
                                  , bool                    iCallCB
                                  , const FBlock*           iSource
                                  , const FRectI&            iSourceRect
                                  , const FTransformation2D&     iTransform
                                  , eResamplingMethod       iMethod );

/////////////////////////////////////////////////////
// XTransformAffineTiled
ULIS_API FBlock* XTransformAffineTiled( FThreadPool*              iThreadPool
                                       , bool                      iBlocking
                                       , uint32                    iPerfIntent
                                       , const FHostDeviceInfo&    iHostDeviceInfo
                                       , bool                      iCallCB
                                       , const FBlock*             iSource
                                       , const FRectI&              iSourceRect
                                       , const FRectI&              iDestRect
                                       , const FTransformation2D&       iTransform
                                       , eResamplingMethod         iMethod );

/////////////////////////////////////////////////////
// XMakeTileableTransformedPattern
ULIS_API FBlock* XMakeTileableTransformedPattern( FThreadPool*              iThreadPool
                                                 , bool                      iBlocking
                                                 , uint32                    iPerfIntent
                                                 , const FHostDeviceInfo&    iHostDeviceInfo
                                                 , bool                      iCallCB
                                                 , const FBlock*             iSource
                                                 , const FRectI&              iSourceRect
                                                 , const FTransformation2D&       iTransform
                                                 , eResamplingMethod         iMethod );

/////////////////////////////////////////////////////
// XTransformPerspective
ULIS_API FBlock* XTransformPerspective( FThreadPool*                   iThreadPool
                                       , bool                           iBlocking
                                       , uint32                         iPerfIntent
                                       , const FHostDeviceInfo&         iHostDeviceInfo
                                       , bool                           iCallCB
                                       , const FBlock*                  iSource
                                       , const FRectI&                   iSourceRect
                                       , const std::vector< FVec2F >&   iDestinationPoints
                                       , eResamplingMethod              iMethod );

/////////////////////////////////////////////////////
// TransformAffineMetrics
ULIS_API FRectI TransformAffineMetrics( const FRectI&          iSourceRect
                                      , const FTransformation2D&   iTransform
                                      , eResamplingMethod     iMethod );

/////////////////////////////////////////////////////
// TransformPerspectiveMetrics
ULIS_API FRectI TransformPerspectiveMetrics( const FRectI&          iSourceRect
                                           , const FTransformation2D&   iTransform
                                           , eResamplingMethod     iMethod );

/////////////////////////////////////////////////////
// TransformBezierMetrics
ULIS_API FRectI TransformBezierMetrics( const FRectI&                                    iSourceRect
                                      , const std::vector< FCubicBezierControlPoint >&  iControlPoints
                                      , eResamplingMethod                               iMethod );

ULIS_NAMESPACE_END

