#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdarg.h>
#include "structures.h"


int create_folder()//crear carpeta cache
{
    if(system("mkdir cache") != 0) {
        printf("Error al crear la carpeta 'files'\n");
        return -1;
    }
    return 0;
}

int load_cachedata(Cache_ *cache)//carga metadata.txt en la estructura Cache_
{
    if (cache == NULL) {
        printf("Error: cache es NULL\n");
        return -1;
    }

    FILE *cachedata = fopen("cache/cachedata.txt", "r");
    if (cachedata == NULL)
    {
        printf("Error al abrir el archivo metadata.txt\n");
        return -1;
    }
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), cachedata))
    {
        if (sscanf(buffer, "Capacidad: %d", &cache->capacity) == 1) {
            continue;
        }
        if (sscanf(buffer, "Tamano actual: %d", &cache->size) == 1) {
            continue;
        }
    }
    
    fclose(cachedata);
    return 0;
}

int update_cache(Cache_ *cache)//crea o actualiza el archivo metadata.txt
{
    FILE *cachedata = fopen("cache/cachedata.txt", "w");

    if(cache == NULL)
    {
        printf("Error: cache es NULL\n");
        return -1;
    }
    if (cachedata == NULL)
    {
        printf("Error al abrir el archivo metadata.txt\n");
        return -1;
    }
    fprintf(cachedata, "Capacidad: %d\n", cache->capacity);
    fprintf(cachedata, "Tamano actual: %d\n", cache->size);

    fclose(cachedata);
    return 0;
}

int rewrite_data(Cache_ *cache)//reescribe el archivo data.txt cuando el cache esta lleno
{
    printf("dentro de rewrite data\n");

    if(cache == NULL || cache->head == NULL)
    {
        printf("Error: cache es NULL\n");
        return -1;
    }

    FILE *data = fopen("cache/data.txt", "w");
    if (data == NULL)
    {
        printf("Error al abrir el archivo data.txt para reescribir\n");
        return -1;
    }

    int count = 0;
    Node_ *current = cache->head;
    while(current != NULL && count < cache->capacity)
    {
        count++;
        current = current->next;
    }

    Node_ *nodes[count];
    current = cache->head;
    for(int i = 0; i < count; i++)
    {
        nodes[i] = current;
        current = current->next;
    }

    for(int i = count - 1; i >= 0; i--)
    {
        if(nodes[i]->data != NULL)
        {
            fprintf(data, "%s\n", nodes[i]->data);
        }
    }
    fclose(data);
    printf("Archivo data.txt reescrito con exito\n");
    return 0;
}
// AQUI EMPEZO
int load_data(Cache_ *cache)
{
    if (!cache)
        return -1;

    FILE *data = fopen("cache/data.txt", "r");
    if (!data)
    {
        printf("No se pudo abrir data.txt\n");
        return -1;
    }

    char buffer[256];
    cache->head = NULL;
    cache->size = 0;

    while (fgets(buffer, sizeof(buffer), data) && cache->size < cache->capacity)
    {
        buffer[strcspn(buffer, "\n")] = 0; // Quita '\n'

        Node_ *new_node = malloc(sizeof(Node_));
        if (!new_node)
        {
            printf("Error al asignar memoria\n");
            fclose(data);
            return -1;
        }

        new_node->data = strdup(buffer);
        new_node->next = cache->head;
        cache->head = new_node;

        cache->size++;
    }

    fclose(data);
    return 0;
}

int update_data(char *data)//crea o actualiza el archivo data.txt
{
    FILE *cachedata = fopen("cache/data.txt", "a");
    if (cachedata == NULL)
    {
        printf("Error al abrir el archivo data.txt update\n");
        return -1;
    }
    fprintf(cachedata, "%s\n", data);
    fclose(cachedata);

    return 0;
}

void swap(char **a, char **b) {
    char *temp = *a;
    *a = *b;
    *b = temp;
}

int isFull(Cache_ *cache) {
    return cache->size >= cache->capacity;
}