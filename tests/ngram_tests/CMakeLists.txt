set(SRC_PATH {CMAKE_SOURCE_DIR}/src)

# add_executable(
#     sw_tests
#     self-written_tests.cpp
# )

enable_testing()

add_executable(
    ngram_tests
    ngram_tests.cpp
)

target_include_directories(
    ngram_tests
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
    PUBLIC
        ${SRC_PATH}
)




target_link_libraries(
    ngram_tests
    ngram_lib
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(ngram_tests)