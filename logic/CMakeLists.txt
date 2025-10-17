set(LOGIC_SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/src/FlagsHandler.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Output.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Scanner.cpp
)

add_library(logic SHARED ${LOGIC_SOURCES})

target_include_directories(logic
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
		${OPENSSL_INCLUDE_DIR}
)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
	target_link_libraries(logic 
		PRIVATE 
			"${OPENSSL_LIBRARIES}/libcrypto.lib"
			"${OPENSSL_LIBRARIES}/libssl.lib"
	)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
	target_link_libraries(logic 
    PRIVATE 
        OpenSSL::Crypto
	)
endif()

set_target_properties(logic PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
)

target_compile_definitions(logic PRIVATE OPENSSL_SUPPRESS_DEPRECATED)





