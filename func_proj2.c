#include "func_proj1.h"
#include "func_proj2.h"


/* Variaveis Globais */


extern int _numVoos;
extern Voo _voos[];


/* Funções Auxiliares */


/* ERRO DE MEMÓRIA
	Esta função termina o programa de forma controlada 
	no caso de haver falha durante a operação malloc(). 
*/
void erroMemoria(Reserva* head)
{
    printf(ERR_MEM);
	destroy(head);
	exit(0);
}

/* POP
	Esta função remove, liberta e retorna 
	o elemento fornecido de uma linked list.
*/
Reserva* pop(Reserva* head) 
{
    Reserva *temp = head->next;
	free(head->codigoReserva);
    free(head);
    return temp;
}

/* DESTROY
	Esta função destroi a linked list cuja cabeça é fornecida, 
	libertando toda a memória alocada.
*/
void destroy(Reserva* head)
{
    while(head != NULL) {
        head = pop(head);
    }
}

/* PUSH
	Esta função insere um elemento no inicio da linked list cuja cabeça é 
	fornecida, alocando memória para o mesmo.

	Erros:
		-> ERROMEMORIA
*/
Reserva* push(Reserva* head, char cV[], Data data, char* cR, int nP)
{
	Reserva *reserva;
	
	if ((reserva = (Reserva*) malloc(sizeof(Reserva))) == NULL)
		erroMemoria(head);

    strcpy(reserva->codigoVoo, cV);
	reserva->data = data;
	reserva->codigoReserva = cR;
	reserva->numPassageiros = nP;
	reserva->next = head;
	return reserva;
}

/* REMOVE VOOS
	Esta função remove todos os voos cujo código é fornecido,
	libertando toda a memória alocada.
*/
int removeVoos(char* codigo, int flag)
{
	int i, j = 0;

	for (i = 0; i < _numVoos; i++) {
		if (strcmp(_voos[i].id, codigo)) {
			_voos[j++] = _voos[i];
		}
		else {
			flag = FALSE;
		}
	}
	_numVoos = j;

	return flag;
}

/* VALIDA CODIGO DE RESERVA 
	Esta função verifica se o código de reserva fornecido é válido.
*/
int testaCodigoReserva(char* cR, int codigoErro)
{
	int i, len = strlen(cR);

	if (len < 10)
		return N_ERR_COD_RES;
    for (i = 0; i < len; i++)
        if (('A' > cR[i] || cR[i] > 'Z') && ('0' > cR[i] || cR[i] > '9'))
            return N_ERR_COD_RES;
    return codigoErro;
}

/* TESTES DE EXISTÊNCIA DE VOO, RESERVA DUPLCIADA E CAPACIDADE DE VOO
	Esta função verifica se o voo como o código cV existe, se o código de 
	reserva já foi usado e se o voo tem capacidade para receber mais 
	passageiros. 
*/
int testesCapacidadeDuplicaExiste(Reserva* head, char* cR, 
		char cV[], Data d, int nP, int codigoErro)
{
	int numReservas = nP, indice = encontraVoo(cV, d);
	Reserva *curr = head;

    if (indice == -1)
        return N_ERR_COD_VOO;

    while (curr != NULL) {
		if (!strcmp(cR, curr->codigoReserva))
			return N_ERR_COD_RES_DUP;

		if (!strcmp(curr->codigoVoo, cV) && 
				converteDataNum(curr->data) == converteDataNum(d))
			numReservas += curr->numPassageiros;
		curr = curr->next;
	}
	if (numReservas > _voos[indice].capacidade)
		return N_ERR_NUM_RES;
	return codigoErro;
}

/* TESTE DA DATA
	Esta função verifica se a data fornecida é válida.
*/
int testeData(Data data, int codigoErro)
{
	return (validaData(data))? codigoErro:N_ERR_DATA;
}

/* TESTE DO NUMERO DE PASSAGEIROS
	Esta função verifica se o número de passageiros fornecido é válido.
*/
int testeNumPassageiros(int numPassageiros, int codigoErro)
{
	return (numPassageiros > 0)? codigoErro:N_ERR_NUM_PASS;
}

/* TESTES DOS ERROS DE ADIÇÃO DE RESERVAS
	Esta função verifica se uma reserva é válida e se pode ser adicionada
	ao programa chamando as funções testeData, testeNumPassageiros, 
	testesCapacidadeDuplicaExiste e testaCodigoReserva.
*/
int testesErrosReservaAdicionar(Reserva* head, 
		char cV[], char* cR, Data data, int nP)
{
	int codigoErro = 0;
	codigoErro = testeNumPassageiros(nP, codigoErro);
	codigoErro = testeData(data, codigoErro);
	codigoErro = testesCapacidadeDuplicaExiste(head, cR, 
			cV, data, nP, codigoErro);
	codigoErro = testaCodigoReserva(cR, codigoErro);
	return codigoErro;
}

/* TESTES DOS ERROS DE LISTAGEM DE RESERVAS
	Esta função verifica se a data e o código de voo fornecidos são válidos.
*/
int testesErrosReservasListar(char cV[], Data data)
{
	int codigoErro = 0;
	codigoErro = testeData(data, codigoErro);
	codigoErro = testesCapacidadeDuplicaExiste(
			NULL, NULL, cV, data, 0, codigoErro);
	return codigoErro;
}

/* TRATA ERROS
	Esta função verifica se algum dos erros das funções anteriores foi 
	detetado e se sim para imprimir o erro correspondente.
*/
void trataErros(int codigoErro, char cV[], char* cR)
{
	switch (codigoErro)
	{
		case N_ERR_COD_RES:
			printf(ERR_COD_RES);
			break;
		case N_ERR_COD_VOO:
			printf(ERR_COD_VOO, cV);
			break;
		case N_ERR_COD_RES_DUP:
			printf(ERR_COD_RES_DUP, cR);
			break;
		case N_ERR_NUM_RES:
			printf(ERR_NUM_RES);
			break;
		case N_ERR_DATA:
			printf(ERR_DATA);
			break;
		case N_ERR_NUM_PASS:
			printf(ERR_NUM_PASS);
			break;
	}
}

/* TROCA RESERVAS
	Esta função troca o conteúdo de duas reservas.
*/
void trocaReservas(Reserva* res1, Reserva* res2)
{
	int i, nP = res1->numPassageiros;
	Data data = res1->data;
	char *cR = res1->codigoReserva, cV[MAX_CODIGO_VOO];

	for (i = 0; i < MAX_CODIGO_VOO; i++) {
		cV[i] = res1->codigoVoo[i];
		res1->codigoVoo[i] = res2->codigoVoo[i];
		res2->codigoVoo[i] = cV[i];
	}

	res1->data = res2->data;
	res2->data = data;

	res1->codigoReserva = res2->codigoReserva;
	res2->codigoReserva = cR;

	res1->numPassageiros = res2->numPassageiros;
	res2->numPassageiros = nP;
}

/* ORDENA RESERVAS
	Esta função ordena as reservas de um voo de acordo com o código de reserva 
	recorrendo a um algoritmo de bubble sort sobre linked lists.
*/
void bubbleSortReservas(Reserva* head)
{
	int troca = TRUE;
	Reserva *curr, *prev = NULL;

	if (head == NULL)
		return;

	while (troca) {
		troca = FALSE;
		curr = head;

		while (curr->next != prev)
		{
			if (strcmp(curr->codigoReserva, curr->next->codigoReserva) > 0)
			{
				trocaReservas(curr, curr->next);
				troca = TRUE;
			}
			curr = curr->next;
		}
		prev = curr;
	}
}

/* MOSTRA RESERVAS
	Esta função mostra as reservas que têm o código de voo e a data fornecidos.
*/
void mostraReservas(Reserva* head, char cV[], Data data)
{
	Reserva *curr;
	for (curr = head; curr != NULL; curr = curr->next) {
		if (!strcmp(curr->codigoVoo, cV) && 
				converteDataNum(curr->data) == converteDataNum(data))
			printf(OUT_RES, curr->codigoReserva, curr->numPassageiros);
	}
}