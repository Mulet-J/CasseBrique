//
// Created by jules on 26/10/2022.
//

#ifndef CASSEBRIQUE_MAP_H
#define CASSEBRIQUE_MAP_H
#include "Structs.h"

void printMap(Map *myMap);

Map convertMap(char *filename);

int playGameSolo(char *filename);

char *mapToString(Map *myMap);

#endif //CASSEBRIQUE_MAP_H
