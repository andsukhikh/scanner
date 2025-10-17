cmake_minimum_required(VERSION 3.16)

project(Scanner)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
	message("-- Windows detected")
	
	set(OPENSSL_ROOT_DIR "$ENV{SystemDrive}/Program Files/OpenSSL-Win64")
	set(OPENSSL_INCLUDE_DIR "${OPENSSL_ROOT_DIR}/include")
	set(OPENSSL_LIBRARIES "${OPENSSL_ROOT_DIR}/lib/VC/x64/MDd")
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
	message("--Linux detected")
	
	find_package(OpenSSL REQUIRED)
else()
	message(FATAL_ERROR "Unsupported operating system: ${CMAKE_SYSTEM_NAME}")
endif()

add_subdirectory(logic)

add_executable(scanner ${CMAKE_CURRENT_SOURCE_DIR}/logic/src/Main.cpp)
target_link_libraries(scanner PRIVATE logic)
set_target_properties(scanner PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}" 
)	