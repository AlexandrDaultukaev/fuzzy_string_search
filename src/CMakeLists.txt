add_library(ngram_lib STATIC ngram/ngram.hpp ngram/ngram.cpp)
set(INCLUDE_PATH ${PROJECT_SOURCE_DIR}/src)


include(CompileOptions)
set_compile_options(ngram_lib)

target_include_directories(
    ngram_lib
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
    PUBLIC
        ${INCLUDE_PATH}
)