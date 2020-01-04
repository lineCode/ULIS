// Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Palettes.h
* @author       Clement Berthaud
* @brief        This file provides classic color palettes definitions.
* @copyright    Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core.h"
#include "Color.h"

ULIS2_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
// Color Palettes

/////////////////////////////////////////////////////
// eMSWindows
static const FColor white       ( 255, 255, 255 );
static const FColor black       ( 0,   0,   0   );
static const FColor red         ( 255, 0,   0   );
static const FColor darkRed     ( 128, 0,   0   );
static const FColor green       ( 0,   255, 0   );
static const FColor darkGreen   ( 0,   128, 0   );
static const FColor blue        ( 0,   0,   255 );
static const FColor darkBlue    ( 0,   0,   128 );
static const FColor cyan        ( 0,   255, 255 );
static const FColor darkCyan    ( 0,   128, 128 );
static const FColor magenta     ( 255, 0,   255 );
static const FColor darkMagenta ( 128, 0,   128 );
static const FColor yellow      ( 255, 255, 0   );
static const FColor darkYellow  ( 128, 128, 0   );
static const FColor gray        ( 160, 160, 164 );
static const FColor darkGray    ( 128, 128, 128 );
static const FColor lightGray   ( 192, 192, 192 );

/////////////////////////////////////////////////////
// PaletteMSPaintDebug 
static const FColor paletteMSPaintDebug[] = {
    CColor( 237,  28,  36 ),
    CColor( 255, 127,  39 ),
    CColor( 255, 242,   0 ),
    CColor(  34, 177,  76 ),
    CColor(   0, 162, 232 ),
    CColor(  63,  72, 204 ),
    CColor( 163,  73, 164 ),
    CColor( 255, 174, 201 ),
    CColor( 255, 201,  14 ),
    CColor( 239, 228, 176 ),
    CColor( 181, 230,  29 ),
    CColor( 153, 217, 234 ),
    CColor( 112, 146, 190 ),
    CColor( 200, 191, 231 ),
}; // colors[]
static constexpr int paletteMSPaintDebug_length = sizeof( colors ) / sizeof( CColor );

ULIS2_NAMESPACE_END

