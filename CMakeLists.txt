cmake_minimum_required(VERSION 3.23)
project(CasseBrique C)

set(CMAKE_C_STANDARD 17)

add_executable(CasseBrique Code/main.c Code/Map.h Code/Map.c Code/Player.h Code/Player.c Code/Utils.h Code/Utils.c Code/Structs.h Code/Bomb.h Code/Bomb.c)
