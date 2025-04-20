cmake_minimum_required(VERSION 3.10)  # Bump to newer CMake
project(cpprestserver LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

# ------------------------------------------------------
# Dependency: served
# ------------------------------------------------------
find_package(PkgConfig REQUIRED)
pkg_check_modules(SERVED_PKG REQUIRED IMPORTED_TARGET served)

# If the above fails, manually specify paths:
# include_directories(/path/to/served/include)
# link_directories(/path/to/served/lib)

# ------------------------------------------------------
# Executable
# ------------------------------------------------------
add_executable(cpprestserver cpprestserver.cpp)
target_link_libraries(cpprestserver PRIVATE PkgConfig::SERVED_PKG)

# ------------------------------------------------------
# Copy heuristics (only if directory exists)
# ------------------------------------------------------
if(EXISTS "${CMAKE_SOURCE_DIR}/heuristics")
  add_custom_command(TARGET cpprestserver POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
      "${CMAKE_SOURCE_DIR}/heuristics"
      "$<TARGET_FILE_DIR:cpprestserver>/heuristics"
  )
else()
  message(WARNING "heuristics/ directory missing! Cube-solving data may not load.")
endif()