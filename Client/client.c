/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <WinSock2.h>

#pragma comment(lib, "Ws2_32.lib")

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

    while(1){
        printf("Client: \t");
        scanf("%s",&buffer[0]);
        send(clientSocket, buffer,strlen(buffer),0);


        if(strcmp(buffer,":exit")==0){
            close(clientSocket);
            printf("[-]Disconnected from server.\n");
            exit(1);
        }
        
        if(recv(clientSocket,buffer,1024,0)<0){
            printf("[-]Error recibiendo datos.\n");
        }else{
            printf("Server: \t%s\n",buffer);
        }
    }
}*/


#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

char SendBuff[512],RecvBuff[512];

int main(int argc, char *argv[]){

    WSADATA wsaData;
    SOCKET conn_socket;
    struct sockaddr_in server;
    struct hostent *hp;
    int resp;

    //Inicializamos la DLL de sockets
    resp=WSAStartup(MAKEWORD(1,0),&wsaData);
    if(resp){
        printf("Error al inicializar socket\n");
        getchar();return -1;
    }

    //Obtenemos la IP del servidor... en este caso
    // localhost indica nuestra propia máquina...
    hp=(struct hostent *)gethostbyname("localhost");

    if(!hp){
        printf("No se ha encontrado servidor...\n");
        getchar();WSACleanup();return WSAGetLastError();
    }

    // Creamos el socket...
    conn_socket=socket(AF_INET,SOCK_STREAM, 0);
    if(conn_socket==INVALID_SOCKET) {
        printf("Error al crear socket\n");
        getchar();WSACleanup();return WSAGetLastError();
    }

    memset(&server, 0, sizeof(server)) ;
    memcpy(&server.sin_addr, hp->h_addr, hp->h_length);
    server.sin_family = hp->h_addrtype;
    server.sin_port = htons(9300);

    // Nos conectamos con el servidor...
    if(connect(conn_socket,(struct sockaddr *)&server,sizeof(server))==SOCKET_ERROR){
        printf("Fallo al conectarse con el servidor\n");
        closesocket(conn_socket);
        WSACleanup();getchar();return WSAGetLastError();
    }
    printf("Conexión establecida con: %s\n", inet_ntoa(server.sin_addr));

    strcpy(SendBuff,"Hola servidor... .P");
    //Enviamos y recibimos datos...
    printf("Enviando Mensaje... \n");
    send(conn_socket,SendBuff,sizeof(SendBuff),0);
    printf("Datos enviados: %s \n", SendBuff);

    printf("Recibiendo Mensaje... \n");
    recv(conn_socket,RecvBuff, sizeof(RecvBuff), 0);
    printf("Datos recibidos: %s \n", RecvBuff);

    getchar();

    // Cerramos el socket y liberamos la DLL de sockets
    closesocket(conn_socket);
    WSACleanup();
    return EXIT_SUCCESS;
}