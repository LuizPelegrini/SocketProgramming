#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int s,server_address_size;
unsigned short port;
struct sockaddr_in server;
char buf[80];
char* msg;


void inicializar(int argc,char** argv)
{
  if(argc != 3)
  {
    printf("Usage: %s <host address> <port> \n",argv[0]);
    exit(1);
  }
  port = htons(atoi(argv[2]));


  if ((s = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
  {
     perror("socket()");
     exit(1);
  }


  server.sin_family      = AF_INET;            /* Internet Domain    */
  server.sin_port        = port;               /* Server Port        */
  server.sin_addr.s_addr = inet_addr(argv[1]); /* Server's Address   */

  server_address_size = sizeof(server);
}


void enviarmsg()
{
  if (sendto(s, buf, (strlen(buf)+1), 0, (struct sockaddr *)&server, sizeof(server)) < 0)
  {
      perror("sendto()");
      exit(2);
  }
}


void recebermsg()
{
  if(recvfrom(s, buf, sizeof(buf), 0, (struct sockaddr *) &server,
            &server_address_size) <0)
  {
      perror("recvfrom()");
      exit(4);
  }

  msg = strtok(buf, "/");
  printf("RECEBI: %s\n",msg);
}



int main(int argc,char** argv)
{
  inicializar(argc,argv);

  while(1)
  {
      fgets(buf, 80, stdin);
      enviarmsg();
      recebermsg();

      if(!strcmp(msg,"END"))
          break;
  }


  printf("Client Ended Successfully\n");
  close(s);
  return 0;
}
