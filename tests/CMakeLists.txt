include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

enable_testing()

set(TEST_SOURCES
    FlagsHandlerTest.cpp
)

add_executable(scanner_tests ${TEST_SOURCES})

target_include_directories(scanner_tests
    PRIVATE
        ${gtest_SOURCE_DIR}/googletest/include
		${gmock_SOURCE_DIR}/googlemock/include
		${CMAKE_SOURCE_DIR}/logic/include
)

target_link_libraries(scanner_tests
    PRIVATE
		gtest 
        gtest_main
		logic
)

set_target_properties(scanner_tests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
)

include(GoogleTest)
gtest_discover_tests(scanner_tests)
