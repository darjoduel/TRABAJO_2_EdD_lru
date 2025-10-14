#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structures.h"
#include "function.h"
#include <string.h>

int lru_create(Cache_ *cache, int capacity) {
    if (capacity < 5) {
        printf("La capacidad minima es 5\n");
        capacity = 5;
    }
    printf("Creando cache de capacidad %d\n", capacity);
    cache = (Cache_ *)malloc(sizeof(Cache_));
    if (cache == NULL) {
        printf("Error al asignar memoria para el cache\n");
        return -1;
    }
    cache->head = NULL;
    cache->tail = NULL;
    cache->size = 0;
    cache->capacity = capacity;
    create_folder();
    update_cachedata(cache);

    printf("Cache creado con exito\n");

    return 0;
}

int lru_add(Cache_ *cache, char *data) {

    load_cachedata(cache);
    
    if (cache == NULL) {
        printf("El cache no ha sido creado. Use 'create <tamano_cache>' para crearlo.\n");
        return -1;
    }
    Node_ *new_node = (Node_ *)malloc(sizeof(Node_));
    if (new_node == NULL) {
        printf("Error al asignar memoria para el nuevo nodo\n");
        return -1;
    }
    new_node->data = strdup(data);
    new_node->next = cache->head;
    new_node->prev = NULL;

    if (cache->head != NULL) {
        cache->head->prev = new_node;
    }
    cache->head = new_node;

    if (cache->tail == NULL) {
        cache->tail = new_node;
    }

    cache->size++;
    if (cache->size > cache->capacity) {
        Node_ *temp = cache->tail;
        cache->tail = cache->tail->prev;
        if (cache->tail != NULL) {
            cache->tail->next = NULL;
        }
        free(temp->data);
        free(temp);
        //cache->size--;
    }
    update_cachedata(cache);
    printf("Datos cargados: Capacidad=%d, Tamano actual=%d\n", cache->capacity, cache->size);   
    printf("Dato '%s' agregado al cache.\n", data);
    return 0;
}

int lru_all(Cache_ *cache) {
    load_cachedata(cache);

    if (cache == NULL) {
        printf("El cache no ha sido creado. Use 'create <tamano_cache>' para crearlo.\n");
        return -1;
    }
    Node_ *current = cache->head;
    printf("Contenido del cache:\n");
    while (current != NULL) {
        printf("hola\n");
        printf("%s\n", current->data);
        current = current->next;
    }
    return 0;
}