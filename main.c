#include <stdio.h>
int opcion;
int main(){
    do{ 
        printf("bienvenido al sistema\n");
        printf("1.registrar destino\n");
        printf("2.registrar pasajero\n");
        printf("3.mostrar pasajeros por destino\n");
        printf("4. resgistrar viaje programado\n");
        printf("5. buscar viaje\n");
        printf("6. mostrar arbol de viajes\n");
        printf("7. realizar embarque\n");
        printf("8. consultar pasajero donde esta / embarcado -a donde\n");
        printf("9. salir\n");
        scanf("%d",&opcion);
        
        switch (opcion){
            case 1:
                printf("registro de destino\n");
                printf("a donde quieres ir\n");
                break;
            case 2:
                printf("registro de pasajero\n");
                printf("nombre\n");
                break;
            case 3:
                printf("mostrar pasajeros por destino\n");
                break;
            case 4:
                printf("registro de viaje programado\n");
                break;
            case 5:
                printf("buscar viaje\n");
                break;
            case 6:
                printf("mostrar arbol de viajes\n");
                break;
            case 7:
                printf("realizar embarque\n");
                break;
            case 8:
                printf("consulta pasajero donde esta\n");
                break;
        }

    }while (opcion !=9);

return 0;
} 