/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS_Test.cpp
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#include <ULIS_CORE>
#include "ULIS/Thread/ULIS.Thread.Pool.h"

#include <thread>
#include <iomanip>
#include <chrono>
#include <vector>

struct Size { int w, h; };
Size sizes[] =  { { 64, 64 }
                , { 128, 128 }
                , { 256, 256 }
                , { 512, 512 }
                , { 1024, 1024 }
                , { 2048, 2048 }
                , { 4096, 4096 }
                , { 8192, 8192 }
                , { 16384, 16384 }
                };


int nums[] = { 1, 2, 4, 8, 16, 32, 64 };


struct TaskReport
{
    Size size;
    int numthreads;
    float time;
};


void fill_mt_imp( ::ULIS::FBlockBGRA8* iBlock, int start, int end, const ::ULIS::FBlockBGRA8::tPixelValue& iValue )
{
    int depth = iBlock->Depth();
    uint8_t* dst = iBlock->DataPtr() + start * depth;
    void* src = iValue.Ptr();
    for( int i = start; i < end; ++i )
    {
        memcpy( dst, src, depth );
        dst = dst + depth;
    }
}

void fill_mt_imp_SSE( ::ULIS::FBlockBGRA8* iBlock, int start, int end, const ::ULIS::FBlockBGRA8::tPixelValue& iValue )
{
    void*       src = iValue.Ptr();
    int         dep = iBlock->Depth();
    uint8_t*    dst = iBlock->DataPtr() + start * dep;
    int         del = ( ( end - start ) / 16 ) / 4; 
    int         det = del / 16;

    ::ULIS::FVectorSIMD128 vec;
    memcpy( &vec.u8[0],  src, dep );
    memcpy( &vec.u8[4],  src, dep );
    memcpy( &vec.u8[8],  src, dep );
    memcpy( &vec.u8[12], src, dep );

    for( int i = 0; i < det; ++i )
    {
        _mm_store_si128( (__m128i*)dst, vec.m128i );
        dst = dst + 16;
    }
}


TaskReport profile( Size iSize, int iNumThreads, int iNumRepeat )
{
    ::ULIS::FBlockBGRA8* block = new ::ULIS::FBlockBGRA8( iSize.w, iSize.h );
    int     num_threads = iNumThreads;
    int     num_op = block->Width() * block->Height();
    int     op_per_thread = num_op / num_threads;

    std::cout << "=========================================" << std::endl;
    std::cout << "Profiling: " << iSize.w << "x" << iSize.h << std::endl;
    std::cout << "Requested num threads:    " << num_threads    << std::endl;
    std::cout << "Total individual op:      " << num_op         << std::endl;
    std::cout << "Op per thread:            " << op_per_thread  << std::endl;

    ::ULIS::FBlockBGRA8::tPixelValue val;
    val.SetColor( ::ULIS::CColor::FromRGB( 255, 0, 0 ) );
    std::thread* pool = new std::thread[num_threads];

    auto start_time = std::chrono::steady_clock::now();

    for( int l = 0; l < iNumRepeat; ++l )
    {
        float percent = (l / (float)(iNumRepeat-1)) * 100;
        std::cout << "\r";
        std::cout << "      ";
        std::cout << "\r";
        std::cout << percent << "%";

        int op_start   = 0;
        int op_end     = op_per_thread;
        for( int i = 0; i < num_threads; ++i )
        {
            pool[i] = std::thread( &fill_mt_imp, block, op_start, op_end, std::ref( val ) );
            op_start   += op_per_thread;
            op_end     += op_per_thread;
        }

        for( int i = 0; i < num_threads; ++i )
            pool[i].join();
    }

    auto end_time = std::chrono::steady_clock::now();
    auto delta = std::chrono::duration_cast< std::chrono::milliseconds>(end_time - start_time ).count();
    float average = delta / (float)iNumRepeat;
    std::cout << std::endl;
    std::cout << "RESULT: " << average << "ms" << std::endl;
    std::cout << std::endl;

    delete[] pool;
    delete  block;

    return  { iSize, iNumThreads, average };
}


void RunTest_Old()
{
    /*
    for( int i = 0; i < 15; ++i )
        for( int j = 0; j < 10; ++j )
            profile( sizes[i], nums[j], 100 );
    */
    std::cout << std::fixed;
    std::cout << std::setprecision(2);

    std::vector< TaskReport > vec;

    for( int i = 0; i < 9; ++i )
        for( int j = 0; j < 7; ++j )
            vec.push_back( profile( sizes[i], nums[j], 200 ) );

    std::cout << "____________________" << std::endl;
    std::cout << "Size      Threads     Time(ms)" << std::endl;
    for( int i = 0; i < vec.size(); ++i )
    {
        std::cout << vec[i].size.w << "     " << vec[i].numthreads << "     " << vec[i].time << std::endl;
    }
}


void InfiniteLoop()
{
    while( true )
    {
        auto dummy = 0;
    }
}



int main()
{
    return 0;
}

