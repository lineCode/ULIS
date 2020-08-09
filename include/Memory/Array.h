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
#include "Math/Math.h"
#include <utility>

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
    ~TArray< T >()
    {
        CleanupBulk();
    }

    /*! Default constructor with size 0, capicity 1, uninitialized. */
    TArray< T >()
        : mBulk( nullptr )
        , mCapacity( 0 )
        , mSize( 0 )
    {}

    /*! Constructor with known size, both capacity and size will match the requested size. */
    TArray< T >( uint64 iSize )
        : mBulk( nullptr )
        , mCapacity( iSize )
        , mSize( iSize )
    {
        if( iSize > 0 ) {
            mBulk = reinterpret_cast< T* >( XMalloc( sizeof( T ) * iSize ) );
            for( uint64 i = 0; i < mSize; ++i ) {
                new  ( mBulk + i )  T;
            }
        }
    }

    /*! Copy constructor. */
    TArray< T >( const TArray< T >& iOther ) = delete;

    /*! Move constructor. */
    TArray< T >( TArray< T >&& iOther )
        : mBulk( iOther.mBulk )
        , mCapacity( iOther.mCapacity )
        , mSize( iOther.mSize )
    {
        iOther.mBulk = nullptr;
        iOther.mSize = 0;
        iOther.mCapacity = 0;
    }

    /*! Returns the raw bits. */
    uint8* Bits() {
        return  reinterpret_cast< uint8* >( mBulk );
    }

    /*! Returns the raw const bits. */
    const uint8* Bits() const {
        return  reinterpret_cast< const uint8* >( mBulk );
    }

    /*! Returns the raw storage. */
    T* Data() {
        return  mBulk;
    }

    /*! Returns the raw storage. */
    const T* Data() const {
        return  mBulk;
    }

    /*! Access component at index. */
    T& operator[]( uint64 iIndex ) {
        ULIS_ASSERT( mSize > 0, "Bad call, array is empty" );
        ULIS_ASSERT( iIndex >= 0 && iIndex < mSize, "Bad Index" );
        ULIS_ASSERT( mBulk != nullptr, "Error, no bulk, array is uninitialized" );
        return  mBulk[ iIndex ];
    }

    /*! Access const component at index. */
    const T& operator[]( uint64 iIndex ) const {
        ULIS_ASSERT( mSize > 0, "Bad call, array is empty" );
        ULIS_ASSERT( iIndex >= 0 && iIndex < mSize, "Bad Index" );
        ULIS_ASSERT( mBulk != nullptr, "Error, no bulk, array is uninitialized" );
        return  mBulk[ iIndex ];
    }

    /*! Access component at index. */
    T& At( uint64 iIndex ) {
        ULIS_ASSERT( mSize > 0, "Bad call, array is empty" );
        ULIS_ASSERT( iIndex >= 0 && iIndex < mSize, "Bad Index" );
        ULIS_ASSERT( mBulk != nullptr, "Error, no bulk, array is uninitialized" );
        return  mBulk[ iIndex ];
    }

    /*! Access const component at index. */
    const T& At( uint64 iIndex ) const {
        ULIS_ASSERT( mSize > 0, "Bad call, array is empty" );
        ULIS_ASSERT( iIndex >= 0 && iIndex < mSize, "Bad Index" );
        ULIS_ASSERT( mBulk != nullptr, "Error, no bulk, array is uninitialized" );
        return  mBulk[ iIndex ];
    }

    /*! Access component at front. */
    T& Front() {
        ULIS_ASSERT( mSize > 0, "Bad call, array is empty" );
        return  At( 0 );
    }

    /*! Access const component at front. */
    const T& Front() const {
        ULIS_ASSERT( mSize > 0, "Bad call, array is empty" );
        return  At( 0 );
    }

    /*! Access component at back. */
    T& Back() {
        ULIS_ASSERT( mSize > 0, "Bad call, array is empty" );
        return  At( mSize - 1 );
    }

    /*! Access const component at back. */
    const T& Back() const {
        ULIS_ASSERT( mSize > 0, "Bad call, array is empty" );
        return  At( mSize - 1 );
    }

    /*! Returns wether the array is empty or not. */
    bool IsEmpty() const {
        return  mSize == 0;
    }

    /*! Returns the array capacity. */
    uint64 Capacity() const {
        return  mCapacity;
    }

    /*! Returns the array size. */
    uint64 Size() const {
        return  mSize;
    }

    /*!
        Reserve some capacity for future usage, if iCapacity is bigger than the
        current capacity. If iCapacity is lower or equal to capacity, this
        function does nothing.
    */
    void Reserve( uint64 iCapacity ) {
        uint64 max_desired = FMath::Max( iCapacity, mCapacity );
        if( max_desired > mCapacity ) {
            T* temp_bulk = reinterpret_cast< T* >( XMalloc( sizeof( T ) * max_desired ) );
            if( mBulk != nullptr ) {
                memcpy( temp_bulk, mBulk, mSize );
                XFree( mBulk );
            }
            mBulk = temp_bulk;
            mCapacity = iCapacity;
        }
    }

    /*!
        Shrink the capacity to fit the size.
        If the capacity is already the same as the size, the function does
        nothing.
    */
    void Shrink() {
        ULIS_ASSERT( mCapacity >= mSize, "Error, invalid state, mCapacity shouldn't be smaller than mSize" );
        if( mCapacity > mSize ) {
            T* temp_bulk = reinterpret_cast< T* >( XMalloc( sizeof( T ) * mSize ) );
            if( mBulk != nullptr ) {
                memcpy( temp_bulk, mBulk, mSize );
                XFree( mBulk );
            }
            mBulk = temp_bulk;
            mCapacity = mSize;
        }
    }

    /*!
        Resize the usage size of the container.
    */
    void Resize( uint64 iSize ) {
        if( iSize == 0 ) {
            Clear();
        } else {
            uint64 min_desired = FMath::Min( iSize, mSize );
            T* temp_bulk = reinterpret_cast< T* >( XMalloc( sizeof( T ) * iSize ) );
            if( mBulk != nullptr ) {
                memcpy( temp_bulk, mBulk, min_desired );
                XFree( mBulk );
            }

            for( uint64 i = min_desired; i < iSize; ++i ) {
                new  ( mBulk + i )  T;
            }

            mCapacity = iSize;
            mSize = iSize;
        }
    }

    /*!
        Clear the array, deallocating everything.
    */
    void Clear() {
        CleanupBulk();
        mCapacity = 0;
        mSize = 0;
    }

    /*!
        PopBack, remove last element.
    */
    void PopBack() {
        ULIS_ASSERT( mSize > 0, "Bad call, array is empty" );
        ULIS_ASSERT( mBulk != nullptr, "Error, no bulk, array is uninitialized" );
        mBulk[ (--mSize) ].~T();
    }

    /*!
        PushBack, insert a new element at the end of the buffer, possibly
        reallocating the underlying storage if the capacity has been reached.
    */
    void PushBack( const T& iValue ) {
        if( mBulk == nullptr ) {
            ULIS_ASSERT( mCapacity == 0, "Invalid state" );
            mBulk = reinterpret_cast< T* >( XMalloc( sizeof( T ) ) );
            mCapacity = 1;
            mSize = 1;
            new  ( mBulk )  T( iValue );
        } else {
            if( mSize == mCapacity ) {
                ULIS_ASSERT( mCapacity > 0, "Invalid state" );
                uint64 new_cap = static_cast< uint64 >( FMath::Ceil( mCapacity * FMath::kGoldenRatio ) );
                T* temp_bulk = reinterpret_cast< T* >( XMalloc( sizeof( T ) * new_cap ) );
                memcpy( temp_bulk, mBulk, mSize );
                XFree( mBulk );
                new  ( mBulk + mSize )  T( iValue );
                mSize++;
            }
        }
    }

    /*!
        PushBack, insert a new element at the end of the buffer, possibly
        reallocating the underlying storage if the capacity has been reached.
    */
    void PushBack( T&& iValue ) {
        if( mBulk == nullptr ) {
            ULIS_ASSERT( mCapacity == 0, "Invalid state" );
            mBulk = reinterpret_cast< T* >( XMalloc( sizeof( T ) ) );
            mCapacity = 1;
            mSize = 1;
            new  ( mBulk )  T( iValue );
        } else {
            if( mSize == mCapacity ) {
                ULIS_ASSERT( mCapacity > 0, "Invalid state" );
                uint64 new_cap = static_cast< uint64 >( FMath::Ceil( mCapacity * FMath::kGoldenRatio ) );
                T* temp_bulk = reinterpret_cast< T* >( XMalloc( sizeof( T ) * new_cap ) );
                memcpy( temp_bulk, mBulk, mSize );
                XFree( mBulk );
                new  ( mBulk + mSize )  T( iValue );
                mSize++;
            }
        }
    }

    /*!
        PushBack, emplace a new element at the end of the buffer, possibly
        reallocating the underlying storage if the capacity has been reached.
    */
    template< class... Args >
    void EmplaceBack( Args&& ... args ) {
        if( mBulk == nullptr ) {
            ULIS_ASSERT( mCapacity == 0, "Invalid state" );
            mBulk = reinterpret_cast< T* >( XMalloc( sizeof( T ) ) );
            mCapacity = 1;
            mSize = 1;
            new  ( mBulk )  T( std::forward< Args >(args)... );
        } else {
            if( mSize == mCapacity ) {
                ULIS_ASSERT( mCapacity > 0, "Invalid state" );
                uint64 new_cap = static_cast< uint64 >( FMath::Ceil( mCapacity * FMath::kGoldenRatio ) );
                T* temp_bulk = reinterpret_cast< T* >( XMalloc( sizeof( T ) * new_cap ) );
                memcpy( temp_bulk, mBulk, mSize );
                XFree( mBulk );
                new  ( mBulk + mSize )  T( std::forward< Args >(args)... );
                mSize++;
            }
        }
    }

private:
    /*!
        CleanupBulk explicitely calls destructors on elements to be removed, then
        deallocates the underlying bulk buffer and sets mBulk to nullptr.
    */
    void CleanupBulk() {
        if( mBulk != nullptr ) {
            for( uint64 i = 0; i < mSize; ++i ) {
                mBulk[i].~T();
            }
            XFree( mBulk );
            mBulk = nullptr;
        }
    }

private:
    T* mBulk; ///< The main buffer storage.
    uint64 mCapacity; ///< The array capacity, may be bigger than size.
    uint64 mSize; ///< The array usage size.
};

ULIS_NAMESPACE_END

