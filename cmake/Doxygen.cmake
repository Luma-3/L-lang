
# Doxygen
find_package(Doxygen REQUIRED)
add_custom_target(doc ALL
	COMMAND ${DOXYGEN_EXECUTABLE} Doxyfile
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
	COMMENT "Generating API documentation with Doxygen"
	VERBATIM
)