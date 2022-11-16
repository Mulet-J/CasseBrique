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
 * Impact de l'eplosion d'une bombe
 * @param myMap Pointeur vers la carte du jeu
 * @param x Rangée
 * @param y Colonne
 * @return 1 si une limite (un élément bloquant l'explosion) est atteinte, 0 sinon
 */
int bombCheckCase(Map *myMap, int x, int y) {
    if(myMap->tileGrid[x][y].wall == 1){
        return 1;
    } else if(myMap->tileGrid[x][y].wall == 2){
        myMap->tileGrid[x][y].wall = 0;
        return 1;
    }
    if(myMap->tileGrid[x][y].player != NULL){
        playerDie(myMap,x,y);
    }
    if(myMap->tileGrid[x][y].bomb.playerID != 0){
        playerDie(myMap,x,y);
    }
    return 0;
}

/**
 * Explosion d'une bombe
 * @param myMap Pointeur vers la carte du jeu
 * @param x Rangée
 * @param y Colonne
 */
void bombExplode(Map *myMap, int x, int y){
    Bomb *myBomb = getBomb(*myMap,x,y);
    Player *myPlayer = getPlayerByID(myMap,myBomb->playerID);
    myPlayer->bombCount++;
    myBomb->playerID = 0;
    bombCheckCase(myMap,x,y);
    for (int i = 0; i < 4; ++i) {
        switch(i){
            case 0: //G
                for (int j = 1; j <= myBomb->strength; ++j) {
                    if(y-j < 0){ //trou dans la carte
                        if(bombCheckCase(myMap,x,myMap->width-(j-y))){
                            break;
                        }
                    } else if(bombCheckCase(myMap,x,y-j)){
                        break;
                    }
                }
            break;
            case 1: //H
                for (int j = 1; j <= myBomb->strength; ++j) {
                    if(x-j < 0){
                        if(bombCheckCase(myMap,myMap->height-(j-x),y)){
                            break;
                        }
                    } else if(bombCheckCase(myMap,x-j,y)){
                        break;
                    }
                }
            break;
            case 2: //D
                for (int j = 1; j <= myBomb->strength; ++j) {
                    if(y+j >= myMap->width){
                        if(bombCheckCase(myMap,x,(y+j)-myMap->width)){
                            break;
                        }
                    } else if(bombCheckCase(myMap,x,y+j)){
                        break;
                    }
                }
            break;
            case 3: //B
                for (int j = 1; j <= myBomb->strength; ++j) {
                    if(x+j >= myMap->height){
                        if(bombCheckCase(myMap,(x+j)-myMap->height,y)){
                            break;
                        }
                    } else if(bombCheckCase(myMap,x+j,y)){
                        break;
                    }
                }
            break;
            default:
            break;
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
