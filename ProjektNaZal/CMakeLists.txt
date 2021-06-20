cmake_minimum_required(VERSION 3.5)

project(ProjektNaZal LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ProjektNaZal main.cpp)

set_target_properties(ProjektNaZal PROPERTIES
    CXX_EXTENSIONS OFF
)

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
target_link_libraries(ProjektNaZal PRIVATE sfml-system sfml-network sfml-graphics sfml-window)
