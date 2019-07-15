#ifndef _MENU_H_
#define _MENU_H_

#include "partida.c"

void menu_jugar_ejecutar();
char menu_jugar_desplegar();
void menu_jugar_gestionar(char opcion);

void menu_ver_mano_ejecutar();
char menu_ver_mano_desplegar();
void menu_ver_mano_gestionar(char opcion);

void menu_principal_ejecutar(tPartida *partida);
char menu_principal_desplegar();
void menu_principal_gestionar(char opcion, tPartida *partida);


#endif
