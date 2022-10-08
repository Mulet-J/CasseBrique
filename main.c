#include <stdio.h>
#include <stdlib.h>

typedef struct Map {
    int width;
    int height;
    short **grid;
} Map;
/*
 * 0 = vide
 * 1-4 = joueurs
 * 5 = mur indestructible
 * 6 = mur destructible
 */
Map createMap(int height, int width){
    Map myMap = {
            .width = width,
            .height = height,
            .grid = malloc(sizeof(int)*(height*2)),  //marche pas avec seulement height
    };
    for (int i = 0; i < myMap.height; ++i) {
        myMap.grid[i] = malloc(sizeof(int)*myMap.width);
        for (int j = 0; j < myMap.width; ++j) {
            if(i==0 || j==0 || i==height-1 || j==width-1){
                myMap.grid[i][j] = 5;
            } else if(i%2 == 0 && j%2 == 0){
                myMap.grid[i][j] = 6;
            } else {
                myMap.grid[i][j] = 0;
            }
        }
    }
    return myMap;
}

void printMap(Map *myMap){
    system("cls");
    for (int i = 0; i < myMap->height; ++i) {
        for (int j = 0; j <myMap->width; ++j) {
            if(myMap->grid[i][j] == 0){
                printf("  ");
            } else if(myMap->grid[i][j] == 5){
                //printf("█ ");
                printf("x ");
            } else if(myMap->grid[i][j] == 6){
                //printf("# ");
                printf("# ");
            }
            //printf("%d ",myMap->grid[i][j]);
        }
        printf("\n");
    }
}

int main() {

    Map myMap = createMap(11,11);
    printMap(&myMap);
    //printf("Hello, World!\n");
    return 0;
}
