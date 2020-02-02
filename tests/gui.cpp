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
using namespace ::ul2;

int
main( int argc, char *argv[] )
{
    int width;
    int height;
    int channels;
    unsigned char *rawtest = stbi_load( "C:/Users/PRAXINOS/Documents/work/TEST.png", &width, &height, &channels, STBI_rgb_alpha );

    FBlock blockA( 512, 512, ULIS2_FORMAT_RGBA8 );
    FBlock blockB( rawtest, width, height, ULIS2_FORMAT_RGBA8, nullptr, FOnInvalid(), FOnCleanup( &OnCleanup_FreeMemory ) );

    FThreadPool pool;
    FPerf perf_low( Perf_Lowest );
    FPerf perf_best( Perf_Best_CPU );
    FCPU cpu_info;
    FPixel red( ULIS2_FORMAT_RGB8, { 198, 145, 46 } );
    FPixel green( ULIS2_FORMAT_RGB8, { 79, 184, 46 } );
    Fill( &pool,  ULIS2_BLOCKING, perf_best, cpu_info, &blockA, red, ULIS2_NOCB );
    //Fill( &pool,  ULIS2_BLOCKING, perf_best, cpu_info, &blockB, green, ULIS2_NOCB );

    for( int y = 0; y < 64; ++y ) {
        float t = ( 1.f - y / 64.f );
        for( int x = 0; x < 64; ++x )
            blockB.PixelProxy( x, y ).SetAlpha( t );
    }

    FFontEngine fontEngine;
    FFontRegistry fontRegistry;
    fontRegistry.Load( fontEngine );
    FFont font( fontEngine, fontRegistry, "Arial", "Black" );
    FT_Face face = font.Handle();
    FT_Error error = FT_Set_Pixel_Sizes( face, 0, 16 );
    FT_UInt glyph_index = FT_Get_Char_Index( face, 'A' );
    error = FT_Load_Glyph( face, glyph_index, FT_LOAD_DEFAULT );
    /* convert to an anti-aliased bitmap */
    error = FT_Render_Glyph( face->glyph, FT_RENDER_MODE_NORMAL );

    FT_Int  x_max = face->glyph->bitmap.width;
    FT_Int  y_max = face->glyph->bitmap.rows;

    for( int x = 0; x < x_max; ++x ) {
        for( int y = 0; y < y_max; ++y ) {
            FPixelProxy prox = blockB.PixelProxy( x, y );
            uint8 val = face->glyph->bitmap.buffer[ y * x_max + x ];
            prox.SetR8 ( 0 );
            prox.SetG8 ( 0 );
            prox.SetB8 ( 0 );
            prox.SetA8 ( val );
        }
    }

    for( int i = 0; i < NUM_BLENDING_MODES; ++i ) {
        int y = ( i / 8 ) * 64;
        int x = ( i % 8 ) * 64;
        BlendRect( &pool, ULIS2_BLOCKING, perf_low, cpu_info, ULIS2_NOSUBPIXEL, &blockB, &blockA, FRect( 0, 0, 64, 64 ), glm::vec2( x, y ), eBlendingMode( i ), AM_NORMAL, 0.5f, ULIS2_CALLCB );
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

