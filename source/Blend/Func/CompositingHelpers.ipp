// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS3
*__________________
*
* @file         CompositingHelpers.ipp
* @author       Clement Berthaud
* @brief        This file provides the declaration for the compositing helper functions.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"
#include "Blend/Modes.h"
#include <vectorclass.h>

#define SampleSubpixelAlpha( _DST )                                                                                 \
if( fmt.HEA ) {                                                                                               \
    m11 = ( notLastCol && notLastLine )                     ? TYPE2FLOAT( src,              fmt.AID ) : 0.f;  \
    m10 = ( notLastCol && ( notFirstLine || hasTopData ) )  ? TYPE2FLOAT( src - iSrcBps,    fmt.AID ) : 0.f;  \
} else {                                                                                                            \
    m11 = ( notLastCol && notLastLine )     ? 1.f : 0.f;                                                            \
    m10 = ( notLastCol && notFirstLine )    ? 1.f : 0.f;                                                            \
}                                                                                                                   \
vv1 = m10 * info.subpixelComponent.y + m11 * info.buspixelComponent.y;                                    \
_DST = vv0 * info.subpixelComponent.x + vv1 * info.buspixelComponent.x;

#define SampleSubpixelChannel( _DST, _CHAN )                                                                                            \
s11 = ( notLastCol  && notLastLine )                                    ?   TYPE2FLOAT( src,                            _CHAN ) : 0.f;  \
s01 = ( notLastLine && ( x > 0 || hasLeftData ) )                       ?   TYPE2FLOAT( src - fmt.BPP,            _CHAN ) : 0.f;  \
s10 = ( notLastCol && ( notFirstLine || hasTopData ) )                  ?   TYPE2FLOAT( src - iSrcBps,                  _CHAN ) : 0.f;  \
s00 = ( ( x > 0 || hasLeftData ) && ( notFirstLine || hasTopData ) )    ?   TYPE2FLOAT( src - iSrcBps - fmt.BPP,  _CHAN ) : 0.f;  \
v1 = ( s00 * m00 ) * info.subpixelComponent.y + ( s01 * m01 ) * info.buspixelComponent.y;                                     \
v2 = ( s10 * m10 ) * info.subpixelComponent.y + ( s11 * m11 ) * info.buspixelComponent.y;                                     \
_DST = res == 0.f ? 0.f : ( ( v1 ) * info.subpixelComponent.x + ( v2 ) * info.buspixelComponent.x ) / res;

#define ULIS3_ACTION_ASSIGN_ALPHAF( _AM, iTarget, iSrc, iBdp )                          iTarget = AlphaF< _AM >( iSrc, iBdp );
#define ULIS3_ACTION_ASSIGN_ALPHASSEF( _AM, iTarget, iSrc, iBdp )                       iTarget = AlphaSSEF< _AM >( iSrc, iBdp );
#define ULIS3_ACTION_ASSIGN_ALPHAAVXF( _AM, iTarget, iSrc, iBdp )                       iTarget = AlphaAVXF< _AM >( iSrc, iBdp );
#define ULIS3_ASSIGN_ALPHAF( iAlphaMode, iTarget, iSrc, iBdp )                          ULIS3_SWITCH_FOR_ALL_DO( iAlphaMode, ULIS3_FOR_ALL_AM_DO, ULIS3_ACTION_ASSIGN_ALPHAF, iTarget, iSrc, iBdp )
#define ULIS3_ASSIGN_ALPHASSEF( iAlphaMode, iTarget, iSrc, iBdp )                       ULIS3_SWITCH_FOR_ALL_DO( iAlphaMode, ULIS3_FOR_ALL_AM_DO, ULIS3_ACTION_ASSIGN_ALPHASSEF, iTarget, iSrc, iBdp )
#define ULIS3_ASSIGN_ALPHAAVXF( iAlphaMode, iTarget, iSrc, iBdp )                       ULIS3_SWITCH_FOR_ALL_DO( iAlphaMode, ULIS3_FOR_ALL_AM_DO, ULIS3_ACTION_ASSIGN_ALPHAAVXF, iTarget, iSrc, iBdp )

ULIS3_NAMESPACE_BEGIN
ULIS3_API ULIS3_FORCEINLINE void BuildRGBA8IndexTable( uint8 iRS, Vec4i* oIDT ) {
    switch( iRS ) {
        case 1:  for( int i = 0; i < 4; ++i ) oIDT->insert( i, ( 3 - i )                             ); break;
        case 2:  for( int i = 0; i < 4; ++i ) oIDT->insert( i, ( i + 1 ) > 3 ? 0 : i + 1             ); break;
        case 3:  for( int i = 0; i < 4; ++i ) oIDT->insert( i, ( 3 - i ) - 1 < 0 ? 3 : ( 3 - i ) - 1 ); break;
        default: for( int i = 0; i < 4; ++i ) oIDT->insert( i, i                                     ); break;
    }
}

ULIS3_NAMESPACE_END

