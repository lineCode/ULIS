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
#include <vectorclass.h>
#include <Windows.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>
using namespace ::ul2;

#include <glm/gtx/matrix_transform_2d.hpp> 

int
main( int argc, char *argv[] )
{
    int width;
    int height;
    int channels;
    unsigned char *base = stbi_load( "C:/Users/PRAXINOS/Documents/work/base_160.png",   &width, &height, &channels, STBI_rgb_alpha );
    unsigned char *over = stbi_load( "C:/Users/PRAXINOS/Documents/work/detail_160.png", &width, &height, &channels, STBI_rgb_alpha );

    FBlock blockA( 1280, 800, ULIS2_FORMAT_RGBA8 );
    FBlock blockBase( base, width, height, ULIS2_FORMAT_RGBA8, nullptr, FOnInvalid(), FOnCleanup( &OnCleanup_FreeMemory ) );
    FBlock blockOver( over, width, height, ULIS2_FORMAT_RGBA8, nullptr, FOnInvalid(), FOnCleanup( &OnCleanup_FreeMemory ) );
    FBlock blockC( 160, 20, ULIS2_FORMAT_RGBA8 );

    FThreadPool pool( 1 );
    FPerf perf_low( Perf_Lowest );
    FPerf perf_best( Perf_Best_CPU );
    FCPU cpu_info;
    FPixel red( ULIS2_FORMAT_RGB8, { 255, 0, 0 } );
    FPixel green( ULIS2_FORMAT_RGB8, { 0, 255, 0 } );
    FPixel black( ULIS2_FORMAT_RGB8, { 0, 0, 0 } );
    FPixel blue( ULIS2_FORMAT_RGB8, { 46, 124, 220 } );
    FPixel white( ULIS2_FORMAT_RGB8, { 255, 255, 255 } );
    //Fill( &pool,  ULIS2_BLOCKING, perf_best, cpu_info, &blockBase, red, ULIS2_NOCB );
    //Fill( &pool,  ULIS2_BLOCKING, perf_best, cpu_info, &blockOver, green, ULIS2_NOCB );
    Clear( &pool,  ULIS2_BLOCKING, perf_best, cpu_info, &blockA, ULIS2_NOCB );
    Fill( &pool,  ULIS2_BLOCKING, perf_best, cpu_info, &blockC, black, ULIS2_NOCB );
    /*
    for( int y = 0; y < 64; ++y ) {
        float t = ( 1.f - y / 64.f );
        for( int x = 0; x < 64; ++x )
            blockB.PixelProxy( x, y ).SetAlpha( t );
    }
    */

    FFontEngine fontEngine;
    FFontRegistry fontRegistry;
    fontRegistry.Load( fontEngine );
    FFont font_arialRegular( fontEngine, fontRegistry, "Segoe UI", "Regular" );

    for( int i = 0; i < NUM_BLENDING_MODES; ++i ) {
        int y = ( i / 8 ) * 160;
        int x = ( i % 8 ) * 160;
        Blend( &pool, ULIS2_BLOCKING, perf_best, cpu_info, ULIS2_NOSUBPIXEL, &blockBase, &blockA, glm::vec2( x, y ), BM_NORMAL, AM_NORMAL, 1.f, ULIS2_CALLCB );
        Blend( &pool, ULIS2_BLOCKING, perf_best, cpu_info, ULIS2_NOSUBPIXEL, &blockOver, &blockA, glm::vec2( x, y ), eBlendingMode( i ), AM_NORMAL, 0.5f, ULIS2_CALLCB );
        Blend( &pool, ULIS2_BLOCKING, perf_best, cpu_info, ULIS2_NOSUBPIXEL, &blockC, &blockA, glm::vec2( x, y + 160.f - 20 ), BM_NORMAL, AM_NORMAL, 0.5f, ULIS2_NOCB );
        TraceText( &pool, ULIS2_NONBLOCKING, perf_best, cpu_info, ULIS2_AA, &blockA, kwBlendingMode[ i ], font_arialRegular, 16, white, glm::vec2( x, y + 160.f - 20 ), glm::mat2( 1.f ), ULIS2_NOCB );
    }

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

