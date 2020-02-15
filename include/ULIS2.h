// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         ULIS2.h
* @author       Clement Berthaud
* @brief        This file provides a unique way to include all the necessary library files.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
// Data
#include "Data/Block.h"
#include "Data/Pixel.h"
// Color
#include "Color/ColorProfile.h"
#include "Color/ProfileRegistry.h"
// Base
#include "Base/CPU.h"
#include "Base/FilePathRegistry.h"
#include "Base/Perf.h"
#include "Base/StringUtils.h"
// Maths
#include "Maths/Geometry.h"
#include "Maths/Maths.h"
#include "Maths/Camera3D.h"
// Thread
#include "Thread/ThreadPool.h"
#include "Thread/ParallelFor.h"
// Interface
#include "Conv/Conv.h"
#include "Misc/Swap.h"
#include "Blend/Blend.h"
#include "Fill/Fill.h"
#include "Clear/Clear.h"
#include "Copy/Copy.h"
#include "Text/FontRegistry.h"
#include "Text/FontEngine.h"
#include "Text/Font.h"
#include "Text/Text.h"
#include "Disk/IO.h"
#include "Raster/Draw.h"

using FVec2 = glm::vec2;
using FMat2 = glm::mat2;
using FMat3 = glm::mat3;

