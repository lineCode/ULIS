@echo off
setlocal
pushd %~dp0

git submodule update --init ULIS/Tools/Submodules/ProjectDependencies/ProjectDependencies
call ULIS/Tools/Scripts/Windows/SetupHooks.bat
if not exist "VisualStudioProjectConfig.cmake" copy "ULIS\Tools\DefaultConfig.cmake" "VisualStudioProjectConfig.cmake"
if not exist "MinGWMakefefilesConfig.cmake" copy "ULIS\Tools\DefaultConfig.cmake" "MinGWMakefefilesConfig.cmake"
call ULIS/Tools/Scripts/Windows/ProjectDependencies.bat -d
pause
