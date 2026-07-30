#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tipos.h"
#include "destinos.h"
#include "pasajeros.h"
#include "avl.h"

// -------------------------------------------------------------
//  Entrada de datos segura
// -------------------------------------------------------------

// Lee un entero desde teclado. Si el usuario escribe algo que no es
// un numero, vuelve a pedirlo en vez de dejar el programa en un
// ciclo infinito (lo que pasaba antes con scanf("%d", ...) sin
// validar su valor de retorno).
int leer_entero(const char* mensaje) {
    char linea[100];
    int valor;

    while (1) {
        printf("%s", mensaje);
        if (fgets(linea, sizeof(linea), stdin) == NULL)
            continue;
        if (sscanf(linea, "%d", &valor) == 1)
            return valor;
        printf("Entrada invalida, debe ser un numero. Intente de nuevo.\n");
    }
}

// Lee una linea de texto de forma segura y le quita el salto de linea.
// Si el usuario solo presiona Enter, buffer queda como cadena vacia
// (""), en vez de contener basura sin inicializar como pasaba antes
// con scanf(" %[^\n]", ...) cuando la entrada estaba vacia.
void leer_linea(char* buffer, int tam) {
    if (fgets(buffer, tam, stdin) == NULL) {
        buffer[0] = '\0';
        return;
    }
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else {
        // La linea escrita era mas larga que el buffer: descartar el resto
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }
}

// -------------------------------------------------------------
//  Funcion para embarcar al primer pasajero de la cola
// -------------------------------------------------------------
void realizar_embarque(Destino* raiz_destinos) {
    int cod_dest = leer_entero("Ingrese el codigo del destino: ");

    Destino* d = buscar_destino(raiz_destinos, cod_dest);
    if (!d) {
        printf("No se encontro ese destino.\n");
        return;
    }

    if (cola_vacia(d->cola)) {
        printf("No hay pasajeros en espera para este destino.\n");
        return;
    }

    int cod_viaje = leer_entero("Ingrese el codigo del viaje: ");

    NodoAVL* viaje = buscar_avl(d->raiz_viajes, cod_viaje);
    if (!viaje) {
        printf("Ese viaje no esta registrado.\n");
        return;
    }

    if (viaje->pasajeros_abordados >= viaje->capacidad_maxima) {
        printf("El viaje ya esta lleno.\n");
        return;
    }

    // Sacar al primer pasajero de la cola
    Pasajero* p = desembarcar_pasajero(d->cola);
    p->estado = EMBARCADO;
    viaje->pasajeros_abordados++;

    printf("Pasajero con documento %d ha sido embarcado en el viaje %d.\n",
           p->num_documento, cod_viaje);

    // Aqui se podria guardar en una lista historica, pero para este ejercicio
    // simplemente liberamos el nodo del pasajero (ya no esta en cola)
    free(p);
}

// -------------------------------------------------------------
//  Consulta global de un pasajero por documento
// -------------------------------------------------------------
void consultar_pasajero_global(Destino* raiz) {
    int doc = leer_entero("Ingrese el numero de documento: ");

    Destino* aux = raiz;
    while (aux) {
        Pasajero* p = buscar_pasajero_en_cola(aux->cola, doc);
        if (p) {
            printf("El pasajero esta en el destino '%s' con estado: %s\n",
                   aux->nombre,
                   p->estado == EN_ESPERA ? "En espera" : "Embarcado");
            return;
        }
        aux = aux->siguiente;
    }
    printf("No se encontro ningun pasajero con ese documento en el sistema.\n");
}

// -------------------------------------------------------------
//  Estadisticas generales del sistema
// -------------------------------------------------------------
void mostrar_estadisticas(Destino* raiz) {
    int total_dest = 0;
    int total_pas_espera = 0;
    int max_espera = -1;
    int min_espera = 99999;
    int total_viajes = 0;
    int total_pas_abordados = 0;

    if (!raiz) {
        printf("\n--- Estadisticas ---\n");
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
    printf("          Reporte Estadistico           \n");
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
//  Menu principal
// -------------------------------------------------------------
int main() {
    Destino* raiz_destinos = NULL;
    int opcion;

    do {
        printf("\n--- Terminal Portuario Turistico ---\n");
        printf("1.  Registrar destino\n");
        printf("2.  Registrar pasajero\n");
        printf("3.  Mostrar pasajeros por destino\n");
        printf("4.  Registrar viaje programado\n");
        printf("5.  Buscar viaje\n");
        printf("6.  Mostrar arbol de viajes\n");
        printf("7.  Realizar embarque\n");
        printf("8.  Consultar pasajero (global)\n");
        printf("9.  Estadisticas\n");
        printf("10. Buscar destino\n");
        printf("11. Modificar destino\n");
        printf("0.  Salir\n");
        opcion = leer_entero("Opcion: ");

        switch (opcion) {
            case 1: {
                char nom[MAX_NOMBRE], emp[MAX_NOMBRE];
                int cod = leer_entero("Codigo del destino: ");
                printf("Nombre del destino: ");
                leer_linea(nom, sizeof(nom));
                printf("Empresa que lo gestiona: ");
                leer_linea(emp, sizeof(emp));

                // Validar que no exista ya un destino con ese codigo
                if (buscar_destino(raiz_destinos, cod) != NULL) {
                    printf("Ya existe un destino con ese codigo.\n");
                } else {
                    agregar_destino(&raiz_destinos, crear_destino(cod, nom, emp));
                    printf("Destino registrado correctamente.\n");
                }
                break;
            }

            case 2: {
                int cod_d = leer_entero("Codigo del destino: ");

                Destino* d = buscar_destino(raiz_destinos, cod_d);
                if (!d) {
                    printf("Ese destino no existe.\n");
                    break;
                }

                int doc = leer_entero("Numero de documento: ");

                if (pasajero_existe_global(raiz_destinos, doc)) {
                    printf("Ese pasajero ya esta registrado en el sistema.\n");
                    break;
                }

                int tipo = leer_entero("Tipo de documento (1: Cédula, 2: Pasaporte, 3: Tarjeta de Identidad): ");

                if (tipo < 1 || tipo > 3) {
                    printf("Tipo de documento no valido.\n");
                    break;
                }

                registrar_pasajero(d->cola, doc, tipo);
                printf("Pasajero registrado en la cola del destino '%s'.\n", d->nombre);
                break;
            }

            case 3: {
                int cod = leer_entero("Codigo del destino: ");

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
                int cod_d = leer_entero("Codigo del destino: ");

                Destino* d = buscar_destino(raiz_destinos, cod_d);
                if (!d) {
                    printf("Destino no existe.\n");
                    break;
                }

                int cod_v = leer_entero("Codigo del viaje: ");
                int cap = leer_entero("Capacidad maxima: ");

                if (cap <= 0) {
                    printf("La capacidad maxima debe ser mayor que 0.\n");
                    break;
                }

                d->raiz_viajes = insertar_avl(d->raiz_viajes, cod_v, cap);
                printf("Viaje registrado y arbol balanceado (AVL).\n");
                break;
            }

            case 5: {
                int cod_d = leer_entero("Codigo del destino: ");

                Destino* d = buscar_destino(raiz_destinos, cod_d);
                if (!d) {
                    printf("Destino no existe.\n");
                    break;
                }

                int cod_v = leer_entero("Codigo del viaje: ");

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
                int cod = leer_entero("Codigo del destino: ");

                Destino* d = buscar_destino(raiz_destinos, cod);
                if (d) {
                    printf("arbol AVL de viajes (vista horizontal):\n");
                    mostrar_avl(d->raiz_viajes, 0);
                } else {
                    printf("Destino no existe.\n");
                }
                break;
            }


            realizar_embarque(raiz_destinos);
                break;

            case 8:
                consultar_pasajero_global(raiz_destinos);
                break;

            case 9:
                mostrar_estadisticas(raiz_destinos);
                break;

            case 10: {
                int cod = leer_entero("Ingrese el codigo del destino a buscar: ");

                Destino* d = buscar_destino(raiz_destinos, cod);
                if (d) {
                    printf("Destino encontrado:\n");
                    printf("  Codigo       : %d\n", d->codigo);
                    printf("  Nombre       : %s\n", d->nombre);
                    printf("  Empresa      : %s\n", d->empresa);
                    printf("  Pasajeros en espera: %d\n", contar_pasajeros_espera(d->cola));
                } else {
                    printf("No hay ningun destino con ese codigo.\n");
                }
                break;
            }

            case 11: {
                char nom[MAX_NOMBRE], emp[MAX_NOMBRE];

                int cod = leer_entero("Ingrese el codigo del destino a modificar: ");

                Destino* d = buscar_destino(raiz_destinos, cod);
                if (!d) {
                    printf("Destino no existe.\n");
                    break;
                }

                printf("Nuevo nombre (deje vacio y presione Enter para no cambiarlo): ");
                leer_linea(nom, sizeof(nom));
                printf("Nueva empresa (deje vacio y presione Enter para no cambiarla): ");
                leer_linea(emp, sizeof(emp));

                modificar_destino(d, nom, emp);
                printf("Datos del destino actualizados.\n");
                break;
            }

            case 0:
                printf("Saliendo del sistema... Liberando memoria.\n");
                break;

            default:
                printf("Opcion invalida. Intente de nuevo.\n");
        }
    } while (opcion != 0);

    liberar_destinos(raiz_destinos);
    return 0;
}