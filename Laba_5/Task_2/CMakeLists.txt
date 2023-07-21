cmake_minimum_required(VERSION 3.22.1)
project(allocate)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

include_directories(.)

add_executable(allocate
        ../logger/logger.cpp
        ../logger/logger.h
        ../logger/logger_builder.cpp
        ../logger/logger_builder.h
        ../logger/logger_builder_concrete.cpp
        ../logger/logger_builder_concrete.h
        ../logger/logger_concrete.cpp
        ../logger/logger_concrete.h
        memory.h
        memory_global_heap.h
        memory_global_heap.cpp
        main.cpp
        )
target_link_libraries(allocate PRIVATE nlohmann_json::nlohmann_json)