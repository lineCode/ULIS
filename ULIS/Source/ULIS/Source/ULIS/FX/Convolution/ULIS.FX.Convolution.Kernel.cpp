/**
*
*   ULIS
*__________________
*
* @file     ULIS.FX.Convolution.Kernel.cpp
* @author   Clement Berthaud
* @brief    This file provides the definition for the Kernel tools.
*/
#pragma once
#include "ULIS/FX/Convolution/ULIS.FX.Convolution.Kernel.h"
#include <cassert>

namespace ULIS {
/////////////////////////////////////////////////////
// FKernel
//--------------------------------------------------------------------------------------
//----------------------------------------------------------- Construction / Destruction
FKernel::~FKernel()
{
    Deallocate();
}


FKernel::FKernel( const FSize& iSize, float iValue, const FPoint& iAnchor, eKernelEdgeMode iKernelEdgeMode )
    : mSize( iSize )
    , mAnchor( iAnchor )
    , mKernelEdgeMode( iKernelEdgeMode )
    , mData( nullptr )
    , mOwning( true )
{
    Init();
    Fill( iValue );
}


FKernel::FKernel( const FSize& iSize, std::initializer_list< float > iNums, const FPoint& iAnchor, eKernelEdgeMode iKernelEdgeMode )
    : mSize( iSize )
    , mAnchor( iAnchor )
    , mKernelEdgeMode( iKernelEdgeMode )
    , mData( nullptr )
    , mOwning( true )
{
    Init();
    assert( Length() == iNums.size() );
    for( int i = 0; i < iNums.size(); ++i )
        mData[ i ] = *( iNums.begin() + i );
}


FKernel::FKernel( const FKernel& iRhs )
    : mSize( iRhs.mSize )
    , mAnchor( iRhs.mAnchor )
    , mKernelEdgeMode( iRhs.mKernelEdgeMode )
    , mData( nullptr )
    , mOwning( true )
{
    Init();
    memcpy( mData, iRhs.mData, Length() * sizeof( float ) );
}


FKernel&
FKernel::operator=( const FKernel& iRhs )
{
    Deallocate();
    mSize = iRhs.mSize;
    mAnchor = iRhs.mAnchor;
    mKernelEdgeMode = iRhs.mKernelEdgeMode;
    Init();
    memcpy( mData, iRhs.mData, Length() * sizeof( float ) );
    mOwning = true;
    return  (*this);
}


FKernel::FKernel( const FKernel&& iRhs )
    : mSize( iRhs.mSize )
    , mAnchor( iRhs.mAnchor )
    , mKernelEdgeMode( iRhs.mKernelEdgeMode )
    , mData( nullptr )
    , mOwning( true )
{
    Init();
    memcpy( mData, iRhs.mData, Length() * sizeof( float ) );
}


//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------- Public API
void
FKernel::Set( std::initializer_list< float > iNums )
{
    assert( Length() == iNums.size() );
    for( int i = 0; i < iNums.size(); ++i )
        mData[ i ] = *( iNums.begin() + i );
}


float
FKernel::At( uint iX, uint iY ) const
{
    assert( iX >= 0 && iX < mSize.x );
    assert( iY >= 0 && iY < mSize.y );
    return  mData[ iY * mSize.x + iX ];
}


float
FKernel::At( FPoint iPoint ) const
{
    assert( iPoint.x >= 0 && iPoint.x < mSize.x );
    assert( iPoint.y >= 0 && iPoint.y < mSize.y );
    return  mData[ iPoint.y * mSize.x + iPoint.x ];
}


void
FKernel::SetAt( uint iX, uint iY, float iValue )
{
    assert( iX >= 0 && iX < mSize.x );
    assert( iY >= 0 && iY < mSize.y );
    mData[ iY * mSize.x + iX ] = iValue;
}


void
FKernel::SetAt( FPoint iPoint, float iValue )
{
    assert( iPoint.x >= 0 && iPoint.x < mSize.x );
    assert( iPoint.y >= 0 && iPoint.y < mSize.y );
    mData[ iPoint.y * mSize.x + iPoint.x ] = iValue;
}


float&
FKernel::operator[] ( uint iIndex )
{
    assert( iIndex >= 0 && iIndex < Length() );
    return  mData[ iIndex ];
}


const float&
FKernel::operator[] ( uint iIndex ) const
{
    assert( iIndex >= 0 && iIndex < Length() );
    return  mData[ iIndex ];
}


void
FKernel::Clear()
{
    memset( mData, 0, Length() * sizeof( float ) );
}


void
FKernel::Fill( float iValue )
{
    for( int i = 0; i < Length(); ++i )
        mData[i] = iValue;
}


void
FKernel::SetZeroes()
{
    Clear();
}


void
FKernel::SetOnes()
{
    Fill( 1.f );
}


float
FKernel::Sum() const
{
    float result = 0.f;
    for( int i = 0; i < Length(); ++i )
        result += mData[i];
    return  result;
}

void
FKernel::Normalize()
{
    float sum = Sum();
    for( int i = 0; i < Length(); ++i )
        mData[i] /= sum;
}

FKernel
FKernel::Normalized() const
{
    FKernel result( *this );
    result.Normalize();
    return  result;
}


bool
FKernel::IsNormalized() const
{
    return  FMath::Abs( Sum() - 1.f ) < FMath::kEpsilonf;
}


int
FKernel::Width() const
{
    return  mSize.x;
}


int
FKernel::Height() const
{
    return  mSize.y;
}


int
FKernel::Length() const
{
    return  Width() * Height();
}


const FSize&
FKernel::Size() const
{
    return  mSize;
}


const FPoint&
FKernel::Anchor() const
{
    return  mAnchor;
}


eKernelEdgeMode
FKernel::KernelEdgeMode() const
{
    return  mKernelEdgeMode;
}


//--------------------------------------------------------------------------------------
//-------------------------------------------------------------------------- Private API
void
FKernel::Init()
{
    ComputeAnchor();
    AssertValid();
    Allocate();
}


void
FKernel::ComputeAnchor()
{
    if( mAnchor.x == -1 && mAnchor.y == -1 )
    {
        mAnchor.x = mSize.x / 2;
        mAnchor.y = mSize.y / 2;
    }
}


void
FKernel::AssertValid() const
{
    assert( mSize.x > 0 && mSize.y > 0 );
    assert( mAnchor.x >= 0 && mAnchor.x < mSize.x );
    assert( mAnchor.y >= 0 && mAnchor.y < mSize.y );
}


void
FKernel::Allocate()
{
    mData = new float[ Length() ];
}


void
FKernel::Deallocate()
{
    if( mOwning )
        delete [] mData;
}


} // namespace ULIS

