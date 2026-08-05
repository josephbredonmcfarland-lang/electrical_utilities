cmake_minimum_required(VERSION 4.2)
project(electrical_utilities)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_library(electrical_utilities
        cpp/Timer555/Timer555.cpp
        cpp/Timer555/Timer555.h
        cpp/ResistorSeries/ResistorSeries.cpp
        cpp/ResistorSeries/ResistorSeries.h
        cpp/Math/RoundTo.cpp
        cpp/Math/RoundTo.h
        cpp/Circuit/Combinations.cpp
        cpp/Circuit/Combinations.h
        cpp/Math/HarmonicSum.cpp
        cpp/Math/HarmonicSum.h
        cpp/Math/PolToCar.cpp
        cpp/Math/PolToCar.h
        cpp/Math/CarToPol.cpp
        cpp/Math/CarToPol.h
)


target_include_directories(electrical_utilities
        PUBLIC
            cpp/Timer555
            cpp/ResistorSeries
            cpp/Math
)

# Build the executable from your main file
add_executable(myapp cpp/Test.cpp)

# Link the library into the executable
target_link_libraries(myapp PRIVATE electrical_utilities)