// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         BlendMT_NonSeparable_CM_Lab_MEM_Generic.ipp
* @author       Clement Berthaud
* @brief        This file provides the declaration for the generic Blend entry point functions.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Base/Core.h"
#include "Blend/Func/BlendHelpers.ipp"
#include "Blend/Modes.h"
#include "Blend/Func/AlphaFuncF.ipp"
#include "Blend/Func/NonSeparableBlendFuncF.ipp"
#include "Color/ModelStructs.h"
#include "Maths/Geometry.h"
#include "Thread/ParallelFor.h"

ULIS2_NAMESPACE_BEGIN
template< typename T >
void
InvokeBlendMTProcessScanline_NonSeparable_CM_Lab_MEM_Generic_Subpixel( int32            iLINE
                                                                     , const tByte*     iSRC
                                                                     , tByte*           iBDP
                                                                     , uint8*           iXIDT
                                                                     , uint8            iBPC
                                                                     , uint8            iNCC
                                                                     , uint8            iHEA
                                                                     , uint8            iSPP
                                                                     , uint8            iBPP
                                                                     , uint8            iAID
                                                                     , tSize             iSRC_BPS
                                                                     , const FRect&     iSrcROI
                                                                     , const FRect&     iBdpROI
                                                                     , const glm::vec2& iSubpixelComponent
                                                                     , eBlendingMode    iBlendingMode
                                                                     , eAlphaMode       iAlphaMode
                                                                     , ufloat           iOpacity )
{
}

template< typename T >
void
BlendMT_NonSeparable_CM_Lab_MEM_Generic_Subpixel( FThreadPool*      iPool
                                                , bool              iBlocking
                                                , const FPerf&      iPerf
                                                , const FBlock*     iSource
                                                , FBlock*           iBackdrop
                                                , const FRect&      iSrcROI
                                                , const FRect&      iBdpROI
                                                , const glm::vec2&  iSubpixelComponent
                                                , eBlendingMode     iBlendingMode
                                                , eAlphaMode        iAlphaMode
                                                , ufloat            iOpacity )
{
    uint8* xidt;
    uint8 bpc, ncc, hea, spp, bpp, aid;
    tSize roi_w, roi_h, src_bps, bdp_bps, src_jmp, bdp_jmp;
    XBuildBlendParams( iBdpROI, iSource, iBackdrop, &bpc, &ncc, &hea, &spp, &bpp, &aid, &xidt, &roi_w, &roi_h, &src_bps, &bdp_bps, &src_jmp, &bdp_jmp );
    ParallelFor( *iPool
               , iBlocking
               , iPerf
               , iBdpROI.h
               , ULIS2_PF_CALL {
                    InvokeBlendMTProcessScanline_NonSeparable_CM_Lab_MEM_Generic_Subpixel< T >( iLine
                                                                                              , iSource->DataPtr()   + ( ( iSrcROI.y + iLine ) * src_bps ) + ( iSrcROI.x * bpp )
                                                                                              , iBackdrop->DataPtr() + ( ( iBdpROI.y + iLine ) * bdp_bps ) + ( iBdpROI.x * bpp )
                                                                                              , xidt, bpc, ncc, hea, spp, bpp, aid, src_bps, iSrcROI, iBdpROI
                                                                                              , iSubpixelComponent, iBlendingMode, iAlphaMode, iOpacity );
               } );
    delete [] xidt;
}

template< typename T >
void
InvokeBlendMTProcessScanline_NonSeparable_CM_Lab_MEM_Generic( int32             iLINE
                                                            , const tByte*      iSRC
                                                            , tByte*            iBDP
                                                            , uint8*            iXIDT
                                                            , uint8             iBPC
                                                            , uint8             iNCC
                                                            , uint8             iHEA
                                                            , uint8             iSPP
                                                            , uint8             iBPP
                                                            , uint8             iAID
                                                            , tSize             iSRC_BPS
                                                            , const FRect&      iSrcROI
                                                            , const FRect&      iBdpROI
                                                            , const glm::vec2&  iSubpixelComponent
                                                            , eBlendingMode     iBlendingMode
                                                            , eAlphaMode        iAlphaMode
                                                            , ufloat            iOpacity )
{
}

template< typename T >
void
BlendMT_NonSeparable_CM_Lab_MEM_Generic( FThreadPool*       iPool
                                       , bool               iBlocking
                                       , const FPerf&       iPerf
                                       , const FBlock*      iSource
                                       , FBlock*            iBackdrop
                                       , const FRect&       iSrcROI
                                       , const FRect&       iBdpROI
                                       , const glm::vec2&   iSubpixelComponent
                                       , eBlendingMode      iBlendingMode
                                       , eAlphaMode         iAlphaMode
                                       , ufloat             iOpacity )
{
    uint8* xidt;
    uint8 bpc, ncc, hea, spp, bpp, aid;
    tSize roi_w, roi_h, src_bps, bdp_bps, src_jmp, bdp_jmp;
    XBuildBlendParams( iBdpROI, iSource, iBackdrop, &bpc, &ncc, &hea, &spp, &bpp, &aid, &xidt, &roi_w, &roi_h, &src_bps, &bdp_bps, &src_jmp, &bdp_jmp );
    ParallelFor( *iPool
               , iBlocking
               , iPerf
               , iBdpROI.h
               , ULIS2_PF_CALL {
                    InvokeBlendMTProcessScanline_NonSeparable_CM_Lab_MEM_Generic< T >( iLine
                                                                                     , iSource->DataPtr()   + ( ( iSrcROI.y + iLine ) * src_bps ) + ( iSrcROI.x * bpp )
                                                                                     , iBackdrop->DataPtr() + ( ( iBdpROI.y + iLine ) * bdp_bps ) + ( iBdpROI.x * bpp )
                                                                                     , xidt, bpc, ncc, hea, spp, bpp, aid, src_bps, iSrcROI, iBdpROI
                                                                                     , iSubpixelComponent, iBlendingMode, iAlphaMode, iOpacity );
               } );
    delete [] xidt;
}

ULIS2_NAMESPACE_END

