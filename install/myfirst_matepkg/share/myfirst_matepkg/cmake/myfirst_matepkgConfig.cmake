# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_myfirst_matepkg_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED myfirst_matepkg_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(myfirst_matepkg_FOUND FALSE)
  elseif(NOT myfirst_matepkg_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(myfirst_matepkg_FOUND FALSE)
  endif()
  return()
endif()
set(_myfirst_matepkg_CONFIG_INCLUDED TRUE)

# output package information
if(NOT myfirst_matepkg_FIND_QUIETLY)
  message(STATUS "Found myfirst_matepkg: 0.0.0 (${myfirst_matepkg_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'myfirst_matepkg' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${myfirst_matepkg_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(myfirst_matepkg_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${myfirst_matepkg_DIR}/${_extra}")
endforeach()
