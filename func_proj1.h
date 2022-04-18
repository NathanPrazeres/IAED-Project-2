#include "defs_structs.h"



#ifndef _AUX_H_
#define _AUX_H_


/* Variaveis Globais */

extern int _numAeroportos;
extern Aeroporto _aeroportos[];
extern int _numVoos;
extern Voo _voos[];
extern Data _hoje;
extern const int _diasMesAc[];


Hora leHora();
Data leData();
int leProximaPalavra(char str[]);
void lePalavraAteFimDeLinha(char str[]);
void leAteFimDeLinha();

void mostraData(Data d);
void mostraHora(Hora h);
int converteDataNum(Data d);
int converteHoraNum(Hora h);
int converteDataHoraNum(Data d, Hora h);
Hora converteNumHora(int num);
Data converteNumData(int num);
int validaData(Data d);
int validaHora(Hora h);

void bubbleSort(int indexes[], int size, int (*cmpFunc) (int a, int b));

int aeroportoInvalido(char id[]);
int encontraAeroporto(char id[]);
void mostraAeroporto(int index);
int cmpAeroportos(int a, int b);
void listaTodosAeroportos();

void mostraVoo(int index);
void mostraVooPartida(int index);
void mostraVooChegada(int index);
int encontraVoo(char id[], Data d);
int validaIDVoo(char id[]);
int validaVoo(Voo v);
void criaVoo(Voo v);
int cmpVoosPartida(int a, int b);
int cmpVoosChegada(int a, int b);

#endif