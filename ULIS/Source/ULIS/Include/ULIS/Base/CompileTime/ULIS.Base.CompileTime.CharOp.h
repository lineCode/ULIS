/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Base.CompileTime.CharOp.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once


namespace ULIS {
namespace _CT {


/////////////////////////////////////////////////////
// Compile-Time Char Operations


constexpr
bool
ct_is_digit( char c )
{
    return c >= '0' && c <= '9';
}


constexpr
int
ct_stoi_impl( const char* s, int value = 0 )
{
    return *s ? ct_is_digit( *s ) ? ct_stoi_impl( s+1, (*s-'0') + value*10 ) : throw "error" : value;
}


constexpr
const int
ct_stoi( const char* s )
{
    return ct_stoi_impl( s );
}



constexpr
const int
ct_strlen( const char* str )
{
    return *str ? 1 + ct_strlen(str + 1) : 0;
}


constexpr
const bool
ct_strings_equal( char const * a, char const * b )
{
    return *a == *b && ( *a == '\0' || ct_strings_equal( a + 1, b + 1 ) );
}


constexpr
const int
ct_indexof( const char* word, const char* str, int from = 0 )
{
    int ret = -1;
    bool exit = false;
    for( int i = from; i <= ct_strlen( str ); ++i ) {
        if( exit ) break;
        for( int j = 0; j <= ct_strlen( word ); ++j ) {
            if( str[i+j] != word[j] )
                break;

            if( j == ct_strlen( word ) - 1 )
            {
                ret = i;
                exit = true;
                break;
            }
        }
    }
    return ret;
}


//constexpr const int ct_char_index_without_digits ( char c, const char* s ) { int cind = 0; int lpos = 0; while(1) { if( s[cind] == c ) { break; } if( !ct_is_digit( s[cind] ) ) { ++lpos; } ++cind; } return lpos; }


} // namespace _CT
} // namespace ULIS

