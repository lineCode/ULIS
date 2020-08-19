// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS
*__________________
*
* @file         AlphaFuncAVX.h
* @author       Clement Berthaud
* @brief        This file provides the implementations for the Vec8f Alpha Modes functions.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"
#include "Blend/Modes.h"
#include "Math/Math.h"
#include <vectorclass.h>

ULIS_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
// Standard Alpha Modes
//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------- Normal
ULIS_FORCEINLINE Vec8f ULIS_VECTORCALL AlphaNormalAVXF( Vec8f iCs, Vec8f iCb ) {
    return ( iCb + iCs ) - ( iCb * iCs );
}
//--------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------- Erase
ULIS_FORCEINLINE Vec8f ULIS_VECTORCALL AlphaEraseAVXF( Vec8f iCs, Vec8f iCb ) {
    return ( 1.f - iCs ) * iCb;
}
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------- Back
ULIS_FORCEINLINE Vec8f ULIS_VECTORCALL AlphaBackAVXF( Vec8f iCs, Vec8f iCb ) {
    return iCb;
}
//--------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------- Top
ULIS_FORCEINLINE Vec8f ULIS_VECTORCALL AlphaTopAVXF( Vec8f iCs, Vec8f iCb ) {
    return iCs;
}
//--------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------- Sub
ULIS_FORCEINLINE Vec8f ULIS_VECTORCALL AlphaSubAVXF( Vec8f iCs, Vec8f iCb ) {
    return  max( iCb - iCs, Vec8f( 0 ) );
}
//--------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------- Add
ULIS_FORCEINLINE Vec8f ULIS_VECTORCALL AlphaAddAVXF( Vec8f iCs, Vec8f iCb ) {
    return  min( iCb + iCs, Vec8f( 1.f ) );
}
//--------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------- Mul
ULIS_FORCEINLINE Vec8f ULIS_VECTORCALL AlphaMulAVXF( Vec8f iCs, Vec8f iCb ) {
    return  iCb * iCs;
}
//--------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------- Min
ULIS_FORCEINLINE Vec8f ULIS_VECTORCALL AlphaMinAVXF( Vec8f iCs, Vec8f iCb ) {
    return  min( iCs, iCb );
}
//--------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------- Max
ULIS_FORCEINLINE Vec8f ULIS_VECTORCALL AlphaMaxAVXF( Vec8f iCs, Vec8f iCb ) {
    return  max( iCs, iCb );
}

/////////////////////////////////////////////////////
// AlphaAVXF Template Selector
//--------------------------------------------------------------------------------------
//-------------------------------------------------- Generic AlphaAVXF Template Selector
template< eAlphaMode _AM >
ULIS_FORCEINLINE Vec8f ULIS_VECTORCALL AlphaAVXF( Vec8f iCs, Vec8f iCb ) {
    ULIS_ASSERT( false, "Alpha Specialization Not Implemented" );
    return  Vec8f( 0.f );
}

//--------------------------------------------------------------------------------------
//------------------------------------------ AlphaAVXF Template Selector Specializations
template<> ULIS_FORCEINLINE Vec8f ULIS_VECTORCALL AlphaAVXF< AM_NORMAL    >( Vec8f iCs, Vec8f iCb ) { return  AlphaNormalAVXF(    iCs, iCb ); }
template<> ULIS_FORCEINLINE Vec8f ULIS_VECTORCALL AlphaAVXF< AM_ERASE     >( Vec8f iCs, Vec8f iCb ) { return  AlphaEraseAVXF(     iCs, iCb ); }
template<> ULIS_FORCEINLINE Vec8f ULIS_VECTORCALL AlphaAVXF< AM_TOP       >( Vec8f iCs, Vec8f iCb ) { return  AlphaTopAVXF(       iCs, iCb ); }
template<> ULIS_FORCEINLINE Vec8f ULIS_VECTORCALL AlphaAVXF< AM_BACK      >( Vec8f iCs, Vec8f iCb ) { return  AlphaBackAVXF(      iCs, iCb ); }
template<> ULIS_FORCEINLINE Vec8f ULIS_VECTORCALL AlphaAVXF< AM_SUB       >( Vec8f iCs, Vec8f iCb ) { return  AlphaSubAVXF(       iCs, iCb ); }
template<> ULIS_FORCEINLINE Vec8f ULIS_VECTORCALL AlphaAVXF< AM_ADD       >( Vec8f iCs, Vec8f iCb ) { return  AlphaAddAVXF(       iCs, iCb ); }
template<> ULIS_FORCEINLINE Vec8f ULIS_VECTORCALL AlphaAVXF< AM_MUL       >( Vec8f iCs, Vec8f iCb ) { return  AlphaMulAVXF(       iCs, iCb ); }
template<> ULIS_FORCEINLINE Vec8f ULIS_VECTORCALL AlphaAVXF< AM_MIN       >( Vec8f iCs, Vec8f iCb ) { return  AlphaMinAVXF(       iCs, iCb ); }
template<> ULIS_FORCEINLINE Vec8f ULIS_VECTORCALL AlphaAVXF< AM_MAX       >( Vec8f iCs, Vec8f iCb ) { return  AlphaMaxAVXF(       iCs, iCb ); }

ULIS_NAMESPACE_END

