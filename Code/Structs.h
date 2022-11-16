//
// Created by jules on 02/11/2022.
//

#ifndef CASSEBRIQUE_STRUCTS_H
#define CASSEBRIQUE_STRUCTS_H

#include <stdlib.h>
#include <stdio.h>

typedef struct Items{
    int kickBomb;
    int passBomb;
    int firePower;
} Items;


typedef struct Player {
    int playerID;
    int health;
    int bombStrength;
    int bombCount;
    int invincibility;
    int isAlive;
    Items items;
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
    Items items;
} Tile;

typedef struct Map {
    int width;
    int height;
    Player *players;
    Tile **tileGrid;
} Map;


#endif //CASSEBRIQUE_STRUCTS_H
