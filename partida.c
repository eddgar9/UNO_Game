#ifndef _PARTIDA_C_
#define _PARTIDA_C_

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

#define MAX_COPIAS 2
#define MAX_N_CARTAS 9
#define MAX_COMODINES 4

#include "partida.h"

void partida_crear(tPartida *partida){
	int num_carta, color_carta, copias;
	
	baraja_crear(&partida->descartes);
	baraja_crear(&partida->mazo);
	jugadores_crear(&partida->bots);
	jugador_crear(&partida->jugador, "Humano", 'H', 0, 0, CARTAS_INICIALES);
	partida->turno = 0;
	partida->sentido = 'v';
	partida->saltar_turno = 0;
	partida->robar = 0;
	partida->ganador = -1;
	
	//COMODINES DE COLOR
	for(copias = 0; copias < MAX_COMODINES; copias++){
		baraja_insertar(&partida->mazo, 11, '-', 'C');
	}
	
	//COMODINES DE ROBAR CUATRO
	for(copias = 0; copias < MAX_COMODINES; copias++){
		baraja_insertar(&partida->mazo, 11, '-', 'R');
	}
	
	for(color_carta = 0; color_carta < MAX_COLORES; color_carta++){
		//CARTAS NUMERADAS
		baraja_insertar(&partida->mazo, 0, codigos_color[color_carta], 'N');
		for(num_carta = 1; num_carta <= MAX_N_CARTAS; num_carta++){
			for(copias = 0; copias < MAX_COPIAS; copias++){
				baraja_insertar(&partida->mazo, num_carta, codigos_color[color_carta], 'N');
			}
		}
		
		//SALTAR TURNO
		for(copias = 0; copias < MAX_COPIAS; copias++){
			baraja_insertar(&partida->mazo, 10, codigos_color[color_carta], 'S');
		}
		
		//CAMBIO DE SENTIDO
		for(copias = 0; copias < MAX_COPIAS; copias++){
			baraja_insertar(&partida->mazo, 10, codigos_color[color_carta], 's');
		}
		
		//ROBAR DOS
		for(copias = 0; copias < MAX_COPIAS; copias++){
			baraja_insertar(&partida->mazo, 10, codigos_color[color_carta], 'r');
		}
	}
	
	//BARAJAR LAS CARTAS DEL MAZO
	baraja_mezclar(&partida->mazo);
}

tJugador * partida_coger_bot(tPartida *partida, int posicion){
	return jugadores_coger_jugador(&partida->bots, posicion);
}

void partida_repartir_cartas(tPartida *partida){
	int posicion, num_carta;
	tJugador *bot;
	tCarta carta;
	
	//GENERAR MANO DEL JUGADOR
	for(num_carta = 0; num_carta < partida->jugador.cartas_iniciales; num_carta++){
		baraja_descarte(&partida->mazo, &carta);
		baraja_insertar(&partida->jugador.mano, carta.numero, carta.color, carta.tipo);
	}
	
	//GENERAR MANO DE LOS BOTS
	for(posicion = 0; posicion < partida->bots.n_jugadores; posicion++){
		bot = partida_coger_bot(partida, posicion);
		for(num_carta = 0; num_carta < bot->cartas_iniciales; num_carta++){
			baraja_descarte(&partida->mazo, &carta);
			baraja_insertar(&bot->mano, carta.numero, carta.color, carta.tipo);
		}
	}
	
}

void partida_turno_humano(tPartida *partida, tJugador *jugador){
	tCarta carta; 
	char accion;
	int color;
	int opcion;
	char respuesta;
	int posicion;
	int repetir = 0, repetir_submenu = 0;
	
	int n_jugables;
	
	if(partida->robar > 0){
		printf("%s ha robado %d cartas por '", jugador->nombre, partida->robar);
		carta_mostrar(partida->descartes.ultima->carta);
		printf("'\n");
	}
	while(partida->robar > 0){
		if(partida->mazo.n_cartas == 0){ partida_recargar_mazo(partida); }
		
		baraja_descarte(&partida->mazo, &carta);
		printf(" '");
		carta_mostrar(carta);
		printf("'\n");
		baraja_insertar(&jugador->mano, carta.numero, carta.color, carta.tipo);
		(partida->robar)--;
	}
	
	if(partida->saltar_turno == 1){
		partida->saltar_turno = 0;
		printf("%s pierde su turno\n", jugador->nombre);
	}else{
		if(partida->mazo.n_cartas == 0){ partida_recargar_mazo(partida); }
		
		
		do{
			printf("%s escoge una accion:\n", jugador->nombre);
			printf("A. Ver mano\n");
			printf("B. Robar carta\n");
			printf("- ");
			fflush(stdin);
			scanf("%c", &accion);
			fflush(stdin);
			switch(accion){
				case 'A':
					partida_limpiar_pantalla(0);
					do{
						repetir = 0;
						
						printf("%d ", jugador->mano.n_cartas);
						if(jugador->mano.n_cartas != 1){
							printf("cartas");
						}else{
							printf("carta");
						}
						printf(":\n");
						
						n_jugables = 0;
						for(posicion = 0; posicion < jugador->mano.n_cartas; posicion++){
							baraja_buscar(&jugador->mano, posicion, &carta);
							printf("\t%d. ", posicion+1);
							carta_mostrar(carta);
							if(baraja_es_jugable(&partida->descartes, carta) == 1){
								printf("\t*");
								n_jugables++;
							}
							printf("\n");
						}
						printf("\n");
						
						printf("%s, escoge una accion:\n", jugador->nombre);
						if(n_jugables > 0){
							printf(" A. Jugar carta\n");
						}
						printf(" B. Robar carta\n");
						printf("- ");
						fflush(stdin);
						scanf("%c", &accion);
						fflush(stdin);
						
						printf("\n");
						switch(accion){
							case 'A':
								if(n_jugables == 0){
									repetir = 1;
								}else{
									do{
										repetir_submenu = 0;
										printf("¿Que carta quieres jugar? ");
										fflush(stdin);
										scanf("%d", &opcion);
										fflush(stdin);
										
										printf("\n");
										
										if(opcion > 0 && opcion <= jugador->mano.n_cartas){
											baraja_buscar(&jugador->mano, opcion-1, &carta);
											
											if(baraja_es_jugable(&partida->descartes, carta) == 1){
												baraja_extraer(&jugador->mano, &carta, opcion-1);
												if(carta.numero == 11){
													do{
														printf("Elige el color del comodin:\n");
														printf("1.- Rojo\n");
														printf("2.- Azul\n");
														printf("3.- Amarillo\n");
														printf("4.- Verde\n");
														printf("Opcion: ");
														fflush(stdin);
														scanf("%d", &color);
														fflush(stdin);
														if(color < 1 || color > 4){
															printf("\nError. Por favor, elige un color valido\n");
														}
													} while(color < 1 || color > 4);
													
													switch(color){
														case 1:
															carta.color = 'R';
															break;
														case 2:
															carta.color = 'B';
															break;
														case 3:
															carta.color = 'Y';
															break;
														case 4:
															carta.color = 'G';
															break;
													}
												}
												printf("%s ha jugado '", jugador->nombre);
												carta_mostrar(carta);
												printf("'\n");
												
												baraja_insertar(&partida->descartes, carta.numero, carta.color, carta.tipo);
												
												if(carta.numero > 9){ partida_efecto_especial(partida, carta); }
											}else{
												printf("\nError. No se puede jugar '");
												carta_mostrar(carta);
												printf("'\n");
												repetir_submenu = 1;
											}
										}else{
											printf("\nError. Elige una carta valida\n");
											repetir_submenu = 1;
										}
									} while(repetir_submenu == 1);
								}
								break;
							case 'B':
								baraja_descarte(&partida->mazo, &carta);
								
								printf("%s ha robado '", jugador->nombre);
								carta_mostrar(carta);
								if(baraja_es_jugable(&partida->descartes, carta) == 1){
									do{
										printf("' ¿Deseas jugar la carta? [S/N] ");
										fflush(stdin);
										scanf("%c", &respuesta);
										fflush(stdin);
										
										if(respuesta != 'S' && respuesta != 's' && respuesta != 'n' && respuesta != 'N'){
											printf("\nError. Por favor, elige una opcion valida\n");
										}
									}while(respuesta != 'S' && respuesta != 's' && respuesta != 'n' && respuesta != 'N');
									if(respuesta == 'S' || respuesta == 's'){
										if(carta.numero == 11){
											do{
												printf("Elige el color del comodin:\n");
												printf("1.- Rojo\n");
												printf("2.- Azul\n");
												printf("3.- Amarillo\n");
												printf("4.- Verde\n");
												printf("Opcion: ");
												fflush(stdin);
												scanf("%d", &color);
												fflush(stdin);
												if(color < 1 || color > 4){
													printf("\nError. Por favor, elige un color valido\n");
												}
											} while(color < 1 || color > 4);
											
											switch(color){
												case 1:
													carta.color = 'R';
													break;
												case 2:
													carta.color = 'B';
													break;
												case 3:
													carta.color = 'Y';
													break;
												case 4:
													carta.color = 'G';
													break;
											}
										}
										
										printf("%s ha jugado '", jugador->nombre);
										carta_mostrar(carta);
										printf("'\n");
										baraja_insertar(&partida->descartes, carta.numero, carta.color, carta.tipo);
										
										if(carta.numero > 9){ partida_efecto_especial(partida, carta); }
										
										repetir = 0;
									}else{
										baraja_insertar(&jugador->mano, carta.numero, carta.color, carta.tipo);
										repetir = 0;
									}
								}else{
									printf("'. No se puede jugar");
									baraja_insertar(&jugador->mano, carta.numero, carta.color, carta.tipo);
								}
								printf("\n");
								break;
							default:
								repetir = 1;
								break;
						}
						printf("\n");
						
						if(repetir == 1){
							printf("\nError. Por favor, elige una opcion de las ofrecidas\n");
						}
					}while(repetir == 1);
				break;
				case 'B':
					baraja_descarte(&partida->mazo, &carta);
					
					printf("%s ha robado '", jugador->nombre);
					carta_mostrar(carta);
					if(baraja_es_jugable(&partida->descartes, carta) == 1){
						do{
							printf("' ¿Deseas jugar la carta? [S/N] ");
							fflush(stdin);
							scanf("%c", &respuesta);
							fflush(stdin);
							
							if(respuesta != 'S' && respuesta != 's' && respuesta != 'n' && respuesta != 'N'){
								printf("\nError. Por favor, elige una opcion valida\n");
							}
						}while(respuesta != 'S' && respuesta != 's' && respuesta != 'n' && respuesta != 'N');
						
						printf("\n");
						
						if(respuesta == 'S' || respuesta == 's'){
							if(carta.numero == 11){
								do{
									printf("Elige el color del comodin:\n");
									printf("1.- Rojo\n");
									printf("2.- Azul\n");
									printf("3.- Amarillo\n");
									printf("4.- Verde\n");
									printf("Opcion: ");
									fflush(stdin);
									scanf("%d", &color);
									fflush(stdin);
									if(color < 1 || color > 4){
										printf("\nError. Por favor, elige un color valido\n");
									}
								} while(color < 1 || color > 4);
								
								switch(color){
								case 1:
									carta.color = 'R';
									break;
								case 2:
									carta.color = 'B';
									break;
								case 3:
									carta.color = 'Y';
									break;
								case 4:
									carta.color = 'G';
									break;
								}
							}
							printf("\n");
							
							printf("%s ha jugado '", jugador->nombre);
							carta_mostrar(carta);
							printf("'\n");
							baraja_insertar(&partida->descartes, carta.numero, carta.color, carta.tipo);
							
							if(carta.numero > 9){ partida_efecto_especial(partida, carta); }
							
							repetir = 0;
						}else{
							baraja_insertar(&jugador->mano, carta.numero, carta.color, carta.tipo);
							repetir = 0;
						}
					}else{
						printf("'. No se puede jugar");
						baraja_insertar(&jugador->mano, carta.numero, carta.color, carta.tipo);
					}
					printf("\n");
					break;
				default:
					printf("\nError. Por favor, elige una opcion de las ofrecidas\n");
					break;
			}
		} while(accion != 'A' && accion != 'B');
	}
	
}

int partida_buscar_carta_bot(tPartida *partida, tJugador *bot){
	int pos_color_valido = -1;
	int pos_numero_valido = -1;
	int pos_comodin_valido = -1;
	int pos_tipo_valido = -1;
	int pos_cero_valido = -1;
	int encontrada = -1;
	tCarta carta;
	tCarta referencia;
	int posicion;
	
	carta_crear(&referencia, partida->descartes.ultima->carta.numero, partida->descartes.ultima->carta.color, partida->descartes.ultima->carta.tipo);
	
	for(posicion = 0; posicion < bot->mano.n_cartas; posicion++){
		baraja_buscar(&bot->mano, posicion, &carta);
		if(baraja_es_jugable(&partida->descartes, carta) == 1){
			if(carta.numero == 0){
				pos_cero_valido = posicion;
			}
			if(carta.color == referencia.color){
				pos_color_valido = posicion;
			}
			if(carta.numero == referencia.color){
				pos_numero_valido = posicion;
			}
			if(carta.numero == 10 && carta.tipo == referencia.tipo){
				pos_tipo_valido = posicion;
			}
			if(carta.numero == 11){
				pos_comodin_valido = posicion;
			}
		}
	}
	
	if(bot->tipo == 'C'){ //Evita lanzar comodines 
		
		if(pos_cero_valido != -1){ 			//Jugar una carta con valor cero
			encontrada = pos_cero_valido;
		}else if(pos_color_valido != -1){ 	//Jugar una carta con el mismo color
			encontrada = pos_color_valido;
		}else if(pos_numero_valido != -1){ 	//Jugar una carta con el mismo número
			encontrada = pos_numero_valido;
		}else if(pos_tipo_valido != -1){ 	//Jugar una carta de tipo especial 
			encontrada = pos_tipo_valido;
		}else if(pos_comodin_valido != -1){ //Jugar un comodin
			encontrada = pos_comodin_valido;
		}
	}else if(bot->tipo == 'A'){ 			//Lanza comodines si puede 
		
		if(pos_comodin_valido != -1){ 		//Jugar un comodin
			encontrada = pos_comodin_valido;
		}else if(pos_cero_valido != -1){ 	//Jugar una carta con valor cero
			encontrada = pos_cero_valido;
		}else if(pos_color_valido != -1){ 	//Jugar una carta con el mismo color
			encontrada = pos_color_valido;
		}else if(pos_numero_valido != -1){ 	//Jugar una carta con el mismo número
			encontrada = pos_numero_valido;
		}else if(pos_tipo_valido != -1){ 	//Jugar una carta de tipo especial 
			encontrada = pos_tipo_valido;
		}
	}
		
	return encontrada;
}

void partida_recargar_mazo(tPartida *partida){
	tCarta carta;
	while(partida->descartes.n_cartas > 0){
		baraja_descarte(&partida->descartes, &carta);
		if(carta.numero == 11){ carta.color = '-'; }
		baraja_insertar(&partida->mazo, carta.numero, carta.color, carta.tipo);
	}
	printf("\n-- Se ha recargado el mazo con las cartas de la mesa --\n");
}

void partida_turno_bot(tPartida *partida, tJugador *bot){
	tCarta carta;
	char color = ' ';
	int carta_elegida = partida_buscar_carta_bot(partida, bot);
	
	srand(time(NULL));
	
	if(partida->robar > 0){
		printf("%s ha robado %d cartas por '", bot->nombre, partida->robar);
		carta_mostrar(partida->descartes.ultima->carta);
		printf("'\n");
	}
	while(partida->robar > 0){
		if(partida->mazo.n_cartas == 0){ partida_recargar_mazo(partida); }
		
		baraja_descarte(&partida->mazo, &carta);
		baraja_insertar(&bot->mano, carta.numero, carta.color, carta.tipo);
		(partida->robar)--;
	}
	
	if(partida->saltar_turno == 1){
		partida->saltar_turno = 0;
		printf("%s pierde su turno\n", bot->nombre);
	}else{
		if(partida->mazo.n_cartas == 0){ partida_recargar_mazo(partida); }
		
		if(carta_elegida == -1){
			baraja_descarte(&partida->mazo, &carta);
			
			printf("%s ha robado una carta\n", bot->nombre);
			if(baraja_es_jugable(&partida->descartes, carta) == 1){
				if((bot->tipo == 'A' && carta.numero == 11) || carta.numero != 11){
					baraja_insertar(&partida->descartes, carta.numero, carta.color, carta.tipo);
					printf("\n%s ha jugado '", bot->nombre);
					carta_mostrar(carta);
					printf("'\n");
				}else if(bot->tipo == 'C' && carta.numero == 11){
					baraja_insertar(&bot->mano, carta.numero, carta.color, carta.tipo);
				}
			}else{
				baraja_insertar(&bot->mano, carta.numero, carta.color, carta.tipo);
			}
		}else{
			baraja_extraer(&bot->mano, &carta, carta_elegida);
			
			if(carta.numero == 11){
				color = baraja_color_predominante(&bot->mano);
			}else{
				color = carta.color;
			}
			
			printf("%s ha jugado '", bot->nombre);
			carta_mostrar(carta);
			printf("'\n");
			
			if(carta.numero > 9){ partida_efecto_especial(partida, carta); }
			
			baraja_insertar(&partida->descartes, carta.numero, color, carta.tipo);
		}
	}
}

void partida_reiniciar(tPartida *partida){
	tCarta carta;
	tJugador *bot;
	int posicion;
	
	while(partida->descartes.n_cartas > 0){
		baraja_descarte(&partida->descartes, &carta);
		baraja_insertar(&partida->mazo, carta.numero, carta.color, carta.tipo);
	}
	while(partida->jugador.mano.n_cartas > 0){
		baraja_descarte(&partida->jugador.mano, &carta);
		baraja_insertar(&partida->mazo, carta.numero, carta.color, carta.tipo);
	}
	for(posicion = 0; posicion < partida->bots.n_jugadores; posicion++){
		bot = partida_coger_bot(partida, posicion);
		while(bot->mano.n_cartas > 0){
			baraja_descarte(&bot->mano, &carta);
			baraja_insertar(&partida->mazo, carta.numero, carta.color, carta.tipo);
		}
	}
	
	partida->turno = 0;
	partida->sentido = 'v';
	partida->ganador = -1;
	partida->saltar_turno = 0;
	partida->robar = 0;
}

void partida_efecto_especial(tPartida *partida, tCarta carta){
	switch(carta.tipo){
		case 'S':
			partida->saltar_turno = 1;
			break;
		case 's':
			partida_cambio_sentido(partida);
			break;
		case 'r':
			partida->robar = 2;
			break;
		case 'R':
			partida->robar = 4;
			break;
	}
}

//0 Jugador | 1-N Bots
void partida_pasar_turno(tPartida *partida){
	switch(partida->sentido){
	case 'v':
		(partida->turno)++;
		if(partida->turno > partida->bots.n_jugadores){ partida->turno = 0; }
		break;
	case '^':
		(partida->turno)--;
		if(partida->turno < 0){ partida->turno = partida->bots.n_jugadores-1; }
		break;
	}
}

void partida_cambio_sentido(tPartida *partida){
	if(partida->sentido == 'v'){
		partida->sentido = '^';
	}else{
		partida->sentido = 'v';
	}
}

void partida_turno(tPartida *partida){
	tJugador *bot;
	
	partida_mostrar(*partida);
	if(partida->turno == 0){ //Jugador 
		partida_turno_humano(partida, &partida->jugador);
		if(partida->jugador.mano.n_cartas == 0){ partida->ganador = 0; }
	}else{ //Bots
		bot = jugadores_coger_jugador(&partida->bots, partida->turno-1);
		partida_turno_bot(partida, bot);
		if(bot->mano.n_cartas == 0){ partida->ganador = partida->turno; }
	}
	partida_limpiar_pantalla(1);
	
	partida_pasar_turno(partida);
}

void partida_limpiar_pantalla(int con_pausa){
	if(con_pausa == 1){ system("pause"); }
	system("cls");
}

void partida_mostrar_estadisticas_bots(tPartida partida){
	tJugador *bot;
	int posicion;
	int total_perdidas_agresivos = 0, total_ganadas_agresivos = 0;
	int total_perdidas_calmados = 0, total_ganadas_calmados = 0;
	float porcentaje_ganadas_agresivos = 0, porcentaje_perdidas_agresivos = 0;
	float porcentaje_ganadas_calmados = 0, porcentaje_perdidas_calmados = 0;
	float porcentaje_total_ganadas = 0, porcentaje_total_perdidas = 0;
	
	printf("UNO - Estadisticas de bots\n\n");
	printf("%-30s%-30s%-30s\n", "Nombre", "Ganadas", "Perdidas");
	for(posicion = 0; posicion < 90; posicion++){ printf("-"); }
	printf("\n");
	for(posicion = 0; posicion < partida.bots.n_jugadores; posicion++){
		bot = partida_coger_bot(&partida, posicion);
		printf("%-30s%-30d%-30d\n", bot->nombre, bot->ganadas, bot->perdidas);
		if(bot->tipo == 'C'){
			total_perdidas_calmados += bot->perdidas;
			total_ganadas_calmados += bot->ganadas;
		}else if(bot->tipo == 'A'){
			total_perdidas_agresivos += bot->perdidas;
			total_ganadas_agresivos += bot->ganadas;
		}
	}
	
	if(total_ganadas_agresivos > 0){ porcentaje_ganadas_agresivos = (float)(total_ganadas_agresivos) * 100.0 / (float)(total_ganadas_agresivos+total_perdidas_agresivos); }
	if(total_perdidas_agresivos > 0){ porcentaje_perdidas_agresivos = (float)(total_perdidas_agresivos) * 100.0 / (float)(total_ganadas_agresivos+total_perdidas_agresivos); }
	
	if(total_ganadas_calmados > 0){ porcentaje_ganadas_calmados = (float)(total_ganadas_calmados) * 100.0 / (float)(total_ganadas_calmados+total_perdidas_calmados); }
	if(total_perdidas_calmados > 0){ porcentaje_perdidas_calmados = (float)(total_perdidas_calmados) * 100.0 / (float)(total_ganadas_calmados+total_perdidas_calmados); }
	
	if(total_ganadas_calmados > 0 || total_ganadas_agresivos > 0){ porcentaje_total_ganadas = (float)(total_ganadas_calmados+total_ganadas_agresivos) * 100.0 / (float)(total_ganadas_calmados+total_perdidas_calmados+total_ganadas_agresivos+total_perdidas_agresivos); }
	if(total_perdidas_calmados > 0 || total_perdidas_agresivos > 0){ porcentaje_total_perdidas = (float)(total_perdidas_calmados+total_perdidas_agresivos) * 100.0 / (float)(total_ganadas_calmados+total_perdidas_calmados+total_ganadas_agresivos+total_perdidas_agresivos); }
	
	for(posicion = 0; posicion < 90; posicion++){ printf("-"); }
	printf("\n");
	
	printf("%-30s%-3d%-27.1f%-3d%-27.1f\n", "Agresivos", total_ganadas_agresivos, porcentaje_ganadas_agresivos, total_perdidas_agresivos, porcentaje_perdidas_agresivos);
	printf("%-30s%-3d%-27.1f%-3d%-7.1f\n", "Calmados", total_ganadas_calmados, porcentaje_ganadas_calmados, total_perdidas_calmados, porcentaje_perdidas_calmados);
	
	for(posicion = 0; posicion < 90; posicion++){ printf("-"); }
	printf("\n");
	
	printf("%-30s%-3d%-27.1f%-3d%-27.1f\n", "Total", total_ganadas_agresivos+total_ganadas_calmados, porcentaje_total_ganadas, total_perdidas_calmados+total_perdidas_agresivos, porcentaje_total_perdidas);
	
	for(posicion = 0; posicion < 90; posicion++){ printf("-"); }
	printf("\n");
}

void partida_mostrar_estadisticas_jugador(tPartida partida){
	int posicion;
	float porcentaje_ganadas = 0, porcentaje_perdidas = 0;
	
	if(partida.jugador.ganadas > 0 || partida.jugador.perdidas > 0){
		porcentaje_ganadas = (float)partida.jugador.ganadas * 100 / (float)(partida.jugador.ganadas+partida.jugador.perdidas);
	}
	if(partida.jugador.ganadas > 0 || partida.jugador.perdidas > 0){
		porcentaje_perdidas = (float)partida.jugador.perdidas * 100 / (float)(partida.jugador.ganadas+partida.jugador.perdidas);
	}
	
	printf("UNO - Estadisticas del jugador");
	printf("Nombre: %s\n", partida.jugador.nombre);
	printf("\n\nEstadisticas de partidas:\n");
	printf("Ganadas  : ");
	for(posicion = 0; posicion < 100; posicion+=10){
		if(posicion < porcentaje_ganadas){
			printf(".");
		}else{
			printf(" ");
		}
	}
	printf("%d (%.1f)\n", partida.jugador.ganadas, porcentaje_ganadas);
	printf("Perdidas : ");
	for(posicion = 0; posicion < 100; posicion+=10){
		if(posicion < porcentaje_perdidas){
			printf(".");
		}else{
			printf(" ");
		}
	}
	printf("%d (%.1f)\n", partida.jugador.perdidas, porcentaje_perdidas);
	printf("\n\n");
}

void partida_guardar_jugador(tJugador jugador, char nombre_fichero[MAXC]){
	FILE *fichero;
	
	fichero = fopen(nombre_fichero, "w");
	
	fprintf(fichero, "%s\n",jugador.nombre);
	fprintf(fichero, "%d\n", jugador.ganadas);
	fprintf(fichero, "%d\n", jugador.perdidas);
	fclose(fichero);
}

int partida_cargar_jugador(tPartida *partida, char nombre_fichero[MAXC]){
	FILE *fichero;
	int datos_validos = 0;
	
	fichero = fopen(nombre_fichero, "r");
	
	if(fichero != NULL){
		fscanf(fichero, "%[^\n]\n", partida->jugador.nombre);
		partida->jugador.tipo = 'H';
		fscanf(fichero, "%d\n", &partida->jugador.ganadas);
		fscanf(fichero, "%d\n", &partida->jugador.perdidas);
		fclose(fichero);
		
		partida->jugador.cartas_iniciales = CARTAS_INICIALES;
		
		datos_validos = 1;
	}else{
		printf("\n\n<< ERROR GRAVE. NO SE HA ENCONTRADO EL FICHERO DE DATOS DEL JUGADOR >>\n\n");
	}
	return datos_validos;
}

int partida_cargar_bots(tPartida *partida, char nombre_fichero[MAXC]){
	int n_bots = 0, posicion;
	int datos_validos = 0;
	
	char caracter[MAXC];
	char nombre[MAXC];
	int cartas_iniciales = 0;
	
	FILE *fichero;
	
	fichero = fopen(nombre_fichero, "r");
	
	if(fichero != NULL){
		fscanf(fichero, "%d\n", &n_bots);
		
		for(posicion = 0; posicion < n_bots; posicion++){
			fscanf(fichero, "%[^\n]\n", nombre);
			fscanf(fichero, "%[^\n]\n", caracter);
			fscanf(fichero, "%d\n", &cartas_iniciales);
			
			partida_nuevo_bot(&partida->bots, nombre, caracter[0], cartas_iniciales);
		}
		
		fclose(fichero);
		
		datos_validos = 1;
	}else{
		printf("\n\n<< ERROR GRAVE. NO SE HA ENCONTRADO EL FICHERO DE DATOS DE LOS BOTS >>\n\n");
	}
	return datos_validos;
}

void partida_mostrar_ganador(tPartida *partida){
	tJugador *bot;
	int posicion;
	if(partida->ganador == 0){
		printf("\n%s ha ganado la partida\n", partida->jugador.nombre);
		
		for(posicion = 0; posicion < partida->bots.n_jugadores; posicion++){
			bot = partida_coger_bot(partida, posicion);
			(bot->perdidas)++;
		}
		partida->jugador.ganadas++;
	}else{
		bot = partida_coger_bot(partida, partida->ganador-1);
		printf("\n%s ha ganado la partida\n", bot->nombre);
		printf("\nEn tu mano aun habia %d ", partida->jugador.mano.n_cartas);
		if(partida->jugador.mano.n_cartas != 1){
			printf("cartas\n");
		}else{
			printf("carta\n");
		}
		
		for(posicion = 0; posicion < partida->bots.n_jugadores; posicion++){
			bot = partida_coger_bot(partida, posicion);
			if(posicion != partida->ganador-1){
				(bot->perdidas)++;
			}else{
				(bot->ganadas)++;
			}
		}
		partida->jugador.perdidas++;
		
	}
}

void partida_mostrar(tPartida partida){
	int posicion;
	tJugador *bot;
	
	for(posicion = 0; posicion <= partida.bots.n_jugadores; posicion++){
		if(posicion == 0){
			jugador_mostrar(&partida.jugador);
			if(partida.turno == posicion){ printf("\t%c", partida.sentido); }
			printf("\n");
		}else{
			bot = jugadores_coger_jugador(&partida.bots, posicion-1);
			jugador_mostrar(bot);
			if(partida.turno-1 == posicion){ printf("\t%c", partida.sentido); }
			printf("\n");
		}
	}
	printf("\n");
	if(partida.descartes.n_cartas == 0){
		printf("  ### Lanza una carta sobre la mesa ###\n");
	}else{
		printf("   ### ");
		carta_mostrar(partida.descartes.ultima->carta);
		printf(" ###\n");
	}
	printf("\n");
}

void partida_asignar_jugador(tPartida *partida, char nombre[MAXC], char tipo, int ganadas, int perdidas){
	strcpy(partida->jugador.nombre, nombre);
	partida->jugador.tipo = tipo;
	partida->jugador.ganadas = ganadas;
	partida->jugador.perdidas = perdidas;
}

void partida_nuevo_bot(tListaJugadores *bots, char nombre[MAXC], char tipo, int n_cartas){
	jugadores_insertar(bots, nombre, tipo, n_cartas);
}

#endif
