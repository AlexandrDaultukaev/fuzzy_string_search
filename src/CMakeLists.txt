add_executable(ngram)
add_library(ngram_lib STATIC ngram/ngram.hpp)
set(INCLUDE_PATH ${PROJECT_SOURCE_DIR}/src/ngram)

target_sources(
    ngram
    PRIVATE
        ngram/ngram.cpp
)

include(CompileOptions)
set_compile_options(ngram)
set_compile_options(ngram_lib)

target_link_libraries(
    ngram
    PRIVATE
        ngram_lib
)