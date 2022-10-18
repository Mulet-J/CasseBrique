#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

typedef struct Player {
    int playerID;
    int health;
    int bombStrength;
    int bombCount;
    int invincibility;
    int isAlive;
} Player;

typedef struct Bomb{
    int playerID;
    int timer;
    int strength;
} Bomb;

typedef struct  Tile {
    int wall;
    int powerUP;
    Player *player;
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
            .timer = 8,
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

Player newPlayer(int playerID, int bombCount, int bombStrength){
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

void actionPlayer(Map *myMap,Player *myPlayer){
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

Player *getPlayerByID(Map *myMap, int playerID){
    return &myMap->players[playerID-1];
}

Player *getPlayerByPos(Map *myMap, int x, int y){
    return myMap->tileGrid[x][y].player;
}

void printMap(Map *myMap){
    //system("cls");  //vide la console sous windows
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
}

void playerDie(Map *myMap, int x, int y){
    Player *myPlayer = getPlayerByPos(myMap,x,y);
    myPlayer->isAlive = 0;
    myMap->tileGrid[x][y].player = NULL;
}

void bombExplode(Map *myMap, int x, int y){
    //ignorer warning c'est géré
    Bomb *myBomb = getBomb(*myMap,x,y);
    Player *myPlayer = getPlayerByID(myMap,myBomb->playerID);
    myPlayer->bombCount++;
    myBomb->playerID = 0;

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

int menu(){
    int choice;
    printf("Bienvenue dans Casse-briques !\n\n");
    printf("Menu principal:\n1. Nouvelle partie\n2. Voir les maps\n3. Quitter le jeu\n\n");
    scanf("%d", &choice);
    while(choice < 1 || choice > 3) {
        printf("Entrez un nombre entre 1 et 3\n");
        scanf("%d", &choice);
    }
    return choice;
}

Map convertMap(char *path){
    int playerCount,bombCount,bombStrength, width, height;
    FILE *map = fopen(path,"r");
    fscanf(map, "%d %d %d %d %d", &playerCount, &bombCount, &bombStrength, &width, &height);
    int playerID = 1;
    Map myMap = {
            .height = height,
            .width = width,
            .players = malloc(sizeof(Player)*playerCount),
            .tileGrid = malloc(sizeof(Tile)*height),
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
    return myMap;
}

int main() {
    /*
    Map myMap = convertMap("../Maps/map3.txt");
    printMap(&myMap);
    printf("\n");
    printf("%d", getPlayerByID(&myMap,3)->playerID);
*/
    int mainMenu = menu();
    if(mainMenu == 1) {
        // Charger la map
        Map myMap = convertMap("../Maps/map3.txt");
        printMap(&myMap);
        while(1){
            if(getPlayerByID(&myMap,1)->isAlive != 1){
                printf("Game over");
                return 0;
            }
            actionPlayer(&myMap, getPlayerByID(&myMap,1));
            checkBomb(&myMap);
            printMap(&myMap);
        }
    }
    if(mainMenu == 2) {
        int choice;
        printf("Affiche la liste des maps\n");
        printf("Choisir une map de la liste : ");
        scanf("%d", &choice);
        printf("%d", choice);
    }
    if(mainMenu == 3) {
        printf("A bientot !");
        return 0;
    }
    /*
     * boucle de jeu :
     * afficher carte
     * entrées utilisateurs
     * action joueurs
     * check bombes
     * check joueur en vie
     */
}