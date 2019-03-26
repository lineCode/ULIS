/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Imaging.CompileTime.BlockID.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once

#include "ULIS/Imaging/CompileTime/ULIS.Imaging.CompileTime.ParsingPPFramework.h"


namespace ULIS {
/////////////////////////////////////////////////////
// Enum and Keyword Declaration
// memory_layout
#define ULIS_KEYS_ML ULIS_KEYS( interleaved, planar )
ULIS_KEYS_TO_KEYWORDS(  _ml, ULIS_KEYS_ML )
ULIS_KEYS_TO_ENUM(      _ml, ULIS_KEYS_ML )
// alpha_mode
#define ULIS_KEYS_AM ULIS_KEYS( straight, premultiplied )
ULIS_KEYS_TO_KEYWORDS(  _am, ULIS_KEYS_AM )
ULIS_KEYS_TO_ENUM(      _am, ULIS_KEYS_AM )
// type
#define ULIS_KEYS_TP ULIS_KEYS( uint8, uint16, uint32, int8, int16, int32, float, double )
ULIS_KEYS_TO_KEYWORDS(  _tp, ULIS_KEYS_TP )
ULIS_KEYS_TO_ENUM(      _tp, ULIS_KEYS_TP )
// arithmetical_set
#define ULIS_KEYS_AS ULIS_KEYS( natural, integer, decimal, rational, real, complex )
ULIS_KEYS_TO_KEYWORDS(  _as, ULIS_KEYS_AS )
ULIS_KEYS_TO_ENUM(      _as, ULIS_KEYS_AS )
// color_model
#define ULIS_KEYS_CM ULIS_KEYS( RGB, HSL, HSV, LAB, XYZ, CMY, CMYK )
ULIS_KEYS_TO_KEYWORDS(  _cm, ULIS_KEYS_CM )
ULIS_KEYS_TO_ENUM(      _cm, ULIS_KEYS_CM )
// endian_mode
#define ULIS_KEYS_EM ULIS_KEYS( big, little, default )
ULIS_KEYS_TO_KEYWORDS(  _em, ULIS_KEYS_EM )
ULIS_KEYS_TO_ENUM(      _em, ULIS_KEYS_EM )
// normal_mode
#define ULIS_KEYS_NM ULIS_KEYS( anormal, normal )
ULIS_KEYS_TO_KEYWORDS(  _nm, ULIS_KEYS_NM )
ULIS_KEYS_TO_ENUM(      _nm, ULIS_KEYS_NM )

#define ULIS_KEYS_ALL ULIS_KEYS( ULIS_KEYS_DATA_TYPE )


/////////////////////////////////////////////////////
// BlockInfo
struct FBlockInfo
{
    const  e_ml         _ml; // memory_layout
    const  e_am         _am; // alpha_mode
    const  e_tp         _tp; // type
    const  e_as         _as; // arithmetical_set
    const  e_cm         _cm; // color_model
    const  e_em         _em; // endian_mode
    const  uint16       _pd; // pixel_depth
    const  uint8        _nc; // num_channels
    const  bool         _ea; // extra_alpha
};


/////////////////////////////////////////////////////
// ParseSpecStr
template< int N >
static constexpr const FBlockInfo ParseSpecStr( _CT::const_str< N > spec_str )
{
    return  { e_ml::kinterleaved
            , e_am::kstraight
            , e_tp::kuint8
            , e_as::knatural
            , e_cm::kRGB
            , e_em::kdefault
            , 32
            , 4
            , true
            };
}


/////////////////////////////////////////////////////
// TBlockSpec
template< uint32 > struct TBlockSpec {};

} // namespace ULIS

