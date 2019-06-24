/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Data.Pixel.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once

#include <utility>
#include "ULIS/Data/ULIS.Data.Spec.h"
#include "ULIS/Maths/ULIS.Maths.Geometry.h"
#include "ULIS/Color/ULIS.Color.CColor.h"

namespace ULIS {


/////////////////////////////////////////////////////
// Defines
#define tSpec TBlockSpec< _SH >

/////////////////////////////////////////////////////
// TPixelLayout
template< int N >
struct TRedirector
{
    const uint8_t arr[ N ];
};


constexpr uint8 ParseLayoutRedirector_Imp_GetIndex( const char* iModel, const char* iLayout, bool iAlpha, int i )
{
    return  i < ::__coal__::strlen( iModel ) ? ::__coal__::indexof( iModel[i], iLayout, 0 ) : ::__coal__::indexof( 'A', iLayout, 0 );
}


template< int N, typename T, T... Nums >
constexpr TRedirector< N > ParseLayoutRedirector_Imp( const char* iModel, const char* iLayout, bool iAlpha, std::integer_sequence< T, Nums... > )
{
    return { ParseLayoutRedirector_Imp_GetIndex( iModel, iLayout, iAlpha, Nums ) ... };
}


template< int N >
constexpr TRedirector< N > ParseLayoutRedirector( const char* iModel, const char* iLayout, bool iAlpha )
{
    return  ParseLayoutRedirector_Imp< N >( iModel, iLayout, iAlpha, std::make_integer_sequence< int, N >() );
}


template< uint32_t _SH >
struct TPixelLayout
{
    static constexpr TRedirector< tSpec::_nf._rc > red = ParseLayoutRedirector< tSpec::_nf._rc >( kw_cm[ (int)tSpec::_nf._cm ], tSpec::_nf._cl, tSpec::_nf._ea == e_ea::khasAlpha );
};

template< uint32_t _SH >
constexpr TRedirector< tSpec::_nf._rc > TPixelLayout< _SH >::red;


/////////////////////////////////////////////////////
// TPixelTypeSelector
template< typename T > struct TNextPixelType { using _tUnderlyingNextPixelType = T; };
template<> struct TNextPixelType< uint8     >{ using _tUnderlyingNextPixelType = uint16; };
template<> struct TNextPixelType< uint16    >{ using _tUnderlyingNextPixelType = uint32; };
template<> struct TNextPixelType< uint32    >{ using _tUnderlyingNextPixelType = uint64; };
template<> struct TNextPixelType< float     >{ using _tUnderlyingNextPixelType = float; };
template<> struct TNextPixelType< double    >{ using _tUnderlyingNextPixelType = float; };
template< typename T > struct TPrevPixelType { using _tUnderlyingPrevPixelType = T; };
template<> struct TPrevPixelType< uint8     >{ using _tUnderlyingPrevPixelType = uint8; };
template<> struct TPrevPixelType< uint16    >{ using _tUnderlyingPrevPixelType = uint8; };
template<> struct TPrevPixelType< uint32    >{ using _tUnderlyingPrevPixelType = uint16; };
template<> struct TPrevPixelType< float     >{ using _tUnderlyingPrevPixelType = float; };
template<> struct TPrevPixelType< double    >{ using _tUnderlyingPrevPixelType = float; };
template< typename T > struct TPixelType { using _tUnderlyingPixelType = T; };
template< e_tp _TP > struct TPixelTypeSelector {};
#define ULIS_TYPE_SELECTOR_REPEAT( r, data, elem )                                                      \
    template<> class TPixelTypeSelector<  BOOST_PP_CAT( e_tp::k, elem ) > : public TPixelType< elem >, public TNextPixelType< elem >, public TPrevPixelType< elem > {};
BOOST_PP_SEQ_FOR_EACH( ULIS_TYPE_SELECTOR_REPEAT, void, ULIS_SEQ_TP )

/////////////////////////////////////////////////////
// TPixelBase
template< uint32_t _SH >
class TPixelInfo
{
public:
    // Typedef
    using tPixelType        = typename TPixelTypeSelector< tSpec::_nf._tp >::_tUnderlyingPixelType;
    using tNextPixelType    = typename TPixelTypeSelector< tSpec::_nf._tp >::_tUnderlyingNextPixelType;
    using tPrevPixelType    = typename TPixelTypeSelector< tSpec::_nf._tp >::_tUnderlyingPrevPixelType;

public:
    // Template API
    template< typename T >
    constexpr  T MaxT() const  { return  (T)tSpec::_nf._tm; }

    template< typename T >
    constexpr  T RangeT() const  { return  (T)tSpec::_nf._rm; }

public:
    // Public API
    inline int         Depth           ()  const   { return tSpec::_nf._pd;                    }
    inline double      MaxD            ()  const   { return MaxT< double >();                   }
    inline int64_t     MaxI            ()  const   { return MaxT< int64_t >();                  }
    inline double      RangeD          ()  const   { return RangeT< double >();                 }
    inline int64_t     RangeI          ()  const   { return RangeT< int64_t >();                }
    inline e_tp        Type            ()  const   { return tSpec::_nf._tp;                    }
    inline e_cm        ColorModel      ()  const   { return tSpec::_nf._cm;                    }
    inline e_ea        ExtraAlpha      ()  const   { return tSpec::_nf._ea;                    }
    inline bool        HasAlpha        ()  const   { return ExtraAlpha() == e_ea::khasAlpha;   }
    inline const char* ChannelLayout   ()  const   { return tSpec::_nf._cl;                    }
    inline e_nm        NormalMode      ()  const   { return tSpec::_nf._nm;                    }
    inline bool        IsNormalized    ()  const   { return NormalMode() == e_nm::knormalized; }
    inline bool        IsDecimal       ()  const   { return tSpec::_nf._dm;                    }
    inline int         NumChannels     ()  const   { return tSpec::_nf._rc;                    }
    inline int         ColorChannels   ()  const   { return tSpec::_nf._nc;                    }
};

/////////////////////////////////////////////////////
// TPixelValue
template< uint32_t _SH >
class TPixelValue final : public TPixelInfo< _SH >
{
public:
    // Typedef
    using tPixelType = typename TPixelInfo< _SH >::tPixelType;

public:
    // Public API
    tPixelType&  operator[]( uint8 i ) { return m[ i ]; }
    const  tPixelType&  operator[]( uint8 i )  const { return m[ i ] }

private:
    // Private Data
    tPixelType m[ tSpec::_nf._rc ];
};

/////////////////////////////////////////////////////
// TPixelProxy
template< uint32_t _SH >
class TPixelProxy final : public TPixelInfo< _SH >
{
public:
    // Typedef
    using tPixelType = typename TPixelInfo< _SH >::tPixelType;

public:
    // Public API
    tPixelType&  operator[]( uint8 i ) { return m[i]; }
    const  tPixelType&  operator[]( uint8 i )  const { return m[i]; }

private:
    // Private Data
    tPixelType* m;
};

/////////////////////////////////////////////////////
// Undefines
#undef tSpec


} // namespace ULIS

