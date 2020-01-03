// Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Pixel.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the FPixel class.
* @copyright    Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core.h"
#include "ColorProfile.h"

ULIS2_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
/// @class      FPixel
/// @brief      The FPixel class provides a mean of storing and manipulating pixels in various formats.
/// @details    The pixel format, type, layout, and other informations can be retrieved in the pixel format member.
class ULIS2_API FPixel
{
public:
    // Construction / Destruction
    virtual ~FPixel();
    FPixel( uint32 iFormat );
    FPixel( tByte* iData, tFormat iFormat );

public:
    // Public API
    tByte*              Ptr();
    const tByte*        Ptr()                           const;
    tSize               BytesPerSample()                const;
    tSize               Depth()                         const;
    tFormat             Format()                        const;
    eModelSig           Model()                         const;
    eType               Type()                          const;
    bool                HasAlpha()                      const;
    bool                Swapped()                       const;
    bool                Reversed()                      const;
    uint8               SamplesPerPixel()               const;
    uint8               NumColorChannels()              const;

private:
    // Private Data Members
    tByte*          mData;
    tFormat         mFormat;
};

ULIS2_NAMESPACE_END

