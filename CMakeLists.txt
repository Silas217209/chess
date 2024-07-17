cmake_minimum_required(VERSION 3.28)

project(
    Chess
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Export compile commands for tooling
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add compile options
add_compile_options(-mbmi2 -flto)

# Gather source files
file(GLOB_RECURSE SRC_FILES src/*.cpp)

# Create executable
add_executable(chess ${SRC_FILES})

# Set include directories
target_include_directories(chess PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_compile_features(chess PRIVATE cxx_std_20)

