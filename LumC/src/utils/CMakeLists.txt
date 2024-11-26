set(UTILS_SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/TokenStream.cc
)

add_library(Utils STATIC ${UTILS_SOURCES})
target_include_directories(Utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})