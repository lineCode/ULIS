@echo off

if not exist "%~dp0ULIS\Tools\Scripts\Windows\Generate_MinGW_Makefiles.bat" goto Error_NotFound
call "%~dp0ULIS\Tools\Scripts\Windows\Generate_MinGW_Makefiles.bat" %*
exit /B %ERRORLEVEL%

:Error_NotFound
echo Generate_MinGW_Makefiles ERROR: The batch file does not appear to be located where it should.
pause
exit /B 1
