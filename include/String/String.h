// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS3
*__________________
*
* @file         String.h
* @author       Clement Berthaud
* @brief        This file provides the definition for the TString class.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"
#include "Memory/Array.h"

ULIS_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
/// @class      TString
/// @brief      The TString class provides a simple dynamic string class
/// @details    The need of a custom TString class rose from the fact that std::
///             classes cannot be exported easily accross dll boundaries when
///             ULIS is compiled as a shared library.
template< typename T >
class TString
    : public TArray< T >
{
public:
    /*! Destroy the Array and cleanup memory. */
    ~TString< T >()
    {
    }

    /*! Default constructor with size 0, capicity 1, uninitialized. */
    TString< T >()
        : TArray< T >()
    {}

    /*! Constructor with known size, both capacity and size will match the requested size. */
    TString< T >( uint64 iSize )
        : TArray< T >( iSize )
    {}

    /*! Copy constructor. */
    TString< T >( const TString< T >& iOther )
        : TArray< T >()
    {}

    /*! Move constructor. */
    TString< T >( TString< T >&& iOther )
        : TArray< T >( std::forward( iOther ) )
    {}
};

typedef TString< char > FString;
typedef TString< wchar_t > FWString;
template class ULIS_API TString< char >;
template class ULIS_API TString< wchar_t >;

ULIS_NAMESPACE_END

