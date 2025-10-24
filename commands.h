#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structures.h"
#include "function.h"
#include <string.h>

Cache_ *lru_create(int capacity) // Comando de creacion de cache
{
    if (capacity < 5)//filtro de capacidad minima
    {
        printf("La capacidad minima es 5\n");
        capacity = 5;
    }

    printf("Creando cache de capacidad %d\n", capacity);    

    Cache_ *cache = (Cache_ *)malloc(sizeof(Cache_));//asigna memoria para la estructura Cache_
    if (!cache)
    {
        printf("Error al asignar memoria para el cache\n");
        return NULL;
    }

    cache->data = (char **)malloc(capacity * sizeof(char *));//asigna memoria para los datos del cache
    if (!cache->data)
    {
        printf("Error al asignar memoria para los datos del cache\n");
        free(cache);
        return NULL;
    }

    //inicializa los campos de la estructura Cache_
    cache->capacity = capacity;
    cache->size = 0;
    cache->head = NULL;

    //crear carpeta cache
    create_folder();

    //crear archivo data.txt vacio
    FILE *data = fopen("cache/data.txt", "w");
    fclose(data);

    //crear archivo metadata.txt
    update_cache(cache);
    printf("Cache creado con exito\n");
    return cache;
}

Cache_* lru_load_cache() // Carga el cache existente
{
    Cache_ *cache = (Cache_ *)malloc(sizeof(Cache_));
    if (!cache) {
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

int lru_add(Cache_ *cache, char *data) // Comando para agregar un dato al cache
{
    if(!cache)
    {
        printf("Cache no inicializado. Use 'create <tamano_cache>' para crear uno.\n");
        return -1;
    }
    if(search_data(cache, data) == 1)//verifica si el dato ya existe en el cache
    {
        printf("El dato '%s' ya existe en el cache. No se agrego.\n", data);
        return -1;
    }
    
    Node_ *TempNode = (Node_ *)malloc(sizeof(Node_));//crea un nuevo nodo
    if(TempNode == NULL)
    {
        printf("Error al asignar memoria para el nuevo nodo\n");
        return -1;
    }
    //une el nuevo nodo al frente del cache
    TempNode->data = strdup(data);
    TempNode->next = cache->head;
    cache->head = TempNode;

    if (cache->size < cache->capacity)//si el cache no esta lleno
    {
        cache->size++;
        printf("Dato '%s' agregado al cache. Tamano actual: %d\n", data, cache->size);
        update_data(data);
    }
    else//si el cache esta lleno
    {
        printf("Cache lleno. Reescribiendo data.txt...\n");
        Node_ *current = cache->head;
        Node_ *prev = NULL;

        if(cache->head == NULL)
        {
            printf("Error: el cache esta vacio, no se puede eliminar ningun dato\n");
            return -1;
        }
        
        while(current->next != NULL)//recorre hasta el ultimo nodo
        {
            prev = current;
            current = current->next;
        }

        printf("Eliminando dato menos reciente: '%s'\n", current->data);

        if(prev != NULL)//desvincula el ultimo nodo
        {
            prev->next = NULL;
            free(current->data);
            free(current);
        }

        rewrite_data(cache);//reescribe el archivo data.txt
        printf("Cache lleno. Dato '%s' agregado al cache, el dato menos reciente fue eliminado.\n", data);
    }
    update_cache(cache);//actualiza el archivo metadata.txt
    return 0;
}

int lru_all(Cache_ *cache) // Comando para mostrar todos los datos en el cache
{
    if(!cache || !cache->head)
    {
        printf("Cache vacio.\n");
        return -1;
    }

    Node_ *current = cache->head;
    int index = 1;

    while(current != NULL)//recorre todos los nodos del cache
    {
        if(current->data == NULL)//si el dato es NULL
        {
            printf("[%d] Dato NULL\n", index);
        }
        else
        {
            printf("%s", current->data);//imprime el dato
        }
        if(index != cache->size)
        {
            printf(" - ");//separa los datos con un guion
        }
        current = current->next;
        index++;
    }

    return 0;
}

int lru_search(Cache_ *cache, char *data) // Comando de busqueda de un dato en el cache
{
   if(!cache || !cache->head)
    {
        printf("Cache vacio.\n");
        return -1;
    }

    if(search_data(cache, data) == 0)//si el dato no se encuentra
    {
        printf("Dato '%s' no encontrado en el cache.\n", data);
        return -1;
    }
    else//si el dato se encuentra
    {
        printf("Dato '%s' encontrado en el cache.\n", data);
    }

    return 0;
}

int lru_get(Cache_ *cache, char *data) // Comandos para obtener un dato del cache
{
    if(!cache || !cache->head)
    {
        printf("Cache vacio.\n");
        return -1;
    } 

    if(search_data(cache, data) == 0)//si el dato no se encuentra
    {
        printf("Dato '%s' no encontrado en el cache.\n", data);
        return -1;
    }
    
    swap(cache, data);//mueve el dato al frente del cache
    rewrite_data(cache);//reescribe el archivo data.txt
    printf("Dato '%s' movido a la posicion mas reciente del cache.\n", data);

    return 0;
}

int lru_exit() // Comando para salir y eliminar el cache
{
    if(!DirExists("cache"))//verifica si la carpeta cache existe
    {
        printf("No hay cache para eliminar.\n");
        return -1;
    }
    #ifdef _WIN32//comando para eliminar la carpeta cache en Windows
        if(system("rmdir /S /Q cache") == -1)
        {
            printf("Error al eliminar la carpeta cache\n");
        }
        else
        {
            printf("Carpeta cache eliminada con exito\n");
        }
    #else//comando para eliminar la carpeta cache en Linux/Mac
        if(system("rm -rf cache") == -1)
        {
            printf("Error al eliminar la carpeta cache\n");
        }
        else
        {
            printf("Carpeta cache eliminada con exito\n");
        }   

    #endif

    return 0;
}