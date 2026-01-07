cmake_minimum_required(VERSION 4.0)
project(RememberProgramGo_deeper)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
include_directories(CLAYMAN external/clay_man)
file(GLOB CLAYMAN_SRC external/clay_man/*.cpp)
include_directories(RAYLIB external/raylib)
file(GLOB CLAY_RAYLIB_SRC external/clay_man/include/raylib/clay_renderer_raylib.c)

# Fuentes del proyecto
file(GLOB SOURCES
        src/*.cpp
        src/ui/*.cpp
        src/ui/Screens/*.cpp
        src/ui/Widgets/*.cpp
        src/core/*.cpp
        src/world/*.cpp
        src/world/Systems/*.cpp
)


# Add executable
add_executable(yodacode
        ${SOURCES} ${CLAYMAN_SRC} ${CLAY_RAYLIB_SRC}
)

add_custom_command(
        TARGET yodacode
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:yodacode>/assets
)

# Include directories
target_include_directories(yodacode PRIVATE
        CLAYMAN
        RAYLIB
)

# Link directories (where the Raylib library is)
link_directories(${CMAKE_SOURCE_DIR}/libs/raylib)

# Link Raylib + system libraries
target_link_libraries(yodacode PRIVATE
        ${CMAKE_SOURCE_DIR}/libs/raylib/libraylib.a          # link Raylib
        winmm
        kernel32
        user32
        gdi32
        winspool
        shell32
        ole32
        oleaut32
        uuid
        comdlg32
        advapi32
)
