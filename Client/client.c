#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

char SendBuff[512],RecvBuff[512];

int main(){

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
    printf("Conexion establecida con: %s\n", inet_ntoa(server.sin_addr));

    // Cerramos el socket y liberamos la DLL de sockets
    closesocket(conn_socket);
    WSACleanup();
    return EXIT_SUCCESS;
}