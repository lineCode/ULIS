// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Mix.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the Conv entry point functions.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Base/Core.h"
#include "Conv/Conv.h"
#include "Data/Pixel.h"
#include "Maths/Maths.h"
#include "Color/srgb2linear.h"

ULIS2_NAMESPACE_BEGIN
FPixelValue
MixNative( ufloat iT, IPixel* iA, IPixel* iB )
{
    ULIS2_ASSERT( iA, "Bad input A" );
    ULIS2_ASSERT( iB, "Bad input B" );
    ufloat t = FMaths::Clamp( iT, 0.f, 1.f );
    FPixelValue native_ret( iA->Format() );
    FPixelValue native_B( iA->Format() );
    Conv( *iB, native_B );
    const uint8 spp = iA->NumSamples();
    for( uint8 i = 0; i < spp; ++i )
        native_ret.SetValue< ufloat >( i, ( 1.f - t ) * iA->GetValue< ufloat >( i ) + t * iB->GetValue< ufloat >( i ) );
    return  native_ret;
}


FPixelValue
MixLinearRGB( ufloat iT, IPixel* iA, IPixel* iB )
{
    ULIS2_ASSERT( iA, "Bad input A" );
    ULIS2_ASSERT( iB, "Bad input B" );
    ufloat t = FMaths::Clamp( iT, 0.f, 1.f );
    FPixelValue rgbA( ULIS2_FORMAT_RGBAF );
    FPixelValue rgbB( ULIS2_FORMAT_RGBAF );
    FPixelValue rgbResult( ULIS2_FORMAT_RGBAF );
    Conv( *iA, rgbA );
    Conv( *iB, rgbB );
    rgbResult.SetRF( srgb2linear( ( 1.f - t ) * rgbA.RF() + t * rgbB.RF() ) );
    rgbResult.SetGF( srgb2linear( ( 1.f - t ) * rgbA.GF() + t * rgbB.GF() ) );
    rgbResult.SetBF( srgb2linear( ( 1.f - t ) * rgbA.BF() + t * rgbB.BF() ) );
    rgbResult.SetAF( srgb2linear( ( 1.f - t ) * rgbA.AF() + t * rgbB.AF() ) );
    return  rgbResult;
}


FPixelValue
MixRGB( ufloat iT, IPixel* iA, IPixel* iB )
{
    ULIS2_ASSERT( iA, "Bad input A" );
    ULIS2_ASSERT( iB, "Bad input B" );
    ufloat t = FMaths::Clamp( iT, 0.f, 1.f );
    FPixelValue rgbA( ULIS2_FORMAT_RGBAF );
    FPixelValue rgbB( ULIS2_FORMAT_RGBAF );
    FPixelValue rgbResult( ULIS2_FORMAT_RGBAF );
    Conv( *iA, rgbA );
    Conv( *iB, rgbB );
    rgbResult.SetRF( ( 1.f - t ) * rgbA.RF() + t * rgbB.RF() );
    rgbResult.SetGF( ( 1.f - t ) * rgbA.GF() + t * rgbB.GF() );
    rgbResult.SetBF( ( 1.f - t ) * rgbA.BF() + t * rgbB.BF() );
    rgbResult.SetAF( ( 1.f - t ) * rgbA.AF() + t * rgbB.AF() );
    return  rgbResult;
}


FPixelValue
MixLab( ufloat iT, IPixel* iA, IPixel* iB )
{
    ULIS2_ASSERT( iA, "Bad input A" );
    ULIS2_ASSERT( iB, "Bad input B" );
    ufloat t = FMaths::Clamp( iT, 0.f, 1.f );
    FPixelValue LabA( ULIS2_FORMAT_LabAD );
    FPixelValue LabB( ULIS2_FORMAT_LabAD );
    FPixelValue LabResult( ULIS2_FORMAT_LabAD );
    Conv( *iA, LabA );
    Conv( *iB, LabB );
    LabResult.SetLD( ( 1.f - t ) * LabA.LD() + t * LabB.LD() );
    LabResult.SetaD( ( 1.f - t ) * LabA.aD() + t * LabB.aD() );
    LabResult.SetbD( ( 1.f - t ) * LabA.bD() + t * LabB.bD() );
    LabResult.SetAD( ( 1.f - t ) * LabA.AD() + t * LabB.AD() );
    return  LabResult;
}

ULIS2_NAMESPACE_END

