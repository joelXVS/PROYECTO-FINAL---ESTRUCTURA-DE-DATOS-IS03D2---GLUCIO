#ifndef AVL_H
#define AVL_H
#include "tipos.h"

NodoAVL* crear_nodo_avl(int codigo, int capacidad);
int obtener_altura(NodoAVL* n);
int max(int a, int b);
int obtener_balance(NodoAVL* n);
NodoAVL* rotar_derecha(NodoAVL* y);
NodoAVL* rotar_izquierda(NodoAVL* x);
NodoAVL* insertar_avl(NodoAVL* nodo, int codigo, int capacidad);
NodoAVL* buscar_avl(NodoAVL* raiz, int codigo);
void mostrar_avl(NodoAVL* raiz, int nivel);
void liberar_avl(NodoAVL* raiz);

#endif