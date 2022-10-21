//
// Created by jules on 26/10/2022.
//
#include "Utils.h"

void selectMap(int choice) {
    if (choice == 1) {
        Map myMap = convertMap("../Maps/map1.txt");
        printMap(&myMap);
    } else if (choice == 2) {
        Map myMap = convertMap("../Maps/map2.txt");
        printMap(&myMap);
    } else if (choice == 3) {
        Map myMap = convertMap("../Maps/map3.txt");
        printMap(&myMap);
    } //else if (choice == 4) main();
}

int menu() {
    int choice;
    printf("Menu principal:\n1. Nouvelle partie\n2. Voir les maps\n3. Quitter le jeu\n\n");
    scanf("%d", &choice);
    while(choice < 1 || choice > 3) {
        printf("Entrez un nombre entre 1 et 3\n");
        scanf("%d", &choice);
    }
    return choice;
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#endif
#ifdef __linux__
    system("clear");
#endif
}
