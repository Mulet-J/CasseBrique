//
// Created by jules on 26/10/2022.
//

#ifndef CASSEBRIQUE_PLAYER_H
#define CASSEBRIQUE_PLAYER_H

#include "Structs.h"

Player newPlayer(int playerID, int bombCount, int bombStrength);

Player *getPlayerByID(Map *myMap, int playerID);

Player *getPlayerByPos(Map *myMap, int x, int y);

void playerDie(Map *myMap, int x, int y);

void actionPlayer(Map *myMap, Player *myPlayer);

#endif //CASSEBRIQUE_PLAYER_H
