# General {{{
# ==============================================================================
# Require minimum version of CMake.
cmake_minimum_required(VERSION 2.8.6)
# ------------------------------------------------------------------------------
# Disable in-source builds.
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_DISABLE_SOURCE_CHANGES  ON)
SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake-modules")

if("${CMAKE_CURRENT_SOURCE_DIR}" STREQUAL "${CMAKE_CURRENT_BINARY_DIR}")
  message(SEND_ERROR "In-source builds are not allowed.")
endif()
# ------------------------------------------------------------------------------
# Declare project.
project("cca.cfd.LB" C CXX)
OPTION (Parallel "Enable parallel" off)

if(Parallel)
	set(CMAKE_CXX_COMPILER "mpiicpc")
	
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DParallel -mt_mpi ")
	
endif(Parallel)
#find_library (PETSC_MKL_INTEL_LP64_LIB mkl_intel_lp64 HINTS "/opt/intel/mkl" "/home/atanasoa/Programme/petsc-3.3-p7/-Xlinker" "/opt/intel/mpi-rt/4.1" "/opt/intel/impi/4.1.3.049/intel64/lib" "/usr/lib/gcc/x86_64-linux-gnu/4.7" "/lib/x86_64-linux-gnu" "/usr/lib/x86_64-linux-gnu" "/opt/intel/composer_xe_2013_sp1.0.080/compiler/lib/intel64" "/opt/intel/composer_xe_2013_sp1.0.080/mkl/lib/intel64" "/usr/lib/i386-linux-gnu" )
#find_library (PETSC_MKL_INTEL_THREAD_LIB mkl_intel_thread HINTS "/opt/intel/mkl" "/home/atanasoa/Programme/petsc-3.3-p7/-Xlinker" "/opt/intel/mpi-rt/4.1" "/opt/intel/impi/4.1.3.049/intel64/lib" "/usr/lib/gcc/x86_64-linux-gnu/4.7" "/lib/x86_64-linux-gnu" "/usr/lib/x86_64-linux-gnu" "/opt/intel/composer_xe_2013_sp1.0.080/compiler/lib/intel64" "/opt/intel/composer_xe_2013_sp1.0.080/mkl/lib/intel64" "/usr/lib/i386-linux-gnu" )
#find_library (PETSC_MKL_CORE_LIB mkl_core HINTS "/opt/intel/mkl" "/home/atanasoa/Programme/petsc-3.3-p7/-Xlinker" "/opt/intel/mpi-rt/4.1" "/opt/intel/impi/4.1.3.049/intel64/lib" "/usr/lib/gcc/x86_64-linux-gnu/4.7" "/lib/x86_64-linux-gnu" "/usr/lib/x86_64-linux-gnu" "/opt/intel/composer_xe_2013_sp1.0.080/compiler/lib/intel64" "/opt/intel/composer_xe_2013_sp1.0.080/mkl/lib/intel64" "/usr/lib/i386-linux-gnu" )
#find_library (PETSC_MKL_LAPACK_LIB mkl_lapack HINTS "/opt/intel/mkl" "/home/atanasoa/Programme/petsc-3.3-p7/-Xlinker" "/opt/intel/mpi-rt/4.1" "/opt/intel/impi/4.1.3.049/intel64/lib" "/usr/lib/gcc/x86_64-linux-gnu/4.7" "/lib/x86_64-linux-gnu" "/usr/lib/x86_64-linux-gnu" "/opt/intel/composer_xe_2013_sp1.0.080/compiler/lib/intel64" "/opt/intel/composer_xe_2013_sp1.0.080/mkl/lib/intel64" "/usr/lib/i386-linux-gnu" )
#find_library (PETSC_MKL_BLAS_LIB mkl_blas HINTS "/opt/intel/mkl" "/home/atanasoa/Programme/petsc-3.3-p7/-Xlinker" "/opt/intel/mpi-rt/4.1" "/opt/intel/impi/4.1.3.049/intel64/lib" "/usr/lib/gcc/x86_64-linux-gnu/4.7" "/lib/x86_64-linux-gnu" "/usr/lib/x86_64-linux-gnu" "/opt/intel/composer_xe_2013_sp1.0.080/compiler/lib/intel64" "/opt/intel/composer_xe_2013_sp1.0.080/mkl/lib/intel64" "/usr/lib/i386-linux-gnu" )
#find_library (BOOST_SYSTEM_LIB boost_system HINTS "/opt/intel/mkl" "/home/atanasoa/Programme/petsc-3.3-p7/-Xlinker" "/opt/intel/mpi-rt/4.1" "/opt/intel/impi/4.1.3.049/intel64/lib" "/usr/lib/gcc/x86_64-linux-gnu/4.7" "/lib/x86_64-linux-gnu" "/usr/lib/x86_64-linux-gnu" "/opt/intel/composer_xe_2013_sp1.0.080/compiler/lib/intel64" "/opt/intel/composer_xe_2013_sp1.0.080/mkl/lib/intel64" "/usr/lib/i386-linux-gnu" )
#find_library (BOOST_THEAD_LIB boost_thread HINTS "/opt/intel/mkl" "/home/atanasoa/Programme/petsc-3.3-p7/-Xlinker" "/opt/intel/mpi-rt/4.1" "/opt/intel/impi/4.1.3.049/intel64/lib" "/usr/lib/gcc/x86_64-linux-gnu/4.7" "/lib/x86_64-linux-gnu" "/usr/lib/x86_64-linux-gnu" "/opt/intel/composer_xe_2013_sp1.0.080/compiler/lib/intel64" "/opt/intel/composer_xe_2013_sp1.0.080/mkl/lib/intel64" "/usr/lib/i386-linux-gnu" )

# ------------------------------------------------------------------------------
# Issue deprecation errors for macros and functions.
set(CMAKE_ERROR_DEPRECATED ON)
# ------------------------------------------------------------------------------
# Be verbose and colorful.
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_COLOR_MAKEFILE   ON)
# ------------------------------------------------------------------------------
# Include the currently being processed both source and build directories.
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# ------------------------------------------------------------------------------
# Remove "lib" prefix for shared libraries (DLLs) on Windows.
if(WIN32)
  set(CMAKE_SHARED_LIBRARY_PREFIX "")
  set(CMAKE_SHARED_MODULE_PREFIX  "")
endif()
# ------------------------------------------------------------------------------
# Install to the current project by default.
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/../../"
                           CACHE
                           PATH
                           ""
                           FORCE)
endif()
# ==============================================================================
# }}} General

# Packages {{{
# ==============================================================================
# JNI {{{
# ==============================================================================
#find_package(JNI REQUIRED)

#include_directories(${JNI_INCLUDE_DIRS})
# ==============================================================================
# }}} JNI

# Threads {{{
# ==============================================================================
set(CMAKE_THREAD_PREFER_PTHREAD ON)

find_package(Threads REQUIRED)

if(NOT CMAKE_USE_PTHREADS_INIT)
  message(FATAL_ERROR "POSIX threads not found.")
endif()

add_definitions(-DTHREADSAFE -D_REENTRANT)

set(Threads_LIBRARIES ${CMAKE_THREAD_LIBS_INIT})
# ==============================================================================
# }}} Threads
# ==============================================================================
# }}} Packages

# Compilers {{{
# ==============================================================================
if(CMAKE_COMPILER_IS_GNUCC)
  set(COMPILER_IS_GCC TRUE)
  set(LINKER_IS_LD    TRUE)
endif()
# ------------------------------------------------------------------------------
if(CMAKE_COMPILER_IS_GNUCXX)
  set(COMPILER_IS_G++ TRUE)
  set(LINKER_IS_LD    TRUE)
endif()
# ==============================================================================
# }}} Compilers

# Flags {{{
# ==============================================================================
if(COMPILER_IS_GCC)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pipe")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wextra")
#  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wpedantic")
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fmessage-length=0")
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

  set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -fomit-frame-pointer")
  set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -funroll-loops")
endif()
# ------------------------------------------------------------------------------
if(COMPILER_IS_G++)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pipe")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")
#  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wpedantic")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmessage-length=0")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions")
#  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++98")

  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -fomit-frame-pointer")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -funroll-loops")
endif()
# ------------------------------------------------------------------------------
if(LINKER_IS_LD)
  if(WIN32)
    if(COMPILER_IS_G++)
      set(CMAKE_EXE_LINKER_FLAGS    "${CMAKE_EXE_LINKER_FLAGS}    -static-libstdc++")
      set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -static-libstdc++")
      set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -static-libstdc++")
    endif()

    set(CMAKE_EXE_LINKER_FLAGS    "${CMAKE_EXE_LINKER_FLAGS}    -static-libgcc")
    set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -static-libgcc")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -static-libgcc")

    set(CMAKE_EXE_LINKER_FLAGS    "${CMAKE_EXE_LINKER_FLAGS}    -static")
    set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -static")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -static")
  endif()
endif()
# ==============================================================================
# }}} Flags

# Targets {{{
# ==============================================================================
FIND_PACKAGE(PETSc REQUIRED)
FIND_PACKAGE(MKL)
FIND_PACKAGE(Boost 1.45.0 REQUIRED)
IF (Boost_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
    ADD_DEFINITIONS( "-DHAS_BOOST" )
ENDIF()
INCLUDE_DIRECTORIES(${PETSC_INCLUDES})
ADD_DEFINITIONS(${PETSC_DEFINITIONS})

include_directories("../../src")
include_directories("../../components/java")
include_directories(../../src/examples/kernel)
include_directories("../../components/c++")
include_directories(../../src/examples/iqn)

include("sources.cmake")

file(GLOB STENCIL_SOURCES ../../src/examples/cfd/lb/stencils/*.cpp)
file(GLOB LB_SOURCES  ../../src/examples/cfd/lb/*.cpp)
file(GLOB LB_PARALLEL_SOURCES  ../../src/examples/cfd/lb/parallelManagers/*.cpp)
file(GLOB COUPLING_SOURCES  ../../src/examples/cfd/lb/coupling/*.cpp)
file(GLOB KERNEL_SOURCES  ../../src/examples/kernel/*.cpp)
file(GLOB_RECURSE IQN_SOURCES  ../../src/examples/iqn/*.cpp)

include("sources.cmake")
set(CPP_FILES
#    ${PETSC_LIBRARIES}
    ${CPP_FILES}
    ${KERNEL_SOURCES}
    ${XML_SOURCES}
    ${IQN_SOURCES}
    ${LB_SOURCES}
    ${LB_PARALLEL_SOURCES}
    ${COUPLING_SOURCES}
   	${STENCIL_SOURCES}
)
include("targets.cmake")

target_link_libraries("cca.cfd.LB"
                      ${JNI_LIBRARIES}
                      ${Threads_LIBRARIES}
                      ${PETSC_LIBRARIES}
                      ${MKL_LIBRARIES}
                      iomp5)

install(TARGETS "cca.cfd.LB"
        ARCHIVE DESTINATION "lib"
        LIBRARY DESTINATION "lib"
        RUNTIME DESTINATION "bin")
# ==============================================================================
# }}} Targets
