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
#define tSpec       TBlockSpec< _SH >
#define tLayout     TPixelLayout< _SH >

/////////////////////////////////////////////////////
// TRedirector
/* A simple array for storing the redirection index */
template< int N > struct TRedirector { const uint8_t arr[ N ]; };

/////////////////////////////////////////////////////
// Layout Redirection Parsing Utility
constexpr uint8 ParseLayoutRedirector_Imp_GetIndex( const char* iModel, const char* iLayout, bool iAlpha, int i )
{
    /* Layout orded */
    //return  i < ::__coal__::strlen( iModel ) ? ::__coal__::indexof( iModel[i], iLayout, 0 ) : ::__coal__::indexof( 'A', iLayout, 0 );

    /* Alpha first */
    //return  iAlpha ? i == 0 ? ::__coal__::indexof( 'A', iLayout, 0 ) : ::__coal__::indexof( iModel[i-1], iLayout, 0 ) : ::__coal__::indexof( iModel[i-1], iLayout, 0 );

    /* Alpha last */
    return  iAlpha ? i == ::__coal__::strlen( iModel ) ? ::__coal__::indexof( 'A', iLayout, 0 ) : ::__coal__::indexof( iModel[i], iLayout, 0 ) : ::__coal__::indexof( iModel[i], iLayout, 0 );
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

/////////////////////////////////////////////////////
// TLayout
/* Pixel Layout obtained from hash, holding the Redirector */
template< uint32_t _SH >
struct TPixelLayout
{
    static constexpr TRedirector< tSpec::_nf._rc > red = ParseLayoutRedirector< tSpec::_nf._rc >( kw_cm[ (int)tSpec::_nf._cm ], tSpec::_nf._cl, tSpec::_nf._ea == e_ea::khasAlpha );
};

/* Post definition of template redirector 'red' member to ensure it has a location in memory for external use */
template< uint32_t _SH > constexpr TRedirector< tSpec::_nf._rc > TPixelLayout< _SH >::red;


/////////////////////////////////////////////////////
// TPixelTypeSelector
/* Shenanigans for type operations */
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
// TPixelInfo
/* Basically a wrapper around FSpec, adding type info for ease of use */
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
    constexpr  tPixelType       Max()       const  { return  (tPixelType)tSpec::_nf._tm; }
    constexpr  tNextPixelType   Range()     const  { return  (tNextPixelType)tSpec::_nf._rm; }

public:
    // Public API
    inline int         Depth           ()  const   { return tSpec::_nf._pd;                     }
    inline e_tp        Type            ()  const   { return tSpec::_nf._tp;                     }
    inline e_cm        ColorModel      ()  const   { return tSpec::_nf._cm;                     }
    inline e_ea        ExtraAlpha      ()  const   { return tSpec::_nf._ea;                     }
    inline bool        HasAlpha        ()  const   { return ExtraAlpha() == e_ea::khasAlpha;    }
    inline const char* ChannelLayout   ()  const   { return tSpec::_nf._cl;                     }
    inline e_nm        NormalMode      ()  const   { return tSpec::_nf._nm;                     }
    inline bool        IsNormalized    ()  const   { return NormalMode() == e_nm::knormalized;  }
    inline bool        IsDecimal       ()  const   { return tSpec::_nf._dm;                     }
    inline int         NumChannels     ()  const   { return tSpec::_nf._rc;                     }
    inline int         ColorChannels   ()  const   { return tSpec::_nf._nc;                     }
    inline int         RedirectedIndex ( int i )  const   { return tLayout::red.arr[i];    }
};

/////////////////////////////////////////////////////
// TPixelBase
template< typename T, uint32_t _SH >
class TPixelBase : public TPixelInfo< _SH >
{
    typedef TPixelInfo< _SH > tSuperClass;

public:
    // Typedef
    using tPixelType = typename tSuperClass::tPixelType;

public:
    // Public API
    inline         tPixelType&     GetRaw( uint8 i )                       { return m[ i ]; }
    inline const   tPixelType&     GetRaw( uint8 i )               const   { return m[ i ]; }
    inline         tPixelType&     GetComponent( uint8 i )                 { return m[ tLayout::red.arr[i] ]; }
    inline const   tPixelType&     GetComponent( uint8 i )         const   { return m[ tLayout::red.arr[i] ]; }
    inline         tPixelType&     GetComponent( uint8 i, tPixelType iValue )                 { m[ tLayout::red.arr[i] ] = iValue; }
    inline const   tPixelType&     GetComponent( uint8 i, tPixelType iValue )         const   { m[ tLayout::red.arr[i] ] = iValue; }
    inline         tPixelType&     operator[]( uint8 i )                   { return m[ tLayout::red.arr[i] ]; }
    inline const   tPixelType&     operator[]( uint8 i )           const   { return m[ tLayout::red.arr[i] ]; }
    inline         tPixelType      Alpha()                         const   { return tSpec::_nf._ea == e_ea::khasAlpha ? m[ tLayout::red.arr[ tSpec::_nf._nc ] ] : Max(); }
    inline         void            SetAlpha( tPixelType iValue )           { if(    tSpec::_nf._ea == e_ea::khasAlpha ) m[ tLayout::red.arr[ tSpec::_nf._nc ] ] = iValue; }

protected:
    // Protected Data
    T m[ tSpec::_nf._rc ];
};

/////////////////////////////////////////////////////
// TPixelAcessor
template< typename T, uint32_t _SH, e_cm _CM >
class TPixelAcessor : public TPixelBase< T, _SH >
{
    typedef TPixelBase< T, _SH > tSuperClass;

public:
    // Typedef
    using tPixelType = typename tSuperClass::tPixelType;

public:
    // Public API
};

#define ULIS_SPEC_PIXEL_ACCESSOR_START( iCm )                       \
    template< typename T, uint32_t _SH >                            \
    class TPixelAcessor< T, _SH, BOOST_PP_CAT( e_cm::k, iCm ) >     \
        : public TPixelBase< T, _SH > {                             \
    typedef TPixelBase< T, _SH > tSuperClass;                       \
    public: using tPixelType = typename tSuperClass::tPixelType;
#define ULIS_SPEC_PIXEL_ACCESSOR_END    };

#define ULIS_SPEC_COMPONENT( iComp, iIndex )                                                                                \
    inline          tPixelType&     iComp       ()                      { return tSuperClass::GetComponent( iIndex );    }  \
    inline  const   tPixelType&     iComp       () const                { return tSuperClass::GetComponent( iIndex );    }  \
    inline          tPixelType      Get##iComp  ()                      { return tSuperClass::GetComponent( iIndex );    }  \
    inline  void                    Set##iComp  ( tPixelType iValue )   { tSuperClass::SetComponent( iIndex, iValue );   }

ULIS_SPEC_PIXEL_ACCESSOR_START( G )
    ULIS_SPEC_COMPONENT( G,     0 )
    ULIS_SPEC_COMPONENT( Gray,  0 )
ULIS_SPEC_PIXEL_ACCESSOR_END

ULIS_SPEC_PIXEL_ACCESSOR_START( RGB )
    ULIS_SPEC_COMPONENT( Red,   0 )
    ULIS_SPEC_COMPONENT( Green, 1 )
    ULIS_SPEC_COMPONENT( Blue,  2 )
    ULIS_SPEC_COMPONENT( R,     0 )
    ULIS_SPEC_COMPONENT( G,     1 )
    ULIS_SPEC_COMPONENT( B,     2 )
ULIS_SPEC_PIXEL_ACCESSOR_END

ULIS_SPEC_PIXEL_ACCESSOR_START( HSL )
    ULIS_SPEC_COMPONENT( Hue,           0 )
    ULIS_SPEC_COMPONENT( Saturation,    1 )
    ULIS_SPEC_COMPONENT( Lightness,     2 )
    ULIS_SPEC_COMPONENT( H,             0 )
    ULIS_SPEC_COMPONENT( S,             1 )
    ULIS_SPEC_COMPONENT( L,             2 )
ULIS_SPEC_PIXEL_ACCESSOR_END

ULIS_SPEC_PIXEL_ACCESSOR_START( HSV )
    ULIS_SPEC_COMPONENT( Hue,           0 )
    ULIS_SPEC_COMPONENT( Saturation,    1 )
    ULIS_SPEC_COMPONENT( Value,         2 )
    ULIS_SPEC_COMPONENT( H,             0 )
    ULIS_SPEC_COMPONENT( S,             1 )
    ULIS_SPEC_COMPONENT( V,             2 )
ULIS_SPEC_PIXEL_ACCESSOR_END

ULIS_SPEC_PIXEL_ACCESSOR_START( CMYK )
    ULIS_SPEC_COMPONENT( Cyan,      0 )
    ULIS_SPEC_COMPONENT( Magenta,   1 )
    ULIS_SPEC_COMPONENT( Yellow,    2 )
    ULIS_SPEC_COMPONENT( Key,       3 )
    ULIS_SPEC_COMPONENT( Black,     3 )
    ULIS_SPEC_COMPONENT( C,         0 )
    ULIS_SPEC_COMPONENT( M,         1 )
    ULIS_SPEC_COMPONENT( Y,         2 )
    ULIS_SPEC_COMPONENT( K,         3 )
ULIS_SPEC_PIXEL_ACCESSOR_END

ULIS_SPEC_PIXEL_ACCESSOR_START( YUV )
    ULIS_SPEC_COMPONENT( Y, 0 )
    ULIS_SPEC_COMPONENT( U, 1 )
    ULIS_SPEC_COMPONENT( V, 2 )
ULIS_SPEC_PIXEL_ACCESSOR_END

ULIS_SPEC_PIXEL_ACCESSOR_START( Lab )
    ULIS_SPEC_COMPONENT( L, 0 )
    ULIS_SPEC_COMPONENT( a, 1 )
    ULIS_SPEC_COMPONENT( b, 2 )
ULIS_SPEC_PIXEL_ACCESSOR_END

ULIS_SPEC_PIXEL_ACCESSOR_START( XYZ )
    ULIS_SPEC_COMPONENT( X, 0 )
    ULIS_SPEC_COMPONENT( Y, 1 )
    ULIS_SPEC_COMPONENT( Z, 2 )
ULIS_SPEC_PIXEL_ACCESSOR_END

/////////////////////////////////////////////////////
// TPixelValue
template< uint32_t _SH >
class TPixelValue final : public TPixelAcessor< typename TPixelInfo< _SH >::tPixelType, _SH, tSpec::_nf._cm >
{
    typedef TPixelAcessor< typename TPixelInfo< _SH >::tPixelType, _SH, tSpec::_nf._cm > tSuperClass;

public:
    // Typedef
    using tPixelType = typename tSuperClass::tPixelType;

public:
    // Construction / Destruction
    TPixelValue()
    {
        for( int i = 0; i < tSpec::_nf._rc; ++i )
            tSuperClass::m[i] = (tPixelType)0;
    }
};

/////////////////////////////////////////////////////
// TPixelProxy
template< uint32_t _SH >
class TPixelProxy final : public TPixelBase< typename TPixelInfo< _SH >::tPixelType*, _SH >
{
    typedef TPixelBase< typename TPixelInfo< _SH >::tPixelType*, _SH > tSuperClass;

public:
    // Typedef
    using tPixelType = typename tSuperClass::tPixelType;

public:
    // Construction / Destruction
    TPixelProxy()
    {
    }
};

/////////////////////////////////////////////////////
// Undefines
#undef tSpec
#undef tLayout


} // namespace ULIS

