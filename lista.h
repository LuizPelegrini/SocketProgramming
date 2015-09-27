/*
    lista.h
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

#include <stdlib.h>


/*-------------------------------------------------------
        	STRUCTS e TYPEDEFS							*/

struct lista
{ // nó descritor da lista
	int nelementos;
	struct node* primeiro;

};
typedef struct lista Lista;


struct node
{ // nó da lista
	void* dado;
	struct node* prox;
};
typedef struct node Node;

//-------------------------------------------------------


/*
	buscarNaLista() : void* = elemento guardado no nó
	-------------------------------------------------------
 	Compara os elementos da lista com a chave por meio da FUNCAO passada e RETORNA o PRIMEIRO elemento encontrado.
	Caso não encontre, RETORNA NULL.

Parâmetros:
	int (*funcao) - caso seja NULL, a buscarNaLista irá checar se os endereços guardados pela chave e pelo elemento da lista sao iguais.
*/
void*
buscarNaLista (Lista* lista, void* chave, int (*funcao)(void* elementoDaLista, void* aChave) );


/*
	buscarPosNaLista() : void* = elemento guardado no nó
	-------------------------------------------------------
  	Busca a N-ésima posição na lista (POS) e retorna a referência para o elemento guardado naquela posição.
*/
void*
buscarPosNaLista (Lista* lista, int pos);



/*
	inicializarLista() -> Lista* = referência ao descritor
	-------------------------------------------------------
  	Cria uma lista vazia e retorna o endereço do nó descritor dela
*/
Lista*
inicializarLista();


/*
	inserirNaLista() -> void
	-------------------------------------------------------
  	Insere um nó no COMEÇO da lista que aponta para o DADO

Obs: NÃO há verificação se o elemento já estava anteriormente na lista
*/
void
inserirNaLista (Lista* lista, void* dado);


/*
	percorrerLista() : void
	-------------------------------------------------------
  	Usa a FUNCAO em cada elemento da lista
*/
void
percorrerLista (Lista* lista, void (*funcao) (void* elementoDaLista));

/*
	removerUmDaLista() : int = sucesso/fracasso
	-------------------------------------------------------
  	Compara os elementos da lista com a chave por meio da FUNCAO passada e REMOVE o PRIMEIRO elemento que retorna 1.

Parâmetros:
	int (*funcao) - caso seja NULL, a buscarNaLista irá checar se os endereços guardados pela chave e pelo elemento da lista sao iguais.
*/
int
removerUmDaLista (Lista* lista, void* chave, int (*funcao) (void* elementoDaLista, void* aChave));

/*
	removerVariosDaLista() -> int = sucesso/fracasso
	-------------------------------------------------------
  	Compara os elementos da lista com a chave por meio da FUNCAO passada como argumento e REMOVE TODOS os elementos que retornam 1.

Parâmetros:
	int (*funcao) - caso seja NULL, a buscarNaLista irá checar se os endereços guardados pela chave e pelo elemento da lista sao iguais.
*/
int
removerVariosDaLista (Lista* lista, void* chave, int (*funcao) (void* elementoDaLista, void* aChave));


/*
	tamanhoDaLista() : int = número de elementos na lista
	-------------------------------------------------------
  	Retorna o número de elementos, tamanho, da lista.
	Retorna -1 caso a lista não exista.
*/
int
tamanhoDaLista (Lista* lista);
