cmake_minimum_required(VERSION 3.23)
project(CasseBrique C)

set(CMAKE_C_STANDARD 17)

add_executable(CasseBrique main.c Map.h Map.c Player.h Player.c Utils.h Utils.c)
