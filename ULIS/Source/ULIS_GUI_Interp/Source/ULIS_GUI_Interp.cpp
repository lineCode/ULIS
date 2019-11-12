/**
*
*   ULIS
*__________________
*
* @file     ULIS_GUI_Interp.cpp
* @author   Clement Berthaud
* @brief    Main file for project ULIS_GUI_Interp.
*/

#include <QApplication>
#include <QWidget>
#include <ULIS_CORE>
#include "Application/Window/Application.Window.MainWindow.h"

int main( int argc, char *argv[] )
{
    QApplication app( argc, argv );

    QWidget* w  = new ::nApplication::nWindow::SMainWindow();
    w->resize( 800, 600 );
    w->show();

    int exit_code = app.exec();

    delete w;
    return  exit_code;
}

