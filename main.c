#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include "Player.h"
#include "Map.h"
#include "Utils.h"

void endParty(int *choice);

int main() {
    int mainMenu = menu();
    if(mainMenu == 1) {
        // Charger la map
        Map myMap = convertMap("../Maps/map3.txt");
        printMap(&myMap);
        while(1){
            if(getPlayerByID(&myMap,1)->isAlive != 1){
                int choice;
                printf("Game over\n\n");
                printf("\n1: Revenir au menu\n2: Quitter le jeu\n");
                scanf("%d", &choice);
                while (choice < 1 || choice > 2) {
                    printf("Rentrez un choix valide svp\n");
                    scanf("%d", &choice);
                }
                if(choice == 1) {
                    return main();
                }
                else if(choice == 2) {
                    printf("A bientot !");
                    return 0;
                }
            }
            if(getPlayerByID(&myMap,2)->isAlive != 1) {
                int choice;
                printf("You win !\n\n");
                printf("\n1: Revenir au menu\n2: Quitter le jeu\n");
                scanf("%d", &choice);
                while (choice < 1 || choice > 2) {
                    printf("Rentrez un choix valide svp\n");
                    scanf("%d", &choice);
                }
                if(choice == 1) {
                    return main();
                }
                else if(choice == 2) {
                    printf("A bientot !");
                    return 0;
                }
            }
            actionPlayer(&myMap, getPlayerByID(&myMap,1));
            checkBomb(&myMap);
            printMap(&myMap);
        }
    }
    if(mainMenu == 2) {
        int choice = 0;
        while(choice != 4) {
            printf("\n1: Map 1\n2: Map 2\n3: Map 3\n4: Retour au menu\n");
            printf("Choisir une map de la liste : \n");
            scanf("%d", &choice);
            while (choice < 1 || choice > 4) {
                printf("Cette map n'existe pas\n");
                scanf("%d", &choice);
            }
            selectMap(choice);
        }
    }
    if(mainMenu == 3) {
        printf("A bientot !");
        return 0;
    }
}