#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdarg.h>
#ifdef _WIN32
    #include <direct.h>
    #include <io.h>
    #define ACCESS _access
    #define F_OK 0
#else
    #include <unistd.h>
    #include <sys/stat.h>
    #define ACCESS access
#endif
#include "structures.h"


int create_folder()//crear carpeta cache
{
    if(system("mkdir cache") != 0)//comando para crear la carpeta cache
    {
        printf("Error al crear la carpeta 'files'\n");
        return -1;
    }
    return 0;
}

int load_cachedata(Cache_ *cache)//carga metadata.txt en la estructura Cache_
{
    if (!cache)
    {
        printf("Error: cache es NULL\n");
        return -1;
    }
    FILE *cachedata = fopen("cache/cachedata.txt", "r");
    if (!cachedata)
    {
        return -1;
    }
    char buffer[256];

    while (fgets(buffer, sizeof(buffer), cachedata))//lee linea por linea
    {
        if (sscanf(buffer, "Capacidad: %d", &cache->capacity) == 1)
        {
            continue;
        }
        if (sscanf(buffer, "Tamano actual: %d", &cache->size) == 1)
        {
            continue;
        }
    }
    
    fclose(cachedata);
    return 0;
}

int update_cache(Cache_ *cache)//crea o actualiza el archivo metadata.txt
{
    if(!cache)
    {
        printf("Error: cache es NULL\n");
        return -1;
    }
    FILE *cachedata = fopen("cache/cachedata.txt", "w");
    if (!cachedata)
    {
        printf("Error al abrir el archivo metadata.txt\n");
        return -1;
    }

    //escribe la capacidad y el tamaño actual del cache
    fprintf(cachedata, "Capacidad: %d\n", cache->capacity);
    fprintf(cachedata, "Tamano actual: %d\n", cache->size);

    fclose(cachedata);
    return 0;
}

int search_data(Cache_ *cache, char *data)//busca un dato en el cache
{
    if(!cache|| !cache->head)
    {
        return -1;
    }

    //recorre los nodos del cache
    Node_ *current = cache->head;
    while(current != NULL)
    {
        if(strcmp(current->data, data) == 0)
        {
            return 1; //dato encontrado
        }
        current = current->next;
    }

    return 0; //dato no encontrado
}

int rewrite_data(Cache_ *cache)//reescribe el archivo data.txt cuando el cache esta lleno
{
    if(!cache || !cache->head)
    {
        printf("Error: cache es NULL\n");
        return -1;
    }
    FILE *data = fopen("cache/data.txt", "w");
    if (!data)
    {
        printf("Error al abrir el archivo data.txt para reescribir\n");
        return -1;
    }

    int count = 0;
    Node_ *current = cache->head;
    while(current != NULL && count < cache->capacity)//cuenta los nodos hasta la capacidad del cache
    {
        count++;
        current = current->next;
    }

    Node_ **nodes = malloc(count * sizeof(Node_*));//arreglo para almacenar los nodos
    if (!nodes)
    {
        fclose(data);
        printf("Error al asignar memoria\n");
        return -1;
    }

    current = cache->head;//reinicia el puntero al inicio del cache
    for (int i = 0; i < count; i++)//almacena los nodos en el arreglo
    {
        nodes[i] = current;
        current = current->next;
    }

    for (int i = count - 1; i >= 0; i--)//escribe los datos en el archivo data.txt en orden
    {
        if (nodes[i]->data != NULL)
        {
            fprintf(data, "%s\n", nodes[i]->data);
        }
    }

    free(nodes);//libera la memoria del arreglo
    fclose(data);
    return 0;
}

int load_data(Cache_ *cache)//carga data.txt en la estructura Cache_
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

    while (fgets(buffer, sizeof(buffer), data) && cache->size < cache->capacity)//lee linea por linea hasta la capacidad del cache
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
    if (!cachedata)
    {
        printf("Error al abrir el archivo data.txt update\n");
        return -1;
    }
    fprintf(cachedata, "%s\n", data);//escribe el nuevo dato al final del archivo
    fclose(cachedata);

    return 0;
}

void swap(Cache_ *cache, char *data)
{
    Node_ *current = cache->head;
    Node_ *prev = NULL;

    while(current->next != NULL)//recorre los nodos del cache
    {
        prev = current;
        current = current->next;

        if(strcmp(current->data, data) == 0)
        {
            //mover el nodo al frente
            if(prev != NULL) {
                prev->next = current->next;
                current->next = cache->head;
                cache->head = current;
            }
            return;
        }
    }
}

int DirExists(const char *path)
{
    struct stat info;

    if (stat(path, &info) != 0) {
        // No se pudo acceder a la ruta
        return 0;
    } else if (info.st_mode & S_IFDIR) {
        // Es un directorio
        return 1;
    } else {
        // Existe, pero no es un directorio
        return 0;
    }
}
