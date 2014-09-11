cmake_minimum_required(VERSION 2.6)

#Declaration du projet

project(KiroGame)

set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})
set(EXECUTABLE_NAME KiroGame)
set(CMAKE_CXX_FLAGS "-std=c++0x -Wall -O2")

file(
GLOB_RECURSE
source_file
Characters/*
Input/*
Maze/*
Misc/*
"Rendering Engine/*"
Views/*
Level.cpp
main.cpp
)

add_executable(
${EXECUTABLE_NAME}
${source_file}
)

#Need SFML Library
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED system window graphics audio)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()



