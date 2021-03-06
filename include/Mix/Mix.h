// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS
*__________________
*
* @file         Mix.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the Mix entry point functions.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"

ULIS_NAMESPACE_BEGIN
ULIS_API FColor MixRGB( ufloat iT, const ISample& iA, const ISample& iB );
ULIS_API FColor MixLab( ufloat iT, const ISample& iA, const ISample& iB );
ULIS_NAMESPACE_END

