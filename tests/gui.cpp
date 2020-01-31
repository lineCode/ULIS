// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         gui.cpp
* @author       Clement Berthaud
* @brief        Gui application for ULIS2.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include <ULIS2>
#include <QApplication>
#include <QWidget>
#include <QImage>
#include <QPixmap>
#include <QLabel>
#include <vectorclass.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <Windows.h>
using namespace ::ul2;

int
main( int argc, char *argv[] )
{
// Related to the earlier posts, this seems to be a reliable way:
// 
// 1) Read the registered Windows font list from HKEY_LOCAL_MACHINE\Software\Microsoft\Windows NT\CurrentVersion\Fonts\ You will obtain file names and alternate file paths here. The Font names are not useful as they can change with user's locale.
// 
// 2) Load the TrueType files (.ttf, .ttc, .otf): Use FreeType https://www.freetype.org/). Just initialize the freetype library and load face with FT_New_Face(library, path, 0, &face).
// 
// 3) Obtain the font Family name using FreeType. Use FT_Get_Sfnt_Name_Count() and FT_Get_Sfnt_Name() to obtain the string table. You will need to check if the encoding is Ansi, UTF16 or other, as some strings will be in multiple different languages and encodings.
// 
// 4) Obtain the OS2 TrueType properties. Use (TT_OS2 *) FT_Get_Sfnt_Table (face, ft_sfnt_os2) to get the OS2 structure. Interpret the structure using docs like https://www.microsoft.com/typography/otspec/os2.htm#fc
// 
// 5) Now you have font file path, family name, style properties and other information. Build a list of these and function to search for a file based on font family and style.

    // Windows
    // On Windows newer than 3.1, the font directory is located in %WINDIR%\fonts.
    //
    // Mac OS X
    // /System/Library/Fonts - Fonts necessary for the system. Do not touch these.
    // /Library/Fonts - Additional fonts that can be used by all users. This is generally where fonts go if they are to be used by other applications.
    // ~/Library/Fonts - Fonts specific to each user.
    // /Network/Library/Fonts - Fonts shared for users on a network.
    // 
    // Linux
    // /usr/share/fonts, /usr/local/share/fonts, and user-specific ~/.fonts
    // /etc/fonts/fonts.conf or /etc/fonts/local.conf.
    std::string font_path;
    #ifdef ULIS2_WIN
        CHAR windir[MAX_PATH];
        GetWindowsDirectoryA( windir, MAX_PATH );
        font_path = std::string( windir );
    #elif defined ULIS2_MACOS
        font_path = "";
    #elif defined ULIS2_LINUX
        font_path = "";
    #endif
    replace( font_path, "\\", "/" );

    FT_Library  library;
    FT_Error error = FT_Init_FreeType( &library );
    if( error ) std::cout << "an error occurred during freetype library initialization ..." << std::endl;

    FFontRegistry refgf;
    refgf.Parse( library );

    FFilePathRegistry reg;
    reg.AddLookupPath( "C:/Windows/Fonts/" );
    reg.AddFilter( ".ttf" );
    reg.AddFilter( ".ttc" );
    reg.AddFilter( ".otf" );
    reg.Parse();
    for( auto it : reg.GetMap() )
    {
        std::cout << it.first << "  " << it.second << std::endl;
        FT_Face face;
        FT_New_Face(library, it.second.c_str(), 0, &face );
        std::cout << "num_faces             " << face->num_faces           << std::endl;
        std::cout << "face_index            " << face->face_index          << std::endl;
        std::cout << "style_flags           " << face->style_flags         << std::endl;
        std::cout << "family_name           " << face->family_name         << std::endl;
        std::cout << "style_name            " << face->style_name          << std::endl;
        std::cout << std::endl;
    }



    //8bit to float
    /*
    {
        Vec16uc src( 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 );
        Vec16us ex16 = extend( src );
        Vec16ui ex32 = extend( ex16 );
        Vec16f  dst = to_float( ex32 );
        auto dummy = 0;
    }
    */

    //8bit mul
    /*
    {
        Vec16uc a( 0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xA, 0xB, 0xC, 0xD, 0xE, 0xF );
        Vec16uc b( 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF );
        Vec16us mul = extend( a ) * extend( b );
        Vec16uc res = compress( ( mul + 1 + ( mul >> 8 ) ) >> 8 );
        auto dummy = 0;
    }
    */

    int width   = 512;
    int height  = 512;
    FBlock blockA( width, height, ULIS2_FORMAT_RGBA8 );
    FBlock blockB( width, height, ULIS2_FORMAT_RGBA8 );

    FThreadPool pool;
    FPerf perf_low( Perf_Lowest );
    FPerf perf_best( Perf_Best_CPU );
    FCPU cpu_info;
    FPixel white( ULIS2_FORMAT_RGB8, { 255, 255, 255 } );
    FPixel black( ULIS2_FORMAT_RGB8, { 0, 0, 0 } );
    Fill( &pool,  ULIS2_BLOCKING, perf_best, cpu_info, &blockA, white, ULIS2_NOCB );
    Fill( &pool,  ULIS2_BLOCKING, perf_best, cpu_info, &blockB, black, ULIS2_NOCB );

    for( int x = 0; x < 512; ++x )
    {
        float t = x / 512.f;
        for( int y = 0; y < 512; ++y )
        {
            blockB.PixelProxy( x, y ).SetAlpha( t );
        }
    }

    BlendRect( &pool, ULIS2_BLOCKING, perf_low, cpu_info, ULIS2_SUBPIXEL, &blockB, &blockA, FRect( 0, 0, 256, 256 ), glm::vec2( 32.5f, 32.5f ), BM_BAYERDITHER8x8, AM_NORMAL, 1.f, ULIS2_CALLCB );

    // Qt Window
    QApplication app( argc, argv );
    QWidget* widget = new  QWidget();
    QImage*  image  = new  QImage( blockA.DataPtr(), blockA.Width(), blockA.Height(), blockA.BytesPerScanLine(), QImage::Format::Format_RGBA8888 );
    QPixmap  pixmap = QPixmap::fromImage( *image );
    QLabel*  label  = new  QLabel( widget );
    label->setPixmap( pixmap );
    widget->resize( pixmap.size() );
    widget->show();

    int exit_code = app.exec();

    delete  label;
    delete  image;
    delete  widget;

    return  exit_code;
}

