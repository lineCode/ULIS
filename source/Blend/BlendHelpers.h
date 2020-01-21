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
#include "glm/vec2.hpp"

ULIS2_NAMESPACE_BEGIN
ULIS2_API ULIS2_FORCEINLINE void ULIS2_VECTORCALL BuildIndexTable( uint8 iCOD, uint8 iSPP, uint8* oIDT, uint8* oAID ) {
    uint8 msp = iSPP - 1;
    switch( iCOD ) {
        case 1:  for( int i = 0; i < iSPP; ++i ) oIDT[i] = ( msp - i );                                 *oAID = 0;   break;
        case 2:  for( int i = 0; i < iSPP; ++i ) oIDT[i] = ( i + 1 ) > msp ? 0 : i + 1;                 *oAID = 0;   break;
        case 3:  for( int i = 0; i < iSPP; ++i ) oIDT[i] = ( msp - i ) - 1 < 0 ? msp : ( msp - i ) - 1; *oAID = msp; break;
        default: for( int i = 0; i < iSPP; ++i ) oIDT[i] = i;                                           *oAID = msp; break;
    }
}

ULIS2_API ULIS2_FORCEINLINE void ULIS2_VECTORCALL  BuildBlendParams( uint8*         oBPC
                                                                   , uint8*         oNCC
                                                                   , uint8*         oHEA
                                                                   , uint8*         oSPP
                                                                   , uint8*         oBPP
                                                                   , tSize*         oBPS
                                                                   , tSize*         oNUM
                                                                   , uint8*         oAID
                                                                   , uint8**        oIDT
                                                                   , uint32         iFmt
                                                                   , uint32         iWidth
                                                                   , const glm::uvec2& iRoiSize ) {
    // BPC: Bytes Per Channel
    // NCC: Num Color Channel ( Without Alpha )
    // HEA: Has Extra Alpha ( 0 = false, else true )
    // SPP: Samples Per Pixel ( Number of Channels with Alpha )
    // BPP: Bytes Per Pixel ( With Alpha )
    // BPS: Bytes Per Scanline
    // NUM: Number or Pixels to treat in ROI
    // AID: Alpha redirected Index
    // IDT: Redirected channels Index table, allocated here, don't forget to delete [] it outside.
    *oBPC = ULIS2_R_DEPTH(    iFmt );
    *oNCC = ULIS2_R_CHANNELS( iFmt );
    *oHEA = ULIS2_R_ALPHA(    iFmt );
    *oSPP = (*oNCC) + (*oHEA);
    *oBPP = (*oBPC) * (*oSPP);
    *oBPS = iWidth * (*oBPP);
    *oNUM = iRoiSize.x * iRoiSize.y;
    uint8 cod = ULIS2_R_RS( iFmt ); // Reverse-Swapped layout identifier
    *oIDT = new uint8[*oSPP];
    BuildIndexTable( cod, *oSPP, *oIDT, oAID );
}

template< typename T >
ULIS2_API ULIS2_FORCEINLINE
float ULIS2_VECTORCALL
SampleSubpixelAlpha( const tByte* iPtr, uint8 iChannel, uint8 iBPP, uint8 iBPS, int64 iX, int64 iY, const glm::uvec2& iRoiSize, int64 iIndex, int64 iWidth, int64 iTotal, const glm::vec2& iT, const glm::vec2& iU ) {
    float m11 = ( iY >= iRoiSize.y || iX >= iRoiSize.x ) /*  || ( iIndex                < 0 || iIndex               >= iTotal ) */ ? 0.f : TYPE2FLOAT( iPtr,               iChannel );
    float m01 = ( iY >= iRoiSize.y || iX - 1 < 0 )       /*  || ( iIndex - 1            < 0 || iIndex - 1           >= iTotal ) */ ? 0.f : TYPE2FLOAT( iPtr - iBPP,        iChannel );
    float m10 = ( iX >= iRoiSize.x || iY - 1 < 0 )       /*  || ( iIndex - iWidth       < 0 || iIndex - iWidth      >= iTotal ) */ ? 0.f : TYPE2FLOAT( iPtr - iBPS,        iChannel );
    float m00 = ( iX - 1 < 0 || iY - 1 < 0 )             /*  || ( iIndex - iWidth - 1   < 0 || iIndex - iWidth - 1  >= iTotal ) */ ? 0.f : TYPE2FLOAT( iPtr - iBPP + iBPP, iChannel );
    float h1 = m00 * iT.x + m10 * iU.x;
    float h2 = m01 * iT.x + m11 * iU.x;
    return  h1 * iT.y + h2 * iU.y;
}

template< typename T >
ULIS2_API ULIS2_FORCEINLINE
void ULIS2_VECTORCALL
SampleSubpixelAlpha( const tByte* iPtr
                   , uint8 iChannel
                   , uint8 iBPP
                   , uint8 iBPS
                   , int64 iX
                   , int64 iY
                   , const glm::uvec2& iRoiSize
                   , int64 iIndex
                   , int64 iWidth
                   , int64 iTotal
                   , const glm::vec2& iT
                   , const glm::vec2& iU
                   , float* oM11
                   , float* oM01
                   , float* oM10
                   , float* oM00
                   , float* oHH0
                   , float* oHH1
                   , float* oRES ) {
    *oM11 = ( iY >= iRoiSize.y || iX >= iRoiSize.x )    || ( iIndex                < 0 || iIndex               >= iTotal ) ? 0.f : TYPE2FLOAT( iPtr,               iChannel );
    *oM01 = ( iY >= iRoiSize.y || iX - 1 < 0 )          || ( iIndex - 1            < 0 || iIndex - 1           >= iTotal ) ? 0.f : TYPE2FLOAT( iPtr - iBPP,        iChannel );
    *oM10 = ( iX >= iRoiSize.x || iY - 1 < 0 )          || ( iIndex - iWidth       < 0 || iIndex - iWidth      >= iTotal ) ? 0.f : TYPE2FLOAT( iPtr - iBPS,        iChannel );
    *oM00 = ( iX - 1 < 0 || iY - 1 < 0 )                || ( iIndex - iWidth - 1   < 0 || iIndex - iWidth - 1  >= iTotal ) ? 0.f : TYPE2FLOAT( iPtr - iBPP + iBPP, iChannel );
    *oHH0 = *oM00 * iT.x + *oM10 * iU.x;
    *oHH1 = *oM01 * iT.x + *oM11 * iU.x;
    *oRES = *oHH0 * iT.y + *oHH1 * iU.y;
}

template< typename T >
ULIS2_API ULIS2_FORCEINLINE
float ULIS2_VECTORCALL
SampleSubpixelChannelPremult( const tByte* iPtr
                            , uint8 iChannel
                            , uint8 iBPP
                            , uint8 iBPS
                            , int64 iX
                            , int64 iY
                            , const glm::uvec2& iRoiSize
                            , int64 iIndex
                            , int64 iWidth
                            , int64 iTotal
                            , const glm::vec2& iT
                            , const glm::vec2& iU
                            , float iA11
                            , float iA01
                            , float iA10
                            , float iA00
                            , float iHH0
                            , float iHH1
                            , float iRES ) {
    float m11 = ( iY >= iRoiSize.y || iX >= iRoiSize.x )    || ( iIndex                < 0 || iIndex               >= iTotal ) ? 0.f : TYPE2FLOAT( iPtr,               iChannel );
    float m01 = ( iY >= iRoiSize.y || iX - 1 < 0 )          || ( iIndex - 1            < 0 || iIndex - 1           >= iTotal ) ? 0.f : TYPE2FLOAT( iPtr - iBPP,        iChannel );
    float m10 = ( iX >= iRoiSize.x || iY - 1 < 0 )          || ( iIndex - iWidth       < 0 || iIndex - iWidth      >= iTotal ) ? 0.f : TYPE2FLOAT( iPtr - iBPS,        iChannel );
    float m00 = ( iX - 1 < 0 || iY - 1 < 0 )                || ( iIndex - iWidth - 1   < 0 || iIndex - iWidth - 1  >= iTotal ) ? 0.f : TYPE2FLOAT( iPtr - iBPP + iBPP, iChannel );
    float h1 = FMaths::FixInf( ( ( m00 * iA00 ) * iT.x + ( m10 * iA10 ) * iU.x ) / iHH0 );
    float h2 = FMaths::FixInf( ( ( m01 * iA01 ) * iT.x + ( m11 * iA11 ) * iU.x ) / iHH1 );
    return  FMaths::FixInf( ( ( h1 * iHH0 ) * iT.y + ( h2 * iHH1 ) * iU.y ) / iRES );
}

ULIS2_NAMESPACE_END

