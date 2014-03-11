cmake_minimum_required(VERSION 2.6)

#Declaration du projet
project(KiroGame)

# set build directory
#set(dir build/)
#set(dir ${CMAKE_CURRENT_BINARY_DIR}/build/)
#set(dir ${CMAKE_BINARY_DIR}/build/)
#set(dir ${PROJECT_BINARY_DIR})

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${dir})
#set(CMAKE_BUILD_FILES_DIRECTORY ${dir})
# read only
#set(CMAKE_BUILD_DIRECTORY ${dir})
#set(CMAKE_BINARY_DIR  ${dir})
#set(CMAKE_CURRENT_BINARY_DIR  ${dir})
#set(CMAKE_PROJECT_BINARY_DIR  ${dir})


#set(EXECUTABLE_OUTPUT_PATH ${dir}/bin/${CMAKE_BUILD_TYPE})
set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})
set(EXECUTABLE_NAME KiroGame)

# Compilator configuration
#set de base kiroxas 
# -visual studio 2012
# -ubuntu clang 3.2
# -ubuntu gcc 4.8
# -mac gcc 4.8

# window choice
if(WIN32) # MSVC MSYS CYGWIN BORLAND
    message("Setting up for window system")
    set(CMAKE_CXX_FLAGS "-std=c++0x -Wall")
endif()

# linux choice
message("show variable " ${CMAKE_SYSTEM_NAME}) 
if(${CMAKE_SYSTEM_NAME} MATCHES "Linux") 
   message("Setting up for linux system")
   message("Setting up gcc for C++11 with libc++.")

   set(CMAKE_CXX_FLAGS "-std=c++0x -Wall")
   #set(CMAKE_CXX_FLAGS "-std=c++0x")
endif()

# mac choice
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
   message("Setting up for mac system")

    #gcc 4.8
    #set(CMAKE_CXX_FLAGS "-std=c++0x -stdlib=libc++")
    set(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++")

    # les deux qui fonctionne
    #set(CMAKE_CXX_FLAGS "-std=c++0x")
    #set(CMAKE_CXX_FLAGS "-std=c++11") 

    # clang 3.4

    #set(CMAKE_CXX_FLAGS "-std=c++0x -stdlib=libc++")
    #set(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++")

    ##bon
    #set(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++")
    ##set(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++ -Wall")
    # set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++")

    # Xcode
    #message("Setting up Xcode for C++11 with libc++.")
    #set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++0x")
    #set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")

    #message("Setting up Xcode for C++11 with libc++.")
    #set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++11")
    #set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
endif()

# sources files
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

# create binaries
add_executable(
${EXECUTABLE_NAME}
${source_file}
)

# add libraries dependencies
#Need SFML Library
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED system window graphics audio)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()
