/*
    lista.h
    -------
    Lista Simplesmente Encadeada com N� Descritor: lista gen�rica capaz de realizar opera��es b�sicas.

    Como utilizar:
        Basta criar uma vari�vel na sua aplica��o do tipo "Lista*" e chamar a fun��o que inicia devidamente a lista: "suaVariavelDeLista = inicializarLista();".
        Todas as fun��es dessa biblioteca necessitam como primeiro argumento a lista.

    Observa��es Importantes:
        1) Inser��o sempre realizada no COME�O da lista.
        2) Na remo��o de um elemento da lista, tanto o elmento, quanto o dado que est� sendo armazenado pelo elemento s�o apagados da mem�ria. Caso a aplica��o
        necessite que o dado nao seja apagado, basta comentar as linhas indicadas com um "@1" nas fun��es de remover.

    Por: Felipe Brand�o 11311BCC023, Frederico Franco 11311BCC057 e Pedro Henrique Ribeiro 11311BCC040, Agosto, 2014.
*/

#include <stdlib.h>


/*-------------------------------------------------------
        	STRUCTS e TYPEDEFS							*/

struct lista
{ // n� descritor da lista
	int nelementos;
	struct node* primeiro;

};
typedef struct lista Lista;


struct node
{ // n� da lista
	void* dado;
	struct node* prox;
};
typedef struct node Node;

//-------------------------------------------------------


/*
	buscarNaLista() : void* = elemento guardado no n�
	-------------------------------------------------------
 	Compara os elementos da lista com a chave por meio da FUNCAO passada e RETORNA o PRIMEIRO elemento encontrado.
	Caso n�o encontre, RETORNA NULL.

Par�metros:
	int (*funcao) - caso seja NULL, a buscarNaLista ir� checar se os endere�os guardados pela chave e pelo elemento da lista sao iguais.
*/
void*
buscarNaLista (Lista* lista, void* chave, int (*funcao)(void* elementoDaLista, void* aChave) );


/*
	buscarPosNaLista() : void* = elemento guardado no n�
	-------------------------------------------------------
  	Busca a N-�sima posi��o na lista (POS) e retorna a refer�ncia para o elemento guardado naquela posi��o.
*/
void*
buscarPosNaLista (Lista* lista, int pos);



/*
	inicializarLista() -> Lista* = refer�ncia ao descritor
	-------------------------------------------------------
  	Cria uma lista vazia e retorna o endere�o do n� descritor dela
*/
Lista*
inicializarLista();


/*
	inserirNaLista() -> void
	-------------------------------------------------------
  	Insere um n� no COME�O da lista que aponta para o DADO

Obs: N�O h� verifica��o se o elemento j� estava anteriormente na lista
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

Par�metros:
	int (*funcao) - caso seja NULL, a buscarNaLista ir� checar se os endere�os guardados pela chave e pelo elemento da lista sao iguais.
*/
int
removerUmDaLista (Lista* lista, void* chave, int (*funcao) (void* elementoDaLista, void* aChave));

/*
	removerVariosDaLista() -> int = sucesso/fracasso
	-------------------------------------------------------
  	Compara os elementos da lista com a chave por meio da FUNCAO passada como argumento e REMOVE TODOS os elementos que retornam 1.

Par�metros:
	int (*funcao) - caso seja NULL, a buscarNaLista ir� checar se os endere�os guardados pela chave e pelo elemento da lista sao iguais.
*/
int
removerVariosDaLista (Lista* lista, void* chave, int (*funcao) (void* elementoDaLista, void* aChave));


/*
	tamanhoDaLista() : int = n�mero de elementos na lista
	-------------------------------------------------------
  	Retorna o n�mero de elementos, tamanho, da lista.
	Retorna -1 caso a lista n�o exista.
*/
int
tamanhoDaLista (Lista* lista);
