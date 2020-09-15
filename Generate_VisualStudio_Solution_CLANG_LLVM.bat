@echo off

if not exist "%~dp0ULIS\Tools\Scripts\Windows\Generate_VisualStudio_Solution_CLANG_LLVM.bat" goto Error_NotFound
call "%~dp0ULIS\Tools\Scripts\Windows\Generate_VisualStudio_Solution_CLANG_LLVM.bat" %*
exit /B %ERRORLEVEL%

:Error_NotFound
echo Generate_VisualStudio_Solution_CLANG_LLVM ERROR: The batch file does not appear to be located where it should.
pause
exit /B 1
