#ifndef PASAJEROS_H
#define PASAJEROS_H
#include "tipos.h"

ColaPasajeros* crear_cola();
int cola_vacia(ColaPasajeros* cola);
void registrar_pasajero(ColaPasajeros* cola, int num_doc, int tipo_doc);
Pasajero* consultar_primero(ColaPasajeros* cola);
Pasajero* desembarcar_pasajero(ColaPasajeros* cola);
void mostrar_pasajeros_cola(ColaPasajeros* cola);
int contar_pasajeros_espera(ColaPasajeros* cola);
Pasajero* buscar_pasajero_en_cola(ColaPasajeros* cola, int num_doc);
void liberar_cola(ColaPasajeros* cola);

#endif