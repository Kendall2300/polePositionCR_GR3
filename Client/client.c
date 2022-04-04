#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 9300

int main(){
    int clientSocket, ret;
    struct sockaddr_in serverAddr;
    char buffer[1024];

    clientSocket = socket(AF_INET,SOCK_STREAM,0);
    if(clientSocket < 0){
        printf("[-]Error en la conexion");
        exit(1);
    }
    printf("[+] Socket del cliente creado \n");
    serverAddr.sin_family=AF_INET;
    serverAddr.sin_port=htons(PORT);
    serverAddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    ret=connect(clientSocket,(struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if(ret<0){
        printf("[--]Error en la conexion");
        exit(1);
    }
    printf("[++]Conectado al servidor \n");
    printf("Client: \t");
    scanf("%s",&buffer[0]);
    send(clientSocket, buffer,strlen(buffer),0);
    
    
    printf(read(clientSocket,buffer,strlen(buffer)));
}