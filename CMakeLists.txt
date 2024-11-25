cmake_minimum_required(VERSION 3.5)

project(L-lang CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES src/*.cc)
file(GLOB_RECURSE HEADERS include/*.h)

include_directories(include)

add_compile_options(-Wall -Wextra -Wpedantic -Werror)

add_library(L-lang_lib STATIC ${SOURCES})

target_include_directories(L-lang_lib PRIVATE include)

add_executable(L-lang app/main.cc)

target_link_libraries(L-lang PRIVATE L-lang_lib)


# Doxygen
find_package(Doxygen REQUIRED)
add_custom_target(doc ALL
	COMMAND ${DOXYGEN_EXECUTABLE} Doxyfile
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
	COMMENT "Generating API documentation with Doxygen"
	VERBATIM
)

# cppcheck
find_program(CPPCHECK_EXECUTABLE cppcheck)
if (CPPCHECK_EXECUTABLE)
	add_custom_target(cppcheck
		COMMAND ${CPPCHECK_EXECUTABLE} --enable=all --inconclusive --force --inline-suppr --quiet --std=c++20 ${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/include
		WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
		COMMENT "Running cppcheck"
		VERBATIM
	)
endif() 


# clang-tidy

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_program(CLANG_TIDY_EXECUTABLE clang-tidy)
if (CLANG_TIDY_EXECUTABLE)
	add_custom_target(clang-tidy
		COMMAND ${CLANG_TIDY_EXECUTABLE} -p ${CMAKE_BINARY_DIR} ${SOURCES} ${HEADERS}
		WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
		COMMENT "Running clang-tidy"
		VERBATIM
	)
endif()

# tests
enable_testing()
add_subdirectory(test)
