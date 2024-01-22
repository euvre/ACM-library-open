cmake_minimum_required(VERSION 3.27 FATAL_ERROR)

include(GoogleTest)

file(GLOB_RECURSE ACM_TEST_SOURCES "${PROJECT_SOURCE_DIR}/test/*/*test.cpp")

foreach (acm_test_source ${ACM_TEST_SOURCES})
    get_filename_component(acm_test_filename ${acm_test_source} NAME)
    string(REPLACE ".cpp" "" acm_test_name ${acm_test_filename})

    add_executable(${acm_test_name} EXCLUDE_FROM_ALL ${acm_test_source} "char_algorithm/manacher_test.cpp")
    
    gtest_discover_tests(${acm_test_name}
        TIMEOUT 120)
    
    target_link_libraries(${acm_test_name} acm_ixx
        gtest
        gmock_main)
endforeach ()