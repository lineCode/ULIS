// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS3
*__________________
*
* @file         Formats.cpp
* @author       Clement Berthaud
* @brief        Formats application for wasm ULIS3.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include <stdio.h>
#include <SDL/SDL.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include <ULIS3>
using namespace ::ul3;

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    int width = 512;
    int height = 256;
    SDL_Surface *screen = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE);

    if (SDL_MUSTLOCK(screen)) SDL_LockSurface(screen);

    FBlock blockA( static_cast< uint8* >( screen->pixels ), width, height, ULIS3_FORMAT_RGBA8 );
    FBlock blockB( width, height, ULIS3_FORMAT_RGBA8 );
    FBlock blockC( 200, 200, ULIS3_FORMAT_RGBA8 );
    FThreadPool* threadPool = XCreateThreadPool();
    FHostDeviceInfo host = FHostDeviceInfo::Detect();

    Fill( threadPool, ULIS3_BLOCKING, 0, host, ULIS3_NOCB, &blockA, FPixelValue::FromRGBA8( 255, 0, 0, 255 ), blockA.Rect() );
    Fill( threadPool, ULIS3_BLOCKING, 0, host, ULIS3_NOCB, &blockB, FPixelValue::FromRGBA8( 0, 255, 0, 255 ), blockB.Rect() );
    Fill( threadPool, ULIS3_BLOCKING, 0, host, ULIS3_NOCB, &blockC, FPixelValue::FromRGBA8( 0, 0, 255, 255 ), blockC.Rect() );
    FBlock* rotatedC = XTransformAffine( threadPool, ULIS3_BLOCKING, 0, host, ULIS3_NOCB, &blockC, blockC.Rect(), FTransform2D( MakeRotationMatrix( FMaths::kPIf / 4.f ) ), INTERP_BILINEAR );

    Blend( threadPool, ULIS3_BLOCKING, 0, host, ULIS3_NOCB, &blockB, &blockA, blockB.Rect(), FVec2F( 0, 0 ), ULIS3_NOAA, BM_BAYERDITHER8x8, AM_NORMAL, 0.5f );
    Blend( threadPool, ULIS3_BLOCKING, 0, host, ULIS3_NOCB, rotatedC, &blockA, blockB.Rect(), FVec2F( 20, 20 ), ULIS3_NOAA, BM_COLOR, AM_NORMAL, 0.5f );

    if (SDL_MUSTLOCK(screen)) SDL_UnlockSurface(screen);
    SDL_Flip(screen);
    SDL_Quit();

    XDeleteBlock( rotatedC );
    XDeleteThreadPool( threadPool );
    return 0;
}
