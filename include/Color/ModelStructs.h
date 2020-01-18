// Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         ModelStructs.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for models structs.
* @copyright    Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Base/Core.h"

ULIS2_NAMESPACE_BEGIN
struct GreyF
{
    float Grey;
};

struct FRGBF
{
    float R;
    float G;
    float B;
};

struct HSVF
{
    float H;
    float S;
    float V;
};

struct HSLF
{
    float H;
    float S;
    float L;
};

struct CMYF
{
    float C;
    float M;
    float Y;
};

struct CMYKF
{
    float C;
    float M;
    float Y;
    float K;
};

struct YUVF
{
    float Y;
    float U;
    float V;
};

struct LabF
{
    float Y;
    float U;
    float V;
};

struct XYZF
{
    float Y;
    float U;
    float V;
};

struct Yxy
{
    float Y;
    float U;
    float V;
};

ULIS2_NAMESPACE_END

