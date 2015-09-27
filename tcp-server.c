#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "sockets-util.h"


#define QUEUE_SIZE 20



int main(int argc, char const *argv[])
{	
	char *path, *port;
	get_input(argc, argv, &path, &port);
	printf("Path = %s\n", path);
	printf("Port = %s\n", port);

	struct addrinfo *serv_info;
	serv_info = create_addrinfo(SOCK_STREAM, NULL, port);
 
	int sock;
	sock = create_socket(serv_info, &bind);
	
// LISTEN
	//int listen(int sockfd, int backlog);
	int new_sock;
	struct sockaddr_storage client_addr;
	socklen_t c_addr_len;
	addr_len = sizeof(struct sockaddr_storage);
	int status;
	while(1){
		status = listen(sock, QUEUE_SIZE);
		if (status == -1)
		{
			printf("Erro no listen!\n");
			exit(1);
		}
		new_sock = accept(sock,(struct sockaddr *)&client_addr, &c_addr_len);
		if(new_sock == -1){
			printf("Erro no Accept!\n");
			exit(1);
		}
		if(!fork()){// is the child process
			/*
			cada processo filho do servidor vai tratar de um cliente. Isso
			garante que o servidor possa atender novas conexoes, enquanto
			os seus filhos tratam de cada cliente.
			*/
			break;
		}
		close(new_sock);
	}

/* Everything that goes here is only used by the child process */


	// RECEIVES

	// SENDS


}