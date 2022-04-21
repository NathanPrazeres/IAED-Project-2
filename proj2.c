/*
	Nathaniel Prazeres
	ist1 103145
	2º Projeto de IAED
*/

#include "func_proj1.h"
#include "func_proj2.h"



/* Variaveis Globais */



int _numAeroportos = 0;		/* número de aeroportos introduzidos */
Aeroporto _aeroportos[MAX_NUM_AEROPORTOS];	/* vetor de aeroportos */

int _numVoos = 0		/* número de voos introduzidos */;
Voo _voos[MAX_NUM_VOOS];	/* vetor de voos */

Data _hoje = { 1, 1, 2022 };	/* data atual do sistema */

const int _diasMesAc[] =	/* dias acumulados por mês (jan=1) */
	{ 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 };



/* Funcoes Aeroportos */



void adicionaAeroporto() {
	Aeroporto a;

	leProximaPalavra(a.id);
	leProximaPalavra(a.pais);
	lePalavraAteFimDeLinha(a.cidade);

	if (aeroportoInvalido(a.id))
		printf("invalid airport ID\n");
	else if (_numAeroportos == MAX_NUM_AEROPORTOS)
		printf("too many airports\n");
	else if (encontraAeroporto(a.id) != NAO_EXISTE)
		printf("duplicate airport\n");
	else {
		strcpy(_aeroportos[_numAeroportos].id, a.id);
		strcpy(_aeroportos[_numAeroportos].pais, a.pais);
		strcpy(_aeroportos[_numAeroportos].cidade, a.cidade);
		_aeroportos[_numAeroportos].numVoos = 0;
		_numAeroportos++;
		printf("airport %s\n", a.id);
	}
}


void listaAeroportos() {
	char id[MAX_CODIGO_AEROPORTO];
	int indexAeroporto, ultima = 0;

	ultima = leProximaPalavra(id);
	if (strlen(id) == 0)
		listaTodosAeroportos();
	else {
		while (strlen(id) != 0) {
			indexAeroporto = encontraAeroporto(id);
			if (indexAeroporto == NAO_EXISTE)
				printf("%s: no such airport ID\n", id);
			else
				mostraAeroporto(indexAeroporto);
			if (!ultima)
				ultima = leProximaPalavra(id);
			else
				break;
		}
	}
}



/* Funcoes Voos */



void adicionaListaVoos() {
	Voo v;
	int i;

	if (leProximaPalavra(v.id)) {
		for (i = 0; i < _numVoos; i++)
			mostraVoo(i);
		return;
	} else {
		leProximaPalavra(v.partida);
		leProximaPalavra(v.chegada);
		v.data = leData();
		v.hora = leHora();
		v.duracao = leHora();
		scanf("%d", &v.capacidade);
		leAteFimDeLinha();
	}

	if (validaVoo(v))
		criaVoo(v);
}


void listaVoosPartida() {
	int indexVoos[MAX_NUM_VOOS], i, n = 0;
	char partida[MAX_CODIGO_AEROPORTO];

	lePalavraAteFimDeLinha(partida);

	if (encontraAeroporto(partida) == NAO_EXISTE)
		printf("%s: no such airport ID\n", partida);

	for (i = 0; i < _numVoos; i++) {
		if (!strcmp(_voos[i].partida, partida))
			indexVoos[n++] = i;
	}

	bubbleSort(indexVoos, n, cmpVoosPartida);

	for (i = 0; i < n; i++)
		mostraVooPartida(indexVoos[i]);
}


void listaVoosChegada() {
	int indexVoos[MAX_NUM_VOOS], i, n = 0;
	char chegada[MAX_CODIGO_AEROPORTO];

	lePalavraAteFimDeLinha(chegada);

	if (encontraAeroporto(chegada) == NAO_EXISTE)
		printf("%s: no such airport ID\n", chegada);

	for (i = 0; i < _numVoos; i++) {
		if (!strcmp(_voos[i].chegada, chegada))
			indexVoos[n++] = i;
	}

	bubbleSort(indexVoos, n, cmpVoosChegada);

	for (i = 0; i < n; i++)
		mostraVooChegada(indexVoos[i]);
}


void alteraData() {
	Data d;

	d = leData();
	leAteFimDeLinha();
	if (validaData(d) == FALSE)
		printf("invalid date\n");
	else {
		_hoje = d;
		mostraData(_hoje);
		printf("\n");
	}
}





/* RESERVAS */





/* ADICIONA OU LISTA RESERVAS
	Esta função é chamada quando o utilizador introduz o comando 'r' e serve 
	para adicionar uma reserva ao sistema. Se apenas for fornecido o código
	de voo e a data da reserva, a função lista as reservas para esse voo. 

	Erros:
		-> Se o código de voo for inválido;
		-> Se o voo não existir;
		-> Se já houver uma reserva com o mesmo código de reserva;
		-> Se a data for inválida;
		-> Se o voo não tiver capacidade para o número de pessoas na reserva.
*/
Reserva* adicionaListaReservas(Reserva* head)
{
    int numPassageiros, errorCode;
    char c, codigoVoo[MAX_CODIGO_VOO], *codigoReserva;
    Data data;

    scanf("%s", codigoVoo);
	data = leData();

    if ((c = getchar()) == '\n') {
		
		errorCode = testesErrosReservasListar(codigoVoo, data);

		if (errorCode)
			trataErros(errorCode, codigoVoo, NULL);
		else {
			bubbleSortReservas(head);
			mostraReservas(head, codigoVoo, data);
		}
    }
    else {
		if ((codigoReserva = (char*) malloc(sizeof(char) * MAX_LINHA)) == NULL) 
			erroMemoria(head);

        scanf("%s %d", codigoReserva, &numPassageiros);

		errorCode = testesErrosReservaAdicionar(head, codigoVoo, 
				codigoReserva, data, numPassageiros);
		
		if (errorCode) {
			trataErros(errorCode, codigoVoo, codigoReserva);
			free(codigoReserva);
		}
		else
			head = push(head, codigoVoo, data, codigoReserva, numPassageiros);
    }

	return head;
}


/* ELIMINA RESERVAS OU VOOS
	Esta função é chamada quando o utilizador introduz o comando 'e' e serve 
	para eliminar uma reserva ou um voo do sistema. Se apenas for fornecido 
	o código de voo, a função elimina esse voo e todas as reservas para esse 
	voo. 

	Erros:
		-> Se o código de voo for inválido;
		-> Se o voo não existir;
		-> Se o código de reserva for inválido;
		-> Se a reserva não existir.
*/
Reserva* eliminaReservasVoos(Reserva* head)
{
	int len, mudaHead = TRUE, flag = TRUE;
	char *codigo;
	Reserva *curr = head, *prev;

	if ((codigo = (char*) malloc(sizeof(char) * MAX_LINHA)) == NULL)
		erroMemoria(head);

	scanf("%s", codigo);
	len = strlen(codigo);

	while (curr != NULL) {

		if (!flag && len >= MAX_CODIGO_VOO) {
			free(codigo);
			return head;
		}
		if (!strcmp(curr->codigoReserva, codigo) || 
				!strcmp(curr->codigoVoo, codigo)) {
			flag = FALSE;

			if (mudaHead) {
				head = curr->next;
			}
			else {
				prev->next = curr->next;
			}
			curr = pop(curr);
		}
		else {
			mudaHead = FALSE;
			prev = curr;
			curr = curr->next;
		}
	}

	flag = removeVoos(codigo, flag);

	if (flag)
		printf(ERR_NOT_FOUND);

	free(codigo);

	return head;
}



int main() {
	int c;
	Reserva *head = NULL;
	
	while ((c = getchar()) != 'q' && c != EOF) {
		switch (c) {
			case 'a': adicionaAeroporto();
				break;
			case 'l': listaAeroportos();
				break;
			case 'v': adicionaListaVoos();
				break;
			case 'p': listaVoosPartida();
				break;
			case 'c': listaVoosChegada();
				break;
			case 't': alteraData();
				break;
			case 'r': head = adicionaListaReservas(head);
				break;
			case 'e': head = eliminaReservasVoos(head);
				break;
		}
	}
	destroy(head);
	return 0;
}
