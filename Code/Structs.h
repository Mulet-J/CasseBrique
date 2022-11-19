//
// Created by jules on 02/11/2022.
//

#ifndef CASSEBRIQUE_STRUCTS_H
#define CASSEBRIQUE_STRUCTS_H

#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>

typedef struct Player {
    int playerID;
    int health;
    int bombStrength;
    int bombCount;
    int invincibility;
    int isAlive;
    int isBot;
} Player;

typedef struct Bomb{
    int playerID;
    int timer;
    int strength;
} Bomb;

typedef struct  Tile {
    int wall;
    int powerUP;
    Player *player;
    Bomb bomb;
} Tile;

typedef struct Map {
    int width;
    int height;
    int playerCount;
    Player *players;
    Tile **tileGrid;
} Map;

typedef struct MapState{
    char *map;
    int isActive;
    int maxPlayers;
} MapState;

typedef struct MapSelection {
    MapState *maps;
    int count;
} MapSelection;

#endif //CASSEBRIQUE_STRUCTS_H
