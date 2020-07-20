## Dependencies
Dependencies are redistributed directly within the repository under the 3rdparty directory.

|Dependency         |Link                                                           |License            |Status                                             |
|-------------------|---------------------------------------------------------------|-------------------|---------------------------------------------------|
|clip               |https://github.com/dacap/clip                                  |MIT                |Keep for now                                       |
|cppfs              |https://github.com/cginternals/cppfs                           |MIT                |Remove when upgrading to C++17                     |
|eigen              |https://gitlab.com/libeigen/eigen                              |MPL2               |Remove and implement Mat8x8                        |
|FeatureDetector    |https://github.com/Mysticial/FeatureDetector                   |CC0 1.0 Universal  |Remove and implement custom device info fetching   |
|freetype2          |https://github.com/aseprite/freetype2                          |FTL ( BSD-like )   |Keep                                               |
|glm                |https://github.com/g-truc/glm                                  |MIT                |Remove and implement vec and mat types             |
|Little-CMS         |https://github.com/mm2/Little-CMS                              |MIT                |Keep                                               |
|OCL-SDK            |https://github.com/GPUOpen-LibrariesAndSDKs/OCL-SDK/releases   |-                  |No need to track as dependency especially for MacOS|
|static_math        |https://github.com/Morwenn/static_math                         |MIT                |Remove and implement basic static operations       |
|stb_image          |https://github.com/nothings/stb                                |MIT                |Keep for now                                       |
|stb_image_write    |https://github.com/nothings/stb                                |MIT                |Keep for now                                       |
|VCL                |https://github.com/vectorclass/version1                        |Apache 2.0         |Remove and implement raw SIMD calls                |

Additionaly, these libraries can be used with ULIS to test samples programs or build the python binding:

        Qt5.x
        Python3.x