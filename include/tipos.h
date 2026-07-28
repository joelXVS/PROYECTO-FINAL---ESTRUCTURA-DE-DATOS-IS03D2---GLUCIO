#ifndef TIPOS_H
#define TIPOS_H

#define MAX_NOMBRE 50
#define TRUE 1
#define FALSE 0

// Tipos de documento
enum TipoDoc { CEDULA = 1, PASAPORTE, TARJETA_ID };
// Estado pasajero
enum Estado { EN_ESPERA = 0, EMBARCADO };

// Estructura Pasajero (Nodo FIFO)
typedef struct Pasajero {
    int num_documento;
    int tipo_documento;
    int estado;
    struct Pasajero* siguiente;
} Pasajero;

// Estructura Cola FIFO
typedef struct ColaPasajeros {
    Pasajero* frente;
    Pasajero* fin;
    int cantidad;
} ColaPasajeros;

// Estructura Nodo AVL (Viajes)
typedef struct NodoAVL {
    int codigo_viaje;
    int capacidad_maxima;
    int pasajeros_abordados;
    int altura;
    struct NodoAVL* izquierda;
    struct NodoAVL* derecha;
} NodoAVL;

// Estructura Destino (Nodo Lista Enlazada)
typedef struct Destino {
    int codigo;
    char nombre[MAX_NOMBRE];
    char empresa[MAX_NOMBRE];
    ColaPasajeros* cola;
    NodoAVL* raiz_viajes;
    struct Destino* siguiente;
} Destino;

#endif