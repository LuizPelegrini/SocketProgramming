#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include "lista.h"


//registro a ser inserido na lista telefônica
//nome é a chave
struct registro
{
    char nome[55];  //chave do registro
    char telefone[9];
};
typedef struct registro Registro;


unsigned short port;       /* port server binds to                  */
char buf[80];              /* buffer for sending and receiving data */
struct sockaddr_in client; /* client address information            */
struct sockaddr_in server; /* server address information            */
int s;                     /* socket for accepting connections      */
int ns;                    /* socket connected to client            */
int namelen;               /* length of client name                 */


Lista* listatelefonica; //lista usada pela aplicação
int func_atual;     //funcionalidade a ser executada
char* cmd;
char* nome;
char* tel;


void conectar(int argc,char** argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s port\n", argv[0]);
        exit(1);
    }

    /*
     * First argument should be the port.
     */
    port = (unsigned short) atoi(argv[1]);

    /*
     * Get a socket for accepting connections.
     */
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Socket()");
        exit(2);
    }

    /*
     * Bind the socket to the server address.
     */
    server.sin_family = AF_INET;
    server.sin_port   = htons(port);
    server.sin_addr.s_addr = INADDR_ANY;

    if (bind(s, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
       perror("Bind()");
       exit(3);
    }

    /*
     * Listen for connections. Specify the backlog as 1.
     */
    if (listen(s, 1) != 0)
    {
        perror("Listen()");
        exit(4);
    }

    /*
     * Accept a connection.
     */
    namelen = sizeof(client);
    if ((ns = accept(s, (struct sockaddr *)&client, &namelen)) == -1)
    {
        perror("Accept()");
        exit(5);
    }
}


void recebermsg()
{
    if (recv(ns, buf, 80, 0) == -1)
    {
        perror("Recv()");
        exit(6);
    }
}


void enviarmsg(char *msg)
{
    strcpy(buf,msg);

    /*
     * Send the message back to the client.
     */
    if (send(ns, buf, strlen(buf), 0) < 0)
    {
        perror("Send()");
        exit(7);
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


int main(int argc,char** argv)
{    
    conectar(argc,argv);
    listatelefonica = inicializarLista();

    while(1)
    {
        recebermsg();
        if(!processar_msg())
            break;
    }

    enviarmsg("END/");
    close(ns);
    close(s);

    printf("Server ended successfully\n");
    return 0;
}


