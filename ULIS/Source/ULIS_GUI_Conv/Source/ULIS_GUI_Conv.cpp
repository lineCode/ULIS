/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS_GUI_Conv.cpp
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#include <QApplication>
#include <QWidget>
#include <QImage>
#include <QPixmap>
#include <QLabel>
#include "ULIS/Conv/ULIS.Conv.ConversionContext.h"
#include <ULIS_CORE>


int main( int argc, char *argv[] )
{
    // Qt App
    QApplication app( argc, argv );

    // ULIS Image Conv
    ::ULIS::IBlock* block8 = ::ULIS::FMakeContext::MakeBlock( 1024, 1024, ::ULIS::FBlockRGBA8::TypeId() );
    ::ULIS::IBlock* blockf = ::ULIS::FMakeContext::MakeBlock( 1024, 1024, ::ULIS::FBlockRGBAf::TypeId() );
    ::ULIS::FClearFillContext::Fill( block8, ::ULIS::CColor( 127, 127, 127 ) );
    ::ULIS::FClearFillContext::Clear( blockf );

    ::ULIS::FConvContext::ConvTypeInto( block8, blockf );

    /*
    // Qt Window
    QImage* image   = new QImage( block->DataPtr(), block->Width(), block->Height(), block->BytesPerScanLine(), QImage::Format::Format_RGBA8888 );
    QPixmap pixmap  = QPixmap::fromImage( *image );
    QWidget* w      = new QWidget();
    QLabel* label   = new QLabel( w );
    label->setPixmap( pixmap );
    w->resize( pixmap.size() );
    w->show();

    int exit_code = app.exec();

    delete label;
    delete image;
    delete w;
    delete block;

    return  exit_code;
    */

    return  0;
}

