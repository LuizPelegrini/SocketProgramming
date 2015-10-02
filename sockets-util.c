#include "sockets-util.h"
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

// handles errors, and PRINT them
void net_error(const char *msg, const int status)
{
	if (status){
		fprintf(stderr, "%s error: %s\n", msg, gai_strerror(status));
		exit(1);
	}
	return;
}


void get_input(const int argc, const char *argv[], char **first, char **second)
{
	
	printf("%s = %ld\n", argv[1], strlen(argv[1]));
	if (argc < 2 || argc > 3)
	{
		fprintf(stderr, "Invalid call!\n");
		exit(1);
	} else if (argc == 2) { // second not declared; default is http
		*second = (char*) malloc(strlen(MY_PORT) * sizeof(char));
		*second = strcpy(*second, MY_PORT);
	} else { // second declared
		*second = (char*) malloc(strlen(argv[2]) * sizeof(char));
		*second = strcpy(*second, argv[2]);
	}

	*first = (char*) malloc(strlen(argv[1]) * sizeof(char));
	strcpy(*first, argv[1]);
}



struct addrinfo* create_addrinfo(int socktype, const char *ip, const char *port)
{
	struct addrinfo hints;
	// prepares the struct adrrinfo
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC; // can be IPv4 or IPv6
	hints.ai_socktype = socktype; // tcp or udp
	hints.ai_flags = AI_PASSIVE; // fill in my IP for me

	int status;
	struct addrinfo *info;
	status = getaddrinfo(ip, port, &hints, &info);
	net_error("GETADDRINFO", status);

	return info;
}

// go through every server addrinfo and tries to create a socket, then tries to make a connection or a binding
int create_socket(struct addrinfo *addrinfo, int (*function)(int, const struct sockaddr* , socklen_t))
{
	struct addrinfo *ai;
	int sock;
	for (ai = addrinfo; ai != NULL; ai = ai->ai_next){
		// creates a socket for this application
		sock = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
		if (sock == -1){ // socket creation error
			continue;
		}
	// do the function passed by the caller to the addrinfos
		if (function(sock, ai->ai_addr, ai->ai_addrlen) == -1){
			close(sock);
			continue; // cant use the function to this
		}
		printf("Socket Creation Accomplished!\n");
		break;
	}
	if (ai == NULL){
		printf("Socket Creation Error!\n");
		sock = -1;
	}

	free(addrinfo);
	return sock;
}

size_t send_all(int socket, const char *msg)
{
	int total_sent = 0; // quantity of bytes already sent
	int sent = 0;
	size_t msg_len = strlen(msg);
	size_t piece_len = msg_len;
	// char *aux = msg;
	while (total_sent < msg_len){
		// aux += total_sent;
		sent = send(socket, msg + total_sent, piece_len, 0);
		total_sent += sent;
		piece_len -= sent;
	}
	return total_sent;
}

size_t recv_all(int socket, char **buffer, const size_t buf_size)
{
	size_t by_recv = 1;// quatity of bytes already received
	size_t count = 0;// total of bytes received in the end
	*buffer = (char*) malloc(sizeof(char) * buf_size);
	while(by_recv > 0 && count < buf_size){
		by_recv = recv(socket, *buffer, buf_size, 0);
		if(by_recv == 0 || by_recv == -1)
			break;
		count += by_recv;
		/*printf("\n** Value received from recv() = %d\n", by_recv);
		printf("** Total bytes recv = %d\n\n\n", count);
		printf("%s\n", *buffer);*/
		if(strstr(*buffer, "\r\n\r\n"))
			break;
	}
	return count;
}