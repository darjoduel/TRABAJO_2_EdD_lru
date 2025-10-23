# Simulación de Caché LRU (Least Recently Used) 💾

## Descripción del Proyecto

Este proyecto implementa un sistema de caché con **política de reemplazo LRU (Least Recently Used - Menos Usado Recientemente)** en lenguaje C. El sistema maneja un caché de tamaño limitado definido por el usuario (mínimo 5 elementos). Los datos, representados por letras mayúsculas, se almacenan y gestionan utilizando una **lista enlazada simple**.

Cuando se accede a un dato (`get`) o se añade (`add`), este se mueve al frente de la lista (mayor prioridad). Si se intenta añadir un dato y el caché está lleno, el elemento al final de la lista (el menos usado recientemente) es eliminado para hacer espacio. El estado del caché (metadatos y orden de los datos) se persiste en archivos dentro de una carpeta `cache/` para simular la carga y guardado entre ejecuciones.

Este proyecto fue desarrollado como parte de la **Tarea 2** para la asignatura **Estructuras de Datos**.

## Integrantes del Grupo 🧑‍💻

* Sebastian Carrasco
* Dario Duarte
* Christofer Gutierrez
* Franco Cartes (?)

---

## Compilación ⚙️

El proyecto utiliza `gcc` y un `Makefile` para la compilación. Para compilar, abre una terminal en la carpeta raíz del proyecto y ejecuta:

```bash
make
Esto generará el archivo ejecutable lru.exe (en Windows con MinGW) o lru (en Linux/macOS).

Para limpiar los archivos generados por la compilación (.exe, .o), puedes usar:

Bash

make clean
Uso del Programa ▶️
El programa se ejecuta desde la línea de comandos, pasando el comando y sus argumentos necesarios.

Formato: ./lru.exe [comando] [argumento] (o .\lru.exe en Windows CMD/PowerShell, ./lru en Linux/macOS)

Comandos Disponibles:

create <tamaño>: Inicializa el caché con la capacidad especificada. Requiere un tamaño mínimo de 5.

Ejemplo: ./lru.exe create 5

add <dato>: Añade un dato (letra mayúscula) al caché. Si está lleno, elimina el LRU. Si ya existe, no hace nada.

Ejemplo: ./lru.exe add A

get <dato>: Marca un dato como usado recientemente, moviéndolo al frente de la lista.

Ejemplo: ./lru.exe get B

search <dato>: Busca un dato en el caché e indica su posición (base 1) si se encuentra, o -1 si no.

Ejemplo: ./lru.exe search C

all: Muestra todos los datos en el caché, ordenados desde el más reciente al menos reciente.

Ejemplo: ./lru.exe all

exit: Elimina la carpeta cache/ con los archivos persistidos y termina el programa.

Ejemplo: ./lru.exe exit

help Muestra una ayuda simple con los comandos.

Ejemplo: ./lru.exe help

Ejemplo de Flujo:

Bash

# Crear caché de tamaño 5
./lru.exe create 5

# Añadir datos A, B, C
./lru.exe add A
./lru.exe add B
./lru.exe add C

# Ver contenido (C más reciente)
./lru.exe all
# Salida esperada: C - B - A

# Usar B (moverlo al frente)
./lru.exe get B

# Ver contenido (B más reciente)
./lru.exe all
# Salida esperada: B - C - A

# Buscar A (está en posición 3)
./lru.exe search A
# Salida esperada: Dato 'A' encontrado en la posicion: 3

# Añadir D, E, F (llenar y reemplazar A)
./lru.exe add D
./lru.exe add E
./lru.exe add F
# Salida esperada (al añadir F): Eliminando dato menos reciente: 'A'

# Ver contenido final
./lru.exe all
# Salida esperada: F - E - D - B - C

# Salir y limpiar
./lru.exe exit
Detalles de Implementación 🛠️
Lenguaje: C (estándar C99).

Estructura Principal: Lista enlazada simple (Node_) para mantener el orden LRU.

Persistencia: Se utiliza una carpeta cache/ con dos archivos:

cachedata.txt: Guarda la capacidad y tamaño actual del caché.

data.txt: Guarda los datos del caché en orden inverso (el último en el archivo es el más reciente en memoria).

Manejo de Comandos: Se procesan argumentos de línea de comandos (argc, argv) en main().