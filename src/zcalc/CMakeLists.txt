set(SOURCE_FILES
    main.cc)

add_executable(zcalc ${SOURCE_FILES})
target_link_libraries(zcalc LINK_PUBLIC parser tokenizer)