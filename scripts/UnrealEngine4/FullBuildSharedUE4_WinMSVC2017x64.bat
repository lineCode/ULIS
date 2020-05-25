@echo off
:: Put this file next to ULIS3 directory and launch to trigger full build and Redist
setlocal
pushd %~dp0

:: Make dir for build if not exist
IF NOT EXIST ULIS3_FullBuildUE4_WinMSVCx64_Redist ( MKDIR ULIS3_FullBuildUE4_WinMSVCx64_Redist )

:: Step in build dir
cd ULIS3_FullBuildUE4_WinMSVCx64_Redist

:: Make Generated dir for generated project if not exist
IF NOT EXIST Generated_VisualStudio_Solution_MSVC ( MKDIR Generated_VisualStudio_Solution_MSVC )

:: Step in Generated dir
cd Generated_VisualStudio_Solution_MSVC

:: Clean cmake garbage if there
IF EXIST CMakeFiles ( rmdir /S /Q CMakeFiles )
IF EXIST cmake_install.cmake ( del cmake_install.cmake )
IF EXIST CMakeCache.txt ( del CMakeCache.txt )

:: Rebuild Project
cmake   -G "Visual Studio 15 2017 Win64"    ^
        -DULIS3_BUILD_SHARED=ON             ^
        ../../ULIS3

cmake --build . --config Debug
cmake --build . --config Release

:: go up to build dir
cd ..

:: Make Redist dir for generated project if not exist
RMDIR /S /Q redist
MKDIR redist
cd redist

mkdir include
cd include
mkdir ULIS3
mkdir static_math
mkdir glm
::mkdir clip
::mkdir cppfs
::mkdir eigen
::mkdir FeatureDetector
::mkdir freetype2
::mkdir Little-CMS
::mkdir OCL-SDK
::mkdir stb
::mkdir VCL

cd ..
mkdir bin   & cd bin
mkdir x64   & cd x64
mkdir release
mkdir debug

cd ../../../../
XCOPY /E /C /I /Q /H /K /Y /B ".\ULIS3\include"                     "ULIS3_FullBuildUE4_WinMSVCx64_Redist\redist\include\ULIS3"
XCOPY /E /C /I /Q /H /K /Y /B ".\ULIS3\3rdparty\static_math"        "ULIS3_FullBuildUE4_WinMSVCx64_Redist\redist\include\static_math"
XCOPY /E /C /I /Q /H /K /Y /B ".\ULIS3\3rdparty\glm"                "ULIS3_FullBuildUE4_WinMSVCx64_Redist\redist\include\glm"
::XCOPY /E /C /I /Q /H /K /Y /B ".\ULIS3\3rdparty\clip"               "ULIS3_FullBuildUE4_WinMSVCx64_Redist\redist\include\clip"
::XCOPY /E /C /I /Q /H /K /Y /B ".\ULIS3\3rdparty\cppfs"              "ULIS3_FullBuildUE4_WinMSVCx64_Redist\redist\include\cppfs"
::XCOPY /E /C /I /Q /H /K /Y /B ".\ULIS3\3rdparty\eigen"              "ULIS3_FullBuildUE4_WinMSVCx64_Redist\redist\include\eigen"
::XCOPY /E /C /I /Q /H /K /Y /B ".\ULIS3\3rdparty\FeatureDetector"    "ULIS3_FullBuildUE4_WinMSVCx64_Redist\redist\include\FeatureDetector"
::XCOPY /E /C /I /Q /H /K /Y /B ".\ULIS3\3rdparty\freetype2"          "ULIS3_FullBuildUE4_WinMSVCx64_Redist\redist\include\freetype2"
::XCOPY /E /C /I /Q /H /K /Y /B ".\ULIS3\3rdparty\Little-CMS"         "ULIS3_FullBuildUE4_WinMSVCx64_Redist\redist\include\Little-CMS"
::XCOPY /E /C /I /Q /H /K /Y /B ".\ULIS3\3rdparty\OCL-SDK"            "ULIS3_FullBuildUE4_WinMSVCx64_Redist\redist\include\OCL-SDK"
::XCOPY /E /C /I /Q /H /K /Y /B ".\ULIS3\3rdparty\stb"                "ULIS3_FullBuildUE4_WinMSVCx64_Redist\redist\include\stb"
::XCOPY /E /C /I /Q /H /K /Y /B ".\ULIS3\3rdparty\VCL"                "ULIS3_FullBuildUE4_WinMSVCx64_Redist\redist\include\VCL"

::COPY /Y "ULIS3_FullBuildUE4_WinMSVCx64_Redist\Generated_VisualStudio_Solution_MSVC\3rdparty\build_clip\Debug\clipd.lib" "ULIS3_FullBuildUE4_WinMSVCx64_Redist\Redist\Lib\Win\MSVC\x64\Debug\clipd.lib"
::COPY /Y "ULIS3_FullBuildUE4_WinMSVCx64_Redist\Generated_VisualStudio_Solution_MSVC\3rdparty\build_clip\Release\clip.lib" "ULIS3_FullBuildUE4_WinMSVCx64_Redist\Redist\Lib\Win\MSVC\x64\Release\clip.lib"
::COPY /Y "ULIS3_FullBuildUE4_WinMSVCx64_Redist\Generated_VisualStudio_Solution_MSVC\3rdparty\build_cppfs\Debug\cppfsd.lib" "ULIS3_FullBuildUE4_WinMSVCx64_Redist\Redist\Lib\Win\MSVC\x64\Debug\cppfsd.lib"
::COPY /Y "ULIS3_FullBuildUE4_WinMSVCx64_Redist\Generated_VisualStudio_Solution_MSVC\3rdparty\build_cppfs\Release\cppfs.lib" "ULIS3_FullBuildUE4_WinMSVCx64_Redist\Redist\Lib\Win\MSVC\x64\Release\cppfs.lib"
::COPY /Y "ULIS3_FullBuildUE4_WinMSVCx64_Redist\Generated_VisualStudio_Solution_MSVC\3rdparty\build_freetype2\Debug\freetyped.lib" "ULIS3_FullBuildUE4_WinMSVCx64_Redist\Redist\Lib\Win\MSVC\x64\Debug\freetyped.lib"
::COPY /Y "ULIS3_FullBuildUE4_WinMSVCx64_Redist\Generated_VisualStudio_Solution_MSVC\3rdparty\build_freetype2\Release\freetype.lib" "ULIS3_FullBuildUE4_WinMSVCx64_Redist\Redist\Lib\Win\MSVC\x64\Release\freetype.lib"
::COPY /Y "ULIS3_FullBuildUE4_WinMSVCx64_Redist\Generated_VisualStudio_Solution_MSVC\3rdparty\build_lcms2\Debug\lcms2d.lib" "ULIS3_FullBuildUE4_WinMSVCx64_Redist\Redist\Lib\Win\MSVC\x64\Debug\lcms2d.lib"
::COPY /Y "ULIS3_FullBuildUE4_WinMSVCx64_Redist\Generated_VisualStudio_Solution_MSVC\3rdparty\build_lcms2\Release\lcms2.lib" "ULIS3_FullBuildUE4_WinMSVCx64_Redist\Redist\Lib\Win\MSVC\x64\Release\lcms2.lib"

::COPY /Y "ULIS3_FullBuildUE4_WinMSVCx64_Redist\Generated_VisualStudio_Solution_MSVC\Debug\ULIS3d.pdb" "ULIS3_FullBuildUE4_WinMSVCx64_Redist\redist\bin\x64\debug\ULIS3d.pdb"
COPY /Y "ULIS3_FullBuildUE4_WinMSVCx64_Redist\Generated_VisualStudio_Solution_MSVC\Debug\ULIS3d.lib" "ULIS3_FullBuildUE4_WinMSVCx64_Redist\redist\bin\x64\debug\ULIS3d.lib"
COPY /Y "ULIS3_FullBuildUE4_WinMSVCx64_Redist\Generated_VisualStudio_Solution_MSVC\Debug\ULIS3d.dll" "ULIS3_FullBuildUE4_WinMSVCx64_Redist\redist\bin\x64\debug\ULIS3d.dll"
COPY /Y "ULIS3_FullBuildUE4_WinMSVCx64_Redist\Generated_VisualStudio_Solution_MSVC\Release\ULIS3.lib" "ULIS3_FullBuildUE4_WinMSVCx64_Redist\redist\bin\x64\release\ULIS3.lib"
COPY /Y "ULIS3_FullBuildUE4_WinMSVCx64_Redist\Generated_VisualStudio_Solution_MSVC\Release\ULIS3.dll" "ULIS3_FullBuildUE4_WinMSVCx64_Redist\redist\bin\x64\release\ULIS3.dll"

COPY /Y "ULIS3\scripts\UnrealEngine4\ULIS.Build.cs" "ULIS3_FullBuildUE4_WinMSVCx64_Redist\ULIS.Build.cs"