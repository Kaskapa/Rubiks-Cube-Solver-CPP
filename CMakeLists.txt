cmake_minimum_required(VERSION 3.10)  # Bump to newer CMake
project(cpprestserver LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

# Add include directories for organized structure
include_directories(${CMAKE_SOURCE_DIR}/include)

# Source files organized by category
set(CORE_SOURCES
  src/core/pieces.cpp
  src/core/cubiecube.cpp
  src/core/facecube.cpp
)

set(ALGORITHM_SOURCES
  src/algorithms/idaStarCross.cpp
  src/algorithms/idaStarF2l.cpp
  src/algorithms/idaStarOLL.cpp
)

set(UTILS_SOURCES
  src/utils/tableloader.cpp
)

# ------------------------------------------------------
# Dependency: served
# ------------------------------------------------------
find_package(PkgConfig REQUIRED)
pkg_check_modules(SERVED_PKG REQUIRED IMPORTED_TARGET served)

# If the above fails, manually specify paths:
# include_directories(/path/to/served/include)
# link_directories(/path/to/served/lib)

# ------------------------------------------------------
# Main executable (REST API Server)
# ------------------------------------------------------
add_executable(cpprestserver 
  ${CORE_SOURCES}
  ${ALGORITHM_SOURCES}
  ${UTILS_SOURCES}
  src/server/cpprestserver.cpp
)
target_link_libraries(cpprestserver PRIVATE PkgConfig::SERVED_PKG)

# Optional: Add test executable
add_executable(cubeSolverTest EXCLUDE_FROM_ALL
  ${CORE_SOURCES}
  ${ALGORITHM_SOURCES}
  ${UTILS_SOURCES}
  test/test.cpp
)

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