// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS
*__________________
*
* @file         ForwardList.h
* @author       Clement Berthaud
* @brief        This file provides the definition for the TForwardList class.
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
/// @class      TForwardList
/// @brief      The TForwardList class provides a simple dynamic singly
///             linked list class for ULIS interfaces.
/// @details    The need of a custom TForwardList class rose from the fact
///             that std:: classes cannot be exported easily accross dll
///             boundaries when ULIS is compiled as a shared library.
template< typename T >
class TForwardList
{
private:
    /// @class      TForwardListNode
    /// @brief      The TForwardListNode class provides a simple node class
    ///             fot TForwardList
    /// @details    TForwardListNode is really a simple way to store nodes
    ///             for singly linked lists, it holds the element and a pointer
    ///             to the next node.
    template< typename U >
    struct TForwardListNode
    {
        TForwardListNode( TForwardListNode< U >* iNext, const T& iValue )
            : mNext( iNext )
            , mValue( iValue )
        {}

        TForwardListNode( TForwardListNode< U >* iNext, T&& iValue )
            : mNext( iNext )
            , mValue( std::forward< U >( iValue )
        {}

        template< class... Args >
        TForwardListNode( TForwardListNode< U >* iNext, Args&& ... args )
            : mNext( iNext )
            , mValue( std::forward< Args >(args)... )
        {}

        TForwardListNode< U >* mNext;
        U mValue;
    };

public:
    /*! Destroy the Array and cleanup memory. */
    ~TForwardList< T >()
    {
    }

    /*! Default constructor ( empty ). */
    TForwardList< T >()
        : mHead( nullptr )
    {}

private:
    TForwardListNode< T >* mFront; ///< The head of the list, start iterating from there.
    TForwardListNode< T >* mBack; ///< The back of the list. Although traversal is one way, this is here to allow easy push back on the list.
};

ULIS_NAMESPACE_END

