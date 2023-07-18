cmake_minimum_required(VERSION 3.22.1)
project(project)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

include_directories(.)

add_executable(project
        logger.cpp
        logger.h
        logger_builder.cpp
        logger_builder.h
        logger_builder_concrete.cpp
        logger_builder_concrete.h
        logger_concrete.cpp
        logger_concrete.h
        main.cpp)
target_link_libraries(project PRIVATE nlohmann_json::nlohmann_json)