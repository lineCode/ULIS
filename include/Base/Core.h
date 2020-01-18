// Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Core.h
* @author       Clement Berthaud
* @brief        This file provides core definitions for the ULIS2 library.
* @copyright    Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
/////////////////////////////////////////////////////
// Includes
#include "Base/Platform.h"
#include "Base/CoreInternal.h"
#include "Base/Types.h"
#include "Base/FDecl.h"
#include "Base/Utils.h"
#include "Base/Format.h"
#include "Base/Decl.h"

/////////////////////////////////////////////////////
// glm FORCE extensions, before any glm related includes
#define GLM_FORCE_SSE42
#define GLM_FORCE_SSE41
#define GLM_FORCE_SSSE3
#define GLM_FORCE_SSE3
#define GLM_FORCE_SSE2
#define GLM_FORCE_SSE
#define GLM_FORCE_INTRINSICS

