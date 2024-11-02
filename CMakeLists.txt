cmake_minimum_required(VERSION 3.5)
project(cpprestserver LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")


add_executable(cpprestserver cpprestserver.cpp)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SERVED_PKG REQUIRED IMPORTED_TARGET served)

target_link_libraries(cpprestserver PkgConfig::SERVED_PKG)

# Copy heuristics directory to the output directory
add_custom_command(TARGET cpprestserver POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/heuristics"
    "$<TARGET_FILE_DIR:cpprestserver>/heuristics"
)
