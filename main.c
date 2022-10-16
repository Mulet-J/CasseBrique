#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct Player {
    int playerID;
    int health;
    int bombStrength;
    int bombCount;
    int invincibility;
} Player;

typedef struct Bomb{
    int playerID;
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
    Player *players;
    Tile **tileGrid;
} Map;

Bomb newBomb(Player *myPlayer){
    Bomb myBomb = {
            .timer = 14,
            .strength = myPlayer->bombStrength,
            .playerID = myPlayer->playerID,
    };
    myPlayer->bombCount -= 1;
    return myBomb;
}

Bomb nullBomb(){
    Bomb myBomb = {
            .timer = 0,
            .strength = 0,
            .playerID = 0,
    };
    return myBomb;
}

Bomb *getBomb(Map myMap, int x, int y){
    return &myMap.tileGrid[x][y].bomb;
}

Player newPlayer(int playerID){
    Player myPlayer = {
            .bombCount = 4,
            .bombStrength = 3,
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

void actionPlayer(Map *myMap,Player *myPlayer){
    int xPlayer;
    int yPlayer;
    char direction;
    for (int x = 0; x < myMap->height; ++x) {
        for (int y = 0; y < myMap->width; ++y) {
            if(myMap->tileGrid[x][y].player.playerID == myPlayer->playerID){
                xPlayer = x;
                yPlayer = y;
            }
        }
    }
    scanf("%c",&direction);
    switch (direction) {
        case 'z':
            if(xPlayer != 0 && myMap->tileGrid[xPlayer-1][yPlayer].wall == 0 && myMap->tileGrid[xPlayer-1][yPlayer].player.playerID == 0 && myMap->tileGrid[xPlayer-1][yPlayer].bomb.playerID == 0){
                myMap->tileGrid[xPlayer-1][yPlayer].player = myMap->tileGrid[xPlayer][yPlayer].player;
                myMap->tileGrid[xPlayer][yPlayer].player = nullPlayer();
            }
            break;
        case 'q':
            if(yPlayer != 0 && myMap->tileGrid[xPlayer][yPlayer-1].wall == 0 && myMap->tileGrid[xPlayer][yPlayer-1].player.playerID == 0 && myMap->tileGrid[xPlayer][yPlayer-1].bomb.playerID == 0){
                myMap->tileGrid[xPlayer][yPlayer-1].player = myMap->tileGrid[xPlayer][yPlayer].player;
                myMap->tileGrid[xPlayer][yPlayer].player = nullPlayer();
            }
            break;
        case 's':
            if(xPlayer != myMap->height-1 && myMap->tileGrid[xPlayer+1][yPlayer].wall == 0 && myMap->tileGrid[xPlayer+1][yPlayer].player.playerID == 0 && myMap->tileGrid[xPlayer+1][yPlayer].bomb.playerID == 0){
                myMap->tileGrid[xPlayer+1][yPlayer].player = myMap->tileGrid[xPlayer][yPlayer].player;
                myMap->tileGrid[xPlayer][yPlayer].player = nullPlayer();
            }
            break;
        case 'd':
            if(yPlayer != myMap->width-1 && myMap->tileGrid[xPlayer][yPlayer+1].wall == 0 && myMap->tileGrid[xPlayer][yPlayer+1].player.playerID == 0 && myMap->tileGrid[xPlayer][yPlayer+1].bomb.playerID == 0){
                myMap->tileGrid[xPlayer][yPlayer+1].player = myMap->tileGrid[xPlayer][yPlayer].player;
                myMap->tileGrid[xPlayer][yPlayer].player = nullPlayer();
            }
            break;
        case ' ':
            if(myMap->tileGrid[xPlayer][yPlayer].bomb.playerID == 0 && myMap->tileGrid[xPlayer][yPlayer].player.bombCount > 0){
                myMap->tileGrid[xPlayer][yPlayer].bomb = newBomb(myPlayer);
            }
            break;
        default:
            break;
    }
}

Player *getPlayerByID(Map *myMap, int playerID){
    for (int x = 0; x < myMap->height; ++x) {
        for (int y = 0; y < myMap->width; ++y) {
            if(myMap->tileGrid[x][y].player.playerID == playerID){
                return &myMap->tileGrid[x][y].player;
            }
        }
    }
    return NULL;
}

Map newMap(int height, int width) {
    //toujours initialiser toutes les valeurs même vides
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
                myMap.tileGrid[x][y].wall = 2;
            } else {
                //vide
            }
        }
    }
    return myMap;
}

void printMap(Map *myMap){
    //system("cls");  //vide la console sous windows
    for (int x = 0; x < myMap->height; ++x) {
        for (int y = 0; y <myMap->width; ++y) {
            if(myMap->tileGrid[x][y].wall==1){
                printf("X ");
            } else if(myMap->tileGrid[x][y].wall==2) {
                printf("# ");
            } else if(myMap->tileGrid[x][y].player.playerID !=0 ) {
                printf("p ");
            } else if(myMap->tileGrid[x][y].bomb.playerID !=0 ) {
                printf("b ");
            } else {
                printf("  ");
            }
        }
        printf("\n");
    }
}

void bombExplode(Map *myMap, int x, int y){
    //ignorer erreur c'est géré
    Bomb *myBomb = getBomb(*myMap,x,y);
    Player *myPlayer = getPlayerByID(myMap,myBomb->playerID);
    myPlayer->bombCount++;
    myBomb->playerID = 0;

    for (int i = 0; i < myBomb->strength; ++i) {
        if(x-i>=0){
            if(myMap->tileGrid[x-i][y].player.playerID != 0){ //joueur présent

            }
            if(myMap->tileGrid[x-i][y].wall == 2){ //mur destructible
                myMap->tileGrid[x-i][y].wall = 0;
            }
            if(myMap->tileGrid[x-i][y].bomb.playerID != 0){ //bombe présente
                bombExplode(myMap,x-i,y);
            }
        }
        if(y-i>=0){
            if(myMap->tileGrid[x][y-i].player.playerID != 0){ //joueur présent

            }
            if(myMap->tileGrid[x][y-i].wall == 2){ //mur destructible
                myMap->tileGrid[x][y-i].wall = 0;
            }
            if(myMap->tileGrid[x][y-i].bomb.playerID != 0){ //bombe présente
                bombExplode(myMap,x,y-i);
            }
        }
        if(x+i<=myMap->height){
            if(myMap->tileGrid[x+i][y].player.playerID != 0){ //joueur présent

            }
            if(myMap->tileGrid[x+i][y].wall == 2){ //mur destructible
                myMap->tileGrid[x+i][y].wall = 0;
            }
            if(myMap->tileGrid[x+i][y].bomb.playerID != 0){ //bombe présente
                bombExplode(myMap,x+i,y);
            }
        }
        if(y+i<=myMap->width){
            if(myMap->tileGrid[x][y+i].player.playerID != 0){ //joueur présent

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

void checkBomb(Map *myMap){
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

int main() {
    Map myMap = newMap(11,11);
    printMap(&myMap);
    for (int i = 0; i < 200; ++i) {
        //la boucle ignore 1/2 scanf et jsp pk
        actionPlayer(&myMap, getPlayerByID(&myMap,2));
        checkBomb(&myMap);
        printMap(&myMap);
    }
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
