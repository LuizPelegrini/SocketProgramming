#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "sockets-util.h"


#define QUEUE_SIZE 20

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}



int main(int argc, char const *argv[])
{	
	char *path, *port;
	get_input(argc, argv, &path, &port);
	printf("Path = %s\n", path);
	printf("Port = %s\n", port);

	char s[INET6_ADDRSTRLEN];

	int client_sock;
	client_sock = create_socket(SOCK_DGRAM, NULL);
	

	struct sockaddr_storage client_addr;
	socklen_t c_addr_len;
	c_addr_len = sizeof(struct sockaddr_storage);
	int status;
	char request[BUF_SIZE];
	while(1){
		if(recvfrom(client_sock, &request, BUF_SIZE-1 , 0,
					(struct sockaddr *)&client_addr, &c_addr_len) == -1) {
			perror("recvfrom error");
			exit(1);
		}
		print_request(request);
		printf("c_addr_len = %d\n",  c_addr_len);

		char response[] = "Testando";
		//get_addr_in()
		if(sendto(client_sock, response, sizeof(response), 0,
				(struct sockaddr*)&client_addr, c_addr_len) == -1){
			perror("sento error");
			exit(1);
		}
		print_response(response);

	}

}