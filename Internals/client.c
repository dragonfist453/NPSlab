#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>            
#include<arpa/inet.h>    

void str_cli(FILE *fp, int sockfd)
{
    int bufsize = 1024, cont;
    char *buffer = malloc(bufsize);

    while(fgets(buffer,bufsize,fp)!=NULL)
    {
        send(sockfd, buffer, sizeof(buffer), 0);  

        if((cont=recv(sockfd, buffer, bufsize, 0))>0) {
            fputs(buffer,stdout);
        }
    }
    printf("\nEOF\n");
}
int main(int argc,char *argv[])
{
    int create_socket,addrlen,connfd;
    struct sockaddr_in address;
    if ((create_socket = socket(AF_INET,SOCK_STREAM,0)) >= 0)
        printf("The Socket was created\n");
    else {
        printf("Error in socket creation :(\nExitting!");
        exit(0);
    }
    address.sin_family = AF_INET;
    address.sin_port = htons(15001);
    inet_pton(AF_INET,argv[1],&address.sin_addr);
    if ((connfd = connect(create_socket,(struct sockaddr *) &address, sizeof(address))) == 0) {
        addrlen = sizeof(struct sockaddr_in);
        int i = getpeername(connfd, (struct sockaddr *)&address, &addrlen);
        printf("The connection was accepted with the server %s and port %d\n",inet_ntoa(address.sin_addr),htons(address.sin_port));
    }
    else {
        printf("Error in connect :(\nExitting!\n");
        exit(0);
    }
    str_cli(stdin,create_socket);
    return close(create_socket);
}