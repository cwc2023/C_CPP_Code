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
    const char * message = "hello from client, i use the udp client sent message to server" ; 
    struct sockaddr_in servaddr; 
    /*创建套接字*/
    if((socket_fd = socket(AF_INET, SOCK_DGRAM,0))< 0 )
    {
        perror("socket creation failed") ; 
        exit(EXIT_FAILURE);
    }

    memset(&servaddr , 0 , sizeof(servaddr)) ; 

    //填写服务器信息
    servaddr.sin_family = AF_INET ;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);


    int len , n ; 

    sendto(socket_fd , (const char*)message, strlen(message),MSG_CONFIRM,(const struct sockaddr *)&servaddr , sizeof(servaddr)) ; 
    printf("hello message sented.\n") ; 

    n = recvfrom(socket_fd,(char * )buffer , BUFFER_SIZE , MSG_WAITALL,(struct sockaddr *)&servaddr ,&len) ; 
    buffer[n] = "\0";
    printf("recv server message the message is :%s\n",buffer) ; 

    close(socket_fd) ; 
    return 0 ; 

}
