#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

unsigned short port;       /* port client will connect to              */
char buf[80];              /* data buffer for sending and receiving    */
struct hostent *hostnm;    /* server host name information             */
struct sockaddr_in server; /* server address                           */
int s;                     /* client socket                            */
char* msg;


void conectar(int argc,char** argv)
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s hostname port\n", argv[0]);
        exit(1);
    }

    /*
     * The host name is the first argument. Get the server address.
     */
    hostnm = gethostbyname(argv[1]);
    if (hostnm == (struct hostent *) 0)
    {
        fprintf(stderr, "Gethostbyname failed\n");
        exit(2);
    }

    /*
     * The port is the second argument.
     */
    port = (unsigned short) atoi(argv[2]);

        /*
     * Put the server information into the server structure.
     * The port must be put into network byte order.
     */
    server.sin_family      = AF_INET;
    server.sin_port        = htons(port);
    server.sin_addr.s_addr = *((unsigned long *)hostnm->h_addr);

    /*
     * Get a stream socket.
     */
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Socket()");
        exit(3);
    }

    /*
     * Connect to the server.
     */
    if (connect(s, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("Connect()");
        exit(4);
    }
}


void enviarmsg()
{
    if (send(s, buf, strlen(buf), 0) < 0)
    {
        perror("Send()");
        exit(5);
    }
}


void recebermsg()
{
    int i;
    if (recv(s, buf, sizeof(buf), 0) < 0)
    {
        perror("Recv()");
        exit(6);
    }

    msg = strtok(buf, "/");
    printf("RECEBI: %s\n",msg);
}


int main(int argc,char** argv)
{
    conectar(argc,argv);

    while(1)
    {
        fgets(buf, 80, stdin);
        enviarmsg();
        recebermsg();

        if(!strcmp(msg,"END"))
            break;
    }


    close(s);

    printf("Client Ended Successfully\n");
    
    return 0;
}


