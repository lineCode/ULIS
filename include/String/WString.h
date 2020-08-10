// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS3
*__________________
*
* @file         WString.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the WString class.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"

ULIS_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
/// @class      FWString
/// @brief      The FSWtring class provides a simple dynamic string class
/// @details    The need of a custom FString class rose from the fact that std::
///             classes cannot be exported easily accross dll boundaries when
///             ULIS is compiled as a shared library.
class ULIS_API FWString
{
};

ULIS_NAMESPACE_END

