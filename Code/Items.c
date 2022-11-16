//
// Created by alexr on 06/11/2022.
//

#include "Items.h"
#include "Player.c"
#include "Bomb.c"

/**
 * Crée une structure item vide (pour les cases ou il n'y a pas de bombes, pour éviter
 * les valeurs déjà présente dans la mémoire
 * @return Structure item à zero
 */

Items nullItem() {
    Items myItems = {
            .passBomb = 0,
            .kickBomb = 0,
            .firePower = 0,
    };
    return myItems;
}

 /** Récupère le pointeur de la bombe à l'emplacement spécifié apres avoir utiliser kickBomb
 * @param myMap Pointeur vers la carte du jeu
 * @param x Rangée
 * @param y Colonne
 * @return Pointeur vers la bombe
 */

Items kickBomb(Map *myMap, int x, int y){
    Bomb bombPos = myMap->tileGrid[x][y].bomb;
    int i =0;
    if (myMap->tileGrid[x][y].wall == 2){
        playerDie(myMap,x,y);
    }
    while (myMap->tileGrid[x][y].wall == 0){

        myMap->tileGrid[x][y].bomb = myMap->tileGrid[x+i][y].bomb;
        i++;
    }
}

/** Récupère le pointeur de la bombe à l'emplacement spécifié
 * @param myMap Pointeur vers la carte du jeu
 * @param x Rangée
 * @param y Colonne
 * @return Pointeur vers la bombe
 */

Bomb firepower(Map *myMap, int power, int x, int y){

    Bomb powerBomb;
    int redFire = 1;
    int yellowFire = 2;
    int blueFire = 3;
    int j = 0;
    int l = 0;
    if (power == 1){
        for (int i =0; i == myMap->width; i++){
            j = i;
        }
        for (int k =0; k == myMap->height; k++){
            l = k;
        }
        powerBomb = myMap->tileGrid[x+j][y+l].bomb;
        printf("RED Bomb will destroy whole map");
    } else if (power == 2){
        powerBomb = myMap->tileGrid[x+1][y+1].bomb;
        printf(" Yellow Bomb Range increased by 1");
    }
    if (power == 3){
        powerBomb = myMap->tileGrid[x - 1][y - 1].bomb;
        printf("Blue Bomb Range decreased by 1");
    }
    return powerBomb;

}
/** Récupère le pointeur de la bombe à l'emplacement spécifié apres avoir utiliser passbomb
 * @param myMap Pointeur vers la carte du jeu
 * @param x Rangée
 * @param y Colonne
 * @return Pointeur vers la bombe
 */

Items *getItem(Map myMap, int x, int y) {

    return &myMap.tileGrid[x][y].items;
}

//Items passBomb (Map *myMap, int x, int y){
//    Bomb bombPos = myMap->tileGrid[x][y].bomb;
//    if (myMap->tileGrid[x][y].bomb != )
//}