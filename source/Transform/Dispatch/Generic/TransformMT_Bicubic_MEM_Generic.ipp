// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         TransformMT_Bicubic_MEM_Generic.ipp
* @author       Clement Berthaud
* @brief        This file provides the declaration for the generic transform entry point functions.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"
#include "Maths/Geometry.h"
#include "Transform/Dispatch/TransformInfo.h"

ULIS2_NAMESPACE_BEGIN
float InterpCubic( float iA, float iB, float iC, float iD, float iT ) {
    float a = -iA / 2.0f + (3.0f*iB) / 2.0f - (3.0f*iC) / 2.0f + iD / 2.0f;
    float b = iA - (5.0f*iB) / 2.0f + 2.0f*iC - iD / 2.0f;
    float c = -iA / 2.0f + iC / 2.0f;
    float d = iB;
 
    return a*iT*iT*iT + b*iT*iT + c*iT + d;
}

template< typename T > ULIS2_FORCEINLINE void
SampleBicubicH( float* iDst, const tByte* iA, const tByte* iB, const tByte* iC, const tByte* iD, const FFormatInfo& iFMT, const float iT ) {
    float alphaA, alphaB, alphaC, alphaD, alphaR;
    alphaA = alphaB = alphaC = alphaD = alphaR = 1.f;
    if( iFMT.HEA ) {
        alphaA = TYPE2FLOAT( iA, iFMT.AID );
        alphaB = TYPE2FLOAT( iB, iFMT.AID );
        alphaC = TYPE2FLOAT( iC, iFMT.AID );
        alphaD = TYPE2FLOAT( iD, iFMT.AID );
        alphaR = InterpCubic( alphaA, alphaB, alphaC, alphaD, iT );
        iDst[iFMT.AID] = alphaR;
        alphaR = alphaR == 0.f ? 0.f : 1.f / alphaR;
    }
    for( int i = 0; i < iFMT.NCC; ++i ) {
        uint8 r = iFMT.IDT[i];
        iDst[r] = InterpCubic( iA[r] * alphaA, iB[r] * alphaB, iC[r] * alphaC, iD[r] * alphaD, iT ) * alphaR;
    }
}

template< typename T > ULIS2_FORCEINLINE void
SampleBicubicV( tByte* iDst, const float* iA, const float* iB, const float* iC, const float* iD, const FFormatInfo& iFMT, const float iT ) {
    float alphaA, alphaB, alphaC, alphaD, alphaR;
    alphaA = alphaB = alphaC = alphaD = alphaR = 1.f;
    if( iFMT.HEA ) {
        alphaA = iA[iFMT.AID];
        alphaB = iB[iFMT.AID];
        alphaC = iC[iFMT.AID];
        alphaD = iD[iFMT.AID];
        alphaR = InterpCubic( alphaA, alphaB, alphaC, alphaD, iT );
        FLOAT2TYPE( iDst, iFMT.AID, FMaths::Clamp( alphaR, 0.f, 1.f ) );
        alphaR = alphaR == 0.f ? 0.f : 1.f / alphaR;
    }
    for( int i = 0; i < iFMT.NCC; ++i ) {
        uint8 r = iFMT.IDT[i];
        *( reinterpret_cast< T* >( iDst ) + r ) = FMaths::Clamp( static_cast< T >( InterpCubic( iA[r] * alphaA, iB[r] * alphaB, iC[r] * alphaC, iD[r] * alphaD, iT ) * alphaR ), MinType< T >(), MaxType< T >() );
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

    tByte* p00 = new tByte[ fmt.SPP * 4 ];      tByte* p01 = new tByte[ fmt.SPP * 4 ];
    tByte* p10 = p00 + fmt.SPP;                 tByte* p11 = p01 + fmt.SPP;
    tByte* p20 = p10 + fmt.SPP;                 tByte* p21 = p11 + fmt.SPP;
    tByte* p30 = p20 + fmt.SPP;                 tByte* p31 = p21 + fmt.SPP;
    tByte* p02 = new tByte[ fmt.SPP * 4 ];      tByte* p03 = new tByte[ fmt.SPP * 4 ];
    tByte* p12 = p02 + fmt.SPP;                 tByte* p13 = p03 + fmt.SPP;
    tByte* p22 = p12 + fmt.SPP;                 tByte* p23 = p13 + fmt.SPP;
    tByte* p32 = p22 + fmt.SPP;                 tByte* p33 = p23 + fmt.SPP;
    float* hh0 = new float[ fmt.SPP * 4 ];
    float* hh1 = new float[ fmt.SPP * 4 ];
    float* hh2 = new float[ fmt.SPP * 4 ];
    float* hh3 = new float[ fmt.SPP * 4 ];

    const int minx = info.src_roi.x;
    const int miny = info.src_roi.y;
    const int maxx = minx + info.src_roi.w;
    const int maxy = miny + info.src_roi.h;
    for( int x = 0; x < info.dst_roi.w; ++x ) {
        const int   src_x   = static_cast< int >( floor( point_in_src.x ) );
        const int   src_y   = static_cast< int >( floor( point_in_src.y ) );
        const float tx      = point_in_src.x - src_x;
        const float ty      = point_in_src.y - src_y;

        #define GETPIXEL( _C, _X, _Y ) if( _X >= minx && _Y >= miny && _X < maxx && _Y < maxy ) { memcpy( _C, info.source->PixelPtr( _X, _Y ), fmt.BPP ); } else { memset( _C, 0, fmt.BPP ); }
        GETPIXEL( p00, src_x - 1, src_y - 1 );  GETPIXEL( p01, src_x - 1, src_y + 0 );  GETPIXEL( p02, src_x - 1, src_y + 1 );  GETPIXEL( p03, src_x - 1, src_y + 2 );
        GETPIXEL( p10, src_x + 0, src_y - 1 );  GETPIXEL( p11, src_x + 0, src_y + 0 );  GETPIXEL( p12, src_x + 0, src_y + 1 );  GETPIXEL( p13, src_x + 0, src_y + 2 );
        GETPIXEL( p20, src_x + 1, src_y - 1 );  GETPIXEL( p21, src_x + 1, src_y + 0 );  GETPIXEL( p22, src_x + 1, src_y + 1 );  GETPIXEL( p23, src_x + 1, src_y + 2 );
        GETPIXEL( p30, src_x + 2, src_y - 1 );  GETPIXEL( p31, src_x + 2, src_y + 0 );  GETPIXEL( p32, src_x + 2, src_y + 1 );  GETPIXEL( p33, src_x + 2, src_y + 2 );
        #undef GETPIXEL
        SampleBicubicH< T >( hh0, p00, p10, p20, p30, fmt, tx );
        SampleBicubicH< T >( hh1, p01, p11, p21, p31, fmt, tx );
        SampleBicubicH< T >( hh2, p02, p12, p22, p32, fmt, tx );
        SampleBicubicH< T >( hh3, p03, p13, p23, p33, fmt, tx );
        SampleBicubicV< T >( dst, hh0, hh1, hh2, hh3, fmt, ty );

        dst += fmt.BPP;
        point_in_src += src_dx;
    }

    delete [] p00;
    delete [] p01;
    delete [] p02;
    delete [] p03;
    delete [] hh0;
    delete [] hh1;
    delete [] hh2;
    delete [] hh3;
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

