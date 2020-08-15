// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS3
*__________________
*
* @file         AXI.cpp
* @author       Clement Berthaud
* @brief        This file provides definitions for API and ABI infos.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"
#include "Core/AXI.h"

ULIS_NAMESPACE_BEGIN
FString
VersionString()
{
    return  VersionMajorString() + "." + VersionMinorString() + "." + VersionPatchString();
}

FString
VersionMajorString()
{
    return  FString( ULIS_VERSION_MAJOR_STR );
}

FString
VersionMinorString()
{
    return  FString( ULIS_VERSION_MINOR_STR );
}

FString
VersionPatchString()
{
    return  FString( ULIS_VERSION_PATCH_STR );
}

uint64
VersionMajor()
{
    return  ULIS_VERSION_MAJOR;
}

uint64
VersionMinor()
{
    return  ULIS_VERSION_MINOR;
}

uint64
VersionPatch()
{
    return  ULIS_VERSION_PATCH;
}

FString
CompilationTimeStamp()
{
    return  FString( ULIS_STRINGIFY( __DATE__ ) ) + " " + ULIS_STRINGIFY( __TIME__ );
}

ULIS_NAMESPACE_END

