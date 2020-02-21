// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         gui.cpp
* @author       Clement Berthaud
* @brief        Gui application for ULIS2.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include <QApplication>
#include <QWidget>
#include <QImage>
#include <QPixmap>
#include <QLabel>
#include <ULIS2>
#include <chrono>

using namespace ::ul2;

int
main( int argc, char *argv[] )
{
    FThreadPool     threadPool;
    FPerf           perfIntentSSE( 0 );
    FPerf           perfIntentAVX( 0 );
    FCPU            cpuInfo;
    FFontEngine     fontEngine;
    FFontRegistry   fontRegistry( fontEngine );
    FFont           font = fontRegistry.LoadFont( "Arial", "Regular" );
    FBlock*         blockBase = XLoadFromFile( &threadPool, ULIS2_BLOCKING, perfIntentAVX, cpuInfo, "C:/Users/conta/Documents/work/pattern.png", ULIS2_FORMAT_RGBA8 );
    FBlock*         blockOver = XLoadFromFile( &threadPool, ULIS2_BLOCKING, perfIntentAVX, cpuInfo, "C:/Users/conta/Documents/work/Over.png", ULIS2_FORMAT_RGBA8 );
    int             wb = blockBase->Width();
    int             hb = blockBase->Height();
    FBlock          blockA( 800, 600, ULIS2_FORMAT_RGBA8 );
    FBlock          blockB( 1, 1, ULIS2_FORMAT_RGBA8 );
    FBlock          blockC( wb, 20, ULIS2_FORMAT_RGBA8 );

    float tx, ty, r, sx, sy, skx, sky;
    auto _t = MakeTranslationMatrix( 50, 20 );
    auto _r = MakeRotationMatrix( 1.57 );
    auto _s = MakeScaleMatrix( 5, 8 );
    auto comp = ComposeMatrix( ComposeMatrix( _s, _r ), _t );
    FTransform2D trans( comp );
    trans.DecomposeMatrix( &tx, &ty, &r, &sx, &sy, &skx, &sky );

    FPixel red(    ULIS2_FORMAT_RGB8, { 255,   0,      0   } );
    FPixel green(  ULIS2_FORMAT_RGB8, { 0,     255,    0   } );
    FPixel black(  ULIS2_FORMAT_RGB8, { 0,     0,      0   } );
    FPixel white(  ULIS2_FORMAT_RGB8, { 255,   255,    255 } );
    Clear( &threadPool, ULIS2_BLOCKING, perfIntentAVX, cpuInfo, &blockA, ULIS2_NOCB );
    Fill( &threadPool, ULIS2_BLOCKING, perfIntentAVX, cpuInfo, &blockC, black, ULIS2_NOCB );

    Fill( &threadPool, ULIS2_BLOCKING, perfIntentAVX, cpuInfo, &blockA, green, ULIS2_NOCB );
    Fill( &threadPool, ULIS2_BLOCKING, perfIntentAVX, cpuInfo, &blockB, red, ULIS2_NOCB );
    //Blend( &threadPool, ULIS2_BLOCKING, perfIntentAVX, cpuInfo, ULIS2_NOAA, blockBase, &blockA, 64.5, 64.5, BM_NORMAL, AM_NORMAL, 1.f, ULIS2_CALLCB );


    FPerfInfo perfParams = {};
    perfParams.pool       = &threadPool;
    perfParams.intent     = FPerf( 0 );
    perfParams.blocking   = ULIS2_BLOCKING;
    perfParams.callCB     = ULIS2_NOCB;

    FBlendInfo blendParams = {};
    blendParams.source              = blockBase;
    blendParams.backdrop            = &blockA;
    blendParams.sourceRect          = FRect( 0, 0, 65, 65 );
    blendParams.backdropPosition    = FVec2F( -20.5, -20.5 );
    blendParams.subpixelFlag        = ULIS2_AA;
    blendParams.blendingMode        = BM_NORMAL;
    blendParams.alphaMode           = AM_NORMAL;
    blendParams.opacityValue        = 1.f;
    BlendRect( perfParams, blendParams );

    // Qt Window
    QApplication    app( argc, argv );
    QWidget*        widget  = new QWidget();
    QImage*         image   = new QImage( blockA.DataPtr(), blockA.Width(), blockA.Height(), blockA.BytesPerScanLine(), QImage::Format::Format_RGBA8888 );
    QPixmap         pixmap  = QPixmap::fromImage( *image );
    QLabel*         label   = new QLabel( widget );
    label->setPixmap( pixmap );
    widget->resize( pixmap.size() );
    widget->show();

    std::cout << "Show";
    int exit_code = app.exec();

    delete  label;
    delete  image;
    delete  widget;
    delete  blockBase;
    delete  blockOver;
    return  exit_code;
}