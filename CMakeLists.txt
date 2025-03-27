cmake_minimum_required(VERSION 3.10)

# Set the project name
project(eventlib)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(eventlib
    main.cpp
    src/data_processor.cpp
    src/result_handler.cpp
    src/logger.cpp
    src/event_bus.cpp
)

# Include directories
target_include_directories(eventlib PRIVATE include)