#ifndef _CARTA_H_
#define _CARTA_H_

#define MAX_COLORES 4

typedef struct tCarta{
	char color; //
	char tipo;  //N - Normal | S - Saltar turno | s - Cambio sentido | r - Robar 2 | R - Comodin robar 4 | C - Comodin color 
	int numero;	//-1 - Comodin color
}tCarta;

char codigos_color[MAX_COLORES] = {'R', 'Y', 'G', 'B'};

void carta_crear(tCarta *carta, int numero, char color, char tipo);
void carta_mostrar(tCarta carta);

#endif
