#ifndef _BARAJA_C_
#define _BARAJA_C_

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

#include "baraja.h"

char baraja_color_predominante(tBaraja *baraja){
	int colores[4] = {0, 0, 0, 0};
	int posicion;
	tCarta carta;
	char color = ' ';
	int mas_veces = 0;
	
	for(posicion = 0; posicion < baraja->n_cartas; posicion++){
		baraja_buscar(baraja, posicion, &carta);
		switch(carta.color){
			case 'R':
				colores[0]++;
				break;
			case 'G':
				colores[1]++;
				break;
			case 'B':
				colores[2]++;
				break;
			case 'Y':
				colores[3]++;
				break;
		}
	}
	
	for(posicion = 0; posicion < 4; posicion++){
		if(colores[posicion] > colores[mas_veces]){
			mas_veces = posicion;
		}
	}
	
	switch(mas_veces){
	case 1:
		color = 'G';
		break;
	case 2:
		color = 'B';
		break;
	case 3:
		color = 'Y';
		break;
	case 0:
		color = 'R';
		break;
	}
	
	return color;
}

void baraja_crear(tBaraja *baraja){
	baraja->n_cartas = 0;
	baraja->cursor = 0;
	baraja->primera = NULL;
	baraja->ultima = NULL;
}

int baraja_es_jugable(tBaraja *baraja, tCarta carta){
	int es_jugable = 0;
	if(baraja->n_cartas == 0){
		es_jugable = 1;
	}else if(carta.numero == 11){ //Es comodin 
		es_jugable = 1;
	}else if(carta.numero == 10 && carta.tipo == baraja->ultima->carta.tipo){
		es_jugable = 1;
	}else if(baraja->ultima->carta.color == carta.color || baraja->ultima->carta.numero == carta.numero){
		es_jugable = 1;
	}
	return es_jugable;
}

void baraja_mostrar(tBaraja *lista){
	tNodoCarta *actual = lista->primera;
	int posicion = 0;
	tCarta carta;
	
	while(posicion < lista->n_cartas){
		carta = actual->carta;
		carta_mostrar(carta);
		printf("\n");
		
		actual = actual->siguiente;
		posicion++;
	}
}

void baraja_buscar(tBaraja *lista, int elegida, tCarta *carta){
	tNodoCarta *actual = lista->primera;
	int posicion = 0;
	
	if(elegida < lista->n_cartas && elegida >= 0){
		while(posicion < elegida && actual->siguiente != NULL){
			actual = actual->siguiente;
			posicion++;
		}
		if(posicion == elegida){
			carta_crear(carta, actual->carta.numero, actual->carta.color, actual->carta.tipo);
		}else{
			carta_crear(carta, -1, '\0', '\0');
		}
	}else{
		carta_crear(carta, -1, '\0', '\0');
	}
}

void baraja_siguiente(tBaraja *lista, tCarta *carta){
	
}

void baraja_anterior(tBaraja *lista, tCarta *carta){
}

void baraja_insertar(tBaraja *lista, int numero, char color, char tipo){
	tNodoCarta *aux;
	aux = (tNodoCarta*)malloc(sizeof(tNodoCarta));
	if (aux != NULL){
		carta_crear(&aux->carta, numero, color, tipo);
		aux->siguiente = NULL;
		if(lista->n_cartas == 0){
			aux->anterior = NULL;
			lista->primera = aux;
		}else{
			aux->anterior = lista->ultima;
			lista->ultima->siguiente = aux;
		}
		lista->ultima = aux;
		(lista->n_cartas)++;
		
	}
}

void baraja_extraer(tBaraja *lista, tCarta *carta, int elegida){
	tNodoCarta *actual = lista->primera;
	int posicion = 0;
	
	if(elegida < lista->n_cartas){
		while(posicion < elegida){
			actual = actual->siguiente;
			posicion++;
		}
		
		carta_crear(carta, actual->carta.numero, actual->carta.color, actual->carta.tipo);
		if(actual->anterior != NULL){
			actual->anterior->siguiente = actual->siguiente;
		}else{
			lista->primera = actual->siguiente;
		}
		(lista->n_cartas)--;
	}
}

void baraja_mezclar(tBaraja *lista){
	int probabilidad;
	tBaraja aux_1;
	tCarta carta;
	baraja_crear(&aux_1);
	
	while(lista->n_cartas > 0){
		probabilidad = rand() % lista->n_cartas;
		baraja_extraer(lista, &carta, probabilidad);
		baraja_insertar(&aux_1, carta.numero, carta.color, carta.tipo);
	}
	
	while(aux_1.n_cartas > 0){
		baraja_descarte(&aux_1, &carta);
		baraja_insertar(lista, carta.numero, carta.color, carta.tipo);
	}
}

void baraja_descarte(tBaraja *lista, tCarta *carta){
	if(lista->n_cartas > 0){
		carta_crear(carta, lista->ultima->carta.numero, lista->ultima->carta.color, lista->ultima->carta.tipo);
		lista->ultima = lista->ultima->anterior;
		(lista->n_cartas)--;
	}else{
		carta_crear(carta, -1, '\0', '\0');
	}
}


#endif
