# - Find SZ3 library
# Find the SZ3 includes and library
# This module defines
#  SZ3_INCLUDE_DIR: where to find SZ3 headers
#  SZ3_FOUND: if false, do not try to use SZ3
#  SZ3_VERSION: The found version of SZ3

find_path(SZ3_INCLUDE_DIR
  NAMES
    def.hpp
  PATHS
    /usr/local/include
    /usr/include
  PATH_SUFFIXES
    SZ3)
mark_as_advanced(SZ3_INCLUDE_DIR)

find_library(SZ3_LIBRARY
  NAMES SZ3 SZ3c
  PATHS /usr/local/lib /usr/lib)
mark_as_advanced(SZ3_LIBRARY)

if (SZ3_INCLUDE_DIR)
  if (EXISTS "${SZ3_INCLUDE_DIR}/version.hpp")
    file(STRINGS "${SZ3_INCLUDE_DIR}/version.hpp" _sz3_version REGEX "#define SZ3_VER[ \t]+\"[0-9]+\\.[0-9]+\\.[0-9]+\"")
    string(REGEX REPLACE ".*#define SZ3_VER[ \t]+\"([0-9]+\\.[0-9]+\\.[0-9]+)\".*" "\\1" SZ3_VERSION "${_sz3_version}")
    unset(_sz3_version)
  else ()
    set(SZ3_VERSION SZ3_VERSION-NOTFOUND)
  endif ()
endif ()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(SZ3
  REQUIRED_VARS SZ3_INCLUDE_DIR SZ3_LIBRARY 
  VERSION_VAR SZ3_VERSION)

if (SZ3_FOUND)
  set(SZ3_INCLUDE_DIR "${SZ3_INCLUDE_DIR}")
  set(SZ3_LIBRARY "${SZ3_LIBRARY}")
  if (NOT TARGET SZ3::SZ3)
    add_library(SZ3::SZ3 UNKNOWN IMPORTED)
    set_target_properties(SZ3::SZ3
      PROPERTIES
        IMPORTED_LOCATION "${SZ3_LIBRARY}"
        INTERFACE_INCLUDE_DIRECTORIES "${SZ3_INCLUDE_DIR}")
  endif ()
endif ()
