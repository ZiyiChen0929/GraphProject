cmake_minimum_required(VERSION 3.10)

# set the project name
project(GraphProject)

# add the executable
add_executable(search-cli main.c search.c search.h stats.c stats.h)