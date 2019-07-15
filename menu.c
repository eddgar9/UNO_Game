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
	printf("\tMenú principal\n");
	printf("\t1. Jugar\n");
	printf("\t2. Mostrar estadísticas\n");
	printf("\t0. Salir\n");
	printf("\tOpción: ");
	fflush(stdin);
	scanf("%c", &opcion);
	fflush(stdin);
	return opcion;
}

void menu_principal_gestionar(char opcion, tPartida *partida){
	printf("\n");
	switch(opcion){
		case '1':
			printf("\tMenú principal - Jugar\n");
			break;
		case '2':
			printf("\tMenú principal - Mostrar estadísticas\n");
			break;
		case '0':
			printf("\tMenú principal - Salir\n");
			printf("\tHasta pronto . . .\n");
			break;
		default:
			printf("\tMenú principal - Error\n");
			printf("\tOpción no válida\n");
			break;
	}
	printf("\n");
}


#endif
