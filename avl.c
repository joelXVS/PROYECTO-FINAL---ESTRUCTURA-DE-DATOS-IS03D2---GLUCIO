#include <stdio.h>
#include <stdlib.h>
#include "include/avl.h"

NodoAVL* crear_nodo_avl(int codigo, int capacidad) {
    NodoAVL* nuevo = (NodoAVL*)malloc(sizeof(NodoAVL));
    nuevo->codigo_viaje = codigo;
    nuevo->capacidad_maxima = capacidad;
    nuevo->pasajeros_abordados = 0;
    nuevo->altura = 1;
    nuevo->izquierda = NULL;
    nuevo->derecha = NULL;
    return nuevo;
}

int obtener_altura(NodoAVL* n) { return n ? n->altura : 0; }
int max(int a, int b) { return (a > b) ? a : b; }

int obtener_balance(NodoAVL* n) { 
    return n ? obtener_altura(n->izquierda) - obtener_altura(n->derecha) : 0; 
}

NodoAVL* rotar_derecha(NodoAVL* y) {
    NodoAVL* x = y->izquierda;
    NodoAVL* T2 = x->derecha;
    x->derecha = y;
    y->izquierda = T2;
    y->altura = max(obtener_altura(y->izquierda), obtener_altura(y->derecha)) + 1;
    x->altura = max(obtener_altura(x->izquierda), obtener_altura(x->derecha)) + 1;
    return x;
}

NodoAVL* rotar_izquierda(NodoAVL* x) {
    NodoAVL* y = x->derecha;
    NodoAVL* T2 = y->izquierda;
    y->izquierda = x;
    x->derecha = T2;
    x->altura = max(obtener_altura(x->izquierda), obtener_altura(x->derecha)) + 1;
    y->altura = max(obtener_altura(y->izquierda), obtener_altura(y->derecha)) + 1;
    return y;
}

NodoAVL* insertar_avl(NodoAVL* nodo, int codigo, int capacidad) {
    if (nodo == NULL) return crear_nodo_avl(codigo, capacidad);

    if (codigo < nodo->codigo_viaje)
        nodo->izquierda = insertar_avl(nodo->izquierda, codigo, capacidad);
    else if (codigo > nodo->codigo_viaje)
        nodo->derecha = insertar_avl(nodo->derecha, codigo, capacidad);
    else return nodo; // Códigos duplicados no permitidos

    nodo->altura = 1 + max(obtener_altura(nodo->izquierda), obtener_altura(nodo->derecha));
    int balance = obtener_balance(nodo);

    // Casos de balanceo AVL
    if (balance > 1 && codigo < nodo->izquierda->codigo_viaje)
        return rotar_derecha(nodo);
    if (balance < -1 && codigo > nodo->derecha->codigo_viaje)
        return rotar_izquierda(nodo);
    if (balance > 1 && codigo > nodo->izquierda->codigo_viaje) {
        nodo->izquierda = rotar_izquierda(nodo->izquierda);
        return rotar_derecha(nodo);
    }
    if (balance < -1 && codigo < nodo->derecha->codigo_viaje) {
        nodo->derecha = rotar_derecha(nodo->derecha);
        return rotar_izquierda(nodo);
    }
    return nodo;
}

NodoAVL* buscar_avl(NodoAVL* raiz, int codigo) {
    if (raiz == NULL || raiz->codigo_viaje == codigo) return raiz;
    if (codigo < raiz->codigo_viaje) return buscar_avl(raiz->izquierda, codigo);
    return buscar_avl(raiz->derecha, codigo);
}

void mostrar_avl(NodoAVL* raiz, int nivel) {
    if (raiz == NULL) return;
    mostrar_avl(raiz->derecha, nivel + 1);
    for (int i = 0; i < nivel; i++) printf("    ");
    printf("%d (Alt: %d, Bal: %d)\n", raiz->codigo_viaje, raiz->altura, obtener_balance(raiz));
    mostrar_avl(raiz->izquierda, nivel + 1);
}

void liberar_avl(NodoAVL* raiz) {
    if (raiz == NULL) return;
    liberar_avl(raiz->izquierda);
    liberar_avl(raiz->derecha);
    free(raiz);
}