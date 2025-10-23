#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structures.h"
#include "function.h"
#include <string.h>

Cache_ *lru_create(int capacity) // Comando de creación de cache
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

Cache_* lru_load_cache() // Carga el cache existente
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

int lru_add(Cache_ *cache, char *data) // Comando para agregar un dato al cache
{
    if(cache == NULL)
    {
        printf("Cache no inicializado. Use 'create <tamano_cache>' para crear uno.\n");
        return -1;
    }
    if(search_data(cache, data) == 1)
    {
        printf("El dato '%s' ya existe en el cache. No se agrego.\n", data);
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
    update_cache(cache);
    return 0;
}

int lru_all(Cache_ *cache) // Comando para mostrar todos los datos en el cache
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
            printf("%s", current->data);
        }
        if(index != cache->size)
        {
            printf(" - ");
        }
        current = current->next;
        index++;
    }

    return 0;
}

int lru_search(Cache_ *cache, char *data) // Comando de búsqueda de un dato en el cache
{
    if(cache == NULL || cache->head == NULL)
    {
        printf("Cache vacio. Resultado: -1\n");
        return -1;
    }

    Node_ *current = cache->head;
    int posicion = 1; // Empezamos a contar desde 1 para la posición

    while(current != NULL)
    {
        // Compara el dato actual con el buscado
        if(strcmp(current->data, data) == 0)
        {
            // ¡Encontrado! Imprime la posición 
            printf("Dato '%s' encontrado en la posicion: %d\n", data, posicion);
            return 0; // Termina la función con éxito
        }
        
        // Si no es el dato, avanza al siguiente nodo
        current = current->next;
        posicion++; // Incrementa el contador de posición
    }

    // Si el bucle termina, significa que no se encontró
    printf("Dato '%s' no encontrado en el cache. Resultado: -1\n", data);
    return -1; // Retorna -1 (como valor de error)
}

int lru_get(Cache_ *cache, char *data) // Comandos para obtener un dato del cache
{
    if(cache == NULL || cache->head == NULL)
    {
        printf("Cache vacio.\n");
        return -1;
    } 

    if(search_data(cache, data) == 0)
    {
        printf("Dato '%s' no encontrado en el cache.\n", data);
        return -1;
    }
    //necesito un swap que recorra desde el nodo encontrado hasta el head
    
    swap(cache, data);
    rewrite_data(cache);
    printf("Dato '%s' movido a la posicion mas reciente del cache.\n", data);

    return 0;
}

int lru_exit() // Comando para salir y eliminar el cache
{
    printf("Eliminando cache y saliendo del programa...\n");

    #ifdef _WIN32
        if(system("rmdir /S /Q cache") == -1)
        {
            printf("Error al eliminar la carpeta cache\n");
        }
        else
        {
            printf("Carpeta cache eliminada con exito\n");
        }
    #else
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