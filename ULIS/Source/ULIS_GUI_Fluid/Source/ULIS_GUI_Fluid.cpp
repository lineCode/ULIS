/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS_GUI_Fluid.cpp
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#include "ULIS_GUI_Fluid.h"


int main( int argc, char *argv[] )
{
    QApplication app( argc, argv );
    SWindow* w = new SWindow();
    w->show();

    int exit_code = app.exec();

    delete w;

    return  exit_code;
}

