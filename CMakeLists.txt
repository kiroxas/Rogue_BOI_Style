cmake_minimum_required(VERSION 2.6)

#Declaration du projet

project(KiroGame)

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

