cmake_minimum_required(VERSION 4.2)
project(electrical_utilities)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_library(electrical_utilities
        cpp/TIMER_xx555/TIMER_xx555.cpp
        cpp/TIMER_xx555/TIMER_xx555.h
        cpp/ResistorSeries/ResistorSeries.cpp
        cpp/ResistorSeries/ResistorSeries.h
        cpp/Math/SigFig.cpp
        cpp/Math/SigFig.h
)


target_include_directories(electrical_utilities PUBLIC cpp/TIMER_xx555, electrical_utilities PUBLIC cpp/ResistorSeries)

# Build the executable from your main file
add_executable(myapp cpp/ResistorSeries/test_files/main.cpp)

# Link the library into the executable
target_link_libraries(myapp PRIVATE electrical_utilities)