#ifndef TIPOS_H
#define TIPOS_H

#define MAX_NOMBRE 50
#define TRUE 1
#define FALSE 0

// Tipos de documento permitidos
enum TipoDoc { CEDULA = 1, PASAPORTE, TARJETA_ID };
enum Estado { EN_ESPERA = 0, EMBARCADO };

// Estructura del pasajero (nodo de la cola FIFO)
typedef struct Pasajero {
    int num_documento;
    int tipo_documento;
    char genero;          // M = Masculino, F = Femenino
    int estado;
    struct Pasajero* siguiente;
} Pasajero;

// Cola FIFO para los pasajeros en espera
typedef struct ColaPasajeros {
    Pasajero* frente;
    Pasajero* fin;
    int cantidad;
} ColaPasajeros;

// Nodo del arbol AVL (viajes programados)
typedef struct NodoAVL {
    int codigo_viaje;
    int capacidad_maxima;
    int pasajeros_abordados;
    int altura;
    struct NodoAVL* izquierda;
    struct NodoAVL* derecha;
} NodoAVL;

// Destino (nodo de la lista enlazada de destinos)
typedef struct Destino {
    int codigo;
    char nombre[MAX_NOMBRE];
    char empresa[MAX_NOMBRE];
    ColaPasajeros* cola;
    NodoAVL* raiz_viajes;
    struct Destino* siguiente;
} Destino;

#endif