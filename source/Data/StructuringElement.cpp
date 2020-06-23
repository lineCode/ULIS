// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS3
*__________________
*
* @file         StructuringElement.cpp
* @author       Clement Berthaud
* @brief        This file provides the definition for the StructuringElement class.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include "Data/StructuringElement.h"
#include "Maths/Maths.h"

ULIS3_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
// FStructuringElement
//--------------------------------------------------------------------------------------
//----------------------------------------------------------- Construction / Destruction
FStructuringElement::~FStructuringElement()
{
}

FStructuringElement::FStructuringElement( const FVec2I& iSize, eStructuringElementValue iValue )
    : tSuperClass( iSize.x, iSize.y, ULIS3_FORMAT_G8 )
    , mPivot( iSize / 2 )
{
    for( int i = 0; i < Length(); ++i )
        mData[ i ] = static_cast< uint8 >( iValue );

}

FStructuringElement::FStructuringElement( const FVec2I& iSize, std::initializer_list< eStructuringElementValue > iNums )
    : tSuperClass( iSize.x, iSize.y, ULIS3_FORMAT_G8 )
    , mPivot( iSize / 2 )
{
    ULIS3_ASSERT( Length() == iNums.size(), "Bad input initialized list for Kernel" );
    for( int i = 0; i < iNums.size(); ++i )
        mData[ i ] = static_cast< uint8 >( *( iNums.begin() + i ) );
}

FStructuringElement::FStructuringElement( const FStructuringElement& iOther )
    : tSuperClass( iOther.Width(), iOther.Height(), ULIS3_FORMAT_G8 )
    , mPivot( iOther.Size() / 2 )
{
    memcpy( mData, iOther.mData, BytesTotal() );
}

FStructuringElement::FStructuringElement( FStructuringElement&& iOther )
    : tSuperClass( iOther.mData, iOther.Width(), iOther.Height(), ULIS3_FORMAT_G8 )
    , mPivot( iOther.Size() / 2 )
{
    iOther.ReleaseOwnership();
    iOther.mData = nullptr;
    TakeOwnership();
}

FStructuringElement&
FStructuringElement::operator=( const FStructuringElement& iOther ) {
    mPivot = iOther.Size() / 2;
    delete [] mData;
    mWidth = iOther.Width();
    mHeight = iOther.Height();
    mBPS = mWidth * FormatInfo().BPP;
    mBTT = mHeight * mBPS;
    mData = new tByte[ mBTT ];
    memcpy( mData, iOther.mData, BytesTotal() );
    return  *this;
}

FStructuringElement&
FStructuringElement::operator=( FStructuringElement&& iOther ) {
    mPivot = iOther.Size() / 2;
    delete [] mData;
    mWidth = iOther.Width();
    mHeight = iOther.Height();
    mBPS = mWidth * FormatInfo().BPP;
    mBTT = mHeight * mBPS;
    iOther.ReleaseOwnership();
    mData = iOther.mData;
    iOther.mData = nullptr;
    TakeOwnership();
    return  *this;
}

//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------- Public API
void
FStructuringElement::Set( std::initializer_list< eStructuringElementValue > iNums ) {
    ULIS3_ASSERT( Length() == iNums.size(), "Bad input initialized list for Kernel" );
    for( int i = 0; i < iNums.size(); ++i )
        mData[ i ] = static_cast< uint8 >( *( iNums.begin() + i ) );
}

eStructuringElementValue
FStructuringElement::At( int iX, int iY ) const {
    return  static_cast< eStructuringElementValue >( *PixelPtr( iX, iY ) );
}

eStructuringElementValue
FStructuringElement::At( FVec2I iPoint ) const {
    return  static_cast< eStructuringElementValue >( *PixelPtr( iPoint.x, iPoint.y ) );
}

void
FStructuringElement::SetAt( int iX, int iY, eStructuringElementValue iValue ) {
    *PixelPtr( iX, iY ) = static_cast< uint8 >( iValue );
}

void
FStructuringElement::SetAt( FVec2I iPoint, eStructuringElementValue iValue ) {
    *PixelPtr( iPoint.x, iPoint.y ) = static_cast< uint8 >( iValue );
}

void
FStructuringElement::Clear() {
    Fill( MP_ZERO );
}

void
FStructuringElement::Fill( eStructuringElementValue iValue ) {
    for( int i = 0; i < Length(); ++i )
        mData[ i ] = static_cast< uint8 >( iValue );
}

void
FStructuringElement::SetZeroes() {
    Clear();
}

void
FStructuringElement::SetOnes() {
    Fill( MP_ZERO );
}

void
FStructuringElement::FlipX() {
    const tSize w = Width() - 1;
    FStructuringElement ret( FVec2I( mWidth, mHeight ) );
    for( int x = 0; x < mWidth; ++x )
        for( int y = 0; y < mHeight; ++y )
            ret.SetAt( x, y, At( w - x, y ) );
    *this = std::move( ret );
}

void
FStructuringElement::FlipY() {
    const tSize h = Height() - 1;
    FStructuringElement ret( FVec2I( mWidth, mHeight ) );
    for( int x = 0; x < mWidth; ++x )
        for( int y = 0; y < mHeight; ++y )
            ret.SetAt( x, y, At( x, h - y ) );
    *this = std::move( ret );
}

void
FStructuringElement::Rotate90CW() {
    FStructuringElement ret( FVec2I( mHeight, mWidth ) );
    const int w = Height() - 1;
    const int h = Width() - 1;
    for( int x = 0; x < mHeight; ++x )
        for( int y = 0; y < mWidth; ++y )
            ret.SetAt( x, y, At( y, w - x ) );
    *this = std::move( ret );
}

void
FStructuringElement::Rotate90CCW() {
    FStructuringElement ret( FVec2I( mHeight, mWidth ) );
    const int w = Height() - 1;
    const int h = Width() - 1;
    for( int x = 0; x < mHeight; ++x )
        for( int y = 0; y < mWidth; ++y )
            ret.SetAt( x, y, At( h - y, x ) );
    *this = std::move( ret );
}

void
FStructuringElement::Rotate180() {
    FStructuringElement ret( FVec2I( mWidth, mHeight ) );
    const int w = Width() - 1;
    const int h = Height() - 1;
    for( int x = 0; x < mWidth; ++x )
        for( int y = 0; y < mHeight; ++y )
            ret.SetAt( x, y, At( w - x, h - y ) );
    *this = std::move( ret );
}

FStructuringElement
FStructuringElement::FlippedX() const { 
    FStructuringElement ret( *this );
    ret.FlipX();
    return  ret;
}

FStructuringElement
FStructuringElement::FlippedY() const {
    FStructuringElement ret( *this );
    ret.FlipY();
    return  ret;
}

FStructuringElement
FStructuringElement::Rotated90CW() const {
    FStructuringElement ret( *this );
    ret.Rotate90CW();
    return  ret;
}

FStructuringElement
FStructuringElement::Rotated90CCW() const {
    FStructuringElement ret( *this );
    ret.Rotate90CCW();
    return  ret;
}

FStructuringElement
FStructuringElement::Rotated180() const {
    FStructuringElement ret( *this );
    ret.Rotate180();
    return  ret;
}

const FVec2I&
FStructuringElement::Size() const {
    return  FVec2I( Width(), Height() );
}

const FVec2I&
FStructuringElement::Pivot() const {
    return  mPivot;
}

void
FStructuringElement::SetPivot( const FVec2I& iPivot ) {
    mPivot = iPivot;
}

ULIS3_NAMESPACE_END

