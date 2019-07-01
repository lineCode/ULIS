/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Data.Block.hr
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once

#include "ULIS/Data/ULIS.Data.Spec.h"
#include "ULIS/Data/ULIS.Data.Pixel.h"
#include "ULIS/Data/ULIS.Data.MD5.h"
#include "ULIS/Data/ULIS.Data.ID.h"
#include "ULIS/Maths/ULIS.Maths.Geometry.h"
#include "ULIS/Color/ULIS.Color.CColor.h"

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
    inline uint8_t*             DataPtr             ()                                              { return data;                          }
    inline const uint8_t*       DataPtr             ()                  const                       { return data;                          }
    inline uint8_t*             PixelPtr            ( int x, int y )                                { return data + ( x * BytesPerPixel() + y * BytesPerScanLine() ); }
    inline const uint8_t*       PixelPtr            ( int x, int y )    const                       { return data + ( x * BytesPerPixel() + y * BytesPerScanLine() ); }
    inline uint8_t*             ScanlinePtr         ( int row )                                     { return data + ( row * BytesPerScanLine() ); }
    inline const uint8_t*       ScanlinePtr         ( int row )         const                       { return data + ( row * BytesPerScanLine() ); }
    inline int                  Depth               ()                  const                       { return tSpec::_nf._pd;                }
    inline int                  Width               ()                  const                       { return width;                         }
    inline int                  Height              ()                  const                       { return height;                        }
    inline int                  BytesPerPixel       ()                  const                       { return Depth();                       }
    inline int                  BytesPerScanLine    ()                  const                       { return Depth() * Width();             }
    inline int                  BytesTotal          ()                  const                       { return Depth() * Width() * Height();  }
    inline CColor               GetPixelColor       ( int x, int y )                                { return CColor();                      }
    inline CColor               GetPixelColor       ( int x, int y )    const                       { return CColor();                      }
    inline TPixelProxy< _SH >   PixelProxy          ( int x, int y )                                { return  TPixelProxy< _SH >( (uint8*)PixelPtr( x, y ) );   }
    inline TPixelProxy< _SH >   PixelProxy          ( int x, int y )    const                       { return  TPixelProxy< _SH >( (uint8*)PixelPtr( x, y ) );   }
    inline TPixelValue< _SH >   PixelValue          ( int x, int y )                                { return  TPixelValue< _SH >( PixelProxy( x, y ) ); }
    inline TPixelValue< _SH >   PixelValue          ( int x, int y )    const                       { return  TPixelValue< _SH >( PixelProxy( x, y ) ); }

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
    virtual uint8_t*        DataPtr             ()                                                  = 0;
    virtual const uint8_t*  DataPtr             ()                                          const   = 0;
    virtual uint8_t*        PixelPtr            ( int x, int y )                                    = 0;
    virtual const uint8_t*  PixelPtr            ( int x, int y )                            const   = 0;
    virtual uint8_t*        ScanlinePtr         ( int row )                                         = 0;
    virtual const uint8_t*  ScanlinePtr         ( int row )                                 const   = 0;
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

    virtual CColor          GetPixelColor       ( int x, int y )                                    = 0;
    virtual CColor          GetPixelColor       ( int x, int y )                            const   = 0;

    void  Invalidate        ()                                          { if( mInvCb ) mInvCb( this, mInvInfo, 0, 0, Width(), Height() ); }
    void  Invalidate        ( const FInvalidRect& iRect )               { if( mInvCb ) mInvCb( this, mInvInfo, iRect.x, iRect.y, iRect.width, iRect.height ); }
    void  SetInvalidateCB   ( fpInvalidateFunction iCb, void* iInfo )   { mInvCb = iCb; mInvInfo = iInfo; }

    virtual std::string     GetMD5Hash          ()                                          const   = 0;
    virtual uint32          GetCRC32Hash        ()                                          const   = 0;
    virtual std::string     GetUUID             ()                                          const   = 0;

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
    // Typedef
    typedef TPixelValue< _SH > tPixelValue;
    typedef TPixelProxy< _SH > tPixelProxy;
    using tPixelType        = typename TPixelTypeSelector< tSpec::_nf._tp >::_tUnderlyingPixelType;
    using tNextPixelType    = typename TPixelTypeSelector< tSpec::_nf._tp >::_tUnderlyingNextPixelType;
    using tPrevPixelType    = typename TPixelTypeSelector< tSpec::_nf._tp >::_tUnderlyingPrevPixelType;

public:
    // Construction / Destruction
    virtual ~TBlock() { delete d; } // Polymorphic
    TBlock()
        : d( nullptr )
    {
        id = generate_uuid( 16 );
    }

    TBlock( int iWidth, int iHeight )
        : d( nullptr )
    {
        d = new tData( iWidth, iHeight );
        id = generate_uuid( 16 );
    }

public:
    // Template API
    template< typename T > inline T MaxT() const  { return  (T)tSpec::_nf._tm; }
    template< typename T > inline T RangeT() const  { return  (T)tSpec::_nf._rm; }
    inline tPixelType       Max     () const { return  MaxT< tPixelType >();        }
    inline tNextPixelType   Range   () const { return  RangeT< tNextPixelType >();  }


public:
    // Public API
    inline virtual const char*              Name                ()                  const   override    final   { return tSpec::_nf._ss;                    }
    inline virtual const uint32_t           Id                  ()                  const   override    final   { return tSpec::_nf._sh;                    }
    inline virtual uint8_t*                 DataPtr             ()                          override    final   { return d->DataPtr();                      }
    inline virtual const uint8_t*           DataPtr             ()                  const   override    final   { return d->DataPtr();                      }
    inline virtual uint8_t*                 PixelPtr            ( int x, int y )            override    final   { return d->PixelPtr( x, y );               }
    inline virtual const uint8_t*           PixelPtr            ( int x, int y )    const   override    final   { return d->PixelPtr( x, y );               }
    inline virtual uint8_t*                 ScanlinePtr         ( int row )                 override    final   { return d->ScanlinePtr( row );             }
    inline virtual const uint8_t*           ScanlinePtr         ( int row )         const   override    final   { return d->ScanlinePtr( row );             }
    inline virtual int                      Depth               ()                  const   override    final   { return d->Depth();                        }
    inline virtual int                      Width               ()                  const   override    final   { return d->Width();                        }
    inline virtual int                      Height              ()                  const   override    final   { return d->Height();                       }
    inline virtual double                   MaxD                ()                  const   override    final   { return MaxT< double >();                  }
    inline virtual int64_t                  MaxI                ()                  const   override    final   { return MaxT< int64_t >();                 }
    inline virtual double                   RangeD              ()                  const   override    final   { return RangeT< double >();                }
    inline virtual int64_t                  RangeI              ()                  const   override    final   { return RangeT< int64_t >();               }
    inline virtual int                      BytesPerPixel       ()                  const   override    final   { return d->BytesPerPixel();                }
    inline virtual int                      BytesPerScanLine    ()                  const   override    final   { return d->BytesPerScanLine();             }
    inline virtual int                      BytesTotal          ()                  const   override    final   { return d->BytesTotal();                   }
    inline virtual e_tp                     Type                ()                  const   override    final   { return tSpec::_nf._tp;                    }
    inline virtual e_cm                     ColorModel          ()                  const   override    final   { return tSpec::_nf._cm;                    }
    inline virtual e_ea                     ExtraAlpha          ()                  const   override    final   { return tSpec::_nf._ea;                    }
    inline virtual bool                     HasAlpha            ()                  const   override    final   { return ExtraAlpha() == e_ea::khasAlpha;   }
    inline virtual const char*              ChannelLayout       ()                  const   override    final   { return tSpec::_nf._cl;                    }
    inline virtual e_nm                     NormalMode          ()                  const   override    final   { return tSpec::_nf._nm;                    }
    inline virtual bool                     IsNormalized        ()                  const   override    final   { return NormalMode() == e_nm::knormalized; }
    inline virtual bool                     IsDecimal           ()                  const   override    final   { return tSpec::_nf._dm;                    }
    inline virtual int                      NumChannels         ()                  const   override    final   { return tSpec::_nf._rc;                    }
    inline virtual int                      ColorChannels       ()                  const   override    final   { return tSpec::_nf._nc;                    }
    inline virtual CColor                   GetPixelColor       ( int x, int y )            override    final   { return  d->GetPixelColor( x, y );         }
    inline virtual CColor                   GetPixelColor       ( int x, int y )    const   override    final   { return  d->GetPixelColor( x, y );         }
    inline virtual std::string              GetMD5Hash          ()                  const   override    final   { return  MD5( DataPtr(), BytesTotal() );   }
    inline virtual uint32                   GetCRC32Hash        ()                  const   override    final   { return  COAL_CRC32_DAT( DataPtr(), BytesTotal() ); }
    inline virtual std::string              GetUUID             ()                  const   override    final   { return  id;                               }

    inline tPixelValue                      PixelValue          ( int x, int y )    const                       { return  d->PixelValue( x, y );            }
    inline tPixelProxy                      PixelProxy          ( int x, int y )    const                       { return  d->PixelProxy( x, y );            }

public:
    // Constexpr API
    inline static constexpr const FSpec     TypeSpec    ()  { return tSpec::_nf;        }
    inline static constexpr const char*     TypeStr     ()  { return tSpec::_nf._ss;    }
    inline static constexpr const uint32_t  TypeId      ()  { return tSpec::_nf._sh;    }

private:
    // Private Data
    tData* d;
    std::string id;
};


/////////////////////////////////////////////////////
// Undefines
#undef tSpec
#undef tData


} // namespace ULIS

