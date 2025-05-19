cmake_minimum_required(VERSION 3.27)
project(platformer)

set(CMAKE_CXX_STANDARD 17)

find_package(raylib CONFIG REQUIRED)
if(APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
elseif(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -fsanitize=address -fsanitize=undefined")
endif()

add_executable(platformer platformer.cpp globals.h graphics.h level.h player.h enemy.h level.h assets.h utilities.h level_controller.cpp level_controller.h enemies_controller.cpp enemies_controller.h player_controller.cpp player_controller.h
        level_controller.cpp
        level_controller.h)
target_link_libraries(platformer PRIVATE raylib)
