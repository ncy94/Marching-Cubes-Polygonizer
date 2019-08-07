cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(cpp_project)

set(CMAKE_CXX_STANDARD 17)

find_library(glm REQUIRED)

include_directories(PUBLIC include)

add_executable(generate_random_point_cloud generateRandomPoints.cpp)
target_link_libraries(generate_random_point_cloud ${GLM_LIBRARIES})
target_include_directories(generate_random_point_cloud PUBLIC ${GLM_INCLUDE_DIRECTORIES})

add_executable(generate_mesh main.cpp)
target_link_libraries(generate_mesh ${GLM_LIBRARIES})
target_include_directories(generate_mesh PUBLIC ${GLM_INCLUDE_DIRECTORIES})
