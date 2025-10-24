#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if !defined(_WIN32)
// Definición portable de strdup para Linux / Codespaces
char *strdup(const char *s) {
    if (!s) return NULL;
    size_t len = strlen(s) + 1;
    char *p = malloc(len);
    if (!p) {
        fprintf(stderr, "Error: malloc falló en strdup\n");
        exit(1);
    }
    memcpy(p, s, len);
    return p;
}
#endif

#include "commands.h"

#define help 168620
#define create 16485289
#define add 16128
#define search 17952822
#define all 16216
#define get 16754
#define exit 167494

int CharToInt(char *str);
int CharToNum(char *str);

int main(int argc, char *argv[])
{
    Cache_ *cache = NULL;
    // Verifica si hay suficientes argumentso
    if (argc < 3 && CharToInt(argv[1]) != help && CharToInt(argv[1]) != all && CharToInt(argv[1]) != exit){
        printf("No hay argumentos\nIntente:[--help]\n");
        return 0;
    }
    switch (CharToInt(argv[1]))
    {
    // Comandos
    case help:
        printf("'create <tamano_cache>' para crear una estructuras de 5 espacios minimo\n");
        printf("'add <nombre_dato>' para agregar un dato dentro del cache\n");
        printf("'get <nombre_dato>' para usar dicho dato dentro del cache\n");
        printf("'search' <nombre_dato> para verificar la existencia de un dato\n");
        printf("'all' para ver el contenido del cache segun su prioridad\n");
        printf("'exit' para eliminar el cache y terminar\n");
        break;
    // Comando de creación de cache
    case create:
        cache = lru_create(CharToNum(argv[2]));
        break;
    // Comando de agregar un dato al cache
    case add:
        cache = lru_load_cache(cache);
        //Verifica si el cache se cargo correctamente
        if(!cache) {
            printf("Error al cargar el cache. Asegurese de crear uno primero.\n");
            return -1;
        }
        load_data(cache);
        lru_add(cache, argv[2]);
        break;
    // Comando de búsqueda de un dato en el cache
    case search:
        cache= lru_load_cache(cache);
        if(!cache)
        {
            printf("Error al cargar el cache. Asegurese de crear uno primero.\n");
            return -1;
        }
        load_data(cache);
        lru_search(cache, argv[2]);
        break;
    // Comando para mostrar todos los datos en el cache
    case all:
        cache= lru_load_cache(cache);
        if(!cache) {
            printf("Error al cargar el cache. Asegurese de crear uno primero.\n");
            return -1;
        }
        load_data(cache);
        lru_all(cache);
        break;
    // Comando para obtener un dato del cache
    case get:
        cache= lru_load_cache(cache);
        if(!cache)
        {
            printf("Error al cargar el cache. Asegurese de crear uno primero.\n");
            return -1;
        }
        load_data(cache);
        lru_get(cache, argv[2]);
        break;
    // Comando para salir y eliminar el cache
    case exit:
        lru_exit();
        break;
    default:
        break;
    }

    return 0;
}

//transforma un string en un numero
int CharToNum(char *str)
{
    return atoi(str);
}

//transforma un string en un entero
int CharToInt(char *str)
{
    int result=0;
    
    while(*str)
    {
        result = result * 10 + (*str + '0');
        str++;
    }

    return result;
}
