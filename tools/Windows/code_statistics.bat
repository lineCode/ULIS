@echo off
setlocal
pushd %~dp0

cd ../../include
echo "Num lines in include/*.h"
powershell "dir -Recurse *.h | Get-Content | Measure-Object -Line"
echo "Num lines in include/*.cpp"
powershell "dir -Recurse *.cpp | Get-Content | Measure-Object -Line"
echo "Num lines in include/*.ipp"
powershell "dir -Recurse *.ipp | Get-Content | Measure-Object -Line"
cd ../source
echo "Num lines in source/*.h"
powershell "dir -Recurse *.h | Get-Content | Measure-Object -Line"
echo "Num lines in source/*.cpp"
powershell "dir -Recurse *.cpp | Get-Content | Measure-Object -Line"
echo "Num lines in source/*.ipp"
powershell "dir -Recurse *.ipp | Get-Content | Measure-Object -Line"
PAUSE
