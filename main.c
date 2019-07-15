#ifndef _STDIO_H_
#include <stdio.h>
#endif

#ifndef _STDLIB_H_
#include <stdlib.h>
#endif

#ifndef _STRING_H_
#include <string.h>
#endif

#ifndef _TIME_H_
#include <time.h>
#endif

#include "menu.c"
#include "partida.c"



int main(int argc, char *argv[]){
	srand(time(NULL));
	tPartida partida;
	char opcion = ' ';
	char eleccion = ' ';
	
	partida_crear(&partida);
	
	if(partida_cargar_jugador(&partida, argv[1]) == 1){
		if(partida_cargar_bots(&partida, argv[2]) == 1){
			while(opcion != '3'){
				printf("UNO\n");
				printf("1. Jugar\n");
				printf("2. Mostrar estadisticas\n");
				printf("3. Salir\n");
				printf("Opcion: ");
				fflush(stdin);
				scanf("%c", &opcion);
				fflush(stdin);
				
				printf("\n");
				partida_limpiar_pantalla(0);
				switch(opcion){
				case '1':
					partida_repartir_cartas(&partida);
					
					while(partida.ganador == -1){
						partida_turno(&partida);
					}
					
					partida_mostrar_ganador(&partida);
					printf("\n");
					
					partida_limpiar_pantalla(1);
					
					partida_reiniciar(&partida);
					break;
				case '2':
					do{
						partida_limpiar_pantalla(0);
						printf("UNO - Estadisticas\n");
						printf("\nElige el tipo de estadisticas a visualizar:\n");
						printf("1. Jugador\n");
						printf("2. Bots\n");
						printf("3. Regresar al menu principal\n");
						printf("\n\nOpcion: ");
						fflush(stdin);
						scanf("%c", &eleccion);
						fflush(stdin);
						partida_limpiar_pantalla(0);
						switch(eleccion){
						case '1':
							partida_mostrar_estadisticas_jugador(partida);
							partida_limpiar_pantalla(1);
							break;
						case '2':
							partida_mostrar_estadisticas_bots(partida);
							partida_limpiar_pantalla(1);
							break;
						case '3':
							break;
						default:
							printf("\nError. Opcion no valida\n");
							partida_limpiar_pantalla(1);
							break;
						}
					} while(eleccion != '3');
					break;
				case '3':
					partida_guardar_jugador(partida.jugador, argv[1]);
					break;
				default:
					printf("\nError. Opcion no valida\n");
					partida_limpiar_pantalla(1);
					break;
				}
			}
		}
	}
	
	
	return 0;
}
