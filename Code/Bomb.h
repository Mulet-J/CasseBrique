//
// Created by jules on 02/11/2022.
//

#ifndef CASSEBRIQUE_BOMB_H
#define CASSEBRIQUE_BOMB_H
#include "Structs.h"

Bomb newBomb(Player *myPlayer, int playerCount);

Bomb nullBomb();

Bomb *getBomb(Map myMap, int x, int y);

void bombExplode(Map *myMap, int x, int y);

void checkBomb(Map *myMap);

int bombCheckCase(Map *myMap, int x, int y);

#endif //CASSEBRIQUE_BOMB_H
