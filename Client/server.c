#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define MAX 100
typedef struct Client{
	int cfd;
	char name[40];
}Client;

Client client[MAX] = {};
size_t cnt = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void broadcast(char *msg,Client c){
	size_t i;
	pthread_mutex_lock(&mutex);
	for(i=0;i<cnt;i++){
		if(client[i].cfd != c.cfd){
			if(send(client[i].cfd,msg,strlen(msg),0)<=0){
				break;
			}
		}
	}
	pthread_mutex_unlock(&mutex);
}

void *pthread_run(void *arg){
	Client cl = *(Client*)(arg);
	while(1){
		char buf[1024]={};
		strcpy(buf,cl.name);
		strcat(buf," :");
		int ret = recv(cl.cfd,buf+strlen(buf),1024-strlen(buf),0);
		if(ret <= 0){
			size_t i;
			for(i=0;i<cnt;i++){
				if(client[i].cfd == cl.cfd){
					client[i] = client[cnt-1];
					--cnt;
					strcpy(buf,"Tu amigo");
					strcat(buf,cl.name);
					strcat(buf,"dejar");
					break;
				}	
			}
			broadcast(buf,cl);
			close(cl.cfd);
			return NULL;
		}else{
			broadcast(buf,cl);
		}
	}
}

int main(int argc,char *argv[]){
	if(argc != 3){
		fprintf(stderr,"use: %s <ip> [port]\n",argv[0]);
		return -1;
	}
	const char *ip = argv[1];
	unsigned short int port = atoi(argv[2]);

	int sfd = socket(AF_INET,SOCK_STREAM,0);
	if(sfd == -1){
		perror("socket");
		return -1;
	}

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr(ip);
	socklen_t addrlen = sizeof(addr);

	int ret = bind(sfd,(struct sockaddr*)(&addr),addrlen);
	if(ret == -1){
		perror("bind");
		return -1;
	}
	if(listen(sfd,10)==-1){
		perror("listen");
		return -1;
	}
	while(1){
		struct sockaddr_in caddr;
		socklen_t len = sizeof(caddr);
		
		printf("Esperando la conexión del cliente ... \ n");
		int cfd = accept(sfd,(struct sockaddr*)(&caddr),&len);
		if(cfd == -1){
			perror("accept");
			return -1;
		}
		char buf[100]={};
		recv(cfd,&client[cnt].name,40,0);
		client[cnt].cfd = cfd;
		pthread_t id;
		strcpy(buf,"Tu amigo");
		strcat(buf,client[cnt].name);
		strcat(buf,"Ir en línea");
		broadcast(buf,client[cnt]);
		ret = pthread_create(&id,NULL,pthread_run,(void*)(&client[cnt]));
		cnt++;
		if(ret != 0){
			printf("pthread_create:%s\n",strerror(ret));
			continue;
		}
		printf("Un cliente se conectó correctamente: ip <% s> puerto [% hu] \ n",inet_ntoa(caddr.sin_addr),ntohs(caddr.sin_port));
	}
	return 0;
}

