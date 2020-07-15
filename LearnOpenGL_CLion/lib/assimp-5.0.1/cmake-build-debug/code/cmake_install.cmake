# Install script for directory: /Users/thomas/Downloads/assimp-5.0.1/code

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/Users/thomas/Downloads/assimp-5.0.1/cmake-build-debug/code/libassimpd.5.0.0.dylib"
    "/Users/thomas/Downloads/assimp-5.0.1/cmake-build-debug/code/libassimpd.5.dylib"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimpd.5.0.0.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimpd.5.dylib"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      execute_process(COMMAND "/usr/bin/install_name_tool"
        -id "/usr/local/lib/libassimpd.5.dylib"
        "${file}")
      execute_process(COMMAND /usr/bin/install_name_tool
        -delete_rpath "/Users/thomas/Downloads/assimp-5.0.1/cmake-build-debug/contrib/irrXML"
        "${file}")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -x "${file}")
      endif()
    endif()
  endforeach()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/Users/thomas/Downloads/assimp-5.0.1/cmake-build-debug/code/libassimpd.dylib")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimpd.dylib" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimpd.dylib")
    execute_process(COMMAND "/usr/bin/install_name_tool"
      -id "/usr/local/lib/libassimpd.5.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimpd.dylib")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/thomas/Downloads/assimp-5.0.1/cmake-build-debug/contrib/irrXML"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimpd.dylib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -x "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimpd.dylib")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xassimp-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp" TYPE FILE FILES
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/anim.h"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/aabb.h"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/ai_assert.h"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/camera.h"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/color4.h"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/color4.inl"
    "/Users/thomas/Downloads/assimp-5.0.1/cmake-build-debug/code/../include/assimp/config.h"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/defs.h"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/Defines.h"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/cfileio.h"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/light.h"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/material.h"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/material.inl"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/matrix3x3.h"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/matrix3x3.inl"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/matrix4x4.h"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/matrix4x4.inl"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/mesh.h"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/pbrmaterial.h"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/postprocess.h"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/quaternion.h"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/quaternion.inl"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/scene.h"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/metadata.h"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/texture.h"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/types.h"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/vector2.h"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/vector2.inl"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/vector3.h"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/vector3.inl"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/version.h"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/cimport.h"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/importerdesc.h"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/Importer.hpp"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/DefaultLogger.hpp"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/ProgressHandler.hpp"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/IOStream.hpp"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/IOSystem.hpp"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/Logger.hpp"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/LogStream.hpp"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/NullLogger.hpp"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/cexport.h"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/Exporter.hpp"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/DefaultIOStream.h"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/DefaultIOSystem.h"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/ZipArchiveIOSystem.h"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/SceneCombiner.h"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/fast_atof.h"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/qnan.h"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/BaseImporter.h"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/Hash.h"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/MemoryIOWrapper.h"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/ParsingUtils.h"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/StreamReader.h"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/StreamWriter.h"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/StringComparison.h"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/StringUtils.h"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/SGSpatialSort.h"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/GenericProperty.h"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/SpatialSort.h"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/SkeletonMeshBuilder.h"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/SmoothingGroups.h"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/SmoothingGroups.inl"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/StandardShapes.h"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/RemoveComments.h"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/Subdivision.h"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/Vertex.h"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/LineSplitter.h"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/TinyFormatter.h"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/Profiler.h"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/LogAux.h"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/Bitmap.h"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/XMLTools.h"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/IOStreamBuffer.h"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/CreateAnimMesh.h"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/irrXMLWrapper.h"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/BlobIOSystem.h"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/MathFunctions.h"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/Macros.h"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/Exceptional.h"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/ByteSwapper.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xassimp-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp/Compiler" TYPE FILE FILES
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/Compiler/pushpack1.h"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/Compiler/poppack1.h"
    "/Users/thomas/Downloads/assimp-5.0.1/code/../include/assimp/Compiler/pstdint.h"
    )
endif()

