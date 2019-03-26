@echo off
setlocal
pushd %~dp0

rmdir /S /Q ULIS\Generated_MinGW_Makefile_GCC
rmdir /S /Q ULIS\Generated_VisualStudio_Solution_CLANG_LLVM
rmdir /S /Q ULIS\Generated_VisualStudio_Solution_MSVC