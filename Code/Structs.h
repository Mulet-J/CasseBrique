//
// Created by jules on 02/11/2022.
//

#ifndef CASSEBRIQUE_STRUCTS_H
#define CASSEBRIQUE_STRUCTS_H

#ifdef WIN32 /* si vous êtes sous Windows */

#include <winsock2.h>

#elif defined (linux) /* si vous êtes sous Linux */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> /* close */
#include <netdb.h> /* gethostbyname */
#define INVALID_SOCKET (-1)
#define SOCKET_ERROR (-1)
#define closesocket(s) close(s)
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

#else /* sinon vous êtes sur une plateforme non supportée */

#error not defined for this platform

#endif

#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>

#define PORT 5000
typedef struct Items {
    int kickbomb;
    int passbomb;
    int firepower;
} Items;
typedef struct Player {
    int playerID;
    int health;
    int bombStrength;
    int bombCount;
    int invincibility;
    int isAlive;
    int isBot;
    Items items;
} Player;

typedef struct Bomb{
    int playerID;
    int timer;
    int strength;
    Items items;
} Bomb;

typedef struct  Tile {
    int wall;
    int powerUP;
    Player *player;
    Bomb bomb;
    Items items;
} Tile;

typedef struct Map {
    int width;
    int height;
    int playerCount;
    Player *players;
    Tile **tileGrid;
} Map;

typedef struct MapState{
    char *map;
    int isActive;
    int maxPlayers;
} MapState;

typedef struct MapSelection {
    MapState *maps;
    int count;
} MapSelection;

#endif //CASSEBRIQUE_STRUCTS_H