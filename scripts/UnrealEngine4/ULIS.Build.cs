// Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
using System;
using System.IO;
using UnrealBuildTool;

public class ULIS : ModuleRules
{
    public ULIS( ReadOnlyTargetRules Target ) : base( Target )
    {
        Type = ModuleType.External;
        if (Target.Platform == UnrealTargetPlatform.Win64 ||
            Target.Platform == UnrealTargetPlatform.Win32 )
        {
            string IncludeBase                      = Path.Combine( ModuleDirectory, "Redist", "Include" );
            PublicSystemIncludePaths.AddRange(
                new string[] {
                      Path.Combine( IncludeBase, "clip" )
                    , Path.Combine( IncludeBase, "cppfs", "source", "cppfs", "include" )
                    , Path.Combine( IncludeBase, "eigen", "Eigen" )
                    , Path.Combine( IncludeBase, "FeatureDetector" )
                    , Path.Combine( IncludeBase, "freetype2", "include" )
                    , Path.Combine( IncludeBase, "glm" )
                    , Path.Combine( IncludeBase, "Little-CMS", "include" )
                    , Path.Combine( IncludeBase, "OCL-SDK", "include" )
                    , Path.Combine( IncludeBase, "static_math", "include" )
                    , Path.Combine( IncludeBase, "stb" )
                    , Path.Combine( IncludeBase, "ULIS3" )
                    , Path.Combine( IncludeBase, "VCL" )
                }
            );

            string LibBase          = Path.Combine( ModuleDirectory, "Redist", "Lib", "Win", "MSVC", "x64" );
            string LibBaseRelease   = Path.Combine( LibBase, "Release" );
            string LibBaseDebug     = Path.Combine( LibBase, "Debug" );
            string LibBaseFull = LibBaseRelease;

            string ULIS_LibName         = "ULIS3";
            string freetype2_LibName    = "freetype";
            string cppfs_LibName        = "cppfs";
            string clip_LibName         = "clip";
            string LittleCMS_LibName    = "lcms2";

            if (Target.Configuration == UnrealTargetConfiguration.Debug && Target.bDebugBuildsActuallyUseDebugCRT) {
                    ULIS_LibName        += "d";
                    freetype2_LibName   += "d";
                    cppfs_LibName       += "d";
                    clip_LibName        += "d";
                    LittleCMS_LibName   += "d";
                    LibBaseFull = LibBaseDebug;
            }

            PublicAdditionalLibraries.AddRange(
                new string[] {
                      Path.Combine( LibBaseFull, ULIS_LibName ) + ".lib"
                    , Path.Combine( LibBaseFull, LittleCMS_LibName ) + ".lib"
                    , Path.Combine( LibBaseFull, freetype2_LibName ) + ".lib"
                    , Path.Combine( LibBaseFull, cppfs_LibName ) + ".lib"
                    , Path.Combine( LibBaseFull, clip_LibName ) + ".lib"
                }
            );

            PublicDefinitions.Add("WITH_ULIS=1");
        }
        else if ( Target.Platform == UnrealTargetPlatform.Mac )
        {
            string IncludeBase                      = Path.Combine( ModuleDirectory, "Redist", "Include" );
            PublicSystemIncludePaths.AddRange(
                new string[] {
                      Path.Combine( IncludeBase, "clip" )
                    , Path.Combine( IncludeBase, "cppfs", "source", "cppfs", "include" )
                    , Path.Combine( IncludeBase, "eigen", "Eigen" )
                    , Path.Combine( IncludeBase, "FeatureDetector" )
                    , Path.Combine( IncludeBase, "freetype2", "include" )
                    , Path.Combine( IncludeBase, "glm" )
                    , Path.Combine( IncludeBase, "Little-CMS", "include" )
                    , Path.Combine( IncludeBase, "OCL-SDK", "include" )
                    , Path.Combine( IncludeBase, "static_math", "include" )
                    , Path.Combine( IncludeBase, "stb" )
                    , Path.Combine( IncludeBase, "ULIS3" )
                    , Path.Combine( IncludeBase, "VCL" )
                }
            );

            string LibBase          = Path.Combine( ModuleDirectory, "Redist", "Lib", "Mac", "Xcode", "x64" );
            string LibBaseRelease   = Path.Combine( LibBase, "Release" );
            string LibBaseDebug     = Path.Combine( LibBase, "Debug" );
            string LibBaseFull = LibBaseRelease;
            
            string ULIS_LibName         = "libULIS3";
            string freetype2_LibName    = "libfreetype";
            string cppfs_LibName        = "libcppfs";
            string clip_LibName         = "libclip";
            string LittleCMS_LibName    = "liblcms2";

            if (Target.Configuration == UnrealTargetConfiguration.Debug && Target.bDebugBuildsActuallyUseDebugCRT) {
                    ULIS_LibName        += "d";
                    freetype2_LibName   += "d";
                    cppfs_LibName       += "d";
                    clip_LibName        += "d";
                    LittleCMS_LibName   += "d";
                    LibBaseFull = LibBaseDebug;
            }

            PublicAdditionalLibraries.AddRange(
                new string[] {
                      Path.Combine( LibBaseFull, ULIS_LibName ) + ".a"
                    , Path.Combine( LibBaseFull, LittleCMS_LibName ) + ".a"
                    , Path.Combine( LibBaseFull, freetype2_LibName ) + ".a"
                    , Path.Combine( LibBaseFull, cppfs_LibName ) + ".a"
                    , Path.Combine( LibBaseFull, clip_LibName ) + ".a"
                }
            );

            PublicDefinitions.Add("WITH_ULIS=1");
        }
        else // unsupported platform
        {
            PublicDefinitions.Add("WITH_ULIS=0");
        }
    }
}

