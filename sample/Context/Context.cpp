// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS
*__________________
*
* @file         Blend.cpp
* @author       Clement Berthaud
* @brief        Blend application for ULIS3.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include <ULIS>

#include <QApplication>
#include <QWidget>
#include <QImage>
#include <QPixmap>
#include <QLabel>

#include <chrono>

int
main( int argc, char *argv[] ) {
    ::ULIS::FThreadPool pool;
    ::ULIS::FCommandQueue queue( pool );
    ::ULIS::eFormat format = ::ULIS::Format_RGBA8;
    ::ULIS::FDevice host;
    ::ULIS::FRasterContext ctx( queue, host, format );

    ::ULIS::FString pathBase = "C:/Users/PRAXINOS/Documents/work/base_160.png";
    ::ULIS::FString pathOver = "C:/Users/PRAXINOS/Documents/work/over_160.png";

    return  0;
}

