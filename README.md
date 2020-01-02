# ULIS2
Unique Library for Imaging Systems

## Description
        - Cross-Platform C++14 Library
        - Generic Digital Image Processing
        - 2D Software Rasterizer
        - All Standard Pixel Blending Modes
        - Many Image Formats, Layouts and Types ( u8, u16, u32, float, double )
        - Color Models ( RGB, HSL, HSV, CMY, CMYK, Lab, XYZ, ... )
        - Color-Managed Pipelines, Color Space Support With Little-CMS
        - Everything Multithreaded
        - SIMD SSE Extensions For Common Heavy Pixel Operations
        - Big Images, Tiled Images ( 300000 px * 300000 px)
        - Image Pools and Caches for Optimisation

## Software Requirements Specification ( SRS )
        - 64bit OS Only
        - Linux, Windows or MacOS
        - CMake ( 3.11+ )
        - Git ( 2.17+ )
        - C++ compiler with support for C++14 or greater

## Supported Compilers
        - MinGW x64
        - Clang LLVM
        - MSVC
        - GNU GCC


## Library Dependencies
        - glm           ( https://github.com/g-truc/glm )
        - Little-CMS    ( https://github.com/Robot-Fromage/Little-CMS )
Note: my Little-CMS fork provides a CMakeLists but may not be up to date. Alternatively, the CMakeLists for Little-CMS is provided within this repository under scripts/.

## Officially Supported IDEs
        - Windows: VisualStudio 2017, 2019
        - MacOS: XCode
        - Linux: SublimeText

## Getting Started
        - git clone git@pro.github.com:Praxinos/ULIS2.git
        - mkdir ULIS2_Build
        - cd ULIS2_Build
        - cmake -G "Visual Studio 15 2017 Win64" -DULIS2_GLM_INCLUDE_PATH:STRING="default" -DULIS2_LCMS2_INCLUDE_PATH:STRING="default" -DULIS2_LCMS2_DEBUG_LIB_PATH:STRING="default" -DULIS2_LCMS2_RELEASE_LIB_PATH:STRING="default" ../ULIS2

Make sure to use out of source generation.

Make sure you cloned the dependencies and built them if needed. You can then copy the path for the requested components instead of the "default" value. All paths should use forward slashes on all OS, even Windows MacOS and Linux. All paths should have a trailing forward slash too. Make sure you fill the path for the config file of your compiler / IDE of choice, and that components you use were built with the same compiler. The building process of the dependencies will not be detailled here, it is left for the user to figure out, although most dependencies are header-only and i provide a CMakeLists in order to build Little-CMS easily, which can also be found in the Scripts folder of ULIS2.

Sample scripts are also available in the repository to help with the build process.

The CMake files will allow you to work with almost any supported IDE and compiler combinations.

## ULIS2 for UnrealEngine ThirdParty Module
A `ULIS2.Build.cs` script is provided within the repository. In order to include ULIS2 as a third party module for UE4 you can build and provide a distribution folder with the build.cs file and put them together in a ULIS2 directory under ThirdParty in your UnrealEngine setup, wether it is a custom build, C++ project or Plugin.
