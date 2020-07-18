// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS3
*__________________
*
* @file         Format.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the Format utilities.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"

ULIS3_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
/// @class  FFormat
struct ULIS3_API FFormat
{
    ~FFormat();
    FFormat( tFormat iFMT );
    FFormat( const FFormat& iOther );
    FFormat( FFormat&& iOther );
    FFormat& operator=( const FFormat& iOther );

    uint8*      IDT; ///< Cached Index Table
    tFormat     FMT; ///< Cached Format
    eType       TP;  ///< Cached Type
    eColorModel CM;  ///< Cached Color Model
    uint8       BPC; ///< Cached Bytes Per Channel
    uint8       NCC; ///< Cached Num Color Channels
    uint8       HEA; ///< Cached Has Extra Alpha
    uint8       RSC; ///< Cached ReverseSwapped Code
    uint8       SPP; ///< Cached Samples Per Pixel
    uint8       BPP; ///< Cached Bytes Per Pixel
    uint8       AID; ///< Cached Alpha Index
    uint8       REV; ///< Cached Reversed
    uint8       SWA; ///< Cached Swapped
    uint8       PRE; ///< Cached Premultiplied
    uint8       LIN; ///< Cached Linear
    uint8       PRO; ///< Cached Default Profile Code
};

/////////////////////////////////////////////////////
/// @class  IHasFormat
class ULIS3_API IHasFormat
{
protected:
    ~IHasFormat()
    {}

    IHasFormat( tFormat iFormat )
        : mFormatInfo( iFormat )
    {}

public:
    ULIS3_FORCEINLINE const FFormat& FormatInfo() const { return  mFormatInfo; }
    ULIS3_FORCEINLINE const uint8* IndexTable() const { return  mFormatInfo.IDT; }
    ULIS3_FORCEINLINE tFormat Format() const { return  mFormatInfo.FMT; }
    ULIS3_FORCEINLINE eType Type() const { return  mFormatInfo.TP; }
    ULIS3_FORCEINLINE eColorModel Model() const { return  mFormatInfo.CM; }
    ULIS3_FORCEINLINE uint8 BytesPerSample() const { return  mFormatInfo.BPC; }
    ULIS3_FORCEINLINE uint8 NumColorChannels() const { return  mFormatInfo.NCC; }
    ULIS3_FORCEINLINE bool HasAlpha() const { return  mFormatInfo.HEA; }
    ULIS3_FORCEINLINE uint8 SamplesPerPixel() const { return  mFormatInfo.SPP; }
    ULIS3_FORCEINLINE uint8 BytesPerPixel() const { return  mFormatInfo.BPP; }
    ULIS3_FORCEINLINE uint8 AlphaIndex() const { return  mFormatInfo.AID; }
    ULIS3_FORCEINLINE bool Reversed() const { return  mFormatInfo.REV; }
    ULIS3_FORCEINLINE bool Swapped() const { return  mFormatInfo.SWA; }
    ULIS3_FORCEINLINE bool Premultiplied() const { return  mFormatInfo.PRE; }
    ULIS3_FORCEINLINE bool Linear() const { return  mFormatInfo.LIN; }
    ULIS3_FORCEINLINE uint8 DefaultProfileCode() const { return  mFormatInfo.PRO; }
    ULIS3_FORCEINLINE uint8 RedirectedIndex( uint8 iIndex ) const {
        ULIS3_ASSERT( iIndex >= 0 && iIndex < mFormatInfo.SPP, "Bad Index" );
        return  mFormatInfo.IDT[ iIndex ];
    }

protected:
    ULIS3_FORCEINLINE void ReinterpretFormat( tFormat iFormat ) {
        mFormatInfo = FFormat( iFormat );
    }

private:
    FFormat mFormatInfo; ///< The FormatInfo.
};

ULIS3_NAMESPACE_END

