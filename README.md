<p align="center">
    <img width="288" height="64" src="samples/Splash.png">
</p>

# Showcase
![Showcase](samples/BlendNormals.png) | ![Showcase](samples/RasterText.png) | ![Showcase](samples/Transforms.png)
---- | ---- | ----
![Showcase](samples/BezierDeform.png) | ![Showcase](samples/TiledBlock.png) | ![Showcase](samples/Benchmark.png)

## License
Check LICENSE.md, ULIS3 is not available for commercial use.
|Name               |Link                                                           |License            |
|-------------------|---------------------------------------------------------------|-------------------|
|ULIS3              |https://github.com/Praxinos/ULIS3                              |CC-BY-NC-ND-4.0    |

## Description

        Cross-Platform C++14 Library
        2D Software Rasterizer on CPU
        Build as static or dynamic library
        Very lightweight, good performance
        Generic Digital Image Processing
        Python3x binding
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
    ULIS is created and maintained by Clément BERTHAUD ( a.k.a Layl, a.k.a Robot-Fromage ).  

    ULIS1 began development in December 2018.  
It was first hosted as a repository listed under user Robot-Fromage.  
It was then developped as a part of Praxinos, for its digital image processing tools.  
ULIS was first released internaly for Praxinos at the end of summer 2019.  
It made its debut in Iliad, a digital painting plugin for UnrealEngine  
The first version of ULIS experienced template bloating, resulting in terrible output binary sizes and compile times.  

    ULIS2, was starting development in beginning of January 2020.  
Compile times were drastically improved as well as output binary sizes.  
ULIS2 brought many things, such as better overall performances, support for more models, actual support for AVX2 optimisations, color mix, smudge, new blending modes and alpha modes, new interpolation types, etc.  
The build framework was also simplified and extended to conform to the typical cmake build process.  
Support for GPU image processing with OpenCL was introduced.  
The library dependencies changed and were embedded in the repository.  

    ULIS3 was introduced in March 2020.  
ULIS3 merged the commit history of both ULIS and ULIS2.  
ULIS3 brings high-level features, such as Tile Pools and Tiled Blocks, or advanced deformation algorithms.  
ULIS3 also aims to introduces WASM a new available compilation target, allowing to run transpiled C++ code on client side in web browsers.  

## Software Requirements Specification ( SRS )

        Linux, Windows or MacOS
        CMake
        Git
        C++ compiler with support for C++14 or greater

## Library Dependencies
Dependencies are redistributed directly within the repository under the 3rdparty directory.

|Dependency         |Link                                                           |License            |
|-------------------|---------------------------------------------------------------|-------------------|
|clip               |https://github.com/dacap/clip                                  |MIT                |
|cppfs              |https://github.com/cginternals/cppfs                           |MIT                |
|eigen              |https://gitlab.com/libeigen/eigen                              |MPL2               |
|FeatureDetector    |https://github.com/Mysticial/FeatureDetector                   |CC0 1.0 Universal  |
|freetype2          |https://github.com/aseprite/freetype2                          |FTL ( BSD-like )   |
|glm                |https://github.com/g-truc/glm                                  |MIT                |
|Little-CMS         |https://github.com/mm2/Little-CMS                              |MIT                |
|OCL-SDK            |https://github.com/GPUOpen-LibrariesAndSDKs/OCL-SDK/releases   |-                  |
|static_math        |https://github.com/Morwenn/static_math                         |MIT                |
|stb_image          |https://github.com/nothings/stb                                |MIT                |
|stb_image_write    |https://github.com/nothings/stb                                |MIT                |
|VCL                |https://github.com/vectorclass/version1                        |Apache 2.0         |

Additional Optional library can be used with ULIS3 to test samples programs or build the python binding:

        Qt5.x
        Python3.x

## Getting Started

        git clone https://github.com/Praxinos/ULIS3
        mkdir ULIS3_Build
        cd ULIS3_Build
        cmake -G ../ULIS3

Sample scripts are also available in the repository to help with the build process.

## ULIS3 for UnrealEngine ThirdParty Module
A `ULIS3.Build.cs` script is provided within the repository.  
ULIS3 GPU capabilities and interop with Direct3D or OpenGL in the context of a generic rendering hardware interface is still a work in progress.

## Examples
This is a small sample illustrating image loading, copy and blend operatios. Check samples to get a gist of how to use ULIS3, more details and specific functions.

```cpp
#include <ULIS3>
using namespace ::ul3;

int main() {
    FThreadPool  threadPool;
    uint32 perfIntent = ULIS3_PERF_MT | ULIS3_PERF_TSPEC | ULIS3_PERF_SSE42 | ULIS3_PERF_AVX2;
    FHostDeviceInfo host = FHostDeviceInfo::Detect();
    std::string pathBase = "base_160.png";
    std::string pathOver = "over_160.png";
    FBlock* blockBase = XLoadFromFile( &threadPool, ULIS3_NONBLOCKING, perfIntent, host, ULIS3_NOCB, pathBase, ULIS3_FORMAT_RGBA8 );
    FBlock* blockOver = XLoadFromFile( &threadPool, ULIS3_NONBLOCKING, perfIntent, host, ULIS3_NOCB, pathOver, ULIS3_FORMAT_RGBA8 );
    Fence( threadPool );
    FRect sourceRect = blockBase->Rect();
    int w = sourceRect.w * 8;
    int h = sourceRect.h * 5;
    FBlock* blockCanvas = new  FBlock( w, h, ULIS3_FORMAT_RGBA8 );
    for( int i = 0; i < NUM_BLENDING_MODES; ++i ) {
        int x = ( i % 8 ) * sourceRect.w;
        int y = ( i / 8 ) * sourceRect.h;
        Copy(   &threadPool, ULIS3_BLOCKING, perfIntent, host, ULIS3_NOCB, blockBase, blockCanvas, sourceRect, FVec2I( x, y ) );
        Blend(  &threadPool, ULIS3_NONBLOCKING, perfIntent, host, ULIS3_NOCB, blockOver, blockCanvas, sourceRect, FVec2F( x, y ), ULIS3_NOAA, static_cast< eBlendingMode >( i ), AM_NORMAL, 0.5f );
    }
    Fence( threadPool );
    delete  blockBase;
    delete  blockOver;
    delete  blockCanvas;
    return  0;
}
```

