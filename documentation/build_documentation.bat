@echo off

:: Ensure local scope
setlocal

:: Ensure current dir
pushd %~dp0

:: CD to root
cd ..

doxygen %~dp0Doxyfile
copy /Y "documentation\doc.png"           "documentation\ULIS3\html\doc.png"
copy /Y "documentation\folderclosed.png"  "documentation\ULIS3\html\folderclosed.png"
copy /Y "documentation\folderopen.png"    "documentation\ULIS3\html\folderopen.png"
