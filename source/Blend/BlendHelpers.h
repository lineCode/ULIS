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
                                                                   , const FRect&   iROI ) {
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
    *oBPS = iROI.w * (*oBPP);
    *oNUM = iROI.w * iROI.h;
    uint8 cod = ULIS2_R_RS( iFmt ); // Reverse-Swapped layout identifier
    *oIDT = new uint8[*oSPP];
    BuildIndexTable( cod, *oSPP, *oIDT, oAID );
}
ULIS2_NAMESPACE_END

