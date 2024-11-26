
add_subdirectory(src/utils)

add_executable(LumC ${L-LANG_COMPILER_MAIN})
target_link_libraries(LumC PRIVATE Utils)

# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

if (BUILD_TESTS)
	enable_testing()
	add_subdirectory(test)
endif()