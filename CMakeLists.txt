cmake_minimum_required(VERSION 3.10)
project(starwars2)

set(CMAKE_CXX_STANDARD 17)


add_executable(starwars2_main main.cpp imperialfleet.h rebelfleet.h battle.h)
add_executable(starwars2_example starwars2_example.cc imperialfleet.h rebelfleet.h battle.h helper.h)
add_executable(test0 test0.cpp imperialfleet.h rebelfleet.h battle.h helper.h)
add_executable(test1 test_michal.cpp imperialfleet.h rebelfleet.h battle.h helper.h)