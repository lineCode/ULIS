/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Imaging.CompileTime.BlockID.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once

#include "ULIS/Base/ULIS.Base.ConstStr.h"

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/tuple/to_seq.hpp>

namespace ULIS {
/////////////////////////////////////////////////////
// Keys
#define ULIS_KEYS( ... ) ( __VA_ARGS__ )
#define ULIS_KEYWORDS_CAT( cat )            kw##cat
#define ULIS_ENUM_CAT( cat )                e##cat
#define ULIS_MAKE_KEYWORD( r, data, elem )  BOOST_PP_STRINGIZE( elem )
#define ULIS_MAKE_ENUM( r, data, elem )     BOOST_PP_CAT( k, elem ),

#define ULIS_KEYS_TO_KEYWORDS( cat, keys )                                              \
    constexpr const char* ULIS_KEYWORDS_CAT( cat )[] = {                                \
        BOOST_PP_SEQ_FOR_EACH( ULIS_MAKE_KEYWORD, 0, BOOST_PP_TUPLE_TO_SEQ( keys ) )    \
    };
#define ULIS_KEYS_TO_ENUM( cat, keys )                                                  \
    enum class ULIS_ENUM_CAT( cat ) : char {                                            \
        BOOST_PP_SEQ_FOR_EACH( ULIS_MAKE_ENUM, 0, BOOST_PP_TUPLE_TO_SEQ( keys ) )       \
    };

#define ULIS_KEYS_DATA_TYPE ULIS_KEYS( uint8, uint16, uint32, int8, int16, int32, float, double )
ULIS_KEYS_TO_KEYWORDS(  DataType, ULIS_KEYS_DATA_TYPE )
ULIS_KEYS_TO_ENUM(      DataType, ULIS_KEYS_DATA_TYPE )

#define ULIS_KEYS_ALL ULIS_KEYS( ULIS_KEYS_DATA_TYPE )


/////////////////////////////////////////////////////
// BlockInfo
struct BlockInfo
{
    const  eDataType        type                    ;
    const  uint16           pixel_depth_bits        ;
    const  uint8            num_channels            ;
    const  uint8            num_channels_noalpha    ;
    const  char*            channels_layout_str     ;
    const  uint32           channels_layout_hash    ;
    const  char*            model_str               ;
    const  uint32           model_hash              ;
    const  char*            model_noalpha_str       ;
    const  uint32           model_noalpha_hash      ;
    const  bool             has_alpha               ;
    const  bool             sub_byte                ;
    const  bool             normalized              ;
    const  bool             decimal                 ;
    const  bool             signed_type             ;
};


/////////////////////////////////////////////////////
// ParseSpecStr
template< int N >
static constexpr const BlockInfo ParseSpecStr( const_str< N > spec_str )
{
    return  { eDataType::kuint8
            , 32
            , 4
            , 3
            , "R8G8B8A8"
            , 0
            , "RGBA"
            , 0
            , "RGB"
            , 0
            , true
            , false
            , false
            , false
            , false };
}


/////////////////////////////////////////////////////
// TBlockSpec
template< uint32 > class TBlock;
template< uint32 > struct TBlockSpec {};
#define ULIS_DECLARE_STATIC_BLOCK_SPEC( spec )                                          \
    static constexpr const uint32 Spec_##spec = CONST_STR( #spec ).CRC32();             \
    template<> struct TBlockSpec< Spec_##spec > {                                       \
        static constexpr const char* spec_str = #spec;                                  \
        static constexpr const uint32 spec_hash = Spec_##spec;                          \
        static constexpr const BlockInfo nfo = ParseSpecStr( CONST_STR( #spec ) );      \
    };                                                                                  \
    typedef TBlock< Spec_##spec > F##spec;


} // namespace ULIS

