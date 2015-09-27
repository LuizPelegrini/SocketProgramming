#ifndef SOCKETS_UTIL_H
#define SOCKETS_UTIL_H 

#include <sys/socket.h>

#ifndef MY_PORT
#define MY_PORT "42420"
#endif

/*
	net_error = verifica se ocorreu erro em alguma funcao associada a sockets.
	------------------------------------------------------------------
	msg -> é a mensagem indicando de onde está vindo o erro.

	status -> é o inteiro q é retornado por quase todas as funcoes relacionadas
	a socket.
*/
void net_error(const char *msg, const int status);

/*
	get_input = pega informações passadas pela linha de comando, e as armazena
	nas variáveis first e second.
*/
void get_input(const int argc, const char *argv[], char **first, char **second);


/*
	create_addrinfo = cria uma estrutura que auxila na hora de criar sockets.
*/
struct addrinfo* create_addrinfo(const int socktype, const char *ip, const char *port);


/*
	create_socket = utiliza a struct addrinfo para criar um socket, e ja dar bind() ou connect() nesse socket.
*/
int create_socket(struct addrinfo *addrinfo, int (*function)(int, const struct sockaddr* , socklen_t));

#endif
