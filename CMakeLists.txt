cmake_minimum_required(VERSION 3.10)
project(starwars2)

set(CMAKE_CXX_STANDARD 17)

add_executable(starwars2 main.cpp imperialfleet.h rebelfleet.h battle.h)