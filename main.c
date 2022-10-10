#include <stdio.h>
#include <stdlib.h>

typedef struct Player {
    int playerID;
    int health;
    int bombStrength;
    int bombCount;
    int invincibility;
} Player;

typedef struct Bomb{
    int timer;
    int strength;
} Bomb;

typedef struct  Tile {
    int wall;
    int powerUP;
    Player player;
    Bomb bomb;
} Tile;

typedef struct Map {
    int width;
    int height;
    Tile **tileGrid;
} Map;

void movePlayer(Map *myMap,int playerID, char direction){
    switch (direction) {
        case 'z':
            break;
        case 'q':
            break;
        case 's':
            break;
        case 'd':
            break;
        default:
            break;
    }
}

void bombExplode(Map *myMap,int x, int y){

}

Player newPlayer(int playerID){
    Player myPlayer = {
            .bombCount = 1,
            .bombStrength = 2,
            .health = 1,
            .invincibility = 0,
            .playerID = playerID,
    };
    return myPlayer;
}

Player nullPlayer(){
    Player myPlayer = {
            .bombCount = 0,
            .bombStrength = 0,
            .health = 0,
            .invincibility = 0,
            .playerID = 0,
    };
    return myPlayer;
}

Bomb newBomb(int strength){
    Bomb myBomb = {
            .timer = 4,
            .strength = strength,
    };
    return myBomb;
}

Bomb nullBomb(){
    Bomb myBomb = {
            .timer = 0,
            .strength = 0,
    };
    return myBomb;
}

Map newMap(int height, int width) {
    //reste initialiser toutes les valeurs même vides
    int playerID = 1;
    Map myMap = {
            .height = height,
            .width = width,
            .tileGrid = malloc(sizeof(Tile)*height),
    };
    for (int x = 0; x < myMap.height; ++x) {
        myMap.tileGrid[x] = malloc(sizeof(Tile)*height);
        for (int y = 0; y < myMap.width; ++y) {
            myMap.tileGrid[x][y].wall = 0;
            myMap.tileGrid[x][y].powerUP = 0;
            myMap.tileGrid[x][y].player = nullPlayer();
            myMap.tileGrid[x][y].bomb = nullBomb();
            //myMap.tileGrid[x][y].player. = ;
            if (x == 0 || y == 0 || x == height - 1 || y == width - 1) {
                myMap.tileGrid[x][y].wall = 1;
            } else if ((x==1 || x == height-2) && (y==1 || y==width-2)) {
                Player myPlayer = newPlayer(playerID);
                myMap.tileGrid[x][y].player = myPlayer;
                playerID++;
                //player
            } else if (x%2 == 0 && y%2 == 0) {
                //mur milieu carte
            } else {
                //vide
            }
        }
    }
    return myMap;
}

void printMap(Map *myMap){
    system("cls");  //vide la console sous windows
    for (int x = 0; x < myMap->height; ++x) {
        for (int y = 0; y <myMap->width; ++y) {
            if(myMap->tileGrid[x][y].wall==1){
                printf("X ");
            } else if(myMap->tileGrid[x][y].wall==2) {
                printf("# ");
            } else if(myMap->tileGrid[x][y].player.playerID !=0 ) {
                printf("p ");
            } else if(myMap->tileGrid[x][y].bomb.strength !=0 ) {
                printf("b ");
            } else {
                printf("  ");
            }
        }
        printf("\n");
    }
}

int main() {
    Map myMap = newMap(11,11);
    printMap(&myMap);
    /*
     * boucle de jeu :
     * afficher carte
     * entrées utilisateurs
     * action joueurs
     * check bombes
     * check joueur en vie
     */

    return 0;
}
