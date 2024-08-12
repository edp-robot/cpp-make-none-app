cmake_minimum_required(VERSION 3.10)

project(MyProject CXX)

set(CacheDIR ${CMAKE_SOURCE_DIR}/lib)

include_directories(include ${CacheDIR}/pkgconfig)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/target)

set(SRC_FILES src/main.cpp src/HttpServer.cpp)
set(TEST_FILES tests/test_main.cpp src/HttpServer.cpp)  # Include HttpServer.cpp in the test target

add_executable(app ${SRC_FILES})
target_link_libraries(app ${CacheDIR}/libmicrohttpd.a)

add_executable(test_main ${TEST_FILES})
target_link_libraries(test_main ${CacheDIR}/libmicrohttpd.a)

if(UNIX AND NOT APPLE)
    set_target_properties(test_main PROPERTIES
        COMMAND "LD_LIBRARY_PATH=${CacheDIR} ./test_main"
    )
endif()

if(APPLE)
    set_target_properties(test_main PROPERTIES
        COMMAND "DYLD_LIBRARY_PATH=${CacheDIR} ./test_main"
    )
endif()

add_custom_target(custom_clean
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/CMakeFiles
    COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/CMakeCache.txt
    COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/Makefile
    COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/cmake_install.cmake
    COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_SOURCE_DIR}/target/app
    COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_SOURCE_DIR}/target/test_main
)
