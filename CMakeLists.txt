project(std)

cmake_minimum_required(VERSION 2.8)

add_definitions("-std=c++1y -Wall -Wfatal-errors -g")

set(BOOST_ROOT $ENV{Boost})

find_package(Boost COMPONENTS unit_test_framework system regex date_time thread filesystem)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${BOOST_ROOT})

file(GLOB_RECURSE HEADER_FILES ./**/*.hpp)

aux_source_directory(mstd/test SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST} ${HEADER_FILES})

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
