#include <stdio.h>
#include <stdlib.h>
#include "pasajeros.h"

// Crea una cola vacia
ColaPasajeros* crear_cola() {
    ColaPasajeros* nueva = (ColaPasajeros*)malloc(sizeof(ColaPasajeros));
    nueva->frente = NULL;
    nueva->fin = NULL;
    nueva->cantidad = 0;
    return nueva;
}

// Verifica si la cola esta vacia
int cola_vacia(ColaPasajeros* cola) {
    return cola->frente == NULL;
}

// Agrega un pasajero al final de la cola
void registrar_pasajero(ColaPasajeros* cola, int num_doc, int tipo_doc, char genero) {
    Pasajero* nuevo = (Pasajero*)malloc(sizeof(Pasajero));

    nuevo->num_documento = num_doc;
    nuevo->tipo_documento = tipo_doc;
    nuevo->genero = genero;
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

// Muestra el primer pasajero sin sacarlo de la cola
Pasajero* consultar_primero(ColaPasajeros* cola) {
    if (cola_vacia(cola))
        return NULL;

    return cola->frente;
}

// Saca al primer pasajero de la cola y lo devuelve
Pasajero* desembarcar_pasajero(ColaPasajeros* cola) {
    if (cola_vacia(cola))
        return NULL;

    Pasajero* aux = cola->frente;
    cola->frente = aux->siguiente;

    if (cola->frente == NULL)
        cola->fin = NULL;

    cola->cantidad--;
    aux->siguiente = NULL;

    return aux;
}

// Muestra todos los pasajeros registrados
void mostrar_pasajeros_cola(ColaPasajeros* cola) {

    Pasajero* aux = cola->frente;
    int hombres = 0;
    int mujeres = 0;

    if (aux == NULL) {
        printf("No hay pasajeros en espera para este destino.\n");
        return;
    }

    while (aux != NULL) {

        printf("Documento: %d | Tipo: %d | Genero: %s | Estado: %s\n",
               aux->num_documento,
               aux->tipo_documento,
               aux->genero == 'M' ? "Masculino" : "Femenino",
               aux->estado == EN_ESPERA ? "En espera" : "Embarcado");

        if (aux->genero == 'M')
            hombres++;
        else
            mujeres++;

        aux = aux->siguiente;
    }

    printf("\nResumen de pasajeros\n");
    printf("Hombres : %d\n", hombres);
    printf("Mujeres : %d\n", mujeres);
    printf("Total   : %d\n", hombres + mujeres);
}

// Retorna la cantidad de pasajeros en espera
int contar_pasajeros_espera(ColaPasajeros* cola) {
    return cola->cantidad;
}

// Busca un pasajero por documento
Pasajero* buscar_pasajero_en_cola(ColaPasajeros* cola, int num_doc) {

    Pasajero* aux = cola->frente;

    while (aux != NULL) {

        if (aux->num_documento == num_doc)
            return aux;

        aux = aux->siguiente;
    }

    return NULL;
}

// Libera toda la memoria de la cola
void liberar_cola(ColaPasajeros* cola) {

    Pasajero* aux;

    while (cola->frente != NULL) {
        aux = cola->frente;
        cola->frente = aux->siguiente;
        free(aux);
    }

    free(cola);
}