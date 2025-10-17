#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structures.h"
#include "function.h"
#include <string.h>

Cache_ *lru_create(int capacity) {

    if (capacity < 5) {
        printf("La capacidad minima es 5\n");
        capacity = 5;
    }
    printf("Creando cache de capacidad %d\n", capacity);    

    Cache_ *cache = (Cache_ *)malloc(sizeof(Cache_));//
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
    update_cachedata(cache);
    printf("Cache creado con exito\n");
    return cache;
}

int lru_add(Cache_ *cache, char *data) {

    Node_ *TempNode = (Node_ *)malloc(sizeof(Node_));

    if(cache == NULL || TempNode == NULL) {
        printf("Cache no inicializado. Use 'create <tamano_cache>' para crear uno.\n");
        return -1;
    }

    TempNode->data = strdup(data);
    TempNode->next = cache->head;
    cache->head = TempNode;
    cache->size++;
    
    /*if (cache->size < cache->capacity) {

        cache->size++;
        printf("Dato '%s' agregado al cache. Tamano actual: %d\n", data, cache->size);
    } else {
        free(cache->data[0]);
        for (int i = 1; i < cache->capacity; i++) {
            cache->data[i - 1] = cache->data[i];
        }
        cache->data[cache->capacity - 1] = strdup(data);
        printf("Cache lleno. Dato '%s' agregado, dato menos reciente eliminado.\n", data);
    }*/
    printf("Dato '%s' agregado al cache. Tamano actual: %d\n", data, cache->size);
    update_cachedata(cache);
    return 0;
}