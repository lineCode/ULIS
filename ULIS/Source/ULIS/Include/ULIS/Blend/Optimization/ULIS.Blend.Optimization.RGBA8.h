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
    static void ProcessScanLineSSE( TBlock< _SH >*                     iBlockTop
                                  , TBlock< _SH >*                     iBlockBack
                                  , typename TBlock< _SH >::tPixelType iOpacity
                                  , const int                          iLine
                                  , const int                          iX1
                                  , const int                          iX2
                                  , const FPoint&                      iShift
                                  , uint8                              iAlphaIndex )
    {
        // Base ptrs for scanlines
        uint8* bpb = iBlockBack->PixelPtr( iX1, iLine );
        uint8* bpt  = iBlockTop->PixelPtr( iX1 + iShift.x, iLine + iShift.y );
        const int delta = iX2 - iX1;
        const int op    = delta / 4;

        uint8 asmi[4];
        asmi[0] = iAlphaIndex;
        asmi[1] = iAlphaIndex + 4;
        asmi[2] = iAlphaIndex + 8;
        asmi[3] = iAlphaIndex + 12;
        __m128i asmv = _mm_set_epi8( asmi[3], asmi[3], asmi[3], asmi[3]
                                   , asmi[2], asmi[2], asmi[2], asmi[2]
                                   , asmi[1], asmi[1], asmi[1], asmi[1]
                                   , asmi[0], asmi[0], asmi[0], asmi[0] );
        __m128i opa = _mm_set1_epi8( iOpacity );
        __m128i max = _mm_set1_epi8( 255 );
        
        for( int i = 0; i < op; ++i )
        {
            __m128i pb = _mm_loadu_si128( (const __m128i*)bpb );
            __m128i pt = _mm_loadu_si128( (const __m128i*)bpt );
            __m128i ab = _mm_shuffle_epi8( pb, asmv );
            __m128i at = _mm_shuffle_epi8( pt, asmv );
            __m128i zero = _mm_setzero_si128();
            __m128i atmullo = _mm_mullo_epi16( _mm_unpacklo_epi8( at, zero), _mm_unpacklo_epi8( opa, zero));
            __m128i atmulhi = _mm_mullo_epi16( _mm_unpackhi_epi8( at, zero), _mm_unpackhi_epi8( opa, zero));
            __m128i ones = _mm_set1_epi16( 1 );
            __m128i atmullodown = _mm_srli_epi16( _mm_adds_epu16( _mm_adds_epu16( atmullo, ones ), _mm_srli_epi16( atmullo, 8 ) ), 8 );
            __m128i atmulhidown = _mm_srli_epi16( _mm_adds_epu16( _mm_adds_epu16( atmulhi, ones ), _mm_srli_epi16( atmulhi, 8 ) ), 8 );
            __m128i absplo = _mm_unpacklo_epi8( ab, zero);
            __m128i absphi = _mm_unpackhi_epi8( ab, zero);
            __m128i addabatsplo = _mm_add_epi16( absplo, atmullodown );
            __m128i addabatsphi = _mm_add_epi16( absphi, atmulhidown );
            __m128i mulabatlo = _mm_mullo_epi16( absplo, atmullodown );
            __m128i mulabathi = _mm_mullo_epi16( absphi, atmulhidown );
            __m128i mulanatlodown = _mm_srli_epi16( _mm_adds_epu16( _mm_adds_epu16( mulabatlo, ones ), _mm_srli_epi16( mulabatlo, 8 ) ), 8 );
            __m128i mulanathidown = _mm_srli_epi16( _mm_adds_epu16( _mm_adds_epu16( mulabathi, ones ), _mm_srli_epi16( mulabathi, 8 ) ), 8 );
            __m128i resabatlosp = _mm_sub_epi16( addabatsplo, mulanatlodown );
            __m128i resabathisp = _mm_sub_epi16( addabatsphi, mulanathidown );
            __m128i resmasklo = _mm_set_epi8(0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 14, 12, 10, 8, 6, 4, 2, 0);
            __m128i resmaskhi = _mm_set_epi8(14, 12, 10, 8, 6, 4, 2, 0, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80);
            __m128i ar = _mm_or_si128( _mm_shuffle_epi8( resabatlosp, resmasklo ), _mm_shuffle_epi8( resabathisp, resmaskhi ) );
            __m128i ex32psm = _mm_set_epi8( 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 12, 8, 4, 0 );
            __m128i arshpr32 = _mm_shuffle_epi8( ar, ex32psm );
            __m128i atcat = _mm_or_si128( _mm_shuffle_epi8( atmullodown, resmasklo ), _mm_shuffle_epi8( atmulhidown, resmaskhi ) );
            __m128i atshpr32 = _mm_shuffle_epi8( atcat, ex32psm );
            __m128i ar32 = _mm_cvtepu8_epi32( arshpr32 );
            __m128i at32 = _mm_cvtepu8_epi32( atshpr32 );
            __m128 arps = _mm_cvtepi32_ps( ar32 );
            __m128 atps = _mm_cvtepi32_ps( at32 );
            __m128 maxps = _mm_set1_ps( 255.f );
            __m128 avarpsuns = _mm_mul_ps( _mm_div_ps( atps, arps ), maxps ) ;
            __m128 zerops = _mm_setzero_ps();
            __m128 atzerom = _mm_cmpeq_ps( atps, zerops );
            __m128 avarps = _mm_blendv_ps( atps, avarpsuns, atzerom );
            __m128i avarsh32 = _mm_cvtps_epi32( avarps );
            __m128i shv = _mm_set_epi8( 12, 12, 12, 12, 8, 8, 8, 8, 4, 4, 4, 4, 0, 0, 0, 0 );
            __m128i avar = _mm_shuffle_epi8( avarsh32, shv );
            __m128i invavar = _mm_sub_epi8( max, avar );
            __m128i invavarlo = _mm_unpacklo_epi8( invavar, zero);
            __m128i invavarhi = _mm_unpackhi_epi8( invavar, zero);
            __m128i pbsplo = _mm_unpacklo_epi8( pb, zero);
            __m128i pbsphi = _mm_unpackhi_epi8( pb, zero);
            __m128i mulinvavarpbsplo = _mm_mullo_epi16( invavarlo, pbsplo);
            __m128i mulinvavarpbsphi = _mm_mullo_epi16( invavarhi, pbsphi );
            __m128i invab = _mm_sub_epi8( max, ab );
            __m128i invablo = _mm_unpacklo_epi8( invab, zero );
            __m128i invabhi = _mm_unpackhi_epi8( invab, zero );
            __m128i ptsplo = _mm_unpacklo_epi8( pt, zero);
            __m128i ptsphi = _mm_unpackhi_epi8( pt, zero);
            __m128i mulinvabptlo = _mm_mullo_epi16( invablo, ptsplo);
            __m128i mulinvabpthi = _mm_mullo_epi16( invabhi, ptsphi );
            __m128i mulabbllo = _mm_mullo_epi16( absplo, ptsplo); // BLEND
            __m128i mulabblhi = _mm_mullo_epi16( absphi, ptsphi); // BLEND
            __m128i rmlo = _mm_add_epi16( mulinvabptlo, mulabbllo );
            __m128i rmhi = _mm_add_epi16( mulinvabpthi, mulabblhi );
            __m128i rmlodown = _mm_srli_epi16( _mm_adds_epu16( _mm_adds_epu16( rmlo, ones ), _mm_srli_epi16( rmlo, 8 ) ), 8 );
            __m128i rmhidown = _mm_srli_epi16( _mm_adds_epu16( _mm_adds_epu16( rmhi, ones ), _mm_srli_epi16( rmhi, 8 ) ), 8 );
            __m128i avarlo = _mm_unpacklo_epi8( avar, zero);
            __m128i avarhi = _mm_unpackhi_epi8( avar, zero);
            __m128i rrlo = _mm_mullo_epi16( avarlo, rmlodown );
            __m128i rrhi = _mm_mullo_epi16( avarhi, rmhidown );
            __m128i cenlo = _mm_add_epi16( mulinvavarpbsplo, rrlo );
            __m128i cenhi = _mm_add_epi16( mulinvavarpbsphi, rrhi );
            __m128i cenlodown = _mm_srli_epi16( _mm_adds_epu16( _mm_adds_epu16( cenlo, ones ), _mm_srli_epi16( cenlo, 8 ) ), 8 );
            __m128i cenhidown = _mm_srli_epi16( _mm_adds_epu16( _mm_adds_epu16( cenhi, ones ), _mm_srli_epi16( cenhi, 8 ) ), 8 );
            __m128i res = _mm_or_si128( _mm_shuffle_epi8( cenlodown, resmasklo ), _mm_shuffle_epi8( cenhidown, resmaskhi ) );
            _mm_storeu_si128( (__m128i*)bpb, res );
            bpb += 16;
            bpt += 16;
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
        uint8 alpha_index     = (uint8) TBlock< _SH >::tPixelProxy::RedirectedIndex( 3 );
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
        /*
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
        */
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
        //}
    }
};

/////////////////////////////////////////////////////
// Undefines
#undef tSpec

} // namespace ULIS