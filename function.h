#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdarg.h>
#include "structures.h"

int create_folder()
{
    if(system("mkdir cache") != 0) {
        printf("Error al crear la carpeta 'files'\n");
        return -1;
    }
    return 0;
}

int change_folder(const char *path)
{
    if(chdir(path) != 0) {
        printf("Error al abrir la carpeta %s\n", path);
        return 1;
    }
    return 0;
}

int load_cachedata(Cache_ *cache)
{
    if (cache == NULL) {
        printf("Error: cache es NULL\n");
        return -1;
    }

    printf("Cargando cachedata...\n");
    FILE *cachedata = fopen("cache/metadata.txt", "r");
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
    
    printf("Cachedata cargado: Capacidad=%d, Tamano actual=%d\n", cache->capacity, cache->size);
    fclose(cachedata);
    return 0;
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

int update_cachedata(Cache_ *cache)//crea o actualiza el archivo metadata.txt
{
    FILE *cachedata = fopen("cache/metadata.txt", "w");
    if (cachedata == NULL) {
        printf("Error al abrir el archivo metadata.txt\n");
        return -1;
    }
    fprintf(cachedata, "Capacidad: %d\n", cache->capacity);
    fprintf(cachedata, "Tamano actual: %d\n", cache->size);
    fprintf(cachedata, "Orden de datos (de más reciente a menos reciente):\n");
    fclose(cachedata);
    return 0;
}

int isFull(Cache_ *cache) {
    return cache->size >= cache->capacity;
}