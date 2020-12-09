#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include<arpa/inet.h>
#include<string.h>

int clients[20];
int len = 0;

void str_echo(int connfd) {
    int n,i;
    int bufsize = 10240;
    int respsize = 10340;
    char *buffer = malloc(bufsize);
    char *response = malloc(respsize);
    //printf("inside the function");
    while((n=recv(connfd, buffer, bufsize, 0))>0) {
        sprintf(response,"Client %d   %s", len, buffer);
        printf("%s", response);
        send(connfd, response, sizeof(response), 0);
        bzero(buffer,10240);
    }
}
int main() {
    int cont,listenfd,connfd,addrlen,addrlen2,fd,pid,addrlen3;
    int i;
    for(i=0;i<20;i++)
        clients[i] = -1;
    //char fname[256];
    struct sockaddr_in address,cli_address;
    if ((listenfd = socket(AF_INET,SOCK_STREAM,0)) > 0) //sockfd
        printf("The socket was created\n");
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(16001);
    printf("The address before bind %s ...\n",inet_ntoa(address.sin_addr));
    if (bind(listenfd,(struct sockaddr *)&address,sizeof(address)) == 0)
        printf("Binding Socket\n");
    printf("The address after bind %s...\n",inet_ntoa(address.sin_addr) );
    listen(listenfd,3);
    printf("server is listening\n");
    //server local address
    getsockname(listenfd,(struct sockaddr *)&address,&addrlen3);
    printf("The server's local address %s ...and port%d\n",inet_ntoa(address.sin_addr),htons(address.sin_port));
    for(;;) {
        addrlen = sizeof(struct sockaddr_in);
        connfd = accept(listenfd,(struct sockaddr *)&cli_address,&addrlen);
        //printf("The address %s ...\n",inet_ntoa(address.sin_addr) );
        addrlen2 = sizeof(struct sockaddr_in);
        printf("The Client %s is Connected...on port%d\n",inet_ntoa(cli_address.sin_addr),htons(cli_address.sin_port));
        clients[len++] = connfd;
        if((pid=fork())==0)
        {
            printf("inside child\n");
            close(listenfd);
            str_echo(connfd);
            exit(0);
        }
        close(connfd);
    }
    return 0 ;
}