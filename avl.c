#include <stdio.h>
#include <stdlib.h>
#include "include/avl.h"

// Crea un nodo para el árbol AVL con los datos del viaje
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

// Devuelve la altura de un nodo (0 si es NULL)
int obtener_altura(NodoAVL* n) {
    return n ? n->altura : 0;
}

// Máximo de dos enteros
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Calcula el factor de balance (altura izquierda - altura derecha)
int obtener_balance(NodoAVL* n) {
    return n ? obtener_altura(n->izquierda) - obtener_altura(n->derecha) : 0;
}

// Rotación simple a la derecha
NodoAVL* rotar_derecha(NodoAVL* y) {
    NodoAVL* x = y->izquierda;
    NodoAVL* T2 = x->derecha;

    x->derecha = y;
    y->izquierda = T2;

    // Actualizar alturas
    y->altura = max(obtener_altura(y->izquierda), obtener_altura(y->derecha)) + 1;
    x->altura = max(obtener_altura(x->izquierda), obtener_altura(x->derecha)) + 1;

    return x; // nueva raíz
}

// Rotación simple a la izquierda
NodoAVL* rotar_izquierda(NodoAVL* x) {
    NodoAVL* y = x->derecha;
    NodoAVL* T2 = y->izquierda;

    y->izquierda = x;
    x->derecha = T2;

    x->altura = max(obtener_altura(x->izquierda), obtener_altura(x->derecha)) + 1;
    y->altura = max(obtener_altura(y->izquierda), obtener_altura(y->derecha)) + 1;

    return y;
}

// Inserta un nuevo viaje en el AVL y lo balancea
NodoAVL* insertar_avl(NodoAVL* nodo, int codigo, int capacidad) {
    // Caso base: árbol vacío
    if (nodo == NULL)
        return crear_nodo_avl(codigo, capacidad);

    // Buscar la posición correcta (clave = código de viaje)
    if (codigo < nodo->codigo_viaje)
        nodo->izquierda = insertar_avl(nodo->izquierda, codigo, capacidad);
    else if (codigo > nodo->codigo_viaje)
        nodo->derecha = insertar_avl(nodo->derecha, codigo, capacidad);
    else
        return nodo; // Código duplicado, no se inserta

    // Actualizar altura del nodo actual
    nodo->altura = 1 + max(obtener_altura(nodo->izquierda), obtener_altura(nodo->derecha));

    // Verificar el balance y rotar si es necesario
    int balance = obtener_balance(nodo);

    // Caso izquierda-izquierda
    if (balance > 1 && codigo < nodo->izquierda->codigo_viaje)
        return rotar_derecha(nodo);

    // Caso derecha-derecha
    if (balance < -1 && codigo > nodo->derecha->codigo_viaje)
        return rotar_izquierda(nodo);

    // Caso izquierda-derecha
    if (balance > 1 && codigo > nodo->izquierda->codigo_viaje) {
        nodo->izquierda = rotar_izquierda(nodo->izquierda);
        return rotar_derecha(nodo);
    }

    // Caso derecha-izquierda
    if (balance < -1 && codigo < nodo->derecha->codigo_viaje) {
        nodo->derecha = rotar_derecha(nodo->derecha);
        return rotar_izquierda(nodo);
    }

    return nodo;
}

// Busca un viaje por su código en el AVL
NodoAVL* buscar_avl(NodoAVL* raiz, int codigo) {
    if (raiz == NULL || raiz->codigo_viaje == codigo)
        return raiz;
    if (codigo < raiz->codigo_viaje)
        return buscar_avl(raiz->izquierda, codigo);
    return buscar_avl(raiz->derecha, codigo);
}

// Muestra el árbol de forma horizontal (raíz a la derecha)
void mostrar_avl(NodoAVL* raiz, int nivel) {
    if (raiz == NULL)
        return;
    mostrar_avl(raiz->derecha, nivel + 1);
    for (int i = 0; i < nivel; i++)
        printf("    ");
    printf("%d (Alt: %d, Bal: %d)\n", raiz->codigo_viaje, raiz->altura, obtener_balance(raiz));
    mostrar_avl(raiz->izquierda, nivel + 1);
}

// Libera recursivamente toda la memoria del árbol
void liberar_avl(NodoAVL* raiz) {
    if (raiz == NULL)
        return;
    liberar_avl(raiz->izquierda);
    liberar_avl(raiz->derecha);
    free(raiz);
}

// Recorre el AVL para acumular total de viajes y pasajeros abordados
void estadisticas_avl(NodoAVL* raiz, int* total_viajes, int* total_pas_abordados) {
    if (raiz == NULL)
        return;

    (*total_viajes)++;
    (*total_pas_abordados) += raiz->pasajeros_abordados;

    estadisticas_avl(raiz->izquierda, total_viajes, total_pas_abordados);
    estadisticas_avl(raiz->derecha, total_viajes, total_pas_abordados);
}