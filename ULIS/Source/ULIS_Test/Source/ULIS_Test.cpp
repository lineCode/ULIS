/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS_Test.cpp
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#include <ULIS_CORE>
#include <cstdio>
#include <cstdlib>

template< uint32_t _SH >
void
Process_Imp( ::ULIS::TBlock< _SH >* iBlock )
{
    return;
}


void
Process( ::ULIS::IBlock* iBlock )
{
    if( !iBlock ) return;

    uint32_t id = iBlock->Id();
    switch( id )
    {
        #define ULIS_REG_SWITCH_OP( z, n, data ) case ::ULIS::ulis_types_reg[ n ]: Process_Imp< ::ULIS::ulis_types_reg[ n ] >( (::ULIS::TBlock< ::ULIS::ulis_types_reg[ n ] >*)iBlock ); break;
        ULIS_REPEAT( ULIS_REG_SIZE, ULIS_REG_SWITCH_OP, void )
        #undef ULIS_REG_SWITCH_OP
        default: return;
    }
}


inline __m128i _mm_mullo_epi8(__m128i a, __m128i b)
{
    __m128i zero    = _mm_setzero_si128();
    __m128i Alo     = _mm_unpacklo_epi8(a, zero);
    __m128i Ahi     = _mm_unpackhi_epi8(a, zero);
    __m128i Blo     = _mm_unpacklo_epi8(b, zero);
    __m128i Bhi     = _mm_unpackhi_epi8(b, zero);
    __m128i Clo     = _mm_mullo_epi16(Alo, Blo);
    __m128i Chi     = _mm_mullo_epi16(Ahi, Bhi);
    __m128i maskLo  = _mm_set_epi8(0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 14, 12, 10, 8, 6, 4, 2, 0);
    __m128i maskHi  = _mm_set_epi8(14, 12, 10, 8, 6, 4, 2, 0, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80);
    __m128i C       = _mm_or_si128(_mm_shuffle_epi8(Clo, maskLo), _mm_shuffle_epi8(Chi, maskHi));
     return C;
}


void printvec( const char* title, const ::ULIS::FVectorSIMD128& iVec )
{
    std::cout << title << ": [";
    for( int i = 0; i < 16; ++i )
        std::cout << (int)iVec.u8[i] << ",";
    std::cout << "]" << std::endl;
}


int main()
{
    using namespace ::ULIS;

    FVectorSIMD128 vec;
    for( int i = 0; i < 16; ++i ) vec.u8[i] = i;

    FVectorSIMD128 mul;
    mul.m128i = _mm_set1_epi8( 16 );

    FVectorSIMD128 res;
    res.m128i = _mm_mullo_epi8( vec.m128i, mul.m128i );

    return 0;
}

