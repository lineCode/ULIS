/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Base.VectorSIMD.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once

#include <immintrin.h>
#include "ULIS/Base/ULIS.Base.BaseTypes.h"
#include "ULIS/Base/ULIS.Base.Platform.h"

namespace ULIS {

/////////////////////////////////////////////////////
// FVectorSIMD128_8bit
struct alignas( 16 ) FVectorSIMD128_8bit
{
    // Data
    union {
        uint8   u8[16];
        uint16  u16[8];
        __m128i m128i;
    };

    // Construction
    ULIS_FORCEINLINE FVectorSIMD128_8bit()
    {}

    // Makers
    ULIS_FORCEINLINE static FVectorSIMD128_8bit Zero() {
        FVectorSIMD128_8bit tmp;
        tmp.SetZero();
        return  tmp;
    }

    ULIS_FORCEINLINE static FVectorSIMD128_8bit Max() {
        FVectorSIMD128_8bit tmp;
        tmp.Set1( 255 );
        return  tmp;
    }

    // Load / Set
    ULIS_FORCEINLINE void Load( const uint8* mem ) {
        m128i = _mm_loadu_si128( (const __m128i*)mem );
    }

    ULIS_FORCEINLINE void SetZero() {
        m128i = _mm_setzero_si128();
    }

    ULIS_FORCEINLINE void Set1( uint8 a ) {
        m128i = _mm_set1_epi8( a );
    }

    ULIS_FORCEINLINE void Set2( uint8 e0, uint8 e1 ) {
        m128i = _mm_set_epi8( e0, e0, e0, e0, e0, e0, e0, e0, e1, e1, e1, e1, e1, e1, e1, e1 );
    }

    ULIS_FORCEINLINE void Set4( uint8 e0, uint8 e1, uint8 e2, uint8 e3 ) {
        m128i = _mm_set_epi8( e0, e0, e0, e0, e1, e1, e1, e1, e2, e2, e2, e2, e3, e3, e3, e3 );
    }

    ULIS_FORCEINLINE void Set8( uint8 e0, uint8 e1, uint8 e2, uint8 e3, uint8 e4, uint8 e5, uint8 e6, uint8 e7 ) {
        m128i = _mm_set_epi8( e0, e0, e1, e1, e2, e2, e3, e3, e4, e4, e5, e5, e6, e6, e7, e7 );
    }

    ULIS_FORCEINLINE void Set16( uint8 e0, uint8 e1, uint8 e2,  uint8 e3,  uint8 e4,  uint8 e5,  uint8 e6,  uint8 e7
                    , uint8 e8, uint8 e9, uint8 e10, uint8 e11, uint8 e12, uint8 e13, uint8 e14, uint8 e15 ) {
        m128i = _mm_set_epi8( e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15 );
    }

    // Operators Imp
    ULIS_FORCEINLINE FVectorSIMD128_8bit AdditionSafe( __m128i i ) {
        FVectorSIMD128_8bit tmp;
        tmp.m128i = _mm_add_epi8( m128i, i );
        return  tmp;
    }

    ULIS_FORCEINLINE FVectorSIMD128_8bit AdditionSat( __m128i i )  {
        FVectorSIMD128_8bit tmp;
        tmp.m128i = _mm_adds_epu8( m128i, i );
        return  tmp;
    }

    ULIS_FORCEINLINE FVectorSIMD128_8bit SubtractionSafe( __m128i i ) {
        FVectorSIMD128_8bit tmp;
        tmp.m128i = _mm_sub_epi8( m128i, i );
        return  tmp;
    }

    ULIS_FORCEINLINE FVectorSIMD128_8bit SubtractionSat( __m128i i )  {
        FVectorSIMD128_8bit tmp;
        tmp.m128i = _mm_subs_epu8( m128i, i );
        return  tmp;
    }

    // Operators
    ULIS_FORCEINLINE FVectorSIMD128_8bit operator+( uint8 i ) { return  AdditionSat( _mm_set1_epi8( i ) ); }
    ULIS_FORCEINLINE FVectorSIMD128_8bit operator-( uint8 i ) { return  SubtractionSat( _mm_set1_epi8( i ) ); }
    ULIS_FORCEINLINE FVectorSIMD128_8bit operator+( __m128i i ) { return  AdditionSat( i ); }
    ULIS_FORCEINLINE FVectorSIMD128_8bit operator-( __m128i i ) { return  SubtractionSat( i ); }
    ULIS_FORCEINLINE FVectorSIMD128_8bit operator+( FVectorSIMD128_8bit i ) { return  AdditionSat( i.m128i ); }
    ULIS_FORCEINLINE FVectorSIMD128_8bit operator-( FVectorSIMD128_8bit i ) { return  SubtractionSat( i.m128i ); }
};

/////////////////////////////////////////////////////
// FVectorSIMD128_Dual8bit
struct alignas( 16 ) FVectorSIMD128_Dual8bit
{
    FVectorSIMD128_8bit lo;
    FVectorSIMD128_8bit hi;
};

} // namespace ULIS
