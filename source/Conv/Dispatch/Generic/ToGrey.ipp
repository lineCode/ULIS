// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         ToGrey.ipp
* @author       Clement Berthaud
* @brief        This file provides the definition for model conversion functions.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Base/Core.h"

ULIS2_NAMESPACE_BEGIN
template< typename T1, typename T2 >
void ConvBufferGreyToGrey( tFormat iSrcFormat, const tByte* iSrc, tSize iSrcBytes, tFormat iDstFormat, tByte* iDst, tSize iDstBytes ) {
    // src info
    uint8 src_bpc = ULIS2_R_DEPTH(      iSrcFormat );
    uint8 src_ncc = ULIS2_R_CHANNELS(   iSrcFormat );
    uint8 src_hea = ULIS2_R_ALPHA(      iSrcFormat );
    uint8 src_spp = src_ncc + src_hea;
    uint8 src_bpp = src_spp * src_bpc;
    tSize src_len = iSrcBytes / src_bpp;

    // dst info
    uint8 dst_bpc = ULIS2_R_DEPTH(      iDstFormat );
    uint8 dst_ncc = ULIS2_R_CHANNELS(   iDstFormat );
    uint8 dst_hea = ULIS2_R_ALPHA(      iDstFormat );
    uint8 dst_spp = dst_ncc + dst_hea;
    uint8 dst_bpp = dst_spp * dst_bpc;
    tSize dst_len = iDstBytes / dst_bpp;

    int32 len;
    while( len-- ) {
    }
}


template< typename T1, typename T2 >
void ConvBufferGreyToRGB( tFormat iSrcFormat, const tByte* iSrc, tSize iSrcBytes, tFormat iDstFormat, tByte* iDst, tSize iDstBytes ) {
}


template< typename T1, typename T2 >
void ConvBufferGreyToHSV( tFormat iSrcFormat, const tByte* iSrc, tSize iSrcBytes, tFormat iDstFormat, tByte* iDst, tSize iDstBytes ) {
}


template< typename T1, typename T2 >
void ConvBufferGreyToHSL( tFormat iSrcFormat, const tByte* iSrc, tSize iSrcBytes, tFormat iDstFormat, tByte* iDst, tSize iDstBytes ) {
}


template< typename T1, typename T2 >
void ConvBufferGreyToCMY( tFormat iSrcFormat, const tByte* iSrc, tSize iSrcBytes, tFormat iDstFormat, tByte* iDst, tSize iDstBytes ) {
}


template< typename T1, typename T2 >
void ConvBufferGreyToCMYK( tFormat iSrcFormat, const tByte* iSrc, tSize iSrcBytes, tFormat iDstFormat, tByte* iDst, tSize iDstBytes ) {
}


template< typename T1, typename T2 >
void ConvBufferGreyToYUV( tFormat iSrcFormat, const tByte* iSrc, tSize iSrcBytes, tFormat iDstFormat, tByte* iDst, tSize iDstBytes ) {
}


template< typename T1, typename T2 >
void ConvBufferGreyToLab( tFormat iSrcFormat, const tByte* iSrc, tSize iSrcBytes, tFormat iDstFormat, tByte* iDst, tSize iDstBytes ) {
}


template< typename T1, typename T2 >
void ConvBufferGreyToXYZ( tFormat iSrcFormat, const tByte* iSrc, tSize iSrcBytes, tFormat iDstFormat, tByte* iDst, tSize iDstBytes ) {
}


template< typename T1, typename T2 >
void ConvBufferGreyToYxy( tFormat iSrcFormat, const tByte* iSrc, tSize iSrcBytes, tFormat iDstFormat, tByte* iDst, tSize iDstBytes ) {
}

ULIS2_NAMESPACE_END
