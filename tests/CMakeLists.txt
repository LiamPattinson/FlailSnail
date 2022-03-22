set(${PROJECT_NAME}_C_TEST_FILES 
    src/c_test.c
)

set(${PROJECT_NAME}_CXX_TEST_FILES 
    src/cpp_test.cpp
)

set(TEST_DIR "${${PROJECT_NAME}_SOURCE_DIR}/tests/bin")
foreach(TEST_SRC ${${PROJECT_NAME}_C_TEST_FILES} ${${PROJECT_NAME}_CXX_TEST_FILES})
    string(REPLACE ${${PROJECT_NAME}_SOURCE_DIR}/ "" TEST_FILE ${TEST_SRC})
    get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)
    set(TEST_NAME "${TEST_NAME}.exe")
    set(TEST_EXE ${TEST_DIR}/${TEST_NAME})
    set(TEST_CMD ${TEST_EXE})
    add_executable(${TEST_NAME} ${TEST_SRC})
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_CMD} )
    set_target_properties(${TEST_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${TEST_DIR})
    target_link_libraries(${TEST_NAME} FlailSnail::FlailSnail)
    add_dependencies(build-tests ${TEST_NAME})
endforeach(TEST_SRC)
