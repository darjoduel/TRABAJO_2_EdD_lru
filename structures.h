#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

// Definicion de la estructura del nodo 
typedef struct Node {
    char *data;
    struct Node *next;
    struct Node *prev;
} Node_;

//Definicion de la estructura del cache
typedef struct Cache {
    char **data;
    int capacity;
    int size;
    Node_ *head;
    Node_ *tail;
} Cache_;


#endif