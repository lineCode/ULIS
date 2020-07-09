// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS3
*__________________
*
* @file         Format.cpp
* @author       Clement Berthaud
* @brief        This file provides the definition for the Format utilities.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include "Data/Format.h"

ULIS3_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
// FFormat
FFormat::~FFormat() {
    if( IDT ) delete [] IDT;
}

FFormat::FFormat( tFormat iFMT )
    : IDT( nullptr )
    , FMT( iFMT )
    , TP( static_cast< eType >( ULIS3_R_TYPE( FMT ) ) )
    , CM( static_cast< eColorModel >( ULIS3_R_MODEL( FMT ) ) )
    , BPC( ULIS3_R_DEPTH( FMT ) )
    , NCC( ULIS3_R_CHANNELS( FMT ) )
    , HEA( ULIS3_R_ALPHA( FMT ) )
    , RSC( ULIS3_R_RS( FMT ) )
    , SPP( NCC + HEA )
    , BPP( SPP * BPC )
    , AID( 0 )
    , REV( ULIS3_R_REVERSE( FMT ) )
    , SWA( ULIS3_R_SWAP( FMT ) )
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
{
    iOther.IDT = nullptr;
}

ULIS3_NAMESPACE_END

