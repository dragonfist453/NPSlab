#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>

int main(){

    int create_socket, fd;
    char buffer[256]={'\0'}, fname[256];
    struct sockaddr_in address;
    
    create_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(create_socket<0){
        printf("Error in socket\n");
        exit(0);
    }
    printf("[+] Socket created\n");

    address.sin_family = AF_INET;
    address.sin_port = htons(1500);
    inet_pton(AF_INET, "127.0.0.1", &address.sin_addr);

    int addrlen = sizeof(struct sockaddr_in);
    if(connect(create_socket, (struct sockaddr*)&address, sizeof(address))<0){
        printf("Connection error\n");
        exit(0);
    }

    printf("[+] Connection done\n");

    // printf("Enter the filename to be requested:\n ");
    // scanf("%s", fname);

    // send(create_socket, fname, sizeof(fname), 0);
    
    // printf("Request sent\n");

    

    while((fd=recv(create_socket, buffer, 256, 0))>0){
        write(1, buffer, 256);
    }

    close(create_socket);
        



    

    return 0;
}
