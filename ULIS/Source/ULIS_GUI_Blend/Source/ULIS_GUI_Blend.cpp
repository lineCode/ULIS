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
#include "MainWindow.h"

#include <ULIS_CORE>

int main( int argc, char *argv[] )
{
    QApplication app( argc, argv );

    cMainWindow* w = new cMainWindow( 0 );
    w->resize( -1, 500 );
    w->show();

    int exit_code = app.exec();

    delete  w;
    return  exit_code;
}

