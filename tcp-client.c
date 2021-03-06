#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "sockets-util.h"



int main(int argc, char const *argv[])
{	
	char *ip, *port;
	get_input(argc, argv, &ip, &port);
	printf("IP = %s\n", ip);
	printf("Port = %s\n", port);
 
	int sock;
	sock = create_socket(SOCK_STREAM, ip);
	

/* PROTOTIPO de como ENVIA mensagens */
	char msg[BUF_SIZE];
	strcat(msg, "GET /index.html HTTP/1.1\r\nHost: ");
	strcat(msg, ip);
	strcat(msg, "\r\n\r\n");
	print_request(msg);

	send_all(sock, msg);

/* PROTOTIPO de como RECEBE mensagens */
	// int recv(int sockfd, void *buf, int len, int flags);
	char *buff;
	size_t by_recv;
	by_recv = recv_all(sock, &buff, BUF_SIZE);

	print_response(buff);
	return 0;
}
