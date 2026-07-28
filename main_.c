#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tipos.h"
#include "destinos.h"
#include "pasajeros.h"
#include "avl.h"

// -------------------------------------------------------------
//  Función para embarcar al primer pasajero de la cola
// -------------------------------------------------------------
void realizar_embarque(Destino* raiz_destinos) {
    int cod_dest, cod_viaje;
    printf("Ingrese el código del destino: ");
    scanf("%d", &cod_dest);

    Destino* d = buscar_destino(raiz_destinos, cod_dest);
    if (!d) {
        printf("No se encontró ese destino.\n");
        return;
    }

    if (cola_vacia(d->cola)) {
        printf("No hay pasajeros en espera para este destino.\n");
        return;
    }

    printf("Ingrese el código del viaje: ");
    scanf("%d", &cod_viaje);

    NodoAVL* viaje = buscar_avl(d->raiz_viajes, cod_viaje);
    if (!viaje) {
        printf("Ese viaje no está registrado.\n");
        return;
    }

    if (viaje->pasajeros_abordados >= viaje->capacidad_maxima) {
        printf("El viaje ya está lleno.\n");
        return;
    }

    // Sacar al primer pasajero de la cola
    Pasajero* p = desembarcar_pasajero(d->cola);
    p->estado = EMBARCADO;
    viaje->pasajeros_abordados++;

    printf("Pasajero con documento %d ha sido embarcado en el viaje %d.\n",
           p->num_documento, cod_viaje);

    // Aquí se podría guardar en una lista histórica, pero para este ejercicio
    // simplemente liberamos el nodo del pasajero (ya no está en cola)
    free(p);
}

// -------------------------------------------------------------
//  Consulta global de un pasajero por documento
// -------------------------------------------------------------
void consultar_pasajero_global(Destino* raiz) {
    int doc;
    printf("Ingrese el número de documento: ");
    scanf("%d", &doc);

    Destino* aux = raiz;
    while (aux) {
        Pasajero* p = buscar_pasajero_en_cola(aux->cola, doc);
        if (p) {
            printf("El pasajero está en el destino '%s' con estado: %s\n",
                   aux->nombre,
                   p->estado == EN_ESPERA ? "En espera" : "Embarcado");
            return;
        }
        aux = aux->siguiente;
    }
    printf("No se encontró ningún pasajero con ese documento en el sistema.\n");
}

// -------------------------------------------------------------
//  Estadísticas generales del sistema
// -------------------------------------------------------------
void mostrar_estadisticas(Destino* raiz) {
    int total_dest = 0;
    int total_pas_espera = 0;
    int max_espera = -1;
    int min_espera = 99999;
    int total_viajes = 0;
    int total_pas_abordados = 0;

    if (!raiz) {
        printf("\n--- Estadísticas ---\n");
        printf("No hay destinos registrados.\n");
        printf("--------------------\n");
        return;
    }

    Destino* aux = raiz;
    while (aux) {
        int espera = contar_pasajeros_espera(aux->cola);
        total_pas_espera += espera;
        total_dest++;

        if (espera > max_espera) max_espera = espera;
        if (espera < min_espera) min_espera = espera;

        // Sumar viajes y pasajeros embarcados desde el AVL de este destino
        estadisticas_avl(aux->raiz_viajes, &total_viajes, &total_pas_abordados);

        aux = aux->siguiente;
    }

    int total_pas_registrados = total_pas_espera + total_pas_abordados;

    printf("\n========================================\n");
    printf("          Reporte Estadístico           \n");
    printf("========================================\n");
    printf("1. Promedio de pasajeros en espera por destino: %.2f\n",
           (float)total_pas_espera / total_dest);

    if (total_viajes > 0) {
        printf("2. Promedio de pasajeros embarcados por viaje : %.2f\n",
               (float)total_pas_abordados / total_viajes);
    } else {
        printf("2. Promedio de pasajeros embarcados por viaje : 0.00 (sin viajes)\n");
    }

    printf("3. Mayor cantidad de pasajeros en espera en un destino: %d\n", max_espera);
    printf("4. Menor cantidad de pasajeros en espera en un destino: %d\n", min_espera);
    printf("5. Total de pasajeros registrados en el sistema     : %d\n", total_pas_registrados);
    printf("6. Total de pasajeros ya embarcados                 : %d\n", total_pas_abordados);
    printf("========================================\n");
}

// -------------------------------------------------------------
//  Menú principal
// -------------------------------------------------------------
int main() {
    Destino* raiz_destinos = NULL;
    int opcion;

    do {
        printf("\n--- Terminal Portuario Turístico ---\n");
        printf("1.  Registrar destino\n");
        printf("2.  Registrar pasajero\n");
        printf("3.  Mostrar pasajeros por destino\n");
        printf("4.  Registrar viaje programado\n");
        printf("5.  Buscar viaje\n");
        printf("6.  Mostrar árbol de viajes\n");
        printf("7.  Realizar embarque\n");
        printf("8.  Consultar pasajero (global)\n");
        printf("9.  Estadísticas\n");
        printf("10. Buscar destino\n");
        printf("11. Modificar destino\n");
        printf("0.  Salir\n");
        printf("Opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1: {
                int cod;
                char nom[50], emp[50];
                printf("Código del destino: ");
                scanf("%d", &cod);
                printf("Nombre del destino: ");
                scanf(" %[^\n]", nom);
                printf("Empresa que lo gestiona: ");
                scanf(" %[^\n]", emp);

                // Validar que no exista ya un destino con ese código
                if (buscar_destino(raiz_destinos, cod) != NULL) {
                    printf("Ya existe un destino con ese código.\n");
                } else {
                    agregar_destino(&raiz_destinos, crear_destino(cod, nom, emp));
                    printf("Destino registrado correctamente.\n");
                }
                break;
            }

            case 2: {
                int cod_d, doc, tipo;
                printf("Código del destino: ");
                scanf("%d", &cod_d);

                Destino* d = buscar_destino(raiz_destinos, cod_d);
                if (!d) {
                    printf("Ese destino no existe.\n");
                    break;
                }

                printf("Número de documento: ");
                scanf("%d", &doc);

                if (pasajero_existe_global(raiz_destinos, doc)) {
                    printf("Ese pasajero ya está registrado en el sistema.\n");
                    break;
                }

                printf("Tipo de documento (1: Cédula, 2: Pasaporte, 3: Tarjeta de Identidad): ");
                scanf("%d", &tipo);

                if (tipo < 1 || tipo > 3) {
                    printf("Tipo de documento no válido.\n");
                    break;
                }

                registrar_pasajero(d->cola, doc, tipo);
                printf("Pasajero registrado en la cola del destino '%s'.\n", d->nombre);
                break;
            }

            case 3: {
                int cod;
                printf("Código del destino: ");
                scanf("%d", &cod);

                Destino* d = buscar_destino(raiz_destinos, cod);
                if (d) {
                    printf("Pasajeros en espera para '%s':\n", d->nombre);
                    mostrar_pasajeros_cola(d->cola);
                } else {
                    printf("Destino no encontrado.\n");
                }
                break;
            }

            case 4: {
                int cod_d, cod_v, cap;
                printf("Código del destino: ");
                scanf("%d", &cod_d);

                Destino* d = buscar_destino(raiz_destinos, cod_d);
                if (!d) {
                    printf("Destino no existe.\n");
                    break;
                }

                printf("Código del viaje: ");
                scanf("%d", &cod_v);
                printf("Capacidad máxima: ");
                scanf("%d", &cap);

                d->raiz_viajes = insertar_avl(d->raiz_viajes, cod_v, cap);
                printf("Viaje registrado y árbol balanceado (AVL).\n");
                break;
            }

            case 5: {
                int cod_d, cod_v;
                printf("Código del destino: ");
                scanf("%d", &cod_d);

                Destino* d = buscar_destino(raiz_destinos, cod_d);
                if (!d) {
                    printf("Destino no existe.\n");
                    break;
                }

                printf("Código del viaje: ");
                scanf("%d", &cod_v);

                NodoAVL* v = buscar_avl(d->raiz_viajes, cod_v);
                if (v) {
                    printf("Viaje %d | Capacidad: %d | Abordados: %d\n",
                           v->codigo_viaje, v->capacidad_maxima, v->pasajeros_abordados);
                } else {
                    printf("Viaje no encontrado.\n");
                }
                break;
            }

            case 6: {
                int cod;
                printf("Código del destino: ");
                scanf("%d", &cod);

                Destino* d = buscar_destino(raiz_destinos, cod);
                if (d) {
                    printf("Árbol AVL de viajes (vista horizontal):\n");
                    mostrar_avl(d->raiz_viajes, 0);
                } else {
                    printf("Destino no existe.\n");
                }
                break;
            }

            case 7:
                realizar_embarque(raiz_destinos);
                break;

            case 8:
                consultar_pasajero_global(raiz_destinos);
                break;

            case 9:
                mostrar_estadisticas(raiz_destinos);
                break;

            case 10: {
                int cod;
                printf("Ingrese el código del destino a buscar: ");
                scanf("%d", &cod);

                Destino* d = buscar_destino(raiz_destinos, cod);
                if (d) {
                    printf("Destino encontrado:\n");
                    printf("  Código       : %d\n", d->codigo);
                    printf("  Nombre       : %s\n", d->nombre);
                    printf("  Empresa      : %s\n", d->empresa);
                    printf("  Pasajeros en espera: %d\n", contar_pasajeros_espera(d->cola));
                } else {
                    printf("No hay ningún destino con ese código.\n");
                }
                break;
            }

            case 11: {
                int cod;
                char nom[50], emp[50];

                printf("Ingrese el código del destino a modificar: ");
                scanf("%d", &cod);

                Destino* d = buscar_destino(raiz_destinos, cod);
                if (!d) {
                    printf("Destino no existe.\n");
                    break;
                }

                printf("Nuevo nombre (deje vacío y presione Enter para no cambiarlo): ");
                scanf(" %[^\n]", nom);
                printf("Nueva empresa (deje vacío y presione Enter para no cambiarla): ");
                scanf(" %[^\n]", emp);

                modificar_destino(d, nom, emp);
                printf("Datos del destino actualizados.\n");
                break;
            }

            case 0:
                printf("Saliendo del sistema... Liberando memoria.\n");
                break;

            default:
                printf("Opción inválida. Intente de nuevo.\n");
        }
    } while (opcion != 0);

    liberar_destinos(raiz_destinos);
    return 0;
}