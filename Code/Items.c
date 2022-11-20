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
            .passbomb = 0,
            .kickbomb = 0,
            .firepower = 0,
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
     for (int i = 0; i < myMap->height; ++i) {
         for (int j = 0; j < myMap->width; ++j){
             if (myMap->tileGrid[x+i][y].wall == 0 ){
                 bombPos = myMap->tileGrid[x+i][y].bomb;
             }else if (myMap->tileGrid[x][y+j].wall == 0){
                 bombPos = myMap->tileGrid[x][y+j].bomb;
             } else {
                 printf("Il est impossible de fraper cet bomb");
                 bombExplode(myMap, x, y);
                 playerDie(myMap, x ,y);
             }
         }
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

Items getItem(Map myMap, int x, int y) {
    return myMap.tileGrid[x][y].items;
}

Bomb passBomb (Map *myMap, int x, int y){
    Bomb bombPos = myMap->tileGrid[x][y].bomb;
    Player *player = getPlayerByPos(myMap, x,y);
    Bomb passBomb;
    if (bombPos.timer > 5 && myMap->tileGrid[x][y+1].wall == 1){
        player = myMap->tileGrid[x+1][y].player;
    } else if (bombPos.timer > 5 && myMap->tileGrid[x+1][y].wall == 1){
        player = myMap->tileGrid[x][y+1].player;
    }
    return bombPos;
}