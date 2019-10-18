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
#include "ULIS/Blend/Optimization/ULIS.Blend.Optimization.BlendFuncSSE.h"
#include <immintrin.h>

namespace ULIS {
/////////////////////////////////////////////////////
// Defines
#define tSpec TBlockInfo< _SH >

/////////////////////////////////////////////////////
// TBlockBlender_RGBA8_SSE
template< uint32 _SH, eBlendingMode _BM >
class TBlockBlender_RGBA8_SSE
{
public:
    static void ProcessScanLineSSE( TBlock< _SH >*                     iBlockTop
                                  , TBlock< _SH >*                     iBlockBack
                                  , typename TBlock< _SH >::tPixelType iOpacity
                                  , const int                          iLine
                                  , const int                          iX1
                                  , const int                          iX2
                                  , const FPoint&                      iShift )
    {
        // Type Info
        using tPixelType                = typename TBlock< _SH >::tPixelType;
        using tPixelValue               = TPixelValue< _SH >;
        using tPixelProxy               = TPixelProxy< _SH >;
        using tPixelBase                = TPixelBase< _SH >;
        using tPixelInfo                = TPixelInfo< _SH >;
        using tBlockInfo                = TBlockInfo< _SH >;


        // Base ptrs for scanlines
        tPixelType* backPixelPtr    = iBlockBack->PixelPtr( iX1, iLine );
        tPixelType* topPixelPtr     = iBlockTop->PixelPtr( iX1 + iShift.x, iLine + iShift.y );
        uint8 alpha_index           = (uint8)tPixelInfo::RedirectedIndex( 3 );
        __m128  opacityf            = _mm_set_ps1( (float)iOpacity );
        __m128 max255f             = _mm_set_ps1( 255.f );
        const int op = iX2 - iX1;

        for( int i = 0; i < op; ++i )
        {
            __m128 backElementsf    = _mm_cvtepi32_ps( _mm_cvtepu8_epi32( _mm_loadu_si128( (const __m128i*)backPixelPtr ) ) );
            __m128 topElementsf     = _mm_cvtepi32_ps( _mm_cvtepu8_epi32( _mm_loadu_si128( (const __m128i*)topPixelPtr ) ) );
            __m128 backAlphaf = _mm_set_ps1( float( *( backPixelPtr + alpha_index ) ) );
            __m128 topAlphaf = _mm_div_ps( _mm_mul_ps( _mm_set_ps1( float( *( topPixelPtr + alpha_index ) ) ), opacityf ), max255f );
            __m128 alphaResultf = BlendAlphaSSE< _BM >::Compute( backAlphaf, topAlphaf );
            __m128 vcmp = _mm_cmpeq_ps( alphaResultf, _mm_setzero_ps());
            int mask = _mm_movemask_ps (vcmp);
            bool result = (mask == 0xf);
            __m128 var = result ? _mm_setzero_ps() : _mm_div_ps( _mm_mul_ps( topAlphaf, max255f ), alphaResultf );

            __m128 compute = BlendFuncSSE< _BM >::Compute( backElementsf, topElementsf );
            __m128 elementsResult = _mm_div_ps( _mm_add_ps( _mm_mul_ps( _mm_sub_ps( max255f, var ), backElementsf ), _mm_mul_ps( var, _mm_div_ps( _mm_add_ps( _mm_mul_ps( _mm_sub_ps( max255f, backAlphaf ), topElementsf ), _mm_mul_ps( backAlphaf, compute ) ), max255f ) ) ), max255f );


            __m128i y = _mm_cvtps_epi32( elementsResult );                     // Convert them to 32-bit ints
            y = _mm_packus_epi32(y, y);                                     // Pack down to 16 bits
            y = _mm_packus_epi16(y, y);                                     // Pack down to 8 bits
            *(uint32*)backPixelPtr = (uint32)_mm_cvtsi128_si32(y);           // Store the lower 32 bits
            __m128i alpha_result = _mm_cvtps_epi32( alphaResultf );             // Convert them to 32-bit ints
            alpha_result = _mm_packus_epi32(alpha_result, alpha_result);    // Pack down to 16 bits
            alpha_result = _mm_packus_epi16(alpha_result, alpha_result);    // Pack down to 8 bits
            uint32 alpha = (uint32)_mm_cvtsi128_si32(alpha_result);         // Store the lower 32 bits
            memcpy( backPixelPtr + alpha_index, &alpha, 1 );


            backPixelPtr    += tBlockInfo::_nf._pd;
            topPixelPtr     += tBlockInfo::_nf._pd;
        }
    }

    static void ProcessBlockSSE( TBlock< _SH >*                     iBlockTop
                               , TBlock< _SH >*                     iBlockBack
                               , typename TBlock< _SH >::tPixelType iOpacity
                               , const FRect&                       iROI
                               , const FPoint&                      iShift )
    {
        // Type Info
        using tPixelType                = typename TBlock< _SH >::tPixelType;
        using tPixelValue               = TPixelValue< _SH >;
        using tPixelProxy               = TPixelProxy< _SH >;
        using tPixelBase                = TPixelBase< _SH >;
        using tPixelInfo                = TPixelInfo< _SH >;
        using tBlockInfo                = TBlockInfo< _SH >;

        // Geom
        const int x1        = iROI.x;
        const int y1        = iROI.y;
        const int x2        = x1 + iROI.w;
        const int y2        = y1 + iROI.h;

        // Base ptrs for scanlines
        tPixelType* backPixelPtr;//     = iBlockBack->PixelPtr( iX1, iLine );
        tPixelType* topPixelPtr; //     = iBlockTop->PixelPtr( iX1 + iShift.x, iLine + iShift.y );
        uint8 alpha_index               = (uint8)tPixelInfo::RedirectedIndex( 3 );
        __m128  opacityf                = _mm_set_ps1( (float)iOpacity );
        __m128 max255f                  = _mm_set_ps1( 255.f );
        const int opx = x2 - x1;

        for( int j = y1; j < y2; ++j )
        {
            backPixelPtr    = iBlockBack->PixelPtr( x1, j );
            topPixelPtr     = iBlockTop->PixelPtr( x1 + iShift.x, j + iShift.y );
            for( int i = 0; i < opx; ++i )
            {
                __m128 backElementsf    = _mm_cvtepi32_ps( _mm_cvtepu8_epi32( _mm_loadu_si128( (const __m128i*)backPixelPtr ) ) );
                __m128 topElementsf     = _mm_cvtepi32_ps( _mm_cvtepu8_epi32( _mm_loadu_si128( (const __m128i*)topPixelPtr ) ) );
                __m128 backAlphaf = _mm_set_ps1( float( *( backPixelPtr + alpha_index ) ) );
                __m128 topAlphaf = _mm_div_ps( _mm_mul_ps( _mm_set_ps1( float( *( topPixelPtr + alpha_index ) ) ), opacityf ), max255f );
                __m128 alphaResultf = BlendAlphaSSE< _BM >::Compute( backAlphaf, topAlphaf );
                __m128 vcmp = _mm_cmpeq_ps( alphaResultf, _mm_setzero_ps());
                int mask = _mm_movemask_ps (vcmp);
                bool result = (mask == 0xf);
                __m128 var = result ? _mm_setzero_ps() : _mm_div_ps( _mm_mul_ps( topAlphaf, max255f ), alphaResultf );

                __m128 compute = BlendFuncSSE< _BM >::Compute( backElementsf, topElementsf );
                __m128 elementsResult = _mm_div_ps( _mm_add_ps( _mm_mul_ps( _mm_sub_ps( max255f, var ), backElementsf ), _mm_mul_ps( var, _mm_div_ps( _mm_add_ps( _mm_mul_ps( _mm_sub_ps( max255f, backAlphaf ), topElementsf ), _mm_mul_ps( backAlphaf, compute ) ), max255f ) ) ), max255f );


                __m128i y = _mm_cvtps_epi32( elementsResult );                  // Convert them to 32-bit ints
                y = _mm_packus_epi32(y, y);                                     // Pack down to 16 bits
                y = _mm_packus_epi16(y, y);                                     // Pack down to 8 bits
                *(uint32*)backPixelPtr = (uint32)_mm_cvtsi128_si32(y);          // Store the lower 32 bits
                __m128i alpha_result = _mm_cvtps_epi32( alphaResultf );         // Convert them to 32-bit ints
                alpha_result = _mm_packus_epi32(alpha_result, alpha_result);    // Pack down to 16 bits
                alpha_result = _mm_packus_epi16(alpha_result, alpha_result);    // Pack down to 8 bits
                uint32 alpha = (uint32)_mm_cvtsi128_si32(alpha_result);         // Store the lower 32 bits
                memcpy( backPixelPtr + alpha_index, &alpha, 1 );


                backPixelPtr    += tBlockInfo::_nf._pd;
                topPixelPtr     += tBlockInfo::_nf._pd;
            }
        }
    }

    static void Run( TBlock< _SH >*                     iBlockTop
                   , TBlock< _SH >*                     iBlockBack
                   , typename TBlock< _SH >::tPixelType iOpacity
                   , const FRect&                       iROI
                   , const FPoint&                      iShift
                   , const FPerformanceOptions&         iPerformanceOptions= FPerformanceOptions() )
    {
        if( iPerformanceOptions.desired_workers > 1 )
        {
            const int x1 = iROI.x;
            const int y1 = iROI.y;
            const int x2 = x1 + iROI.w;
            const int y2 = y1 + iROI.h;
            FThreadPool& global_pool = FGlobalThreadPool::Get();
            for( int y = y1; y < y2; ++y )
                global_pool.ScheduleJob( TBlockBlender_RGBA8_SSE< _SH, _BM >::ProcessScanLineSSE, iBlockTop, iBlockBack, iOpacity, y, x1, x2, iShift );
            global_pool.WaitForCompletion();
        }
        else
        {
            ProcessBlockSSE( iBlockTop, iBlockBack, iOpacity, iROI, iShift );
        }
    }
};

/////////////////////////////////////////////////////
// TBlockBlender_Imp
template< uint32        _SH,    // Format
          eBlendingMode _BM,    // Blending Mode
          uint32        _LH,    // Layout
          e_nm          _NM,    // Normalized
          bool          _DM >   // Decimal
class TBlockBlender_Imp< _SH,                // Format
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
                   , const FPerformanceOptions&                  iPerformanceOptions= FPerformanceOptions() )
    {
        TBlockBlender_RGBA8_SSE< _SH, _BM >::Run( iBlockTop
                                                , iBlockBack
                                                , iOpacity
                                                , iROI
                                                , iShift
                                                , iPerformanceOptions);
    }
};

/////////////////////////////////////////////////////
// Undefines
#undef tSpec

} // namespace ULIS