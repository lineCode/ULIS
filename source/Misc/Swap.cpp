// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Swap.cpp
* @author       Clement Berthaud
* @brief        This file provides the definitions for the Swap entry point functions.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include "Misc/Swap.h"
#include "Base/Perf.h"
#include "Data/Block.h"
#include "Maths/Geometry.h"
#include "Thread/ParallelFor.h"
#include "Thread/ThreadPool.h"

ULIS2_NAMESPACE_BEGIN
void
InvokeSwapMTProcessScanline_MEM( tByte* iDst, tSize iCount, uint8 iC1, uint8 iC2, tSize iBPC, tSize iBPP )
{
    tByte* dst = iDst;
    tByte* tmp = new tByte[iBPC];
    for( uint32 i = 0; i < iCount; ++i )
    {
        memcpy( tmp, dst + iC1, iBPC );
        memcpy( dst + iC1, dst + iC2, iBPC );
        memcpy( dst + iC2, tmp, iBPC );
        dst += iBPP;
    }
    delete [] tmp;
}

void
Swap( FThreadPool*  iPool
    , bool          iBlocking
    , const FPerf&  iPerf
    , const FCPU&   iCPU
    , FBlock*       iDst
    , uint8         iC1
    , uint8         iC2
    , bool          iCallInvalidCB )
{
    ULIS2_ASSERT( iPool,                                    "Bad pool" );
    ULIS2_ASSERT( iDst,                                     "Bad destination" );
    ULIS2_ASSERT( iC1 < iDst->SamplesPerPixel(),            "Bad channel" );
    ULIS2_ASSERT( iC2 < iDst->SamplesPerPixel(),            "Bad channel" );
    ULIS2_ASSERT( !( (!iBlocking) && (iCallInvalidCB ) ),   "Calling invalid CB on non-blocking operation may induce race condition and undefined behaviours." );
    if( iC1 == iC2 )
        return;

    const tSize bpc = iDst->BytesPerSample();
    const tSize spp = iDst->SamplesPerPixel();
    const tSize bpp = iDst->BytesPerPixel();
    const tSize w   = iDst->Width();
    const tSize bps = iDst->BytesPerScanLine();
    tByte*      dsb = iDst->DataPtr();
    #define DST dsb + ( pLINE * bps )
    ULIS2_MACRO_INLINE_PARALLEL_FOR( iPerf, iPool, iBlocking, iDst->Height(), InvokeSwapMTProcessScanline_MEM, DST, w, iC1, iC2, bpc, bpp )
    iDst->Invalidate( iCallInvalidCB );
}

ULIS2_NAMESPACE_END

