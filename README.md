# ULIS2
Unique Library for Imaging Systems

## License
Check LICENSE.md, ULIS2 is not available for commerical use.

## Description

        Cross-Platform C++14 Library
        2D Software Rasterizer on CPU
        Build as static or dynamic library
        Very lightweight, good performance
        Generic Digital Image Processing

Details:

        Read Write from files for many popular formats
        Image conversions
        Render Text to any image in memory
        Affine Image Transforms
        FX, Convolution, Blur, Noise, ...
        All Standard Pixel Blending Modes
        Many Image Formats, Layouts and Types ( u8, u16, u32, float, double )
        Color Models ( RGB, HSL, HSV, CMY, CMYK, Lab, XYZ, ... )
        Color-Managed Pipelines, Color Profiles Support
        Multithreaded optimisations
        SSE4.2 and AVX2 optimisations
        Support for GPU image processing with OpenCL
        Large Tiled Images ( 300000 px * 300000 px)
        Image Pools and Caches for Optimisation

## History
ULIS was first developped by Clément BERTHAUD ( a.k.a Layl or Robot-Fromage ) on his spare-time in December 2018.  
It was then developped as part of Praxinos, aiming for robust tools for digital image processing.  
ULIS "1.0" was first released internaly for Praxinos at the end of summer 2019, and used in Iliad, a digital painting plugin for UnrealEngine developped by Praxinos.  
ULIS "1.0" had a lot of issues. It was hard to maintain and overused template, resulting in terrible binary sizes for the compiled library ( over 200mo for a release build ).  
Performance was ok but there was a lot of room for improvments.  
The library needed to mature a bit, and the changes to make were so drastic that a separate successor library, ULIS2, was starting development in beginning of January 2020.  
ULIS2 was scheduled for release in February 2020, and comes with a much simpler API, drastically reduced compile times and output binary sizes, better performances, and a lot of additional features such as support for more models, actual support for AVX2 optimisations, color mix, smudge, new blending modes and alpha modes, new interpolation types, etc.  
The build framework was also simplified and extended to conform to the typical cmake build process.  
Support for GPU image processing with OpenCL was introduced.  
Additionally, the library dependencies changed and are now embedded in the repository. The library doesn't rely on preprocessor so much anymore so boost_preprocessor and coal were removed, Qt and OpenCL are now fully optional, and VCL was added for handling SSE / AVX optimisations in a simpler way.  

## Software Requirements Specification ( SRS )

        64bit OS Only
        Linux, Windows or MacOS
        CMake
        Git
        C++ compiler with support for C++14 or greater

## Library Dependencies
Dependencies are redistributed directly within the repository under the 3rdparty directory.

        cppfs
        FeatureDetector
        freetype2
        glm
        OpenCL
        Little-CMS
        stb
        VCL ( Agner Fog's Vector Class Library )

Additional Optional library can be used with ULIS2 to test or extend capabilities:

        Qt

## Getting Started

        git clone https://github.com/Praxinos/ULIS2
        mkdir ULIS2_Build
        cd ULIS2_Build
        cmake -G ../ULIS2

Sample scripts are also available in the repository to help with the build process.

## ULIS2 for UnrealEngine ThirdParty Module
A `ULIS2.Build.cs` script is provided within the repository.
ULIS2 GPU capabilities and interop with Direct3D or OpenGL in the context of a generic rendering hardware interface is still a work in progress.

## Examples
Include ULIS2 headers:
```cpp
#include <ULIS2>
using namespace ul2;
// Ready to go
```

Create colors in different models:
```cpp
	FColor color_rgb8_red(  	ULIS2_FORMAT_RGB8,  { 255, 0, 0 } 			); 	// Red, constructed from int clamped in range 0-255.
	FColor color_rgba8_blue(    ULIS2_FORMAT_RGBA8, { 0, 0, 255, 127 } 		);  // Blue with semi transparent alpha information, constructed from int clamped in range 0-255.
	FColor color_rgba8_green(   ULIS2_FORMAT_RGBA8, { 0.f, 1.f, 0.f, 0.5f } );  // Green with semi transparent alpha information, constructed from float scaled to range 0-255
	FColor color_bgraF_red(     ULIS2_FORMAT_RGBAF, { 1.f, 0.f, 0.f, 0.5f } );  // Red with semi transparent alpha information, constructed from float, not clamped.
	FColor color_LabD(          ULIS2_FORMAT_LabD );    // Lab double color, initialized with zero values.
	FColor color_LabF(          ULIS2_FORMAT_LabF );    // Lab float color, initialized with zero values.
	FColor color_HSVAF(         ULIS2_FORMAT_HSVAF );   // HSV float color with alpha information, initialized with zero values.
	FColor color_CMYKA16(       ULIS2_FORMAT_CMYKA16 ); // CMYK 16bit uint color with alpha information, initialized with zero values.
	FColor color_ABGR8(         ULIS2_FORMAT_ABGR8 );   // Rgb 8bit uint color with alpha information, ABGR8888 memory layout, initialized with zero values.
	FColor color_BGRA8(         ULIS2_FORMAT_BGRA8 );   // Rgb 8bit uint color with alpha information, BGRA8888 memory layout, initialized with zero values.
	// etc ...
	
	FColor color( ULIS2_FORMAT_RGBA8 );
	color.SetR8( 255 );
	color.SetG8( 255 );
	color.SetB8( 255 );
	color.SetA8( 255 );
	// Color will be white.
	// Other accessors can be used too:
	color.SetRF( 0.5 );
	color.SetGF( 0.2 );
	color.SetBF( 0.0 );
	color.SetA8( 1.f );
	
	// Conversion of any combinations of models can be performed with Conv( Src, Dst )
	FColor color_RGBA8( ULIS2_FORMAT_RGBA8 		);
	FColor color_RGBA16( ULIS2_FORMAT_RGBA16 	);
	FColor color_BGRAD( ULIS2_FORMAT_BGRAD 		);
	FColor color_AbaLF( ULIS2_FORMAT_AbaLF 		);
	Conv( color_RGBA8, color_RGBA16 );  // perform value conversion from range 0-255 to 0-65535
	Conv( color_RGBA8, color_BGRAD );   // perform layout conversion from RGBA to BGRA and value conversion from range 0-255 to 0.0-1.0
	Conv( color_RGBA8, color_AbaLF );   // perform model conversion and value conversion from RGBA uint8 to Lab float with specified memory layout AbaLffff.
	// etc ...
```

Get info from pixel colors in different models:
```cpp
	FPixel rgba8( ULIS2_FORMAT_RGBA8 );
	pixelcolor.BytesPerSample()     // 1
	pixelcolor.Depth()              // 4
	pixelcolor.Format()             // ULIS2_FORMAT_RGBA8
	pixelcolor.Model()              // CM_RGB
	pixelcolor.Type()               // TYPE_UINT8
	pixelcolor.HasAlpha()           // true
	pixelcolor.NumSamples()         // 4
	pixelcolor.NumColorChannels()   // 3
```

Create and manipulate Images in various formats:
```cpp
	int         width   = 512;
	int         height  = 512;
	
	// Allocate blocks of size 512x512, with format layout in memory RGBA8888, memory is uninitialized
	FBlock      image_A( width, height, ULIS2_FORMAT_RGBA8 );
	FBlock      image_B( width, height, ULIS2_FORMAT_RGBA8 );
	
	// Create a thread pool with as many threads as supported by the system, and launch these threads
	FThreadPool threadPool;

	// Specify performances intent for operations.
	// User may want to not use multithreading or AVX optimisation for benchmark purpose
	FPerf       perfIntent( Perf_MT | Perf_SSE4_2 | Perf_AVX2 );
	
	// Pixel colors in RGB8
	FColor      colorWhite( ULIS2_FORMAT_RGB8, { 255, 255, 255 } );
	FColor      colorBlack( ULIS2_FORMAT_RGB8, { 0, 0, 0 } );
```

Full program for rendering simple black text on white background (API is subject to changes):
```cpp
#include <ULIS2>

int
main( int argc, char *argv[] )
{
	FBlock          block( 512, 512, ULIS2_FORMAT_BGRA8 );
	FThreadPool     threadPool;
	FPerf           perfIntent( Perf_Best_CPU );
	FCPU            cpuInfo
	FPixel          white( ULIS2_FORMAT_BGRA8, { 255_u8, 255_u8, 255_u8, 255_u8 } );
	FPixel          black( ULIS2_FORMAT_BGRA8, { 0_u8, 0_u8, 0_u8, 0_u8 } );

	Fill( &threadPool, ULIS2_BLOCKING, perfIntent, cpuInfo, &block, white, ULIS2_NOCB );

	FFontEngine     fontEngine;
	FFontRegistry   fontRegistry;
	fontRegistry.Load( fontEngine );

	FFont font_Arial_Black( fontEngine, fontRegistry, "Arial", "Black" );

	DrawText( &threadPool, ULIS2_BLOCKING, perfIntent, cpuInfo, &block, "Hello World !", glm::vec2( 0.f ), black, font_Arial_Black, 16px, ULIS2_NOCB );

	return  0;
}
```

The new API for complex blend operations:
```cpp
#include <ULIS2>

int
main( int argc, char *argv[] )
{
	// Bake data
	FBlock          blockBase( 1024, 1024, ULIS2_FORMAT_BGRA8 );
	FBlock          blockOver( 512, 512, ULIS2_FORMAT_BGRA8 );
	
	// Bake perf info
	FPerfInfo perfInfo = {};
    perfInfo.pool    	= &threadPool;
    perfInfo.intent     = FPerf( Perf_MT | Perf_TSPEC | Perf_AVX2 );
    perfInfo.blocking   = ULIS2_NONBLOCKING;
    perfInfo.callCB     = ULIS2_NOCB;

	// Bake blend info
    FBlendInfo blendInfo = {};
    blendInfo.source          	= &blockBase;
    blendInfo.backdrop         	= &blockOver;
    blendInfo.sourceRect       	= FRect( 64, 64, 128, 128 );
    blendInfo.tilingTranslation	= FVec2I( 32, 0 );
    blendInfo.backdropPosition 	= FVec2F( 200.2, 430.34 );
    blendInfo.backdropCoverage 	= FVec2I( 256, 256 );
    blendInfo.subpixelFlag     	= ULIS2_AA;
    blendInfo.blendingMode     	= BM_NORMAL;
    blendInfo.alphaMode        	= AM_NORMAL;
    blendInfo.opacityValue      = 0.85f;
	
	// Apply operation
    BlendRect( perfInfo, blendInfo );

	return  0;
}
```

