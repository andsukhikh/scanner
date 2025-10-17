cmake_minimum_required(VERSION 3.16)

project(Scanner)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
	message("-- Windows detected")
	
	find_package(OpenSSL QUIET)
	
	if (OpenSSL_FOUND)
		message(STATUS "-- OpenSSL found. Version: ${OPENSSL_VERSION}\n")
	else()
		message("-- OpenSSL environment variables were not found. Library paths will be set to default:\n")
		
		set(OPENSSL_ROOT_DIR "$ENV{SystemDrive}/Program Files/OpenSSL-Win64")
		set(OPENSSL_INCLUDE_DIR "${OPENSSL_ROOT_DIR}/include")
		set(OPENSSL_LIBRARIES "${OPENSSL_ROOT_DIR}/lib/VC/x64/MDd")
		
		message("-- OPENSSL_ROOT_DIR --> ${OPENSSL_ROOT_DIR}")
		message("-- OPENSSL_INCLUDE_DIR --> ${OPENSSL_INCLUDE_DIR}")
		message("-- OPENSSL_LIBRARIES --> ${OPENSSL_LIBRARIES}")
		message("\n")
		
	endif()
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
	message("-- Linux detected")
	
	find_package(OpenSSL REQUIRED)
else()
	message(FATAL_ERROR "Unsupported operating system: ${CMAKE_SYSTEM_NAME}\n")
endif()

add_subdirectory(logic)

add_executable(scanner ${CMAKE_CURRENT_SOURCE_DIR}/logic/src/Main.cpp)
target_link_libraries(scanner PRIVATE logic)
set_target_properties(scanner PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}" 
)	