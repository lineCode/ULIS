set -e
cd "`dirname "$0"`"

## Call full setup & build for Xcode
if [ -f FullEmbeddedSetupAndBuild_Xcode.sh ]; then
    sh FullEmbeddedSetupAndBuild_Xcode.sh
fi

## cd to current script dir
cd "`dirname "$0"`"

## cd to root
cd ../../../../

## set utility variables
ROOT=$PWD

## bake distro directories
mkdir Redist
cd Redist

mkdir Include
cd Include
mkdir ULIS
mkdir boost_preprocessor
mkdir Little-CMS
mkdir glm
mkdir coal

cd ..
mkdir Lib
cd Lib
mkdir Mac
cd Mac
mkdir Xcode
cd Xcode
mkdir x64
cd x64
mkdir Release
mkdir Debug

cd ..
cd ..
cd ..
cd ..
cd ..

cp $ROOT\ULIS\Tools\EmbeddedDependencies\Coal\coal\Source\coal\Include $ROOT\Redist\Include\coal
cp $ROOT\ULIS\Tools\EmbeddedDependencies\glm\glm $ROOT\Redist\Include\glm
cp $ROOT\ULIS\Tools\EmbeddedDependencies\preprocessor\include $ROOT\Redist\Include\boost_preprocessor
cp $ROOT\ULIS\Tools\EmbeddedDependencies\Little-CMS\include $ROOT\Redist\Include\Little-CMS
cp $ROOT\ULIS\Source\ULIS\Include $ROOT\Redist\Include\ULIS

cp $ROOT\ULIS\Generated_Xcode\Debug\ULIS1.0d.lib $ROOT\Redist\Lib\Mac\Xcode\x64\Debug\ULIS1.0d.dylib
cp $ROOT\ULIS\Generated_Xcode\Release\ULIS1.0.lib $ROOT\Redist\Lib\Mac\Xcode\x64\Release\ULIS1.0.dylib
cp $ROOT\ULIS\Tools\EmbeddedDependencies\Little-CMS_Xcode\Debug\lcms2d.lib $ROOT\Redist\Lib\Mac\Xcode\x64\Debug\lcms2d.dylib
cp $ROOT\ULIS\Tools\EmbeddedDependencies\Little-CMS_Xcode\Release\lcms2.lib $ROOT\Redist\Lib\Mac\Xcode\x64\Release\lcms2.dylib

cp $ROOT\ULIS\Tools\Scripts\Unreal\ULIS.Build.cs $ROOT\ULIS.Build.cs

