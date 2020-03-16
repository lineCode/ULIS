// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         TiledBlock.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the FTiledBlock class.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"
#include "Data/Block.h"
#include "Maths/Geometry.h"

ULIS2_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
/// FTile
class ULIS2_API FTile {
public:
    // Construction / Destruction
    virtual ~FTile();

    FTile( int iSize
         , tFormat iFormat
         , FColorProfile* iProfile = nullptr );
};

/////////////////////////////////////////////////////
/// FTiledBlock
class ULIS2_API FTiledBlock
{
public:
    // Construction / Destruction
    virtual ~FTiledBlock();
    FTiledBlock( int iWidth
               , int iHeight
               , tFormat iFormat
               , FColorProfile* iProfile = nullptr );

public:
    // Public API
    tByte*                  PixelPtr( int iX, int iY );
    void                    AssignProfile( FColorProfile* iProfile );
    const tByte*            PixelPtr( int iX, int iY )                          const;
    tSize                   Width()                                             const;
    tSize                   Height()                                            const;
    tSize                   BytesPerSample()                                    const;
    tSize                   BytesPerPixel()                                     const;
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
    std::string             UUID()                                              const;
    uint8*                  IndexTable()                                        const;
    const FFormatInfo&      FormatInfo()                                        const;

private:
    // Private Data Members
    FVec2F          mPos;
    FVec2I          mSize;
    FColorProfile*  mProfile;
    std::string     mUUID;
    FFormatInfo     mInfo;
};

ULIS2_NAMESPACE_END

