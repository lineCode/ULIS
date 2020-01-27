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
using namespace ::ul2;

int
main( int argc, char *argv[] )
{
    {
        FBlock test( 1, 1, ULIS2_FORMAT_RGBA8 );
        FPixelProxy prox = test.PixelProxy( 0, 0 );
        FPixelValue valu0( ULIS2_FORMAT_RGBA8 );
        FPixelValue valu1( ULIS2_FORMAT_RGBA8, { 255_u8, 255_u8, 255_u8, 255_u8 } );
        IPixel* pix = &prox;
        FPixelValue t0 = prox;
        auto dummy = 0;
    }

    /*
    {
        Vec16uc src( 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 );
        Vec16us ex16 = extend( src );
        Vec16ui ex32 = extend( ex16 );
        Vec16f  dst = to_float( ex32 );
        auto dummy = 0;
    }
    */

    //8bit mul
    /*
    {
        Vec16uc a( 0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xA, 0xB, 0xC, 0xD, 0xE, 0xF );
        Vec16uc b( 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF );
        Vec16us mul = extend( a ) * extend( b );
        Vec16uc res = compress( ( mul + 1 + ( mul >> 8 ) ) >> 8 );
        auto dummy = 0;
    }
    */

    QApplication app( argc, argv );
    int width   = 512;
    int height  = 512;
    FBlock blockA( width, height, ULIS2_FORMAT_RGBA8 );
    FBlock blockB( width, height, ULIS2_FORMAT_RGBA8 );

    FThreadPool pool;
    FPerf perf_low( Perf_Lowest );
    FPerf perf_best( Perf_Best_CPU );
    FPixel green(   ULIS2_FORMAT_RGB8, { 0, 255, 0 } );
    FPixel red(     ULIS2_FORMAT_RGB8, { 255, 0, 0 } );
    Fill( &pool, &blockA, green, perf_best, ULIS2_NOCB );
    Fill( &pool, &blockB, red,   perf_best, ULIS2_NOCB );

    for( int x = 0; x < 512; ++x ) {
        float t = (float)x / (float)512;
        for( int y = 0; y < 512; ++y ) {
            blockB.PixelProxy( x, y ).SetAlpha8( t * 255 );
        }
    }

    BlendRect( &pool, ULIS2_BLOCKING, ULIS2_SUBPIXEL, &blockB, &blockA, FRect( 0, 0, 256, 256 ), glm::vec2( 32.5f, 32.5f ), BM_LIGHTEN, AM_NORMAL, 0.8f, perf_low, ULIS2_CALLCB );

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

