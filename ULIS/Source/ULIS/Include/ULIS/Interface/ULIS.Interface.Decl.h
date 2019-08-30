/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Interface.Decl.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once


#include "ULIS/Data/ULIS.Data.Block.h"
#include "ULIS/Base/ULIS.Base.Registry.h"
#include <boost/preprocessor/slot/slot.hpp>


namespace ULIS {
/////////////////////////////////////////////////////
// Embedded python program for combination generation
/*
    tp = [ "uint8", "uint16", "uint32", "float", "double" ]
    cm = [ "G", "RGB", "HSL", "HSV", "CMYK", "YUV", "Lab", "XYZ" ]
    ea = [ "hasAlpha", "noAlpha" ]
    nm = [ "normalized", "typeLimits" ]

    variants =    {
        ( "G", "noAlpha"        )   : [ "G" ],
        ( "G", "hasAlpha"       )   : [ "GA", "AG" ],
        ( "RGB", "noAlpha"      )   : [ "RGB", "BGR" ],
        ( "RGB", "hasAlpha"     )   : [ "ARGB", "ABGR", "RGBA", "BGRA" ],
        ( "HSL", "noAlpha"      )   : [ "HSL" ],
        ( "HSL", "hasAlpha"     )   : [ "HSLA", "AHSL" ],
        ( "HSV", "noAlpha"      )   : [ "HSV" ],
        ( "HSV", "hasAlpha"     )   : [ "HSVA", "AHSV" ],
        ( "CMYK", "noAlpha"     )   : [ "CMYK", "KCMY" ],
        ( "CMYK", "hasAlpha"    )   : [ "CMYKA", "KCMYA", "ACMYK", "AKCMY" ],
        ( "YUV", "noAlpha"      )   : [ "YUV" ],
        ( "YUV", "hasAlpha"     )   : [ "YUVA", "AYUV" ],
        ( "Lab", "noAlpha"      )   : [ "Lab" ],
        ( "Lab", "hasAlpha"     )   : [ "LabA", "ALab" ],
        ( "XYZ", "noAlpha"      )   : [ "XYZ" ],
        ( "XYZ", "hasAlpha"     )   : [ "XYZA", "AXYZ" ],
    }

    def is_decimal( iType ):
        return  iType == "float" or iType == "double"

    for icm in cm:
        for itp in tp: 
            for iea in ea:
                for inm in nm:
                    if( not is_decimal( itp ) and inm == "normalized" ):
                        continue
                        
                    var = ( icm, iea )
                    for ivar in variants[var]:
                        print( "ULIS_DECLSPEC(" + itp + "," + icm + "," + iea + "," + ivar + "," + inm + ")" )
*/

/////////////////////////////////////////////////////
// Reg baking
/* we spec the name of the build reg */
#define ULIS_REG_BUILDER ulis_reg_builder
/* we create the reg with a first invalid entry (0) */
ULIS_CREATE_REG( ULIS_REG_BUILDER, 0 )

/////////////////////////////////////////////////////
// Types declspec
/* Actual types specializations */
ULIS_DECLSPEC(uint8,G,hasAlpha,GA,typeLimits)
ULIS_DECLSPEC(uint8,G,hasAlpha,AG,typeLimits)
ULIS_DECLSPEC(uint8,G,noAlpha,G,typeLimits)
ULIS_DECLSPEC(uint16,G,hasAlpha,GA,typeLimits)
ULIS_DECLSPEC(uint16,G,hasAlpha,AG,typeLimits)
ULIS_DECLSPEC(uint16,G,noAlpha,G,typeLimits)
ULIS_DECLSPEC(uint32,G,hasAlpha,GA,typeLimits)
ULIS_DECLSPEC(uint32,G,hasAlpha,AG,typeLimits)
ULIS_DECLSPEC(uint32,G,noAlpha,G,typeLimits)
ULIS_DECLSPEC(float,G,hasAlpha,GA,normalized)
ULIS_DECLSPEC(float,G,hasAlpha,AG,normalized)
ULIS_DECLSPEC(float,G,noAlpha,G,normalized)
ULIS_DECLSPEC(uint8,RGB,hasAlpha,ARGB,typeLimits)
ULIS_DECLSPEC(uint8,RGB,hasAlpha,ABGR,typeLimits)
ULIS_DECLSPEC(uint8,RGB,hasAlpha,RGBA,typeLimits)
ULIS_DECLSPEC(uint8,RGB,hasAlpha,BGRA,typeLimits)
ULIS_DECLSPEC(uint8,RGB,noAlpha,RGB,typeLimits)
ULIS_DECLSPEC(uint8,RGB,noAlpha,BGR,typeLimits)
ULIS_DECLSPEC(uint16,RGB,hasAlpha,ARGB,typeLimits)
ULIS_DECLSPEC(uint16,RGB,hasAlpha,ABGR,typeLimits)
ULIS_DECLSPEC(uint16,RGB,hasAlpha,RGBA,typeLimits)
ULIS_DECLSPEC(uint16,RGB,hasAlpha,BGRA,typeLimits)
ULIS_DECLSPEC(uint16,RGB,noAlpha,RGB,typeLimits)
ULIS_DECLSPEC(uint16,RGB,noAlpha,BGR,typeLimits)
ULIS_DECLSPEC(uint32,RGB,hasAlpha,ARGB,typeLimits)
ULIS_DECLSPEC(uint32,RGB,hasAlpha,ABGR,typeLimits)
ULIS_DECLSPEC(uint32,RGB,hasAlpha,RGBA,typeLimits)
ULIS_DECLSPEC(uint32,RGB,hasAlpha,BGRA,typeLimits)
ULIS_DECLSPEC(uint32,RGB,noAlpha,RGB,typeLimits)
ULIS_DECLSPEC(uint32,RGB,noAlpha,BGR,typeLimits)
ULIS_DECLSPEC(float,RGB,hasAlpha,ARGB,normalized)
ULIS_DECLSPEC(float,RGB,hasAlpha,ABGR,normalized)
ULIS_DECLSPEC(float,RGB,hasAlpha,RGBA,normalized)
ULIS_DECLSPEC(float,RGB,hasAlpha,BGRA,normalized)
ULIS_DECLSPEC(float,RGB,noAlpha,RGB,normalized)
ULIS_DECLSPEC(float,RGB,noAlpha,BGR,normalized)
ULIS_DECLSPEC(uint8,HSL,hasAlpha,HSLA,typeLimits)
ULIS_DECLSPEC(uint16,HSL,hasAlpha,HSLA,typeLimits)
ULIS_DECLSPEC(uint32,HSL,hasAlpha,HSLA,typeLimits)
ULIS_DECLSPEC(float,HSL,hasAlpha,HSLA,normalized)
ULIS_DECLSPEC(uint8,HSV,hasAlpha,HSVA,typeLimits)
ULIS_DECLSPEC(uint16,HSV,hasAlpha,HSVA,typeLimits)
ULIS_DECLSPEC(uint32,HSV,hasAlpha,HSVA,typeLimits)
ULIS_DECLSPEC(float,HSV,hasAlpha,HSVA,normalized)
ULIS_DECLSPEC(uint8,CMYK,hasAlpha,CMYKA,typeLimits)
ULIS_DECLSPEC(uint16,CMYK,hasAlpha,CMYKA,typeLimits)
ULIS_DECLSPEC(uint32,CMYK,hasAlpha,CMYKA,typeLimits)
ULIS_DECLSPEC(float,CMYK,hasAlpha,CMYKA,normalized)
ULIS_DECLSPEC(uint8,Lab,hasAlpha,LabA,typeLimits)
ULIS_DECLSPEC(uint16,Lab,hasAlpha,LabA,typeLimits)
ULIS_DECLSPEC(uint32,Lab,hasAlpha,LabA,typeLimits)
ULIS_DECLSPEC(float,Lab,hasAlpha,LabA,normalized)
ULIS_DECLSPEC(uint8,XYZ,hasAlpha,XYZA,typeLimits)
ULIS_DECLSPEC(uint16,XYZ,hasAlpha,XYZA,typeLimits)
ULIS_DECLSPEC(uint32,XYZ,hasAlpha,XYZA,typeLimits)
ULIS_DECLSPEC(float,XYZ,hasAlpha,XYZA,normalized)

/////////////////////////////////////////////////////
// Reg assign
/* we assign the result reg */
ULIS_REG_TYPE ulis_types_reg = ULIS_ASSIGN_REG( ULIS_REG_BUILDER );
/* we spec the name of the result reg for easy usage */
#define ULIS_REG ::ULIS::ulis_types_reg

/////////////////////////////////////////////////////
// Reg Size
/* temp assign reg size ( workaround ) */
constexpr auto temp_reg_size = ulis_types_reg.Size();
/* Reg size macro for usage during preprocessor ( workaround ) */
#define ULIS_REG_SIZE 57

/////////////////////////////////////////////////////
// Extern template declarations
void ULIS_DECL_EXPORT_SYMBOL();
/*
#define ULIS_REG_OP( z, n, data ) extern template class TBlock< ::ULIS::ulis_types_reg[ n ] >;
ULIS_REPEAT( ULIS_REG_SIZE, ULIS_REG_OP, void )
#undef ULIS_REG_OP
*/

/////////////////////////////////////////////////////
// Mainstream typedefs
/* easy typedefs for the most common block types defined earlier */
typedef ::ULIS::FBlockuint8GnoAlphaGtypeLimits FBlockG8;
typedef ::ULIS::FBlockfloatGnoAlphaGnormalized FBlockGf;
typedef ::ULIS::FBlockuint8RGBhasAlphaRGBAtypeLimits FBlockRGBA8;
typedef ::ULIS::FBlockuint8RGBhasAlphaBGRAtypeLimits FBlockBGRA8;
typedef ::ULIS::FBlockuint8RGBhasAlphaARGBtypeLimits FBlockARGB8;
typedef ::ULIS::FBlockuint8RGBhasAlphaABGRtypeLimits FBlockABGR8;
typedef ::ULIS::FBlockfloatRGBhasAlphaRGBAnormalized FBlockRGBAf;
typedef ::ULIS::FBlockfloatRGBhasAlphaBGRAnormalized FBlockBGRAf;
typedef ::ULIS::FBlockfloatRGBhasAlphaARGBnormalized FBlockARGBf;
typedef ::ULIS::FBlockfloatRGBhasAlphaABGRnormalized FBlockABGRf;

typedef ::ULIS::TPixelValue< FBlockuint8GnoAlphaGtypeLimits::TypeId() > FValueG8;
typedef ::ULIS::TPixelValue< FBlockfloatGnoAlphaGnormalized::TypeId() > FValueGf;
typedef ::ULIS::TPixelValue< FBlockuint8RGBhasAlphaRGBAtypeLimits::TypeId() > FValueRGBA8;
typedef ::ULIS::TPixelValue< FBlockuint8RGBhasAlphaBGRAtypeLimits::TypeId() > FValueBGRA8;
typedef ::ULIS::TPixelValue< FBlockuint8RGBhasAlphaARGBtypeLimits::TypeId() > FValueARGB8;
typedef ::ULIS::TPixelValue< FBlockuint8RGBhasAlphaABGRtypeLimits::TypeId() > FValueABGR8;
typedef ::ULIS::TPixelValue< FBlockfloatRGBhasAlphaRGBAnormalized::TypeId() > FValueRGBAf;
typedef ::ULIS::TPixelValue< FBlockfloatRGBhasAlphaBGRAnormalized::TypeId() > FValueBGRAf;
typedef ::ULIS::TPixelValue< FBlockfloatRGBhasAlphaARGBnormalized::TypeId() > FValueARGBf;
typedef ::ULIS::TPixelValue< FBlockfloatRGBhasAlphaABGRnormalized::TypeId() > FValueABGRf;

/////////////////////////////////////////////////////
// TDefaultModelFormat Specialization
template<> constexpr uint32 TDefaultModelFormat< e_cm::kG >()     { return  FBlockfloatGhasAlphaGAnormalized::TypeId();       }
template<> constexpr uint32 TDefaultModelFormat< e_cm::kRGB >()   { return  FBlockfloatRGBhasAlphaRGBAnormalized::TypeId();   }
template<> constexpr uint32 TDefaultModelFormat< e_cm::kHSL >()   { return  FBlockfloatHSLhasAlphaHSLAnormalized::TypeId();   }
template<> constexpr uint32 TDefaultModelFormat< e_cm::kHSV >()   { return  FBlockfloatHSVhasAlphaHSVAnormalized::TypeId();   }
template<> constexpr uint32 TDefaultModelFormat< e_cm::kCMYK >()  { return  FBlockfloatCMYKhasAlphaCMYKAnormalized::TypeId(); }
template<> constexpr uint32 TDefaultModelFormat< e_cm::kLab >()   { return  FBlockfloatLabhasAlphaLabAnormalized::TypeId();   }
template<> constexpr uint32 TDefaultModelFormat< e_cm::kXYZ >()   { return  FBlockfloatXYZhasAlphaXYZAnormalized::TypeId();   }
/////////////////////////////////////////////////////
// CMS extra formats for connection
#define ULIS_LCMS_DTYPE_GRAYA_FLT   (FLOAT_SH(1)|COLORSPACE_SH(PT_GRAY)|EXTRA_SH(1)|CHANNELS_SH(1)|BYTES_SH(4))
#define ULIS_LCMS_DTYPE_RGBA_FLT    (FLOAT_SH(1)|COLORSPACE_SH(PT_RGB)|EXTRA_SH(1)|CHANNELS_SH(3)|BYTES_SH(4))
#define ULIS_LCMS_DTYPE_CMYKA_FLT   (FLOAT_SH(1)|COLORSPACE_SH(PT_CMYK)|EXTRA_SH(1)|CHANNELS_SH(4)|BYTES_SH(4))
#define ULIS_LCMS_DTYPE_LabA_FLT    (FLOAT_SH(1)|COLORSPACE_SH(PT_Lab)|EXTRA_SH(1)|CHANNELS_SH(3)|BYTES_SH(4))
#define ULIS_LCMS_DTYPE_XYZA_FLT    (FLOAT_SH(1)|COLORSPACE_SH(PT_XYZ)|EXTRA_SH(1)|CHANNELS_SH(3)|BYTES_SH(4))
/////////////////////////////////////////////////////
// TCMSConnectionFormat Specialization
template<> constexpr uint32 TCMSConnectionType< e_cm::kG >()     { return  ULIS_LCMS_DTYPE_GRAYA_FLT; }
template<> constexpr uint32 TCMSConnectionType< e_cm::kRGB >()   { return  ULIS_LCMS_DTYPE_RGBA_FLT;  }
template<> constexpr uint32 TCMSConnectionType< e_cm::kHSL >()   { return  ULIS_LCMS_DTYPE_RGBA_FLT;  }
template<> constexpr uint32 TCMSConnectionType< e_cm::kHSV >()   { return  ULIS_LCMS_DTYPE_RGBA_FLT;  }
template<> constexpr uint32 TCMSConnectionType< e_cm::kCMYK >()  { return  ULIS_LCMS_DTYPE_CMYKA_FLT; }
template<> constexpr uint32 TCMSConnectionType< e_cm::kLab >()   { return  ULIS_LCMS_DTYPE_LabA_FLT;  }
template<> constexpr uint32 TCMSConnectionType< e_cm::kXYZ >()   { return  ULIS_LCMS_DTYPE_XYZA_FLT;  }
/////////////////////////////////////////////////////
// TModelConnectionFormat Specialization
template<> constexpr uint32 TModelConnectionFormat< e_cm::kG >()     { return  FBlockfloatGhasAlphaGAnormalized::TypeId();       }
template<> constexpr uint32 TModelConnectionFormat< e_cm::kRGB >()   { return  FBlockfloatRGBhasAlphaRGBAnormalized::TypeId();   }
template<> constexpr uint32 TModelConnectionFormat< e_cm::kHSL >()   { return  FBlockfloatRGBhasAlphaRGBAnormalized::TypeId();   }
template<> constexpr uint32 TModelConnectionFormat< e_cm::kHSV >()   { return  FBlockfloatRGBhasAlphaRGBAnormalized::TypeId();   }
template<> constexpr uint32 TModelConnectionFormat< e_cm::kCMYK >()  { return  FBlockfloatCMYKhasAlphaCMYKAnormalized::TypeId(); }
template<> constexpr uint32 TModelConnectionFormat< e_cm::kLab >()   { return  FBlockfloatLabhasAlphaLabAnormalized::TypeId();   }
template<> constexpr uint32 TModelConnectionFormat< e_cm::kXYZ >()   { return  FBlockfloatXYZhasAlphaXYZAnormalized::TypeId();   }

} // namespace ULIS
