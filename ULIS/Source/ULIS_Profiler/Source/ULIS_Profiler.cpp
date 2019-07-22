/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS_Test_Thread.cpp
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#include <ULIS_Core>

struct FSize { int w, h; };
FSize image_sizes[] ={ { 64, 64 }
                    , { 128, 128 }
                    , { 256, 256 }
                    , { 512, 512 }
                    , { 1024, 1024 }
                    , { 2048, 2048 }
                    , { 4096, 4096 }
                    , { 8192, 8192 }
                    , { 16384, 16384 } };
#define SIZEOF_IMAGE_SIZES sizeof( image_sizes ) / sizeof( FSize )
#define SIZEOF_NUM_THREADS sizeof( num_threads ) / sizeof( int )

int error( const char* iMsg )
{
    std::cout << iMsg << std::endl;
    return -1;
}

bool check_fmt( ::ULIS::uint32 fmt )
{
    if( fmt == 0 )
        return  false;

    bool in = false;
    for( int i = 0; i < ULIS_REG_SIZE; ++i )
        if( ULIS_REG[i] == fmt )
            in = true;

    return  in;
}


bool check_NT( int NT )
{
    return  NT > 0 && NT <= 64;
}


bool check_num( int num )
{
    return  num > 0;
}

bool check_size( int size )
{
    bool in = false;
    for( int i = 0; i < SIZEOF_IMAGE_SIZES; ++i )
        if( image_sizes[i].w == size )
            in = true;

    return  in;
}


bool check_opt( const std::string& opt )
{
    return  ( opt == "sse" || opt == "mem" || opt == "reg" );
}


bool check_mode( int mode )
{
    return  mode >= 0 && mode < (int)::ULIS::eBlendingMode::kNumBlendingModes;
}

int clear( int argc, char *argv[] )
{
    // Expected input:
    // 0 - ignored
    // 1 - clear
    // 2 - fmt
    // 3 - NT
    // 4 - num
    // 5 - size
    // 6 - opt
    // 7 - ignored
    std::cout << "Processing clear, parsing args..." << std::endl;
    if( argc != 7 ) { return error( "Bad args, abort." ); }
    ::ULIS::uint32  fmt  = std::stoul( std::string( argv[2] ).c_str() );
    ::ULIS::uint32  NT   = std::atoi( std::string( argv[3] ).c_str() );
    ::ULIS::uint32  num  = std::atoi( std::string( argv[4] ).c_str() );
    ::ULIS::uint32  size = std::atoi( std::string( argv[5] ).c_str() );
    std::string     opt  = std::string( argv[6] );
    std::cout << "OP:   " << "clear"    << std::endl;
    if( check_fmt(    fmt     ) )   { std::cout << "fmt:  " << fmt << " (" << ::ULIS::BlockSpec( fmt )._ss << ")" << std::endl; } else { return error( "Bad arg: fmt, abort."   ); }
    if( check_NT(     NT      ) )   { std::cout << "NT:   " << NT         << std::endl; } else { return error( "Bad arg: NT, abort."    ); }
    if( check_num(    num     ) )   { std::cout << "num:  " << num        << std::endl; } else { return error( "Bad arg: num, abort."   ); }
    if( check_size(   size    ) )   { std::cout << "size: " << size       << std::endl; } else { return error( "Bad arg: size, abort."  ); }
    if( check_opt(    opt     ) )   { std::cout << "opt:  " << opt        << std::endl; } else { return error( "Bad arg: opt, abort."   ); }

    return 0;
}

int fill( int argc, char *argv[] )
{
    // Expected input:
    // 0 - ignored
    // 1 - fill
    // 2 - fmt
    // 3 - NT
    // 4 - num
    // 5 - size
    // 6 - opt
    // 7 - ignored
    std::cout << "Processing fill, parsing args..." << std::endl;
    if( argc != 7 ) { return error( "Bad args, abort." ); }
    ::ULIS::uint32  fmt  = std::stoul( std::string( argv[2] ).c_str() );
    ::ULIS::uint32  NT   = std::atoi( std::string( argv[3] ).c_str() );
    ::ULIS::uint32  num  = std::atoi( std::string( argv[4] ).c_str() );
    ::ULIS::uint32  size = std::atoi( std::string( argv[5] ).c_str() );
    std::string     opt  = std::string( argv[6] );
    std::cout << "OP:   " << "fill"    << std::endl;
    if( check_fmt(    fmt     ) )   { std::cout << "fmt:  " << fmt << " (" << ::ULIS::BlockSpec( fmt )._ss << ")" << std::endl; } else { return error( "Bad arg: fmt, abort."   ); }
    if( check_NT(     NT      ) )   { std::cout << "NT:   " << NT         << std::endl; } else { return error( "Bad arg: NT, abort."    ); }
    if( check_num(    num     ) )   { std::cout << "num:  " << num        << std::endl; } else { return error( "Bad arg: num, abort."   ); }
    if( check_size(   size    ) )   { std::cout << "size: " << size       << std::endl; } else { return error( "Bad arg: size, abort."  ); }
    if( check_opt(    opt     ) )   { std::cout << "opt:  " << opt        << std::endl; } else { return error( "Bad arg: opt, abort."   ); }

    return 0;
}

int blend( int argc, char *argv[] )
{
    // Expected input:
    // 0 - ignored
    // 1 - blend
    // 2 - fmt
    // 3 - NT
    // 4 - num
    // 5 - size
    // 6 - opt
    // 7 - mode
    std::cout << "Processing fill, parsing args..." << std::endl;
    if( argc != 8 ) { return error( "Bad args, abort." ); }
    ::ULIS::uint32  fmt  = std::stoul( std::string( argv[2] ).c_str() );
    ::ULIS::uint32  NT   = std::atoi( std::string( argv[3] ).c_str() );
    ::ULIS::uint32  num  = std::atoi( std::string( argv[4] ).c_str() );
    ::ULIS::uint32  size = std::atoi( std::string( argv[5] ).c_str() );
    std::string     opt  = std::string( argv[6] );
    ::ULIS::uint32  mode = std::atoi( std::string( argv[7] ).c_str() );
    std::cout << "OP:   " << "fill"    << std::endl;
    if( check_fmt(    fmt     ) )   { std::cout << "fmt:  " << fmt << " (" << ::ULIS::BlockSpec( fmt )._ss << ")" << std::endl; } else { return error( "Bad arg: fmt, abort."   ); }
    if( check_NT(     NT      ) )   { std::cout << "NT:   " << NT         << std::endl; } else { return error( "Bad arg: NT, abort."    ); }
    if( check_num(    num     ) )   { std::cout << "num:  " << num        << std::endl; } else { return error( "Bad arg: num, abort."   ); }
    if( check_size(   size    ) )   { std::cout << "size: " << size       << std::endl; } else { return error( "Bad arg: size, abort."  ); }
    if( check_opt(    opt     ) )   { std::cout << "opt:  " << opt        << std::endl; } else { return error( "Bad arg: opt, abort."   ); }
    if( check_mode(   mode    ) )   { std::cout << "mode: " << ::ULIS::kwBlendingMode[mode] << std::endl; } else { return error( "Bad arg: opt, abort."   ); }

    return 0;
}

int copy( int argc, char *argv[] )
{
    // Expected input:
    // 0 - ignored
    // 1 - copy
    // 2 - fmt
    // 3 - NT
    // 4 - num
    // 5 - size
    // 6 - opt
    // 7 - ignored
    std::cout << "Processing copy, parsing args..." << std::endl;
    if( argc != 7 ) { return error( "Bad args, abort." ); }
    ::ULIS::uint32  fmt  = std::stoul( std::string( argv[2] ).c_str() );
    ::ULIS::uint32  NT   = std::atoi( std::string( argv[3] ).c_str() );
    ::ULIS::uint32  num  = std::atoi( std::string( argv[4] ).c_str() );
    ::ULIS::uint32  size = std::atoi( std::string( argv[5] ).c_str() );
    std::string     opt  = std::string( argv[6] );
    std::cout << "OP:   " << "copy"    << std::endl;
    if( check_fmt(    fmt     ) )   { std::cout << "fmt:  " << fmt << " (" << ::ULIS::BlockSpec( fmt )._ss << ")" << std::endl; } else { return error( "Bad arg: fmt, abort."   ); }
    if( check_NT(     NT      ) )   { std::cout << "NT:   " << NT         << std::endl; } else { return error( "Bad arg: NT, abort."    ); }
    if( check_num(    num     ) )   { std::cout << "num:  " << num        << std::endl; } else { return error( "Bad arg: num, abort."   ); }
    if( check_size(   size    ) )   { std::cout << "size: " << size       << std::endl; } else { return error( "Bad arg: size, abort."  ); }
    if( check_opt(    opt     ) )   { std::cout << "opt:  " << opt        << std::endl; } else { return error( "Bad arg: opt, abort."   ); }

    return 0;
}

// Call examples:
// ULIS_Profiler.exe clear  0           64  1000    256     mem
// ULIS_Profiler.exe fill   0           32  200     2048    sse
// ULIS_Profiler.exe clear  3726693057  64  500     8192    reg
int main( int argc, char *argv[] )
{
    // Expected input:
    // 0 - ignored
    // 1 - OP
    // 2 - fmt
    // 3 - NT
    // 4 - num
    // 5 - size
    // 6 - opt
    // 7 - extra
    if( argc <=1 ) { return error( "No args, abort." ); }

    std::cout << "Requested OP: " << argv[1] << std::endl;
    std::string op = argv[1];

         if( op == "clear"  ) { return  clear(  argc, argv ); }
    else if( op == "fill"   ) { return  fill(   argc, argv ); }
    else if( op == "blend"  ) { return  blend(  argc, argv ); }
    else if( op == "copy"   ) { return  copy(   argc, argv ); }
    else { return  error( "Bad Op, abort." ); }

    return 0;
}

