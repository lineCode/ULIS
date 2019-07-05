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



int main( int argc, char *argv[] )
{
    QApplication app( argc, argv );

    ::ULIS::IBlock* block = new ::ULIS::FBlockBGRA8( 500, 500 );
    ::ULIS::FBlockBGRA8* ptr = (::ULIS::FBlockBGRA8*)block;

    for( int y = 0; y < ptr->Height(); ++y )
    {
        for( int x = 0; x < ptr->Width(); ++x )
        {
            block->SetPixelColor( x, y, ::ULIS::CColor::FromHSV( x, y, y, 255 ) );
        }
    }


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

