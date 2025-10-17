#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H


typedef struct Node {
    char *data;
    struct Node *next;
} Node_;


typedef struct Cache {
    char **data;
    int capacity;
    int size;
    Node_ *head;
} Cache_;/**/


#endif