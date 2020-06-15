// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS3
*__________________
*
* @file         Test.cpp
* @author       Clement Berthaud
* @brief        Test application for ULIS3.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include <ULIS3>
#include <immintrin.h>
#include <vectorclass.h>

using namespace ::ul3;

int
main() {
    uint8 val1 = 128;
    uint8 val2 = 255;
    uint8 src[16];
    uint8 bdp[16];
    for( int i = 0; i < 16; ++i ) {
        src[i] = 127;
        bdp[i] = 0;
    }

    uint8 aid = 3;
    uint8 ard[4];
    ard[0] = aid;
    ard[1] = aid + 4;
    ard[2] = aid + 8;
    ard[3] = aid + 12;
    __m128i alpha_mask = _mm_set_epi8( ard[3], ard[3], ard[3], ard[3]
                                     , ard[2], ard[2], ard[2], ard[2]
                                     , ard[1], ard[1], ard[1], ard[1]
                                     , ard[0], ard[0], ard[0], ard[0] );
    uint8 alpha_s0 = 128;
    uint8 alpha_s1 = 128;
    uint8 alpha_b0 = 128;
    uint8 alpha_b1 = 128;
    uint8 alpha_c0 = ( alpha_s0 + alpha_b0 ) - ConvType< uint16, uint8 >( alpha_s0 * alpha_b0 );
    uint8 alpha_c1 = ( alpha_s1 + alpha_b1 ) - ConvType< uint16, uint8 >( alpha_s1 * alpha_b1 );
    uint8 var0 = alpha_c0 == 0 ? 0 : ( alpha_s0 * 0xFF ) / alpha_c0;
    uint8 var1 = alpha_c1 == 0 ? 0 : ( alpha_s1 * 0xFF ) / alpha_c1;
    const __m128i var = _mm_set_epi16( var1, var1, var1, var1, var0, var0, var0, var0 );
    const __m128i cb = _mm_set_epi16( alpha_b1, alpha_b1, alpha_b1, alpha_b1, alpha_b0, alpha_b0, alpha_b0, alpha_b0 );
    const __m128i cs = _mm_set_epi16( var1, var1, var1, var1, var0, var0, var0, var0 );
    __m128i src_chan = _mm_cvtepu8_epi16( _mm_loadu_si128( reinterpret_cast< const __m128i* >( src ) ) );
    __m128i bdp_chan = _mm_cvtepu8_epi16( _mm_loadu_si128( reinterpret_cast< const __m128i* >( bdp ) ) );

    __m128i termA = _mm_sub_epi16( _mm_set1_epi16( 0xFF ), var );
    __m128i termB = _mm_mullo_epi16( termA, cb );
    __m128i termC = _mm_srli_epi16( _mm_adds_epu16( _mm_adds_epu16( termB, _mm_set1_epi16( 1 ) ), _mm_srli_epi16( termB, 8 ) ), 8 );

    //return ( 1.f - iVar ) * iCb + iVar * ( ( 1.f - iAb ) * iCs + iAb * iCr );

    int ghi = 010;

    /*
    const __m128i maskLo    = _mm_set_epi8(0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 14, 12, 10, 8, 6, 4, 2, 0);
    const __m128i maskHi    = _mm_set_epi8(14, 12, 10, 8, 6, 4, 2, 0, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80);
    __m128i src_chan        = _mm_loadu_si128( reinterpret_cast< const __m128i* >( src ) );
    __m128i bdp_chan        = _mm_loadu_si128( reinterpret_cast< const __m128i* >( bdp ) );
    __m128i src_alpha_LO    = _mm_cvtepu8_epi16( _mm_shuffle_epi8( src_chan, alpha_mask ) );
    __m128i bdp_alpha_LO    = _mm_cvtepu8_epi16( _mm_shuffle_epi8( bdp_chan, alpha_mask ) );
    __m128i alpha_addo16    = _mm_add_epi16( src_alpha_LO, bdp_alpha_LO );
    __m128i alpha_mullo16   = _mm_mullo_epi16( src_alpha_LO, bdp_alpha_LO );
    __m128i alpha_mullo8    = _mm_srli_epi16( _mm_adds_epu16( _mm_adds_epu16( alpha_mullo16, _mm_set1_epi16( 1 ) ), _mm_srli_epi16( alpha_mullo16, 8 ) ), 8 );
    __m128i alpha_comp16    = _mm_sub_epi16( alpha_addo16, alpha_mullo8 );
    __m128i eq = _mm_cmpeq_epi16( alpha_comp16, _mm_setzero_si128() );
    int mask = _mm_movemask_epi8( eq );
    __m128i var = _mm_cvtepi32_epi16( _mm_cvtps_epi32( 

    Vec4f( _mm_cvtepi32_ps( _mm_cvtepu8_epi32( _mm_loadu_si128( reinterpret_cast< const __m128i* >( src ) ) ) ) ) / 255.f;
    */

    auto dummy = 0;

    //Vec4f var           = select( alpha_comp == 0.f, 0.f, alpha_src / alpha_comp );

    //__m128i C = _mm_or_si128( _mm_shuffle_epi8( Clodown, maskLo ), _mm_shuffle_epi8( Chidown, maskHi ) );

    /*
    ULIS3_FORCEINLINE Vec4f ULIS3_VECTORCALL AlphaNormalSSEF( Vec4f iCs, Vec4f iCb ) {
    return ( iCb + iCs ) - ( iCb * iCs );
    }
    */


    /*
    ULIS3_FORCEINLINE Vec4f ComposeSSEF( Vec4f iCs, Vec4f iCb, Vec4f iAb, Vec4f iVar, Vec4f iCr ) {
        return ( 1.f - iVar ) * iCb + iVar * ( ( 1.f - iAb ) * iCs + iAb * iCr );
    }
    */


    return  0;
}

