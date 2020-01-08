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
void OnCleanup_FreeMemory( tByte* iData, void* iInfo );
void OnCleanup_DoNothing( tByte* iData, void* iInfo );

/////////////////////////////////////////////////////
/// @class      FBlock
/// @brief      The FBlock class provides a mean of storing and manipulating digital images in various formats.
/// @details    The block format, type, layout, and other informations can be retrieved in the block format member.
class ULIS2_API FBlock
{
public:
    // Construction / Destruction
    virtual ~FBlock();
    FBlock( tSize iWidth, tSize iHeight, tFormat iFormat, const FOnInvalid& = FOnInvalid(), const FOnCleanup& = FOnCleanup( &OnCleanup_FreeMemory ) );
    FBlock( tSize iWidth, tSize iHeight, tFormat iFormat, FColorProfile* iProfile = nullptr, const FOnInvalid& = FOnInvalid(), const FOnCleanup& = FOnCleanup( &OnCleanup_FreeMemory ) );
    FBlock( tByte* iData, tSize iWidth, tSize iHeight, tFormat iFormat, const FOnInvalid& = FOnInvalid(), const FOnCleanup& = FOnCleanup( &OnCleanup_DoNothing ) );
    FBlock( tByte* iData, tSize iWidth, tSize iHeight, tFormat iFormat, FColorProfile* iProfile = nullptr, const FOnInvalid& = FOnInvalid(), const FOnCleanup& = FOnCleanup( &OnCleanup_DoNothing ) );

public:
    // Public API
    tByte*                  DataPtr();
    const tByte*            DataPtr()                                   const;
    tByte*                  PixelPtr( tIndex iX, tIndex iY );
    const tByte*            PixelPtr( tIndex iX, tIndex iY )            const;
    tByte*                  ScanlinePtr( tIndex iRow );
    const tByte*            ScanlinePtr( tIndex iRow )                  const;
    tSize                   Width()                                     const;
    tSize                   Height()                                    const;
    tSize                   BytesPerSample()                            const;
    tSize                   BytesPerPixel()                             const;
    tSize                   BytesPerScanLine()                          const;
    tSize                   BytesTotal()                                const;
    tFormat                 Format()                                    const;
    eModelSig               Model()                                     const;
    eType                   Type()                                      const;
    bool                    HasAlpha()                                  const;
    bool                    Swapped()                                   const;
    bool                    Reversed()                                  const;
    uint8                   SamplesPerPixel()                           const;
    uint8                   NumColorChannels()                          const;
    const FColorProfile&    Profile()                                   const;
    void                    AssignProfile( FColorProfile* iProfile );
    void                    Invalidate()                                const;
    void                    Invalidate( const FRect& iRect )            const;

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
