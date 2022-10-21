//
// Created by jules on 26/10/2022.
//

#ifndef CASSEBRIQUE_PLAYER_H
#define CASSEBRIQUE_PLAYER_H

#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct Player {
    int playerID;
    int health;
    int bombStrength;
    int bombCount;
    int invincibility;
    int isAlive;
} Player;

Player newPlayer(int playerID, int bombCount, int bombStrength);

#endif //CASSEBRIQUE_PLAYER_H
