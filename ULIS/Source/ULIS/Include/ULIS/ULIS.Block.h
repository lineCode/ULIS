/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Block.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once

#include "ULIS/Imaging/ULIS.Imaging.BlockSpecInfo.h"

namespace ULIS {


/////////////////////////////////////////////////////
// Defines
#define tSpec TBlockSpec< _SH >
#define tData TBlockData< _SH >


/////////////////////////////////////////////////////
// TBlockData
template< uint32 _SH >
class TBlockData
{
public:
    // Construction / Destruction
    TBlockData()
        : data( NULL )
        , width( 0 )
        , height( 0 )
        , allocated( false )
    {}

    TBlockData( int iwidth, int iheight )
        : data( new uint8[ iwidth * iheight * tSpec::_pd ] )
        , width( iwidth )
        , height( iheight )
        , allocated( true )
    {}

    ~TBlockData() { if( allocated ) delete[] data; }
public:
    // Public API
    uint8*          Data() { return data; }
    const uint8*    Data() const { return data; }
    uint8*          Pixel( int x, int y ) { return NULL; }
    const uint8*    Pixel( int x, int y ) const { return NULL; }
    uint8*          Scanline( int row ) { return NULL; }
    const uint8*    Scanline( int row ) const { return NULL; }
    int             Depth() const { return 0; }
    int             Width() const { return width; }
    int             Height() const { return height; }

private:
    // Private Data
    uint32  width;
    uint32  height;
    uint8*  data;
    bool    allocated;
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
    virtual const char*     Name() const = 0;
    virtual const uint32    Id() const = 0;
    virtual uint8*          Data() = 0;
    virtual const uint8*    Data() const = 0;
    virtual uint8*          Pixel( int x, int y ) = 0;
    virtual const uint8*    Pixel( int x, int y ) const = 0;
    virtual uint8*          Scanline( int row ) = 0;
    virtual const uint8*    Scanline( int row ) const = 0;
    virtual int             Depth() const = 0;
    virtual int             Width() const = 0;
    virtual int             Height() const = 0;
};


/////////////////////////////////////////////////////
// TBlock
template< uint32 _SH >
class TBlock : public IBlock
{
public:
    // Construction / Destruction
    TBlock() { d = new tData(); }
    virtual ~TBlock() { delete d; } // Polymorphic
public:
    // Public API
    FORCEINLINE virtual const char*     Name() const override final {                   return tSpec::_ss; }
    FORCEINLINE virtual const uint32    Id() const override final {                     return tSpec::_sh; }
    FORCEINLINE virtual uint8*          Data() override final {                         return d->Data(); }
    FORCEINLINE virtual const uint8*    Data() const override final {                   return d->Data(); }
    FORCEINLINE virtual uint8*          Pixel( int x, int y ) override final {          return d->Pixel( x, y ); }
    FORCEINLINE virtual const uint8*    Pixel( int x, int y ) const override final {    return d->Pixel( x, y ); }
    FORCEINLINE virtual uint8*          Scanline( int row ) override final {            return d->Scanline( row ); }
    FORCEINLINE virtual const uint8*    Scanline( int row ) const override final {      return d->Scanline( row ); }
    FORCEINLINE virtual int             Depth() const override final {                  return d->Depth(); }
    FORCEINLINE virtual int             Width() const override final {                  return d->Width(); }
    FORCEINLINE virtual int             Height() const override final {                 return d->Height(); }

public:
    // Constexpr API
    static constexpr const char*    SpecStr() { return tSpec::_ss; }
    static constexpr const uint32   SpecHash() { return tSpec::_sh; }
private:
    // Private Data
    tData* d;
};


/////////////////////////////////////////////////////
// Undefines
#undef tSpec
#undef tData


} // namespace ULIS

