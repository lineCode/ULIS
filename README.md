# ULIS
![alt text](http://clementberthaud.com/dev/dep/ULIS/media/com/Banner.png "ULIS")
Unlimited Library for Imaging Systems

## Description
        - Cross-Platform C++14 Library
        - Generic digital image processing
        - 2D Software rasterizer
        - Unlimited image formats ( u8, u16, u32, float, double )
        - Custom bit-ordered memory layouts
        - All Photoshop pixel blending modes
        - Color models ( RGB, HSL, HSV, CMYK, ... )
        - Color-managed pipelines, Color Space support ( icm profiles and device-independant )
        - Optimized algorithms with multithreading
        - Optimized algorithms with SIMD Extensions ( SSE2 )
        - Big Images ( 300000 px * 300000 px)
        - Image pools and caches for optimisations
        - Memory storage of animated image sequences

## Software Requirements Specification ( SRS )
        - 64bit OS - Linux, Windows or MacOS
        - CMake ( 3.11.4 or greater )
        - Git ( 2.17.0 or greater )
        - C++ compiler with C++14 support
        - Python ( 3.7 or greater ) available from PATH as "python3" ( optional )

## Supported Compilers
        - MinGW 64 7.xx
        - Clang LLVM xx
        - MSVC
        - GNU GCC

## Library Dependencies
        - coal ( https://github.com/Robot-Fromage/coal )
        - boost_preprocessor ( https://github.com/boostorg/preprocessor )
        - glm ( https://github.com/g-truc/glm )
        - Qt ( https://www.qt.io/, Optional )

## Officially Supported IDEs
        - Windows: VisualStudio 2017
        - macOS: XCode
        - Linux: SublimeText

## Getting Started
        - git clone https://github.com/Robot-Fromage/ULIS
        - cd ULIS
        - #Windows: call Setup.bat
        - #macOS / Linux : sh Setup.sh