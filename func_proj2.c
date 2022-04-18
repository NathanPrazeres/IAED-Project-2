#include "func_proj1.h"
#include "func_proj2.h"

/* Variaveis Globais */

extern int _numVoos;
extern Voo _voos[];


/* Reservas */


void memoryOverload(Reserva* head)
{
    printf(ERR_MEM);
	destroy(head);
	exit(0);
}

Reserva* pop(Reserva* head) 
{
    Reserva * aux = head->next;
	free(head->codigoReserva);
    free(head);
    return aux;
}


void destroy(Reserva* head)
{
    while(head != NULL) {
        head = pop(head);
    }
}


Reserva* push(Reserva* head, char cV[], Data data, char* cR, int nP)
{
	int i;
	Reserva *reserva;
	
	if ((reserva = (Reserva*) malloc(sizeof(Reserva))) == NULL)
		memoryOverload(head);

	for (i = 0; i < MAX_CODIGO_VOO; i++)
		reserva->codigoVoo[i] = cV[i];
	reserva->data = data;
	reserva->codigoReserva = cR;
	reserva->numPassageiros = nP;
	reserva->next = head;
	return reserva;
}


int removeVoos(char* codigo, int flag)
{
	int i;

	for (i = 0; i < _numVoos; i++) {
		if (!strcmp(_voos[i].id, codigo)) {
			flag = FALSE;
			for (i = i; i < _numVoos - 1; i++)
				_voos[i] = _voos[i + 1];
			_numVoos--;
			i--;
		}
	}
	return flag;
}


int testaCodigoReserva(char* cR, int errorCode)
{
	int i, len, flag = FALSE;

	len = strlen(cR);
	if (len < 10)
		flag = TRUE;
	for (i = 0; i < len; i++)
		if (!(('A' <= cR[i] && cR[i] <= 'Z') || ('0' <= cR[i] && cR[i] <= '9')))
			flag = TRUE;
	return flag? 1:errorCode;
}


int testeVooExiste(char cV[], Data data, int errorCode)
{
	return (encontraVoo(cV, data) == -1)? 2:errorCode;
}


int testeReservasDuplicas(char* cR, Reserva* head, int errorCode)
{
	Reserva *curr = head;

	while (curr != NULL) {
		if (!strcmp(cR, curr->codigoReserva))
			return 3;
		curr = curr->next;
	}
	return errorCode;
}


int testeCapacidadeVoo(Reserva* head, char cV[], Data d, int nP, int errorCode)
{
	int numReservas = nP, indice = encontraVoo(cV, d);
	Reserva *curr = head;

	while (curr != NULL) {
		if (!strcmp(curr->codigoVoo, cV) && 
				converteDataNum(d) == 
				converteDataNum(curr->data))
			numReservas += curr->numPassageiros;
		curr = curr->next;
	}
	if (indice != -1 && numReservas > _voos[indice].capacidade)
		return 4;
	return errorCode;
}


int testeData(Data data, int errorCode)
{
	return (validaData(data))? errorCode:5;
}


int testeNumPassageiros(int numPassageiros, int errorCode)
{
	return (numPassageiros > 0)? errorCode:6;
}


int testesErrosReservaAdicionar(Reserva* head, 
		char cV[], char* cR, Data data, int nP)
{
	int errorCode = 0;
	errorCode = testeNumPassageiros(nP, errorCode);
	errorCode = testeData(data, errorCode);
	errorCode = testeCapacidadeVoo(head, cV, data, nP, errorCode);
	errorCode = testeReservasDuplicas(cR, head, errorCode);
	errorCode = testeVooExiste(cV, data, errorCode);
	errorCode = testaCodigoReserva(cR, errorCode);
	return errorCode;
}


int testesErrosReservasListar(char cV[], Data data)
{
	int errorCode = 0;
	errorCode = testeData(data, errorCode);
	errorCode = testeVooExiste(cV, data, errorCode);
	return errorCode;
}


void trataErros(int errorCode, char cV[], char* cR)
{
	switch (errorCode)
	{
		case 1:
			printf(ERR_COD_RES);
			break;
		case 2:
			printf(ERR_COD_VOO, cV);
			break;
		case 3:
			printf(ERR_COD_RES_DUP, cR);
			break;
		case 4:
			printf(ERR_NUM_RES);
			break;
		case 5:
			printf(ERR_DATA);
			break;
		case 6:
			printf(ERR_NUM_PASS);
			break;
	}
}




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
	res1->codigoReserva = res2->codigoReserva;
	res1->numPassageiros = res2->numPassageiros;

	res2->data = data;
	res2->codigoReserva = cR;
	res2->numPassageiros = nP;
}

void bubbleSortReservas(Reserva* head)
{
	int swapped;
	Reserva *curr;
	Reserva *last = NULL;

	if (head == NULL)
		return;

	do
	{
		swapped = FALSE;
		curr = head;

		while (curr->next != last)
		{
			if (strcmp(curr->codigoReserva, curr->next->codigoReserva) > 0)
			{ 
				trocaReservas(curr, curr->next);
				swapped = TRUE;
			}
			curr = curr->next;
		}
		last = curr;
	}
	while (swapped);
}

void mostraReservas(Reserva* head, char cV[], Data data)
{
	Reserva *curr;
	for (curr = head; curr != NULL; curr = curr->next) {
		if (!strcmp(curr->codigoVoo, cV) && 
				converteDataNum(data) == 
				converteDataNum(curr->data))
			printf(OUT_RES, curr->codigoReserva, 
					curr->numPassageiros);
	}
}