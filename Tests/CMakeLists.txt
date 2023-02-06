add_custom_target(generate_tests
        COMMAND ${CMAKE_CURRENT_LIST_DIR}/generate_tests.sh ${CMAKE_SOURCE_DIR}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        DEPENDS ${CMAKE_CURRENT_LIST_DIR}/generate_tests.sh)

make_test(MODULE_UNDER_TEST ../MessageDecoding.c
            TEST_DEFINITION MessageDecoding.cpp)
target_link_libraries(MessageDecoding.test PUBLIC ToolboxPlaneMessageDefs)
add_dependencies(MessageDecoding.test generate_tests)

make_test(MODULE_UNDER_TEST ../MessageEncoding.c
        TEST_DEFINITION MessageEncoding.cpp)
target_link_libraries(MessageEncoding.test PUBLIC ToolboxPlaneMessageDefs)
add_dependencies(MessageEncoding.test generate_tests)
