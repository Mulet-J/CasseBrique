//
// Created by jules on 26/10/2022.
//

#include <stdlib.h>
#include <stdio.h>
#include "Map.h"
#include "Utils.h"
#include "Player.h"
#include "Bomb.h"

/**
 * Affiche la carte actuelle dans la console
 * @param myMap Pointeur vers la carte du jeu
 */
void printMap(Map *myMap) {
    //clearScreen(); //fonctionne mais buggé avec le cli CLion
    for (int x = 0; x < myMap->height; ++x) {
        for (int y = 0; y < myMap->width; ++y) {
            if(myMap->tileGrid[x][y].wall==1) {
                printf("X ");
            } else if(myMap->tileGrid[x][y].wall==2) {
                printf("# ");
            } else if(myMap->tileGrid[x][y].player != NULL) {
                printf("p ");
            } else if(myMap->tileGrid[x][y].bomb.playerID !=0 ) {
                printf("b ");
            } else {
                printf("  ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

/**
 * Génère une carte à partir d'un fichier
 * @param path Chemin du fichier
 * @return Une carte de jeu
 */
Map convertMap(char *filename) {
    int playerCount,bombCount,bombStrength, width, height;
    char buffer[1024] = "../Maps/";
    strcat(buffer,filename);
    FILE *map = fopen(buffer,"r");
    fscanf(map, "%d %d %d %d %d", &playerCount, &bombCount, &bombStrength, &width, &height);
    int playerID = 1;
    Map myMap = {
            .height = height,
            .width = width,
            .players = malloc(sizeof(Player)*playerCount),
            .tileGrid = malloc(sizeof(Tile)*height),
            .playerCount = playerCount,

    };
    for (int i = 0; i < playerCount; ++i) {
        myMap.players[i] = newPlayer(i+1,bombCount,bombStrength);
    }
    for (int x = 0; x < myMap.height; ++x) {
        //ignore les \n du fichier, moche mais fonctionne
        fseek(map,2,SEEK_CUR);
        myMap.tileGrid[x] = malloc(sizeof(Tile)*width);
        for (int y = 0; y < myMap.width; ++y) {
            myMap.tileGrid[x][y].wall = 0;
            myMap.tileGrid[x][y].powerUP = 0;
            myMap.tileGrid[x][y].player = NULL;
            myMap.tileGrid[x][y].bomb = nullBomb();
            char currentChar = getc(map);
            if(currentChar == 'x'){
                myMap.tileGrid[x][y].wall = 1;
            } else if(currentChar == 'm'){
                myMap.tileGrid[x][y].wall = 2;
            } else if(currentChar == 'p'){
                myMap.tileGrid[x][y].player = getPlayerByID(&myMap,playerID);
                playerID++;
            }
        }
    }
    printf("\n");
    fclose(map);
    return myMap;
}

int playGame(char *filename, int solo) {
    Map myMap = convertMap(filename);
    int play = 1;
    if(solo){
        myMap.players[0].isBot = 0;
    }
    int latestPlayer = 0;
    while(play){
        for (int i = 0; i < myMap.playerCount; ++i) {
            if(myMap.players[i].isAlive){
                //plus qu'un seul joueur
                if(latestPlayer == myMap.players[i].playerID){
                    printf("Joueur %d a gagne\n",myMap.players[i].playerID);
                    play = 0;
                    break;
                }
                latestPlayer = myMap.players[i].playerID;
                if(myMap.players[i].isBot != 1){
                    char direction;
                    printMap(&myMap);
                    scanf(" %c", &direction);
                    actionPlayer(&myMap, getPlayerByID(&myMap,i+1), direction);
                } else {
                    ;
                }
            }
        }
        checkBomb(&myMap);
    }
    return 1;
}
