# General {{{
# ==============================================================================
# Require minimum version of CMake.
cmake_minimum_required(VERSION 2.8.6)
# ------------------------------------------------------------------------------
# Disable in-source builds.
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_DISABLE_SOURCE_CHANGES  ON)

if("${CMAKE_CURRENT_SOURCE_DIR}" STREQUAL "${CMAKE_CURRENT_BINARY_DIR}")
  message(SEND_ERROR "In-source builds are not allowed.")
endif()
# ------------------------------------------------------------------------------
# Install to the current project by default.
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}" CACHE PATH "")
# ==============================================================================
# }}} General
set(PETSC_EXECUTABLE_RUNS ON)
set(MKL_DIR "/lrz/sys/intel/mkl110u3")
add_subdirectory(cmake/cca.cfd.CouplingDriver)
add_subdirectory(cmake/cca.cfd.UekermannDriver)
add_subdirectory(cmake/cca.cfd.LB)
add_subdirectory(cmake/cca.cfd.NS)
