#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H


typedef struct Node {
    char *data;
    struct Node *next;
    struct Node *prev;
} Node_;


typedef struct Cache {
    char **data;
    int capacity;
    int size;
    Node_ *head;
    Node_ *tail;
} Cache_;/**/


#endif