//
// Created by jules on 26/10/2022.
//
#include "Utils.h"
#include "Map.h"
#include "Player.h"
#include "Bomb.h"
#include <time.h>

/**
 * Selection des cartes
 */

void insert(int *arr, int N, int position, int value) {
    for(int i = N-1; i >= position; i--) {
        arr[i+1] = arr[i];
    }
    arr[position] = value;
}



int selectMap() {
    int choice = 0;
    int length = 0;
    int arrMap[length];
    srand(time(NULL));
    while(choice != 4) {
        printf("\n1: Map 1\n2: Map 2\n3: Map 3\n4: Lancer la partie\n");
        printf("Choisir une map de la liste : \n");
        scanf("%d", &choice);
        while (choice < 1 || choice > 4) {
            printf("Cette map n'existe pas\n");
            scanf("%d", &choice);
        }
        if (choice == 1) {
            length+=1;
            /*
             * PROBLEME AVEC LE CONTAIN : REMPLI LE TABLEAU AVEC MAX 2 VALEURS
             */
            /*if(contains(arrMap, length, choice)) {
                printf("Map deja ajoutee \n");
                length--;
            } else { */
                insert(arrMap, length, 0, 1);
            //}
            for(int j = 0; j < length; j++) {
                printf("%d ", arrMap[j]);
            }
        } else if (choice == 2) {
            length+=1;
            /*if(contains(arrMap, length, choice)) {
                printf("Map deja ajoutee \n");
                length--;
            } else { */
            insert(arrMap, length, 0, 2);
            //}
            for(int j = 0; j < length; j++) {
                printf("%d ", arrMap[j]);
            }
        } else if (choice == 3) {
            length+=1;
            /*if(contains(arrMap, length, choice)) {
                printf("Map deja ajoutee \n");
                length--;
            } else { */
            insert(arrMap, length, 0, 3);
            //}
            for(int j = 0; j < length; j++) {
                printf("%d ", arrMap[j]);
            }
        } else if(choice == 4) {
            break;
        }
        // printf("LANCER LE JEU");

        // Lancer le jeu
        // printf("%d", res);
    }
    printf("LEN:%d :LEN", length);
    int res = rand()%length;
    printf("RES:%d :RES", arrMap[res]);
    return arrMap[res];
}

void showMap() {
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
        } else if (choice == 4) {

        }
    }
}

/**
 * Affichage du menu
 * @return Retour 0 en cas de fermeture du programme
 */
int menu() {
    int choice = 0;
    int play = 1;
    while(choice < 1 || choice > 4) {
        printf("Menu principal:\n1. Demarrer\n2. Demarrer le serveur\n3. Rejoindre un serveur\n4. Quitter le jeu\n");
        MapSelection *myMapSelection = getAlltxtMap();
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                //jouer en solo
                while (1){
                    printf("1/2/3/n pour ajouter une carte (une a la fois). 0 pour lancer le jeu\n");
                    printAvailableMaps(myMapSelection);
                    scanf("%d", &choice);
                    if(choice == 0){
                        break;
                    }
                    toggleMapSelect(myMapSelection, choice);
                }
                while(play){
                    for (int i = 0; i < myMapSelection->count; ++i) {
                        if(myMapSelection->maps[i].isActive){
                            play = playGame(myMapSelection->maps[i].map,1);
                            printf("1 pour passer a la carte suivante, 0 pour arreter\n");
                            scanf("%d",&play);
                        }
                    }
                }
                return 1;
            case 2:
                //démarrer le serveur
                return 1;
            case 3:
                //rejoindre un serveur
                return 1;
            case 4:
                //fermer l'application
                return 0;
            default:
                printf("Merci d'entrer un choix valable\n");
                choice = 0;
                break;
        }
    }
    return 1;
}

void printAvailableMaps(MapSelection *maps) {
    for (int i = 0; i < maps->count; ++i) {
        printf("Carte %d : %s Nb joueurs max : %d Selectionne : %d\n",i+1,maps->maps[i].map,maps->maps[i].maxPlayers, maps->maps[i].isActive);
    }
}

void toggleMapSelect(MapSelection *maps, int choice) {
    choice--;
    if(maps->maps[choice].isActive == 0){
        maps->maps[choice].isActive = 1;
    } else {
        maps->maps[choice].isActive = 0;
    }
}

int getMapPlayerCount(char *filename) {
    char path[256] = "../Maps/";
    strcat(path,filename);
    FILE *map = fopen(path,"r");
    int count;
    fscanf(map,"%d",&count);
    return count;
}

MapSelection *getAlltxtMap() {
    DIR *d;
    int count = 0;
    MapState **maps = malloc(sizeof(MapSelection*)*1024);
    struct dirent *dir;
    d = opendir("../Maps/");
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            if(strcmp(dir->d_name,"format.txt") != 0 && strcmp(dir->d_name,".") != 0 && strcmp(dir->d_name,"..") != 0){
                maps[count] = malloc(sizeof(MapState));
                maps[count]->map = malloc(sizeof(char) * 256);
                maps[count]->isActive = 0;
                maps[count]->maxPlayers = getMapPlayerCount(dir->d_name);
                strcpy(maps[count]->map, dir->d_name);
                ++count;
            }
        }
        closedir(d);
    }
    MapSelection *selection = malloc(sizeof(MapSelection));
    selection->maps = malloc(sizeof(MapState)*count);
    selection->count = count;
    for (int i = 0; i < selection->count; ++i) {
        selection->maps[i] = *maps[i];
    }
    free(maps);
    return selection;
}

/**
 * Vide la console
 */
void clearScreen() {
#ifdef _WIN32
    system("cls");
#endif
#ifdef __linux__
    system("clear");
#endif
}
