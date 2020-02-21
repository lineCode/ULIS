// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Blend.cpp
* @author       Clement Berthaud
* @brief        This file provides the definitions for the Blend entry point functions.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include "Blend/Blend.h"
#include "Base/CPU.h"
#include "Base/Perf.h"
#include "Data/Block.h"
#include "Maths/Geometry.h"
#include "Maths/Maths.h"
#include <glm/common.hpp>
// Distpach
#include "Blend/Dispatch/Dispatch.ipp"

ULIS2_NAMESPACE_BEGIN

void BlendRect( const FPerfInfo& iPerfParams, const FBlendInfo& iBlendParams ) {
    // Assertions
    ULIS2_ASSERT( iBlendParams.source,                                              "Bad source." );
    ULIS2_ASSERT( iBlendParams.backdrop,                                            "Bad destination." );
    ULIS2_ASSERT( iBlendParams.source->Format() == iBlendParams.backdrop->Format(), "Formats do not match." );
    ULIS2_ASSERT( !iPerfParams.intent.UseMT() || iPerfParams.pool,                  "Multithreading flag is specified but no thread pool is provided." );
    ULIS2_ASSERT( !iPerfParams.callCB || iPerfParams.blocking,                      "Callback flag is specified on non-blocking operation." );

    // Compute coordinates of target rect in destination, with source rect dimension
    FRect src_roi = iBlendParams.sourceRect & iBlendParams.source->Rect();
    int target_xmin, target_ymin, target_xmax, target_ymax;

    if( iBlendParams.subpixelFlag ) {
        target_xmin = static_cast< int >( FMaths::RoundToNegativeInfinity( iBlendParams.backdropPosition.x ) );
        target_ymin = static_cast< int >( FMaths::RoundToNegativeInfinity( iBlendParams.backdropPosition.y ) );
        target_xmax = static_cast< int >( FMaths::RoundToPositiveInfinity( iBlendParams.backdropPosition.x + src_roi.w ) );
        target_ymax = static_cast< int >( FMaths::RoundToPositiveInfinity( iBlendParams.backdropPosition.y + src_roi.h ) );
    } else {
        target_xmin = static_cast< int >( FMaths::RoundToNegativeInfinity( iBlendParams.backdropPosition.x ) );
        target_ymin = static_cast< int >( FMaths::RoundToNegativeInfinity( iBlendParams.backdropPosition.y ) );
        target_xmax = static_cast< int >( FMaths::RoundToNegativeInfinity( iBlendParams.backdropPosition.x + src_roi.w ) );
        target_ymax = static_cast< int >( FMaths::RoundToNegativeInfinity( iBlendParams.backdropPosition.y + src_roi.h ) );
    }

    // Ensure the selected target actually fits in destination
    FRect dst_target = FRect::FromMinMax( target_xmin, target_ymin, target_xmax, target_ymax );
    FRect dst_fit    = dst_target & iBlendParams.backdrop->Rect();

    // Check no-op
    if( dst_fit.Area() <= 0 )
        return;

    FVec2F      subpixelComponent   = FMaths::AbsFloatingPart( iBlendParams.backdropPosition );
    const int   translationX        = dst_fit.x - dst_target.x;
    const int   translationY        = dst_fit.y - dst_target.y;
    const int   coverageX           = src_roi.w - ( src_roi.x + translationX ) >= dst_fit.w ? dst_fit.w : static_cast< int >( dst_fit.w - ceil( subpixelComponent.x ) );
    const int   coverageY           = src_roi.h - ( src_roi.y + translationY ) >= dst_fit.h ? dst_fit.h : static_cast< int >( dst_fit.h - ceil( subpixelComponent.y ) );
    FVec2F      buspixelComponent;
    buspixelComponent.x = 1.f - subpixelComponent.x;
    buspixelComponent.y = 1.f - subpixelComponent.y;

    // Bake forward params.
    // Shared Ptr for thread safety and scope life time extension.
    // Use for non blocking multithreaded processing.
    std::shared_ptr< FBlendInfo > forwardBlendInfo = std::make_shared< FBlendInfo >( iBlendParams );
    FBlendInfo& _fbi = *forwardBlendInfo;
    _fbi.sourceRect             = src_roi;
    _fbi.backdropPosition       = subpixelComponent;
    _fbi.opacityValue           = FMaths::Clamp( iBlendParams.opacityValue, 0.f, 1.f );
    _fbi._shift                 = FVec2I( translationX, translationY );
    _fbi._backdropCoverage      = FVec2I( coverageX, coverageY );
    _fbi._backdropWorkingRect   = dst_fit;
    _fbi._buspixelComponent     = buspixelComponent;

    // Query dispatched method
    fpDispatchedBlendFunc fptr = QueryDispatchedBlendFunctionForParameters( iBlendParams.source->FormatInfo(), iPerfParams, _fbi );
    if( fptr ) fptr( forwardBlendInfo->source->FormatInfo(), iPerfParams, forwardBlendInfo );

    forwardBlendInfo->backdrop->Invalidate( forwardBlendInfo->_backdropWorkingRect, iPerfParams.callCB );
}

ULIS2_NAMESPACE_END

