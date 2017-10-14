#-*-Cmake-*- for xtalgrowth
##
cmake_minimum_required(VERSION 3.9)
project(xtalgrowth C)
add_subdirectory(src)
install(FILES xtalgrowth.1 DESTINATION share/man/man1)
