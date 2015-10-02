/* contém as funções utilizadas pela aplicação implementada no lado do servidor */

#include "lista.h"


//variável global da aplicação
Lista listatelefonica;


//registro a ser inserido na lista telefônica
struct registro
{
	char nome[55];	//chave do registro
	char telefone[8];
};
typedef struct registro Registro;


//insere registro válido na lista sem garantia de que não há repetição
int inserir(Registro r);


//altera o telefone de um registro e o retorna
Registro alterar(char chave[55]);


//remove registro da lista e retorna sucesso ou fracasso se não encontrado
int remover(char chave[55]);


//busca pelo nome
Registro buscar(char chave[55]);


//encerra aplicação
void finapp();
