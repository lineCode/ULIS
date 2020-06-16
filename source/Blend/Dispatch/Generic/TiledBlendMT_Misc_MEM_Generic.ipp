// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS3
*__________________
*
* @file         BlendMT_Misc_MEM_Generic.ipp
* @author       Clement Berthaud
* @brief        This file provides the declaration for the generic Blend entry point functions.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"
#include "Base/PRNG.h"
#include "Blend/Dispatch/BlendInfo.h"
#include "Blend/Func/AlphaFuncF.ipp"
#include "Blend/Modes.h"
#include "Maths/Geometry.h"
#include "Thread/ThreadPool.h"

ULIS3_NAMESPACE_BEGIN
template< typename T >
void
InvokeTiledBlendMTProcessScanline_Misc_MEM_Generic( const tByte* iSrc, tByte* iBdp, int32 iLine, std::shared_ptr< const _FBlendInfoPrivate > iInfo ) {
    const _FBlendInfoPrivate&   info    = *iInfo;
    const FFormatInfo&          fmt     = info.source->FormatInfo();
    const tByte*                src     = iSrc;
    tByte*                      bdp     = iBdp;

    switch( info.blendingMode ) {
        case BM_DISSOLVE: {
            int32 seedy = info.backdropWorkingRect.y + iLine + 1;
            uint32 localPRNGSeed = ( 8253729 % seedy ) * GetWeakPRNGSeed() + ( 2396403 % ( seedy + 64578 ) * seedy );

            for( int x = 0; x < info.backdropWorkingRect.w; ++x ) {
                const float alpha_bdp   = fmt.HEA ? TYPE2FLOAT( bdp, fmt.AID ) : 1.f;
                const float alpha_src   = fmt.HEA ? TYPE2FLOAT( src, fmt.AID ) * info.opacityValue : info.opacityValue;
                localPRNGSeed = 8253729 * localPRNGSeed + 2396403;
                float toss = ( localPRNGSeed % 65537 ) / 65537.f;
                if( toss < alpha_src ) {
                    float alpha_result;
                    ULIS3_ASSIGN_ALPHAF( info.alphaMode, alpha_result, 1.f, alpha_bdp );
                    memcpy( bdp, src, fmt.BPP );
                    if( fmt.HEA ) FLOAT2TYPE( bdp, fmt.AID, alpha_result );
                }
                src += fmt.BPP;
                bdp += fmt.BPP;
            }
            break;
        }

        case BM_BAYERDITHER8x8: {
            for( int x = 0; x < info.backdropWorkingRect.w; ++x ) {
                const float alpha_bdp   = fmt.HEA ? TYPE2FLOAT( bdp, fmt.AID ) : 1.f;
                const float alpha_src   = fmt.HEA ? TYPE2FLOAT( src, fmt.AID ) * info.opacityValue : info.opacityValue;
                const float bayerEl     = gBayer8x8Matrix[ ( info.backdropWorkingRect.y + iLine ) % 8 ][ ( info.backdropWorkingRect.x + x ) % 8 ];
                if( alpha_src >= bayerEl ) {
                    float alpha_result;
                    ULIS3_ASSIGN_ALPHAF( info.alphaMode, alpha_result, 1.f, alpha_bdp );
                    memcpy( bdp, src, fmt.BPP );
                    if( fmt.HEA ) FLOAT2TYPE( bdp, fmt.AID, alpha_result );
                }
                src += fmt.BPP;
                bdp += fmt.BPP;
            }
            break;
        }
    }
}

template< typename T >
void
TiledBlendMT_Misc_MEM_Generic( std::shared_ptr< const _FBlendInfoPrivate > iInfo ) {
    const _FBlendInfoPrivate&   info        = *iInfo;
    const tByte*                src         = info.source->DataPtr();
    tByte*                      bdp         = info.backdrop->DataPtr();
    const tSize                 src_bps     = info.source->BytesPerScanLine();
    const tSize                 bdp_bps     = info.backdrop->BytesPerScanLine();
    const tSize                 src_decal_y = info.shift.y + info.sourceRect.y;
    const tSize                 src_decal_x = ( info.shift.x + info.sourceRect.x )  * info.source->BytesPerPixel();
    const tSize                 bdp_decal_x = ( info.backdropWorkingRect.x )        * info.source->BytesPerPixel();
    ULIS3_MACRO_INLINE_PARALLEL_FOR( info.perfIntent, info.pool, info.blocking
                                   , info.backdropWorkingRect.h
                                   , InvokeTiledBlendMTProcessScanline_Misc_MEM_Generic< T >
                                   , src + ( ( src_decal_y + pLINE )                * src_bps ) + src_decal_x
                                   , bdp + ( ( info.backdropWorkingRect.y + pLINE ) * bdp_bps ) + bdp_decal_x
                                   , pLINE , iInfo );
}

ULIS3_NAMESPACE_END

