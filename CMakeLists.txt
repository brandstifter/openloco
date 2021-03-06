
# ----------------------------------------------------------------------------
# project setup
# ----------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.4.3)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/Modules)
include(${CMAKE_SOURCE_DIR}/cmake/Modules/unit_test.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/Modules/testfile_runner.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/Modules/coverage_build_type.cmake)

project(openloco C CXX)

# ----------------------------------------------------------------------------
# Compiler settings
# ----------------------------------------------------------------------------

add_definitions(-std=c++17)
add_definitions(-g)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message("-- HOST_SYSTEM")
message("--    name:            ${CMAKE_HOST_SYSTEM_NAME}")
message("--    version:         ${CMAKE_HOST_SYSTEM_VERSION}")
message("--    processor:       ${CMAKE_HOST_SYSTEM_PROCESSOR}")
message("--    system:          ${CMAKE_HOST_SYSTEM}")

message("-- COMPILER")
message("--    Build type:      ${CMAKE_BUILD_TYPE}")
message("--    Generator:       ${CMAKE_GENERATOR}")
message("--    C compiler:      ${CMAKE_C_COMPILER_ID}")
message("--    C++ compiler:    ${CMAKE_CXX_COMPILER_ID}")

# ----------------------------------------------------------------------------
# Include / Link directories
# ----------------------------------------------------------------------------

include_directories(
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

# ----------------------------------------------------------------------------
# Find packages
# ----------------------------------------------------------------------------

message("-- LIBRARIES")

if(Win32)
	include_directories("C:/msys2/usr/include")
	link_directories("C:/msys2/usr/lib")

	set(GTEST_ROOT "C:/Program Files (x86)/googletest-distribution")
	list(APPEND CMAKE_STATIC_LIBRARY_SUFFIX ".a")
endif()


find_package(Threads REQUIRED)
    message("--    PThreads found: ${THREADS_FOUND}")

find_package(GTest REQUIRED pthread)
    message("--    GTest found:    ${GTEST_FOUND}")
    include_directories(${GTEST_INCLUDE_DIRS})

find_package(Boost COMPONENTS system thread program_options REQUIRED)
#	include_directories(${BOOST_INCLUDEDIR})
#	link_directories(${BOOST_LIBRARYDIR})


# see: http://llvm.org/docs/CMake.html#embedding-llvm-in-your-project
# TODO: put LLVM_CONFIG_DIR into CMAKE_PREFIX_PATH

set(LLVM_DIR "/opt/local/libexec/llvm-6.0/")
find_package(LLVM 6.0 REQUIRED CONFIG)
    message("-- LLVM")
    message("--    LLVM version:   ${LLVM_VERSION_BASE_STRING}")
    message("--    Target Triple:  ${LLVM_HOST_TARGET}")

    # include_directories(${LLVM_INCLUDE_DIRS})
    # add_definitions(${LLVM_DEFINITIONS})
    # link_directories(${LLVM_LIBRARY_DIRS})
    llvm_map_components_to_libnames($OPENLOCO_LLVM_LIBS support core irreader)
    # all-targets analysis asmparser asmprinter bitreader bitwriter codegen core debuginfocodeview debuginfodwarf debuginfomsf debuginfopdb globalisel instcombine ipa ipo instrumentation irreader libdriver linker lto mc mcdisassembler mcparser objcarcopts object option profiledata scalaropts selectiondag support tablegen target transformutils vectorize windowsmanifest

    #set(CMAKE_PREFIX_PATH "/Users/tb/usr/Qt/5.11.3/clang_64")
    #find_package(Qt5 COMPONENTS Core REQUIRED)
    #        message("-- Qt ")

# ----------------------------------------------------------------------------
# CTEST CDASH
# ----------------------------------------------------------------------------

include(CTest)
enable_testing()


# ----------------------------------------------------------------------------
# dive into the code
# ----------------------------------------------------------------------------

message("-- Configuring begin")

add_subdirectory(source)

message("-- Configuring end")
