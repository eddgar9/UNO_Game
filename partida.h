#ifndef _PARTIDA_H_
#define _PARTIDA_H_

#include "listaJugadores.c"
#include "baraja.c"

typedef struct tPartida{
	tBaraja descartes;
	tBaraja mazo;
	tJugador jugador;
	tListaJugadores bots;
	int turno;
	char sentido;
	int robar;
	int ganador;
	int saltar_turno;
}tPartida;


void partida_guardar_jugador(tJugador jugador, char nombre_fichero[MAXC]);
void partida_mostrar_estadisticas_bots(tPartida partida);
void partida_mostrar_estadisticas_jugador(tPartida partida);
void partida_mostrar_ganador(tPartida *partida);
int partida_cargar_jugador(tPartida *partida, char nombre_fichero[MAXC]);
int partida_cargar_bots(tPartida *partida, char fichero[MAXC]);
void partida_reiniciar(tPartida *partida);
void partida_limpiar_pantalla(int con_pausa);
void partida_turno_humano(tPartida *partida, tJugador *jugador);
void partida_turno_bot(tPartida *partida, tJugador *bot);
void partida_crear(tPartida *partida);
void partida_mostrar(tPartida partida);
void partida_repartir_cartas(tPartida *partida);
void partida_descartar(tJugador *jugador, tBaraja *descartes);
void partida_cambiar_sentido(char *sentido);
void partida_pasar_turno(tPartida *partida);
void partida_barajar_mazo(tBaraja *mazo);
void partida_restaurar_mazo(tBaraja *mazo, tBaraja *descartes);
void partida_nuevo_bot(tListaJugadores *bots, char nombre[MAXC], char tipo, int n_cartas);
void partida_buscar_jugador(tListaJugadores *bots, int turno);
void partida_cargar(tListaJugadores *bots);
void partida_asignar_jugador(tPartida *partida, char nombre[MAXC], char tipo, int ganadas, int perdidas);
tJugador * partida_coger_bot(tPartida *partida, int posicion);
void partida_recargar_mazo(tPartida *partida);
void partida_cambio_sentido(tPartida *partida);
void partida_efecto_especial(tPartida *partida, tCarta carta);

#endif
