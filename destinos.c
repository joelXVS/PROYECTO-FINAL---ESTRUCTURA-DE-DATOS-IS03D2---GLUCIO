#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "destinos.h"
#include "pasajeros.h"
#include "avl.h"

// Crea un nuevo destino con su cola y arbol de viajes vacios
Destino* crear_destino(int codigo, char* nombre, char* empresa) {
    Destino* nuevo = (Destino*)malloc(sizeof(Destino));
    nuevo->codigo = codigo;
    strncpy(nuevo->nombre, nombre, MAX_NOMBRE - 1);
    nuevo->nombre[MAX_NOMBRE - 1] = '\0';
    strncpy(nuevo->empresa, empresa, MAX_NOMBRE - 1);
    nuevo->empresa[MAX_NOMBRE - 1] = '\0';
    nuevo->cola = crear_cola();
    nuevo->raiz_viajes = NULL;
    nuevo->siguiente = NULL;
    return nuevo;
}

// Agrega un destino al final de la lista enlazada
void agregar_destino(Destino** raiz, Destino* nuevo) {
    if (*raiz == NULL) {
        *raiz = nuevo;
    } else {
        Destino* aux = *raiz;
        while (aux->siguiente != NULL)
            aux = aux->siguiente;
        aux->siguiente = nuevo;
    }
}

// Busca un destino por su codigo en la lista
Destino* buscar_destino(Destino* raiz, int codigo) {
    Destino* aux = raiz;
    while (aux) {
        if (aux->codigo == codigo)
            return aux;
        aux = aux->siguiente;
    }
    return NULL;
}

// Muestra todos los destinos con su cantidad de pasajeros en espera
void mostrar_destinos(Destino* raiz) {
    Destino* aux = raiz;
    if (!aux) {
        printf("No hay destinos registrados.\n");
        return;
    }
    while (aux) {
        printf("Codigo: %d | Nombre: %s | Empresa: %s | Pasajeros en espera: %d\n",
               aux->codigo, aux->nombre, aux->empresa, contar_pasajeros_espera(aux->cola));
        aux = aux->siguiente;
    }
}

// Verifica si un pasajero ya esta registrado en cualquier cola del sistema
int pasajero_existe_global(Destino* raiz, int num_doc) {
    Destino* aux = raiz;
    while (aux) {
        if (buscar_pasajero_en_cola(aux->cola, num_doc) != NULL)
            return 1;
        aux = aux->siguiente;
    }
    return 0;
}

// Modifica el nombre y/o la empresa de un destino existente
void modificar_destino(Destino* destino, char* nuevo_nombre, char* nueva_empresa) {
    if (nuevo_nombre && strlen(nuevo_nombre) > 0) {
        strncpy(destino->nombre, nuevo_nombre, MAX_NOMBRE - 1);
        destino->nombre[MAX_NOMBRE - 1] = '\0';
    }
    if (nueva_empresa && strlen(nueva_empresa) > 0) {
        strncpy(destino->empresa, nueva_empresa, MAX_NOMBRE - 1);
        destino->empresa[MAX_NOMBRE - 1] = '\0';
    }
}

// Libera toda la memoria: destinos, colas y arboles AVL
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