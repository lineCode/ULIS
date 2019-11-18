/**
*
*   ULIS
*__________________
*
* @file     ULIS.FX.Convolution.Kernel.h
* @author   Clement Berthaud
* @brief    This file provides the declaration for the Kernel tools.
*/
#pragma once
#include "ULIS/Base/ULIS.Base.BaseTypes.h"
#include "ULIS/Maths/ULIS.Maths.Geometry.h"
#include "ULIS/Maths/ULIS.Maths.Utility.h"
#include <initializer_list>

namespace ULIS {
/////////////////////////////////////////////////////
// Kernel Edge Handling
enum class eKernelEdgeMode : uint8
{
      kExtend
    , kConstant
    , kMirror
    , kWrap
    , kTransparent
    , kSkip
};


/////////////////////////////////////////////////////
// FKernel
class  FKernel
{
public:
    // Construction / Destruction
    ~FKernel();
    FKernel( const FSize& iSize, float iValue = 0.f, const FPoint& iAnchor = FPoint( -1, -1 ), eKernelEdgeMode iKernelEdgeMode = eKernelEdgeMode::kExtend );
    FKernel( const FSize& iSize, std::initializer_list< float > iNums, const FPoint& iAnchor = FPoint( -1, -1 ), eKernelEdgeMode iKernelEdgeMode = eKernelEdgeMode::kExtend );
    FKernel( const FKernel& iRhs );             // Copy Constructor
    FKernel& operator=( const FKernel& iRhs );  // Copy Assignment Operator
    FKernel( const FKernel&& iRhs );

public:
    // Public API
    void  Set( std::initializer_list< float > iNums );
    float At( uint iX, uint iY ) const;
    float At( FPoint iPoint ) const;
    void SetAt( uint iX, uint iY, float iValue );
    void SetAt( FPoint iPoint, float iValue );
    float& operator[] ( uint iIndex );
    const float& operator[] ( uint iIndex ) const;
    void Clear();
    void Fill( float iValue );
    void SetZeroes();
    void SetOnes();
    float Sum() const;
    void Normalize();
    FKernel Normalized() const;
    bool IsNormalized() const;
    int Width() const;
    int Height() const;
    int Length() const;
    const FSize& Size() const;
    const FPoint& Anchor() const;
    eKernelEdgeMode KernelEdgeMode() const;

private:
    // Private API
    void Init();
    void ComputeAnchor();
    void AssertValid() const;
    void Allocate();
    void Deallocate();

private:
    // Private member data
    FSize mSize;
    FPoint mAnchor;
    eKernelEdgeMode mKernelEdgeMode;
    float* mData;
    bool mOwning;
};

} // namespace ULIS

