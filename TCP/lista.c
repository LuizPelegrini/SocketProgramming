/*
    lista.c
    -------
    Lista Simplesmente Encadeada com Nó Descritor: lista genérica capaz de realizar operações básicas.

    Como utilizar:
        Basta criar uma variável na sua aplicação do tipo "Lista*" e chamar a função que inicia devidamente a lista: "suaVariavelDeLista = inicializarLista();".
        Todas as funções dessa biblioteca necessitam como primeiro argumento a lista.

    Observações Importantes:
        1) Inserção sempre realizada no COMEÇO da lista.
        2) Na remoção de um elemento da lista, tanto o elmento, quanto o dado que está sendo armazenado pelo elemento são apagados da memória. Caso a aplicação
        necessite que o dado nao seja apagado, basta comentar as linhas indicadas com um "@1" nas funções de remover.

    Por: Felipe Brandão 11311BCC023, Frederico Franco 11311BCC057 e Pedro Henrique Ribeiro 11311BCC040, Agosto, 2014.
*/

#include "lista.h"

void*
buscarNaLista (Lista* lista, void* chave, int (*funcao)(void*, void*) )
{
	Node* aux;

	for( aux= lista->primeiro ; aux!=NULL ; aux=aux->prox )
	{
		if( (*funcao) (aux->dado, chave) == 1)
			return aux->dado;
	}

	return NULL;
}


void*
buscarPosNaLista (Lista* lista, int pos)
{
	Node* aux;
	int i;

	if (pos > lista->nelementos)
		return NULL;

	for( aux= lista->primeiro, i=1 ;
		aux!=NULL && i < lista->nelementos ;
		aux=aux->prox, i++ )
	{
		if( i == pos)
			return aux->dado;
	}

	return NULL;
}


Lista*
inicializarLista()
{
	Lista* lista;

	lista= (Lista*) malloc(sizeof(Lista));
	if(lista==NULL)
		return NULL;

	lista->nelementos=0;
	lista->primeiro=NULL;

	return lista;
}



void
inserirNaLista (Lista* lista, void* dado)
{
	Node* node;

	node=(Node*) malloc(sizeof(Node));
	if(node==NULL)
		return;
	node->dado = dado;
	node->prox = lista->primeiro;

	lista->primeiro = node;
	lista->nelementos++;

}

void
percorrerLista (Lista* lista, void (*funcao) (void*))
{
	Node* aux;

	if( !lista || !lista->primeiro || !funcao )
		return;

	for(aux=lista->primeiro ; aux != NULL ; aux=aux->prox)
		funcao(aux->dado);

}

int
removerUmDaLista (Lista* lista, void* chave, int (*funcao) (void*, void*))
{ // remove um nó da lista
	Node* aux, *anterior=NULL;

	if(!lista || !lista->primeiro )
		return 0;

	for( aux= lista->primeiro ; aux!=NULL ; anterior=aux, aux=aux->prox )
	{
		if( !funcao && ( aux->dado == chave ) )
		{
			if(anterior==NULL)
				lista->primeiro=aux->prox;
			else
				anterior->prox = aux->prox;

			free(aux->dado); // @1
			free(aux);

			lista->nelementos--;

			return 1;
		}

		else if( funcao && (*funcao) (aux->dado, chave) == 1)
		{ //Frederico Franco Calhau
			if(anterior==NULL)
				lista->primeiro=aux->prox;
			else
				anterior->prox = aux->prox;

			free(aux->dado); // @1
			free(aux);

			lista->nelementos--;

			return 1;

		}
	}

	return 0;
}

int
removerVariosDaLista (Lista* lista, void* chave, int (*funcao)(void*, void*))
{ // remove varios nós da lista
	Node* aux, *anterior=NULL, *excluido;

	if(!lista || !lista->primeiro )
		return 0;

	for( aux= lista->primeiro ; aux!=NULL ; )
	{
		if( !funcao && (aux->dado==chave) )
		{
			if(anterior==NULL)
				lista->primeiro=aux->prox;
			else
				anterior->prox = aux->prox;

			excluido = aux;
			aux = aux->prox;

			free(excluido->dado); // @1
			free(excluido);

			lista->nelementos--;

		}

		else if( funcao && (*funcao) (aux->dado, chave) == 1)
		{
			if(anterior==NULL)
				lista->primeiro=aux->prox;
			else
				anterior->prox = aux->prox;

			excluido=aux;
			aux=aux->prox;

			free(excluido->dado); // @1
			free(excluido);

			lista->nelementos--;
		}

		else
		{
			anterior=aux;
			aux=aux->prox;
		}

	}

	return 1;
}


int
tamanhoDaLista (Lista* lista)
{
	if (!lista)
		return -1;

	return lista->nelementos;
}
