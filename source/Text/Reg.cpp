// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Reg.cpp
* @author       Clement Berthaud
* @brief        This file provides the registry classes for the Font Registry tools.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include "Text/Reg.h"
#include "Base/FilePathRegistry.h"
#include "Base/String.h"
#ifdef ULIS2_WIN
#include <Windows.h>
#endif

ULIS2_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
// FFontStyleKey
//--------------------------------------------------------------------------------------
//----------------------------------------------------------- Construction / Destruction
FFontStyleKey::~FFontStyleKey()
{
}


FFontStyleKey::FFontStyleKey( const std::string& iFamilyName, const std::string& iStyleName, const std::string& iFontPath )
    : mFamilyName( iFamilyName )
    , mStyleName( iStyleName )
    , mFontPath( iFontPath )
{
}

/////////////////////////////////////////////////////
// FFontFamilyKey
//--------------------------------------------------------------------------------------
//----------------------------------------------------------- Construction / Destruction
FFontFamilyKey::~FFontFamilyKey()
{
}


FFontFamilyKey::FFontFamilyKey( const std::string& iFamilyName )
    : mFamilyName( iFamilyName )
{
}


//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------- Public API
void FFontFamilyKey::AddFontStyleKey( const std::string& iStyle, const FFontStyleKey& iFontStyleKey )
{
    mStyles.try_emplace( iStyle, iFontStyleKey );
}

/////////////////////////////////////////////////////
// FFontRegistry
//--------------------------------------------------------------------------------------
//----------------------------------------------------------- Construction / Destruction
FFontRegistry::~FFontRegistry()
{
}


FFontRegistry::FFontRegistry()
{
    #ifdef ULIS2_WIN
        std::string sysfpath;
        CHAR windir[MAX_PATH];
        GetWindowsDirectoryA( windir, MAX_PATH );
        sysfpath = std::string( windir );
        replace( sysfpath, "\\", "/" );
        sysfpath += "/Fonts/";
        mLookupPaths.push_back( sysfpath );
    #elif defined ULIS2_MACOS
        mLookupPaths.push_back( "/System/Library/Fonts/" );
        mLookupPaths.push_back( "/Library/Fonts/" );
        mLookupPaths.push_back( "~/Library/Fonts/" );
        mLookupPaths.push_back( "/Network/Library/Fonts/" );
    #elif defined ULIS2_LINUX
        mLookupPaths.push_back( "/usr/share/fonts/" );
        mLookupPaths.push_back( "/usr/local/share/fonts/" );
        mLookupPaths.push_back( "~/.fonts/" );
        mLookupPaths.push_back( "/etc/fonts/fonts.conf/" );
        mLookupPaths.push_back( "/etc/fonts/local.conf./" );
    #endif
}


//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------- Public API
void
FFontRegistry::AddLookupPath( const std::string& iPath )
{
    mLookupPaths.push_back( iPath );
}


void
FFontRegistry::AddLookupPaths( const std::vector< std::string >& iPaths )
{
    for( auto it : iPaths )
        mLookupPaths.push_back( it );
}


void
FFontRegistry::Parse( FT_Library iFT_Library )
{
    mFamilies.clear();
    FFilePathRegistry reg;
    reg.AddLookupPaths( mLookupPaths );
    reg.AddFilter( ".ttf" );
    reg.AddFilter( ".ttc" );
    reg.AddFilter( ".otf" );
    reg.Parse();

    for( auto it : reg.GetMap() )
    {
        FT_Face face;
        FT_New_Face( iFT_Library, it.second.c_str(), 0, &face );
        std::string familyName( face->family_name );
        std::string style( face->style_name );
        mFamilies.try_emplace( familyName, FFontFamilyKey( familyName ) );
        mFamilies.at( familyName ).AddFontStyleKey( style, FFontStyleKey( familyName, style, it.second ) );
    }

    auto dummy = 0;
}

ULIS2_NAMESPACE_END

