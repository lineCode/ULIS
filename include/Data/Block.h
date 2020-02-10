// Copyright � 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Block.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the FBlock class.
* @copyright    Copyright � 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Base/Core.h"
#include "Data/FormatInfo.h"
#include "Data/Pixel.h"
#include "Base/Callbacks.h"

ULIS2_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
/// @class      FBlock
/// @brief      The FBlock class provides a mean of storing and manipulating digital images in various formats.
/// @details    The block format, type, layout, and other informations can be retrieved with dedicated functions.
/// @details    FBlock differs from FTexture because FBlock only lives on host CPU memory.
class ULIS2_API FBlock
{
public:
    // Construction / Destruction
    ~FBlock();

    FBlock( tSize iWidth
          , tSize iHeight
          , tFormat iFormat
          , FColorProfile* iProfile = nullptr
          , const FOnInvalid& iOnInvalid = FOnInvalid()
          , const FOnCleanup& iOnCleanup = FOnCleanup( &OnCleanup_FreeMemory ) );

    FBlock( tByte* iData
          , tSize iWidth
          , tSize iHeight
          , tFormat iFormat
          , FColorProfile* iProfile = nullptr
          , const FOnInvalid& iOnInvalid = FOnInvalid()
          , const FOnCleanup& iOnCleanup = FOnCleanup( &OnCleanup_DoNothing ) );

public:
    // Public API
    tByte*                  DataPtr();
    tByte*                  PixelPtr( int iX, int iY );
    tByte*                  ScanlinePtr( int iRow );
    void                    AssignProfile( FColorProfile* iProfile );
    const tByte*            DataPtr()                                           const;
    const tByte*            PixelPtr( int iX, int iY )                          const;
    const tByte*            ScanlinePtr( int iRow )                             const;
    tSize                   Width()                                             const;
    tSize                   Height()                                            const;
    tSize                   BytesPerSample()                                    const;
    tSize                   BytesPerPixel()                                     const;
    tSize                   BytesPerScanLine()                                  const;
    tSize                   BytesTotal()                                        const;
    tFormat                 Format()                                            const;
    eColorModel             Model()                                             const;
    eType                   Type()                                              const;
    bool                    HasAlpha()                                          const;
    bool                    Swapped()                                           const;
    bool                    Reversed()                                          const;
    uint8                   SamplesPerPixel()                                   const;
    uint8                   NumColorChannels()                                  const;
    FColorProfile*          Profile()                                           const;
    uint8                   RedirectedIndex( uint8 iIndex )                     const;
    uint8                   AlphaIndex()                                        const;
    void                    Invalidate( bool iCall = true )                     const;
    void                    Invalidate( const FRect& iRect, bool iCall = true ) const;
    FRect                   Rect()                                              const;
    FPixelValue             PixelValue( int iX, int iY )                        const;
    FPixelProxy             PixelProxy( int iX, int iY );
    const FPixelProxy       PixelProxy( int iX, int iY )                        const;
    uint32                  CRC32()                                             const;
    std::string             MD5()                                               const;
    std::string             UUID()                                              const;
    uint8*                  IndexTable()                                        const;
    const FFormatInfo&      FormatInfo()                                        const;
    void                    TweakFormat( tFormat iFormat );

private:
    // Private Data Members
    tByte*          mData;
    tSize           mWidth;
    tSize           mHeight;
    FOnInvalid      mOnInvalid;
    FOnCleanup      mOnCleanup;
    FColorProfile*  mProfile;
    std::string     mUUID;
    FFormatInfo     mInfo;
    tSize           mBPS;
    tSize           mBTT;
};

ULIS2_NAMESPACE_END

