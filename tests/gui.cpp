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

int
main( int argc, char *argv[] ) {
    using namespace ::ul2;
    FThreadPool  threadPool;
    FPerf perfIntent( Perf_AVX2   | Perf_TSPEC );

    FPerfInfo perfInfo = {};
    perfInfo.pool       = &threadPool;
    perfInfo.intent     = perfIntent;
    perfInfo.blocking   = ULIS2_NONBLOCKING;
    perfInfo.callCB     = ULIS2_NOCB;

    FXLoadFromClipboardInfo loadFromClipboardInfo = {};
    loadFromClipboardInfo.desiredFormat = ULIS2_FORMAT_RGBA8;
    loadFromClipboardInfo.perfInfo      = perfInfo;
    FBlock* blockA = XLoadFromClipboard( loadFromClipboardInfo );
    Fence( threadPool );

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
    return  exit_code;
}

