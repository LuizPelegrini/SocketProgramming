/* contém as funções utilizadas pela aplicação implementada no lado do servidor */

#include "app-server.h"


void processar_msg(char *msg)
{
	//extrair protocolo e dados referentes à funcionalidade desejada
}


//...


void selecionar_funcao()
{
	switch(func_atual)
	{
		case -1:
			//imprimir erro
			break;

		case 0:
			inserir();
			break;

		case 1:
			alterar();
			break;

		case 2:
			remover();
			break;

		case 3:
			buscar();
			break;

		case 4:
			finapp();
			break;
	}
}


//tenta inserir registro válido na lista
//retorna 1 se registro já existe
int inserir()
{
	if(buscarNaLista(reg_atual....))	//é preciso alterar a função buscarNaLista para permitir comparação de strings
		return 1;

	inserirNaLista(listatelefonica,reg_atual);
	return 0;
}


//altera o telefone de um registro e o retorna
Registro alterar()
{
	return NULL;
}


//remove registro da lista e retorna sucesso ou fracasso se não encontrado
int remover()
{
  return 0;
}


//busca pelo nome
Registro buscar()
{
  return NULL;
}


//encerra aplicação
void finapp()
{
}
