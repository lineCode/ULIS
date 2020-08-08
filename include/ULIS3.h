// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS3
*__________________
*
* @file         ULIS3.h
* @author       Clement Berthaud
* @brief        This file provides a unique way to include all the necessary library files.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
// Data
#include "Image/Block.h"
#include "Image/Color.h"
#include "Image/ColorSpace.h"
#include "Image/Format.h"
#include "Image/Pixel.h"
#include "Image/Sample.h"
// Base
#include "System/HostDeviceInfo.h"
#include "System/FilePathRegistry.h"
// Thread
#include "Thread/ThreadInterface.h"
// Maths
#include "Math/Geometry/Rectangle.h"
#include "Math/Geometry/Vector.h"
#include "Math/Geometry/Transformation2D.h"
#include "Math/Interpolation/Bezier.h"
#include "Math/Interpolation/CatmullRom.h"
#include "Math/Math.h"
// Interface
#include "Conv/Conv.h"
#include "Misc/Extract.h"
#include "Misc/Filter.h"
#include "Misc/GammaCompress.h"
#include "Misc/Premult.h"
#include "Misc/SummedAreaTable.h"
#include "Misc/Swap.h"
#include "Misc/Trim.h"
#include "Misc/Sanitize.h"
#include "Blend/Blend.h"
#include "Fill/Fill.h"
#include "Fill/FillPreserveAlpha.h"
#include "Clear/Clear.h"
#include "Copy/Copy.h"
#include "Text/FontRegistry.h"
#include "Text/TextEngine.h"
#include "Text/Font.h"
#include "Text/Text.h"
#include "IO/Disk.h"
#include "IO/Clipboard.h"
#include "Raster/Draw.h"
#include "Mix/Mix.h"
#include "Transform/Transform.h"
#include "Image/Sparse/TiledBlock.h"
#include "Image/Sparse/TilePool.h"

