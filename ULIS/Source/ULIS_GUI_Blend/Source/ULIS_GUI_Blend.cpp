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
#include <ULIS_Core>

int main( int argc, char *argv[] )
{
    QApplication app( argc, argv );

    QImage* qsource_under = new QImage( "Resources/ULIS_GUI_Blend/Under.png" );
    QImage::Format fmt = qsource_under->format();
    auto dummy = 0;

    QPixmap pixmap  = QPixmap::fromImage( *qsource_under );
    QWidget* w      = new QWidget();
    QLabel* label   = new QLabel( w );
    label->setPixmap( pixmap );

    w->setFixedSize( pixmap.size() );
    w->show();

    int exit_code = app.exec();

    delete label;
    delete qsource_under;
    delete w;
    return  exit_code;
}

