// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS3
*__________________
*
* @file         TransformBezier_Bilinear_MEM_Generic.ipp
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

ULIS3_NAMESPACE_BEGIN
template< typename T > void
InvokeTransformBezierMTProcessScanline_Bilinear_MEM_Generic( tByte* iDst, int32 iLine, std::shared_ptr< const FTransformArgs > iInfo, std::shared_ptr< const FBlock > iField, std::shared_ptr< const FBlock > iMask ) {
    const FTransformArgs&   info    = *iInfo;
    const FFormatInfo&      fmt     = info.destination->FormatInfo();
    tByte*                  dst     = iDst;
    const float*            field   = reinterpret_cast< const float* >( iField->ScanlinePtr( iLine ) );
    const uint8*            mask    = reinterpret_cast< const uint8* >( iMask->ScanlinePtr( iLine ) );
    const int rangex = info.src_roi.w - 1;
    const int rangey = info.src_roi.h - 1;

    tByte* c00 = new tByte[ fmt.BPP * 4 ];
    tByte* c10 = c00 + fmt.BPP;
    tByte* c11 = c10 + fmt.BPP;
    tByte* c01 = c11 + fmt.BPP;
    tByte* hh0 = new tByte[ fmt.BPP * 2 ];
    tByte* hh1 = hh0 + fmt.BPP;
    const int minx = info.src_roi.x;
    const int miny = info.src_roi.y;
    const int maxx = minx + info.src_roi.w;
    const int maxy = miny + info.src_roi.h;
    for( int x = 0; x < info.dst_roi.w; ++x ) {
        if( *mask & 0xFF ) {
            float srcxf = field[0] * rangex;
            float srcyf = field[1] * rangey;
            const int   left    = static_cast< int >( floor( srcxf ) );
            const int   top     = static_cast< int >( floor( srcyf ) );
            const int   right   = left + 1;
            const int   bot     = top + 1;
            const float tx      = srcxf - left;
            const float ux      = 1.f - tx;
            const float ty      = srcyf - top;
            const float uy      = 1.f - ty;

            #define TEMP( _C, _X, _Y ) if( _X >= minx && _Y >= miny && _X < maxx && _Y < maxy ) { memcpy( _C, info.source->PixelPtr( _X, _Y ), fmt.BPP ); } else { memset( _C, 255, fmt.BPP ); }
            TEMP( c00, left, top );
            TEMP( c10, right, top );
            TEMP( c11, right, bot );
            TEMP( c01, left, bot );
            #undef TEMP
            SampleBilinear< T >( hh0, c00, c10, fmt, tx, ux );
            SampleBilinear< T >( hh1, c01, c11, fmt, tx, ux );
            SampleBilinear< T >( dst, hh0, hh1, fmt, ty, uy );

        }
        dst += fmt.BPP;
        field += 2;
        ++mask;
    }

    delete [] c00;
    delete [] hh0;
}

template< typename T > void
TransformBezierMT_Bilinear_MEM_Generic( std::shared_ptr< const FTransformArgs > iInfo, std::shared_ptr< const FBlock > iField, std::shared_ptr< const FBlock > iMask ) {
    const FTransformArgs&   info        = *iInfo;
    tByte*                  dst         = info.destination->DataPtr();
    const tSize             dst_bps     = info.destination->BytesPerScanLine();
    const tSize             dst_decal_y = info.dst_roi.y;
    const tSize             dst_decal_x = info.dst_roi.x * info.destination->BytesPerPixel();
    ULIS3_MACRO_INLINE_PARALLEL_FOR( info.perfIntent, info.pool, info.blocking
                                   , info.dst_roi.h
                                   , InvokeTransformBezierMTProcessScanline_Bilinear_MEM_Generic< T >
                                   , dst + ( ( dst_decal_y + pLINE ) * dst_bps ) + dst_decal_x, pLINE, iInfo, iField, iMask );
}

ULIS3_NAMESPACE_END

