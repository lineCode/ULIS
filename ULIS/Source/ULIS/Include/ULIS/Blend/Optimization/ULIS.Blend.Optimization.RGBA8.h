/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Blend.Optimization.RGBA8.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once

#include <assert.h>
#include "ULIS/Base/ULIS.Base.BaseTypes.h"
#include "ULIS/Blend/ULIS.Blend.BlendingModes.h"
#include "ULIS/Blend/ULIS.Blend.BlockBlender.h"
#include "ULIS/Data/ULIS.Data.Block.h"
#include "ULIS/Global/ULIS.Global.GlobalCPUConfig.h"
#include "ULIS/Global/ULIS.Global.GlobalThreadPool.h"

namespace ULIS {
/////////////////////////////////////////////////////
// Defines
#define tSpec TBlockInfo< _SH >

/////////////////////////////////////////////////////
// TBlockBlender_RGBA8_SSE
template< uint32 _SH >
class TBlockBlender_RGBA8_SSE
{
public:
    static void ProcessScanLineSSE( TBlock< _SH >*                  iBlockTop
                               , TBlock< _SH >*                     iBlockBack
                               , typename TBlock< _SH >::tPixelType iOpacity
                               , const int                          iLine
                               , const int                          iX1
                               , const int                          iX2
                               , const FPoint&                      iShift
                               , const uint8                        iAlphaIndex )
    {
        // Base ptrs for scanlines
        uint8* base_pixel_back = iBlockBack->PixelPtr( iX1, iLine );
        uint8* base_pixel_top  = iBlockTop->PixelPtr( iX1 + iShift.x, iLine + iShift.y );
        const int delta = iX2 - iX1;
        const int op    = delta / 4;

        uint8 asmi[4] = { iAlphaIndex, iAlphaIndex + 4, iAlphaIndex + 8, iAlphaIndex + 12 };
        __m128i asm = _mm_set_epi8( asmi[3], asmi[3], asmi[3], asmi[3]
                                  , asmi[2], asmi[2], asmi[2], asmi[2]
                                  , asmi[1], asmi[1], asmi[1], asmi[1]
                                  , asmi[0], asmi[0], asmi[0], asmi[0] );
        FVectorSIMD128_8bit var_spread_mask;
        var_spread_mask.Set4( 0, 1, 2, 3 );
        FVectorSIMD128_8bit opacity;
        opacity.Set1( iOpacity );
        FVectorSIMD128_8bit max = FVectorSIMD128_8bit::Max();
        FVectorSIMD128_8bit pixel_back_SIMD;
        FVectorSIMD128_8bit pixel_top_SIMD;
        FVectorSIMD128_8bit alpha_back_SIMD;
        FVectorSIMD128_8bit alpha_top_SIMD;
        FVectorSIMD128_8bit alpha_resultSIMD;
        FVectorSIMD128_8bit alpha_varSIMD;
        FVectorSIMD128_8bit res;
        for( int i = 0; i < op; ++i )
        {
            pixel_back_SIMD.Load( base_pixel_back );
            pixel_top_SIMD.Load( base_pixel_top );
            alpha_back_SIMD.m128i = _mm_shuffle_epi8( pixel_back_SIMD.m128i, asm );
            alpha_top_SIMD.m128i =  _mm_shuffle_epi8( pixel_top_SIMD.m128i, asm );
            alpha_top_SIMD = DownScale( alpha_top_SIMD * opacity );
            alpha_resultSIMD = Contract( ( Spread( alpha_back_SIMD ) + Spread( alpha_top_SIMD ) ) - Spread( DownScale( alpha_back_SIMD * alpha_top_SIMD ) ) );
            alpha_varSIMD.u8[0] = alpha_resultSIMD.u8[0] == 0 ? 0 : ( alpha_top_SIMD.u8[0] * 255 ) / alpha_resultSIMD.u8[0];
            alpha_varSIMD.u8[1] = alpha_resultSIMD.u8[1] == 0 ? 0 : ( alpha_top_SIMD.u8[1] * 255 ) / alpha_resultSIMD.u8[1];
            alpha_varSIMD.u8[2] = alpha_resultSIMD.u8[2] == 0 ? 0 : ( alpha_top_SIMD.u8[2] * 255 ) / alpha_resultSIMD.u8[2];
            alpha_varSIMD.u8[3] = alpha_resultSIMD.u8[3] == 0 ? 0 : ( alpha_top_SIMD.u8[3] * 255 ) / alpha_resultSIMD.u8[3];
            alpha_varSIMD.m128i = _mm_shuffle_epi8( alpha_varSIMD.m128i, var_spread_mask.m128i );

            res = DownScale( ( max - alpha_varSIMD ) * pixel_back_SIMD + alpha_varSIMD * DownScale( ( max - alpha_back_SIMD ) * pixel_top_SIMD + alpha_back_SIMD * /*BLEND*/pixel_top_SIMD/*BLEND*/ ) );
            _mm_storeu_si128( (__m128i*)base_pixel_back, res.m128i );
            /*
            *( base_alpha_back ) = alpha_result[0];
            *( base_alpha_back + 4 ) = alpha_result[1];
            *( base_alpha_back + 8 ) = alpha_result[2];
            *( base_alpha_back + 12 ) = alpha_result[3];
            */

            base_pixel_back   += 16;
            base_pixel_top    += 16;
        }
    }

    static void Run( TBlock< _SH >*                     iBlockTop
                   , TBlock< _SH >*                     iBlockBack
                   , typename TBlock< _SH >::tPixelType iOpacity
                   , const FRect&                       iROI
                   , const FPoint&                      iShift
                   , const FPerfStrat&                  iPerfStrat = FPerfStrat() )
    {
        const int x1 = iROI.y;
        const int y1 = iROI.y;
        const int x2 = x1 + iROI.w;
        const int y2 = y1 + iROI.h;
        const uint8 alpha_index     = (uint8) TBlock< _SH >::tPixelProxy::RedirectedIndex( 3 );
        FThreadPool& global_pool = FGlobalThreadPool::Get();
        for( int y = y1; y < y2; ++y )
            global_pool.ScheduleJob( TBlockBlender_RGBA8_SSE< _SH >::ProcessScanLineSSE, iBlockTop, iBlockBack, iOpacity, y, x1, x2, iShift, alpha_index );

        global_pool.WaitForCompletion();
    }
};

/////////////////////////////////////////////////////
// TBlockBlender_Imp
template< uint32        _SH,    // Format
          eBlendingMode _BM,    // Blending Mode
          uint32        _LH,    // Layout
          e_nm          _NM,    // Normalized
          bool          _DM >   // Decimal
class TBlockBlenderImp< _SH,                // Format
                        _BM,                // Blending Mode
                        e_tp::kuint8,       // uint8
                        e_cm::kRGB,         // RGB
                        e_ea::khasAlpha,    // Alpha
                        _LH,                // Layout
                        _NM,                // Normalized
                        _DM >               // Decimal
{
public:
    static void Run( TBlock< _SH >*                     iBlockTop
                   , TBlock< _SH >*                     iBlockBack
                   , typename TBlock< _SH >::tPixelType iOpacity
                   , const FRect&                       iROI
                   , const FPoint&                      iShift
                   , const FPerfStrat&                  iPerfStrat = FPerfStrat() )
    {
        if( iPerfStrat.use_sse_if_available && FGlobalCPUConfig::Get().info.HW_SSSE3 )
        {
            TBlockBlender_RGBA8_SSE< _SH >::Run( iBlockTop
                                               , iBlockBack
                                               , iOpacity
                                               , iROI
                                               , iShift
                                               , iPerfStrat );
        }
        else
        {
            TBlockBlender_Default< _SH
                             , _BM
                             , tSpec::_nf._tp
                             , tSpec::_nf._cm
                             , tSpec::_nf._ea
                             , tSpec::_nf._lh
                             , tSpec::_nf._nm
                             , tSpec::_nf._dm >
                             ::Run( iBlockTop
                                  , iBlockBack
                                  , iOpacity
                                  , iROI
                                  , iShift
                                  , iPerfStrat );
        }
    }
};

/////////////////////////////////////////////////////
// Undefines
#undef tSpec

} // namespace ULIS