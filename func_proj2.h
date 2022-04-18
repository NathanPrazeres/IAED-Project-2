#include "defs_structs.h"



#ifndef _FUNC_PROJ2_H_
#define _FUNC_PROJ2_H_

/* Variaveis Globais */

extern int _numVoos;
extern Voo _voos[];

/* Prototipos das Funcoes de Reservas */

void memoryOverload(Reserva* head);

Reserva* pop(Reserva* head);

void destroy(Reserva* head);

Reserva* push(Reserva* head, char cV[], Data data, char* cR, int nP);

int removeVoos(char* codigo, int flag);

int testaCodigoReserva(char* cR, int errorCode);

int testeVooExiste(char cV[], Data data, int errorCode);

int testeReservasDuplicas(char* cR, Reserva* head, int errorCode);

int testeCapacidadeVoo(Reserva* head, char cV[], Data d, int nP, 
        int errorCode);

int testeData(Data data, int errorCode);

int testeNumPassageiros(int numPassageiros, int errorCode);

int testesErrosReservaAdicionar(Reserva* head, 
        char cV[], char* cR, Data data, int nP);

int testesErrosReservasListar(char cV[], Data data);

void trataErros(int errorCode, char cV[], char* cR);

void trocaReservas(Reserva* res1, Reserva* res2);

void bubbleSortReservas(Reserva* head);

void mostraReservas(Reserva* head, char cV[], Data data);

#endif