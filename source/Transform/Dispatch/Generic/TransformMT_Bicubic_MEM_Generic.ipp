// Copyright � 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         TransformMT_Bicubic_MEM_Generic.ipp
* @author       Clement Berthaud
* @brief        This file provides the declaration for the generic transform entry point functions.
* @copyright    Copyright � 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"
#include "Maths/Geometry.h"
#include "Transform/Dispatch/TransformInfo.h"

ULIS2_NAMESPACE_BEGIN

template< typename T > ULIS2_FORCEINLINE void
SampleBicubic( tByte* iDst, const tByte* iCA, const tByte* iCB, const FFormatInfo& iFMT, const float iT, const float iU ) {
    float alphaA, alphaB, alphaC;
    alphaA = alphaB = alphaC = 0.f;
    if( iFMT.HEA ) {
        alphaA = TYPE2FLOAT( iCA, iFMT.AID );
        alphaB = TYPE2FLOAT( iCB, iFMT.AID );
        alphaC = ( alphaA * iU + alphaB * iT );
        FLOAT2TYPE( iDst, iFMT.AID, alphaC );
    }
    for( int i = 0; i < iFMT.NCC; ++i ) {
        uint8 r = iFMT.IDT[i];
        *( reinterpret_cast< T* >( iDst ) + r ) = static_cast< T >( ( iCA[r] * alphaA * iU + iCB[r] * alphaB * iT ) / alphaC );
    }
}

template< typename T > void
InvokeTransformMTProcessScanline_Bicubic_MEM_Generic( tByte* iDst, int32 iLine, std::shared_ptr< const _FTransformInfoPrivate > iInfo ) {
    const _FTransformInfoPrivate&   info    = *iInfo;
    const FFormatInfo&              fmt     = info.destination->FormatInfo();
    tByte*                          dst     = iDst;

    glm::vec3 point_in_dst( info.dst_roi.x, info.dst_roi.y + iLine, 1.f );
    glm::vec2 point_in_src( info.inverseTransform * point_in_dst );
    glm::vec2 src_dx( info.inverseTransform * glm::vec3( 1.f, 0.f, 0.f ) );
    tByte* c00 = new tByte[ fmt.SPP * 4 ];
    tByte* c10 = c00 + fmt.SPP;
    tByte* c11 = c10 + fmt.SPP;
    tByte* c01 = c11 + fmt.SPP;
    tByte* hh0 = new tByte[ fmt.SPP * 2 ];
    tByte* hh1 = hh0 + fmt.SPP;

    const int minx = info.src_roi.x;
    const int miny = info.src_roi.y;
    const int maxx = minx + info.src_roi.w;
    const int maxy = miny + info.src_roi.h;
    for( int x = 0; x < info.dst_roi.w; ++x ) {
        const int   left    = static_cast< int >( floor( point_in_src.x ) );
        const int   top     = static_cast< int >( floor( point_in_src.y ) );
        const int   right   = left + 1;
        const int   bot     = top + 1;
        const float tx      = point_in_src.x - left;
        const float ux      = 1.f - tx;
        const float ty      = point_in_src.y - top;
        const float uy      = 1.f - ty;

        #define TEMP( _C, _X, _Y ) if( _X >= minx && _Y >= miny && _X < maxx && _Y < maxy ) { memcpy( _C, info.source->PixelPtr( _X, _Y ), fmt.BPP ); } else { memset( _C, 0, fmt.BPP ); }
        TEMP( c00, left, top );
        TEMP( c10, right, top );
        TEMP( c11, right, bot );
        TEMP( c01, left, bot );
        #undef TEMP
        SampleBicubic< T >( hh0, c00, c10, fmt, tx, ux );
        SampleBicubic< T >( hh1, c01, c11, fmt, tx, ux );
        SampleBicubic< T >( dst, hh0, hh1, fmt, ty, uy );

        dst += fmt.BPP;
        point_in_src += src_dx;
    }

    delete [] c00;
    delete [] hh0;
}

template< typename T > void
TransformMT_Bicubic_MEM_Generic( std::shared_ptr< const _FTransformInfoPrivate > iInfo ) {
    const _FTransformInfoPrivate&   info        = *iInfo;
    tByte*                          dst         = info.destination->DataPtr();
    const tSize                     dst_bps     = info.destination->BytesPerScanLine();
    const tSize                     dst_decal_y = info.dst_roi.y;
    const tSize                     dst_decal_x = info.dst_roi.x * info.destination->BytesPerPixel();
    ULIS2_MACRO_INLINE_PARALLEL_FOR( info.perfIntent, info.pool, info.blocking
                                   , info.dst_roi.h
                                   , InvokeTransformMTProcessScanline_Bicubic_MEM_Generic< T >
                                   , dst + ( ( dst_decal_y + pLINE ) * dst_bps ) + dst_decal_x, pLINE, iInfo );
}


ULIS2_NAMESPACE_END

