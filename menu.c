#ifndef _MENU_C_
#define _MENU_C_

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

#include "menu.h"

void menu_principal_ejecutar(tPartida *partida){
	char opcion = ' ';
	do{
		opcion = menu_principal_desplegar();
		menu_principal_gestionar(opcion, partida);
	} while(opcion != '0');
}

char menu_principal_desplegar(){
	char opcion;
	printf("\tMen� principal\n");
	printf("\t1. Jugar\n");
	printf("\t2. Mostrar estad�sticas\n");
	printf("\t0. Salir\n");
	printf("\tOpci�n: ");
	fflush(stdin);
	scanf("%c", &opcion);
	fflush(stdin);
	return opcion;
}

void menu_principal_gestionar(char opcion, tPartida *partida){
	printf("\n");
	switch(opcion){
		case '1':
			printf("\tMen� principal - Jugar\n");
			break;
		case '2':
			printf("\tMen� principal - Mostrar estad�sticas\n");
			break;
		case '0':
			printf("\tMen� principal - Salir\n");
			printf("\tHasta pronto . . .\n");
			break;
		default:
			printf("\tMen� principal - Error\n");
			printf("\tOpci�n no v�lida\n");
			break;
	}
	printf("\n");
}


#endif
