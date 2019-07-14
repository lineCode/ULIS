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
    static void ProcessScanLine( TBlock< _SH >*                     iBlockTop
                               , TBlock< _SH >*                     iBlockBack
                               , typename TBlock< _SH >::tPixelType iOpacity
                               , const int                          iLine
                               , const int                          iX1
                               , const int                          iX2
                               , const FPoint&                      iShift
                               , const uint8                        iAlphaIndex )
    {
        // Base ptrs for scanlines
        uint8* scanline_pixel_back  = iBlockBack->PixelPtr( iX1, iLine );
        uint8* scanline_pixel_top   = iBlockTop->PixelPtr( iX1 + iShift.x, iLine + iShift.y );
        uint8* base_pixel_back      = scanline_pixel_back;
        uint8* base_pixel_top       = scanline_pixel_top ;
        uint8* base_alpha_back      = scanline_pixel_back   + iAlphaIndex;
        uint8* base_alpha_top       = scanline_pixel_top    + iAlphaIndex;
        const int   delta   = iX2 - iX1;
        const int   op      = delta / 4;

        for( int i = 0; i < op; ++i )
        {
            FVectorSIMD128 pixel_back_SIMD;
            pixel_back_SIMD.m128i = _mm_loadu_si128( (__m128i const*)base_pixel_back );
            FVectorSIMD128 pixel_top_SIMD;
            pixel_top_SIMD.m128i = _mm_loadu_si128( (__m128i const*)base_pixel_top );

            uint8 alpha_back[4] = { *( base_alpha_back ), *( base_alpha_back + 4 ), *( base_alpha_back + 8 ), *( base_alpha_back + 12 ) };
            uint8 alpha_top[4]  = { *( base_alpha_top ),  *( base_alpha_top + 4 ),  *( base_alpha_top + 8 ),  *( base_alpha_top + 12 ) };

            uint8 alpha_result[4];
            uint8 alpha_var[4];
            for( int i = 0; i < 4; ++i ) {
                alpha_result[i] = Union< _SH >( *( alpha_back + ( i * 4 ) ), *( base_alpha_top + ( i * 4 ) ) );
                alpha_var[i]    = alpha_result[i] == 0 ? 0 : ( alpha_top[i] * 255 ) / alpha_result[i];
            }

            FVectorSIMD128 alpha_back_SIMD;
            alpha_back_SIMD.m128i = _mm_set_epi8( alpha_back[0], alpha_back[0], alpha_back[0], alpha_back[0]
                                                , alpha_back[1], alpha_back[1], alpha_back[1], alpha_back[1]
                                                , alpha_back[2], alpha_back[2], alpha_back[2], alpha_back[2]
                                                , alpha_back[3], alpha_back[3], alpha_back[3], alpha_back[3] );

            FVectorSIMD128 alpha_var_SIMD;
            alpha_var_SIMD.m128i = _mm_set_epi8( alpha_var[0], alpha_var[0], alpha_var[0], alpha_var[0]
                                               , alpha_var[1], alpha_var[1], alpha_var[1], alpha_var[1]
                                               , alpha_var[2], alpha_var[2], alpha_var[2], alpha_var[2]
                                               , alpha_var[3], alpha_var[3], alpha_var[3], alpha_var[3] );

            FVectorSIMD128 vec255;
            vec255.m128i = _mm_set1_epi8( 255 );

            // ( ( MAX_uint8 - var ) * Cb + var * ( ( ( MAX_uint8 - ab ) * Cs + ab * BlendFunc< mode, uint8 >::Compute( Cb, Cs ) ) / MAX_uint8 ) ) / MAX_uint8;

            // ( ( 255 - var ) * Cb + var * ( ( ( 255 - ab ) * Cs + ab * Blend( Cb, Cs ) ) / 255 ) ) / 255;

            // ( 255 - var ) * Cb + var * ( ( 255 - ab ) * Cs + ab * Blend( Cb, Cs ) );


            base_pixel_back   = base_pixel_back + 16;
            base_pixel_top    = base_pixel_top  + 16;
            base_alpha_back   = base_alpha_back + 16;
            base_alpha_top    = base_alpha_top  + 16;
        }

        /*
        for( int x = iX1; x < iX2; ++x )
        {
            typename TBlock< _SH >::tPixelProxy         pixelBack   = back->PixelProxy( x, y );
            typename TBlock< _SH >::tPixelProxy         pixelTop    = top->PixelProxy( x + shift.x, y + shift.y );
            const typename TBlock< _SH >::tPixelType    alphaBack   = pixelBack.GetAlpha();
            const typename TBlock< _SH >::tPixelType    alphaTop    = ConvType< typename TBlock< _SH >::tNextPixelType, typename TBlock< _SH >::tPixelType >( (typename TBlock< _SH >::tNextPixelType)( pixelTop.GetAlpha() * opacity ) );
            const typename TBlock< _SH >::tPixelType    alphaResult = Union< _SH >( alphaBack, alphaTop );
            const typename TBlock< _SH >::tPixelType    var         = alphaResult == 0 ? 0 : ( alphaTop * TBlock< _SH >::StaticMax() ) / alphaResult;
            const int max_chan = TBlock< _SH >::StaticNumColorChannels();
            for( int i = 0; i < max_chan; ++i )
                pixelBack.SetComponent( i, Composer< _SH, _BM >::BasicCompositing( pixelBack.GetComponent( i ), pixelTop.GetComponent( i ), alphaBack, var ) );
            pixelBack.SetAlpha( alphaResult );
        }
        */
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
            global_pool.ScheduleJob( TBlockBlender_RGBA8_SSE< _SH >::ProcessScanLine, iBlockTop, iBlockBack, iOpacity, y, x1, x2, iShift, alpha_index );

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