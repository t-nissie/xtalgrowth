#-*-CMake-*- for xtalgrowth
##
cmake_minimum_required(VERSION 3.5...4.2)
enable_testing()   # Put it BEFORE add_subdirectory(s).
project(xtalgrowth C)
add_subdirectory(src)
install(FILES xtalgrowth.1 DESTINATION share/man/man1)
install(FILES index.en.html
              index.es.html
              index.ja.html
              COPYING style.css favicon.ico README.md
                          DESTINATION share/doc/xtalgrowth)
install(DIRECTORY figures DESTINATION share/doc/xtalgrowth)
