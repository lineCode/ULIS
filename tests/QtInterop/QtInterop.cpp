// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS3
*__________________
*
* @file         QtInterop.cpp
* @author       Clement Berthaud
* @brief        Gui application for ULIS3.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include <ULIS3>

#include <QApplication>
#include <QWidget>
#include <QImage>
#include <QPixmap>
#include <QLabel>

using namespace ::ul3;

int
main( int argc, char *argv[] ) {
    FThreadPool* threadPool = XCreateThreadPool();
    uint32 perfIntent = ULIS3_PERF_SSE42 | ULIS3_PERF_AVX2;
    FHostDeviceInfo host = FHostDeviceInfo::Detect();

    FBlock* blockA = new FBlock( 256, 256, ULIS3_FORMAT_RGBA8 );

    ::ul3::Clear( threadPool, ULIS3_BLOCKING, perfIntent, host, ULIS3_NOCB, blockA, blockA->Rect() );
    FPixelValue color = FPixelValue::FromRGBA8( 255, 0, 0, 255 );

    FVec2F P0( 75, 52 );
    FVec2F P1( 75, 52 );
    FVec2F P2( 139, 69 );
    FVec2F P3( 202, 17 );

    std::vector< FVec2F > points;
    uint32 count = 10;
    CatmullRomPoints( P0, P1, P2, P3, count, &points, 0.5f );
    for( int i = 0; i < count; ++i ) {
        FPixelProxy prox = blockA->PixelProxy( points[i].x, points[i].y );
        prox.SetA8( 255 );
    }

    // Qt Window
    QApplication    app( argc, argv );
    QWidget*        widget  = new QWidget();
    QImage*         image   = new QImage( blockA->DataPtr(), blockA->Width(), blockA->Height(), blockA->BytesPerScanLine(), QImage::Format::Format_RGBA8888 );
    QPixmap         pixmap  = QPixmap::fromImage( *image );
    QLabel*         label   = new QLabel( widget );
    label->setPixmap( pixmap );
    widget->resize( pixmap.size() );
    widget->show();

    int exit_code = app.exec();

    delete  label;
    delete  image;
    delete  widget;

    delete  blockA;
    XDeleteThreadPool( threadPool );
    return  exit_code;
}

