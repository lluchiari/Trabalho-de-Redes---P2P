#ifndef MY_LIST_H
#define MY_LIST_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "myerror.h"

#define NAME_LENGTH 100

typedef int data_type;

typedef struct Nodes node;

typedef struct list list_t;

//Creates a Empty List
list_t *createList();

//Iserts one element on a List at the last position.
int insertList(list_t *, node *, int);

//Pull an element from the List
int pull(list_t *, data_type *, int);

//Serch for a name and returns their position at the list
int serch_by_name(list_t *, char name[NAME_LENGTH]);

//Free a List previousily allocated
//Returns 1 if the operation was sucessful. Else return 0
int freedom(list_t *L);

//Removes a name from a file
int remove_name(list_t *L, int position, data_type *value);

int verifica(list_t *L, int part_tam);

//Otimizes
void otimiza(list_t *L, int *Espaco_Livre);

#endif
