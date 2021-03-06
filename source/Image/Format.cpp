// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS
*__________________
*
* @file         Format.cpp
* @author       Clement Berthaud
* @brief        This file provides the definition for the Format utilities.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include "Image/Format.h"

ULIS_NAMESPACE_BEGIN
FFormat::~FFormat() {
    if( IDT ) delete [] IDT;
}

FFormat::FFormat( eFormat iFMT )
    : IDT( nullptr )
    , FMT( iFMT )
    , TP( static_cast< eType >( ULIS_R_TYPE( FMT ) ) )
    , CM( static_cast< eColorModel >( ULIS_R_MODEL( FMT ) ) )
    , BPC( ULIS_R_DEPTH( FMT ) )
    , NCC( ULIS_R_CHANNELS( FMT ) )
    , HEA( ULIS_R_ALPHA( FMT ) )
    , RSC( ULIS_R_RS( FMT ) )
    , SPP( NCC + HEA )
    , BPP( SPP * BPC )
    , AID( 0 )
    , REV( ULIS_R_REVERSE( FMT ) )
    , SWA( ULIS_R_SWAP( FMT ) )
    , PRE( ULIS_R_PREMULT( FMT ) )
    , LIN( ULIS_R_LINEAR( FMT ) )
    , PRO( ULIS_R_PROFILE( FMT ) )
    , PLA( ULIS_R_PLANAR( FMT ) )
{
    IDT = new uint8[ SPP ];
    uint8 msp = SPP - 1;
    switch( RSC ) {
        case 1:  for( int i = 0; i < SPP; ++i ) IDT[i] = ( msp - i );                                   AID = 0;   break;
        case 2:  for( int i = 0; i < SPP; ++i ) IDT[i] = ( i + 1 ) > msp ? 0 : i + 1;                   AID = 0;   break;
        case 3:  for( int i = 0; i < SPP; ++i ) IDT[i] = ( msp - i ) - 1 < 0 ? msp : ( msp - i ) - 1;   AID = msp; break;
        default: for( int i = 0; i < SPP; ++i ) IDT[i] = i;                                             AID = msp; break;
    }
}

FFormat::FFormat( const FFormat& iOther )
    : IDT( nullptr )
    , FMT( iOther.FMT )
    , TP( iOther.TP )
    , CM( iOther.CM )
    , BPC( iOther.BPC )
    , NCC( iOther.NCC )
    , HEA( iOther.HEA )
    , RSC( iOther.RSC )
    , SPP( iOther.SPP )
    , BPP( iOther.BPP )
    , AID( iOther.AID )
    , REV( iOther.REV )
    , SWA( iOther.SWA )
    , PRE( iOther.PRE )
    , LIN( iOther.LIN )
    , PRO( iOther.PRO )
    , PLA( iOther.PLA )
{
    IDT = new uint8[ SPP ];
    memcpy( IDT, iOther.IDT, SPP );
}

FFormat&
FFormat::operator=( const FFormat& iOther )
{
    if( IDT ) delete [] IDT;
    FMT = iOther.FMT;
    TP  = iOther.TP;
    CM  = iOther.CM;
    BPC = iOther.BPC;
    NCC = iOther.NCC;
    HEA = iOther.HEA;
    RSC = iOther.RSC;
    SPP = iOther.SPP;
    BPP = iOther.BPP;
    AID = iOther.AID;
    REV = iOther.REV;
    SWA = iOther.SWA;
    PRE = iOther.PRE;
    LIN = iOther.LIN;
    PRO = iOther.PRO;
    PLA = iOther.PLA;

    IDT = new uint8[ SPP ];
    memcpy( IDT, iOther.IDT, SPP );
    return  *this;
}

FFormat::FFormat( FFormat&& iOther )
    : IDT( iOther.IDT )
    , FMT( iOther.FMT )
    , TP( iOther.TP )
    , CM( iOther.CM )
    , BPC( iOther.BPC )
    , NCC( iOther.NCC )
    , HEA( iOther.HEA )
    , RSC( iOther.RSC )
    , SPP( iOther.SPP )
    , BPP( iOther.BPP )
    , AID( iOther.AID )
    , REV( iOther.REV )
    , SWA( iOther.SWA )
    , PRE( iOther.PRE )
    , LIN( iOther.LIN )
    , PRO( iOther.PRO )
    , PLA( iOther.PLA )
{
    iOther.IDT = nullptr;
}

ULIS_NAMESPACE_END

