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
#include <ULIS2>
#include <QApplication>
#include <QWidget>
#include <QImage>
#include <QPixmap>
#include <QLabel>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>
using namespace ::ul2;

#include <glm/gtx/matrix_transform_2d.hpp>

int
main( int argc, char *argv[] )
{
    int wb, hb, wo, ho, cb, co;
    unsigned char *base = stbi_load( "C:/Users/PRAXINOS/Documents/work/base_160.png",   &wb, &hb, &cb, STBI_rgb_alpha );
    unsigned char *over = stbi_load( "C:/Users/PRAXINOS/Documents/work/detail_160.png", &wo, &ho, &co, STBI_rgb_alpha );

    FBlock  blockA( wb * 8, wb * 5, ULIS2_FORMAT_RGBA8 );
    FBlock  blockBase( base, wb, hb, ULIS2_FORMAT_RGBA8, nullptr, FOnInvalid(), FOnCleanup( &OnCleanup_FreeMemory ) );
    FBlock  blockOver( over, wo, ho, ULIS2_FORMAT_RGBA8, nullptr, FOnInvalid(), FOnCleanup( &OnCleanup_FreeMemory ) );
    FBlock  blockC( wb, 20, ULIS2_FORMAT_RGBA8 );

    FThreadPool     threadPool(64);
    FPerf           perfIntent( Perf_Best_CPU );
    FCPU            cpuInfo;

    FPixel  red(    ULIS2_FORMAT_RGB8, { 255, 0, 0 } );
    FPixel  green(  ULIS2_FORMAT_RGB8, { 0, 255, 0 } );
    FPixel  black(  ULIS2_FORMAT_RGB8, { 0, 0, 0 } );
    FPixel  white(  ULIS2_FORMAT_RGB8, { 255, 255, 255 } );

    Fill( &threadPool,  ULIS2_NONBLOCKING, perfIntent, cpuInfo, &blockA, black, ULIS2_NOCB );
    Fill( &threadPool,  ULIS2_NONBLOCKING, perfIntent, cpuInfo, &blockC, black, ULIS2_NOCB );
    threadPool.WaitForCompletion();

    FFontEngine     fontEngine;
    FFontRegistry   fontRegistry( fontEngine );
    fontRegistry.Load();
    FFont font = fontRegistry.LoadFont( "Arial", "Regular" );

    for( int i = 0; i < NUM_BLENDING_MODES; ++i ) {
        int y = ( i / 8 ) * wb;
        int x = ( i % 8 ) * wb;
        Blend( &threadPool, ULIS2_BLOCKING, perfIntent, cpuInfo, ULIS2_SUBPIXEL, &blockBase, &blockA, glm::vec2( x, y ), BM_NORMAL, AM_NORMAL, 1.f, ULIS2_CALLCB );
        Blend( &threadPool, ULIS2_BLOCKING, perfIntent, cpuInfo, ULIS2_SUBPIXEL, &blockOver, &blockA, glm::vec2( x, y ), eBlendingMode( i ), AM_NORMAL, 0.75f, ULIS2_CALLCB );
        Blend( &threadPool, ULIS2_BLOCKING, perfIntent, cpuInfo, ULIS2_SUBPIXEL, &blockC, &blockA, glm::vec2( x, y + hb - 20 ), BM_NORMAL, AM_NORMAL, 0.5f, ULIS2_NOCB );
        Blend( &threadPool, ULIS2_BLOCKING, perfIntent, cpuInfo, ULIS2_SUBPIXEL, &blockC, &blockA, glm::vec2( x, y + hb - 20 ), BM_BAYERDITHER8x8, AM_NORMAL, 0.5f, ULIS2_NOCB );
        TraceText( &threadPool, ULIS2_BLOCKING, perfIntent, cpuInfo, ULIS2_AA, &blockA, kwBlendingMode[ i ], font, 16, white, glm::vec2( x, y + hb - 20 ), glm::mat2( 1.f ), ULIS2_NOCB );
    }

    glm::mat2 mat = glm::rotate( glm::mat3( 1.f ), 0.785f );
    FRect metrics = TextMetrics( "Hello World", font, 16, glm::vec2( 64 ), mat );
    FillRect( &threadPool, ULIS2_BLOCKING, perfIntent, cpuInfo, &blockA, red, metrics, ULIS2_NOCB );
    TraceText( &threadPool, ULIS2_BLOCKING, perfIntent, cpuInfo, ULIS2_AA, &blockA, "Hello World", font, 16, white, glm::vec2( 64 ), mat, ULIS2_NOCB );

    FBlock blockLab( blockA.Width(), blockA.Height(), ULIS2_FORMAT_Lab32 );
    FColor labGreen = Conv( green, ULIS2_FORMAT_Lab32 );
    FColor labRed = Conv( red, ULIS2_FORMAT_Lab32 );
    FColor interp = Conv( red, ULIS2_FORMAT_Lab32 );
    for( int x = 0; x < blockLab.Width(); ++x ) {
        udouble t = x / static_cast< udouble >( blockLab.Width() );
        interp.SetL32( labGreen.L32() * ( 1 - t ) + labRed.L32() * t );
        interp.Seta32( labGreen.a32() * ( 1 - t ) + labRed.a32() * t );
        interp.Setb32( labGreen.b32() * ( 1 - t ) + labRed.b32() * t );
        for( int y = 0; y < blockLab.Height(); ++y ) {
            blockLab.PixelProxy( x, y ).AssignMemoryUnsafe( interp );
        }
    }
    FBlock* grad = XConv( &threadPool, ULIS2_BLOCKING, perfIntent, cpuInfo, &blockLab, ULIS2_FORMAT_RGBA8 );
    Blend( &threadPool, ULIS2_BLOCKING, perfIntent, cpuInfo, ULIS2_SUBPIXEL, grad, &blockA, ULIS2_NODELTA, BM_COLOR, AM_NORMAL, 0.9f, ULIS2_NOCB );
    delete grad;

    // Qt Window
    QApplication app( argc, argv );
    QWidget* widget = new  QWidget();
    QImage*  image  = new  QImage( blockA.DataPtr(), blockA.Width(), blockA.Height(), blockA.BytesPerScanLine(), QImage::Format::Format_RGBA8888 );
    QPixmap  pixmap = QPixmap::fromImage( *image );
    QLabel*  label  = new  QLabel( widget );
    label->setPixmap( pixmap );
    widget->resize( pixmap.size() );
    widget->show();

    int exit_code = app.exec();

    delete  label;
    delete  image;
    delete  widget;

    return  exit_code;
}

