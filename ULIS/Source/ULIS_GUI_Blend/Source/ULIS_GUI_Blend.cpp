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
#include <QScrollArea>
#include <ULIS_Core>

int main( int argc, char *argv[] )
{
    QApplication app( argc, argv );

    QImage* qsource_under = new QImage( "Resources/ULIS_GUI_Blend/Under.png" );
    QImage::Format fmt = qsource_under->format();
    auto dummy = 0;

    QWidget* w = new QWidget( 0 );
    QScrollArea* scrollArea = new QScrollArea( w );
    scrollArea->setVerticalScrollBarPolicy( Qt::ScrollBarPolicy::ScrollBarAlwaysOn );
    scrollArea->setHorizontalScrollBarPolicy( Qt::ScrollBarPolicy::ScrollBarAlwaysOff );
    QWidget* canvas = new QWidget( 0 );
    scrollArea->setWidget( canvas );
    canvas->resize( 200, 150 );

    QPixmap pixmap  = QPixmap::fromImage( *qsource_under );
    QLabel* label   = new QLabel( canvas );
    label->setPixmap( pixmap );

    scrollArea->setFixedSize( 222, 100 );
    w->setFixedSize( 221, 100 );
    w->show();

    int exit_code = app.exec();

    delete label;
    delete qsource_under;
    delete w;
    return  exit_code;
}

