@echo off
setlocal
pushd %~dp0

call Generate_VisualStudio_Solution_MSVC.bat
cd ULIS
cd Generated_VisualStudio_Solution_MSVC
cmake --build . --config Debug
cmake --build . --config Release