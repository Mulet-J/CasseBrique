//
// Created by jules on 18/11/2022.
//

#ifndef CASSEBRIQUE_CLIENT_H
#define CASSEBRIQUE_CLIENT_H

#include "Structs.h"

int client(char *ip);

void printString(SOCKET sock);

void waitForServer(SOCKET sock);

void sendToServer(SOCKET sock);

int actionClient(char action, SOCKET sock);
#endif //CASSEBRIQUE_CLIENT_H
