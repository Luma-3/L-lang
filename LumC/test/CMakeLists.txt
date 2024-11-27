include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest
  GIT_TAG        v1.15.2
)


FetchContent_MakeAvailable(googletest)

add_executable(tests
  test.cc
  TokenStreamTest.cc
)

target_link_libraries(tests
  gtest_main
  Utils
)

# target_include_directories(tests PRIVATE
#   ${LANG_COMPILER_DIR}/src
# )



add_test(
  NAME run_tests
  COMMAND tests
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
