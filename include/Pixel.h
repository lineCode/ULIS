// Copyright � 2018-2019 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Pixel.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the FPixel class.
* @copyright    Copyright � 2018-2019 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core.h"

ULIS2_FDECL_CLASS( FColorProfile );

ULIS2_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
/// @class      FPixel
/// @brief      The FPixel class provides a mean of storing and manipulating pixels in various formats.
/// @details    The pixel format, type, layout, and other informations can be retrieved in the pixel format member.
class ULIS2_API FPixel
{
public:
    // Construction / Destruction
    virtual ~FPixel() = 0;
    FPixel( uint32 iFormat );
    FPixel( uint32 iFormat, FColorProfile* iProfile = nullptr );
    FPixel( tByte* iData, tFormat iFormat );
    FPixel( tByte* iData, tFormat iFormat, FColorProfile* iProfile = nullptr );

public:
    // Public API
    tByte*                  Ptr();
    const tByte*            Ptr()                                       const;
    tSize                   BytesPerSample()                            const;
    tSize                   Depth()                                     const;
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

protected:
    // Protected Data Members
    tByte*          mData;
    tFormat         mFormat;
    FColorProfile*  mProfile;
};

ULIS2_NAMESPACE_END

