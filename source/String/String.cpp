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
#include "Memory/Array.h"

ULIS_NAMESPACE_BEGIN
FString::~FString() {
}

FString::FString() {
}

FString::FString( const char_type* iStr ) {
}

FString::FString( const FString& iStr ) {
}

FString::FString( FString&& iStr ) {
}

FString::FString( const FWString& iWStr ) {
}

FString&
FString::operator=( const FString& iStr ) {
}

FString&
FString::operator=( FString& iStr ) {
}

FString
FString::Copy() const {
}

FString
FString::SubString( uint64 iPos, uint64 iCount ) const {
}

uint64
FString::Capacity() const {
}

uint64
FString::Size() const {
}

const FString::char_type*
FString::Data() const {
}


FString::char_type&
FString::operator[]( uint64 iIndex ) {
}

const FString::char_type&
FString::operator[]( uint64 iIndex ) const {
}

FString::char_type&
FString::At( uint64 iIndex ) {
}

const FString::char_type&
FString::At( uint64 iIndex ) const {
}

FString::char_type&
FString::Front() {
}

const
FString::char_type&
FString::Front() const {
}

FString::char_type&
FString::Back() {
}

const FString::char_type&
FString::Back() const {
}


FWString
FString::ToWString() const {
}

FString&
FString::Append( const FString& iStr ) {
}

FString&
FString::Append( const char_type* iStr ) {
}

FString&
FString::Append( char_type iChar ) {
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

ULIS_NAMESPACE_END

