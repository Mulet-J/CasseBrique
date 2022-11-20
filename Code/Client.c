//
// Created by jules on 18/11/2022.
//

#include "Client.h"

void clientInit() {
#ifdef WIN32
    WSADATA wsa;
    if(WSAStartup(MAKEWORD(2, 2), &wsa) < 0)
    {
        puts("WSAStartup failed !");
        exit(EXIT_FAILURE);
    }
#endif
}

void clientEnd() {
#ifdef WIN32
    WSACleanup();
#endif
}

int client(char *ip) {
    SOCKET sock;
    int fd;
    struct sockaddr_in address;
    char *buffer = calloc(sizeof(char)*1024, sizeof(char)*1024);

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(ip);
    address.sin_port = htons(PORT);

    clientInit();
    if((sock = socket(AF_INET, SOCK_STREAM, 0)) == 0){
        perror("socket()");
        exit(errno);
    }
    if(connect(sock,(struct sockaddr*)&address, sizeof(address)) < 0){
        perror("connect()");
        exit(errno);
    }

    fd_set readfds;
    while(1){
        FD_ZERO(&readfds);
        FD_SET(sock,&readfds);

        if(select((int)sock+1, &readfds, NULL, NULL, NULL) < 1){
            perror("select()");
            exit(errno);
        }
        break;
    }
    char action;
    int play = 1;
    while (play){
        waitForServer(sock);
        recv(sock, &action, sizeof(int), 0);
        play = actionClient(action, sock);
    }
    closesocket(sock);
    clientEnd();
}

void waitForServer(SOCKET sock) {
    fd_set readfds;
    while(1){
        FD_ZERO(&readfds);
        FD_SET(sock,&readfds);

        if(select((int)sock+1, &readfds, NULL, NULL, NULL) < 1){
            perror("select()");
            exit(errno);
        }
        break;
    }
}

//défini ce que le client doit faire
int actionClient(char action, SOCKET sock) {
    char direction;
    switch (action) {
        case 1: //le client joue
            printString(sock);
            scanf(" %c", &direction); //entree utilisateur
            send(sock, &direction, sizeof(char),0); //envoie action
            waitForServer(sock); //se remet en attente
            return 1;
        case 2: //affiche la carte et attend
            printString(sock);
            waitForServer(sock); //se remet en attente
            return 1;
        case 3: //la partie est finie
            printString(sock);
            printf("La partie est terminée, en attente du serveur\n");
            waitForServer(sock);
            return 1;
        case 4: //le serveur s'arrête
            printf("Serveur deconnecte\n");
            return 0;
        default:
            perror("Action client inconnue\n");
            return 0;
    }
}

void printString(SOCKET sock) {
    char *buffer = calloc(sizeof(char)*1024, sizeof(char));
    recv(sock, buffer, sizeof(char)*1024,0);
    printf("%s", buffer);
    free(buffer);
}
