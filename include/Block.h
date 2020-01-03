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

ULIS2_NAMESPACE_BEGIN

extern FOnCleanup OnCleanup_FreeMemory;
extern FOnCleanup OnCleanup_DoNothing;

/////////////////////////////////////////////////////
/// @class      FBlock
/// @brief      The FBlock class provides a mean of storing and manipulating digital images in various formats.
/// @details    The block format, type, layout, and other informations can be retrieved in the block format member.
class FBlock
{
public:
    // Construction / Destruction
    virtual ~FBlock();
    FBlock( tSize iWidth, tSize iHeight, tFormat iFormat, const FOnInvalid& = FOnInvalid(), const FOnCleanup& = FOnCleanup() );
    FBlock( tByte* iData, tSize iWidth, tSize iHeight, tFormat iFormat, const FOnInvalid& = FOnInvalid(), const FOnCleanup& = FOnCleanup() );

public:
    // Public API
    tByte*              DataPtr();
    const tByte*        DataPtr()                       const;
    tByte*              PixelPtr( int iX, int iY );
    const tByte*        PixelPtr( int iX, int iY )      const;
    tByte*              ScanlinePtr( int iRow );
    const tByte*        ScanlinePtr( int iRow )         const;
    tSize               Width()                         const;
    tSize               Height()                        const;
    tSize               BytesPerSample()                const;
    tSize               BytesPerPixel()                 const;
    tSize               BytesPerScanLine()              const;
    tSize               BytesTotal()                    const;
    tFormat             Format()                        const;
    eModel              Model()                         const;
    eType               Type()                          const;
    bool                HasAlpha()                      const;
    bool                Swapped()                       const;
    bool                Reversed()                      const;
    uint8               SamplesPerPixel()               const;
    uint8               NumColorChannels()              const;

private:
    // Private Data Members
    tByte*      mData;
    tSize       mWidth;
    tSize       mHeight;
    tFormat     mFormat;
    FOnInvalid  mOnInvalid;
    FOnCleanup  mOnCleanup;
};

ULIS2_NAMESPACE_END

