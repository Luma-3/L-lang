
include(${CMAKE_CURRENT_SOURCE_DIR}/Doxygen.cmake)

add_subdirectory(src/utils)
add_subdirectory(src/lexer)

add_executable(LumC ${L-LANG_COMPILER_MAIN})
target_link_libraries(LumC PRIVATE Utils Lexer)
target_include_directories(LumC PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

if (BUILD_TESTS)
	enable_testing()
	add_subdirectory(test)
endif()