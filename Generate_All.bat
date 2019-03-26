@echo off
setlocal
pushd %~dp0

call Generate_MinGW_Makefile_GCC.bat
call Generate_VisualStudio_Solution_CLANG_LLVM.bat
call Generate_VisualStudio_Solution_MSVC.bat