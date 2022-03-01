cmake_minimum_required(VERSION 3.22.0)
set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED ON)
project(game-of-life)

set(SFML_BUILD_NETWORK OFF)
set(SFML_BUILD_DOC OFF)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
find_package(SFML 2.5.1 COMPONENTS system audio window graphics REQUIRED)

include_directories(include)
file(GLOB SOURCE_FILES src/*.c)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} m csfml-system csfml-audio csfml-window csfml-graphics)
