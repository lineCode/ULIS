// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS3
*__________________
*
* @file         FormatInfo.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the FormatInfo utilities.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"

ULIS3_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
/// @class  FFormatInfo
struct ULIS3_API FFormatInfo
{
    ~FFormatInfo();
    FFormatInfo( tFormat iFMT );
    FFormatInfo( const FFormatInfo& iOther );
    FFormatInfo( FFormatInfo&& iOther );
    FFormatInfo& operator=( const FFormatInfo& iOther );

    uint8*      IDT; ///< Index Table
    tFormat     FMT; ///< Format
    eType       TP;  ///< Type
    eColorModel CM;  ///< Color Model
    uint8       BPC; ///< Bytes Per Channel
    uint8       NCC; ///< Num Color Channels
    uint8       HEA; ///< Has Extra Alpha
    uint8       RSC; ///< ReverseSwapped Code
    uint8       SPP; ///< Samples Per Pixel
    uint8       BPP; ///< Bytes Per Pixel
    uint8       AID; ///< Alpha Index
    uint8       REV; ///< Reversed
    uint8       SWA; ///< Swapped
    uint8       PRE; ///< Premultiplied
    uint8       LIN; ///< Linear
    uint8       PRO; ///< Default Profile Code
};

/////////////////////////////////////////////////////
/// @class  FHasFormat
class ULIS3_API FHasFormat
{
public:
    virtual ~FHasFormat() {}

    FHasFormat( tFormat iFormat )
        : mFormatInfo( iFormat )
    {}

    ULIS3_FORCEINLINE const FFormatInfo&    FormatInfo()                    const { return  mFormatInfo; }
    ULIS3_FORCEINLINE const uint8*          IndexTable()                    const { return  mFormatInfo.IDT; }
    ULIS3_FORCEINLINE tFormat               Format()                        const { return  mFormatInfo.FMT; }
    ULIS3_FORCEINLINE eType                 Type()                          const { return  mFormatInfo.TP; }
    ULIS3_FORCEINLINE eColorModel           Model()                         const { return  mFormatInfo.CM; }
    ULIS3_FORCEINLINE uint8                 BytesPerSample()                const { return  mFormatInfo.BPC; }
    ULIS3_FORCEINLINE uint8                 NumColorChannels()              const { return  mFormatInfo.NCC; }
    ULIS3_FORCEINLINE bool                  HasAlpha()                      const { return  mFormatInfo.HEA; }
    ULIS3_FORCEINLINE uint8                 SamplesPerPixel()               const { return  mFormatInfo.SPP; }
    ULIS3_FORCEINLINE uint8                 BytesPerPixel()                 const { return  mFormatInfo.BPP; }
    ULIS3_FORCEINLINE uint8                 AlphaIndex()                    const { return  mFormatInfo.AID; }
    ULIS3_FORCEINLINE bool                  Reversed()                      const { return  mFormatInfo.REV; }
    ULIS3_FORCEINLINE bool                  Swapped()                       const { return  mFormatInfo.SWA; }
    ULIS3_FORCEINLINE bool                  Premultiplied()                 const { return  mFormatInfo.PRE; }
    ULIS3_FORCEINLINE bool                  Linear()                        const { return  mFormatInfo.LIN; }
    ULIS3_FORCEINLINE uint8                 DefaultProfileCode()            const { return  mFormatInfo.PRO; }
    ULIS3_FORCEINLINE uint8                 RedirectedIndex( uint8 iIndex ) const {
        ULIS3_ASSERT( iIndex >= 0 && iIndex < mFormatInfo.SPP, "Bad Index" );
        return  mFormatInfo.IDT[ iIndex ];
    }

private:
    FFormatInfo mFormatInfo;
};

ULIS3_NAMESPACE_END

