// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS
*__________________
*
* @file         SinglyLinkedList.h
* @author       Clement Berthaud
* @brief        This file provides the definition for the TSinglyLinkedList class.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"
#include "Memory/Memory.h"
#include "Math/Math.h"
#include <utility>

ULIS_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
/// @class      TSinglyLinkedList
/// @brief      The TSinglyLinkedList class provides a simple dynamic singly
///             linked list class for ULIS interfaces.
/// @details    The need of a custom TSinglyLinkedList class rose from the fact
///             that std:: classes cannot be exported easily accross dll
///             boundaries when ULIS is compiled as a shared library.
template< typename T >
class TSinglyLinkedList
{
public:
    /*! Destroy the Array and cleanup memory. */
    ~TSinglyLinkedList< T >()
    {
    }

    /*! Default constructor ( empty ). */
    TSinglyLinkedList< T >()
    {}

private:
};

ULIS_NAMESPACE_END

