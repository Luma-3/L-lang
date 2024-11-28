set(LEXER_SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/Lexer.cc
)

add_library(Lexer STATIC ${LEXER_SOURCES})
target_link_libraries(Lexer PRIVATE Utils)
