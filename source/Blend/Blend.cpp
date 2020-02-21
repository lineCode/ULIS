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
void
Blend( FThreadPool*         iPool
     , bool                 iBlocking
     , const FPerf&         iPerf
     , const FCPU&          iCPU
     , bool                 iSubpixel
     , const FBlock*        iSource
     , FBlock*              iBackdrop
     , float                iDstX
     , float                iDstY
     , eBlendingMode        iBlendingMode
     , eAlphaMode           iAlphaMode
     , float                iOpacity
     , bool                 iCallInvalidCB )
{
    BlendRect( iPool
             , iBlocking
             , iPerf
             , iCPU
             , iSubpixel
             , iSource
             , iBackdrop
             , iSource->Rect()
             , 0
             , 0
             , iDstX
             , iDstY
             , iSource->Width()
             , iSource->Height()
             , iBlendingMode
             , iAlphaMode
             , iOpacity
             , iCallInvalidCB );
}


void
BlendRect( FThreadPool*         iPool
         , bool                 iBlocking
         , const FPerf&         iPerf
         , const FCPU&          iCPU
         , bool                 iSubpixel
         , const FBlock*        iSource
         , FBlock*              iBackdrop
         , const FRect&         iSrcRect
         , int32                iSrcShiftX
         , int32                iSrcShiftY
         , float                iDstX
         , float                iDstY
         , int32                iDstCoverageW
         , int32                iDstCoverageH
         , eBlendingMode        iBlendingMode
         , eAlphaMode           iAlphaMode
         , float                iOpacity
         , bool                 iCallInvalidCB )
{
    ULIS2_ASSERT( iPool,                                    "Bad pool" );
    ULIS2_ASSERT( iSource,                                  "Bad source" );
    ULIS2_ASSERT( iBackdrop,                                "Bad destination" );
    ULIS2_ASSERT( iSource->Format() == iBackdrop->Format(), "Formats do not match" );
    ULIS2_ASSERT( !( (!iBlocking) && ( iCallInvalidCB ) ),  "Calling invalid CB on non-blocking operation may induce race condition and undefined behaviours." );
    ULIS2_WARNING( iSource != iBackdrop,                    "Blending a block on itself may trigger data race, use at your own risk or ensure written areas do not overlap." );
    // Ensure the selected source rect actually fits in source dimensions.
    FRect src_roi = iSrcRect & iSource->Rect();
    // Compute coordinates of target rect in destination, with source rect dimension
    int target_xmin = iSubpixel ? static_cast< int >( FMaths::RoundToNegativeInfinity( iDstX ) )                    : static_cast< int >( FMaths::RoundToNegativeInfinity( iDstX ) );
    int target_ymin = iSubpixel ? static_cast< int >( FMaths::RoundToNegativeInfinity( iDstY ) )                    : static_cast< int >( FMaths::RoundToNegativeInfinity( iDstY ) );
    int target_xmax = iSubpixel ? static_cast< int >( FMaths::RoundToPositiveInfinity( iDstX + iDstCoverageW ) )    : static_cast< int >( FMaths::RoundToNegativeInfinity( iDstX + iDstCoverageW ) );
    int target_ymax = iSubpixel ? static_cast< int >( FMaths::RoundToPositiveInfinity( iDstY + iDstCoverageH ) )    : static_cast< int >( FMaths::RoundToNegativeInfinity( iDstY + iDstCoverageH ) );
    FRect dst_target = FRect::FromMinMax( target_xmin, target_ymin, target_xmax, target_ymax );

    // Ensure the selected target actually fits in destination
    FRect dst_fit = dst_target & iBackdrop->Rect();

    if( dst_fit.Area() <= 0 ) return;
    src_roi.x -= dst_target.x - dst_fit.x;
    src_roi.y -= dst_target.y - dst_fit.y;
    float       opacity = FMaths::Clamp( iOpacity, 0.f, 1.f );
    glm::vec2   subpixel_component = glm::abs( FMaths::FloatingPart( glm::vec2( iDstX, iDstY ) ) );

    int srcshiftx = -iSrcShiftX;
    int srcshifty = -iSrcShiftY;
    while( srcshiftx < 0 ) srcshiftx+=src_roi.w;
    while( srcshifty < 0 ) srcshifty+=src_roi.h;
    /*
    fpDispatchedBlendFunc fptr = QueryDispatchedBlendFunctionForParameters( iSource->Format(), iBlendingMode, iAlphaMode, iSubpixel, iPerf, iCPU );
    if( fptr ) fptr( iPool, iBlocking, iPerf, iSource, iBackdrop, src_roi, dst_fit, glm::ivec2( srcshiftx, srcshifty ), subpixel_component, iBlendingMode, iAlphaMode, opacity );
    iBackdrop->Invalidate( dst_fit, iCallInvalidCB );
    */
}

void BlendRect( const FPerfInfo& iPerfParams, const FBlendInfo& iBlendParams ) {
    // Assertions
    ULIS2_ASSERT( iBlendParams.source,                                              "Bad source." );
    ULIS2_ASSERT( iBlendParams.backdrop,                                            "Bad destination." );
    ULIS2_ASSERT( iBlendParams.source->Format() == iBlendParams.backdrop->Format(), "Formats do not match." );
    ULIS2_ASSERT( !iPerfParams.intent.UseMT() || iPerfParams.pool,                  "Multithreading flag is specified but no thread pool is provided." );
    ULIS2_ASSERT( !iPerfParams.callCB || iPerfParams.blocking,                      "Callback flag is specified on non-blocking operation." );

    // Compute coordinates of target rect in destination, with source rect dimension
    FRect src_roi = iBlendParams.sourceRect & iBlendParams.source->Rect();
    FVec2I dstCoverage = FMaths::Max( iBlendParams.backdropCoverage, 0 );
    int target_xmin, target_ymin, target_xmax, target_ymax;

    if( iBlendParams.subpixelFlag ) {
        target_xmin = static_cast< int >( FMaths::RoundToNegativeInfinity( iBlendParams.backdropPosition.x ) );
        target_ymin = static_cast< int >( FMaths::RoundToNegativeInfinity( iBlendParams.backdropPosition.y ) );
        target_xmax = static_cast< int >( FMaths::RoundToPositiveInfinity( iBlendParams.backdropPosition.x + dstCoverage.x ) );
        target_ymax = static_cast< int >( FMaths::RoundToPositiveInfinity( iBlendParams.backdropPosition.y + dstCoverage.y ) );
    } else {
        target_xmin = static_cast< int >( FMaths::RoundToNegativeInfinity( iBlendParams.backdropPosition.x ) );
        target_ymin = static_cast< int >( FMaths::RoundToNegativeInfinity( iBlendParams.backdropPosition.y ) );
        target_xmax = static_cast< int >( FMaths::RoundToNegativeInfinity( iBlendParams.backdropPosition.x + dstCoverage.x ) );
        target_ymax = static_cast< int >( FMaths::RoundToNegativeInfinity( iBlendParams.backdropPosition.y + dstCoverage.y ) );
    }

    // Ensure the selected target actually fits in destination
    FRect dst_target = FRect::FromMinMax( target_xmin, target_ymin, target_xmax, target_ymax );
    FRect dst_fit    = dst_target & iBlendParams.backdrop->Rect();

    // Check no-op
    if( dst_fit.Area() <= 0 )
        return;

    FVec2F      subpixelComponent   = FMaths::AbsFloatingPart( iBlendParams.backdropPosition );
    const int   coverageX           = src_roi.w - src_roi.x >= dst_fit.w ? dst_fit.w : static_cast< int >( dst_fit.w - ceil( subpixelComponent.x ) );
    const int   coverageY           = src_roi.h - src_roi.y >= dst_fit.h ? dst_fit.h : static_cast< int >( dst_fit.h - ceil( subpixelComponent.y ) );
    const int   translationX        = FMaths::PyModulo( iBlendParams.tilingTranslation.x - ( dst_target.x - dst_fit.x ), src_roi.w );
    const int   translationY        = FMaths::PyModulo( iBlendParams.tilingTranslation.y - ( dst_target.y - dst_fit.y ), src_roi.h );

    // Bake forward params.
    // Shared Ptr for thread safety and scope life time extension.
    // Use for non blocking multithreaded processing.
    std::shared_ptr< FBlendInfo > forwardBlendInfo = std::make_shared< FBlendInfo >( iBlendParams );
    forwardBlendInfo->sourceRect            = src_roi;
    forwardBlendInfo->tilingTranslation     = FVec2I( translationX, translationY );
    forwardBlendInfo->backdropPosition      = subpixelComponent;
    forwardBlendInfo->backdropCoverage      = FVec2I( coverageX, coverageY );
    forwardBlendInfo->opacityValue          = FMaths::Clamp( iBlendParams.opacityValue, 0.f, 1.f );
    forwardBlendInfo->_backdropWorkingRect  = dst_fit;

    // Query dispatched method
    fpDispatchedBlendFunc fptr = QueryDispatchedBlendFunctionForParameters( iBlendParams.source->FormatInfo(), iPerfParams, *forwardBlendInfo );
    if( fptr ) fptr( forwardBlendInfo->source->FormatInfo(), iPerfParams, forwardBlendInfo );

    forwardBlendInfo->backdrop->Invalidate( forwardBlendInfo->_backdropWorkingRect, iPerfParams.callCB );
}

ULIS2_NAMESPACE_END

