// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         AlphaFuncF.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the ufloat Blending functions.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Base/Core.h"
#include "Blend/Modes.h"
#include "Maths/Maths.h"

ULIS2_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
// Standard Alpha Modes
//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------- Normal
ULIS2_FORCEINLINE ufloat ULIS2_VECTORCALL AlphaNormalF( ufloat iCs, ufloat iCb ) {
    return ( iCb + iCs ) - ( iCb * iCs );
}
//--------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------- Erase
ULIS2_FORCEINLINE ufloat ULIS2_VECTORCALL AlphaEraseF( ufloat iCs, ufloat iCb ) {
    return ( 1.f - iCs ) * iCb;
}
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------- Back
ULIS2_FORCEINLINE ufloat ULIS2_VECTORCALL AlphaBackF( ufloat iCs, ufloat iCb ) {
    return iCb;
}
//--------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------- Top
ULIS2_FORCEINLINE ufloat ULIS2_VECTORCALL AlphaTopF( ufloat iCs, ufloat iCb ) {
    return iCs;
}
//--------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------- Sub
ULIS2_FORCEINLINE ufloat ULIS2_VECTORCALL AlphaSubF( ufloat iCs, ufloat iCb ) {
    return  iCb > iCs ? iCb - iCs : 0;
}
//--------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------- Add
ULIS2_FORCEINLINE ufloat ULIS2_VECTORCALL AlphaAddF( ufloat iCs, ufloat iCb ) {
    return  ( 1.f - iCb ) > iCs ? iCb + iCs : 1.f;
}
//--------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------- Mul
ULIS2_FORCEINLINE ufloat ULIS2_VECTORCALL AlphaMulF( ufloat iCs, ufloat iCb ) {
    return  iCb * iCs;
}
//--------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------- Min
ULIS2_FORCEINLINE ufloat ULIS2_VECTORCALL AlphaMinF( ufloat iCs, ufloat iCb ) {
    return  FMaths::Min( iCs, iCb );
}
//--------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------- Max
ULIS2_FORCEINLINE ufloat ULIS2_VECTORCALL AlphaMaxF( ufloat iCs, ufloat iCb ) {
    return  FMaths::Max( iCs, iCb );
}
//--------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------- InvMax
ULIS2_FORCEINLINE ufloat ULIS2_VECTORCALL AlphaInvMaxF( ufloat iCs, ufloat iCb ) {
    ufloat invCs = iCs == 0.f ? 0.f : 1.f / iCs;
    ufloat invCb = iCb == 0.f ? 0.f : 1.f / iCb;
    ufloat max = FMaths::Max( invCs, invCb );
    ufloat res = max == 0.f ? 0.f : 1.f / max;
    return  res;
}

ULIS2_NAMESPACE_END

