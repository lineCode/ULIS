// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS3
*__________________
*
* @file         Vec.h
* @author       Clement Berthaud
* @brief        This file provides a central point to include vector types.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"
#include "Maths/Geometry/Vec2.h"
#include "Maths/Geometry/Vec3.h"
#include "Maths/Geometry/Vec4.h"

ULIS3_NAMESPACE_BEGIN
template< typename T >
TVec2< T >::TVec2( const TVec3< T >& iVec )
    : x( iVec.x )
    : y( iVec.y )
{}

template< typename T >
TVec2< T >::TVec2( const TVec4< T >& iVec )
    : x( iVec.x )
    , y( iVec.y )
{}

template< typename T >
TVec3< T >::TVec3( const TVec2< T >& iVec, T iZ )
    : x( iVec.x )
    , y( iVec.y )
    , z( 0 )
{}

template< typename T >
TVec3< T >::TVec3( const TVec4< T >& iVec )
    : x( iVec.x )
    , y( iVec.y )
    , z( iVec.z )
{}


template< typename T >
TVec4< T >::TVec4( const TVec2< T >& iVec, T iZ, T iW )
    : x( iVec.x )
    , y( iVec.y )
    , z( 0 )
    , w( 0 )
{}

template< typename T >
TVec4< T >::TVec4( const TVec3< T >& iVec, T iW )
    : x( iVec.x )
    , y( iVec.y )
    , z( iVec.z )
    , w( 0 )
{}

ULIS3_NAMESPACE_END

