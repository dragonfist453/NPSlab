#include<sys/types.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<netinet/in.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<arpa/inet.h>
void echo(int connfd) {
    int n;
    int bufsize = 1024;
    char *buffer = malloc(bufsize);
    do {
        while((n=recv(connfd, buffer, bufsize, 0)) > 0)
            send(connfd, buffer, n, 0);
    }while(n<0);
}

int main() {
    int listenfd, connfd, addrlen,pid;
    struct sockaddr_in address,cli_address;

    //Creation of socket
    if((listenfd = socket(AF_INET, SOCK_STREAM,0)) >= 0) {
        printf("Socket was successfully created\n");
    }
    else {
        printf("Error in socket creation :(\nExitting!\n");
        exit(0);
    }

    //Address specification
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(15001);

    //Binding socket
    if((bind(listenfd, (struct sockaddr *)&address, sizeof(address))) >= 0) {
        printf("Socket binded successfully\n");
    }
    else {
        printf("Error on binding socket :(\nExitting!\n");
        exit(0);
    }

    //Listen to socket
    listen(listenfd, 3);
    printf("The server's local address %s and port %d\n",inet_ntoa(address.sin_addr),htons(address.sin_port));

    while(1) {
        addrlen = sizeof(struct sockaddr_in);
        connfd = accept(listenfd, (struct sockaddr*)&cli_address, &addrlen);
        int i = getpeername(connfd,(struct sockaddr *)&cli_address,&addrlen);
        printf("The Client  %s is Connected on port %d\n",inet_ntoa(cli_address.sin_addr),htons(cli_address.sin_port));
        if((pid=fork()) == 0) {
            close(listenfd);
            echo(connfd);
            exit(0);
        }
        close(connfd);
    }
    return 0;
}