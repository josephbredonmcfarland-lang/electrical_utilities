cmake_minimum_required(VERSION 4.2)
project(electrical_utilities)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_library(electrical_utilities
        cpp/ResistorSeries/ResistorSeries.cpp
        cpp/ResistorSeries/ResistorSeries.h
        cpp/Timer555/Timer555.cpp
        cpp/Timer555/Timer555.h

        cpp/Math/CarToPol.cpp
        cpp/Math/CarToPol.h
        cpp/Math/Polar.h
        cpp/Math/ParallelSum.cpp
        cpp/Math/ParallelSum.h
        cpp/Math/PolToCar.cpp
        cpp/Math/PolToCar.h
        cpp/Math/RoundTo.cpp
        cpp/Math/RoundTo.h

        cpp/Circuit/Branch.cpp
        cpp/Circuit/Branch.h
        cpp/Circuit/Combinations.cpp
        cpp/Circuit/Combinations.h
        cpp/Circuit/Element.cpp
        cpp/Circuit/Element.h
        cpp/Circuit/Node.cpp
        cpp/Circuit/Node.h
        cpp/Circuit/Netlist.cpp
        cpp/Circuit/Netlist.h
)


target_include_directories(electrical_utilities
        PUBLIC
            cpp/Timer555
            cpp/ResistorSeries
            cpp/Math
            cpp/Circuit
)

# Build the executable from your main file
add_executable(myapp cpp/Test.cpp)

# Link the library into the executable
target_link_libraries(myapp PRIVATE electrical_utilities)