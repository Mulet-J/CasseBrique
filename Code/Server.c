//
// Created by jules on 18/11/2022.
//

#include "Server.h"
#include "Map.h"
#include "Player.h"
#include "Bomb.h"

//Example code: A simple server side code, which echos back the received message.
//Handle multiple socket connections with select and fd_set on Linux

void serverInit() {
#ifdef WIN32
    WSADATA wsa;
    if(WSAStartup(MAKEWORD(2, 2), &wsa) < 0)
    {
        puts("WSAStartup failed !");
        exit(EXIT_FAILURE);
    }
#endif
}

void serverEnd() {
#ifdef WIN32
    WSACleanup();
#endif
}

int server(int clientCount, char *map) {
    SOCKET sock, newSock, clientSocket[clientCount];
    int expectedClients = 0;
    struct sockaddr_in address;

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    int addrlen = sizeof(address);

    //initialisation du serveur
    serverInit();
    if((sock = socket(AF_INET, SOCK_STREAM, 0)) == 0){
        perror("socket()");
        exit(errno);
    }
    if(bind(sock, (struct sockaddr *)&address, sizeof(address)) < 0){
        perror("bind()");
        exit(errno);
    }
    if(listen(sock, 3) < 0){
        perror("listen()");
        exit(errno);
    }
    fd_set readfds;

    //attend les connexions
    while(1){
        if(expectedClients == clientCount){
            //tous les clients attendus sont connectés
            break;
        }
        FD_ZERO(&readfds);
        FD_SET(sock,&readfds);

        if(select((int)sock+1, &readfds, NULL, NULL, NULL) < 1){
            perror("select()");
            exit(errno);
        }

        if (FD_ISSET(sock, &readfds))
        {
            if ((newSock = accept(sock, (struct sockaddr *)&address, &addrlen)) < 0)
            {
                perror("accept");
                exit(EXIT_FAILURE);
            }
            clientSocket[expectedClients] = newSock;
            printf("Client %d connected\n", expectedClients);
            expectedClients++;
        }
    }
    Map myMap = convertMap(map);
    for (int i = 0; i < expectedClients; ++i) {
        myMap.players[i].isBot = 0;
    }
    boucleJeu(myMap,clientSocket);

    closesocket(sock);
    serverEnd();
    return 1;
}

void waitForClient(SOCKET sock) {
    fd_set readfds;
    while(1) {
        FD_ZERO(&readfds);
        FD_SET(sock, &readfds);

        if (select((int)sock + 1, &readfds, NULL, NULL, NULL) < 1) {
            perror("select()");
            exit(errno);
        }
        break;
    }
}

void sendToClient(SOCKET sock, Map *myMap) {
    char *buffer = mapToString(myMap);
    send(sock, buffer, sizeof(char)*1024,0);
}

void boucleJeu(Map myMap, SOCKET *clientSocket) {
    int latestPlayer;
    int play = 1;
    char *mess = malloc(sizeof(char)*1024);
    while(play){
        for (int i = 0; i < myMap.playerCount; ++i) {
            if(myMap.players[i].isAlive){
                //plus qu'un seul joueur
                if(latestPlayer == myMap.players[i].playerID){
                    char action = 4;
                    sprintf(mess, "Joueur %d a gagne\n",i);
                    for (int j = 0; j < myMap.playerCount-1; ++j) {
                        send(clientSocket[i],&action, sizeof(char),0);
                        //send(clientSocket[i], mess, sizeof(char)*1024,0);
                    }
                    play = 0;
                    break;
                }
                latestPlayer = myMap.players[i].playerID;
                if(i==0){
                    char direction;
                    printMap(&myMap);
                    scanf(" %c", &direction);
                    actionPlayer(&myMap, getPlayerByID(&myMap,i+1), direction);
                } else {
                    char action = 1;
                    char direction;
                    send(clientSocket[i-1],&action, sizeof(char),0);
                    sendToClient(clientSocket[i-1],&myMap);
                    waitForClient(clientSocket[i-1]);
                    recv(clientSocket[i-1], &direction, sizeof(char),0);
                    actionPlayer(&myMap, getPlayerByID(&myMap,i+1), direction);
                }
            }
            checkBomb(&myMap);
        }
    }
}

