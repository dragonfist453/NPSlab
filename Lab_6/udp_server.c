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

void str_echo(int connfd, struct sockaddr *cli_addr, socklen_t addrlen)
{
    int n;
    int bufsize = 1024;
    char *buffer = malloc(bufsize);
    while((n=recvfrom(connfd, buffer, bufsize, 0, cli_addr, &addrlen))>0)	
        sendto(connfd,buffer,n,0, cli_addr, addrlen);
}
int main()
{
    int cont,connfd;
    socklen_t addrlen;
    struct sockaddr_in serv_address,cli_address;
    memset(&serv_address, 0, sizeof(serv_address)); 
    memset(&cli_address, 0, sizeof(cli_address)); 
    if ((connfd = socket(AF_INET,SOCK_DGRAM,0)) > 0)
        printf("The socket was created\n");
    serv_address.sin_family = AF_INET;
    serv_address.sin_addr.s_addr = INADDR_ANY;
    serv_address.sin_port = htons(15001);

    if (bind(connfd, (const struct sockaddr *)&serv_address, sizeof(serv_address)) < 0) 
    { 
        perror("socket bind failed"); 
        exit(0); 
    }
    printf("Bind successful"); 
    while(1) {
        addrlen = sizeof(struct sockaddr);	
        str_echo(connfd, (struct sockaddr *)&cli_address, addrlen);
        close(connfd);
    }
    return 0 ;
}