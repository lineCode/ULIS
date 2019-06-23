/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Data.Block.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once

#include "ULIS/Data/ULIS.Data.Spec.h"

namespace ULIS {


/////////////////////////////////////////////////////
// Defines
#define tSpec TBlockSpec< _SH >
#define tData TBlockData< _SH >

/////////////////////////////////////////////////////
// TBlockDataInfo
    /*
template< uint32_t _SH , typename T >
struct TTypeInfo
{
    static constexpr const char*    type_name() { return typeid( T ).name(); } // Type Name as c-string
    static constexpr const T        type_max    = std::numeric_limits< T >::max();
    static constexpr const T        type_min    = std::numeric_limits< T >::min();
    static constexpr const T        range_max   = tSpec::_nm: ? (T)1 : type_max;
    static constexpr const T        range_min   = tSpec::_nm: ? (T)0 : type_max;
};
*/

/////////////////////////////////////////////////////
// TBlockData
template< uint32_t _SH >
class TBlockData
{
public:
    // Construction / Destruction
    TBlockData()
        : width     ( 0         )
        , height    ( 0         )
        , data      ( nullptr   )
    {}

    TBlockData( int iwidth, int iheight )
        : width     ( iwidth    )
        , height    ( iheight   )
        , data      ( new uint8_t[ iwidth * iheight * tSpec::_pd ] )
    {}

    ~TBlockData() { if( data ) delete[] data; }
public:
    // Public API
    uint8_t*        Data()                      { return data; }
    const uint8_t*  Data() const                { return data; }
    uint8_t*        Pixel( int x, int y )       { return nullptr; }
    const uint8_t*  Pixel( int x, int y ) const { return nullptr; }
    uint8_t*        Scanline( int row )         { return nullptr; }
    const uint8_t*  Scanline( int row ) const   { return nullptr; }
    int             Depth() const               { return 0; }
    int             Width() const               { return width; }
    int             Height() const              { return height; }

private:
    // Private Data
    uint32_t    width;
    uint32_t    height;
    uint8_t*    data;
};


/////////////////////////////////////////////////////
// IBlock
class IBlock
{
public:
    // Construction / Destruction
    IBlock() {}
    virtual ~IBlock() {} // Polymorphic
public:
    // Public API
    virtual const char*     Name() const                    = 0;
    virtual const uint32_t  Id() const                      = 0;
    virtual uint8_t*        Data()                          = 0;
    virtual const uint8_t*  Data() const                    = 0;
    virtual uint8_t*        Pixel( int x, int y )           = 0;
    virtual const uint8_t*  Pixel( int x, int y ) const     = 0;
    virtual uint8_t*        Scanline( int row )             = 0;
    virtual const uint8_t*  Scanline( int row ) const       = 0;
    virtual int             Depth() const                   = 0;
    virtual int             Width() const                   = 0;
    virtual int             Height() const                  = 0;
};


/////////////////////////////////////////////////////
// TBlock
template< uint32_t _SH >
class TBlock : public IBlock
{
public:
    // Construction / Destruction
    TBlock() { d = new tData(); }
    virtual ~TBlock() { delete d; } // Polymorphic
public:
    // Public API
    virtual const char*             Name        ()                  const   override    final   { return tSpec::_nf._ss;            }
    virtual const uint32_t          Id          ()                  const   override    final   { return tSpec::_nf._sh;            }
    virtual uint8_t*                Data        ()                  override            final   { return d->Data();             }
    virtual const uint8_t*          Data        ()                  const   override    final   { return d->Data();             }
    virtual uint8_t*                Pixel       ( int x, int y )            override    final   { return d->Pixel( x, y );      }
    virtual const uint8_t*          Pixel       ( int x, int y )    const   override    final   { return d->Pixel( x, y );      }
    virtual uint8_t*                Scanline    ( int row )                 override    final   { return d->Scanline( row );    }
    virtual const uint8_t*          Scanline    ( int row )         const   override    final   { return d->Scanline( row );    }
    virtual int                     Depth       ()                  const   override    final   { return d->Depth();            }
    virtual int                     Width       ()                  const   override    final   { return d->Width();            }
    virtual int                     Height      ()                  const   override    final   { return d->Height();           }

public:
    // Constexpr API
    static constexpr const char*    SpecStr() { return tSpec::_ss; }
    static constexpr const uint32_t SpecHash() { return tSpec::_sh; }

private:
    // Private Data
    tData* d;

};


/////////////////////////////////////////////////////
// Undefines
#undef tSpec
#undef tData


} // namespace ULIS

