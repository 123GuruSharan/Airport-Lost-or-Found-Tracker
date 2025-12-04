cmake_minimum_required(VERSION 3.5)
project(app)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Required for crow_all.h
add_definitions(-DCROW_MAIN)

# Include current directory (contains crow_all.h)
include_directories(${CMAKE_SOURCE_DIR})

# Boost (Crow v0.3 uses some Boost features)
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(app main.cpp)
