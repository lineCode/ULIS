// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         BlendMT_Separable_MEM_Generic.ipp
* @author       Clement Berthaud
* @brief        This file provides the declaration for the generic Blend entry point functions.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Base/Core.h"
#include "Blend/Blend.h"
#include "Base/Helpers.ipp"
#include "Blend/Modes.h"
#include "Blend/Func/SeparableBlendFuncF.ipp"
#include "Blend/Func/AlphaFuncF.ipp"
#include "Maths/Geometry.h"
#include "Thread/ParallelFor.h"

ULIS2_NAMESPACE_BEGIN
template< typename T >
void
InvokeBlendMTProcessScanline_Separable_MEM_Generic_Subpixel( const tByte* iSrc, tByte* iBdp, int32 iLine, const tSize iSrcBps, const FFormatInfo* iFmtInfo, std::shared_ptr< const FBlendInfo > iBlendParams )
{
    const FBlendInfo&   blendInfo       = *iBlendParams;
    const tByte*        src             = iSrc;
    tByte*              bdp             = iBdp;
    const bool          notLastLine     = iLine < blendInfo._backdropCoverage.y;
    const bool          notFirstLine    = iLine > 0;
    const bool          onLeftBorder    = blendInfo._backdropWorkingRect.x == 0;
    const bool          hasLeftData     = blendInfo.sourceRect.x + blendInfo._shift.x > 0;
    const bool          hasTopData      = blendInfo.sourceRect.y + blendInfo._shift.y > 0;

    float m11, m01, m10, m00, vv0, vv1, res;
    m11 = ( notLastLine && onLeftBorder && hasLeftData )    ? TYPE2FLOAT( src - iFmtInfo->BPP,              iFmtInfo->AID ) : 0.f;
    m10 = ( hasLeftData && ( notFirstLine || hasTopData ) ) ? TYPE2FLOAT( src - iSrcBps - iFmtInfo->BPP,    iFmtInfo->AID ) : 0.f;
    vv1 = m10 * blendInfo.backdropPosition.y + m11 * blendInfo._buspixelComponent.y;

    for( int x = 0; x < blendInfo._backdropWorkingRect.w; ++x ) {
        const bool notLastCol = x < blendInfo._backdropCoverage.x;
        m00 = m10;
        m01 = m11;
        vv0 = vv1;

        if( iFmtInfo->HEA ) {
            m11 = ( notLastCol && notLastLine )                     ? TYPE2FLOAT( src,              iFmtInfo->AID ) : 0.f;
            m10 = ( notLastCol && ( notFirstLine || hasTopData ) )  ? TYPE2FLOAT( src - iSrcBps,    iFmtInfo->AID ) : 0.f;
        } else {
            m11 = ( notLastCol && notLastLine )     ? 1.f : 0.f;
            m10 = ( notLastCol && notFirstLine )    ? 1.f : 0.f;
        }

        vv1 = m10 * blendInfo.backdropPosition.y + m11 * blendInfo._buspixelComponent.y;
        res = vv0 * blendInfo.backdropPosition.x + vv1 * blendInfo._buspixelComponent.x;
        const float alpha_bdp   = iFmtInfo->HEA ? TYPE2FLOAT( bdp, iFmtInfo->AID ) : 1.f;
        const float alpha_src   = res * blendInfo.opacityValue;
        const float alpha_comp  = AlphaNormalF( alpha_src, alpha_bdp );
        const float var         = alpha_comp == 0.f ? 0.f : alpha_src / alpha_comp;
        float alpha_result;
        ULIS2_ASSIGN_ALPHAF( blendInfo.alphaMode, alpha_result, alpha_src, alpha_bdp );

        for( uint8 j = 0; j < iFmtInfo->NCC; ++j ) {
            uint8 r = iFmtInfo->IDT[j];
            float s11 = ( notLastCol  && notLastLine )                                      ?   TYPE2FLOAT( src,                            r ) : 0.f;
            float s01 = ( notLastLine && ( x > 0 || hasLeftData ) )                         ?   TYPE2FLOAT( src - iFmtInfo->BPP,            r ) : 0.f;
            float s10 = ( notLastCol && ( notFirstLine || hasTopData ) )                    ?   TYPE2FLOAT( src - iSrcBps,                  r ) : 0.f;
            float s00 = ( ( x > 0 || hasLeftData > 0 ) && ( notFirstLine || hasTopData ) )  ?   TYPE2FLOAT( src - iSrcBps - iFmtInfo->BPP,  r ) : 0.f;
            float v1 = ( s00 * m00 ) * blendInfo.backdropPosition.y + ( s01 * m01 ) * blendInfo._buspixelComponent.y;
            float v2 = ( s10 * m10 ) * blendInfo.backdropPosition.y + ( s11 * m11 ) * blendInfo._buspixelComponent.y;
            float srcvf = res == 0.f ? 0.f : ( ( v1 ) * blendInfo.backdropPosition.x + ( v2 ) * blendInfo._buspixelComponent.x ) / res;
            float bdpvf = TYPE2FLOAT( bdp, r );
            #define TMP_ASSIGN( _BM, _E1, _E2, _E3 ) FLOAT2TYPE( bdp, r, SeparableCompOpF< _BM >( srcvf, bdpvf, alpha_bdp, var ) );
            ULIS2_SWITCH_FOR_ALL_DO( blendInfo.blendingMode, ULIS2_FOR_ALL_SEPARABLE_BM_DO, TMP_ASSIGN, 0, 0, 0 )
            #undef TMP_ASSIGN
        }

        if( iFmtInfo->HEA ) FLOAT2TYPE( bdp, iFmtInfo->AID, alpha_result );
        src += iFmtInfo->BPP;
        bdp += iFmtInfo->BPP;
    }
}

template< typename T >
void
BlendMT_Separable_MEM_Generic_Subpixel( const FFormatInfo& iFormatInfo, const FPerfInfo& iPerfParams, std::shared_ptr< const FBlendInfo > iBlendParams ) {
    const FBlendInfo&   blendInfo   = *iBlendParams;
    const tByte*        src         = iBlendParams->source->DataPtr();
    tByte*              bdp         = iBlendParams->backdrop->DataPtr();
    const tSize         src_bps     = iBlendParams->source->BytesPerScanLine();
    const tSize         bdp_bps     = iBlendParams->backdrop->BytesPerScanLine();
    const tSize         src_decal_y = blendInfo._shift.y + blendInfo.sourceRect.y;
    const tSize         src_decal_x = ( blendInfo._shift.x + blendInfo.sourceRect.x )   * iFormatInfo.BPP;
    const tSize         bdp_decal_x = ( blendInfo._backdropWorkingRect.x )              * iFormatInfo.BPP;
    ULIS2_MACRO_INLINE_PARALLEL_FOR( iPerfParams.intent, iPerfParams.pool, iPerfParams.blocking
                                   , iBlendParams->_backdropWorkingRect.h
                                   , InvokeBlendMTProcessScanline_Separable_MEM_Generic_Subpixel< T >
                                   , src + ( ( src_decal_y + pLINE )                        * src_bps ) + src_decal_x
                                   , bdp + ( ( blendInfo._backdropWorkingRect.y + pLINE )   * bdp_bps ) + bdp_decal_x
                                   , pLINE , src_bps, &iFormatInfo, iBlendParams );
}

template< typename T >
void
InvokeBlendMTProcessScanline_Separable_MEM_Generic( const tByte* iSrc, tByte* iBdp, int32 iLine, const FFormatInfo* iFmtInfo, std::shared_ptr< const FBlendInfo > iBlendParams )
{
    const FBlendInfo&   blendInfo   = *iBlendParams;
    const tByte*        src         = iSrc;
    tByte*              bdp         = iBdp;

    for( int x = 0; x < blendInfo._backdropWorkingRect.w; ++x ) {
        const float alpha_src       = iFmtInfo->HEA ? TYPE2FLOAT( src, iFmtInfo->AID ) * blendInfo.opacityValue : blendInfo.opacityValue;
        const float alpha_bdp       = iFmtInfo->HEA ? TYPE2FLOAT( bdp, iFmtInfo->AID ) : 1.f;
        const float alpha_comp      = AlphaNormalF( alpha_src, alpha_bdp );
        const float var             = alpha_comp == 0.f ? 0.f : alpha_src / alpha_comp;
        float alpha_result;
        ULIS2_ASSIGN_ALPHAF( blendInfo.alphaMode, alpha_result, alpha_src, alpha_bdp );
        for( uint8 j = 0; j < iFmtInfo->NCC; ++j ) {
            uint8 r = iFmtInfo->IDT[j];
            float srcvf = TYPE2FLOAT( src, r );
            float bdpvf = TYPE2FLOAT( bdp, r );
            #define TMP_ASSIGN( _BM, _E1, _E2, _E3 ) FLOAT2TYPE( bdp, r, SeparableCompOpF< _BM >( srcvf, bdpvf, alpha_bdp, var ) );
            ULIS2_SWITCH_FOR_ALL_DO( blendInfo.blendingMode, ULIS2_FOR_ALL_SEPARABLE_BM_DO, TMP_ASSIGN, 0, 0, 0 )
            #undef TMP_ASSIGN
        }
        if( iFmtInfo->HEA ) FLOAT2TYPE( bdp, iFmtInfo->AID, alpha_result );
        src += iFmtInfo->BPP;
        bdp += iFmtInfo->BPP;
    }
}

template< typename T >
void
BlendMT_Separable_MEM_Generic( const FFormatInfo& iFormatInfo, const FPerfInfo& iPerfParams, std::shared_ptr< const FBlendInfo > iBlendParams ) {
    const FBlendInfo&   blendInfo   = *iBlendParams;
    const tByte*        src         = iBlendParams->source->DataPtr();
    tByte*              bdp         = iBlendParams->backdrop->DataPtr();
    const tSize         src_bps     = iBlendParams->source->BytesPerScanLine();
    const tSize         bdp_bps     = iBlendParams->backdrop->BytesPerScanLine();
    const tSize         src_decal_x = blendInfo.sourceRect.x            * iFormatInfo.BPP;
    const tSize         bdp_decal_x = blendInfo._backdropWorkingRect.x  * iFormatInfo.BPP;
    ULIS2_MACRO_INLINE_PARALLEL_FOR( iPerfParams.intent, iPerfParams.pool, iPerfParams.blocking
                                   , iBlendParams->_backdropWorkingRect.h
                                   , InvokeBlendMTProcessScanline_Separable_MEM_Generic< T >
                                   , src + ( ( blendInfo.sourceRect.y           + pLINE ) * src_bps ) + src_decal_x
                                   , bdp + ( ( blendInfo._backdropWorkingRect.y + pLINE ) * bdp_bps ) + bdp_decal_x
                                   , pLINE , &iFormatInfo, iBlendParams );
}

ULIS2_NAMESPACE_END

