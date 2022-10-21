//
// Created by jules on 26/10/2022.
//

#ifndef CASSEBRIQUE_MAP_H
#define CASSEBRIQUE_MAP_H
#include "Player.h"

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
    Player *players;
    Tile **tileGrid;
} Map;

void printMap(Map *myMap);

Bomb newBomb(Player *myPlayer);

Bomb nullBomb();

Bomb *getBomb(Map myMap, int x, int y);

void actionPlayer(Map *myMap,Player *myPlayer);

void bombExplode(Map *myMap, int x, int y);

Player *getPlayerByID(Map *myMap, int playerID);

Player *getPlayerByPos(Map *myMap, int x, int y);

void playerDie(Map *myMap, int x, int y);

Map convertMap(char *path);

void checkBomb(Map *myMap);

#endif //CASSEBRIQUE_MAP_H
