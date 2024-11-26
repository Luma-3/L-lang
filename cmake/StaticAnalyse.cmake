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

find_program(CLANG_TIDY_EXECUTABLE clang-tidy)
if (CLANG_TIDY_EXECUTABLE)
	add_custom_target(clang-tidy
		COMMAND ${CLANG_TIDY_EXECUTABLE} -p ${CMAKE_BINARY_DIR} ${SOURCES} ${HEADERS}
		WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
		COMMENT "Running clang-tidy"
		VERBATIM
	)
endif()