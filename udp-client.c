#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "sockets-util.h"

#define BUFFER 1000000


int main(int argc, char const *argv[])
{	
	char *ip, *port;
	get_input(argc, argv, &ip, &port);
	printf("IP = %s\n", ip);
	printf("Port = %s\n", port);

	struct addrinfo *serv_info;
	serv_info = create_addrinfo(SOCK_DGRAM, ip, port);
 
	int sock;
	sock = create_socket(serv_info, &connect);
	

/* PROTOTIPO de como ENVIA mensagens */
	char msg[BUFFER];
	strcat(msg, "GET /index.html HTTP/1.1\r\nHost: ");
	strcat(msg, argv[IP]);
	strcat(msg, "\r\n\r\n");
	printf("\n*MESSAGE* (http)\n%s\n", msg );

	int by_sent = 0; // quantity of bytes already sent
	int msg_len = strlen(msg);
	char *aux = msg;
	while (by_sent < msg_len){
		aux = aux + by_sent;
		by_sent = send(sock, aux, msg_len, 0);
		printf("bytes sent = %d\n", by_sent);
	}

/* PROTOTIPO de como RECEBE mensagens */
	// int recv(int sockfd, void *buf, int len, int flags);
	int by_recv = 1;// quatity of bytes already received
	char buff[BUFFER];
	int count = 0;// total of bytes received in the end
	while(by_recv > 0 && count < BUFFER){
		by_recv = recv(sock, &buff, BUFFER, 0);
		if(by_recv == 0 || by_recv == -1)
			break;
		count += by_recv;
		printf("\n** Value received from recv() = %d\n", by_recv);
		printf("** Total bytes recv = %d\n\n\n", count);
		printf("%s\n", buff);
		if(strstr(buff, "\r\n\r\n"))
			break;
	}


	printf("\n\nMessage has ended; received %d bytes!\n", count);
	return 0;
}
