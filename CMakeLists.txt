cmake_minimum_required(VERSION 3.5)

project(Lum-lang CXX)

include(${CMAKE_SOURCE_DIR}/cmake/option.cmake)

# Modules
include(${CMAKE_SOURCE_DIR}/cmake/StaticAnalyse.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/Doxygen.cmake)


if (L-LANG_BUILD_COMPILER)
	add_subdirectory(LumC)
endif()