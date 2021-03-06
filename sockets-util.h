#ifndef SOCKETS_UTIL_H
#define SOCKETS_UTIL_H 

#include <sys/socket.h>

#ifndef MY_PORT
#define MY_PORT "42421"
#endif

#ifndef BUF_SIZE
#define BUF_SIZE 100000
#endif

#ifndef QUEUE_SIZE
#define QUEUE_SIZE 20
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
struct addrinfo* _create_addrinfo(const int socktype, const char *ip, const char *port);


/*
	create_socket = utiliza a struct addrinfo para criar um socket, e ja dar bind() ou connect() nesse socket.
*/
int _socket(struct addrinfo *addrinfo, int (*function)(int, const struct sockaddr* , socklen_t));

int create_socket(int sock_type, const char *ip);


size_t send_all(int socket, const char *msg);


size_t recv_all(int socket, char **buffer, const size_t buf_size);


#endif
