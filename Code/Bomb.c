//
// Created by jules on 02/11/2022.
//
#include "Bomb.h"
#include "Player.h"

/**
 * Crée une structure bombe et enlève une bombe au joueur
 * @param myPlayer Pointeur vers le joueur qui à posé la bombe
 * @return Structure bombe
 */
Bomb newBomb(Player *myPlayer) {
    Bomb myBomb = {
            .timer = 8,
            .strength = myPlayer->bombStrength,
            .playerID = myPlayer->playerID,
    };
    myPlayer->bombCount -= 1;
    return myBomb;
}

/**
 * Crée une structure bombe vide (pour les cases ou il n'y a pas de bombes, pour éviter
 * les valeurs déjà présente dans la mémoire
 * @return Structure bombe à zero
 */
Bomb nullBomb() {
    Bomb myBomb = {
            .timer = 0,
            .strength = 0,
            .playerID = 0,
    };
    return myBomb;
}

/**
 * Récupère le pointeur de la bombe à l'emplacement spécifié
 * @param myMap Pointeur vers la carte du jeu
 * @param x Rangée
 * @param y Colonne
 * @return Pointeur vers la bombe
 */
Bomb *getBomb(Map myMap, int x, int y) {
    return &myMap.tileGrid[x][y].bomb;
}

/**
 * Explosion d'une bombe à l'emplacement spécifié
 * @param myMap Pointeur vers la carte du jeu
 * @param x Rangée
 * @param y Colonne
 */
void bombExplode(Map *myMap, int x, int y) {
    //ignorer warning c'est géré
    Bomb *myBomb = getBomb(*myMap,x,y);
    Player *myPlayer = getPlayerByID(myMap,myBomb->playerID);
    myPlayer->bombCount++;
    myBomb->playerID = 0;
    if(myMap->tileGrid[x][y].player != NULL){
        playerDie(myMap,x,y);
    }
    for (int i = 0; i < myBomb->strength; ++i) {
        if(x-i>=0){
            if(myMap->tileGrid[x-i][y].player != NULL){ //joueur présent
                playerDie(myMap, x-i, y);
            }
            if(myMap->tileGrid[x-i][y].wall == 2){ //mur destructible
                myMap->tileGrid[x-i][y].wall = 0;
            }
            if(myMap->tileGrid[x-i][y].bomb.playerID != 0){ //bombe présente
                bombExplode(myMap,x-i,y);
            }
        }
        if(y-i>=0){
            if(myMap->tileGrid[x][y-i].player != NULL){ //joueur présent
                playerDie(myMap, x, y-i);
            }
            if(myMap->tileGrid[x][y-i].wall == 2){ //mur destructible
                myMap->tileGrid[x][y-i].wall = 0;
            }
            if(myMap->tileGrid[x][y-i].bomb.playerID != 0){ //bombe présente
                bombExplode(myMap,x,y-i);
            }
        }
        if(x+i<myMap->height){
            if(myMap->tileGrid[x+i][y].player != NULL){ //joueur présent
                playerDie(myMap, x+i, y);
            }
            if(myMap->tileGrid[x+i][y].wall == 2){ //mur destructible
                myMap->tileGrid[x+i][y].wall = 0;
            }
            if(myMap->tileGrid[x+i][y].bomb.playerID != 0){ //bombe présente
                bombExplode(myMap,x+i,y);
            }
        }
        if(y+i<myMap->width){
            if(myMap->tileGrid[x][y+i].player != NULL){ //joueur présent
                playerDie(myMap, x, y+i);
            }
            if(myMap->tileGrid[x][y+i].wall == 2){ //mur destructible
                myMap->tileGrid[x][y+i].wall = 0;
            }
            if(myMap->tileGrid[x][y+i].bomb.playerID != 0){ //bombe présente
                bombExplode(myMap,x,y+i);
            }
        }
    }
}

/**
 * Parcours la carte et vérifie si une bombe doit exploser ou doit réduire le timer
 * @param myMap Pointeur vers la carte du jeu
 */
void checkBomb(Map *myMap) {
    for (int x = 0; x < myMap->height; ++x) {
        for (int y = 0; y < myMap->width; ++y) {
            if(myMap->tileGrid[x][y].bomb.playerID != 0 && myMap->tileGrid[x][y].bomb.timer == 0){
                bombExplode(myMap,x,y);
            }
            else if(myMap->tileGrid[x][y].bomb.timer >0){
                myMap->tileGrid[x][y].bomb.timer--;
            }
        }
    }
}
