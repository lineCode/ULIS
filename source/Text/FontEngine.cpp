// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         FontEngine.cpp
* @author       Clement Berthaud
* @brief        This file provides the definition for the FFontEngine class.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include "Text/FontEngine.h"

ULIS2_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
// FFontEngine
//--------------------------------------------------------------------------------------
//----------------------------------------------------------- Construction / Destruction
FFontEngine::~FFontEngine()
{
    FT_Done_FreeType( mHandle );
}


FFontEngine::FFontEngine()
    : mHandle( nullptr )
{
    FT_Error error = FT_Init_FreeType( &mHandle );
    ULIS2_ERROR( !error, "Error initializing freetype2" );
}


//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------- Public API
FT_Library
FFontEngine::Handle() const
{
    return  mHandle;
}


ULIS2_NAMESPACE_END

