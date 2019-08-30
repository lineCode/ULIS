/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS_GUI_Conv.cpp
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#include <QApplication>
#include <QWidget>
#include <QImage>
#include <QPixmap>
#include <QLabel>
#include <ULIS_CORE>
#include "ULIS/Conv/ULIS.Conv.ConversionContext.h"

int main( int argc, char *argv[] )
{
    // Qt App
    QApplication app( argc, argv );

    // ULIS Image Conv
    ::ULIS::IBlock* block8 = ::ULIS::FMakeContext::MakeBlock( 1024, 1024, ::ULIS::FBlockRGBA8::TypeId(), "AdobeRGB_compat" );
    ::ULIS::IBlock* blockH = ::ULIS::FMakeContext::MakeBlock( 1024, 1024, ::ULIS::FBlockfloatHSLhasAlphaHSLAnormalized::TypeId(), ::ULIS::DefaultProfiles::AdobeRGB_compat );
    ::ULIS::IBlock* blockf = ::ULIS::FMakeContext::MakeBlock( 1024, 1024, ::ULIS::FBlockBGRAfn::TypeId() );
    ::ULIS::IBlock* blockg = ::ULIS::FMakeContext::MakeBlock( 1024, 1024, ::ULIS::FBlockGf::TypeId() );

    //::ULIS::FClearFillContext::Fill( block8, ::ULIS::CColor( 0, 128, 255 ) );
    //::ULIS::FClearFillContext::Clear( blockf );
    //::ULIS::FClearFillContext::Fill( blockg, ::ULIS::CColor::FromGreyF( 0.5f ) );

    ::ULIS::FValueRGBA8 val = ::ULIS::PixelValueAutoCastChecked( block8, 0, 0 );
    int R = val.R();
    int G = val.G();
    int B = val.B();
    int A = val.GetAlpha();
    std::string profilename = val.ColorProfile()->Name();
    auto dummy = 0;
    //::ULIS::TConversionContext::ConvertTypeAndLayoutInto< ::ULIS::FBlockRGBA8::TypeId(), ::ULIS::FBlockRGBA8::TypeId() >( ::ULIS::PixelValueAutoCastChecked( block8, 0, 0 ), val );

    ::ULIS::FValueRGBA8 v1;
    v1.SetR( 255 );
    v1.SetG( 0 );
    v1.SetB( 0 );
    v1.SetAlpha( 255 );
    ::ULIS::FValueLabAfn v2;
    ::ULIS::TConversionContext::Convert( v1, v2 );
    float lL = v2.L();
    float la = v2.a();
    float lb = v2.b();
    float lA = v2.GetAlpha();
    auto dummyx = 0;

    /*
    // Qt Window
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
    */

    return  0;
}

