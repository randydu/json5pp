find_package(Catch2)

add_executable(json5pp_test
    basic_tests get_tests.cpp  obj_tests.cpp main.cpp
)

target_include_directories(json5pp_test PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../include)

add_test(json5pp_test json5pp_test)