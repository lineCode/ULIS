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
namespace nCT {

/////////////////////////////////////////////////////
// Compile time char operations
constexpr
const bool
ct_is_digit( char c )
{
    return c <= '9' && c >= '0';
}


constexpr
const int
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



constexpr const int ct_strlen( const char* str )
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
    int length_word = ct_strlen( word );
    int remaining_length = ct_strlen( str ) - from;
    int lenght_str = ct_strlen( str );
    bool exit = length_word > remaining_length;
    int ret = -1;

    if( !exit )
    {
        int indexof_word_occurence_start = 0;
        int current_word_index = 0;
        for( int current_str_index = from; current_str_index <= lenght_str; ++current_str_index )
        {
            const char char_word = word[current_word_index];
            const char char_str = str[current_str_index];

            if( current_word_index == length_word )
            {
                ret = indexof_word_occurence_start;
                break;
            }

            if( char_word == char_str )
            {
                if( current_word_index == 0 )
                    indexof_word_occurence_start = current_str_index;

                ++current_word_index;
            }
            else
            {
                current_word_index = 0;
            }
        }
    }

    return ret;
}


//constexpr const int ct_char_index_without_digits ( char c, const char* s ) { int cind = 0; int lpos = 0; while(1) { if( s[cind] == c ) { break; } if( !ct_is_digit( s[cind] ) ) { ++lpos; } ++cind; } return lpos; }


} // namespace nCT
} // namespace ULIS

