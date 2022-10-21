//
// Created by jules on 26/10/2022.
//
#include "Player.h"

Player newPlayer(int playerID, int bombCount, int bombStrength) {
    Player myPlayer = {
            .playerID = playerID,
            .bombCount = bombCount,
            .bombStrength = bombStrength,
            .health = 1,
            .invincibility = 0,
            .isAlive = 1,
    };
    return myPlayer;
}
