# Projects Settings
cmake_minimum_required (VERSION 3.1)
project (COMP371)

# The main executable
include_directories(src)
add_executable(main
        src/cpp/textures_practice.cpp
        src/cpp/shader.cpp
        src/cpp/texture.cpp
        src/cpp/camera.cpp
        )
set_property(TARGET main PROPERTY CXX_STANDARD 11)
target_compile_options(main PRIVATE -Wall)

# stb library
include_directories(lib)
add_executable(stbi
        lib/stb/stb_image.cpp
        lib/stb/stb_image.h)
set_property(TARGET stbi PROPERTY CXX_STANDARD 11)
target_compile_options(stbi PRIVATE -Wall)

# assets
include_directories(assets/textures)

# glad
add_subdirectory(lib/glad EXCLUDE_FROM_ALL)
target_link_libraries(main PRIVATE glad)

# glfw
add_subdirectory(lib/glfw EXCLUDE_FROM_ALL)
target_link_libraries(main PRIVATE glfw)

## glew
#add_definitions(-DGLEW_STATIC)
#add_subdirectory(lib/glew EXCLUDE_FROM_ALL)
#target_link_libraries(main PRIVATE libglew_static)

# glm
add_subdirectory(lib/glm EXCLUDE_FROM_ALL)
target_link_libraries(main PRIVATE glm)