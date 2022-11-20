//
// Created by jules on 18/11/2022.
//

#ifndef CASSEBRIQUE_SERVER_H
#define CASSEBRIQUE_SERVER_H

#include "Structs.h"

int server(int clientCount, char *map);

void serverInit();

void serverEnd();

void waitForClient(SOCKET sock);

void sendToClient(SOCKET sock, Map *myMap);

void boucleJeu(Map myMap, SOCKET clientSocket[]);

#endif //CASSEBRIQUE_SERVER_H
