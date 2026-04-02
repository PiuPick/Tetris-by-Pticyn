cmake_minimum_required(VERSION 3.20)
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
        src/ScoreManager.cpp
        src/Heap.cpp
        src/Info.cpp
        src/ConsoleMenu.cpp
        src/TestRunner.cpp
        include/views/TetrominoView.cpp
        include/views/HeapView.cpp
        include/views/BoardView.cpp
        include/views/NextTetrominoView.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR})

target_link_libraries(
        ${PROJECT_NAME}
        sfml-graphics
)

file(COPY res DESTINATION ${CMAKE_BINARY_DIR})
if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /utf-8)
endif ()