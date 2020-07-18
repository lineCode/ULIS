// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS3
*__________________
*
* @file         Sample.cpp
* @author       Clement Berthaud
* @brief        This file provides the definition for the ISample classes.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include "Data/Sample.h"

ULIS3_NAMESPACE_BEGIN
ISample::~ISample()
{}

ISample::ISample( uint8* iData, tFormat iFormat, const FColorSpace* iColorSpace )
    : IHasFormat( iFormat )
    , IHasColorSpace( iColorSpace )
    , mSignal( iData )
{
}

bool
ISample::operator==( const  ISample& iOther )  const {

    if( Format() != iOther.Format() )
        return  false;


    bool bytePerfectMatch = true;
    for( int i = 0; i < BytesPerPixel(); ++i ) {
        if( mSignal[i] != iOther.mSignal[i] ) {
            bytePerfectMatch = false;
            break;
        }
    }

    return  bytePerfectMatch;
}

bool
ISample::operator!=( const  ISample& iOther )  const {
    return  !( *this == iOther );
}

uint8*
ISample::Bits()
{
    return  mSignal;
}

const uint8*
ISample::Bits() const
{
    return  mSignal;
}

ULIS3_NAMESPACE_END

