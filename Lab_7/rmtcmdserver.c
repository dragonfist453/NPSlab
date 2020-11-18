#include<stdio.h>
#include<stdlib.h> 
#include<string.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<errno.h>
#include<fcntl.h>

int main()
{ 
    int sd,acpt,len,bytes,port;
    char receiv[50];
    struct sockaddr_in serv,cli;
    if((sd=socket(AF_INET,SOCK_STREAM,0))<0) { 
        printf("Error in socket\n"); 
        exit(0);
    }
    bzero(&serv,sizeof(serv));
    serv.sin_family=AF_INET; 
    serv.sin_port=htons(15002); 
    serv.sin_addr.s_addr=htonl(INADDR_ANY);
    if(bind(sd,(struct sockaddr *)&serv,sizeof(serv))<0) { 
        printf("Error in bind\n"); 
        exit(0); 
    }
    if(listen(sd,3)<0) { 
        printf("Error in listen\n"); 
        exit(0); 
    }
    if((acpt=accept(sd,(struct sockaddr*)NULL,NULL))<0) { 
        printf("\n\t Error in accept"); 
        exit(0); 
    }
    while(1) { 
        bytes=recv(acpt,receiv,50,0); 
        receiv[bytes]='\0'; 
        if(strcmp(receiv ,"end")==0) { 
            close(acpt); 
            close(sd); 
            exit(0); 
        }
        else { 
            printf("Command received : %s",receiv); 
            system(strcat(receiv, " > temp"));
            int fd = open("temp", O_RDONLY);
            char buf[512];
            read(fd, buf, 512);
            send(acpt, buf, 512,0);
            system("rm temp");
            printf("\n"); 
        }
    }
}