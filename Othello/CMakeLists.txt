cmake_minimum_required(VERSION 3.30)
project(Othello)

set(CMAKE_CXX_STANDARD 20)

add_executable(Othello
        Game.cpp
        Game.h
        Board.cpp
        Board.h
        Position.cpp
        Position.h
        PlayablePosition.cpp
        PlayablePosition.h
        UnplayablePosition.cpp
        UnplayablePosition.h
        Player.cpp
        Player.h
        Main.cpp
)
