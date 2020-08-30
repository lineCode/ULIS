// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS
*__________________
*
* @file         CommmandArgs.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the ICommmandArgs structure.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"

ULIS_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
// FBlendArgs
class ICommandArgs {
public:
    virtual ~ICommandArgs() = 0;
    ICommandArgs();
};

ULIS_NAMESPACE_END

