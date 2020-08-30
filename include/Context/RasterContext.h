// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS
*__________________
*
* @file         FRasterContext.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the FRasterContext class.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"
#include "Blend/Modes.h"
#include "Math/Geometry/Rectangle.h"
#include "Math/Geometry/Vector.h"
#include "Scheduling/SchedulePolicy.h"
#include "Scheduling/TaskEvent.h"

ULIS_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
/// @class      FRasterContext
/// @brief      The FRasterContext class provides a monolithic context for
///             calling image raster and composition functions for a given format.
/// @details    The FRasterContext works on FBlock and is bound to a
///             specific format. It prefetches the dispatched implementation to
///             select the fastest method according to the format, and its
///             specializations if available, and according to the current runtime
///             device and its support for SIMD features or thread support.
///
///             There can be multiple FRasterContext object instances for
///             different formats, each sharing the same FDevice. Keep in mind
///             this object is rather heavy as it caches the pre-dispatched
///             paths to the specific implementations of each feature it exposes.
///
///             FRasterContext can be expected to reach a size in the Ko
///             magnitude, and there is a significant overhead during
///             instanciation at runtime. But once created, the gain is
///             significant as the path to the implementation has been cached
///             once and for all. The only exception is for the Conversion
///             functions, which are not cached as it would bloat the memory due
///             to the many possible combinations of source and targets ( 1M+ ).
///
///             \sa FBlock
///             \sa FThreadPool
///             \sa FDevice
///             \sa FCommandQueue
class ULIS_API FRasterContext
{
private:
    struct FContextualDispatchTable;

public:
    /*! Destructor */
    ~FRasterContext();

    /*! Constructor */
    FRasterContext( const FDevice& iDevice, eFormat iFormat );

public:
/////////////////////////////////////////////////////
// Blend
    /*!
        Perform a blend operation with iSource composited on top of iBackdrop.
        iBackdrop is modified to receive the result of the operation, while
        iSource is left untouched.

        You can specify a sub-portion of the iSource image by specifying the
        iSourceRect to the desired part of the picture. If you want to blend the
        whole image, use the FBlock::Rect() method on the iSource block.
        You can also specify where in iBackdrop the iSource FBlock should be
        composited, in integer coordinates.

        If the iSourceRect and/or iPosition lead to a destination geometry that
        does not intersect the rectangular geometry of iBackdrop, the call will
        not perform any computation and will return safely, so it is safe to
        specify out-of-bounds positions.

        \sa BlendAA()
    */
    const FTaskEvent&
    Blend(
          const FBlock& iSource
        , FBlock& iBackdrop
        , const FRectI& iSourceRect = FRectI( 0, 0, INT_MAX, INT_MAX )
        , const FVec2I& iPosition = FVec2I( 0, 0 )
        , eBlendMode iBlendingMode = BM_NORMAL
        , eAlphaMode iAlphaMode = AM_NORMAL
        , ufloat iOpacity = 1.0f
        , const FSchedulePolicy& iPolicy = FSchedulePolicy()
        , const FTaskEvent& iWait = FTaskEvent()
    );

    /*!
        Perform an antialiased blend operation with iSource composited on top of
        iBackdrop. iBackdrop is modified to receive the result of the operation,
        while iSource is left untouched.

        An antialiasing blend accepts floating point coordinates and performs
        antialiasing at the same time as it performs the compositing, this is
        useful for drawing, sometimes also referred to as subpixel blending.

        You can specify a sub-portion of the iSource image by specifying the
        iSourceRect to the desired part of the picture. If you want to blend the
        whole image, use the FBlock::Rect() method on the iSource block.
        You can also specify where in iBackdrop the iSource FBlock should be
        composited, in floating point coordinates.

        If the iSourceRect and/or iPosition lead to a destination geometry that
        does not intersect the rectangular geometry of iBackdrop, the call will
        not perform any computation and will return safely, so it is safe to
        specify out-of-bounds positions.

        \sa Blend()
    */
    const FTaskEvent&
    BlendAA(
          const FBlock& iSource
        , FBlock& iBackdrop
        , const FRectI& iSourceRect = FRectI( 0, 0, INT_MAX, INT_MAX )
        , const FVec2F& iPosition = FVec2F( 0.f, 0.f )
        , eBlendMode iBlendingMode = BM_NORMAL
        , eAlphaMode iAlphaMode = AM_NORMAL
        , ufloat iOpacity = 1.0f
        , const FSchedulePolicy& iPolicy = FSchedulePolicy()
        , const FTaskEvent& iWait = FTaskEvent()
    );

private:
    FContextualDispatchTable* mContextualDispatchTable;
    const FDevice& mDevice;
    eFormat mFormat;
};

ULIS_NAMESPACE_END

