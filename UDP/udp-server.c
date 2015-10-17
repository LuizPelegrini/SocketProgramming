#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include "lista.h"


//registro a ser inserido na lista telefônica
//nome é a chave
struct registro
{
    char nome[55];  //chave do registro
    char telefone[9];
};
typedef struct registro Registro;

int sockint,s, namelen, client_address_size;
struct sockaddr_in client, server;
char buf[80];

Lista* listatelefonica; //lista usada pela aplicação
int func_atual;     //funcionalidade a ser executada
char* cmd;
char* nome;
char* tel;


void inicializar()
{
   if ((s = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
   {
       perror("socket()");
       exit(1);
   }

   server.sin_family      = AF_INET;   /* Server is in Internet Domain */
   server.sin_port        = 0;         /* Use any available port       */
   server.sin_addr.s_addr = INADDR_ANY;/* Server's Internet Address    */

   if (bind(s, (struct sockaddr *)&server, sizeof(server)) < 0)
   {
       perror("bind()");
       exit(2);
   }

   namelen = sizeof(server);
   if (getsockname(s, (struct sockaddr *) &server, &namelen) < 0)
   {
       perror("getsockname()");
       exit(3);
   }

   printf("Port assigned is %d\n", ntohs(server.sin_port));


   client_address_size = sizeof(client);
}


void enviarmsg(char *msg)
{
  strcpy(buf,msg);

  if (sendto(s, buf, (strlen(buf)+1), 0, (struct sockaddr *)&client, sizeof(client)) < 0)
  {
      perror("sendto()");
      exit(2);
  }
}


void recebermsg()
{
   if(recvfrom(s, buf, sizeof(buf), 0, (struct sockaddr *) &client,
            &client_address_size) <0)
   {
       perror("recvfrom()");
       exit(4);
   }
}


//função de comparação para a busca
int comparar_registros(void* r, void* chave)
{
    return !strcmp(((Registro*) r)->nome, (char *) chave);
}


void imprimirRegistro(void* reg)
{
    printf("%s\t%s\n",((Registro*)reg)->nome,((Registro*)reg)->telefone);
}


void imprimirlista()
{
    printf("Conteúdo da lista:\nNome\tTelefone\n");
    percorrerLista(listatelefonica,&imprimirRegistro);
    printf("\n");
}


//tenta inserir registro válido na lista
void inserir()
{
    Registro* reg = malloc(sizeof(Registro));

    strcpy(reg->nome,nome);
    strcpy(reg->telefone,tel);

    Registro* r = (Registro *) buscarNaLista(listatelefonica,nome,&comparar_registros);
    if(r!=NULL)
    {
        enviarmsg("UPDATE?/"); //enviar ao cliente
        recebermsg();
        cmd = strtok(buf, "/");
        if(!strcmp(cmd,"YES"))
        {
            strcpy(r->telefone,reg->telefone);
        }
    }
    else
        inserirNaLista(listatelefonica,reg);
    enviarmsg("OK/");
    imprimirlista();
}


//remove registro da lista
void remover()
{
    
    if(removerUmDaLista(listatelefonica, nome,&comparar_registros) == 0)
         enviarmsg("NOT FOUND/");
     else
        enviarmsg("OK/");
    imprimirlista();
}


//busca pelo nome
void buscar()
{
    char tel[11];
    Registro* r = (Registro *) buscarNaLista(listatelefonica,nome,&comparar_registros);
    if(r==NULL)
        enviarmsg("NOT FOUND/");
    else
    {
        strcpy(tel,r->telefone);
        strcat(tel,"/");
        enviarmsg(tel);
    }

}


int processar_msg()
{
    int i,j;
    cmd = strtok(buf, "/");
    nome = strtok(NULL, "/");
    tel = strtok(NULL, "/");

    printf("Comando recebido: %s\n",cmd);

    if(!strcmp(cmd,"END"))
        return 0;
    else if(!strcmp("STORE", cmd)){

        inserir();
    }else if(!strcmp("REMOVE", cmd)){
        remover();
    }else if(!strcmp("GET", cmd)){
        buscar();
    }

    return 1;
}


int main()
{
  inicializar();
  listatelefonica = inicializarLista();

  while(1)
  {
      recebermsg();
      if(!processar_msg())
          break;
  }

  enviarmsg("END/");
  
  close(s);
  printf("Server ended successfully\n");
  return 0;
}
