cmake_minimum_required(VERSION 3.30)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "Vcpkg toolchain file")

project(RememberProgramGo_deeper VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(SDL3 CONFIG REQUIRED)
find_package(RmlUi CONFIG REQUIRED)
find_package(SDL3_image CONFIG REQUIRED)

set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

add_executable(RememberProgramGo_deeper)

file(GLOB_RECURSE RememberProgramGo_deeper_SOURCES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*inl"
        #UI
        "${CMAKE_CURRENT_SOURCE_DIR}/src/ui/*cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/ui/*h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/ui/*hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/ui/*inl"
        #CORE
        "${CMAKE_CURRENT_SOURCE_DIR}/src/core/*cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/core/*h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/core/*hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/core/*inl"
        #LIB SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/external/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/external/*.h"
)

target_sources(RememberProgramGo_deeper PRIVATE ${RememberProgramGo_deeper_SOURCES})

target_include_directories(RememberProgramGo_deeper PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/external
)


# Copy assets folder next to the executable after build
add_custom_command(
        TARGET RememberProgramGo_deeper
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:RememberProgramGo_deeper>/assets
)

#target_compile_definitions(RememberProgramGo_deeper PRIVATE
#
#)

target_link_libraries(RememberProgramGo_deeper PRIVATE
        SDL3::SDL3
        $<IF:$<TARGET_EXISTS:SDL3_image::SDL3_image-shared>,SDL3_image::SDL3_image-shared,SDL3_image::SDL3_image-static>
        RmlUi::RmlUi
)

# Add directories with any random loose .dlls or .libs here
target_link_directories(RememberProgramGo_deeper PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/lib
)
add_definitions(-DRMLUI_SDL_VERSION_MAJOR=3)

# Set configuration properties for Playground
if(MSVC)
    target_compile_options(RememberProgramGo_deeper PRIVATE
            /W3
            /MP # multithreaded build
            /WX # warnings as errors
            /ZI # program database for edit and continue
    )
else()
    target_compile_options(RememberProgramGo_deeper PRIVATE
            -Wall
            -Wextra
            -Wpedantic
    )
endif()

# Set Playground as the startup project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT RememberProgramGo_deeper)

# Filters
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" PREFIX "Source Files" FILES ${RememberProgramGo_deeper_SOURCES})

# Enable solution folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)







