#include <stdio.h>
#include <stdlib.h>

typedef struct Map {
    int width;
    int height;
    int **grid;
} Map;
/*
 * 0 = vide
 * 1-4 = joueurs
 * 5 = mur indestructible
 * 6 = mur destructible
 */
Map createMap(int height, int width){
    int player = 1;
    Map myMap = {
            .width = width,
            .height = height,
            .grid = malloc(sizeof(int)*(height*2)),  //marche pas avec seulement height
    };
    for (int i = 0; i < myMap.height; ++i) {
        myMap.grid[i] = malloc(sizeof(int)*myMap.width);
        for (int j = 0; j < myMap.width; ++j) {
            if (i == 0 || j == 0 || i == height - 1 || j == width - 1) {
                myMap.grid[i][j] = 5;
            } else if ((i==1 || i == height-2) && (j==1 || j==width-2)) {
                myMap.grid[i][j] = player;
                player++;
            } else if (i%2 == 0 && j%2 == 0) {
                myMap.grid[i][j] = 6;
            } else {
                myMap.grid[i][j] = 0;
            }
        }
    }
    return myMap;
}

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

void printMap(Map *myMap){
    system("cls");  //vide la console sous windows
    for (int i = 0; i < myMap->height; ++i) {
        for (int j = 0; j <myMap->width; ++j) {
            switch (myMap->grid[i][j]) {
                case 0:
                    printf("  ");
                    break;
                case 1:
                case 2:
                case 3:
                case 4:
                    printf("%d ", myMap->grid[i][j]);
                    break;
                case 5:
                    printf("x ");
                    break;
                case 6:
                    printf("# ");
                    break;
            }
            //printf("%d ",myMap->grid[i][j]);
        }
        printf("\n");
    }
}

int main() {
    Map myMap = createMap(11,11);
    printMap(&myMap);
    /*
     * boucle de jeu :
     * afficher carte
     * entrées utilisateurs
     * action joueurs
     * check bombes
     * check joueur en vie
     */

    //printf("Hello, World!\n");
    return 0;
}
