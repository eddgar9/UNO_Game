#ifndef _BARAJA_H_
#define _BARAJA_H_

#include "carta.c"

typedef struct tNodoCarta{
	tCarta carta;
	struct tNodoCarta *siguiente;
	struct tNodoCarta *anterior;
}tNodoCarta;

typedef struct tBaraja{
	int n_cartas;
	int cursor;
	tNodoCarta *primera;
	tNodoCarta *ultima;
}tBaraja;

char baraja_color_predominante(tBaraja *baraja);
void baraja_crear(tBaraja *lista);
void baraja_mostrar(tBaraja *lista);
void baraja_buscar(tBaraja *lista, int posicion, tCarta *carta);
void baraja_siguiente(tBaraja *lista, tCarta *carta);
void baraja_anterior(tBaraja *lista, tCarta *carta);
void baraja_insertar(tBaraja *lista, int numero, char color, char tipo);
void baraja_mezclar(tBaraja *lista);
void baraja_descarte(tBaraja *lista, tCarta *carta);	

#endif
