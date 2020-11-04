#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h> 
#include<arpa/inet.h>               

void str_cli(FILE *fp, int sockfd, struct sockaddr *addr, socklen_t addrlen)
{
    int bufsize = 1024, cont;
    char *buffer = malloc(bufsize);

    while(fgets(buffer,bufsize,fp)!=NULL)
    {
        sendto(sockfd, buffer, sizeof(buffer), 0, addr, addrlen);  

        if((cont=recvfrom(sockfd, buffer, bufsize, 0, addr, &addrlen))>0) {  // SERVER--- Msg—- CLIENT
            fputs(buffer,stdout);
        }
    }
    printf("\nEOF\n");
}
int main(int argc,char *argv[])
{
    int create_socket;
    struct sockaddr_in address;
    if ((create_socket = socket(AF_INET,SOCK_DGRAM,0)) > 0)
        printf("The Socket was created\n");
    address.sin_family = AF_INET;
    address.sin_port = htons(15001);
    address.sin_addr.s_addr = INADDR_ANY; 
    socklen_t addrlen = sizeof(struct sockaddr_in);
    str_cli(stdin,create_socket,(struct sockaddr *)&address,addrlen);
    return close(create_socket);
}