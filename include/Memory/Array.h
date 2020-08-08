// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS3
*__________________
*
* @file         Vec2.h
* @author       Clement Berthaud
* @brief        This file provides the definition for the TVector2 class.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"
#include "Memory/Memory.h"

ULIS_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
/// @class      TArray
/// @brief      The TArray class provides a simple dynamic array or vector
///             class for ULIS interfaces.
/// @details    The need of a custom TArray class rose from the fact that std::
///             classes cannot be exported easily accross dll boundaries when
///             ULIS is compiled as a shared library.
template< typename T >
class TArray
{
public:
    /*! Destroy the Array and cleanup memory. */
    ~TArray< T >();

    /*! Default constructor with size 0, uninitialized. */
    TArray< T >();

    /*! Constructor with known size, both capacity and size will match the requested size. */
    TArray< T >( uint64 iSize );

private:
    T* mBulk;
    uint64 mCapacity;
    uint64 mSize;
};

ULIS_NAMESPACE_END

