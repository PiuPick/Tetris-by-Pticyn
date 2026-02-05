cmake_minimum_required(VERSION 4.1)
project(Tetris-by-Pticyn)
set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        sfml
        GIT_REPOSITORY https://github.com/SFML/SFML
        GIT_TAG 3.0.2
)
FetchContent_MakeAvailable(sfml)

add_executable(
        ${PROJECT_NAME}
        main.cpp
        src/Game.cpp
        src/Board.cpp
        src/Tetromino.cpp
)
target_link_libraries(
        ${PROJECT_NAME}
        sfml-graphics
)