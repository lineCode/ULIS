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
// TBlockData
template< uint32_t _SH >
class TBlockData final
{
public:
    // Construction / Destruction
    TBlockData()
        : width     ( 0         )
        , height    ( 0         )
        , data      ( nullptr   )
    {}

    TBlockData( int iWidth, int iHeight )
        : width     ( iWidth    )
        , height    ( iHeight   )
        , data      ( new uint8_t[ iWidth * iHeight * tSpec::_nf._pd ] )
    {}

    ~TBlockData() { if( data ) delete[] data; }
public:
    // Public API
    uint8_t*        Data                        ()                                              { return data;                  }
    const uint8_t*  Data                        ()                  const                       { return data;                  }
    uint8_t*        Pixel                       ( int x, int y )                                { return nullptr;               }
    const uint8_t*  Pixel                       ( int x, int y )    const                       { return nullptr;               }
    uint8_t*        Scanline                    ( int row )                                     { return nullptr;               }
    const uint8_t*  Scanline                    ( int row )         const                       { return nullptr;               }
    int             Depth                       ()                  const                       { return tSpec::_nf._pd;        }
    int             Width                       ()                  const                       { return width;                 }
    int             Height                      ()                  const                       { return height;                }

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
    virtual const char*     Name                ()                  const   = 0;
    virtual const uint32_t  Id                  ()                  const   = 0;
    virtual uint8_t*        Data                ()                          = 0;
    virtual const uint8_t*  Data                ()                  const   = 0;
    virtual uint8_t*        Pixel               ( int x, int y )            = 0;
    virtual const uint8_t*  Pixel               ( int x, int y )    const   = 0;
    virtual uint8_t*        Scanline            ( int row )                 = 0;
    virtual const uint8_t*  Scanline            ( int row )         const   = 0;
    virtual int             Depth               ()                  const   = 0;
    virtual int             Width               ()                  const   = 0;
    virtual int             Height              ()                  const   = 0;
    virtual double          MaxD                ()                  const   = 0;
    virtual int64_t         MaxI                ()                  const   = 0;
};


/////////////////////////////////////////////////////
// TBlock
template< uint32_t _SH >
class TBlock final : public IBlock
{
public:
    // Construction / Destruction
    virtual ~TBlock() { delete d; } // Polymorphic
    TBlock()
        : d( nullptr )
    {}

    TBlock( int iWidth, int iHeight )
        : d( nullptr )
    {
        d = new tData( iWidth, iHeight );
    }

public:
    // Template API
    template< typename T >
    constexpr  T Max() const  { return  (T)tSpec::_nf._tm; }

public:
    // Public API
    virtual const char*             Name        ()                  const   override    final   { return tSpec::_nf._ss;        }
    virtual const uint32_t          Id          ()                  const   override    final   { return tSpec::_nf._sh;        }
    virtual uint8_t*                Data        ()                          override    final   { return d->Data();             }
    virtual const uint8_t*          Data        ()                  const   override    final   { return d->Data();             }
    virtual uint8_t*                Pixel       ( int x, int y )            override    final   { return d->Pixel( x, y );      }
    virtual const uint8_t*          Pixel       ( int x, int y )    const   override    final   { return d->Pixel( x, y );      }
    virtual uint8_t*                Scanline    ( int row )                 override    final   { return d->Scanline( row );    }
    virtual const uint8_t*          Scanline    ( int row )         const   override    final   { return d->Scanline( row );    }
    virtual int                     Depth       ()                  const   override    final   { return d->Depth();            }
    virtual int                     Width       ()                  const   override    final   { return d->Width();            }
    virtual int                     Height      ()                  const   override    final   { return d->Height();           }
    virtual double                  MaxD        ()                  const   override    final   { return  Max< double >();      }
    virtual int64_t                 MaxI        ()                  const   override    final   { return  Max< int64_t >();     }

public:
    // Constexpr API
    static constexpr const char*    TypeStr()   { return tSpec::_nf._ss; }
    static constexpr const uint32_t TypeId()    { return tSpec::_nf._sh; }

private:
    // Private Data
    tData* d;

};


/////////////////////////////////////////////////////
// Undefines
#undef tSpec
#undef tData


} // namespace ULIS

