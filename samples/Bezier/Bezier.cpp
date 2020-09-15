// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS3
*__________________
*
* @file         Transform.cpp
* @author       Clement Berthaud
* @brief        Transform application for ULIS3.
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
    FHostDeviceInfo host = FHostDeviceInfo::Detect();
    uint32 perfIntent = 0 | ULIS3_PERF_SSE42 | ULIS3_PERF_AVX2;

    std::string path = "C:/Users/PRAXINOS/Documents/work/TEST.png";
    FBlock* blockSRC = XLoadFromFile( threadPool, ULIS3_BLOCKING, perfIntent, host, ULIS3_NOCB, path, ULIS3_FORMAT_RGBA8 );
    FBlock* blockDST = new  FBlock( 1024, 1024, ULIS3_FORMAT_RGBA8 );
    Clear( threadPool, ULIS3_BLOCKING, perfIntent, host, ULIS3_NOCB, blockDST, blockDST->Rect() );

    int size = 256;
    int shift = 100;
    FVec2F A( shift, shift );
    FVec2F B( shift + size, shift );
    FVec2F C( shift + size, shift + size );
    FVec2F D( shift, shift + size );
    std::vector< FBezierCubicControlPoint > ctrlpoints = { { A, A + FVec2F( 50, -50 ), A }
                                                         , { B, B, B }
                                                         , { C, C + FVec2F( -50, -50 ), C }
                                                         , { D, D + FVec2F( 50, -50 ), D } };
    TransformBezier( threadPool, ULIS3_NONBLOCKING, perfIntent, host, ULIS3_NOCB, blockSRC, blockDST, blockSRC->Rect(), ctrlpoints, 0.5f, 1, INTERP_NN );

    QApplication    app( argc, argv );
    QWidget*        widget  = new QWidget();
    QImage*         image   = new QImage( blockDST->DataPtr()
                                        , blockDST->Width()
                                        , blockDST->Height()
                                        , blockDST->BytesPerScanLine()
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

    delete  blockDST;
    delete  blockSRC;

    XDeleteThreadPool( threadPool );
    return  exit_code;
}

