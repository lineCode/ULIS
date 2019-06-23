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
#include "ULIS/Maths/ULIS.Maths.Geometry.h"

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
    // Typedef
    typedef void (*fpInvalidateFunction)( IBlock* /*data*/, void* /*info*/, int /*x*/, int /*y*/, int /*width*/, int /*height*/ );

public:
    // Construction / Destruction
    IBlock() {}
    virtual ~IBlock() {} // Polymorphic

public:
    // Public API
    virtual const char*     Name                ()                                          const   = 0;
    virtual const uint32_t  Id                  ()                                          const   = 0;
    virtual uint8_t*        Data                ()                                                  = 0;
    virtual const uint8_t*  Data                ()                                          const   = 0;
    virtual uint8_t*        Pixel               ( int x, int y )                                    = 0;
    virtual const uint8_t*  Pixel               ( int x, int y )                            const   = 0;
    virtual uint8_t*        Scanline            ( int row )                                         = 0;
    virtual const uint8_t*  Scanline            ( int row )                                 const   = 0;
    virtual int             Depth               ()                                          const   = 0;
    virtual int             Width               ()                                          const   = 0;
    virtual int             Height              ()                                          const   = 0;
    virtual double          MaxD                ()                                          const   = 0;
    virtual int64_t         MaxI                ()                                          const   = 0;
    virtual double          RangeD              ()                                          const   = 0;
    virtual int64_t         RangeI              ()                                          const   = 0;
    virtual int             BytesPerPixel       ()                                          const   = 0;
    virtual int             BytesPerScanLine    ()                                          const   = 0;
    virtual int             BytesTotal          ()                                          const   = 0;
    virtual e_tp            Type                ()                                          const   = 0;
    virtual e_cm            ColorModel          ()                                          const   = 0;
    virtual e_ea            ExtraAlpha          ()                                          const   = 0;
    virtual bool            HasAlpha            ()                                          const   = 0;
    virtual const char*     ChannelLayout       ()                                          const   = 0;
    virtual e_nm            NormalMode          ()                                          const   = 0;
    virtual bool            IsNormalized        ()                                          const   = 0;
    virtual bool            IsDecimal           ()                                          const   = 0;
    virtual int             NumChannels         ()                                          const   = 0;
    virtual int             ColorChannels       ()                                          const   = 0;

    void  Invalidate        ()                                          { if( mInvCb ) mInvCb( this, mInvInfo, 0, 0, Width(), Height() ); }
    void  Invalidate        ( const FInvalidRect& iRect )               { if( mInvCb ) mInvCb( this, mInvInfo, iRect.x, iRect.y, iRect.width, iRect.height ); }
    void  SetInvalidateCB   ( fpInvalidateFunction iCb, void* iInfo )   { mInvCb = iCb; mInvInfo = iInfo; }

protected:
    fpInvalidateFunction    mInvCb;
    void*                   mInvInfo;
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

    template< typename T >
    constexpr  T Range() const  { return  (T)tSpec::_nf._rm; }

public:
    // Public API
    virtual const char*             Name                ()                  const   override    final   { return tSpec::_nf._ss;                    }
    virtual const uint32_t          Id                  ()                  const   override    final   { return tSpec::_nf._sh;                    }
    virtual uint8_t*                Data                ()                          override    final   { return d->Data();                         }
    virtual const uint8_t*          Data                ()                  const   override    final   { return d->Data();                         }
    virtual uint8_t*                Pixel               ( int x, int y )            override    final   { return d->Pixel( x, y );                  }
    virtual const uint8_t*          Pixel               ( int x, int y )    const   override    final   { return d->Pixel( x, y );                  }
    virtual uint8_t*                Scanline            ( int row )                 override    final   { return d->Scanline( row );                }
    virtual const uint8_t*          Scanline            ( int row )         const   override    final   { return d->Scanline( row );                }
    virtual int                     Depth               ()                  const   override    final   { return d->Depth();                        }
    virtual int                     Width               ()                  const   override    final   { return d->Width();                        }
    virtual int                     Height              ()                  const   override    final   { return d->Height();                       }
    virtual double                  MaxD                ()                  const   override    final   { return Max< double >();                   }
    virtual int64_t                 MaxI                ()                  const   override    final   { return Max< int64_t >();                  }
    virtual double                  RangeD              ()                  const   override    final   { return Range< double >();                 }
    virtual int64_t                 RangeI              ()                  const   override    final   { return Range< int64_t >();                }
    virtual int                     BytesPerPixel       ()                  const   override    final   { return d->Depth();                        }
    virtual int                     BytesPerScanLine    ()                  const   override    final   { return Depth() * Width();                 }
    virtual int                     BytesTotal          ()                  const   override    final   { return Depth() * Height();                }
    virtual e_tp                    Type                ()                  const   override    final   { return tSpec::_nf._tp;                    }
    virtual e_cm                    ColorModel          ()                  const   override    final   { return tSpec::_nf._cm;                    }
    virtual e_ea                    ExtraAlpha          ()                  const   override    final   { return tSpec::_nf._ea;                    }
    virtual bool                    HasAlpha            ()                  const   override    final   { return ExtraAlpha() == e_ea::khasAlpha;   }
    virtual const char*             ChannelLayout       ()                  const   override    final   { return tSpec::_nf._cl;                    }
    virtual e_nm                    NormalMode          ()                  const   override    final   { return tSpec::_nf._nm;                    }
    virtual bool                    IsNormalized        ()                  const   override    final   { return NormalMode() == e_nm::knormalized; }
    virtual bool                    IsDecimal           ()                  const   override    final   { return tSpec::_nf._dm;                    }
    virtual int                     NumChannels         ()                  const   override    final   { return tSpec::_nf._rc;                    }
    virtual int                     ColorChannels       ()                  const   override    final   { return tSpec::_nf._nc;                    }

public:
    // Constexpr API
    static constexpr const FSpec    TypeSpec    ()  { return tSpec::_nf;        }
    static constexpr const char*    TypeStr     ()  { return tSpec::_nf._ss;    }
    static constexpr const uint32_t TypeId      ()  { return tSpec::_nf._sh;    }

private:
    // Private Data
    tData* d;
};


/////////////////////////////////////////////////////
// Undefines
#undef tSpec
#undef tData


} // namespace ULIS

