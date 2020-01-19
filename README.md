# ULIS2
Unique Library for Imaging Systems

## Description
        - Cross-Platform C++14 Library
        - Build as static or dynamic library
        - Very lightweight, good performance
        - Generic Digital Image Processing
        - Read Write from files for many popular formats
        - Image conversions
        - Affine Image Transforms
        - FX, Convolution, Blur, Noise, ...
        - 2D Software Rasterizer
        - All Standard Pixel Blending Modes
        - Many Image Formats, Layouts and Types ( u8, u16, u32, float, double )
        - Color Models ( RGB, HSL, HSV, CMY, CMYK, Lab, XYZ, ... )
        - Color-Managed Pipelines, Color Space Support With Little-CMS
        - Multithreaded optimisations
        - SSE4.2 and AVX2 optimisations
        - Support for GPU image processing with OpenCL
        - Large Tiled Images ( 300000 px * 300000 px)
        - Image Pools and Caches for Optimisation

## Software Requirements Specification ( SRS )
        - 64bit OS Only
        - Linux, Windows or MacOS
        - CMake
        - Git
        - C++ compiler with support for C++14 or greater

## Library Dependencies
Dependencies are redistributed directly within the repository under the 3rdparty directory.

        - glm
        - Little-CMS
        - VCL ( Agner Fog's Vector Class Library )
        - FeatureDetector

Additional Optional library can be used with ULIS2 to test or extend capabilities:
        - OpenCL
        - Qt


## Getting Started
        - git clone https://github.com/Praxinos/ULIS2
        - mkdir ULIS2_Build
        - cd ULIS2_Build
        - cmake -G ../ULIS2

Sample scripts are also available in the repository to help with the build process.

## ULIS2 for UnrealEngine ThirdParty Module
A `ULIS2.Build.cs` script is provided within the repository.
