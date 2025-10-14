#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    Cache_ cache;

    if (argc < 2) {
        printf("No hay argumentos\nIntente:[--help]\n");
        return 0;
    }
    switch (CharToInt(argv[1]))
    {
    case help:
        printf("'create <tamano_cache>' para crear una estructuras de 5 espacios minimo\n");
        printf("'add <nombre_dato>' para agregar un dato dentro del cache\n");
        printf("'get <nombre_dato>' para usar dicho dato dentro del cache\n");
        printf("'search' <nombre_dato> para verificar la existencia de un dato\n");
        printf("'all' para ver el contenido del cache segun su prioridad\n");
        printf("'exit' para eliminar el cache y terminar\n");
        break;
    case create:
        lru_create(&cache, CharToNum(argv[2]));
        break;
    case add:
        lru_add(&cache, argv[2]);
        break;
    case search:
        break;
    case all:
        lru_all(&cache);
        break;
    case get:
        break;
    case exit:
        break;
    default:
        break;
    }

    return 0;
}

int CharToNum(char *str)
{
    return atoi(str);
}

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
