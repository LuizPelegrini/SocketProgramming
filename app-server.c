/* contém as funções utilizadas pela aplicação implementada no lado do servidor */

#include "app-server.h"


void processar_msg(char *msg)
{
	//extrair protocolo e dados referentes à funcionalidade desejadavoid processar_msg(char *msg)
	cmd = strtok(msg, " ");
	nome = strtok(NULL, " ");
	tel = strtok(NULL, " ");

	if(!strcmp("STORE", cmd)){
		func_atual = 0;
	}else if(!strcmp("REMOVE", cmd)){
		func_atual = 1;
	}else if(!strcmp("GET", cmd)){
		func_atual = 2;
	}else if(!strcmp("END", cmd)){
		func_atual = 3;
	}else{
		printf("command: not recognized")
		exit(1);
	}

	reg_atual = (Registro*)malloc(sizeof(Registro));
	strcpy(reg_atual->nome, nome);
	strcpy(reg_atual->telefone, tel);

	
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
	Registro* r = (Registro *) buscarNaLista(reg_atual->nome);
	strcpy(r->telefone,reg_atual->telefone);
	return r;
}


//remove registro da lista e retorna sucesso ou fracasso se não encontrado
int remover()
{
	Registro* r = (Registro *) buscarNaLista(reg_atual->nome);
	if(r == NULL)
		return 0;
		
	removerUmDaLista(r->nome);
  	return 1;
}


//busca pelo nome
Registro buscar()
{
	return (Registro *) buscarNaLista(reg_atual->nome);
}


//encerra aplicação
void finapp()
{
}
