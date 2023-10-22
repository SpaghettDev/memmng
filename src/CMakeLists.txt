cmake_minimum_required(VERSION 3.20)

set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")

file(GLOB_RECURSE SRC_FILES
    "${SRC_DIR}/**.hpp"
)

add_library(${PROJECT_NAME} INTERFACE ${SRC_FILES})
target_include_directories(${PROJECT_NAME} INTERFACE .)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 20)
set_target_properties(memmng PROPERTIES CXX_STANDARD 20)
