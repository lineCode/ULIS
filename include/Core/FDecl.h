// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS3
*__________________
*
* @file         FDecl.h
* @author       Clement Berthaud
* @brief        This file provides core forward declarations for the ULIS3 library.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Platform.h"

ULIS3_NAMESPACE_BEGIN
class   FBlock;
class   ISample;
class   FColor;
class   FPixel;
class   FProfileRegistry;
class   FColorSpace;
class   FThreadPool;
class   FFontRegistry;
class   FFontEngine;
class   FFont;
class   FTransform2D;
class   ITiledBlock;
class   FKernel;
class   FStructuringElement;
struct  FPerfInfo;
struct  FHostDeviceInfo;
struct  FFormat;
struct  FTileElement;
class   ITiledBlock;
class   ITilePool;

template< typename T > struct   TVec2;
typedef TVec2< int >            FVec2I;
typedef TVec2< float >          FVec2F;
typedef TVec2< double >         FVec2D;
typedef TVec2< uint8 >          FVec2UI8;
typedef TVec2< uint16 >         FVec2UI16;
typedef TVec2< uint32 >         FVec2UI32;
typedef TVec2< uint64 >         FVec2UI64;
typedef TVec2< int32 >          FVec2I32;
typedef TVec2< int64 >          FVec2I64;
template< typename T > struct   TVec3;
typedef TVec3< int >            FVec3I;
typedef TVec3< float >          FVec3F;
typedef TVec3< double >         FVec3D;
typedef TVec3< uint8 >          FVec3UI8;
typedef TVec3< uint16 >         FVec3UI16;
typedef TVec3< uint32 >         FVec3UI32;
typedef TVec3< uint64 >         FVec3UI64;
typedef TVec3< int32 >          FVec3I32;
typedef TVec3< int64 >          FVec3I64;
template< typename T > struct   TVec4;
typedef TVec4< int >            FVec4I;
typedef TVec4< float >          FVec4F;
typedef TVec4< double >         FVec4D;
typedef TVec4< uint8 >          FVec4UI8;
typedef TVec4< uint16 >         FVec4UI16;
typedef TVec4< uint32 >         FVec4UI32;
typedef TVec4< uint64 >         FVec4UI64;
typedef TVec4< int32 >          FVec4I32;
typedef TVec4< int64 >          FVec4I64;
template< typename T > struct   TVec8;
typedef TVec8< int >            FVec8I;
typedef TVec8< float >          FVec8F;
typedef TVec8< double >         FVec8D;
typedef TVec8< uint8 >          FVec8UI8;
typedef TVec8< uint16 >         FVec8UI16;
typedef TVec8< uint32 >         FVec8UI32;
typedef TVec8< uint64 >         FVec8UI68;
typedef TVec8< int32 >          FVec8I32;
typedef TVec8< int64 >          FVec8I68;
template< typename T > struct   TRect;
typedef TRect< int >            FRectI;
typedef TRect< float >          FRectF;
typedef TRect< double >         FRectD;
typedef TRect< uint8 >          FRectUI8;
typedef TRect< uint16 >         FRectUI16;
typedef TRect< uint32 >         FRectUI32;
typedef TRect< uint64 >         FRectUI64;
typedef TRect< int32 >          FRectI32;
typedef TRect< int64 >          FRectI64;
ULIS3_NAMESPACE_END

