This ULIS.Build.cs file can be used to turn the ULIS3 library into an UnrealEngine4 third party library Module. Simply make a distribution with the built binaries and includes, along with the required dependencies and copy the build.cs file to make a ThirdParty module.  
First, copy `FullBuildUE4_WinMSVCx64.bat` next to the root of the ULIS3 repository. Then launch `FullBuildUE4_WinMSVCx64.bat`.  
You should obtain this directory tree:
```
    •
    |_ ULIS3
    |_ FullBuildUE4_WinMSVCx64.bat
    |_ ULIS3_FullBuildUE4_WinMSVCx64_Redist
       |_ Generated_VisualStudio_Solution_MSVC
       |_ ULIS.Build.cs
       |_ redist
```
Copy both redist folder and ULIS.Build.cs script in a folder named `ULIS` under the plugins source for your C++ UE4 project.