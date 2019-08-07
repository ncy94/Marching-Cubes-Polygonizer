cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(cpp_project)

set(CMAKE_CXX_STANDARD 17)

find_library(glm REQUIRED)

include_directories(PUBLIC include)

add_executable(generateRandomPoints generateRandomPoints.cpp)
target_link_libraries(generateRandomPoints ${GLM_LIBRARIES})
target_include_directories(generateRandomPoints PUBLIC ${GLM_INCLUDE_DIRECTORIES})

add_executable(mc main.cpp)
target_link_libraries(mc ${GLM_LIBRARIES})
target_include_directories(mc PUBLIC ${GLM_INCLUDE_DIRECTORIES})
