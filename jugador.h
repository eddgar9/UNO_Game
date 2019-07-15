#ifndef _JUGADOR_H_
#define _JUGADOR_H_

#include "baraja.c"

#define MAXC 50
#define CARTAS_INICIALES 7

typedef struct tJugador{
	char nombre[MAXC];
	char tipo; //H - Humano | C - Bot Calmado | A - Bot Agresivo
	tBaraja mano;
	int cartas_iniciales;
	int ganadas;
	int perdidas;
}tJugador;
/*
void jugador_crear(tJugador *jugador, char nombre[MAXC], char tipo, int ganadas, int perdidas, int n_cartas);
void jugador_mostrar(tJugador *jugador);
*/
#endif
