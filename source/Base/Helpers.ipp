// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         BlendHelpers.cpp
* @author       Clement Berthaud
* @brief        This file provides the definitions for the Blend entry point functions.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Base/Core.h"
#include "Base/Utils.h"
#include "Blend/Modes.h"
#include "Data/Block.h"
#include "glm/vec2.hpp"
#include <vectorclass.h>

ULIS2_NAMESPACE_BEGIN

struct _FBMTPSSSSERGBA8SP {
    const int32          mCoverageX;
    const int32          mCoverageY;
    const tSize          mSrcBps;
    const uint8          mAid;
    const Vec4f          mTX;
    const Vec4f          mTY;
    const Vec4f          mUX;
    const Vec4f          mUY;
    const eBlendingMode  mBlendingMode;
    const eAlphaMode     mAlphaMode;
    const ufloat         mOpacity;
};

struct _FBMTPSSAVXRGBA8SP {
    const int32          mCoverageX;
    const int32          mCoverageY;
    const tSize          mSrcBps;
    const uint8          mAid;
    const Vec8f          mTX;
    const Vec8f          mTY;
    const Vec8f          mUX;
    const Vec8f          mUY;
    const eBlendingMode  mBlendingMode;
    const eAlphaMode     mAlphaMode;
    const ufloat         mOpacity;
};

ULIS2_API ULIS2_FORCEINLINE void BuildIndexTable( uint8 iCOD, uint8 iSPP, uint8* oIDT, uint8* oAID ) {
    uint8 msp = iSPP - 1;
    switch( iCOD ) {
        case 1:  for( int i = 0; i < iSPP; ++i ) oIDT[i] = ( msp - i );                                 *oAID = 0;   break;
        case 2:  for( int i = 0; i < iSPP; ++i ) oIDT[i] = ( i + 1 ) > msp ? 0 : i + 1;                 *oAID = 0;   break;
        case 3:  for( int i = 0; i < iSPP; ++i ) oIDT[i] = ( msp - i ) - 1 < 0 ? msp : ( msp - i ) - 1; *oAID = msp; break;
        default: for( int i = 0; i < iSPP; ++i ) oIDT[i] = i;                                           *oAID = msp; break;
    }
}

ULIS2_API ULIS2_FORCEINLINE void BuildRGBA8IndexTable( tFormat iFmt, Vec4i* oIDT, uint8* oAID ) {
    uint8 cod = ULIS2_R_RS( iFmt );
    switch( cod ) {
        case 1:  for( int i = 0; i < 4; ++i ) oIDT->insert( i, ( 3 - i )                             ); *oAID = 0; break;
        case 2:  for( int i = 0; i < 4; ++i ) oIDT->insert( i, ( i + 1 ) > 3 ? 0 : i + 1             ); *oAID = 0; break;
        case 3:  for( int i = 0; i < 4; ++i ) oIDT->insert( i, ( 3 - i ) - 1 < 0 ? 3 : ( 3 - i ) - 1 ); *oAID = 3; break;
        default: for( int i = 0; i < 4; ++i ) oIDT->insert( i, i                                     ); *oAID = 3; break;
    }
}

ULIS2_API ULIS2_FORCEINLINE void  BuildTraceTextParams( const FBlock*   iDST
                                                       , uint8*         oBPC
                                                       , uint8*         oNCC
                                                       , uint8*         oHEA
                                                       , uint8*         oSPP
                                                       , uint8*         oBPP
                                                       , uint8*         oAID
                                                       , uint8**        oIDT
                                                       , tSize*         oBPS )
{
    tFormat fmt = iDST->Format();
    // BPC: Bytes Per Channel
    // NCC: Num Color Channel ( Without Alpha )
    // HEA: Has Extra Alpha ( 0 = false, else true )
    // SPP: Samples Per Pixel ( Number of Channels with Alpha )
    // BPP: Bytes Per Pixel ( With Alpha )
    // NUM: Number or Pixels to treat in ROI
    // AID: Alpha redirected Index
    // IDT: Redirected channels Index table, allocated here, don't forget to delete [] it outside.
    // BPS: Bytes per scanline for src
    *oBPC = iDST->BytesPerSample();
    *oNCC = iDST->NumColorChannels();
    *oHEA = iDST->HasAlpha();
    *oSPP = iDST->SamplesPerPixel();
    *oBPP = iDST->BytesPerPixel();
    *oIDT = iDST->IndexTable();
    *oAID = iDST->AlphaIndex();
    *oBPS = iDST->BytesPerScanLine();
}

template< typename T >
ULIS2_API ULIS2_FORCEINLINE
void
SampleSubpixelAlphaOpt( const tByte* iPtr, bool iHEA, uint8 iChannel, int64 iBPP, int64 iBPS, int64 iX, int64 iY, int64 iROI_X, int64 iROI_Y, int64 iROI_W, int64 iROI_H, const glm::vec2& iT, const glm::vec2& iU, float iVV0, float* oM11, float* oM10, float* oVV1, float* oRES ) {
    if( iHEA ) {
        *oM11 = ( iY < iROI_H && iX < iROI_W )              ? TYPE2FLOAT( iPtr, iChannel ) : 0.f;
        *oM10 = ( iX < iROI_W && ( iY > 0 || iROI_Y > 0 ) ) ? TYPE2FLOAT( iPtr - iBPS,        iChannel ) : 0.f;
    } else {
        *oM11 = ( iY >= iROI_H || iX >= iROI_W )    ? 0.f : 1.f;
        *oM10 = ( iX >= iROI_W || iY - 1 < 0 )      ? 0.f : 1.f;
    }
    *oVV1 = (*oM10) * iT.y + (*oM11) * iU.y;
    *oRES = iVV0 * iT.x + (*oVV1) * iU.x;
}

template< typename T >
ULIS2_API ULIS2_FORCEINLINE
float
SampleSubpixelChannelPremult( const tByte* iPtr
                            , uint8 iChannel
                            , int64 iBPP
                            , int64 iBPS
                            , int64 iX
                            , int64 iY
                            , int64 iROI_X
                            , int64 iROI_Y
                            , int64 iROI_W
                            , int64 iROI_H
                            , const glm::vec2& iT
                            , const glm::vec2& iU
                            , float iA11
                            , float iA01
                            , float iA10
                            , float iA00
                            , float iRES ) {

    float m11 = ( iY < iROI_H && iX < iROI_W )              ?               TYPE2FLOAT( iPtr,               iChannel ) : 0.f;
    float m01 = ( iY < iROI_H && ( iX > 0 || iROI_X > 0 ) ) ?               TYPE2FLOAT( iPtr - iBPP,        iChannel ) : 0.f;
    float m10 = ( iX < iROI_W && ( iY > 0 || iROI_Y > 0 ) ) ?               TYPE2FLOAT( iPtr - iBPS,        iChannel ) : 0.f;
    float m00 = ( ( iX > 0 || iROI_X > 0 ) && ( iY > 0 || iROI_Y > 0 ) ) ?  TYPE2FLOAT( iPtr - iBPS - iBPP, iChannel ) : 0.f;

    /*
    float m11 = ( iY >= iROI_H || iX >= iROI_W )    ? 0.f : TYPE2FLOAT( iPtr,               iChannel );
    float m01 = ( iY >= iROI_H || iX - 1 < 0 )      ? 0.f : TYPE2FLOAT( iPtr - iBPP,        iChannel );
    float m10 = ( iX >= iROI_W || iY - 1 < 0 )      ? 0.f : TYPE2FLOAT( iPtr - iBPS,        iChannel );
    float m00 = ( iX - 1 < 0 || iY - 1 < 0 )        ? 0.f : TYPE2FLOAT( iPtr - iBPS - iBPP, iChannel );
    */

    float v1 = ( m00 * iA00 ) * iT.y + ( m01 * iA01 ) * iU.y;
    float v2 = ( m10 * iA10 ) * iT.y + ( m11 * iA11 ) * iU.y;
    return  iRES == 0.f ? 0.f : ( ( v1 ) * iT.x + ( v2 ) * iU.x ) / iRES;
}

ULIS2_NAMESPACE_END

