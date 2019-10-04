/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.FX.Noise.ValueNoise.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/
#pragma once
#include "ULIS/Base/ULIS.Base.BaseTypes.h"
#include "ULIS/Base/ULIS.Base.PerformanceOptions.h"
#include "ULIS/Data/ULIS.Data.Block.h"
#include "ULIS/Global/ULIS.Global.GlobalThreadPool.h"
#include "ULIS/FX/Noise/ULIS.FX.Noise.NoiseUtils.h"

namespace ULIS {
/////////////////////////////////////////////////////
// TBrownianNoiseGenerator_Default_ScanLine
template< uint32 _SH >
class TBrownianNoiseGenerator_Default_ScanLine
{
public:
    static void ProcessScanLine( TBlock< _SH >*     iBlock
                               , const int          iLine
                               , const int          iX1
                               , const int          iX2
                               , const float        iFrequency
                               , float              iFrequencyMult
                               , float              iAmplitudeMult
                               , uint8              iNumLayers
                               , float              iAmplitudeMax
                               , const ValueNoise&  iGen )
    {
        using tPixelProxy = typename TBlock< _SH >::tPixelProxy;
        using info = TBlockInfo< _SH >;

        for( int x = iX1; x < iX2; ++x )
        {
            tPixelProxy proxy = iBlock->PixelProxy( x, iLine );
            Vec2f pointNoise = Vec2f( x, iLine ) * iFrequency;
            float amplitude = 1.f;
            float floatvalue = 0;

            for( int i = 0; i < iNumLayers; ++i )
            {
                floatvalue  += iGen.eval( pointNoise ) * amplitude;
                pointNoise  *= iFrequencyMult;
                amplitude   *= iAmplitudeMult;
            }

            floatvalue /= iAmplitudeMax;
            tPixelProxy::tPixelType value = ConvType< float, typename tPixelProxy::tPixelType >( floatvalue );

            for( int i = 0; i < info::_nf._nc; ++i )
                proxy.SetComponent( i, value );

            proxy.SetAlpha( proxy.Max() );
        }
    }

    static inline void Run( TBlock< _SH >* iBlock, float iFrequency, float iFrequencyMult, float iAmplitudeMult, uint8 iNumLayers, int iSeed )
    {
        uint32 seed = iSeed < 0 ? time( NULL ) : iSeed;
        ValueNoise noise( seed );

        float ampMax = 0;
        {
            float amplitude = 1.0f;
            for( int i = 0; i < iNumLayers; ++i )
            {
                ampMax += amplitude;
                amplitude *= iAmplitudeMult;
            }
        }

        const int x1 = 0;
        const int y1 = 0;
        const int x2 = iBlock->Width();
        const int y2 = iBlock->Height();
        FThreadPool& global_pool = FGlobalThreadPool::Get();
        for( int y = y1; y < y2; ++y )
            global_pool.ScheduleJob( ProcessScanLine, iBlock, y, x1, x2, iFrequency, iFrequencyMult, iAmplitudeMult, iNumLayers, ampMax, noise );

        global_pool.WaitForCompletion();
    }
};


/////////////////////////////////////////////////////
// TBrownianNoiseGenerator_Default_MonoThread
template< uint32 _SH >
class TBrownianNoiseGenerator_Default_MonoThread
{
public:
    static void Run( TBlock< _SH >* iBlock, float iFrequency, float iFrequencyMult, float iAmplitudeMult, uint8 iNumLayers, int iSeed )
    {
        using tPixelProxy = typename TBlock< _SH >::tPixelProxy;
        using info = TBlockInfo< _SH >;

        uint32 seed = iSeed < 0 ? time( NULL ) : iSeed;
        ValueNoise noise( seed );

        float ampMax = 0;
        {
            float amplitude = 1.0f;
            for( int i = 0; i < iNumLayers; ++i )
            {
                ampMax += amplitude;
                amplitude *= iAmplitudeMult;
            }
        }

        const int x1 = 0;
        const int y1 = 0;
        const int x2 = iBlock->Width();
        const int y2 = iBlock->Height();
        for( int y = y1; y < y2; ++y )
        {
            for( int x = x1; x < x2; ++x )
            {
                tPixelProxy proxy = iBlock->PixelProxy( x, y );
                Vec2f pointNoise = Vec2f( x, y ) * iFrequency;
                float amplitude = 1.f;
                float floatvalue = 0;

                for( int i = 0; i < iNumLayers; ++i )
                {
                    floatvalue  += noise.eval( pointNoise ) * amplitude;
                    pointNoise  *= iFrequencyMult;
                    amplitude   *= iAmplitudeMult;
                }

                floatvalue /= ampMax;
                tPixelProxy::tPixelType value = ConvType< float, typename tPixelProxy::tPixelType >( floatvalue );

                for( int i = 0; i < info::_nf._nc; ++i )
                    proxy.SetComponent( i, value );

                proxy.SetAlpha( proxy.Max() );
            }
        }
    }
};


/////////////////////////////////////////////////////
// TBrownianNoiseGenerator
template< uint32 _SH >
class TBrownianNoiseGenerator
{
public:
    static inline void Run( TBlock< _SH >*              iBlock
                          , float iFrequency
                          , float iFrequencyMult
                          , float iAmplitudeMult
                          , uint8 iNumLayers
                          , int iSeed
                          , const FPerformanceOptions&  iPerformanceOptions= FPerformanceOptions() )
    {
        if( iPerformanceOptions.desired_workers > 1 )
        {
            TBrownianNoiseGenerator_Default_ScanLine< _SH >::Run( iBlock, iFrequency, iFrequencyMult, iAmplitudeMult, iNumLayers, iSeed );
        }
        else
        {
            TBrownianNoiseGenerator_Default_MonoThread< _SH >::Run( iBlock, iFrequency, iFrequencyMult, iAmplitudeMult, iNumLayers, iSeed );
        }
    }
};

} // namespace ULIS
