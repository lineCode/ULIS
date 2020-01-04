// Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Block.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the FBlock class.
* @copyright    Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core.h"

ULIS2_FDECL_CLASS( FColorProfile );

ULIS2_NAMESPACE_BEGIN
ULIS2_API extern const FOnCleanup OnCleanup_FreeMemory;
ULIS2_API extern const FOnCleanup OnCleanup_DoNothing;

/////////////////////////////////////////////////////
/// @class      FBlock
/// @brief      The FBlock class provides a mean of storing and manipulating digital images in various formats.
/// @details    The block format, type, layout, and other informations can be retrieved in the block format member.
class ULIS2_API FBlock
{
public:
    // Construction / Destruction
    virtual ~FBlock();
    FBlock( tSize iWidth, tSize iHeight, tFormat iFormat, const FOnInvalid& = FOnInvalid(), const FOnCleanup& = FOnCleanup() );
    FBlock( tSize iWidth, tSize iHeight, tFormat iFormat, FColorProfile* iProfile = nullptr, const FOnInvalid& = FOnInvalid(), const FOnCleanup& = FOnCleanup() );
    FBlock( tByte* iData, tSize iWidth, tSize iHeight, tFormat iFormat, const FOnInvalid& = FOnInvalid(), const FOnCleanup& = FOnCleanup() );
    FBlock( tByte* iData, tSize iWidth, tSize iHeight, tFormat iFormat, FColorProfile* iProfile = nullptr, const FOnInvalid& = FOnInvalid(), const FOnCleanup& = FOnCleanup() );

public:
    // Public API
    tByte*                  DataPtr();
    const tByte*            DataPtr()                           const;
    tByte*                  PixelPtr( tIndex iX, tIndex iY );
    const tByte*            PixelPtr( tIndex iX, tIndex iY )    const;
    tByte*                  ScanlinePtr( tIndex iRow );
    const tByte*            ScanlinePtr( tIndex iRow )          const;
    tSize                   Width()                             const;
    tSize                   Height()                            const;
    tSize                   BytesPerSample()                    const;
    tSize                   BytesPerPixel()                     const;
    tSize                   BytesPerScanLine()                  const;
    tSize                   BytesTotal()                        const;
    tFormat                 Format()                            const;
    eModelSig               Model()                             const;
    eType                   Type()                              const;
    bool                    HasAlpha()                          const;
    bool                    Swapped()                           const;
    bool                    Reversed()                          const;
    uint8                   SamplesPerPixel()                   const;
    uint8                   NumColorChannels()                  const;
    const FColorProfile&    Profile()                           const;

private:
    // Private Data Members
    tByte*          mData;
    tSize           mWidth;
    tSize           mHeight;
    tFormat         mFormat;
    FOnInvalid      mOnInvalid;
    FOnCleanup      mOnCleanup;
    FColorProfile*  mProfile;
};

ULIS2_NAMESPACE_END

