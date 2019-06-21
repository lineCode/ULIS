@echo off
setlocal
pushd %~dp0

call Clean_All.bat
call Generate_All.bat
cd ULIS
cd Generated_MinGW_Makefile_GCC
cd Debug
cmake --build .
cd ..
cd Release
cmake --build .
cd ..
cd ..
cd Generated_VisualStudio_Solution_CLANG_LLVM
cmake --build . --config Release
cmake --build . --config Debug
cd ..
cd Generated_VisualStudio_Solution_MSVC
cmake --build . --config Release
cmake --build . --config Debug
cd ..
cd ..