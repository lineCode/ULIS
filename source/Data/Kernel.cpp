// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS3
*__________________
*
* @file         Kernel.cpp
* @author       Clement Berthaud
* @brief        This file provides the definition for the FKernel class.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include "Data/Kernel.h"

ULIS3_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
// FKernel
//--------------------------------------------------------------------------------------
//----------------------------------------------------------- Construction / Destruction
FKernel::~FKernel()
{
}


FKernel::FKernel( int iWidth, int iHeight )
    : tSuperClass( iWidth, iHeight, ULIS3_FORMAT_GF )
{
}

ULIS3_NAMESPACE_END

