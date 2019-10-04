/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS_GUI_Transform.cpp
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
    using namespace ::ULIS;
    QApplication app( argc, argv );
    IBlock* block = FMakeContext::MakeBlock( 1024, 1024, Format::Format_RGBA8 );

    FFXContext::Clouds( block );

    QImage*     image   = new QImage( block->DataPtr()
                                    , block->Width()
                                    , block->Height()
                                    , block->BytesPerScanLine()
                                    , QImage::Format::Format_RGBA8888 );
    QPixmap     pixmap  = QPixmap::fromImage( *image );
    QWidget*    w       = new QWidget();
    QLabel*     label   = new QLabel( w );
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

