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
    Node_ *head;
    Node_ *tail;
    int size;
    int capacity;
} Cache_;


#endif