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

int change_folder(const char *path)//cambiar carpeta
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
    
    //printf("Cachedata cargado: Capacidad=%d, Tamano actual=%d\n", cache->capacity, cache->size);
    fclose(cachedata);
    return 0;
}

int load_data(Cache_ *cache)
{
    FILE *data = fopen("cache/data.txt", "r");
    if (data == NULL)
    {
        printf("Error al abrir el archivo data.txt\n");
        return -1;
    }
    char buffer[256];
    int index = 0;
    cache->data = (char **)malloc(cache->capacity * sizeof(char *));
    if (cache->data == NULL)
    {
        printf("Error al asignar memoria para los datos del cache\n");
        fclose(data);
        return -1;
    }
    else
    {
        cache->data[index] = strdup(buffer);    
    }
    while (fgets(buffer, sizeof(buffer), data) && index <= cache->size)
    {
        printf("4");
        buffer[strcspn(buffer, "\n")] = 0; // Eliminar el salto de línea
        cache->data[index] = strdup(buffer);
        index++;
    }/**/
    fclose(data);
    return 0;
}

int update_data(char *data)
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

void swap(char **a, char **b) {
    char *temp = *a;
    *a = *b;
    *b = temp;
}

int isFull(Cache_ *cache) {
    return cache->size >= cache->capacity;
}