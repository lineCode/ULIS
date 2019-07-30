/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS_GUI.cpp
* Thomas Schmitt
* Please refer to LICENSE.md
*/

#include <QApplication>
#include <QWidget>
#include <QImage>
#include <QPixmap>
#include <QLabel>
#include <ULIS_CORE>
#include "ULIS/Maths/ULIS.Maths.Geometry.h"



int main( int argc, char *argv[] )
{
    
    QApplication app( argc, argv );

    ::ULIS::IBlock* block = ::ULIS::FMakeContext::MakeBlock( 1024, 1024, ::ULIS::FBlockRGBA8::TypeId() );
    ::ULIS::FClearFillContext::Fill( block, ::ULIS::CColor( 255, 255, 255 ) );

    //Vertical
    ::ULIS::FPainterContext::DrawLine( block, ::ULIS::FPoint(500,50), ::ULIS::FPoint(500, 500), ::ULIS::CColor( 0, 0 ,0 ) );
    
    ::ULIS::FPainterContext::DrawLine( block, ::ULIS::FPoint(500,950), ::ULIS::FPoint(500, 500), ::ULIS::CColor( 0, 0 ,0 ) );
    
    //Horizontal
    ::ULIS::FPainterContext::DrawLine( block, ::ULIS::FPoint(50,500), ::ULIS::FPoint(500, 500), ::ULIS::CColor( 0, 0 ,0 ) );
    
    ::ULIS::FPainterContext::DrawLine( block, ::ULIS::FPoint(950,500), ::ULIS::FPoint(500, 500), ::ULIS::CColor( 0, 0 ,0 ) );
    
    
    //x slope
    ::ULIS::FPainterContext::DrawLine( block, ::ULIS::FPoint(100,300), ::ULIS::FPoint(500, 500), ::ULIS::CColor( 0, 0 ,255 ) );
    
    ::ULIS::FPainterContext::DrawLine( block, ::ULIS::FPoint(900,300), ::ULIS::FPoint(500, 500), ::ULIS::CColor( 0, 0 ,255 ) );

    ::ULIS::FPainterContext::DrawLine( block, ::ULIS::FPoint(100,700), ::ULIS::FPoint(500, 500), ::ULIS::CColor( 0, 0 ,255 ) );
    
    ::ULIS::FPainterContext::DrawLine( block, ::ULIS::FPoint(900,700), ::ULIS::FPoint(500, 500), ::ULIS::CColor( 0, 0 ,255 ) );
    
    //y slope
    ::ULIS::FPainterContext::DrawLine( block, ::ULIS::FPoint(300,100), ::ULIS::FPoint(500, 500), ::ULIS::CColor( 255, 0 ,0 ) );
    
    ::ULIS::FPainterContext::DrawLine( block, ::ULIS::FPoint(700,100), ::ULIS::FPoint(500, 500), ::ULIS::CColor( 255, 0 ,0 ) );

    ::ULIS::FPainterContext::DrawLine( block, ::ULIS::FPoint(300,900), ::ULIS::FPoint(500, 500), ::ULIS::CColor( 255, 0 ,0 ) );
    
    ::ULIS::FPainterContext::DrawLine( block, ::ULIS::FPoint(700,900), ::ULIS::FPoint(500, 500), ::ULIS::CColor( 255, 0 ,0 ) );
    
    for( int i = 0; i < 255; i++)
    {
        ::ULIS::FPainterContext::DrawCircle( block, ::ULIS::FPoint(500,500), i, ::ULIS::CColor( 0, i ,0 ) );
    }

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

