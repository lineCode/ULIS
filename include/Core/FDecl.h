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

ULIS_NAMESPACE_BEGIN
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

template< typename T > struct   TVector2;
typedef TVector2< int >            FVec2I;
typedef TVector2< float >          FVec2F;
typedef TVector2< double >         FVec2D;
typedef TVector2< uint8 >          FVec2UI8;
typedef TVector2< uint16 >         FVec2UI16;
typedef TVector2< uint32 >         FVec2UI32;
typedef TVector2< uint64 >         FVec2UI64;
typedef TVector2< int32 >          FVec2I32;
typedef TVector2< int64 >          FVec2I64;
template< typename T > struct   TVector3;
typedef TVector3< int >            FVec3I;
typedef TVector3< float >          FVec3F;
typedef TVector3< double >         FVec3D;
typedef TVector3< uint8 >          FVec3UI8;
typedef TVector3< uint16 >         FVec3UI16;
typedef TVector3< uint32 >         FVec3UI32;
typedef TVector3< uint64 >         FVec3UI64;
typedef TVector3< int32 >          FVec3I32;
typedef TVector3< int64 >          FVec3I64;
template< typename T > struct   TVector4;
typedef TVector4< int >            FVec4I;
typedef TVector4< float >          FVec4F;
typedef TVector4< double >         FVec4D;
typedef TVector4< uint8 >          FVec4UI8;
typedef TVector4< uint16 >         FVec4UI16;
typedef TVector4< uint32 >         FVec4UI32;
typedef TVector4< uint64 >         FVec4UI64;
typedef TVector4< int32 >          FVec4I32;
typedef TVector4< int64 >          FVec4I64;
template< typename T > struct   TVector8;
typedef TVector8< int >            FVec8I;
typedef TVector8< float >          FVec8F;
typedef TVector8< double >         FVec8D;
typedef TVector8< uint8 >          FVec8UI8;
typedef TVector8< uint16 >         FVec8UI16;
typedef TVector8< uint32 >         FVec8UI32;
typedef TVector8< uint64 >         FVec8UI68;
typedef TVector8< int32 >          FVec8I32;
typedef TVector8< int64 >          FVec8I68;
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
ULIS_NAMESPACE_END

