#-*-CMake-*- for xtalgrowth
##
cmake_minimum_required(VERSION 3.5)
enable_testing()   # Put it BEFORE add_subdirectory(s).
project(xtalgrowth C)
add_subdirectory(src)
install(FILES xtalgrowth.1 DESTINATION share/man/man1)
