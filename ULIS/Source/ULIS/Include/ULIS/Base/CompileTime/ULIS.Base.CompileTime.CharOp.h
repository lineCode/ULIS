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
// Compile-Time Constexpr cpp0x compliant Char Operations


/* check if char is a digit at compile time */
constexpr bool
is_digit( char c )
{
    return c >= '0' && c <= '9';
}


/* convert cstring to int at compile time, implementation, fail if not a number */
constexpr int
stoi_impl( const char* s, int value = 0 )
{
    return *s ? is_digit( *s ) ? stoi_impl( s+1, (*s-'0') + value*10 ) : -1 : value;
}


/* convert cstring to int at compile time */
constexpr int
stoi( const char* s )
{
    return stoi_impl( s );
}


/* compute cstring length at compile time */
constexpr int
strlen( const char* str )
{
    return *str ? 1 + strlen(str + 1) : 0;
}


/* compare two cstrings at compile time */
constexpr bool
streq( char const * a, char const * b )
{
    return *a == *b && ( *a == '\0' || streq( a + 1, b + 1 ) );
}


/* check if cstring is a number at compile time */
constexpr bool
is_number( const char* s )
{
    return *s ? is_digit( *s ) ? is_number( s+1 ) : false : true;
}


/* find index of word occurence from start in cstring at compile time */
constexpr int
indexof( const char* word, const char* str, int from = 0 )
{
    int ret = -1;
    bool exit = false;
    for( int i = from; i <= strlen( str ); ++i ) {
        if( exit ) break;
        for( int j = 0; j <= strlen( word ); ++j ) {
            if( str[i+j] != word[j] )
                break;

            if( j == strlen( word ) - 1 )
            {
                ret = i;
                exit = true;
                break;
            }
        }
    }
    return ret;
}

/* short version ( breaks recursion depth limit )*/
constexpr int indof( cstr w, cstr s, int f=0, int q=0 )
{
    return s[f+q] ? w[q] ? s[f+q] == w[q] ? q == strlen( w ) - 1 ? f : indof( w, s, f, q+1 ) : indof( w, s, f, q+1 ) : indof( w, s, f+1 ) : -1;
}

//constexpr const int ct_char_index_without_digits ( char c, const char* s ) { int cind = 0; int lpos = 0; while(1) { if( s[cind] == c ) { break; } if( !is_digit( s[cind] ) ) { ++lpos; } ++cind; } return lpos; }


} // namespace _CT
} // namespace ULIS

