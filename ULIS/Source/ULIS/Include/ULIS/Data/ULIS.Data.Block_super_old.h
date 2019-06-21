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

#include <stdint.h>
#include <limits>
#include "ULIS/Base/ULIS.Base.Types.h"

namespace ULIS {

// ID specification
//  32bit pattern:   0000 0000   0000 0000   0000 0000   0000 0000
//  Track:
//      - M: colormode ( bit, gray, RGB, CMY, CMYK, Lab, XYZ, HSL, HSV, Yuv, Yxy, YCBcr ) ( 4bits )
//      - O: defaultcolorspace ( custom, sRGB, AdobeRGB, XYZ, Lab ) ( 8 possible values ) ( 4bit )
//      - D: Channel Depth / Channel type ( 8, 16, 32, 64, 128, 256 ) ( int8, int16, int32, uint8, uint16, uint32, float, double ) ( 4bits )
//      - I: Decimal / Integer ( 1 bit )
//      - P: Planar / Interleaved ( 0, 1 ) ( 1bit )
//      - S: Premultiplied / Straight ( 0, 1 ) ( 1bit )
//      - N: Channel Num ( 1, 2, 3, 4, 5, 6, 7, 8 ) ( 4bits )
//      - F: First Swapped ( 0 1 ) ( ARGB / RGBA ) ( 1bit )
//      - C: Component Swapped ( 0 1 ) ( RGB / BGR - RGBA / BGRA )
//      - E: Extra Alpha Channel ( 0 1 )
//  32bit pattern:   MMMM OOOO   DDDD LIPS   NNNN FCE0   0000 0000


/////////////////////////////////////////////////////
// Colormode IDs
#define ULIS_FCM_BIT        0x0
#define ULIS_FCM_GRAY       0x1
#define ULIS_FCM_RGB        0x2
#define ULIS_FCM_CMY        0x3
#define ULIS_FCM_CMYK       0x4
#define ULIS_FCM_LAB        0x5
#define ULIS_FCM_XYZ        0x6
#define ULIS_FCM_HSV        0x7
#define ULIS_FCM_HSL        0x8


/////////////////////////////////////////////////////
// Colorspace IDs
#define ULIS_FCS_NONE       0x0
#define ULIS_FCS_SRGB       0x1
#define ULIS_FCS_CADBRGB    0x2
#define ULIS_FCS_CXYZ       0x3
#define ULIS_FCS_CLAB       0x4


/////////////////////////////////////////////////////
// Type IDs
#define ULIS_FCT_I8         0x0
#define ULIS_FCT_I16        0x1
#define ULIS_FCT_I32        0x2
#define ULIS_FCT_UI8        0x3
#define ULIS_FCT_UI16       0x4
#define ULIS_FCT_UI32       0x5
#define ULIS_FCT_F          0x6
#define ULIS_FCT_D          0x7


/////////////////////////////////////////////////////
// Left Shift bitfield encoding
#define ULIS_LS_CM( i )     ((i&0xf)<<28)
#define ULIS_LS_CS( i )     ((i&0xf)<<24)
#define ULIS_LS_CT( i )     ((i&0xf)<<20)
#define ULIS_LS_LI( i )     ((i&1)<<19)
#define ULIS_LS_DE( i )     ((i&1)<<18)
#define ULIS_LS_PL( i )     ((i&1)<<17)
#define ULIS_LS_PR( i )     ((i&1)<<16)
#define ULIS_LS_NC( i )     ((i&0xf)<<12)
#define ULIS_LS_FS( i )     ((i&1)<<11)
#define ULIS_LS_SC( i )     ((i&1)<<10)
#define ULIS_LS_HE( i )     ((i&1)<<9)


/////////////////////////////////////////////////////
// Right Shift bitfield decoding
#define ULIS_RS_CM( i )     ((i&0xf0000000)>>28)
#define ULIS_RS_CS( i )     ((i&0x0f000000)>>24)
#define ULIS_RS_CT( i )     ((i&0x00f00000)>>20)
#define ULIS_RS_LI( i )     ((i&0x00080000)>>19)
#define ULIS_RS_DE( i )     ((i&0x00040000)>>18)
#define ULIS_RS_PL( i )     ((i&0x00020000)>>17)
#define ULIS_RS_PR( i )     ((i&0x00010000)>>16)
#define ULIS_RS_NC( i )     ((i&0x0000f000)>>12)
#define ULIS_RS_FS( i )     ((i&0x00000800)>>11)
#define ULIS_RS_SC( i )     ((i&0x00000400)>>10)
#define ULIS_RS_HE( i )     ((i&0x00000200)>>9)


/////////////////////////////////////////////////////
// Bitfield Utility
#define ULIS_ENCODE_ALL_FIELDS( cm, cs, ct, li, de, pl, pr, nc, fs, sc, he )    (   ULIS_LS_CM( cm ) | ULIS_LS_CS( cs ) | ULIS_LS_CT( ct ) | ULIS_LS_LI( li ) | ULIS_LS_DE( de ) | ULIS_LS_PL( pl ) | ULIS_LS_PR( pr ) | ULIS_LS_NC( nc ) | ULIS_LS_FS( fs ) | ULIS_LS_SC( sc ) | ULIS_LS_HE( he ) )


/////////////////////////////////////////////////////
// Bitfields
#define ULIS_TYPE_sRGB_RGBI8            ULIS_ENCODE_ALL_FIELDS( ULIS_FCM_RGB, ULIS_FCS_SRGB, ULIS_FCT_I8, 0, 0, 0, 0, 3, 0, 0, 0 )
#define ULIS_TYPE_sRGB_RGBI8_PLANAR     ULIS_ENCODE_ALL_FIELDS( ULIS_FCM_RGB, ULIS_FCS_SRGB, ULIS_FCT_I8, 0, 0, 1, 0, 3, 0, 0, 0 )


/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
#define ULIS_ADD_INDEX_RULE( iCount, ... )          template< bool _tfs, bool _tsc > struct TPixelIndexRule< _tfs, _tsc, iCount > { static constexpr const uint8 m[iCount] = __VA_ARGS__; }; 
#define ULIS_ADD_FS_INDEX_RULE( iCount, ... )       template< bool _tsc > struct TPixelIndexRule< true, _tsc, iCount > { static constexpr const uint8 m[iCount] = __VA_ARGS__; }; 
#define ULIS_ADD_SC_INDEX_RULE( iCount, ... )       template< bool _tfs > struct TPixelIndexRule< _tfs, true, iCount > { static constexpr const uint8 m[iCount] = __VA_ARGS__; }; 
#define ULIS_ADD_FS_SC_INDEX_RULE( iCount, ... )    template<> struct TPixelIndexRule< true, true, iCount > { static constexpr const uint8 m[iCount] = __VA_ARGS__; }; 
template< bool _tfs, bool _tsc, uint8 _tnc >
struct TPixelIndexRule final {};
ULIS_ADD_INDEX_RULE( 1, { 0 } )
ULIS_ADD_INDEX_RULE( 2, { 0, 1 } )
ULIS_ADD_INDEX_RULE( 3, { 0, 1, 2 } )
ULIS_ADD_INDEX_RULE( 4, { 0, 1, 2, 3 } )
ULIS_ADD_INDEX_RULE( 5, { 0, 1, 2, 3, 4 } )
ULIS_ADD_FS_INDEX_RULE( 1, { 0 } )
ULIS_ADD_FS_INDEX_RULE( 2, { 1, 0 } )
ULIS_ADD_FS_INDEX_RULE( 3, { 1, 2, 0 } )
ULIS_ADD_FS_INDEX_RULE( 4, { 1, 2, 3, 0 } )
ULIS_ADD_FS_INDEX_RULE( 5, { 1, 2, 3, 4, 0 } )
ULIS_ADD_SC_INDEX_RULE( 1, { 0 } )
ULIS_ADD_SC_INDEX_RULE( 2, { 1, 0 } )
ULIS_ADD_SC_INDEX_RULE( 3, { 2, 1, 0 } )
ULIS_ADD_SC_INDEX_RULE( 4, { 2, 1, 0, 3 } )
ULIS_ADD_SC_INDEX_RULE( 5, { 1, 2, 3, 0, 4 } )
ULIS_ADD_FS_SC_INDEX_RULE( 1, { 0 } )
ULIS_ADD_FS_SC_INDEX_RULE( 2, { 0, 1 } )
ULIS_ADD_FS_SC_INDEX_RULE( 3, { 2, 1, 0 } )
ULIS_ADD_FS_SC_INDEX_RULE( 4, { 3, 2, 1, 0 } )
ULIS_ADD_FS_SC_INDEX_RULE( 5, { 2, 3, 4, 1, 0 } )


/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
// TBlockDataInfo
template< typefield T, typename _tt >
struct TBlockDataInfo
{
    static constexpr const typefieldId  cm = ULIS_RS_CM( T ); // ColorMode (Id)
    static constexpr const typefieldId  cs = ULIS_RS_CS( T ); // ColorSpace (Id)
    static constexpr const typefieldId  ct = ULIS_RS_CT( T ); // ChannelType (Id)
    static constexpr const typefieldBit li = ULIS_RS_LI( T ); // Linear (Bit)
    static constexpr const typefieldBit de = ULIS_RS_DE( T ); // Decimal (Bit)
    static constexpr const typefieldBit pl = ULIS_RS_PL( T ); // Planar (Bit)
    static constexpr const typefieldBit pr = ULIS_RS_PR( T ); // Premultiplied (Bit)
    static constexpr const uint8        nc = ULIS_RS_NC( T ); // NumChannel ( Count )
    static constexpr const typefieldBit fs = ULIS_RS_FS( T ); // FirstSwapped (Bit)
    static constexpr const typefieldBit sc = ULIS_RS_SC( T ); // SwappedComponent (Bit)
    static constexpr const typefieldBit he = ULIS_RS_HE( T ); // HasExtra (Bit)
    static constexpr const uint8        channelCount = nc+(uint8)he; // Real Channel Count, add Extra Alpha if specified
    static constexpr const char*        type_name() { return typeid(_tt).name(); } // Type Name as c-string
    static constexpr const _tt          realtypemax = std::numeric_limits< _tt >::max();
    static constexpr const _tt          realtypemin = std::numeric_limits< _tt >::min();
    static constexpr const _tt          trangemax = de ? (_tt)1.0 : realtypemax;
    static constexpr const _tt          trangemin = de ? (_tt)0.0 : realtypemin;
    static constexpr const int64        irangemax = de ? 1 : (int64)realtypemax;
    static constexpr const int64        irangemin = de ? 0 : (int64)realtypemin;
    static constexpr const double       drangemax = de ? 1.0 : (double)realtypemax;
    static constexpr const double       drangemin = de ? 0.0 : (double)realtypemin;
    static constexpr uint16_t           depthBytes = cm == ULIS_FCM_BIT ? 0 : sizeof( _tt );
    static constexpr uint16_t           depthBits = cm == ULIS_FCM_BIT ? 1 : depthBytes * 8;
    static constexpr uint16_t           bitsPerPixel = depthBits * channelCount;
    static constexpr uint16_t           bytesPerPixel = depthBytes * channelCount;
};


/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
// TPixelProxyBase
template< typefield T, typename _tt >
struct TPixelProxy
{
    typedef TBlockDataInfo< T, _tt > tBlockDataInfoType;
    typedef TPixelIndexRule< tBlockDataInfoType::fs, tBlockDataInfoType::sc, tBlockDataInfoType::channelCount > tPixelIndexRuleType;
    _tt* c[tBlockDataInfoType::channelCount];
};


/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
// TBlockDataStructure
template< typefield T, typename _tt >
class TBlockDataBase
{
    typedef TBlockDataInfo< T, _tt > tBlockDataInfoType;

public:
    typefieldId     ColorModeID() const { return  tBlockDataInfoType::cm; }
    typefieldId     ColorSpaceID() const { return  tBlockDataInfoType::cs; }
    typefieldId     ChannelTypeID() const { return  tBlockDataInfoType::ct; }
    bool            IsLinear() const { return  tBlockDataInfoType::li; }
    bool            IsDecimal() const { return  tBlockDataInfoType::de; }
    bool            IsPlanar() const { return  tBlockDataInfoType::pl; }
    bool            IsPremultiplied() const { return  tBlockDataInfoType::pr; }
    bool            HasAlpha() const { return  tBlockDataInfoType::he; }
    bool            IsSwapped() const { return  tBlockDataInfoType::sc; }
    bool            IsAlphaFirst() const { return  tBlockDataInfoType::fs; };
    int             ChannelCount() const { return  tBlockDataInfoType::channelCount; }
    const char*     TypeName() const { return  tBlockDataInfoType::type_name(); }
    int64           RangeMaxI() const { return  tBlockDataInfoType::irangemax; }
    int64           RangeMinI() const { return  tBlockDataInfoType::irangemin; }
    double          RangeMaxD() const { return  tBlockDataInfoType::drangemax; }
    double          RangeMinD() const { return  tBlockDataInfoType::drangemin; }
    int             DepthBytes() const { return  tBlockDataInfoType::depthBytes; }
    int             DepthBits() const { return  tBlockDataInfoType::depthBits; }
    int             BytesPerPixel() const { return  tBlockDataInfoType::bytesPerPixel; }
    int             BitsPerPixel() const { return  tBlockDataInfoType::bitsPerPixel; }
};

/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
// TBlockDataStructure
//--------------------------------------------------------------------------------------
//----------------------------------------------------------- typefieldBit _tpl PL false, Interleaved
template< typefield T, typename _tt, typefieldBit _tpl >
class TBlockDataStructure : public TBlockDataBase< T, _tt >
{
    typedef TBlockDataInfo< T, _tt > tBlockDataInfoType;

public:
    // Construction / Destruction
    TBlockDataStructure() : data( NULL ), width(0), height(0) {}

    TBlockDataStructure( int iwidth, int iheight ) : width(iwidth), height(iheight) {
        data = new _tt[ width * height * tBlockDataInfoType::channelCount ];
    }

    ~TBlockDataStructure() { delete [] data; }

protected:
    // Protected Data
    _tt* data; // Interleaved contiguous repr
    uint32 width, height;
};


//--------------------------------------------------------------------------------------
//----------------------------------------------------------- typefieldBit _tpl PL true, Planar
template< typefield T, typename _tt >
class TBlockDataStructure< T, _tt, true > : public TBlockDataBase< T, _tt >
{
    typedef TBlockDataInfo< T, _tt > tBlockDataInfoType;

public:
    // Construction / Destruction
    TBlockDataStructure() : data( NULL ), width(0), height(0) {}

    TBlockDataStructure( int iwidth, int iheight ) : width(iwidth), height(iheight) {
        data = new _tt*[ tBlockDataInfoType::channelCount ];
        for( int i = 0; i < tBlockDataInfoType::channelCount; ++ i )
            data[i] = new _tt[ width * height ];
    }

    ~TBlockDataStructure() {
        for( int i = 0; i < tBlockDataInfoType::channelCount; ++ i )
            delete [] data[i];
        delete [] data;
    }

protected:
    // Protected Data
    _tt** data; // Planar channels repr
    uint32 width, height;
};


/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
// TBlockDataStructureTypeSelector
#define ULIS_ADD_STRUCTURE_TYPE( iID, iType ) template< typefield T > class TBlockDataStructureTypeSelector< T, /**/iID/**/ > : public TBlockDataStructure< T, /**/iType/**/, ULIS_RS_PL( T ) > { using tSuperClass = TBlockDataStructure< T, /**/iType/**/, ULIS_RS_PL( T ) >; using tSuperClass::tSuperClass; };
template< typefield T, typefieldId _tct > class TBlockDataStructureTypeSelector final {};
ULIS_ADD_STRUCTURE_TYPE( ULIS_FCT_I8  , int8   )
ULIS_ADD_STRUCTURE_TYPE( ULIS_FCT_I16 , int16  )
ULIS_ADD_STRUCTURE_TYPE( ULIS_FCT_I32 , int32  )
ULIS_ADD_STRUCTURE_TYPE( ULIS_FCT_UI8 , uint8  )
ULIS_ADD_STRUCTURE_TYPE( ULIS_FCT_UI16, uint16 )
ULIS_ADD_STRUCTURE_TYPE( ULIS_FCT_UI32, uint32 )
ULIS_ADD_STRUCTURE_TYPE( ULIS_FCT_F   , float  )
ULIS_ADD_STRUCTURE_TYPE( ULIS_FCT_D   , double )


/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
// TBlockData
template< typefield T >
class TBlockData :
    public TBlockDataStructureTypeSelector< T, ULIS_RS_CT( T ) >
{
    using tSuperClass = TBlockDataStructureTypeSelector< T, ULIS_RS_CT( T ) >;
    using tSuperClass::tSuperClass; 

public:
    uint8*          Bytes() { return (uint8*)tSuperClass::data; }
    const uint8*    Bytes() const { return (uint8*)tSuperClass::data; }
    uint8*          PixelByte( int x, int y ) { return (uint8*)tSuperClass::data; }
    const uint8*    PixelByte( int x, int y ) const { return (uint8*)tSuperClass::data; }
    uint8*          ScanlineByte( int row ) { return (uint8*)tSuperClass::data; }
    const uint8*    ScanlineByte( int row ) const { return (uint8*)tSuperClass::data; }
    int             Width() const { return  tSuperClass::width; }
    int             Height() const { return  tSuperClass::height; }
};


/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
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
    virtual typefield       ID() const = 0;
    virtual uint8*          Bytes() = 0;
    virtual const uint8*    Bytes() const = 0;
    virtual uint8*          PixelByte( int x, int y ) = 0;
    virtual const uint8*    PixelByte( int x, int y ) const = 0;
    virtual uint8*          ScanlineByte( int row ) = 0;
    virtual const uint8*    ScanlineByte( int row ) const = 0;
    virtual typefieldId     ColorModeID() const = 0;
    virtual typefieldId     ColorSpaceID() const = 0;
    virtual typefieldId     ChannelTypeID() const = 0;
    virtual bool            IsLinear() const = 0;
    virtual bool            IsDecimal() const = 0;
    virtual bool            IsPlanar() const = 0;
    virtual bool            IsPremultiplied() const = 0;
    virtual bool            HasAlpha() const = 0;
    virtual bool            IsSwapped() const = 0;
    virtual bool            IsAlphaFirst() const = 0;
    virtual int             ChannelCount() const = 0;
    virtual const char*     TypeName() const = 0;
    virtual int64           RangeMaxI() const = 0;
    virtual int64           RangeMinI() const = 0;
    virtual double          RangeMaxD() const = 0;
    virtual double          RangeMinD() const = 0;
    virtual int             DepthBytes() const = 0;
    virtual int             DepthBits() const = 0;
    virtual int             BytesPerPixel() const = 0;
    virtual int             BitsPerPixel() const = 0;
    virtual int             Width() const = 0;
    virtual int             Height() const = 0;
};


/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
// TBlock
template< typefield T >
class TBlock final : public IBlock
{
    typedef TBlockData< T > tBlockDataType;

public:
    // Construction / Destruction
    TBlock() { d = new tBlockDataType( 0, 0 ); }
    TBlock( int iwidth, int iheight ) { d = new tBlockDataType( iwidth, iheight ); }
    virtual ~TBlock() { delete d; } // Polymorphic

public:
    // Public API
    FORCEINLINE virtual typefield       ID() const override final { return T; }
    FORCEINLINE virtual uint8*          Bytes() override final { return d->Bytes(); }
    FORCEINLINE virtual const uint8*    Bytes() const override final { return d->Bytes(); }
    FORCEINLINE virtual uint8*          PixelByte( int x, int y ) override final { return d->PixelByte( x, y ); }
    FORCEINLINE virtual const uint8*    PixelByte( int x, int y ) const override final { return d->PixelByte( x, y ); }
    FORCEINLINE virtual uint8*          ScanlineByte( int row ) override final { return d->ScanlineByte( row ); }
    FORCEINLINE virtual const uint8*    ScanlineByte( int row ) const override final { return d->ScanlineByte( row ); }
    FORCEINLINE virtual typefieldId     ColorModeID() const override final { return d->ColorModeID(); }
    FORCEINLINE virtual typefieldId     ColorSpaceID() const override final { return d->ColorSpaceID(); }
    FORCEINLINE virtual typefieldId     ChannelTypeID() const override final { return d->ChannelTypeID(); }
    FORCEINLINE virtual bool            IsLinear() const override final { return d->IsLinear(); }
    FORCEINLINE virtual bool            IsDecimal() const override final { return d->IsDecimal(); }
    FORCEINLINE virtual bool            IsPlanar() const override final { return d->IsPlanar(); }
    FORCEINLINE virtual bool            IsPremultiplied() const override final { return d->IsPremultiplied(); }
    FORCEINLINE virtual bool            HasAlpha() const override final { return d->HasAlpha(); }
    FORCEINLINE virtual bool            IsSwapped() const override final { return d->IsSwapped(); }
    FORCEINLINE virtual bool            IsAlphaFirst() const override final { return d->IsAlphaFirst(); }
    FORCEINLINE virtual int             ChannelCount() const override final { return d->ChannelCount(); }
    FORCEINLINE virtual const char*     TypeName() const override final { return d->TypeName(); }
    FORCEINLINE virtual int64           RangeMaxI() const override final { return d->RangeMaxI(); }
    FORCEINLINE virtual int64           RangeMinI() const override final { return d->RangeMinI(); }
    FORCEINLINE virtual double          RangeMaxD() const override final { return d->RangeMaxD(); }
    FORCEINLINE virtual double          RangeMinD() const override final { return d->RangeMinD(); }
    FORCEINLINE virtual int             DepthBytes() const override final { return d->DepthBytes(); }
    FORCEINLINE virtual int             DepthBits() const override final { return d->DepthBits(); }
    FORCEINLINE virtual int             BytesPerPixel() const override final { return d->BytesPerPixel(); }
    FORCEINLINE virtual int             BitsPerPixel() const override final { return d->BitsPerPixel(); }
    FORCEINLINE virtual int             Width() const override final { return d->Width(); }
    FORCEINLINE virtual int             Height() const override final { return d->Height(); }

public:
    // Constexpr API
    static constexpr typefield Typefield() { return T; }

private:
    // Private Data
    tBlockDataType* d;
};


/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
// Typedefs
typedef TBlock< ULIS_TYPE_sRGB_RGBI8 >           FBlock_sRGB_RGBI8;
typedef TBlock< ULIS_TYPE_sRGB_RGBI8_PLANAR >    FBlock_sRGB_RGBI8_Planar;


} // namespace ULIS
