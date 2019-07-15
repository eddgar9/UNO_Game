#ifndef _LISTAJUGADORES_C_
#define _LISTAJUGADORES_C_

#ifndef _STDIO_H_
#define _STDIO_H_
#include <stdio.h>
#endif

#ifndef _STDLIB_H_
#define _STDLIB_H_
#include <stdlib.h>
#endif

#ifndef _STRING_H_
#define _STRING_H_
#include <string.h>
#endif

#ifndef _TIME_H_
#define _TIME_H_
#include <time.h>
#endif

#include "listaJugadores.h"


void jugadores_mostrar(tListaJugadores *lista){
	tNodoJugador *actual = lista->primero;
	int posicion = 0;
	tJugador bot;
	
	while(posicion < lista->n_jugadores){
		bot = actual->jugador;
		printf("\t%s %c\n", bot.nombre, bot.tipo);
		
		actual = actual->siguiente;
		posicion++;
	}
}

tJugador * jugadores_coger_jugador(tListaJugadores *lista, int elegido){
	tNodoJugador *actual = lista->primero;
	int posicion = 0;
	
	if(elegido < lista->n_jugadores){
		while(posicion < elegido){
			actual = actual->siguiente;
			posicion++;
		}
		return &actual->jugador;
	}else{
		return  NULL;
	}
}

void jugadores_crear(tListaJugadores *lista){
	lista->cursor = 0;
	lista->n_jugadores = 0;
	lista->primero = NULL;
	lista->ultimo = NULL;
}

void jugadores_buscar(tListaJugadores *lista, int posicion, tJugador *jugador){
}

void jugadores_siguiente(tListaJugadores *lista, tJugador *jugador){
	tNodoJugador *actual = lista->primero;
	int posicion = 0;
	(lista->cursor)++;
	if(lista->cursor >= lista->n_jugadores){
		lista->cursor = 0;
	}
	
	while(posicion < lista->cursor){
		actual = actual->siguiente;
		posicion++;
	}
	jugador = &(actual->jugador);
}

void jugadores_anterior(tListaJugadores *lista, tJugador *jugador){
	tNodoJugador *actual = lista->primero;
	int posicion = 0;
	(lista->cursor)--;
	if(lista->cursor < 0){
		lista->cursor = lista->n_jugadores-1;
	}
	
	while(posicion < lista->cursor){
		actual = actual->siguiente;
		posicion++;
	}
	jugador = &(actual->jugador);
}

void jugadores_insertar(tListaJugadores *lista, char nombre[MAXC], char tipo, int n_cartas){
	tNodoJugador *aux;
	aux = (tNodoJugador*)malloc(sizeof(tNodoJugador));
	if (aux != NULL){
		jugador_crear(&aux->jugador, nombre, tipo, 0, 0, n_cartas);
		aux->siguiente = NULL;
		aux->anterior = NULL;
		if(lista->n_jugadores == 0){
			aux->anterior = NULL;
			lista->primero = aux;
		}else{
			aux->anterior = lista->ultimo;
			lista->ultimo->siguiente = aux;
		}
		lista->ultimo = aux;
		(lista->n_jugadores)++;
		
	}
}


#endif
