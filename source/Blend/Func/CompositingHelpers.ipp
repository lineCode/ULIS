// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         CompositingHelpers.ipp
* @author       Clement Berthaud
* @brief        This file provides the declaration for the compositing helper functions.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once

#define SampleSubpixelAlpha( _DST )                                                                                 \
if( iFmtInfo->HEA ) {                                                                                               \
    m11 = ( notLastCol && notLastLine )                     ? TYPE2FLOAT( src,              iFmtInfo->AID ) : 0.f;  \
    m10 = ( notLastCol && ( notFirstLine || hasTopData ) )  ? TYPE2FLOAT( src - iSrcBps,    iFmtInfo->AID ) : 0.f;  \
} else {                                                                                                            \
    m11 = ( notLastCol && notLastLine )     ? 1.f : 0.f;                                                            \
    m10 = ( notLastCol && notFirstLine )    ? 1.f : 0.f;                                                            \
}                                                                                                                   \
vv1 = m10 * blendInfo.backdropPosition.y + m11 * blendInfo._buspixelComponent.y;                                    \
_DST = vv0 * blendInfo.backdropPosition.x + vv1 * blendInfo._buspixelComponent.x;

#define SampleSubpixelChannel( _DST, _CHAN )                                                                                            \
s11 = ( notLastCol  && notLastLine )                                    ?   TYPE2FLOAT( src,                            _CHAN ) : 0.f;  \
s01 = ( notLastLine && ( x > 0 || hasLeftData ) )                       ?   TYPE2FLOAT( src - iFmtInfo->BPP,            _CHAN ) : 0.f;  \
s10 = ( notLastCol && ( notFirstLine || hasTopData ) )                  ?   TYPE2FLOAT( src - iSrcBps,                  _CHAN ) : 0.f;  \
s00 = ( ( x > 0 || hasLeftData ) && ( notFirstLine || hasTopData ) )    ?   TYPE2FLOAT( src - iSrcBps - iFmtInfo->BPP,  _CHAN ) : 0.f;  \
v1 = ( s00 * m00 ) * blendInfo.backdropPosition.y + ( s01 * m01 ) * blendInfo._buspixelComponent.y;                                     \
v2 = ( s10 * m10 ) * blendInfo.backdropPosition.y + ( s11 * m11 ) * blendInfo._buspixelComponent.y;                                     \
_DST = res == 0.f ? 0.f : ( ( v1 ) * blendInfo.backdropPosition.x + ( v2 ) * blendInfo._buspixelComponent.x ) / res;
