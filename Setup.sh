#!/bin/sh

set -e
cd "`dirname "$0"`"

git submodule update --init ULIS/Tools/Submodules/ProjectDependencies/ProjectDependencies
if [ ! -f Xcode_Config.cmake ]; then
     cp "ULIS/Tools/DefaultConfig.cmake" "Xcode_Config.cmake"
fi

if [ ! -f Ubuntu_Config.cmake ]; then
     cp "ULIS/Tools/DefaultConfig.cmake" "Ubuntu_Config.cmake"
fi