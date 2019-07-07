/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS_Test_Thread.cpp
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#include <ULIS_CORE>
#include "ULIS/Thread/ULIS.Thread.Pool.h"

#include <thread>
#include <iomanip>
#include <chrono>
#include <vector>
#include <sstream>

struct Size { int w, h; };
Size image_sizes[] ={ { 64, 64 }
                    , { 128, 128 }
                    , { 256, 256 }
                    , { 512, 512 }
                    , { 1024, 1024 }
                    , { 2048, 2048 }
                    , { 4096, 4096 }
                    , { 8192, 8192 }
                    , { 16384, 16384 } };
int num_threads[] = { 1, 2, 4, 8, 16, 32, 64 };
#define SIZEOF_IMAGE_SIZES sizeof( image_sizes ) / sizeof( Size )
#define SIZEOF_NUM_THREADS sizeof( num_threads ) / sizeof( int )

struct TaskReport {
    Size    size;
    int     num_threads;
    float   time;
};


void mt_fill_memcpy( ::ULIS::FBlockBGRA8* iBlock, int start, int end, const ::ULIS::FBlockBGRA8::tPixelValue& iValue )
{
    void*       src     = iValue.Ptr();
    int         dep     = iBlock->Depth();
    uint8_t*    dst     = iBlock->DataPtr() + start * dep;

    for( int i = start; i < end; ++i )
    {
        memcpy( dst, src, dep );
        dst = dst + dep;
    }
}

void mt_fill_SSE( ::ULIS::FBlockBGRA8* iBlock, int start, int end, const ::ULIS::FBlockBGRA8::tPixelValue& iValue )
{
    void*       src = iValue.Ptr();
    int         dep = iBlock->Depth();
    uint8_t*    dst = iBlock->DataPtr() + start * dep;
    int         del = ( end - start ) / 16;

    ::ULIS::FVectorSIMD128 vec;
    memcpy( &vec.u8[0],  src, dep );
    memcpy( &vec.u8[4],  src, dep );
    memcpy( &vec.u8[8],  src, dep );
    memcpy( &vec.u8[12], src, dep );

    for( int i = 0; i < del; ++i )
    {
        _mm_store_si128( (__m128i*)dst, vec.m128i );
        dst = dst + 16;
    }
}

template< class F >
TaskReport ProfileBatch( F f, Size iSize, int iNumThreads, int iNumRepeat )
{
    ::ULIS::FBlockBGRA8* block = new ::ULIS::FBlockBGRA8( iSize.w, iSize.h );
    int     num_threads     = iNumThreads;
    int     num_op          = block->Width() * block->Height();
    int     op_per_thread   = num_op / num_threads;

    ::ULIS::FBlockBGRA8::tPixelValue val;
    val.R() = 'R';
    val.G() = 'G';
    val.B() = 'B';
    val.SetAlpha( 'A' );
    std::thread* batch = new std::thread[ num_threads ];

    std::cout << "=========================================" << std::endl;
    std::cout << "Profiling: " << iSize.w << "x" << iSize.h << std::endl;
    std::cout << "Num Threads:      " << num_threads    << std::endl;
    std::cout << "Total Op:         " << num_op         << std::endl;
    std::cout << "Op per Thread:    " << op_per_thread  << std::endl;
    std::cout << std::fixed;
    std::cout << std::setprecision( 2 );

    auto start_time = std::chrono::steady_clock::now();

    for( int l = 0; l < iNumRepeat; ++l )
    {
        float percent = ( l / (float)( iNumRepeat-1 ) ) * 100;
        std::cout << "\r";
        std::cout << "      ";
        std::cout << "\r";
        std::cout << percent << "%";

        int op_start   = 0;
        int op_end     = op_per_thread;
        for( int i = 0; i < num_threads; ++i )
        {
            batch[i] = std::thread( f, block, op_start, op_end, std::ref( val ) );
            op_start   += op_per_thread;
            op_end     += op_per_thread;
        }

        for( int i = 0; i < num_threads; ++i )
            batch[i].join();
    }

    auto end_time   = std::chrono::steady_clock::now();
    auto delta      = std::chrono::duration_cast< std::chrono::milliseconds>(end_time - start_time ).count();
    float average   = delta / (float)iNumRepeat;

    std::cout << std::endl;
    std::cout << "Result:   " << average << "ms" << std::endl;
    std::cout << std::endl;

    delete[] batch;
    delete  block;

    return  { iSize, iNumThreads, average };
}


template< class F >
TaskReport ProfilePool( F f, Size iSize, int iNumThreads, int iNumRepeat )
{
    ::ULIS::FBlockBGRA8* block = new ::ULIS::FBlockBGRA8( iSize.w, iSize.h );
    int     num_threads     = iNumThreads;
    int     num_op          = block->Width() * block->Height();
    int     op_per_thread   = num_op / num_threads;

    ::ULIS::FBlockBGRA8::tPixelValue val;
    val.R() = 'R';
    val.G() = 'G';
    val.B() = 'B';
    val.SetAlpha( 'A' );
    ::ULIS::FThreadPool pool( iNumThreads );

    std::cout << "=========================================" << std::endl;
    std::cout << "Profiling: " << iSize.w << "x" << iSize.h << std::endl;
    std::cout << "Num Threads:      " << num_threads    << std::endl;
    std::cout << "Total Op:         " << num_op         << std::endl;
    std::cout << "Op per Thread:    " << op_per_thread  << std::endl;
    std::cout << std::fixed;
    std::cout << std::setprecision( 2 );

    auto start_time = std::chrono::steady_clock::now();

    for( int l = 0; l < iNumRepeat; ++l )
    {
        float percent = ( l / (float)( iNumRepeat-1 ) ) * 100;
        std::cout << "\r";
        std::cout << "      ";
        std::cout << "\r";
        std::cout << percent << "%";

        int op_start   = 0;
        int op_end     = op_per_thread;
        for( int i = 0; i < num_threads; ++i )
        {
            pool.ScheduleJob( f, block, op_start, op_end, std::ref( val ) );
            op_start   += op_per_thread;
            op_end     += op_per_thread;
        }

        pool.WaitForCompletion();
    }

    auto end_time   = std::chrono::steady_clock::now();
    auto delta      = std::chrono::duration_cast< std::chrono::milliseconds>(end_time - start_time ).count();
    float average   = delta / (float)iNumRepeat;

    std::cout << std::endl;
    std::cout << "Result:   " << average << "ms" << std::endl;
    std::cout << std::endl;

    delete  block;

    return  { iSize, iNumThreads, average };
}


template< class F >
void RunBatch( F f, std::vector< TaskReport >& iReport, int iIterations )
{
    iReport.clear();

    for( int i = 0; i < SIZEOF_IMAGE_SIZES; ++i )
        for( int j = 0; j < SIZEOF_NUM_THREADS; ++j )
            iReport.push_back( ProfileBatch( f, image_sizes[i], num_threads[j], iIterations ) );
}


template< class F >
void RunPool( F f, std::vector< TaskReport >& iReport, int iIterations )
{
    iReport.clear();

    for( int i = 0; i < SIZEOF_IMAGE_SIZES; ++i )
    {
        for( int j = 0; j < SIZEOF_NUM_THREADS; ++j )
        {
            iReport.push_back( ProfilePool( f, image_sizes[i], num_threads[j], iIterations ) );
        }
    }

}

std::string bake_tab( int count )
{
    std::string out;
    for( int i = 0; i < count; ++ i )
        out += ' ';
    return  out;
}

std::string stringizefloat( float val )
{
    std::string out;
    
    double pi = 3.14159265359;
    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << val;
    out = stream.str();
    return  out;
}

void ProfileFillRectAA()
{
    ::ULIS::FBlockBGRA8* block = new ::ULIS::FBlockBGRA8( 256, 256 );
    int     num_threads     = 2;
    int     num_op          = block->Width() * block->Height();
    int     op_per_thread   = num_op / num_threads;

    ::ULIS::FBlockBGRA8::tPixelValue val;
    val.R() = 'R';
    val.G() = 'G';
    val.B() = 'B';
    val.SetAlpha( 'A' );
    ::ULIS::FThreadPool pool( num_threads );

    std::cout << "=========================================" << std::endl;
    std::cout << "Profiling: " << 256 << "x" << 256     << std::endl;
    std::cout << "Num Threads:      " << num_threads    << std::endl;
    std::cout << "Total Op:         " << num_op         << std::endl;
    std::cout << "Op per Thread:    " << op_per_thread  << std::endl;
    std::cout << std::fixed;
    std::cout << std::setprecision( 2 );

    auto start_time = std::chrono::steady_clock::now();

    for( int k = 0; k < 1000; ++k )
    {
        std::cout << k << std::endl;
        for( int l = 0; l < 1000; ++l )
        {
            int op_start   = 0;
            int op_end     = op_per_thread;
            for( int i = 0; i < num_threads; ++i )
            {
                pool.ScheduleJob( mt_fill_memcpy, block, op_start, op_end, std::ref( val ) );
                op_start   += op_per_thread;
                op_end     += op_per_thread;
            }

            pool.WaitForCompletion();
        }
    }
    auto end_time   = std::chrono::steady_clock::now();
    auto delta      = std::chrono::duration_cast< std::chrono::milliseconds>(end_time - start_time ).count();
    auto avg        = delta / 1000.f;

    std::cout << std::endl;
    std::cout << "Result:   " << avg << "ms" << std::endl;
    std::cout << std::endl;

    delete  block;
}


int main( int argc, char *argv[] )
{
    /*
    int iterations = 200;

    std::vector< TaskReport > batch_mt_fill_memcpy_report;
    RunBatch( &mt_fill_memcpy, batch_mt_fill_memcpy_report, iterations );

    std::vector< TaskReport > batch_mt_fill_SSE_report;
    RunBatch( &mt_fill_SSE, batch_mt_fill_SSE_report, iterations );

    std::vector< TaskReport > pool_mt_fill_memcpy_report;
    RunPool( &mt_fill_memcpy, pool_mt_fill_memcpy_report, iterations );

    std::vector< TaskReport > pool_mt_fill_SSE_report;
    RunPool( &mt_fill_SSE, pool_mt_fill_SSE_report, iterations );

    std::cout << "____________________" << std::endl;
    for( int i = 0; i < batch_mt_fill_memcpy_report.size(); ++i )
    {
        int dec = 10;
        std::string size    = std::to_string( batch_mt_fill_memcpy_report[i].size.w );
        std::string num     = std::to_string( batch_mt_fill_memcpy_report[i].num_threads );
        std::string t0      = stringizefloat( batch_mt_fill_memcpy_report[i].time );
        std::string t1      = stringizefloat( batch_mt_fill_SSE_report[i].time );
        std::string t2      = stringizefloat( pool_mt_fill_memcpy_report[i].time );
        std::string t3      = stringizefloat( pool_mt_fill_SSE_report[i].time );
        std::string decn = bake_tab( dec - size.length() );
        std::string dec0 = bake_tab( dec - num.length() );
        std::string dec1 = bake_tab( dec - t0.length() );
        std::string dec2 = bake_tab( dec - t1.length() );
        std::string dec3 = bake_tab( dec - t2.length() );
        std::cout << std::fixed;
        std::cout << std::setprecision( 2 );
        std::cout << size << decn << num << dec0 << t0 << dec1 << t1 << dec2 << t2 << dec3 << t3 << std::endl;
    }
    */
    ProfileFillRectAA();
    return 0;
}

