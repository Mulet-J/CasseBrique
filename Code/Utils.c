//
// Created by jules on 26/10/2022.
//
#include <time.h>
#include "Utils.h"
#include "Map.h"
#include "Server.h"
#include "Client.h"

/**
 * Affichage du menu
 * @return Retour 0 en cas de fermeture du programme
 */
int menu() {
    int choice = 0;
    int play = 1;
    int clientCount = 0;
    char *ip = calloc(sizeof(char)*20, sizeof(char));
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
                            play = playGameSolo(myMapSelection->maps[i].map);
                            printf("1 pour passer a la carte suivante, 0 pour arreter\n");
                            scanf("%d",&play);
                            if(play == 0){
                                break;
                            }
                        }
                    }
                }
                free(myMapSelection->maps);
                free(myMapSelection);
                return 1;
            case 2:
                //démarrer le serveur

                printf("Nombre de clients\n");
                scanf("%d", &clientCount);
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
                            play = server(clientCount, "map1.txt");
                            scanf("%d",&play);
                            if(play == 0){
                                break;
                            }
                        }
                    }

                }
                return 1;
            case 3:
                //rejoindre un serveur
                printf("Entrer l'ip de l'hote\n");
                scanf("%s", ip);
                client("127.0.0.1");
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
