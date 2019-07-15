#ifndef _LISTAJUGADORES_H_
#define _LISTAJUGADORES_H_

#include "jugador.c"

typedef struct tNodoJugador{
	tJugador jugador;
	struct tNodoJugador *siguiente;
	struct tNodoJugador *anterior;
}tNodoJugador;

typedef struct tListaJugadores{
	int n_jugadores;
	int cursor;
	tNodoJugador *primero;
	tNodoJugador *ultimo;
}tListaJugadores;

void jugadores_mostrar(tListaJugadores *lista);
void jugadores_crear(tListaJugadores *lista);
void jugadores_buscar(tListaJugadores *lista, int posicion, tJugador *jugador);
void jugadores_siguiente(tListaJugadores *lista, tJugador *jugador);
void jugadores_anterior(tListaJugadores *lista, tJugador *jugador);
void jugadores_insertar(tListaJugadores *lista, char nombre[MAXC], char tipo, int n_cartas);
tJugador* jugadores_coger_jugador(tListaJugadores *lista, int elegido);

#endif
