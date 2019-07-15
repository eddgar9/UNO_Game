#ifndef _JUGADOR_C_
#define _JUGADOR_C_

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

#include "jugador.h"

void jugador_crear(tJugador *jugador, char nombre[MAXC], char tipo, int ganadas, int perdidas, int n_cartas){
	baraja_crear(&jugador->mano);
	strcpy(jugador->nombre, nombre);
	jugador->cartas_iniciales = CARTAS_INICIALES;
	jugador->tipo = tipo;
	jugador->ganadas = ganadas;
	jugador->perdidas = perdidas;
	jugador->cartas_iniciales = n_cartas;
}

void jugador_mostrar(tJugador *jugador){
	int posicion;
	for(posicion = 0; posicion < 20; posicion++){
		if(posicion < strlen(jugador->nombre)){
			printf("%c", jugador->nombre[posicion]);
		}else{
			printf(" ");
		}
	}
	printf("% 2d", jugador->mano.n_cartas);
	if(jugador->mano.n_cartas != 1){
		printf(" cartas\t");
	}else{
		printf(" carta\t");
	}
}

#endif
