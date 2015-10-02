#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "sockets-util.h"

#define BUFFER 100000


int main(int argc, char const *argv[])
{	
	char *ip, *port;
	get_input(argc, argv, &ip, &port);
	printf("IP = %s\n", ip);
	printf("Port = %s\n", port);

	struct addrinfo *serv_info;
	serv_info = create_addrinfo(SOCK_STREAM, ip, port);
 
	int sock;
	sock = create_socket(serv_info, &connect);
	

/* PROTOTIPO de como ENVIA mensagens */
	char msg[BUFFER];
	strcat(msg, "GET /index.html HTTP/1.1\r\nHost: ");
	strcat(msg, ip);
	strcat(msg, "\r\n\r\n");
	printf("\n*MESSAGE* (http)\n%s\n", msg );

	send_all(sock, msg);

/* PROTOTIPO de como RECEBE mensagens */
	// int recv(int sockfd, void *buf, int len, int flags);
	char *buff;
	size_t by_recv;
	by_recv = recv_all(sock, &buff, BUFFER);


	printf("\n\nMessage has ended; received %ld bytes!\n", by_recv);
	return 0;
}
