cmake_minimum_required(VERSION 2.6)

#Declaration du projet

project(KiroGame)

set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})

#Need Boost Library
include_directories(${boost_include_dir})
link_directories(${boost_lib_dir})

include _directories(${opengl_include_path})

#Need SFML Library
include_directories(${sfml_include_dir})
link_directories(${sfml_lib_dir})

file(
GLOB_RECURSE
source_file
Characters/*
Input/*
Maze/*
Misc/*
"Rendering Engine/*"
main.cpp
)

add_executable(
KiroGame
${source_file}
)

target_link_libraries(
KiroGame
${boost_lib_name}
${sfml_lib_name}
)

