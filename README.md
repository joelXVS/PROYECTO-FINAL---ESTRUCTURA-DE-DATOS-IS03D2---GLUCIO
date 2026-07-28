# 🚢 Sistema de Gestión del Terminal Portuario Turístico de Buenaventura

Proyecto final desarrollado en **C** para la gestión dinámica de destinos, pasajeros y viajes programados en el Terminal Portuario Turístico de Buenaventura. El sistema integra estructuras de datos lineales y no lineales, haciendo uso intensivo de apuntadores y memoria dinámica.

## 📋 Descripción del Proyecto
El sistema permite administrar de forma dinámica **N destinos** (inicialmente La Bocana, Ladrilleros y Piangüita). Cada destino gestiona su propia **cola FIFO** de pasajeros en espera y un **Árbol Binario de Búsqueda Balanceado (AVL)** para sus viajes programados. 

### 🧠 Estructuras de Datos Implementadas
- **Lista Enlazada Simple:** Para la gestión dinámica de los destinos (sin límite fijo).
- **Colas FIFO (Enlazadas):** Para manejar el orden de llegada y embarque de los pasajeros por cada destino.
- **Árbol AVL:** Para almacenar y buscar eficientemente los viajes programados de cada destino, garantizando una complejidad de $O(\log n)$ mediante rotaciones de balanceo.

## 📂 Estructura del Repositorio
El proyecto sigue una arquitectura modular separando las declaraciones (`include`) de las implementaciones (`src`):

```text
text
PROYECTO-FINAL-ESTRUCTURA-DE-DATOS/
│
│ ├── tipos.h # Definición de structs y enums globales
│ ├── destinos.h # Prototipos para gestión de destinos
│ ├── pasajeros.h # Prototipos para operaciones de colas FIFO
│ └── avl.h # Prototipos para el árbol AVL y rotaciones│
│ ├── main.c # Menú principal y orquestación del sistema
│ ├── destinos.c # Lógica de creación y búsqueda de destinos
│ ├── pasajeros.c # Lógica de encolado, desencolado y búsqueda FIFO
│ └── avl.c # Lógica de inserción, búsqueda y rotaciones AVL
│
├── Makefile # Script de compilación automatizada
├── README.md # Documentación del proyecto
└── Informe_Tecnico.pdf # Documentación teórica y evidencias
```

## ⚙️ Prerrequisitos
Para compilar y ejecutar este proyecto, necesitas:
- **GCC** (GNU Compiler Collection) instalado en tu sistema.
- **Make** (para usar el Makefile).

*En sistemas basados en Linux (Ubuntu/Debian), puedes instalarlos con:*
```bash
sudo apt update
sudo apt install build-essential
```

## 🚀 Instrucciones de Compilación y Uso
1. Compilar el proyecto
Abre la terminal en la raíz del repositorio y ejecuta:

make clean  # Limpia compilaciones anteriores (opcional pero recomendado)
make        # Compila todos los archivos y genera el ejecutable

2. Ejecutar el programa
Una vez compilado, ejecuta el binario generado:
```bash
./terminal_portuario
```

3. Menú Principal
Al ejecutar el programa, interactuarás con el siguiente menú:
a. Registrar destino: Agrega un nuevo destino al sistema dinámicamente.
b. Registrar pasajero: Añade un pasajero a la cola FIFO de un destino específico (valida documentos y evita duplicados).
c. Mostrar pasajeros por destino: Imprime la cola FIFO de un destino.
d. Registrar viaje programado: Inserta un viaje en el árbol AVL del destino.
e. Buscar viaje: Busca un viaje específico en el AVL.
f. Mostrar árbol de viajes: Imprime gráficamente el AVL (con alturas y factores de balance).
g. Realizar embarque: Desencola al primer pasajero FIFO y lo asigna a un viaje.
h.Consultar pasajero: Busca un pasajero por documento en todo el sistema.
i. Estadísticas y Reportes: Genera promedios, máximos y mínimos del sistema.
j. Salir: Libera toda la memoria dinámica y termina el programa.

## 🧹 Gestión de Memoria
El programa hace uso estricto de malloc para la creación de nodos y free para su liberación. Al seleccionar la opción de Salir, el sistema recorre todas las estructuras (destinos, colas y árboles) para liberar el 100% de la memoria asignada en el Heap, evitando fugas de memoria (Memory Leaks).

## 👥 Miembros del Grupo y Participación
Este proyecto fue desarrollado de manera colaborativa. A continuación, se detallan los autores y sus principales aportes (ver historial de commits para más detalles):

Nombre | Rol / GitHub | Aportes Principales
Joel [Tu Apellido] | @[TuUsuarioGitHub] | Implementación del AVL, rotaciones y menú principal.
[Nombre Compañero 2] | @[UsuarioGitHub2] | Implementación de colas FIFO y gestión de pasajeros.
[Nombre Compañero 3] | @[UsuarioGitHub3] | Gestión de destinos, estadísticas y documentación.

## 📄 Licencia
Proyecto académico desarrollado para la clase de Estructuras de Datos. Uso exclusivamente educativo.