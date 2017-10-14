# Use pkg-config
find_package(PkgConfig QUIET)
if(PKG_CONFIG_FOUND)
  pkg_search_module(PC_POPT QUIET popt)
endif()

# Find the include directory
find_path(
  POPT_INCLUDE_PATH
  NAMES popt.h
  HINTS
  ${PC_POPT_INCLUDEDIR}
  ${PC_POPT_INCLUDE_DIRS}
  DOC "Path containing popt.h")

# Find the library directory
find_library(
  POPT_LIBRARY
  NAMES popt
  HINTS
  ${PC_POPT_LIBRARYDIR}
  ${PC_POPT_LIBRARY_DIRS}
  DOC "Path to libpopt.so, libpopt.dylib or so on")

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
  POPT
  REQUIRED_VARS POPT_INCLUDE_PATH POPT_LIBRARY
  VERSION_VAR PC_POPT_VERSION)
