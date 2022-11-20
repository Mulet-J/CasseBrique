//
// Created by jules on 26/10/2022.
//

#ifndef CASSEBRIQUE_UTILS_H
#define CASSEBRIQUE_UTILS_H
#include "Structs.h"

int menu();

void clearScreen();

MapSelection *getAlltxtMap();

int getMapPlayerCount(char *filename);

void printAvailableMaps(MapSelection *maps);

void toggleMapSelect(MapSelection *maps, int choice);

#endif //CASSEBRIQUE_UTILS_H
