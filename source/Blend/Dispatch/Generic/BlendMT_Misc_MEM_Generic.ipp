// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         BlendMT_Misc_MEM_Generic.ipp
* @author       Clement Berthaud
* @brief        This file provides the declaration for the generic Blend entry point functions.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Base/Core.h"
#include "Blend/BlendingPRNGSeed.h"
#include "Blend/Modes.h"
#include "Blend/Func/AlphaFuncF.ipp"
#include "Color/ModelStructs.h"
#include "Maths/Geometry.h"
#include "Thread/ParallelFor.h"

float gBayer8x8Matrix[8][8] = {
    { 0.015625f, 0.765625f, 0.203125f, 0.953125f, 0.0625f, 0.8125f, 0.25f, 1.0f          },
    { 0.515625f, 0.265625f, 0.703125f, 0.453125f, 0.5625f, 0.3125f, 0.75f, 0.5f          },
    { 0.140625f, 0.890625f, 0.078125f, 0.828125f, 0.1875f, 0.9375f, 0.125f, 0.875f       },
    { 0.640625f, 0.390625f, 0.578125f, 0.328125f, 0.6875f, 0.4375f, 0.625f, 0.375f       },
    { 0.046875f, 0.796875f, 0.234375f, 0.984375f, 0.03125f, 0.78125f, 0.21875f, 0.96875f },
    { 0.546875f, 0.296875f, 0.734375f, 0.484375f, 0.53125f, 0.28125f, 0.71875f, 0.46875f },
    { 0.171875f, 0.921875f, 0.109375f, 0.859375f, 0.15625f, 0.90625f, 0.09375f, 0.84375f },
    { 0.671875f, 0.421875f, 0.609375f, 0.359375f, 0.65625f, 0.40625f, 0.59375f, 0.34375f } };

ULIS2_NAMESPACE_BEGIN
template< typename T >
void
InvokeBlendMTProcessScanline_Misc_MEM_Generic_Subpixel( const tByte* iSrc, tByte* iBdp, int32 iLine, const tSize iSrcBps, const FFormatInfo* iFmtInfo, std::shared_ptr< const FBlendInfo > iBlendParams ) {
    const FBlendInfo&   blendInfo       = *iBlendParams;
    const tByte*        src             = iSrc;
    tByte*              bdp             = iBdp;
    const bool          notLastLine     = iLine < blendInfo._backdropCoverage.y;
    const bool          notFirstLine    = iLine > 0;
    const bool          onLeftBorder    = blendInfo._backdropWorkingRect.x == 0;
    const bool          hasLeftData     = blendInfo.sourceRect.x + blendInfo._shift.x > 0;
    const bool          hasTopData      = blendInfo.sourceRect.y + blendInfo._shift.y > 0;

    switch( blendInfo.blendingMode ) {
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case BM_DISSOLVE: {
            uint32 localPRNGSeed = gBlendingPRNGSeed;
            int32 seedy = blendInfo._backdropWorkingRect.y + iLine + 1;
            localPRNGSeed = ( 8253729 % seedy ) * localPRNGSeed + ( 2396403 % ( seedy + 64578 ) * seedy );

            float m11, m01, m10, m00, vv0, vv1, res;
            m11 = ( notLastLine && onLeftBorder && hasLeftData )    ? TYPE2FLOAT( src - iFmtInfo->BPP,              iFmtInfo->AID ) : 0.f;
            m10 = ( hasLeftData && ( notFirstLine || hasTopData ) ) ? TYPE2FLOAT( src - iSrcBps - iFmtInfo->BPP,    iFmtInfo->AID ) : 0.f;
            vv1 = m10 * blendInfo.backdropPosition.y + m11 * blendInfo._buspixelComponent.y;

            for( int x = 0; x < blendInfo._backdropWorkingRect.w; ++x ) {
                const bool notLastCol = x < blendInfo._backdropCoverage.x;
                m00 = m10;
                m01 = m11;
                vv0 = vv1;
                SampleSubpixelAlpha( res );
                const float alpha_bdp   = iFmtInfo->HEA ? TYPE2FLOAT( bdp, iFmtInfo->AID ) : 1.f;
                const float alpha_src   = res * blendInfo.opacityValue;
                localPRNGSeed = 8253729 * localPRNGSeed + 2396403;
                float toss = ( localPRNGSeed % 65537 ) / 65537.f;
                if( toss < alpha_src ) {
                    float alpha_result;
                    ULIS2_ASSIGN_ALPHAF( blendInfo.alphaMode, alpha_result, alpha_src, alpha_bdp );
                    memcpy( bdp, src, iFmtInfo->BPP );
                    if( iFmtInfo->HEA ) FLOAT2TYPE( bdp, iFmtInfo->AID, alpha_result );
                }
                src += iFmtInfo->BPP;
                bdp += iFmtInfo->BPP;
            }
            break;
        } // BM_DISSOLVE
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case BM_BAYERDITHER8x8: {
            float m11, m01, m10, m00, vv0, vv1, res;
            m11 = ( notLastLine && onLeftBorder && hasLeftData )    ? TYPE2FLOAT( src - iFmtInfo->BPP,              iFmtInfo->AID ) : 0.f;
            m10 = ( hasLeftData && ( notFirstLine || hasTopData ) ) ? TYPE2FLOAT( src - iSrcBps - iFmtInfo->BPP,    iFmtInfo->AID ) : 0.f;
            vv1 = m10 * blendInfo.backdropPosition.y + m11 * blendInfo._buspixelComponent.y;

            for( int x = 0; x < blendInfo._backdropWorkingRect.w; ++x ) {
                const bool notLastCol = x < blendInfo._backdropCoverage.x;
                m00 = m10;
                m01 = m11;
                vv0 = vv1;
                SampleSubpixelAlpha( res );
                const float alpha_bdp   = iFmtInfo->HEA ? TYPE2FLOAT( bdp, iFmtInfo->AID ) : 1.f;
                const float alpha_src   = res * blendInfo.opacityValue;
                const tSize bayerX          = ( blendInfo._backdropWorkingRect.x + x )     % 8;
                const tSize bayerY          = ( blendInfo._backdropWorkingRect.y + iLine ) % 8;
                const float bayerEl = gBayer8x8Matrix[ bayerY ][ bayerX ];
                if( alpha_src >= bayerEl ) {
                    float alpha_result;
                    ULIS2_ASSIGN_ALPHAF( blendInfo.alphaMode, alpha_result, alpha_src, alpha_bdp );
                    memcpy( bdp, src, iFmtInfo->BPP );
                    if( iFmtInfo->HEA ) FLOAT2TYPE( bdp, iFmtInfo->AID, alpha_result );
                }
                src += iFmtInfo->BPP;
                bdp += iFmtInfo->BPP;
            }
            break;
        } // BM_DISSOLVE
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    }
}

template< typename T >
void
BlendMT_Misc_MEM_Generic_Subpixel( const FFormatInfo& iFormatInfo, std::shared_ptr< const FBlendInfo > iBlendParams ) {
    const FBlendInfo&   blendInfo   = *iBlendParams;
    const tByte*        src         = iBlendParams->source->DataPtr();
    tByte*              bdp         = iBlendParams->backdrop->DataPtr();
    const tSize         src_bps     = iBlendParams->source->BytesPerScanLine();
    const tSize         bdp_bps     = iBlendParams->backdrop->BytesPerScanLine();
    const tSize         src_decal_y = blendInfo._shift.y + blendInfo.sourceRect.y;
    const tSize         src_decal_x = ( blendInfo._shift.x + blendInfo.sourceRect.x )   * iFormatInfo.BPP;
    const tSize         bdp_decal_x = ( blendInfo._backdropWorkingRect.x )              * iFormatInfo.BPP;
    ULIS2_MACRO_INLINE_PARALLEL_FOR( blendInfo.perfInfo.intent, blendInfo.perfInfo.pool, blendInfo.perfInfo.blocking
                                   , blendInfo._backdropWorkingRect.h
                                   , InvokeBlendMTProcessScanline_Misc_MEM_Generic_Subpixel< T >
                                   , src + ( ( src_decal_y + pLINE )                        * src_bps ) + src_decal_x
                                   , bdp + ( ( blendInfo._backdropWorkingRect.y + pLINE )   * bdp_bps ) + bdp_decal_x
                                   , pLINE , src_bps, &iFormatInfo, iBlendParams );
}

template< typename T >
void
InvokeBlendMTProcessScanline_Misc_MEM_Generic( const tByte* iSrc, tByte* iBdp, int32 iLine, const FFormatInfo* iFmtInfo, std::shared_ptr< const FBlendInfo > iBlendParams ) {
    const FBlendInfo&   blendInfo   = *iBlendParams;
    const tByte*        src         = iSrc;
    tByte*              bdp         = iBdp;

    switch( blendInfo.blendingMode ) {
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case BM_DISSOLVE: {
            uint32 localPRNGSeed = gBlendingPRNGSeed;
            int32 seedy = blendInfo._backdropWorkingRect.y + iLine + 1;
            localPRNGSeed = ( 8253729 % seedy ) * localPRNGSeed + ( 2396403 % ( seedy + 64578 ) * seedy );
            for( int x = 0; x < blendInfo._backdropWorkingRect.w; ++x ) {
                const float alpha_bdp       = iFmtInfo->HEA ? TYPE2FLOAT( bdp, iFmtInfo->AID ) : 1.f;
                const float alpha_src       = iFmtInfo->HEA ? TYPE2FLOAT( src, iFmtInfo->AID ) * blendInfo.opacityValue : blendInfo.opacityValue;
                localPRNGSeed = 8253729 * localPRNGSeed + 2396403;
                float toss = ( localPRNGSeed % 65537 ) / 65537.f;
                if( toss < alpha_src ) {
                    float alpha_result;
                    ULIS2_ASSIGN_ALPHAF( blendInfo.alphaMode, alpha_result, alpha_src, alpha_bdp );
                    memcpy( bdp, src, iFmtInfo->BPP );
                    if( iFmtInfo->HEA ) FLOAT2TYPE( bdp, iFmtInfo->AID, alpha_result );
                }
                // Increment ptrs by one pixel
                src += iFmtInfo->BPP;
                bdp += iFmtInfo->BPP;
            }
            break;
        } // BM_DISSOLVE
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case BM_BAYERDITHER8x8: {
            for( int x = 0; x < blendInfo._backdropWorkingRect.w; ++x ) {
                const float alpha_bdp       = iFmtInfo->HEA ? TYPE2FLOAT( bdp, iFmtInfo->AID ) : 1.f;
                const float alpha_src       = iFmtInfo->HEA ? TYPE2FLOAT( src, iFmtInfo->AID ) * blendInfo.opacityValue : blendInfo.opacityValue;
                const tSize bayerX          = ( blendInfo._backdropWorkingRect.x + x )     % 8;
                const tSize bayerY          = ( blendInfo._backdropWorkingRect.y + iLine ) % 8;
                const float bayerEl = gBayer8x8Matrix[ bayerY ][ bayerX ];
                if( alpha_src >= bayerEl ) {
                    float alpha_result;
                    ULIS2_ASSIGN_ALPHAF( blendInfo.alphaMode, alpha_result, alpha_src, alpha_bdp );
                    memcpy( bdp, src, iFmtInfo->BPP );
                    if( iFmtInfo->HEA ) FLOAT2TYPE( bdp, iFmtInfo->AID, alpha_result );
                }
                // Increment ptrs by one pixel
                src += iFmtInfo->BPP;
                bdp += iFmtInfo->BPP;
            }
            break;
        } // BM_DISSOLVE
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    }
}

template< typename T >
void
BlendMT_Misc_MEM_Generic( const FFormatInfo& iFormatInfo, std::shared_ptr< const FBlendInfo > iBlendParams ) {
    const FBlendInfo&   blendInfo   = *iBlendParams;
    const tByte*        src         = iBlendParams->source->DataPtr();
    tByte*              bdp         = iBlendParams->backdrop->DataPtr();
    const tSize         src_bps     = iBlendParams->source->BytesPerScanLine();
    const tSize         bdp_bps     = iBlendParams->backdrop->BytesPerScanLine();
    const tSize         src_decal_y = blendInfo._shift.y + blendInfo.sourceRect.y;
    const tSize         src_decal_x = ( blendInfo._shift.x + blendInfo.sourceRect.x )   * iFormatInfo.BPP;
    const tSize         bdp_decal_x = ( blendInfo._backdropWorkingRect.x )              * iFormatInfo.BPP;
    ULIS2_MACRO_INLINE_PARALLEL_FOR( blendInfo.perfInfo.intent, blendInfo.perfInfo.pool, blendInfo.perfInfo.blocking
                                   , blendInfo._backdropWorkingRect.h
                                   , InvokeBlendMTProcessScanline_Misc_MEM_Generic< T >
                                   , src + ( ( src_decal_y + pLINE )                        * src_bps ) + src_decal_x
                                   , bdp + ( ( blendInfo._backdropWorkingRect.y + pLINE )   * bdp_bps ) + bdp_decal_x
                                   , pLINE , &iFormatInfo, iBlendParams );
}

ULIS2_NAMESPACE_END

