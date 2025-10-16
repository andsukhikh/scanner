cmake_minimum_required(VERSION 3.16)

project(Scanner)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(OPENSSL_ROOT_DIR "C:/Program Files/OpenSSL-Win64")
set(OPENSSL_INCLUDE_DIR "${OPENSSL_ROOT_DIR}/include")
set(OPENSSL_LIBRARIES "${OPENSSL_ROOT_DIR}/lib/VC/x64/MDd")

#find_package(OpenSSL REQUIRED)

add_subdirectory(logic)
#add_subdirectory(tests)

add_executable(utility ${CMAKE_CURRENT_SOURCE_DIR}/logic/src/Main.cpp)
target_link_libraries(utility PRIVATE logic)
set_target_properties(utility PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}" 
)	