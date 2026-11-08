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
        ability/ability.h
        ability/heal_ability.cpp
        ability/heal_ability.h
        ability/area_strike_ability.h
        ability/area_strike_ability.cpp
        ability/ranged_strike_ability.cpp
        ability/teleport_ability.cpp
        ability/ranged_strike_ability.h
        ability/teleport_ability.h
        status/status.h
        status/status_base.cpp
        status/status_base.h
        status/slow_status.cpp
        status/slow_status.h
        status/overload_status.cpp
        status/overload_status.h
        status/burn_status.cpp
        status/burn_status.h
        status/shield_status.cpp
        status/shield_status.h
        status/status_type.h
        status/status_factory.cpp
        status/status_factory.h
        ability/ability_type.h
        ability/ability_factory.cpp
        ability/ability_factory.h
)
