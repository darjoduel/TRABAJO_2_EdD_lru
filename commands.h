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
    if(cache == NULL)
    {
        printf("Cache no inicializado. Use 'create <tamano_cache>' para crear uno.\n");
        return -1;
    }
    
    Node_ *TempNode = (Node_ *)malloc(sizeof(Node_));
    if(TempNode == NULL)
    {
        printf("Error al asignar memoria para el nuevo nodo\n");
        return -1;
    }
    TempNode->data = strdup(data);
    TempNode->next = cache->head;
    cache->head = TempNode;

    if (cache->size < cache->capacity)
    {
        cache->size++;
        printf("Dato '%s' agregado al cache. Tamano actual: %d\n", data, cache->size);
        update_data(data);
    }
    else//aqui debe estar la funcion para reescribir el archivo data.txt
    {
        printf("Cache lleno. Reescribiendo data.txt...\n");
        Node_ *current = cache->head;
        Node_ *prev = NULL;

        if(cache->head == NULL) {
            printf("Error: el cache esta vacio, no se puede eliminar ningun dato\n");
            return -1;
        }
        
        while(current->next != NULL)
        {
            printf("avanzando en la lista\n");
            prev = current;
            current = current->next;
        }

        printf("Eliminando dato menos reciente: '%s'\n", current->data);

        if(prev != NULL)
        {
            prev->next = NULL;
            free(current->data);
            free(current);
        }

        rewrite_data(cache);
        printf("Cache lleno. Dato '%s' agregado al cache, el dato menos reciente fue eliminado.\n", data);
    }
//hasta aqui nose
    update_cache(cache);
//hasta aqui bien
    return 0;
}

int lru_all(Cache_ *cache)
{
    if(cache == NULL || cache->head == NULL)
    {
        printf("Cache vacio.\n");
        return -1;
    }

    Node_ *current = cache->head;
    int index = 1;

    while(current != NULL)
    {
        if(current->data == NULL)
        {
            printf("[%d] Dato NULL\n", index);
        }
        else
        {
            printf("[%d] %s\n", index, current->data);
        }

        current = current->next;
        index++;
    }

    return 0;
}