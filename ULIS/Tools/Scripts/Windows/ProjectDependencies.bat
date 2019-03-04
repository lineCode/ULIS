@echo off

:: Ensure local scope
setlocal

:: Ensure current dir
pushd %~dp0

:: CD 2 steps up
cd ../../

set "SCRIPT_PATH=Submodules/ProjectDependencies/ProjectDependencies/ProjectDependencies.py"

if not exist %SCRIPT_PATH%              goto :no_script
call python3 -c "import colorama"   ||  goto :python3_error
call python3 %SCRIPT_PATH% %*       ||  goto :script_error
goto :EOF

:no_script
echo Warning: ProjectDependencies.py not found
goto :EOF

:python3_error
echo Error: could not find python3.
echo Make sure it is accessible from environment variables
echo Make sure required modules are installed
goto :EOF

:script_error
echo Error: ProjectDependencies.py, found errors
goto :EOF
