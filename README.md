# ULIS2
U Library for Imaging Systems

## License
Check LICENSE.md, ULIS2 is not available for commercial use.
|Name               |Link                                                           |License            |
|-------------------|---------------------------------------------------------------|-------------------|
|ULIS2              |https://github.com/Praxinos/ULIS2                              |CC-BY-NC-ND-4.0    |

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
|stb_image          |https://github.com/nothings/stb                                |MIT                |
|stb_image_write    |https://github.com/nothings/stb                                |MIT                |
|VCL                |https://github.com/vectorclass/version1                        |Apache 2.0         |

## Description

        Cross-Platform C++14 Library
        2D Software Rasterizer on CPU
        Build as static or dynamic library
        Very lightweight, good performance
        Generic Digital Image Processing
        Python3x binding

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
Additionally, the library dependencies changed and are now embedded in the repository. The library doesn't rely on preprocessor trickery so much anymore so boost_preprocessor and coal were removed, Qt and OpenCL are now fully optional, and VCL was added for handling SSE / AVX optimisations in a simpler way.  

## Software Requirements Specification ( SRS )

        64bit OS Only
        Linux, Windows or MacOS
        CMake
        Git
        C++ compiler with support for C++14 or greater

## Library Dependencies
Dependencies are redistributed directly within the repository under the 3rdparty directory.

        clip
        cppfs
        Eigen
        FeatureDetector
        Freetype2
        glm
        OpenCL
        Little-CMS2
        stb
        VCL ( Agner Fog's Vector Class Library )

Additional Optional library can be used with ULIS2 to test or extend capabilities:

        Qt
        Python3x

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

Check samples to get a gist of how to use ULIS2, more details and specific functions.
