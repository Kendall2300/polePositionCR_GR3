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

}

/*int main(){
    char *ip = "127.0.0.1";
    int port = 9300;

    int sock;
    struct sockaddr_in addr;
    socklen_t addr_size;
    char buffer[1024];
    int n;

    sock=socket(AF_INET,SOCK_STREAM,0);
    if(sock<0){
        perror("[-]Socket error");
        exit(1);
    }
    printf("[+]TCP server socket created.\n");
    
    memset(&addr, "\0", sizeof(addr));
    addr.sin_family=AF_INET;
    addr.sin_port=port;
    addr.sin_addr.s_addr=inet_addr(ip);

    connect(sock,(struct sockaddr*)&addr, sizeof(addr));

    printf("Conectado al servidor \n");
}*/