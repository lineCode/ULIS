// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Reg.h
* @author       Clement Berthaud
* @brief        This file provides the registry classes for the Font Registry tools.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Base/Core.h"
#include <map>
#include <vector>
#include <ft2build.h>
#include FT_FREETYPE_H

ULIS2_NAMESPACE_BEGIN
class FFontRegistry;
class FFontFamilyKey;
class FFontStyleKey;

/////////////////////////////////////////////////////
/// @class      FFontStyleKey
/// @brief      The FFontStyleKey class provides a mean of storing and manipulating font families file paths.
class ULIS2_API FFontStyleKey
{
public:
    // Construction / Destruction
    ~FFontStyleKey();
    FFontStyleKey( const std::string& iFamilyName, const std::string& iStyleName, const std::string& iFontPath );

private:
    // Private Data Members
    std::string mFamilyName;
    std::string mStyleName;
    std::string mFontPath;
};

/////////////////////////////////////////////////////
/// @class      FFontFamilyKey
/// @brief      The FFontFamilyKey class provides a mean of storing and manipulating font families file paths.
class ULIS2_API FFontFamilyKey
{
public:
    // Construction / Destruction
    ~FFontFamilyKey();
    FFontFamilyKey( const std::string& iFamilyName );

public:
    // Public API
    void AddFontStyleKey( const std::string& iStyle, const FFontStyleKey& iFontStyleKey );

private:
    // Private Data Members
    std::string mFamilyName;
    std::map< std::string, FFontStyleKey > mStyles;
};

/////////////////////////////////////////////////////
/// @class      FFontRegistry
/// @brief      The FFontRegistry class provides a mean of storing and manipulating font families file paths.
class ULIS2_API FFontRegistry
{
public:
    // Construction / Destruction
    ~FFontRegistry();
    FFontRegistry();

public:
    // Public API
    void AddLookupPath( const std::string& iPath );
    void AddLookupPaths( const std::vector< std::string >& iPaths );
    void Parse( FT_Library iFT_Library );

private:
    // Private Data Members
    std::vector< std::string > mLookupPaths;
    std::map< std::string, FFontFamilyKey > mFamilies;
};

ULIS2_NAMESPACE_END

