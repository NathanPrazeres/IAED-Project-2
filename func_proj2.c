#include "func_proj1.h"
#include "func_proj2.h"

/* Variaveis Globais */

extern int _numVoos;
extern Voo _voos[];


/* Reservas */


void erroMemoria(Reserva* head)
{
    printf(ERR_MEM);
	destroy(head);
	exit(0);
}

Reserva* pop(Reserva* head) 
{
    Reserva *temp = head->next;
	free(head->codigoReserva);
    free(head);
    return temp;
}


void destroy(Reserva* head)
{
    while(head != NULL) {
        head = pop(head);
    }
}


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


int testaCodigoReserva(char* cR, int codigoErro)
{
	int i, len = strlen(cR);

	if (len < 10)
		return 1;
    for (i = 0; i < len; i++)
        if (('A' > cR[i] || cR[i] > 'Z') && ('0' > cR[i] || cR[i] > '9'))
            return 1;
    return codigoErro;
}


int testeVooExiste(char cV[], Data data, int codigoErro)
{
	return (encontraVoo(cV, data) == -1)? 2:codigoErro;
}


int testeReservasDuplicas(char* cR, Reserva* head, int codigoErro)
{
	Reserva *curr = head;
    if (codigoErro == 2)
        return codigoErro;
    while (curr != NULL) {
		if (!strcmp(cR, curr->codigoReserva))
			return 3;
		curr = curr->next;
	}
	return codigoErro;
}


int testeCapacidadeVoo(Reserva* head, char cV[], Data d, int nP, int codigoErro)
{
	int numReservas = nP, indice = encontraVoo(cV, d);
	Reserva *curr = head;

    if (indice == -1)
        return 2;
    while (curr != NULL) {
		if (!strcmp(curr->codigoVoo, cV) && d.dia == curr->data.dia && 
                d.mes == curr->data.mes && d.ano == curr->data.ano)
			numReservas += curr->numPassageiros;
		curr = curr->next;
	}
	if (numReservas > _voos[indice].capacidade)
		return 4;
	return codigoErro;
}


int testeData(Data data, int codigoErro)
{
	return (validaData(data))? codigoErro:5;
}


int testeNumPassageiros(int numPassageiros, int codigoErro)
{
	return (numPassageiros > 0)? codigoErro:6;
}


int testesErrosReservaAdicionar(Reserva* head, 
		char cV[], char* cR, Data data, int nP)
{
	int codigoErro = 0;
	codigoErro = testeNumPassageiros(nP, codigoErro);
	codigoErro = testeData(data, codigoErro);
	codigoErro = testeCapacidadeVoo(head, cV, data, nP, codigoErro);
	codigoErro = testeReservasDuplicas(cR, head, codigoErro);
    if (codigoErro != 2)
	    codigoErro = testeVooExiste(cV, data, codigoErro);
	codigoErro = testaCodigoReserva(cR, codigoErro);
	return codigoErro;
}


int testesErrosReservasListar(char cV[], Data data)
{
	int codigoErro = 0;
	codigoErro = testeData(data, codigoErro);
	codigoErro = testeVooExiste(cV, data, codigoErro);
	return codigoErro;
}


void trataErros(int codigoErro, char cV[], char* cR)
{
	switch (codigoErro)
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
	res2->data = data;

	res1->codigoReserva = res2->codigoReserva;
	res2->codigoReserva = cR;

	res1->numPassageiros = res2->numPassageiros;
	res2->numPassageiros = nP;
}

void bubbleSortReservas(Reserva* head)
{
	int troca;
	Reserva *curr;
	Reserva *previous = NULL;

	if (head == NULL)
		return;

	do
	{
		troca = FALSE;
		curr = head;

		while (curr->next != previous)
		{
			if (strcmp(curr->codigoReserva, curr->next->codigoReserva) > 0)
			{
				trocaReservas(curr, curr->next);
				troca = TRUE;
			}
			curr = curr->next;
		}
		previous = curr;
	}
	while (troca);
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