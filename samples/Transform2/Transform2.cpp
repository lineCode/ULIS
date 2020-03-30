// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS3
*__________________
*
* @file         Transform.cpp
* @author       Clement Berthaud
* @brief        Transform application for ULIS3.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
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
    FThreadPool  threadPool;
    FHostDeviceInfo host = FHostDeviceInfo::Detect();
    uint32 perfIntent = ULIS3_PERF_MT | ULIS3_PERF_TSPEC | ULIS3_PERF_SSE42 | ULIS3_PERF_AVX2;

    std::string path = "C:/Users/PRAXINOS/Documents/work/TEST.png";
    FBlock* source = XLoadFromFile( &threadPool, ULIS3_BLOCKING, perfIntent, host, ULIS3_NOCB, path, ULIS3_FORMAT_RGBA8 );
    FBlock* canvas = new  FBlock( 1200, 1000, ULIS3_FORMAT_RGBA8 );
    glm::mat3 translation = MakeTranslationMatrix( 0, 0 );
    glm::mat3 scale = MakeScaleMatrix( 8, 8 );
    glm::mat3 rotation = MakeRotationMatrix( FMaths::kPIf / 4 );

    std::vector< FVec2F > dstpoints = { FVec2F( 0, 0 ), FVec2F( source->Width(), 10 ), FVec2F( source->Width(), source->Height() - 10 ), FVec2F( 0, source->Height() ) };
    for( auto& it : dstpoints ) {
        it.x += 30;
        it.y += 30;
    }
    FBlock* transformed = XTransformPerspective( &threadPool, ULIS3_BLOCKING, perfIntent, host, ULIS3_NOCB, source, source->Rect(), dstpoints, INTERP_BILINEAR );
    Clear( &threadPool, ULIS3_BLOCKING, 0, host, ULIS3_NOCB, canvas, canvas->Rect() );
    Blend( &threadPool, ULIS3_BLOCKING, perfIntent, host, ULIS3_NOCB, transformed, canvas, transformed->Rect(), FVec2F( 20, 20 ), ULIS3_NOAA, BM_NORMAL, AM_NORMAL, 1.f );

    delete  source;
    delete  transformed;

    QApplication    app( argc, argv );
    QWidget*        widget  = new QWidget();
    QImage*         image   = new QImage( canvas->DataPtr()
                                        , canvas->Width()
                                        , canvas->Height()
                                        , canvas->BytesPerScanLine()
                                        , QImage::Format_RGBA8888 );
    QPixmap         pixmap  = QPixmap::fromImage( *image );
    QLabel*         label   = new QLabel( widget );
    label->setPixmap( pixmap );
    widget->resize( pixmap.size() );
    widget->show();

    int exit_code = app.exec();

    delete  label;
    delete  image;
    delete  widget;

    delete  canvas;

    return  exit_code;
}
