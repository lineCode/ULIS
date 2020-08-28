// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS
*__________________
*
* @file         SpecializationCondition.h
* @author       Clement Berthaud
* @brief        This file provides declaration for the dispatch specialization utilities.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"

ULIS_NAMESPACE_BEGIN
typedef bool (*fpCond)( eFormat );
bool DispatchTestIsUnorderedRGBA8( eFormat iFormat );
bool DispatchTestIsUnorderedRGBAF( eFormat iFormat );

ULIS_NAMESPACE_END

