//
// Created by jules on 26/10/2022.
//
#include "Player.h"
#include "Bomb.h"

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

Player *getPlayerByID(Map *myMap, int playerID) {
    return &myMap->players[playerID-1];
}

Player *getPlayerByPos(Map *myMap, int x, int y) {
    return myMap->tileGrid[x][y].player;
}

void playerDie(Map *myMap, int x, int y) {
    Player *myPlayer = getPlayerByPos(myMap,x,y);
    myPlayer->isAlive = 0;
    myMap->tileGrid[x][y].player = NULL;
}

void actionPlayer(Map *myMap, Player *myPlayer) {
    int xPlayer;
    int yPlayer;
    char direction;
    for (int x = 0; x < myMap->height; ++x) {
        for (int y = 0; y < myMap->width; ++y) {
            if(myMap->tileGrid[x][y].player == myPlayer){
                xPlayer = x;
                yPlayer = y;
            }
        }
    }
    //solution 1
    scanf("%c",&direction);
    scanf("%c",&direction);
    //solution 2 (espace pas utilisable)
    //scanf(" %c",&direction);

    switch (direction) {
        case 'z':
            if(xPlayer != 0 && myMap->tileGrid[xPlayer-1][yPlayer].wall == 0 && myMap->tileGrid[xPlayer-1][yPlayer].player == NULL && myMap->tileGrid[xPlayer-1][yPlayer].bomb.playerID == 0){
                myMap->tileGrid[xPlayer-1][yPlayer].player = myMap->tileGrid[xPlayer][yPlayer].player;
                myMap->tileGrid[xPlayer][yPlayer].player = NULL;
            }
            break;
        case 'q':
            if(yPlayer != 0 && myMap->tileGrid[xPlayer][yPlayer-1].wall == 0 && myMap->tileGrid[xPlayer][yPlayer-1].player == NULL && myMap->tileGrid[xPlayer][yPlayer-1].bomb.playerID == 0){
                myMap->tileGrid[xPlayer][yPlayer-1].player = myMap->tileGrid[xPlayer][yPlayer].player;
                myMap->tileGrid[xPlayer][yPlayer].player = NULL;
            }
            break;
        case 's':
            if(xPlayer != myMap->height-1 && myMap->tileGrid[xPlayer+1][yPlayer].wall == 0 && myMap->tileGrid[xPlayer+1][yPlayer].player == NULL && myMap->tileGrid[xPlayer+1][yPlayer].bomb.playerID == 0){
                myMap->tileGrid[xPlayer+1][yPlayer].player = myMap->tileGrid[xPlayer][yPlayer].player;
                myMap->tileGrid[xPlayer][yPlayer].player = NULL;
            }
            break;
        case 'd':
            if(yPlayer != myMap->width-1 && myMap->tileGrid[xPlayer][yPlayer+1].wall == 0 && myMap->tileGrid[xPlayer][yPlayer+1].player == NULL && myMap->tileGrid[xPlayer][yPlayer+1].bomb.playerID == 0){
                myMap->tileGrid[xPlayer][yPlayer+1].player = myMap->tileGrid[xPlayer][yPlayer].player;
                myMap->tileGrid[xPlayer][yPlayer].player = NULL;
            }
            break;
        case ' ':
            if(myMap->tileGrid[xPlayer][yPlayer].bomb.playerID == 0 && myMap->tileGrid[xPlayer][yPlayer].player->bombCount > 0){
                myMap->tileGrid[xPlayer][yPlayer].bomb = newBomb(myPlayer);
            }
            break;
        default:
            break;
    }
}
