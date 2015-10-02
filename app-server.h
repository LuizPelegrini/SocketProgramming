/* contém as funções utilizadas pela aplicação implementada no lado do servidor */

#include "lista.h"


//variáveis globais
Lista listatelefonica;	//lista usada pela aplicação
Registro* reg_atual;	//ponteiro auxiliar para as funcionalidades (inserir,remover etc)
int func_atual;		//funcionalidade a ser executada


//registro a ser inserido na lista telefônica
//nome é a chave
struct registro
{
	char nome[55];	//chave do registro
	char telefone[9];
};
typedef struct registro Registro;


//recebe uma mensagem e seta func_atual, reg_atual de acordo com o protocolo da aplicação
//func_atual = -1 se há falha no protocolo
void processa_msg(char *msg);


//tenta inserir registro válido na lista
//retorna 1 se registro já existe
int inserir(Registro r);


//altera o telefone de um registro e o retorna
Registro alterar(char* chave);


//remove registro da lista e retorna sucesso ou fracasso se não encontrado
int remover(char* chave);


//busca pelo nome
Registro buscar(char* chave);


//encerra aplicação
void finapp();
