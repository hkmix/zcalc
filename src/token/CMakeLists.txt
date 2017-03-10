set(SOURCE_FILES
    token.cc
    tokenizer.cc
    tokenizer_exception.cc)

add_library(tokenizer ${SOURCE_FILES})

target_include_directories(tokenizer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})