cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(cpp_project)

set(CMAKE_CXX_STANDARD 17)

find_library(GLM REQUIRED)

include_directories(PUBLIC include)

add_executable(generate_random_point_cloud generateRandomPoints.cpp)
target_link_libraries(generate_random_point_cloud ${GLM_LIBRARY_DIR})
target_include_directories(generate_random_point_cloud PUBLIC ${GLM_INCLUDE_DIR})

add_executable(generate_mesh main.cpp)
target_link_libraries(generate_mesh ${GLM_LIBRAR_DIR})
target_include_directories(generate_mesh PUBLIC ${GLM_INCLUDE_DIR})

install(TARGETS generate_random_point_cloud generate_mesh DESTINATION bin)

install(PROGRAMS demo DESTINATION bin)
install(FILES testfile/bunny.xyz DESTINATION bin)