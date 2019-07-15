#ifndef _CARTA_C_
#define _CARTA_C_

#ifndef _STDIO_H_
#include <stdio.h>
#endif

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

#include "carta.h"

void carta_crear(tCarta *carta, int numero, char color, char tipo){
	carta->color = color;
	carta->numero = numero;
	carta->tipo = tipo;
}

void carta_mostrar(tCarta carta){
	switch(carta.numero){
		case 11:
			printf("Comodin de ");
			break;
		case 10:
			break;
		default:
			printf("%d ", carta.numero);
			break;
	}
	
	switch(carta.tipo){
		case 'S':
			printf("Saltar turno ");
			break;
		case 's':
			printf("Cambio de sentido ");
			break;
		case 'r':
			printf("Robar 2 ");
			break;
		case 'R':
			printf("Robar 4 ");
			break;
		case 'C':
			printf("Color ");
			break;
	}
	
	switch(carta.color){
		case 'R':
			printf("Rojo");
			break;
		case 'G':
			printf("Verde");
			break;
		case 'B':
			printf("Azul");
			break;
		case 'Y':
			printf("Amarillo");
			break;
	}
}

#endif
