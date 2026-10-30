cmake_minimum_required(VERSION 3.20)
project(OOP)

set(CMAKE_CXX_STANDARD 20)

add_executable(OOP main.cpp
        config/game_constants.h
        robot/robot.cpp
        robot/robot.h
        robot/team.h
        cell/cell.cpp
        cell/cell.h
        gamefield/gamefield.cpp
        gamefield/gamefield.h
        movement/movement.cpp
        movement/movement.h
        gameloop/gameloop.cpp
        gameloop/gameloop.h
        visualizer/visualizer.cpp
        visualizer/visualizer.h
        robotfactory/robotfactory.cpp
        robotfactory/robotfactory.h
        enemycontroller/enemycontroller.cpp
        enemycontroller/enemycontroller.h
)
