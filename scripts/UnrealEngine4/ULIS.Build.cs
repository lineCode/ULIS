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
            string IncludeBase                      = Path.Combine( ModuleDirectory, "redist", "include" );
            PublicSystemIncludePaths.AddRange(
                new string[] {
                      Path.Combine( IncludeBase, "ULIS3" )
                    , Path.Combine( IncludeBase, "glm" )
                }
            );

            string LibBase          = Path.Combine( ModuleDirectory, "redist", "lib" );
            string ULIS_LibName         = "ULIS3";

            if (Target.Configuration == UnrealTargetConfiguration.Debug && Target.bDebugBuildsActuallyUseDebugCRT) {
                    ULIS_LibName        += "d";
            }

            PublicAdditionalLibraries.AddRange(
                new string[] {
                      Path.Combine( LibBase, ULIS_LibName ) + ".lib"
                }
            );

            PublicDefinitions.Add("WITH_ULIS=1");
            PublicDefinitions.Add("ULIS3_DYNAMIC_LIBRARY");
        }
        else if ( Target.Platform == UnrealTargetPlatform.Mac )
        {
            string IncludeBase                      = Path.Combine( ModuleDirectory, "redist", "include" );
            PublicSystemIncludePaths.AddRange(
                new string[] {
                      Path.Combine( IncludeBase, "ULIS3" )
                    , Path.Combine( IncludeBase, "glm" )
                }
            );

            string LibBase          = Path.Combine( ModuleDirectory, "redist", "lib" );
            string ULIS_LibName         = "ULIS3";

            if (Target.Configuration == UnrealTargetConfiguration.Debug && Target.bDebugBuildsActuallyUseDebugCRT) {
                    ULIS_LibName        += "d";
            }

            PublicAdditionalLibraries.AddRange(
                new string[] {
                      Path.Combine( LibBase, ULIS_LibName ) + ".a"
                }
            );

            PublicDefinitions.Add("WITH_ULIS=1");
            PublicDefinitions.Add("ULIS3_DYNAMIC_LIBRARY");
        }
        else // unsupported platform
        {
            PublicDefinitions.Add("WITH_ULIS=0");
        }
    }
}

