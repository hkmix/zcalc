set(SOURCE_FILES
    evaluation_exception.cc
    parser.cc)

add_library(parser ${SOURCE_FILES})

target_include_directories(parser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})