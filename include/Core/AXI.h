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
FString VersionString();
FString VersionMajorString();
FString VersionMinorString();
FString VersionPatchString();
uint64 VersionMajor();
uint64 VersionMinor();
uint64 VersionPatch();
FString CompilationTimeStamp();
ULIS_NAMESPACE_END

