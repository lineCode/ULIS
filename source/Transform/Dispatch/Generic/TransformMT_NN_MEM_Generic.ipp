// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         TransformMT_NearestNeighbour_MEM_Generic.ipp
* @author       Clement Berthaud
* @brief        This file provides the declaration for the generic transform entry point functions.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"
#include "Maths/Geometry.h"
#include "Transform/Dispatch/TransformInfo.h"
#include "Maths/Geometry.h"
#include "Thread/ThreadPool.h"

ULIS2_NAMESPACE_BEGIN
template< typename T > void
InvokeTransformMTProcessScanline_NN_MEM_Generic( tByte* iDst, int32 iLine, std::shared_ptr< const _FTransformInfoPrivate > iInfo ) {
    const _FTransformInfoPrivate&   info    = *iInfo;
    const FFormatInfo&              fmt     = info.destination->FormatInfo();
    tByte*                          dst     = iDst;

    const int maxx = info.source->Width();
    const int maxy = info.source->Height();
    for( int x = 0; x < info.dst_roi.w; ++x ) {
        glm::vec3 point_in_dst( x, iLine, 1.f );
        glm::vec2 point_in_src( info.inverseTransform * point_in_dst );
        int src_x = static_cast< int >( floor( point_in_src.x ) );
        int src_y = static_cast< int >( floor( point_in_src.y ) );
        if( src_x >= 0 && src_y >= 0 && src_x < maxx && src_y < maxy )
            memcpy( dst, info.source->PixelPtr( src_x, src_y ), fmt.BPP );
        dst += fmt.BPP;
    }
}

template< typename T > void
TransformMT_NN_MEM_Generic( std::shared_ptr< const _FTransformInfoPrivate > iInfo ) {
    const _FTransformInfoPrivate&   info        = *iInfo;
    tByte*                          dst         = info.destination->DataPtr();
    const tSize                     dst_bps     = info.destination->BytesPerScanLine();
    const tSize                     dst_decal_y = info.dst_roi.y;
    const tSize                     dst_decal_x = info.dst_roi.x * info.destination->BytesPerPixel();
    ULIS2_MACRO_INLINE_PARALLEL_FOR( info.perfIntent, info.pool, info.blocking
                                   , info.dst_roi.h
                                   , InvokeTransformMTProcessScanline_NN_MEM_Generic< T >
                                   , dst + ( ( dst_decal_y + pLINE ) * dst_bps ) + dst_decal_y, pLINE, iInfo );
}

ULIS2_NAMESPACE_END

