// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS
*__________________
*
* @file         Queue.h
* @author       Clement Berthaud
* @brief        This file provides the definition for the TQueue class.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"
#include "Memory/ForwardList.h"

ULIS_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
/// @class      TQueue
/// @brief      The TQueue class provides a simple dynamic queue based on a
///             forward queue.
/// @details    The need of a custom TQueue class rose from the fact
///             that std:: classes cannot be exported easily accross dll
///             boundaries when ULIS is compiled as a shared library.
template< typename T >
class TQueue
    : private TForwardList< T >
{
    typedef TForwardList< T >   tSuperClass;
    typedef TQueue< T >         tSelf;

public:
    /*! Destroy the queue and cleanup memory. */
    ~TQueue< T >()
    {
    }

    /*! Default constructor ( empty ). */
    TQueue< T >()
        : tSuperClass()
    {}

    /*! Copy constructor, explicitely removed. */
    TQueue< T >( const TQueue< T >& iOther ) = delete;

    /*! Copy Assignment Operator, explicitely removed. */
    TQueue< T >& operator=( const TQueue< T >& iOther ) = delete;

    /*! Move Assignment Operator, explicitely removed. */
    TQueue< T >& operator=( TQueue< T >&& iOther ) = delete;

    /*!
        Move constructor.
        The first object is left in a valid but empty state.
        The second object steals the state.
    */
    TQueue< T >( TQueue< T >&& iOther )
        : tSuperClass( std::forward< tSelf >( iOther ) )
    {}

    /*!
        Access component at front.
        The behaviour is undefined if the queue is empty.
    */
    T& Front() {
        return  Front();
    }

    /*!
        Access const component at front.
        The behaviour is undefined if the queue is empty.
    */
    T& Front() const {
        return  Front();
    }

    /*!
        Access component at back.
        The behaviour is undefined if the queue is empty.
    */
    T& Back() {
        return  Back();
    }

    /*!
        Access const component at back.
        The behaviour is undefined if the queue is empty.
    */
    const T& Back() const {
        return  Back();
    }

    /*! Returns wether the queue is empty or not. */
    bool IsEmpty() const {
        return  IsEmpty();
    }

    /*! Returns the queue size. */
    uint64 Size() const {
        return  Size();
    }

    /*!
        Clear the queue, deallocating everything.
    */
    void Clear() {
        Clear();
    }

    /*!
        Push, insert a new element at the end of the queue.
    */
    void Push( const T& iValue ) {
        PushBack( iValue );
    }

    /*!
        Push, insert a new element at the end of the queue.
    */
    void Push( T&& iValue ) {
        PushBack( std::forward< T >( iValue ) );
    }

    /*!
        Emplace, emplace a new element at end of the queue.
    */
    template< class... Args >
    void Emplace( Args&& ... args ) {
        EmplaceBack( std::forward< Args >(args)... );
    }

    /*!
        Pop, pop the front element.
        The behaviour is undefined is the queue is empty.
    */
    void Pop() {
        PopFront();
    }
};

ULIS_NAMESPACE_END

