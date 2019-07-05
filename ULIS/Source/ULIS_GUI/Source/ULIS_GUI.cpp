/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS_Test.cpp
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#include <QApplication>
#include <QWidget>
#include <QImage>
#include <QPixmap>
#include <QLabel>
#include <ULIS_CORE>
#include <thread>

int main( int argc, char *argv[] )
{
    QApplication app( argc, argv );

    ::ULIS::FBlockBGRA8* block = new ::ULIS::FBlockBGRA8( 64, 64 );
    ::ULIS::FBlockBGRA8::tPixelValue val;

    val.SetColor( ::ULIS::CColor::FromRGB( 255, 0, 0 ) );
    for( int y = 0; y < block->Height(); ++y )
        for( int x = 0; x < block->Width(); ++x )
            block->SetPixelValue( x, y, val );

    QImage* image   = new QImage( block->DataPtr(), block->Width(), block->Height(), block->BytesPerScanLine(), QImage::Format::Format_ARGB32 );
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

