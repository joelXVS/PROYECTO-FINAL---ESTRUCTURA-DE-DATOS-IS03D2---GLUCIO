#include <stdio.h>
#include <stdlib.h>
#include "pasajeros.h"

ColaPasajeros* crear_cola() {
    ColaPasajeros* nueva = (ColaPasajeros*)malloc(sizeof(ColaPasajeros));
    nueva->frente = NULL;
    nueva->fin = NULL;
    nueva->cantidad = 0;
    return nueva;
}

int cola_vacia(ColaPasajeros* cola) {
    return cola->frente == NULL;
}

void registrar_pasajero(ColaPasajeros* cola, int num_doc, int tipo_doc) {
    Pasajero* nuevo = (Pasajero*)malloc(sizeof(Pasajero));
    nuevo->num_documento = num_doc;
    nuevo->tipo_documento = tipo_doc;
    nuevo->estado = EN_ESPERA;
    nuevo->siguiente = NULL;

    if (cola_vacia(cola)) {
        cola->frente = nuevo;
        cola->fin = nuevo;
    } else {
        cola->fin->siguiente = nuevo;
        cola->fin = nuevo;
    }
    cola->cantidad++;
}

Pasajero* consultar_primero(ColaPasajeros* cola) {
    if (cola_vacia(cola)) return NULL;
    return cola->frente;
}

Pasajero* desembarcar_pasajero(ColaPasajeros* cola) {
    if (cola_vacia(cola)) return NULL;
    Pasajero* aux = cola->frente;
    cola->frente = aux->siguiente;
    if (cola->frente == NULL) cola->fin = NULL;
    cola->cantidad--;
    aux->siguiente = NULL;
    return aux;
}

void mostrar_pasajeros_cola(ColaPasajeros* cola) {
    Pasajero* aux = cola->frente;
    if (!aux) { printf("  No hay pasajeros en espera.\n"); return; }
    while (aux) {
        printf("  Doc: %d | Tipo: %d | Estado: %s\n", 
               aux->num_documento, aux->tipo_documento, 
               aux->estado == EN_ESPERA ? "En espera" : "Embarcado");
        aux = aux->siguiente;
    }
}

int contar_pasajeros_espera(ColaPasajeros* cola) {
    return cola->cantidad;
}

Pasajero* buscar_pasajero_en_cola(ColaPasajeros* cola, int num_doc) {
    Pasajero* aux = cola->frente;
    while (aux) {
        if (aux->num_documento == num_doc) return aux;
        aux = aux->siguiente;
    }
    return NULL;
}

void liberar_cola(ColaPasajeros* cola) {
    Pasajero* aux;
    while (cola->frente) {
        aux = cola->frente;
        cola->frente = aux->siguiente;
        free(aux);
    }
    free(cola);
}