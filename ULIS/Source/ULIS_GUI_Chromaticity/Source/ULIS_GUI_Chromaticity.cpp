/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS_GUI_Chromaticity.cpp
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#include <QApplication>
#include <QWidget>
#include <QImage>
#include <QPixmap>
#include <QLabel>
#include <ULIS_CORE>
#include <ULIS/Color/ULIS.Color.ColorMatching.h>

int main( int argc, char *argv[] )
{
    QApplication app( argc, argv );

    ::ULIS::IBlock* block = ::ULIS::FMakeContext::MakeBlock( 512, 512, ::ULIS::FBlockRGBA8::TypeId() );
    ::ULIS::FClearFillContext::Fill( block, ::ULIS::CColor( 20, 20, 20 ) );

    cmsHPROFILE hInProfile;
    cmsHPROFILE hOutProfile;
    cmsHTRANSFORM hTransform;
    hInProfile  = cmsCreateXYZProfile();
    hOutProfile = cmsCreate_sRGBProfile();

    hTransform = cmsCreateTransform( hInProfile
                                   , TYPE_XYZ_DBL
                                   , hOutProfile
                                   , TYPE_RGBA_8
                                   , INTENT_PERCEPTUAL, 0 );
    cmsCloseProfile( hInProfile  );
    cmsCloseProfile( hOutProfile );

    float deadzone_vertical = 0.15f;
    float deadzone_horizontal = 0.25f;
    int padding_left = ( deadzone_horizontal * block->Width() ) / 2;
    int padding_top = -( deadzone_vertical * block->Height() ) / 2;
    for( int i = 0; i < 471; ++i ) // 1nanometer step 830 - 360 = 470
    {
        cmsCIEXYZ XYZ;
        XYZ.X = ::ULIS::CMF_XYZ_CIE_2_1931_1nm[i].x;
        XYZ.Y = ::ULIS::CMF_XYZ_CIE_2_1931_1nm[i].y;
        XYZ.Z = ::ULIS::CMF_XYZ_CIE_2_1931_1nm[i].z;
        cmsCIExyY xyY;
        cmsXYZ2xyY( &xyY, &XYZ );
        int x = xyY.x * block->Width()              + padding_left;
        int y = (1.0 - xyY.y) * block->Height()     + padding_top;
        cmsDoTransform( hTransform, &XYZ, block->PixelPtr( x, y ), 1 );
    }

    /*
    for( int y = 0; y < block->Height(); ++y )
    {
        for( int x = 0; x < block->Width(); ++x )
        {
            cmsCIExyY xyY;
            xyY.x = x / (double)block->Width();
            xyY.y = 1.0 - ( y / (double)block->Height() );
            xyY.Y = sqrt( pow( xyY.x - ::ULIS::whitepoint_D65.x, 2 ) + pow( xyY.y - ::ULIS::whitepoint_D65.y, 2 ) );
            cmsCIEXYZ XYZ;
            cmsDoTransform( hTransform, &XYZ, block->PixelPtr( x, y ), 1 );
        }
    }
    */

    cmsDeleteTransform( hTransform );

    int wp_x = ::ULIS::whitepoint_D65.x * block->Width() + padding_left;
    int wp_y = (1-::ULIS::whitepoint_D65.y)*block->Height() + padding_top;
    cmsCIExyY sRGB_chroma_r = { 0.6400, 0.3300, 0.2126 };
    cmsCIExyY sRGB_chroma_g = { 0.3000, 0.6000, 0.7152 };
    cmsCIExyY sRGB_chroma_b = { 0.1500, 0.0600, 0.0722 };
    int chr_r_x = sRGB_chroma_r.x * block->Width() + padding_left;
    int chr_g_x = sRGB_chroma_g.x * block->Width() + padding_left;
    int chr_b_x = sRGB_chroma_b.x * block->Width() + padding_left;
    int chr_r_y = (1-sRGB_chroma_r.y )*block->Height() + padding_top;
    int chr_g_y = (1-sRGB_chroma_g.y )*block->Height() + padding_top;
    int chr_b_y = (1-sRGB_chroma_b.y )*block->Height() + padding_top;

    block->SetPixelColor( wp_x, wp_y, ::ULIS::white );
    block->SetPixelColor( chr_r_x, chr_r_y, ::ULIS::red );
    block->SetPixelColor( chr_g_x, chr_g_y, ::ULIS::green );
    block->SetPixelColor( chr_b_x, chr_b_y, ::ULIS::blue );

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

