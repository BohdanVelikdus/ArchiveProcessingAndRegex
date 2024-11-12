cmake_minimum_required( VERSION 3.30)
project(HelloWorld)

find_package(fmt CONFIG REQUIRED)
find_package(LibArchive REQUIRED)

add_executable(${PROJECT_NAME} "./main/main.cpp")

target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt LibArchive::LibArchive)

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../Debug"  
)