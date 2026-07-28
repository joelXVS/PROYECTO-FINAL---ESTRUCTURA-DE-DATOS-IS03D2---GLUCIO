#ifndef DESTINOS_H
#define DESTINOS_H
#include "tipos.h"

Destino* crear_destino(int codigo, char* nombre, char* empresa);
Destino* buscar_destino(Destino* raiz, int codigo);
void agregar_destino(Destino** raiz, Destino* nuevo);
void mostrar_destinos(Destino* raiz);
void liberar_destinos(Destino* raiz);
int pasajero_existe_global(Destino* raiz, int num_doc);
void modificar_destino(Destino* destino, char* nuevo_nombre, char* nueva_empresa);

#endif