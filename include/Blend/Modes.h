// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Pçdes.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the Blend and Alpha modes enums and related info.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Base/Core.h"

ULIS2_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
// eBlendingMode
enum eBlendingMode
{
      BM_NORMAL
    , BM_TOP
    , BM_BACK
    , BM_BEHIND
    , BM_DISSOLVE
    , BM_BAYERDITHER8x8
    , BM_DARKEN
    , BM_MULTIPY
    , BM_COLORBURN
    , BM_LINEARBURN
    , BM_DARKERCOLOR
    , BM_LIGHTEN
    , BM_SCREEN
    , BM_COLORDODGE
    , BM_LINEARDODGE
    , BM_LIGHTERCOLOR
    , BM_OVERLAY
    , BM_SOFTLIGHT
    , BM_HARDLIGHT
    , BM_VIVIDLIGHT
    , BM_LINEARLIGHT
    , BM_PINLIGHT
    , BM_HARDMIX
    , BM_PHOENIX
    , BM_REFLECT
    , BM_GLOW
    , BM_DIFFERENCE
    , BM_EXCLUSION
    , BM_ADD
    , BM_SUBSTRACT
    , BM_DIVIDE
    , BM_AVERAGE
    , BM_HUE
    , BM_SATURATION
    , BM_COLOR
    , BM_LUMINOSITY
    , NUM_BLENDING_MODES
};


static const char* kwBlendingMode[] =
{
      "Normal"
    , "Top"
    , "Back"
    , "Behind"
    , "Dissolve"
    , "OrderedDitheringBayer8x8"
    , "Darken"
    , "Multiply"
    , "ColorBurn"
    , "LinearBurn"
    , "DarkerColor"
    , "Lighten"
    , "Screen"
    , "ColorDodge"
    , "LinearDodge"
    , "LighterColor"
    , "Overlay"
    , "SoftLight"
    , "HardLight"
    , "VividLight"
    , "LinearLight"
    , "PinLight"
    , "HardMix"
    , "Phoenix"
    , "Reflect"
    , "Glow"
    , "Difference"
    , "Exclusion"
    , "Add"
    , "Substract"
    , "Divide"
    , "Average"
    , "Hue"
    , "Saturation"
    , "Color"
    , "Luminosity"
    , "Invalid"
};


/////////////////////////////////////////////////////
// eAlphaMode
enum eAlphaMode
{
      AM_NORMAL
    , AM_ERASE
    , AM_TOP
    , AM_BACK
    , AM_SUB
    , AM_ADD
    , AM_MUL
    , AM_MIN
    , AM_MAX
    , AM_INVMAX
    , NUM_ALPHA_MODES
};


static const char* kwAlphaMode[] =
{
      "Normal"
    , "Erase"
    , "Top"
    , "Back"
    , "Sub"
    , "Add"
    , "Mul"
    , "Min"
    , "Max"
    , "InvMax"
    , "Invalid"
};


enum eBlendingModeQualifier
{
      BMQ_SEPARABLE
    , BMQ_NONSEPARABLE
    , BMQ_MISC
};


static
inline
constexpr
eBlendingModeQualifier
BlendingModeQualifier( eBlendingMode iBlendingMode )
{
    switch( iBlendingMode ) {
        case BM_DISSOLVE        :   return  BMQ_MISC;
        case BM_BAYERDITHER8x8  :   return  BMQ_MISC;
        case BM_DARKERCOLOR     :   return  BMQ_NONSEPARABLE;
        case BM_LIGHTERCOLOR    :   return  BMQ_NONSEPARABLE;
        case BM_HUE             :   return  BMQ_NONSEPARABLE;
        case BM_SATURATION      :   return  BMQ_NONSEPARABLE;
        case BM_COLOR           :   return  BMQ_NONSEPARABLE;
        case BM_LUMINOSITY      :   return  BMQ_NONSEPARABLE;
        default                 :   return  BMQ_SEPARABLE;
    }
}

#define ULIS2_ENCODE_BM_AM( iBM, iAM )  uint32( uint32( iBM ) | ( uint32( iAM ) << 16 ) )
#define ULIS2_DECODE_BM( iENCODED )     eBlendingMode( iENCODED & 0xFFFF )
#define ULIS2_DECODE_AM( iENCODED )     eBlendingMode( ( iENCODED >> 16 ) & 0xFFFF )

// Macro for all types for template instanciation
#define ULIS2_FOR_ALL_SEPARABLE_BM_DO( X, _E0, _E1, _E2, _E3 )  \
    X( BM_NORMAL            , _E0, _E1, _E2, _E3 )              \
    X( BM_TOP               , _E0, _E1, _E2, _E3 )              \
    X( BM_BACK              , _E0, _E1, _E2, _E3 )              \
    X( BM_BEHIND            , _E0, _E1, _E2, _E3 )              \
    X( BM_DARKEN            , _E0, _E1, _E2, _E3 )              \
    X( BM_MULTIPY           , _E0, _E1, _E2, _E3 )              \
    X( BM_COLORBURN         , _E0, _E1, _E2, _E3 )              \
    X( BM_LINEARBURN        , _E0, _E1, _E2, _E3 )              \
    X( BM_LIGHTEN           , _E0, _E1, _E2, _E3 )              \
    X( BM_SCREEN            , _E0, _E1, _E2, _E3 )              \
    X( BM_COLORDODGE        , _E0, _E1, _E2, _E3 )              \
    X( BM_LINEARDODGE       , _E0, _E1, _E2, _E3 )              \
    X( BM_OVERLAY           , _E0, _E1, _E2, _E3 )              \
    X( BM_SOFTLIGHT         , _E0, _E1, _E2, _E3 )              \
    X( BM_HARDLIGHT         , _E0, _E1, _E2, _E3 )              \
    X( BM_VIVIDLIGHT        , _E0, _E1, _E2, _E3 )              \
    X( BM_LINEARLIGHT       , _E0, _E1, _E2, _E3 )              \
    X( BM_PINLIGHT          , _E0, _E1, _E2, _E3 )              \
    X( BM_HARDMIX           , _E0, _E1, _E2, _E3 )              \
    X( BM_PHOENIX           , _E0, _E1, _E2, _E3 )              \
    X( BM_REFLECT           , _E0, _E1, _E2, _E3 )              \
    X( BM_GLOW              , _E0, _E1, _E2, _E3 )              \
    X( BM_DIFFERENCE        , _E0, _E1, _E2, _E3 )              \
    X( BM_EXCLUSION         , _E0, _E1, _E2, _E3 )              \
    X( BM_ADD               , _E0, _E1, _E2, _E3 )              \
    X( BM_SUBSTRACT         , _E0, _E1, _E2, _E3 )              \
    X( BM_DIVIDE            , _E0, _E1, _E2, _E3 )              \
    X( BM_AVERAGE           , _E0, _E1, _E2, _E3 )

#define ULIS2_FOR_ALL_NONSEPARABLE_BM_DO( X, _E0, _E1, _E2, _E3 )   \
    X( BM_DARKERCOLOR       , _E0, _E1, _E2, _E3 )                  \
    X( BM_LIGHTERCOLOR      , _E0, _E1, _E2, _E3 )                  \
    X( BM_HUE               , _E0, _E1, _E2, _E3 )                  \
    X( BM_SATURATION        , _E0, _E1, _E2, _E3 )                  \
    X( BM_COLOR             , _E0, _E1, _E2, _E3 )                  \
    X( BM_LUMINOSITY        , _E0, _E1, _E2, _E3 )

#define ULIS2_FOR_ALL_MISC_BM_DO( X, _E0, _E1, _E2, _E3 )   \
    X( BM_DISSOLVE          , _E0, _E1, _E2, _E3 )          \
    X( BM_BAYERDITHER8x8    , _E0, _E1, _E2, _E3 )

#define ULIS2_FOR_ALL_BM_DO( X, _E0, _E1, _E2, _E3 )            \
    ULIS2_FOR_ALL_SEPARABLE_BM_DO(      X, _E0, _E1, _E2, _E3 ) \
    ULIS2_FOR_ALL_NONSEPARABLE_BM_DO(   X, _E0, _E1, _E2, _E3 ) \
    ULIS2_FOR_ALL_MISC_BM_DO(           X, _E0, _E1, _E2, _E3 )

#define ULIS2_FOR_ALL_AM_DO( X, _E0, _E1, _E2, _E3 )    \
    X( AM_NORMAL        , _E0, _E1, _E2, _E3 )          \
    X( AM_ERASE         , _E0, _E1, _E2, _E3 )          \
    X( AM_TOP           , _E0, _E1, _E2, _E3 )          \
    X( AM_BACK          , _E0, _E1, _E2, _E3 )          \
    X( AM_SUB           , _E0, _E1, _E2, _E3 )          \
    X( AM_ADD           , _E0, _E1, _E2, _E3 )          \
    X( AM_MUL           , _E0, _E1, _E2, _E3 )          \
    X( AM_MIN           , _E0, _E1, _E2, _E3 )          \
    X( AM_MAX           , _E0, _E1, _E2, _E3 )          \
    X( AM_INVMAX        , _E0, _E1, _E2, _E3 )

//#define ULIS2_ENUM_CASE_AM_DO( _AM, _BM, _ACTION, _E2, _E3 )                                                        case _AM: _ACTION( _BM, _AM, _E2, _E3 ); break;
//#define ULIS2_ENUM_CASE_BM_SWITCH_FOR_ALL_AM_DO( _BM, iAlphaMode, _ACTION, _E2, _E3 )                               case _BM: switch( iAlphaMode ) { ULIS2_FOR_ALL_AM_DO( ULIS2_ENUM_CASE_AM_DO, _BM, _ACTION, _E2, _E3 ) } break;
//#define ULIS2_SWITCH_FOR_ALL_BM_SUBSET_AM_COMBINATIONS_DO( iBlendingMode, iAlphaMode, _SUBSET, _ACTION, _E2, _E3 )  switch( iBlendingMode ) { _SUBSET( ULIS2_ENUM_CASE_BM_SWITCH_FOR_ALL_AM_DO, iAlphaMode, _ACTION, _E2, _E3 ) }
//#define ULIS2_RET_COMP_OP( _BM, _AM, iSubpixel, _FUNCTION )                                                         return  iSubpixel ? & _FUNCTION ## _Subpixel < T, _BM, _AM > : & _FUNCTION < T, _BM, _AM >;
//#define ULIS2_SELECT_COMP_OP( _SUBSET, iBlendingMode, iAlphaMode, iSubpixel, _FUNCTION )                            ULIS2_SWITCH_FOR_ALL_BM_SUBSET_AM_COMBINATIONS_DO( iBlendingMode, iAlphaMode, _SUBSET, ULIS2_RET_COMP_OP, iSubpixel, _FUNCTION )

//#define ULIS2_COMBINE_DO( _AM, _BM, _TYPE, _ACTION, _E2 )                                   _ACTION( _TYPE, _BM, _AM, _E2 )
//#define ULIS2_ENUMERATE_AM_DO( _BM, _TYPE, _ACTION, _E2, _E3 )                              ULIS2_FOR_ALL_AM_DO( ULIS2_COMBINE_DO, _BM, _TYPE, _ACTION, _E2 )
//#define ULIS2_ENUMERATE_BM_SUBSET_AM_COMBINATIONS_DO( _TYPE, _SUBSET, _ACTION, _E2, _E3 )   _SUBSET( ULIS2_ENUMERATE_AM_DO, _TYPE, _ACTION, _E2, _E3 )
//#define ULIS2_ENUMERATE_TYPES_BM_SUBSET_AM_COMBINATIONS_DO( _SUBSET, _ACTION, _E2, _E3 )    ULIS2_FOR_ALL_TYPES_DO( ULIS2_ENUMERATE_BM_SUBSET_AM_COMBINATIONS_DO, _SUBSET, _ACTION, _E2, _E3 )

//#define ULIS2_DELETE_COMP_OP_INSTANCIATION_IMP( _TYPE, _BM, _AM, _FUNCTION ) template<> void _FUNCTION < _TYPE, _BM, _AM >( const FBlock*, FBlock*, const FRect&, const FRect&, const glm::vec2&, ufloat, const FPerf& ) = delete;
//#define ULIS2_DELETE_COMP_OP_INSTANCIATION( _SUBSET, _FUNCTION ) ULIS2_ENUMERATE_TYPES_BM_SUBSET_AM_COMBINATIONS_DO( _SUBSET, ULIS2_DELETE_COMP_OP_INSTANCIATION_IMP, _FUNCTION, 0 )

#define ULIS2_SELECT_COMP_OP( iSubpixel, _FUNCTION )    iSubpixel ? & _FUNCTION ## _Subpixel < T > : & _FUNCTION < T >

#define ULIS2_ENUM_CASE_DO( _CASE, _ACTION, _E1, _E2, _E3 )  case _CASE: _ACTION( _CASE, _E1, _E2, _E3 ); break;
#define ULIS2_SWITCH_FOR_ALL_DO( iValue, _SUBSET, _ACTION, _E1, _E2, _E3 )  switch( iValue ) { _SUBSET( ULIS2_ENUM_CASE_DO, _ACTION, _E1, _E2, _E3 ) }

#define ULIS2_ACTION_ASSIGN_ALPHAF( _AM, iTarget, iSrc, iBdp )   iTarget = AlphaF< _AM >( iSrc, iBdp );
#define ULIS2_ACTION_ASSIGN_ALPHASSEF( _AM, iTarget, iSrc, iBdp )   iTarget = AlphaSSEF< _AM >( iSrc, iBdp );
#define ULIS2_ASSIGN_ALPHAF( iAlphaMode, iTarget, iSrc, iBdp )  ULIS2_SWITCH_FOR_ALL_DO( iAlphaMode, ULIS2_FOR_ALL_AM_DO, ULIS2_ACTION_ASSIGN_ALPHAF, iTarget, iSrc, iBdp )
#define ULIS2_ASSIGN_ALPHASSEF( iAlphaMode, iTarget, iSrc, iBdp )  ULIS2_SWITCH_FOR_ALL_DO( iAlphaMode, ULIS2_FOR_ALL_AM_DO, ULIS2_ACTION_ASSIGN_ALPHASSEF, iTarget, iSrc, iBdp )

ULIS2_NAMESPACE_END

