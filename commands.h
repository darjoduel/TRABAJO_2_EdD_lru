#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structures.h"
#include "function.h"
#include <string.h>

Cache_ *lru_create(int capacity)
{
    if (capacity < 5) {
        printf("La capacidad minima es 5\n");
        capacity = 5;
    }
    printf("Creando cache de capacidad %d\n", capacity);    

    Cache_ *cache = (Cache_ *)malloc(sizeof(Cache_));
    if (cache == NULL) {
        printf("Error al asignar memoria para el cache\n");
        return NULL;
    }

    cache->data = (char **)malloc(capacity * sizeof(char *));
    if (cache->data == NULL) {
        printf("Error al asignar memoria para los datos del cache\n");
        free(cache);
        return NULL;
    }

    cache->capacity = capacity;
    cache->size = 0;
    cache->head = NULL;

    create_folder();

    
    FILE *data = fopen("cache/data.txt", "w");
    fclose(data);

    update_cache(cache);
    printf("Cache creado con exito\n");
    return cache;
}

Cache_* lru_load_cache()
{
    Cache_ *cache = (Cache_ *)malloc(sizeof(Cache_));
    if (cache == NULL) {
        printf("Error al asignar memoria para el cache\n");
        return NULL;
    }

    cache->data = NULL;
    cache->capacity = 0;
    cache->size = 0;

    if (load_cachedata(cache) != 0) {
        free(cache);
        return NULL;
    }

    return cache;
}

int lru_add(Cache_ *cache, char *data)
{
    Node_ *TempNode = (Node_ *)malloc(sizeof(Node_));

    if(cache == NULL)
    {
        printf("Cache no inicializado. Use 'create <tamano_cache>' para crear uno.\n");
        return -1;
    }

    TempNode->data = strdup(data);
    TempNode->next = cache->head;
    cache->head = TempNode;

    if (cache->size < cache->capacity)
    {
        cache->size++;
        printf("Dato '%s' agregado al cache. Tamano actual: %d\n", data, cache->size);
    }
    else//hasta aqui bien
    {
        Node_ *current = cache->head;
        Node_ *prev = NULL;

        while(current->next != NULL) {
            prev = current;
            current = current->next;
        }

        if(prev != NULL) {
            prev->next = NULL;
            free(current->data);
            free(current);
        }
        printf("Cache lleno. Dato '%s' agregado al cache, el dato menos reciente fue eliminado.\n", data);
    }
//hasta aqui nose
    update_cache(cache);
    update_data(data);
//hasta aqui bien
    return 0;
}

int lru_all(Cache_ *cache)
{//funciona hasta all eso es lo que queda por ver
    if(cache == NULL)
    {
        printf("Cache no inicializado. Use 'create <tamano_cache>' para crear uno.\n");
        return -1;
    }

    printf("Contenido del cache (de mas reciente a menos reciente):\n");
    Node_ *reader = cache->head;
    while(reader != NULL)
    {
        printf("dentro del while\n");
        if (reader->data == NULL)
            printf("Dato nulo en este nodo!\n");
        else
            printf("Dato: '%s'\n", reader->data);

        if (reader->next == NULL)
            printf("Este era el último nodo.\n");
        else
            printf("Siguiente nodo existe.\n");

        reader = reader->next;

    }

    return 0;
}