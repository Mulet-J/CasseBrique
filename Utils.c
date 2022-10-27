//
// Created by jules on 26/10/2022.
//
#include "Utils.h"

void selectMap() {
    int choice = 0;
    while(choice != 4) {
        printf("\n1: Map 1\n2: Map 2\n3: Map 3\n4: Retour au menu\n");
        printf("Choisir une map de la liste : \n");
        scanf("%d", &choice);
        while (choice < 1 || choice > 4) {
            printf("Cette map n'existe pas\n");
            scanf("%d", &choice);
        }
        if (choice == 1) {
            Map myMap = convertMap("../Maps/map1.txt");
            printMap(&myMap);
        } else if (choice == 2) {
            Map myMap = convertMap("../Maps/map2.txt");
            printMap(&myMap);
        } else if (choice == 3) {
            Map myMap = convertMap("../Maps/map3.txt");
            printMap(&myMap);
        } else if (choice == 4){
            menu();
        }
    }

}

int menu() {
    int mainMenu;
    printf("Menu principal:\n1. Nouvelle partie\n2. Voir les maps\n3. Quitter le jeu\n\n");
    scanf("%d", &mainMenu);
    while(mainMenu < 1 || mainMenu > 3) {
        printf("Entrez un nombre entre 1 et 3\n");
        scanf("%d", &mainMenu);
    }
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
                    return 1;
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
                    return 1;
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
        selectMap();
    }
    if(mainMenu == 3) {
        printf("A bientot !");
        return 0;
    }
    return 1;
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#endif
#ifdef __linux__
    system("clear");
#endif
}
