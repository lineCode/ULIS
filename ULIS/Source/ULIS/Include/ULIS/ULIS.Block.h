/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Block.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#include <stdint.h>

/////////////////////////////////////////////////////
// Fundamental Typedefs
typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;


// ID specification
//  32bit pattern:   0000 0000   0000 0000   0000 0000   0000 0000
//  Track:
//      - M: colormode ( bit, gray, RGB, CMY, CMYK, Lab, XYZ, HSL, HSV, Yuv, Yxy, YCBcr ) ( 4bits )
//      - O: defaultcolorspace ( custom, sRGB, AdobeRGB, XYZ, Lab ) ( 8 possible values ) ( 4bit )
//      - D: Channel Depth / Channel type ( 8, 16, 32, 64, 128, 256 ) ( int8, int16, int32, uint8, uint16, uint32, float, double ) ( 4bits )
//      - L: Linear / Gamma ( 0, 1 ) ( 1bit )
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
#define FCM_BIT     0x0
#define FCM_GRAY    0x1
#define FCM_RGB     0x2
#define FCM_CMY     0x3
#define FCM_CMYK    0x4
#define FCM_LAB     0x5
#define FCM_XYZ     0x6
#define FCM_HSV     0x7
#define FCM_HSL     0x8


/////////////////////////////////////////////////////
// Colorspace IDs
#define FCS_NONE    0x0
#define FCS_SRGB    0x1
#define FCS_CADBRGB 0x2
#define FCS_CXYZ    0x3
#define FCS_CLAB    0x4


/////////////////////////////////////////////////////
// Type IDs
#define FCT_I8      0x0
#define FCT_I16     0x1
#define FCT_I32     0x2
#define FCT_UI8     0x3
#define FCT_UI16    0x4
#define FCT_UI32    0x5
#define FCT_F       0x6
#define FCT_D       0x7


/////////////////////////////////////////////////////
// Left Shift bitfield encoding
#define LS_CM( i )  ((i&0xf)<<28)
#define LS_CS( i )  ((i&0xf)<<24)
#define LS_CT( i )  ((i&0xf)<<20)
#define LS_LI( i )  ((i&1)<<19)
#define LS_DE( i )  ((i&1)<<18)
#define LS_PL( i )  ((i&1)<<17)
#define LS_PR( i )  ((i&1)<<16)
#define LS_NC( i )  ((i&0xf)<<12)
#define LS_FS( i )  ((i&1)<<11)
#define LS_SC( i )  ((i&1)<<10)
#define LS_HE( i )  ((i&1)<<9)


/////////////////////////////////////////////////////
// Right Shift bitfield decoding
#define RS_CM( i )  ((i&0xf0000000)>>28)
#define RS_CS( i )  ((i&0x0f000000)>>24)
#define RS_CT( i )  ((i&0x00f00000)>>20)
#define RS_LI( i )  ((i&0x00080000)>>19)
#define RS_DE( i )  ((i&0x00040000)>>18)
#define RS_PL( i )  ((i&0x00020000)>>17)
#define RS_PR( i )  ((i&0x00010000)>>16)
#define RS_NC( i )  ((i&0x0000f000)>>12)
#define RS_FS( i )  ((i&0x00000800)>>11)
#define RS_SC( i )  ((i&0x00000400)>>10)
#define RS_HE( i )  ((i&0x00000200)>>9)


/////////////////////////////////////////////////////
// Bitfield Enum IDs
// Types
#define CM_T    uint8
#define CS_T    uint8
#define CT_T    uint8
#define LI_T    bool
#define DE_T    bool
#define PL_T    bool
#define PR_T    bool
#define NC_T    uint8
#define FS_T    bool
#define SC_T    bool
#define HE_T    bool

// Names
#define CM_N    _tcm
#define CS_N    _tcs
#define CT_N    _tct
#define LI_N    _tli
#define DE_N    _tde
#define PL_N    _tpl
#define PR_N    _tpr
#define NC_N    _tnc
#define FS_N    _tfs
#define SC_N    _tsc
#define HE_N    _the


/////////////////////////////////////////////////////
// Bitfield Utility
#define DECODE_ALL_FIELDS( i )  \
     RS_CM( i ) \
    ,RS_CS( i ) \
    ,RS_CT( i ) \
    ,RS_LI( i ) \
    ,RS_DE( i ) \
    ,RS_PL( i ) \
    ,RS_PR( i ) \
    ,RS_NC( i ) \
    ,RS_FS( i ) \
    ,RS_SC( i ) \
    ,RS_HE( i )

#define REQUIRE_ALL_FIELDS \
     CM_T CM_N \
    ,CS_T CS_N \
    ,CT_T CT_N \
    ,LI_T LI_N \
    ,DE_T DE_N \
    ,PL_T PL_N \
    ,PR_T PR_N \
    ,NC_T NC_N \
    ,FS_T FS_N \
    ,SC_T SC_N \
    ,HE_T HE_N

#define UNROLL_ALL_FIELDS \
     CM_N \
    ,CS_N \
    ,CT_N \
    ,LI_N \
    ,DE_N \
    ,PL_N \
    ,PR_N \
    ,NC_N \
    ,FS_N \
    ,SC_N \
    ,HE_N

/////////////////////////////////////////////////////
// Bitfields
#define TYPE_sRGB_RGBI8         ( LS_CM( FCM_RGB ) | LS_CS( FCS_SRGB ) | LS_CT( FCT_I8 ) | LS_LI( 0 ) | LS_DE( 0 ) | LS_PL( 0 ) | LS_PR( 0 ) | LS_NC( 3 ) | LS_FS( 0 ) | LS_SC( 0 ) )
#define TYPE_sRGB_RGBI8_PLANAR  ( LS_CM( FCM_RGB ) | LS_CS( FCS_SRGB ) | LS_CT( FCT_I8 ) | LS_LI( 0 ) | LS_DE( 0 ) | LS_PL( 1 ) | LS_PR( 0 ) | LS_NC( 3 ) | LS_FS( 0 ) | LS_SC( 0 ) )


/////////////////////////////////////////////////////
// TPPXIndex
template< bool _tfs, bool _tsc, uint8 _tnc > struct TPPXIndex { const uint8 arr[_tnc] = { 0 }; };
template< bool _tfs, bool _tsc > struct TPPXIndex< _tfs, _tsc, 1 > { const uint8 arr[1] = { 0 }; };
template< bool _tfs, bool _tsc > struct TPPXIndex< _tfs, _tsc, 2 > { const uint8 arr[2] = { 0, 1 }; };
template< bool _tfs, bool _tsc > struct TPPXIndex< _tfs, _tsc, 3 > { const uint8 arr[3] = { 0, 1, 2 }; };
template< bool _tfs, bool _tsc > struct TPPXIndex< _tfs, _tsc, 4 > { const uint8 arr[4] = { 0, 1, 2, 3 }; };
template< bool _tfs, bool _tsc > struct TPPXIndex< _tfs, _tsc, 5 > { const uint8 arr[5] = { 0, 1, 2, 3, 4 }; };
template< bool _tsc > struct TPPXIndex< true, _tsc, 1 > { const uint8 arr[1] = { 0 }; };
template< bool _tsc > struct TPPXIndex< true, _tsc, 2 > { const uint8 arr[2] = { 1, 0 }; };
template< bool _tsc > struct TPPXIndex< true, _tsc, 3 > { const uint8 arr[3] = { 1, 2, 0 }; };
template< bool _tsc > struct TPPXIndex< true, _tsc, 4 > { const uint8 arr[4] = { 1, 2, 3, 0 }; };
template< bool _tsc > struct TPPXIndex< true, _tsc, 5 > { const uint8 arr[5] = { 1, 2, 3, 4, 0 }; };
template< bool _tfs > struct TPPXIndex< _tfs, true, 1 > { const uint8 arr[1] = { 0 }; };
template< bool _tfs > struct TPPXIndex< _tfs, true, 2 > { const uint8 arr[2] = { 1, 0 }; };
template< bool _tfs > struct TPPXIndex< _tfs, true, 3 > { const uint8 arr[3] = { 2, 1, 0 }; };
template< bool _tfs > struct TPPXIndex< _tfs, true, 4 > { const uint8 arr[4] = { 2, 1, 0, 3 }; };
template< bool _tfs > struct TPPXIndex< _tfs, true, 5 > { const uint8 arr[5] = { 1, 2, 3, 0, 4 }; };
template<> struct TPPXIndex< true, true, 1 > { const uint8 arr[1] = { 0 }; };
template<> struct TPPXIndex< true, true, 2 > { const uint8 arr[2] = { 0, 1 }; };
template<> struct TPPXIndex< true, true, 3 > { const uint8 arr[3] = { 2, 1, 0 }; };
template<> struct TPPXIndex< true, true, 4 > { const uint8 arr[4] = { 3, 2, 1, 0 }; };
template<> struct TPPXIndex< true, true, 5 > { const uint8 arr[5] = { 2, 3, 4, 1, 0 }; };


/////////////////////////////////////////////////////
// IPixelProxy
class IPixelProxy
{
public:
    IPixelProxy() {}
    ~IPixelProxy() {}
};


/////////////////////////////////////////////////////
// TPixelProxyBase
template< typename _tt, bool _tpl, bool _tfs, bool _tsc, uint8 _tnc >
struct TPixelProxyBase : public IPixelProxy
{
    TPPXIndex< _tfs, _tsc, _tnc > indexlist;
};


/////////////////////////////////////////////////////
// TBlockInfo
template< typename _tt, bool _tpl, bool _tfs, bool _tsc, uint8 _tnc >
struct TBlockInfo
{
};


/////////////////////////////////////////////////////
// TBlockStructureSelector
//--------------------------------------------------------------------------------------
//----------------------------------------------------------- _tpl false, Interleaved
template< typename _tt, bool _tpl, bool _tfs, bool _tsc, uint8 _tnc >
class TBlockStructureSelector
{
public:
    // Construction / Destruction
    TBlockStructureSelector() {
        data = NULL;
    }

    TBlockStructureSelector( int width, int height ) {
        data = new _tt[ width * height * _tnc ];
    }

    ~TBlockStructureSelector() {
        delete [] data;
    }

private:
    // Private Data
    _tt* data; // Interleaved contiguous repr
};


//--------------------------------------------------------------------------------------
//----------------------------------------------------------- _tpl true, Planar
template< typename _tt, bool _tfs, bool _tsc, uint8 _tnc >
class TBlockStructureSelector< _tt, true, _tfs, _tsc, _tnc >
{
public:
    TBlockStructureSelector() {
        data = NULL;
    }

    TBlockStructureSelector( int width, int height ) {
        data = new _tt*[ _tnc ];
        for( int i = 0; i < _tnc; ++ i )
            data[i] = new _tt[ width * height ];
    }

    ~TBlockStructureSelector() {
        for( int i = 0; i < _tnc; ++ i )
            delete [] data[i];
        delete [] data;
    }

private:
    // Private Data
    _tt** data; // Planar channels repr
};


/////////////////////////////////////////////////////
// TBlockTypeSelector
// FCT_I8   = 0 = int8
// FCT_I16  = 1 = int16
// FCT_I32  = 2 = int32
// FCT_UI8  = 3 = uint8
// FCT_UI16 = 4 = uint16
// FCT_UI32 = 5 = uint32
// FCT_F    = 6 = float
// FCT_D    = 7 = double
template< uint8 _tc, bool _tpl, bool _tfs, bool _tsc, uint8 _tnc > class TBlockTypeSelector final {};
template< bool _tpl, bool _tfs, bool _tsc, uint8 _tnc > class TBlockTypeSelector< FCT_I8,     _tpl, _tfs, _tsc, _tnc > : public TBlockStructureSelector< int8,      _tpl, _tfs, _tsc, _tnc > { using tSuperClass = TBlockStructureSelector< int8,      _tpl, _tfs, _tsc, _tnc >; using tSuperClass::tSuperClass; };
template< bool _tpl, bool _tfs, bool _tsc, uint8 _tnc > class TBlockTypeSelector< FCT_I16,    _tpl, _tfs, _tsc, _tnc > : public TBlockStructureSelector< int16,     _tpl, _tfs, _tsc, _tnc > { using tSuperClass = TBlockStructureSelector< int16,     _tpl, _tfs, _tsc, _tnc >; using tSuperClass::tSuperClass; };
template< bool _tpl, bool _tfs, bool _tsc, uint8 _tnc > class TBlockTypeSelector< FCT_I32,    _tpl, _tfs, _tsc, _tnc > : public TBlockStructureSelector< int32,     _tpl, _tfs, _tsc, _tnc > { using tSuperClass = TBlockStructureSelector< int32,     _tpl, _tfs, _tsc, _tnc >; using tSuperClass::tSuperClass; };
template< bool _tpl, bool _tfs, bool _tsc, uint8 _tnc > class TBlockTypeSelector< FCT_UI8,    _tpl, _tfs, _tsc, _tnc > : public TBlockStructureSelector< uint8,     _tpl, _tfs, _tsc, _tnc > { using tSuperClass = TBlockStructureSelector< uint8,     _tpl, _tfs, _tsc, _tnc >; using tSuperClass::tSuperClass; };
template< bool _tpl, bool _tfs, bool _tsc, uint8 _tnc > class TBlockTypeSelector< FCT_UI16,   _tpl, _tfs, _tsc, _tnc > : public TBlockStructureSelector< uint16,    _tpl, _tfs, _tsc, _tnc > { using tSuperClass = TBlockStructureSelector< uint16,    _tpl, _tfs, _tsc, _tnc >; using tSuperClass::tSuperClass; };
template< bool _tpl, bool _tfs, bool _tsc, uint8 _tnc > class TBlockTypeSelector< FCT_UI32,   _tpl, _tfs, _tsc, _tnc > : public TBlockStructureSelector< uint32,    _tpl, _tfs, _tsc, _tnc > { using tSuperClass = TBlockStructureSelector< uint32,    _tpl, _tfs, _tsc, _tnc >; using tSuperClass::tSuperClass; };
template< bool _tpl, bool _tfs, bool _tsc, uint8 _tnc > class TBlockTypeSelector< FCT_F,      _tpl, _tfs, _tsc, _tnc > : public TBlockStructureSelector< float,     _tpl, _tfs, _tsc, _tnc > { using tSuperClass = TBlockStructureSelector< float,     _tpl, _tfs, _tsc, _tnc >; using tSuperClass::tSuperClass; };
template< bool _tpl, bool _tfs, bool _tsc, uint8 _tnc > class TBlockTypeSelector< FCT_D,      _tpl, _tfs, _tsc, _tnc > : public TBlockStructureSelector< double,    _tpl, _tfs, _tsc, _tnc > { using tSuperClass = TBlockStructureSelector< double,    _tpl, _tfs, _tsc, _tnc >; using tSuperClass::tSuperClass; };


/////////////////////////////////////////////////////
// TBlockData
template< REQUIRE_ALL_FIELDS >
class TBlockData :
    public TBlockTypeSelector< _tct, _tpl, _tfs, _tsc, _tnc >
{
private:
    // Forward Constructors
    using tSuperClass = TBlockTypeSelector< _tct, _tpl, _tfs, _tsc, _tnc >;
    using tSuperClass::tSuperClass;
};


/////////////////////////////////////////////////////
// IAbstractBlock
class IAbstractBlock
{
public:
    // Construction / Destruction
    IAbstractBlock() {}
    virtual ~IAbstractBlock() {} // Polymorphic

public:
    // Public API
    virtual uint32 ID() const = 0;
};


/////////////////////////////////////////////////////
// TBlock
template< uint32 _tid >
class TBlock : public IAbstractBlock
{
public:
    // Typedefs
    typedef TBlockData< DECODE_ALL_FIELDS( _tid ) > tBlockDataType;

public:
    // Construction / Destruction
    TBlock() { d = new tBlockDataType( 0, 0 ); }
    virtual ~TBlock() { delete d; } // Polymorphic

public:
    // ¨Public API
    virtual uint32 ID() const override { return _tid; }

public:
    // Constexpr API
    static constexpr uint32 bitfield() { return _tid; }

private:
    // Private Data
    tBlockDataType* d;
};


/////////////////////////////////////////////////////
// Typedefs
typedef TBlock< TYPE_sRGB_RGBI8 > FBlock_sRGB_RGBI8;
typedef TBlock< TYPE_sRGB_RGBI8_PLANAR > FBlock_sRGB_RGBI8_Planar;


/////////////////////////////////////////////////////
// Utility

template< uint32 _tid >
void DoStuff( TBlock< _tid >* iBlock )
{
    auto dummy = 0;
}


void DoStuff2( IAbstractBlock* iBlock )
{
    auto dummy = 0;
}


IAbstractBlock* CreateBlock( uint32 id )
{
    switch( id )
    {
        case TYPE_sRGB_RGBI8:
        {
            return  new FBlock_sRGB_RGBI8();
            break;
        }

        case TYPE_sRGB_RGBI8_PLANAR:
        {
            return  new FBlock_sRGB_RGBI8_Planar();
            break;
        }
    }
    return NULL;
}


void CallDoStuffSelectCast( IAbstractBlock* iBlock )
{
    switch( iBlock->ID() )
    {
        case TYPE_sRGB_RGBI8:
        {
            DoStuff( (TBlock< TYPE_sRGB_RGBI8 >*)iBlock );
            break;
        }

        case TYPE_sRGB_RGBI8_PLANAR:
        {
            DoStuff( (TBlock< TYPE_sRGB_RGBI8_PLANAR >*)iBlock );
            break;
        }
    }
}