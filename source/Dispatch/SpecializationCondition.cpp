// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS
*__________________
*
* @file         SpecializationCondition.cpp
* @author       Clement Berthaud
* @brief        This file provides implementation for the dispatch specialization utilities.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Dispatch/SpecializationCondition.h"
#include "Image/Format.h"

ULIS_NAMESPACE_BEGIN
bool DispatchTestIsUnorderedRGBA8( const FFormat& iFormatInfo ) {
    return  ( iFormatInfo.FMT & ULIS_FORMAT_MASK_LAYOUT ) == eFormat::Format_RGBA8;
}

bool DispatchTestIsUnorderedRGBAF( const FFormat& iFormatInfo ) {
    return  ( iFormatInfo.FMT & ULIS_FORMAT_MASK_LAYOUT ) == eFormat::Format_RGBAF;
}

ULIS_NAMESPACE_END

