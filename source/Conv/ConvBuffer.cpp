// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         ConvBuffer.cpp
* @author       Clement Berthaud
* @brief        This file provides the definitions for the ConvBuffer entry point functions.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include "Conv/Conv.h"
#include "Maths/Maths.h"
#include "Color/Illuminants.h"
#include "Color/ModelCompat.h"
#include "Color/ColorProfile.h"
#include "Color/ProfileRegistry.h"
#include "Color/srgb2linear.h"
#include "lcms2.h"
//Dispatch
#include "Conv/Dispatch/DispatchType.ipp"

ULIS2_NAMESPACE_BEGIN

ULIS2_NAMESPACE_END


/*
void
ProfileConvBuffer( FColorProfile* iSrcProfile, tFormat iSrcFormat, const tByte* iSrc, tSize iSrcBytes
                 , FColorProfile* iDstProfile, tFormat iDstFormat,       tByte* iDst, tSize iDstBytes, uint32 iIntent = 0 )
{
    ULIS2_ASSERT( iSrcProfile, "Bad profile" );
    ULIS2_ASSERT( iDstProfile, "Bad profile" );
    ULIS2_ASSERT( iSrc, "Bad source" );
    ULIS2_ASSERT( iDst, "Bad destination" );

    tFormat src_lcms2_format = F42( iSrcFormat );
    tFormat dst_lcms2_format = F42( iDstFormat );
    cmsHPROFILE hInProfile  = iSrcProfile->ProfileHandle();
    cmsHPROFILE hOutProfile = iDstProfile->ProfileHandle();

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

    // Check
    ULIS2_ASSERT( src_len == dst_len, "Bad data provided" );

    cmsHTRANSFORM hTransform;
    hTransform = cmsCreateTransform( hInProfile
                                   , src_lcms2_format
                                   , hOutProfile
                                   , dst_lcms2_format
                                   , INTENT_PERCEPTUAL, 0 );
    cmsDoTransform( hTransform, iSrc, iDst, src_len );
    cmsDeleteTransform( hTransform );
}
*/