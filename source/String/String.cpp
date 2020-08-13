// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS3
*__________________
*
* @file         String.cpp
* @author       Clement Berthaud
* @brief        This file provides the definition for the FString class.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "String/String.h"
#include "String/WString.h"
#include "String/CRC32.h"
#include "String/MD5.h"
#include "String/UUID.h"
#include "Math/Math.h"
#include "Memory/Array.h"
#include <cstring>

ULIS_NAMESPACE_BEGIN
FString::~FString() {
    CleanupBulk();
}

FString::FString()
    : mBulk( nullptr )
    , mCapacity( 1 )
    , mSize( 0 )
{
    mBulk = new char_type[1];
    mBulk[0] = '\0';
}

FString::FString( const char_type* iStr )
    : mBulk( nullptr )
    , mCapacity( 0 )
    , mSize( 0 )
{
    uint64 len = strlen( iStr ) + 1;
    mBulk = new char_type[ len ];
    memcpy( mBulk, iStr, sizeof( char_type ) * len );
    mCapacity = len;
    mSize = len - 1;
}

FString::FString( const FString& iStr )
    : mBulk( nullptr )
    , mCapacity( 0 )
    , mSize( 0 )
{
    uint64 len = iStr.Size() + 1;
    mBulk = new char_type[ len ];
    memcpy( mBulk, iStr.mBulk, sizeof( char_type ) * len );
    mCapacity = len;
    mSize = len - 1;
}

FString::FString( FString&& iStr )
    : mBulk( iStr.mBulk )
    , mCapacity( iStr.mCapacity )
    , mSize( iStr.mSize )
{
    iStr.mBulk = nullptr;
    iStr.mCapacity = 0;
    iStr.mSize = 0;
}

FString::FString( const FWString& iWStr )
    : mBulk( nullptr )
    , mCapacity( 1 )
    , mSize( 0 )
{
    ULIS_ASSERT( false, "TODO" );
    mBulk = new char_type[1];
    mBulk[0] = '\0';
}

FString&
FString::operator=( const FString& iStr ) {
    CleanupBulk();
    uint64 len = iStr.Size() + 1;
    mBulk = new char_type[ len ];
    memcpy( mBulk, iStr.mBulk, sizeof( char_type ) * len );
    mCapacity = len;
    mSize = len - 1;
}

FString&
FString::operator=( FString&& iStr ) {
    mBulk = iStr.mBulk;
    mCapacity = iStr.mCapacity;
    mSize = iStr.mSize;
    iStr.mBulk = nullptr;
    iStr.mCapacity = 0;
    iStr.mSize = 0;
}

FString
FString::Copy() const {
    return  FString( *this );
}

FString
FString::SubString( uint64 iPos, uint64 iCount ) const {
    uint64 start = FMath::Min( iPos, mSize );
    uint64 end = FMath::Min( iPos + iCount, mSize );
    uint64 len = end - start;
    FString result( len );
    memcpy( result.mBulk, mBulk + start, len );
    result.mBulk[len] = '\0';

    return  result;
}

uint64
FString::Capacity() const {
    return  mCapacity;
}

uint64
FString::Size() const {
    return  mSize;
}

const FString::char_type*
FString::Data() const {
    return  mBulk;
}


FString::char_type&
FString::operator[]( uint64 iIndex ) {
    ULIS_ASSERT( mSize > 0, "Bad call, string is empty" );
    ULIS_ASSERT( iIndex >= 0 && iIndex < mSize, "Bad Index" );
    ULIS_ASSERT( mBulk != nullptr, "Error, no bulk, string is uninitialized" );
    return  mBulk[ iIndex ];
}

const FString::char_type&
FString::operator[]( uint64 iIndex ) const {
    ULIS_ASSERT( mSize > 0, "Bad call, string is empty" );
    ULIS_ASSERT( iIndex >= 0 && iIndex < mSize, "Bad Index" );
    ULIS_ASSERT( mBulk != nullptr, "Error, no bulk, string is uninitialized" );
    return  mBulk[ iIndex ];
}

FString::char_type&
FString::At( uint64 iIndex ) {
    ULIS_ASSERT( mSize > 0, "Bad call, string is empty" );
    ULIS_ASSERT( iIndex >= 0 && iIndex < mSize, "Bad Index" );
    ULIS_ASSERT( mBulk != nullptr, "Error, no bulk, string is uninitialized" );
    return  mBulk[ iIndex ];
}

const FString::char_type&
FString::At( uint64 iIndex ) const {
    ULIS_ASSERT( mSize > 0, "Bad call, string is empty" );
    ULIS_ASSERT( iIndex >= 0 && iIndex < mSize, "Bad Index" );
    ULIS_ASSERT( mBulk != nullptr, "Error, no bulk, string is uninitialized" );
    return  mBulk[ iIndex ];
}

FString::char_type&
FString::Front() {
    ULIS_ASSERT( mSize > 0, "Bad call, string is empty" );
    ULIS_ASSERT( mBulk != nullptr, "Error, no bulk, string is uninitialized" );
    return  mBulk[ 0 ];
}

const
FString::char_type&
FString::Front() const {
    ULIS_ASSERT( mSize > 0, "Bad call, string is empty" );
    ULIS_ASSERT( mBulk != nullptr, "Error, no bulk, string is uninitialized" );
    return  mBulk[ 0 ];
}

FString::char_type&
FString::Back() {
    ULIS_ASSERT( mSize > 0, "Bad call, string is empty" );
    ULIS_ASSERT( mBulk != nullptr, "Error, no bulk, string is uninitialized" );
    return  mBulk[ mSize - 1 ];
}

const FString::char_type&
FString::Back() const {
    ULIS_ASSERT( mSize > 0, "Bad call, string is empty" );
    ULIS_ASSERT( mBulk != nullptr, "Error, no bulk, string is uninitialized" );
    return  mBulk[ mSize - 1 ];
}

FWString
FString::ToWString() const {
    ULIS_ASSERT( false, "TODO" );
    FWString result;
    return  result;
}

FString&
FString::Append( const FString& iStr ) {
    uint64 len = mSize + iStr.mSize + 1;
    char_type* tmp = new char_type[ len ];
    memcpy( tmp, mBulk, mSize );
    memcpy( tmp + mSize, iStr.mBulk, iStr.mSize );
    mCapacity = len;
    mSize = len - 1;
    tmp[ len ] = '\0';
    CleanupBulk();
    mBulk = tmp;
}

FString&
FString::Append( const char_type* iStr ) {
    uint64 olen = strlen( iStr );
    uint64 len = mSize + olen + 1;
    char_type* tmp = new char_type[ len ];
    memcpy( tmp, mBulk, mSize );
    memcpy( tmp + mSize, iStr, olen );
    mCapacity = len;
    mSize = len - 1;
    tmp[ len ] = '\0';
    CleanupBulk();
    mBulk = tmp;
}

FString&
FString::Append( char_type iChar ) {
    uint64 len = mSize + 1 + 1;
    char_type* tmp = new char_type[ len ];
    memcpy( tmp, mBulk, mSize );
    tmp[ mSize ] = iChar;
    mCapacity = len;
    mSize = len - 1;
    tmp[ len ] = '\0';
    CleanupBulk();
    mBulk = tmp;
}

FString&
FString::Prepend( const FString& iStr ) {
}

FString&
FString::Prepend( const char_type* iStr ) {
}

FString&
FString::Prepend( char_type iChar ) {
}

bool
FString::operator==( const FString& iOther ) {
}

bool
FString::operator!=( const FString& iOther ) {
}

int
FString::ToInt() const {
}

unsigned int
FString::ToUnsignedInt() const {
}


float
FString::ToFloat() const {
}

double
FString::ToDouble() const {
}

//static
FString
FString::FromInt( int iValue ) {
}

//static
FString
FString::FromUnsignedInt( unsigned int iValue ) {
}

//static
FString
FString::FromFloat( float iValue ) {
}

//static
FString
FString::FromDouble( double iValue ) {
}

//static
FString
FString::FromWString( const FWString& iValue ) {
}

FString
FString::ToUpper() const {
}

FString
FString::ToLower() const {
}

bool
FString::IsEmpty() const {
}

void
FString::Reserve( uint64 iCapacity ) {
}

void
FString::Shrink() {
}

void
FString::Resize( uint64 iSize ) {
}

void
FString::Clear() {
}

TArray< FString >
FString::Split( const FString& iSep ) const {
}

TArray< FString >
FString::Split( char_type iSep ) const {
}

void
FString::Erase( uint64 iPos, uint64 iCount ) const {
}

void
FString::Insert( uint64 iPos, const FString& iStr ) const {
}

int64
FString::FindFirst( const FString& iStr ) const {
}

int64
FString::FindLast( const FString& iStr ) const {
}

int64
FString::FindFrom( uint64 iPos, const FString& iStr ) const {
}

bool
FString::ReplaceFirst( const FString& iA, const FString& iB ) const {
}

bool
FString::ReplaceLast( const FString& iA, const FString& iB ) const {
}

bool
FString::ReplaceFrom( uint64 iPos, const FString& iA, const FString& iB ) const {
}

uint64
FString::ReplaceAll( const FString& iA, const FString& iB ) const {
}

FString
FString::MD5() const {
}

uint32
FString::CRC32() const {
}

// Private
void
FString::CleanupBulk() {
    if( mBulk != nullptr ) {
        delete [] mBulk;
        mBulk = nullptr;
    }
}

FString::FString( uint64 iSize )
    : mBulk( new char_type[ iSize + 1 ] )
    , mCapacity( iSize + 1 )
    , mSize( iSize )
{
}

ULIS_NAMESPACE_END

