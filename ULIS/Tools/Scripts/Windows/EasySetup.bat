@echo off

:: Ensure local scope
setlocal

:: Ensure current dir
pushd %~dp0

:: diagnosis
call diagnosis.bat

:: CD 3 steps up to root
cd ../../../../
call setup.bat
cd ULIS/Tools/EmbeddedDependencies/
git clone https://github.com/boostorg/preprocessor
git clone https://github.com/g-truc/glm
git clone https://github.com/Robot-Fromage/Coal

pause
