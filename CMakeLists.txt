cmake_minimum_required(VERSION 4.3)
project(electrical_utilities)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_library(electrical_utilities
        cpp/TIMER_xx555/TIMER_xx555.cpp
        cpp/TIMER_xx555/TIMER_xx555.h
        cpp/TIMER_xx555/TIMER_xx555.h
        cpp/TIMER_xx555/555_Deposit.h)

target_include_directories(electrical_utilities PUBLIC cpp/TIMER_xx555)