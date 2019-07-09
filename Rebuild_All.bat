@echo off
setlocal
pushd %~dp0

call Generate_All.bat
cd ULIS
cd Generated_VisualStudio_Solution_CLANG_LLVM
cmake --build . --config Release
cmake --build . --config Debug
cd ..
cd Generated_VisualStudio_Solution_MSVC
cmake --build . --config Release
cmake --build . --config Debug
cd ..
cd Generated_MinGW_Makefile_GCC
cd Release
cmake --build .
cd ..
cd Debug
cmake --build .
cd ..
cd ..