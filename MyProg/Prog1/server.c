#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int main(){
    int create_socket, new_socket, cont, bufsize=1024, addrlen, fd;
    char buffer[256]={'h','i'}, fname[256];
    struct sockaddr_in address;

    create_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(create_socket<0){
        printf("Server error\n");
        exit(0);
    }
    printf("[+] Socket created\n");
    
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(1500);
    address.sin_family = AF_INET;
    
    if(bind(create_socket, (struct sockaddr*)&address, sizeof(address))<0){
        printf("Bind error\n");
        exit(0);
    }
    printf("[+] Bind successful\n");

    listen(create_socket, 3);

    addrlen = sizeof(struct sockaddr_in);
    new_socket = accept(create_socket, (struct sockaddr*)&address, &addrlen);

    if(new_socket<0){
        printf("Acceptance error\n");
        exit(0);
    }

    printf("[+] Socket accepted the connection from %s\n",inet_ntoa(address.sin_addr));

    // recv(new_socket, fname, 50, 0);
    // printf("Request received for file %s\n", fname);

    // fd = open(fname, O_RDONLY);
    // while((cont=read(fd, buffer, bufsize))>0){
    //     send(new_socket, buffer, cont, 0);
    // }
    
    send(new_socket, buffer, 256, 0);
    
    printf("[+] Request completed\n");

    close(new_socket);
    close(create_socket);

    return 0;
}
