#include <stdio.h>
#include <stdlib.h>
#include "tipos.h"
#include "destinos.h"
#include "pasajeros.h"
#include "avl.h"

// estadística y embarque
void realizar_embarque(Destino* raiz_destinos) {
    int cod_dest, cod_viaje;
    printf("Ingrese codigo del destino: "); scanf("%d", &cod_dest);
    Destino* d = buscar_destino(raiz_destinos, cod_dest);
    if (!d) { printf("Destino no encontrado.\n"); return; }
    if (cola_vacia(d->cola)) { printf("No hay pasajeros en espera.\n"); return; }

    printf("Ingrese codigo del viaje: "); scanf("%d", &cod_viaje);
    NodoAVL* viaje = buscar_avl(d->raiz_viajes, cod_viaje);
    if (!viaje) { printf("Viaje no encontrado.\n"); return; }
    if (viaje->pasajeros_abordados >= viaje->capacidad_maxima) {
        printf("Viaje lleno.\n"); return;
    }

    Pasajero* p = desembarcar_pasajero(d->cola);
    p->estado = EMBARCADO;
    viaje->pasajeros_abordados++;
    printf("Pasajero %d embarcado en viaje %d.\n", p->num_documento, cod_viaje);
    
    // Sacamos al pasajero embarcado del avl
    free(p); 
}

void consultar_pasajero_global(Destino* raiz) {
    int doc;
    printf("Ingrese numero de documento: "); scanf("%d", &doc);
    Destino* aux = raiz;
    while (aux) {
        Pasajero* p = buscar_pasajero_en_cola(aux->cola, doc);
        if (p) {
            printf("Pasajero encontrado en destino %s. Estado: %s\n", 
                   aux->nombre, p->estado == EN_ESPERA ? "En espera" : "Embarcado");
            return;
        }
        aux = aux->siguiente;
    }
    printf("Pasajero no encontrado en ninguna cola.\n");
}

void mostrar_estadisticas(Destino* raiz) {
    int total_dest = 0, total_pas_espera = 0, max_espera = -1, min_espera = 9999;
    int total_viajes = 0, total_pas_abordados = 0;
    Destino* aux = raiz;
    while (aux) {
        int espera = contar_pasajeros_espera(aux->cola);
        total_pas_espera += espera;
        total_dest++;
        if (espera > max_espera) max_espera = espera;
        if (espera < min_espera) min_espera = espera;

        aux = aux->siguiente;
    }
    printf("\n--- ESTADISTICAS ---\n");
    if(total_dest > 0) {
        printf("Promedio pasajeros en espera por destino: %.2f\n", (float)total_pas_espera / total_dest);
        printf("Destino con mayor espera: %d | Menor espera: %d\n", max_espera, min_espera);
    }
    printf("Total pasajeros registrados en colas: %d\n", total_pas_espera);
    printf("--------------------\n");
}

int main() {
    Destino* raiz_destinos = NULL;
    int opcion;

    do {
        printf("\n--- TERMINAL PORTUARIO TURISTICO ---\n");
        printf("1. Registrar destino\n2. Registrar pasajero\n3. Mostrar pasajeros por destino\n");
        printf("4. Registrar viaje programado\n5. Buscar viaje\n6. Mostrar arbol de viajes\n");
        printf("7. Realizar embarque\n8. Consultar pasajero\n9. Estadisticas\n0. Salir\n");
        printf("Opcion: "); scanf("%d", &opcion);

        switch (opcion) {
            case 1: {
                int cod; char nom[50], emp[50];
                printf("Codigo destino: "); scanf("%d", &cod);
                printf("Nombre destino: "); scanf("%s", nom);
                printf("Empresa: "); scanf("%s", emp);
                agregar_destino(&raiz_destinos, crear_destino(cod, nom, emp));
                break;
            }
            case 2: {
                int cod_d, doc, tipo;
                printf("Codigo destino: "); scanf("%d", &cod_d);
                Destino* d = buscar_destino(raiz_destinos, cod_d);
                if (!d) { printf("Destino no existe.\n"); break; }
                printf("Numero documento: "); scanf("%d", &doc);
                if (pasajero_existe_global(raiz_destinos, doc)) {
                    printf("Pasajero ya registrado en el sistema.\n"); break;
                }
                printf("Tipo (1:CC, 2:Pasaporte, 3:TI): "); scanf("%d", &tipo);
                if (tipo < 1 || tipo > 3) { printf("Tipo invalido.\n"); break; }
                registrar_pasajero(d->cola, doc, tipo);
                break;
            }
            case 3: {
                int cod;
                printf("Codigo destino: "); scanf("%d", &cod);
                Destino* d = buscar_destino(raiz_destinos, cod);
                if (d) mostrar_pasajeros_cola(d->cola);
                else printf("Destino no encontrado.\n");
                break;
            }
            case 4: {
                int cod_d, cod_v, cap;
                printf("Codigo destino: "); scanf("%d", &cod_d);
                Destino* d = buscar_destino(raiz_destinos, cod_d);
                if (!d) { printf("Destino no existe.\n"); break; }
                printf("Codigo viaje: "); scanf("%d", &cod_v);
                printf("Capacidad maxima: "); scanf("%d", &cap);
                d->raiz_viajes = insertar_avl(d->raiz_viajes, cod_v, cap);
                printf("Viaje registrado y arbol balanceado (AVL).\n");
                break;
            }
            case 5: {
                int cod_d, cod_v;
                printf("Codigo destino: "); scanf("%d", &cod_d);
                Destino* d = buscar_destino(raiz_destinos, cod_d);
                if (!d) break;
                printf("Codigo viaje: "); scanf("%d", &cod_v);
                NodoAVL* v = buscar_avl(d->raiz_viajes, cod_v);
                if (v) printf("Viaje %d | Cap: %d | Abordados: %d\n", v->codigo_viaje, v->capacidad_maxima, v->pasajeros_abordados);
                else printf("Viaje no encontrado.\n");
                break;
            }
            case 6: {
                int cod;
                printf("Codigo destino: "); scanf("%d", &cod);
                Destino* d = buscar_destino(raiz_destinos, cod);
                if (d) { printf("Arbol AVL de viajes (Invertido para visualizacion):\n"); mostrar_avl(d->raiz_viajes, 0); }
                break;
            }
            case 7: realizar_embarque(raiz_destinos); break;
            case 8: consultar_pasajero_global(raiz_destinos); break;
            case 9: mostrar_estadisticas(raiz_destinos); break;
            case 0: printf("Saliendo y liberando memoria...\n"); break;
            default: printf("Opcion invalida.\n");
        }
    } while (opcion != 0);

    liberar_destinos(raiz_destinos);
    return 0;
}

