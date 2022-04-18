#ifndef _DEFS_STRUCTS_H_
#define _DEFS_STRUCTS_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Definicoes */

#define MAX_NUM_AEROPORTOS 40	/* número máximo de areoportos */
#define MAX_NUM_VOOS 30000	/* número máximo de voos */

#define MAX_CODIGO_AEROPORTO 4	/* dimensão do código do aeroporto */
#define MAX_NOME_PAIS 31	/* dimensão do nome do pais */
#define MAX_NOME_CIDADE 51	/* dimensão do nome da cidade */

#define MAX_CODIGO_VOO 7	/* dimensão do código do voo */
#define MAX_DATA 11		/* dimensão da data */
#define MAX_HORA 6		/* dimensão da hora */

#define MAX_LINHA 65535        /* dimensão maxima duma linha lida do ficheiro */

#define NAO_EXISTE -1		/* código de erro */

#define ANO_INICIO 2022		/* ano inicial do sistema */
#define DIAS_ANO 365		/* número de dias no ano */
#define HORAS_DIA 24		/* número de horas por dia */
#define MINUTOS_HORA 60		/* número de minutos numa hora */
#define MINUTOS_DIA 1440	/* número de minutos do dia */

#define TRUE 1			/* verdadeiro */
#define FALSE 0			/* falso */

/* MENSAGENS DE ERRO */

#define ERR_NOT_FOUND "not found\n"

#define ERR_MEM "No memory.\n"
#define ERR_COD_RES "invalid reservation code\n"
#define ERR_COD_VOO "%s: flight does not exist\n"
#define ERR_COD_RES_DUP "%s: flight reservation already used\n"
#define ERR_NUM_RES "too many reservations\n"
#define ERR_DATA "invalid date\n"
#define ERR_NUM_PASS "invalid passenger number\n"

#define OUT_RES "%s %d\n"

/* Estruturas de Dados */

typedef struct {
	char id[MAX_CODIGO_AEROPORTO];
	char pais[MAX_NOME_PAIS];
	char cidade[MAX_NOME_CIDADE];
	int numVoos;
} Aeroporto;

typedef struct {
	int dia;
	int mes;
	int ano;
} Data;

typedef struct {
	int hora;
	int minuto;
} Hora;

typedef struct {
	char id[MAX_CODIGO_VOO];
	char partida[MAX_CODIGO_AEROPORTO];
	char chegada[MAX_CODIGO_AEROPORTO];
	Data data;
	Hora hora;
	Hora duracao;
	int capacidade;
	int horaPartida;
	int horaChegada;
} Voo;

typedef struct node {
	char codigoVoo[MAX_CODIGO_VOO];
	Data data;
	char *codigoReserva;
	int numPassageiros;
	struct node *next;
} Reserva;


#endif