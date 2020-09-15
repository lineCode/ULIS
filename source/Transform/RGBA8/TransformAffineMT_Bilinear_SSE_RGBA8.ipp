// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS3
*__________________
*
* @file         TransformAffineMT_Bilinear_SSE_RGBA8.ipp
* @author       Clement Berthaud
* @brief        This file provides the implementation for a Transform specialization as described in the title.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"
#include "Data/Block.h"
#include "Maths/Geometry.h"
#include "Transform/TransformArgs.h"
#include "Transform/TransformHelpers.h"
#include "Thread/ThreadPool.h"
#include <vectorclass.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

ULIS3_NAMESPACE_BEGIN
void
InvokeTransformAffineMTProcessScanline_Bilinear_SSE_RGBA8( tByte* iDst, int32 iLine, std::shared_ptr< const FTransformArgs > iInfo, const Vec4i iIDT ) {
    const FTransformArgs&   info    = *iInfo;
    const FFormatInfo&      fmt     = info.destination->FormatInfo();
    tByte*                  dst     = iDst;

    glm::vec3 point_in_dst( info.dst_roi.x, info.dst_roi.y + iLine, 1.f );
    glm::vec2 point_in_src( info.inverseTransform * point_in_dst );
    glm::vec2 src_dx( info.inverseTransform * glm::vec3( 1.f, 0.f, 0.f ) );

    Vec4f c00, c10, c11, c01, hh0, hh1, res, alp;

    const int minx = info.src_roi.x;
    const int miny = info.src_roi.y;
    const int maxx = minx + info.src_roi.w;
    const int maxy = miny + info.src_roi.h;
    for( int x = 0; x < info.dst_roi.w; ++x ) {
        const int   left    = static_cast< int >( floor( point_in_src.x ) );
        const int   top     = static_cast< int >( floor( point_in_src.y ) );
        const int   right   = left + 1;
        const int   bot     = top + 1;
        const Vec4f tx      = point_in_src.x - left;
        const Vec4f ux      = 1.f - tx;
        const Vec4f ty      = point_in_src.y - top;
        const Vec4f uy      = 1.f - ty;

        #define LOAD( X )   _mm_cvtepi32_ps( _mm_cvtepu8_epi32( _mm_loadu_si128( reinterpret_cast< const __m128i* >( X ) ) ) )
        #define TEMP( _C, _X, _Y )                                                                                                                          \
            if( _X >= minx && _Y >= miny && _X < maxx && _Y < maxy ) {                                                                                      \
                const tByte* pptr = info.source->PixelPtr( _X, _Y );                                                                                        \
                Vec4f _ch = LOAD( pptr );                                                                                                                   \
                Vec4f _al = _mm_set_ps1( pptr[ fmt.AID ] );                                                                                                 \
                _C = lookup8( iIDT, ( _ch * _al ) / 255.f, _al );                                                                                           \
            } else {                                                                                                                                        \
                _C = _mm_setzero_ps();                                                                                                                      \
            }

        TEMP( c00, left, top );
        TEMP( c10, right, top );
        TEMP( c11, right, bot );
        TEMP( c01, left, bot );
        #undef TEMP
        #undef LOAD
        hh0 = c00 * ux + c10 * tx;
        hh1 = c01 * ux + c11 * tx;
        res = hh0 * uy + hh1 * ty;
        alp = lookup4( fmt.AID, res );
        alp.insert( fmt.AID, 255.f );
        res = ( res * 255.f ) / alp;

        auto _pack = _mm_cvtps_epi32( res );
        _pack = _mm_packus_epi32( _pack, _pack );
        _pack = _mm_packus_epi16( _pack, _pack );
        *( uint32* )dst = static_cast< uint32 >( _mm_cvtsi128_si32( _pack ) );

        dst += fmt.BPP;
        point_in_src += src_dx;
    }
}

void
TransformAffineMT_Bilinear_SSE_RGBA8( std::shared_ptr< const FTransformArgs > iInfo ) {
    const FTransformArgs&   info        = *iInfo;
    tByte*                  dst         = info.destination->DataPtr();
    const tSize             dst_bps     = info.destination->BytesPerScanLine();
    const tSize             dst_decal_y = info.dst_roi.y;
    const tSize             dst_decal_x = info.dst_roi.x * info.destination->BytesPerPixel();
    Vec4i idt( 0, 1, 2, 3 );
    idt.insert( info.source->FormatInfo().AID, 4 );
    ULIS3_MACRO_INLINE_PARALLEL_FOR( info.perfIntent, info.pool, info.blocking
                                   , info.dst_roi.h
                                   , InvokeTransformAffineMTProcessScanline_Bilinear_SSE_RGBA8
                                   , dst + ( ( dst_decal_y + pLINE ) * dst_bps ) + dst_decal_x, pLINE, iInfo, idt );
}

ULIS3_NAMESPACE_END

