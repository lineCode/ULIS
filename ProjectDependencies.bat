@echo off

if not exist "%~dp0ULIS\Tools\Scripts\Windows\ProjectDependencies.bat" goto Error_NotFound
call "%~dp0ULIS\Tools\Scripts\Windows\ProjectDependencies.bat" %*
exit /B %ERRORLEVEL%

:Error_NotFound
echo ProjectDependencies ERROR: The batch file does not appear to be located where it should.
pause
exit /B 1
