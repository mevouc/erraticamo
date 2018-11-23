cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "-std=c++17 -pedantic -Wall -Wextra -Werror")
set(CMAKE_CXX_FLAGS_DEBUG "-g -fno-inline")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

find_package(Boost COMPONENTS program_options REQUIRED)
find_package(OpenCV REQUIRED)

include_directories(src/
                    ${Boost_INCLUDE_DIRS}
                    ${OpenCV_INCLUDE_DIRS})

set(SRC src/erraticamo.cc
        src/camo-generator.cc
        src/layer.cc
        src/noise.cc
        src/utils.cc)

add_executable(erraticamo ${SRC})
target_link_libraries(erraticamo ${Boost_LIBRARIES})
target_link_libraries(erraticamo ${OpenCV_LIBRARIES})
