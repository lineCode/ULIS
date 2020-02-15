// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         IO.cpp
* @author       Clement Berthaud
* @brief        This file provides the definition for the disk IO entry point functions.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include "Disk/IO.h"
#include "Base/StringUtils.h"
#include "Data/Block.h"
#include "Base/Perf.h"
#include "base/CPU.h"
#include "Conv/Conv.h"

// STD
#include <fstream>

// STB
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

// LCMS
#include "lcms2.h"

// CPPFS
#include <cppfs/fs.h>
#include <cppfs/FileHandle.h>
#include <cppfs/FilePath.h>

ULIS2_NAMESPACE_BEGIN
FBlock*
XLoadFromFile( FThreadPool*       iPool
             , bool               iBlocking
             , const FPerf&       iPerf
             , const FCPU&        iCPU
             , const std::string& iPath
             , tFormat            iDesiredFormat )
{
    //cppfs::FilePath     path( iPath );
    //std::string         ext = path.extension();
    cppfs::FileHandle   fh = cppfs::fs::open( iPath );

    if( ( !fh.exists() ) || ( !fh.isFile() ) ) {
        ULIS2_ASSERT( false, "Error bad input file" );
    }

    std::ifstream file( iPath.c_str(), std::ios::binary | std::ios::ate );
    std::streamsize size = file.tellg();
    file.seekg( 0, std::ios::beg );
    std::vector<char> buffer(size);
    if( !file.read( buffer.data(), size ) ) {
        ULIS2_ASSERT( false, "Error bad input file" );
    }

    // profile handle cannot be found this way, we have to user proper apis for different formats to access the profile header block
    // cmsHPROFILE profileHandle = cmsOpenProfileFromMem( (const void*)buffer.data(), static_cast< cmsUInt32Number>( size ) );

    eType type = TYPE_UINT8;
    type = stbi_is_16_bit_from_memory( (const stbi_uc*)buffer.data(), static_cast< int >( size ) )  ? TYPE_UINT16 : type;
    type = stbi_is_hdr_from_memory( (const stbi_uc*)buffer.data(), static_cast< int >( size ) )     ? TYPE_UFLOAT : type;

    int desiredChannels = STBI_default;
    eColorModel desiredModel = static_cast< eColorModel >( ULIS2_R_MODEL( iDesiredFormat ) );
    bool needgrey   = desiredModel == CM_GREY;
    bool needrgb    = desiredModel == CM_RGB;
    bool needalpha  = ULIS2_R_ALPHA( iDesiredFormat );
    if( needgrey )  desiredChannels = needalpha ? 2 : 1;
    if( needrgb )   desiredChannels = needalpha ? 4 : 3;

    tByte* data = nullptr;
    int width, height, channels, depth;
    width = height = channels = depth = 1;
    bool floating;
    switch( type ) {
        case TYPE_UINT8:    data = (tByte*)stbi_load(       iPath.c_str(), &width, &height, &channels, desiredChannels ); depth = 1;    floating = false;   break;
        case TYPE_UINT16:   data = (tByte*)stbi_load_16(    iPath.c_str(), &width, &height, &channels, desiredChannels ); depth = 2;    floating = false;   break;
        case TYPE_UFLOAT:   data = (tByte*)stbi_loadf(      iPath.c_str(), &width, &height, &channels, desiredChannels ); depth = 4;    floating = true;    break;
    }

    if( !data )
        ULIS2_ASSERT( false, "Error bad input file" );

    if( desiredChannels != STBI_default )
        channels = desiredChannels;

    eColorModel model;
    bool hea;
    switch( channels ) {
        case 1: model = CM_GREY;    hea = false;    break;
        case 2: model = CM_GREY;    hea = true;     break;
        case 3: model = CM_RGB;     hea = false;    break;
        case 4: model = CM_RGB;     hea = true;     break;
    }
    channels = channels - hea;

    tFormat fmt = ULIS2_W_TYPE( type ) | ULIS2_W_CHANNELS( channels ) | ULIS2_W_MODEL( model ) | ULIS2_W_ALPHA( hea ) | ULIS2_W_DEPTH( depth ) | ULIS2_W_FLOATING( floating );
    FBlock* ret = new FBlock( data, width, height, fmt, nullptr, FOnInvalid(), FOnCleanup( &OnCleanup_FreeMemory ) );

    if( iDesiredFormat != 0 && iDesiredFormat != fmt ) {
        FBlock* conv = XConv( iPool, iBlocking, iPerf, iCPU, ret, iDesiredFormat );
        delete ret;
        ret = conv;
    }

    return  ret;
}

void SaveToFile( FThreadPool*       iPool
               , bool               iBlocking
               , const FPerf&       iPerf
               , const FCPU&        iCPU
               , const FBlock*      iSource
               , const std::string& iPath
               , eImageFormat       iImageFormat
               , int                iQuality )
{
    tFormat     format  = iSource->Format();
    eColorModel model   = iSource->Model();
    eType       type    = iSource->Type();

    bool layout_valid   = ULIS2_R_RS( format ) == 0;
    bool model_valid    = model == CM_GREY || model == CM_RGB;
    bool type_valid     = ( iImageFormat != IM_HDR && type == TYPE_UINT8 ) || ( iImageFormat == IM_HDR && type == TYPE_UFLOAT && model == CM_RGB );

    int w = iSource->Width();
    int h = iSource->Height();
    int c = iSource->SamplesPerPixel();
    const uint8* dat = iSource->DataPtr();
    FBlock* conv = nullptr;
    if( !( layout_valid && model_valid && type_valid ) ) {
        if( iImageFormat == IM_HDR ) {
            conv = XConv( iPool, iBlocking, iPerf, iCPU, iSource, ULIS2_FORMAT_RGBF );
        } else if( model == CM_GREY ) {
            conv = XConv( iPool, iBlocking, iPerf, iCPU, iSource, ULIS2_FORMAT_G8 | ULIS2_W_ALPHA( iSource->HasAlpha() ) );
        } else {
            conv = XConv( iPool, iBlocking, iPerf, iCPU, iSource, ULIS2_FORMAT_RGB8 | ULIS2_W_ALPHA( iSource->HasAlpha() ) );
        }

        dat = conv->DataPtr();
    }

    switch( iImageFormat ) {
        case IM_PNG: stbi_write_png( iPath.c_str(), w, h, c, dat, 0         );  break;
        case IM_BMP: stbi_write_bmp( iPath.c_str(), w, h, c, dat            );  break;
        case IM_TGA: stbi_write_tga( iPath.c_str(), w, h, c, dat            );  break;
        case IM_JPG: stbi_write_jpg( iPath.c_str(), w, h, c, dat, iQuality  );  break; // Quality: 0 - 100;
        case IM_HDR: stbi_write_hdr( iPath.c_str(), w, h, c, (float*)dat );     break;
    }

    if( conv )
        delete  conv;
}

ULIS2_NAMESPACE_END

