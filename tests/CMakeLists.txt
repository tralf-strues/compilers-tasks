message(STATUS "Generating tests")

get_filename_component(TESTS_PATH "." ABSOLUTE)
# file(GLOB_RECURSE TEST_SOURCES ${TESTS_PATH}/*.cpp)
set(TEST_SOURCES ${TESTS_PATH}/main.cpp ${TESTS_PATH}/tralf_strues/cases.cpp)

add_executable(tests ${TEST_SOURCES})
target_link_libraries(tests PRIVATE compiler)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
