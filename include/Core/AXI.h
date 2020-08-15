// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS3
*__________________
*
* @file         AXI.h
* @author       Clement Berthaud
* @brief        This file provides declarations for API and ABI infos.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"
#include "String/String.h"

ULIS_NAMESPACE_BEGIN
ULIS_API FString VersionString();
ULIS_API FString VersionMajorString();
ULIS_API FString VersionMinorString();
ULIS_API FString VersionPatchString();
ULIS_API uint64 VersionMajor();
ULIS_API uint64 VersionMinor();
ULIS_API uint64 VersionPatch();
ULIS_API FString CompilationTimeStamp();
ULIS_NAMESPACE_END

