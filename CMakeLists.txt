cmake_minimum_required(VERSION 3.10)

# Set the project name
project(WordProcessor)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

find_package(CURL REQUIRED)

# Add the executable
add_executable(Main
    src/main.cpp
    src/part1.cpp
    src/part2.cpp
    src/trades.cpp
    src/hash.cpp
    src/word_utils.cpp
    include/config_loader.hpp
)

include_directories(${CURL_INCLUDE_DIRS})

target_link_libraries(Main CURL::libcurl)

add_custom_command(
    TARGET Main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/data/Book.txt"
        $<TARGET_FILE_DIR:Main>
)

add_custom_command(
    TARGET Main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/config/config.json"
        $<TARGET_FILE_DIR:Main>
)

add_executable(AllTests
    tests/tests.cpp
    src/hash.cpp
    src/word_utils.cpp
)