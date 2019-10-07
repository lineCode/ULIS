set -e
cd "`dirname "$0"`"

## cd to root
cd ../../../../

## setup repository
if [ -f setup.sh ]; then
    sh setup.sh
fi

## set utility variables
ROOT=$PWD
EMB=$ROOT/ULIS/Tools/EmbeddedDependencies/
cd ULIS/Tools/

## make EmbeddedDependencies dir if not exist
if [ ! -d EmbeddedDependencies ]; then 
	mkdir EmbeddedDependencies
fi
cd EmbeddedDependencies

## clone dependencies
git clone https://github.com/boostorg/preprocessor
git clone https://github.com/g-truc/glm
git clone https://github.com/Robot-Fromage/Coal
git clone https://github.com/Robot-Fromage/Little-CMS

## build dependencies
mkdir Little-CMS_Xcode
cd Little-CMS_Xcode
cmake -G "Xcode" ../Little-CMS/.
cmake --build . --config Debug
cmake --build . --config Release

## cd to root again and write config for Xcode
cd $ROOT
rm Xcode_Config.cmake
echo "SET( ULIS_BOOST_INCLUDE_PATH        \"$EMBpreprocessor/include/\" )"
echo "SET( ULIS_COAL_INCLUDE_PATH         \"$EMBcoal/coal/Source/coal/Include/\" )"
echo "SET( ULIS_BUILD_SHARED              OFF )"
echo "SET( ULIS_BUILD_TESTS               OFF )"
echo "SET( ULIS_BUILD_GUIS                OFF )"
echo "SET( ULIS_QT_CMAKE_PATH             \"default\" )"
echo "SET( ULIS_GLM_INCLUDE_PATH          \"$EMBglm/\" )"
echo "SET( ULIS_LCMS2_INCLUDE_PATH        \"$EMBLittle-CMS/include/\" )"
echo "SET( ULIS_LCMS2_DEBUG_LIB_PATH      \"$EMBLittle-CMS_Xcode/Debug/lcms2d.a\" )"
echo "SET( ULIS_LCMS2_RELEASE_LIB_PATH    \"$EMBLittle-CMS_Xcode/Release/lcms2.a\" )"

## generate project files for Xcode
if [ -f Generate_Xcode.sh ]; then
    sh Generate_Xcode.sh
fi

## build Xcode
cd ULIS/Generated_Xcode
cmake --build . --config Debug
cmake --build . --config Release
