#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

#define PORT 8080 
#define BUFFER_SIZE 1024

int main(int argc , char * argv[])
{
    int socket_fd ; 
    char buffer[BUFFER_SIZE] ; 
    struct sockaddr_in servaddr , cliaddr ; 

    if((socket_fd = socket(AF_INET, SOCK_DGRAM,0))< 0 )
    {
        perror("socket creation error") ; 
        exit(EXIT_FAILURE);
    }

    memset(&servaddr , 0 , sizeof(servaddr)) ; 
    memset(&cliaddr , 0 , sizeof(cliaddr))   ; 

    servaddr.sin_family = AF_INET ;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    if(bind(socket_fd,(const struct sockaddr*)&servaddr,sizeof(servaddr))< 0 ) 
    {
        perror("bind failed\n") ; 
        close(socket_fd) ;
        exit(EXIT_FAILURE);
    }
    int len , n ; 

    len = sizeof(cliaddr) ; 
    n = recvfrom(socket_fd , (char*)buffer , BUFFER_SIZE, MSG_WAITALL,(struct sockaddr *)&cliaddr ,&len ) ; 
    buffer[n] = '\0' ; 
    printf("client : %s\n",buffer) ; 

    const char * message = "hello from server";
    sendto(socket_fd , (const char*)message, strlen(message),MSG_CONFIRM,(const struct sockaddr *)&cliaddr , len) ; 
    printf("hello message sent.\n") ; 

    close(socket_fd) ; 
    return 0 ; 

}