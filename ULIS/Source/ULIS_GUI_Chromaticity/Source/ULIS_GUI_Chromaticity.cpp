/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS_GUI_Chromaticity.cpp
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#include <QApplication>
#include <QWidget>
#include <QImage>
#include <QPixmap>
#include <QLabel>
#include <ULIS_CORE>

int main( int argc, char *argv[] )
{
    QApplication app( argc, argv );

    ::ULIS::IBlock* block = ::ULIS::FMakeContext::MakeBlock( 1024, 1024, ::ULIS::FBlockRGBA8::TypeId() );
    ::ULIS::FClearFillContext::Fill( block, ::ULIS::CColor( 255, 255, 255 ) );

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
}

