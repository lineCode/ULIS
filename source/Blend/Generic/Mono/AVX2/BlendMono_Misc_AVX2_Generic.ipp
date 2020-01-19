// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         BlendMono_Misc_AVX2_Generic.ipp
* @author       Clement Berthaud
* @brief        This file provides the declaration for the generic Blend entry point functions.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Base/Core.h"
#include "Blend/BlendHelpers.h"
#include "Blend/BlendingPRNGSeed.h"
#include "Blend/Modes.h"
#include "Blend/Func/AlphaFuncF.ipp"
#include "Color/ModelStructs.h"
#include "Maths/Geometry.h"

ULIS2_NAMESPACE_BEGIN
template< typename T >
void BlendMono_Misc_AVX2( const FBlock*          iSource
                        , FBlock*                iBackdrop
                        , const FRect&           iSrcRoi
                        , const FRect&           iDstRoi
                        , const eBlendingMode    iBlendingMode
                        , const eAlphaMode       iAlphaMode
                        , const float            iOpacity )
{
    // There is only one Misc mode ATM: Dissolve, hence this function processes for dissolve only.

    uint8 bpc, ncc, hea, spp, bpp, aid;
    tSize bps, num;
    uint8* idt;
    BuildBlendParams( &bpc, &ncc, &hea, &spp, &bpp, &bps, &num, &aid, &idt, iSource->Format(), iSrcRoi );
    const tByte* src = iSource->DataPtr()   + ( iSrcRoi.y * bps ) + ( iSrcRoi.x * bpp );
    tByte*       bdp = iBackdrop->DataPtr() + ( iDstRoi.y * bps ) + ( iDstRoi.x * bpp );

    uint32 localPRNGSeed = gBlendingPRNGSeed;
    for( tSize i = 0; i < num; ++i ) {
        // Random toss, pseudo random can be improved.
        const float alpha_bdp       = hea ? TYPE2FLOAT( bdp, aid ) : 1.f;
        const float alpha_src       = hea ? TYPE2FLOAT( src, aid ) * iOpacity : iOpacity;

        localPRNGSeed = 8253729 * localPRNGSeed + 2396403;
        float toss = ( localPRNGSeed % 65537 ) / 65537.f;

        if( toss < alpha_src ) {
            float alpha_result;
            switch( iAlphaMode ) {
                case AM_NORMAL  : alpha_result = AlphaNormalF(  1.f, alpha_bdp );
                case AM_ERASE   : alpha_result = AlphaEraseF(   1.f, alpha_bdp );
                case AM_TOP     : alpha_result = AlphaTopF(     1.f, alpha_bdp );
                case AM_BACK    : alpha_result = AlphaBackF(    1.f, alpha_bdp );
                case AM_SUB     : alpha_result = AlphaSubF(     1.f, alpha_bdp );
                case AM_ADD     : alpha_result = AlphaAddF(     1.f, alpha_bdp );
                case AM_MUL     : alpha_result = AlphaMulF(     1.f, alpha_bdp );
                case AM_MIN     : alpha_result = AlphaMinF(     1.f, alpha_bdp );
                case AM_MAX     : alpha_result = AlphaMaxF(     1.f, alpha_bdp );
                case AM_INVMAX  : alpha_result = AlphaInvMaxF(  1.f, alpha_bdp );
            }
            memcpy( bdp, src, bpp );
            if( hea ) FLOAT2TYPE( bdp, aid, alpha_result );
        }

        // Increment ptrs by one pixel
        src += bpp;
        bdp += bpp;
    }

    delete [] idt;
}

ULIS2_NAMESPACE_END

