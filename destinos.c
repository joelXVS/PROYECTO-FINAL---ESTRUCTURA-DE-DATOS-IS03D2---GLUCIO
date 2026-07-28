#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "destinos.h"
#include "pasajeros.h"

Destino* crear_destino(int codigo, char* nombre, char* empresa) {
    Destino* nuevo = (Destino*)malloc(sizeof(Destino));
    nuevo->codigo = codigo;
    strncpy(nuevo->nombre, nombre, MAX_NOMBRE);
    strncpy(nuevo->empresa, empresa, MAX_NOMBRE);
    nuevo->cola = crear_cola();
    nuevo->raiz_viajes = NULL;
    nuevo->siguiente = NULL;
    return nuevo;
}

void agregar_destino(Destino** raiz, Destino* nuevo) {
    if (*raiz == NULL) {
        *raiz = nuevo;
    } else {
        Destino* aux = *raiz;
        while (aux->siguiente != NULL) aux = aux->siguiente;
        aux->siguiente = nuevo;
    }
}

Destino* buscar_destino(Destino* raiz, int codigo) {
    Destino* aux = raiz;
    while (aux) {
        if (aux->codigo == codigo) return aux;
        aux = aux->siguiente;
    }
    return NULL;
}

void mostrar_destinos(Destino* raiz) {
    Destino* aux = raiz;
    if (!aux) { printf("No hay destinos registrados.\n"); return; }
    while (aux) {
        printf("Codigo: %d | Nombre: %s | Empresa: %s | Pasajeros en espera: %d\n",
               aux->codigo, aux->nombre, aux->empresa, contar_pasajeros_espera(aux->cola));
        aux = aux->siguiente;
    }
}

// Evitar registro duplicado global
int pasajero_existe_global(Destino* raiz, int num_doc) {
    Destino* aux = raiz;
    while (aux) {
        if (buscar_pasajero_en_cola(aux->cola, num_doc) != NULL) return 1;
        aux = aux->siguiente;
    }
    return 0;
}

void liberar_destinos(Destino* raiz) {
    Destino* aux;
    while (raiz) {
        aux = raiz;
        raiz = raiz->siguiente;
        liberar_cola(aux->cola);
        liberar_avl(aux->raiz_viajes);
        free(aux);
    }
}