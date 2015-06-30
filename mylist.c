#include "mylist.h"

struct list
{
    node *start, *end;
    int qtyElements;
};

struct Nodes{
    data_type info;
    char name[NAME_LENGTH];
    node *next;
};

//Creates a Empty List
list_t *createList()
{
    list_t *aux;
    aux = (list_t *) malloc(sizeof(list_t));
    if(aux == NULL) {return NULL;}
    else
    {
        aux->start = NULL;
        aux->end = NULL;
    }
    aux->qtyElements = 0;
    return aux;
}

//Iserts one element on a List at the last position.
int insertList(list_t *L, node *aux, int position)
{
    node *find, *aux2;
    int count = 0;

    if(L == NULL){return 0;}
    if(aux == NULL){return 0;}

    //Fila Vazia. Inserir o elemento na primeira posição//
    if(L->start == NULL)
    {
        aux->next = NULL;
        L->start = aux;
        L->end = aux;
        L->qtyElements++;
        return 1;
    }
    //Position < 0 or Position > Quanty of Elements at the line --> inserts at the end//
    else if(position < 0 || position > L->qtyElements)
    {
        aux->next = L->end;
        L->end = aux;
        L->qtyElements++;
        return 1;
    }
    //First Position//
    else if(position == 0)
    {
        aux->next = L->start;
        L->start = aux;
        L->qtyElements++;
        return 1;
    }
    //Other Valid Position//
    else
    {
        find = L->start;
        while(find != NULL && count < position-1)
        {
            find = find->next;
            count++;
        }
        if(find != NULL){return ERROR;}
        {
            aux->next = find->next;
            find->next = aux;
            return 1;
        }
    }
    return ERROR;
}

//Pull an element from the List
int pull(list_t *L, data_type *x, int position)
{
    //Verifica se a Lista existe e se ela está vazia
    if(L == NULL || L->start == NULL){return 0;}
    int count = 1;
    node *aux, *aux2;
    aux = L->start;
    //Verify id its a valid position
    if(position<=0){return 0;}
    if(L->start != L->end)
    {
        while(count < position-1)   {aux = aux->next; count++;}
        if(aux->next == NULL){return 0;}
    }
    else
    {
        if(position != 1){return 0;}
        *x = aux->info;
        L->start = L->end = NULL;
        free(aux);
        return 1;
    }
    if(position == 1)
    {
        *x = aux->info;
        L->start = aux->next;
        free(aux);
        return 1;
    }
    else
    {
        aux2 = aux->next;
        *x = aux2->info;
        aux->next = aux2->next;
        free(aux2);
        return 1;
    }
    return 0;
}

//Serch for a name and returns their position at the list
int serch_by_name(list_t *L, char name[NAME_LENGTH])
{
    if(L == NULL){return -1;}
    int count = 1;
    node *aux = L->start;
    while(aux != NULL)
    {
        if(!strcmp((aux->name), name)){return count;}
        aux = aux->next;
        count++;
    }
    return -1;
}

//Free a List previousily allocated
int freedom(list_t *L)
{
    node *aux;
    if(L == NULL){return 1;}
    else if(L->start != NULL)
    {
        aux = L->start;
        while(aux != NULL)
        {
            L->start = L->start->next;
            free(aux);
            aux = L->start;
        }
    }
    free(L);
    return 1;
}

//Removes a name from a file
int remove_name(list_t *L, int position, data_type *value)
{
    if(L == NULL || L->start == NULL){return 0;}
    int count = 1;
    node *aux = L->start;
    if(L->start != L->end)
    {
        while(aux != NULL && count++ < position)   {aux = aux->next;}
    }
    *value = aux->info;
    aux->name[0] = '\0';
    return 1;
}

int verifica(list_t *L, int part_tam)
{
    int sum = 0, sum_empty = 0, aux_sum = 0, i, turn;
    data_type lenght;
    float p = 0;
    node *aux = L->start;
    while(aux != NULL)
    {
        turn = ((aux->info+sum)/part_tam);
        lenght = aux->info;
        for(i = 0; i<turn; i++)
        {
            //Calcula a diferença
            if(i == 0){aux_sum = (sum+(aux->info))- part_tam;}
            else {lenght = aux_sum; aux_sum = sum-part_tam;}

            if(!strcmp((aux->name), "\0"))
            {
                sum_empty += lenght - aux_sum;
                sum += lenght - aux_sum;
            }

            else {sum = sum + lenght - aux_sum;}

            p = (float)sum_empty/part_tam;
            if(p>0.75 && p<=1){printf("[ ] ");}
            if(p>0.25 && p<=0.75){printf("[-] ");}
            if(p>=0 && p<=0.25){printf("[#] ");}

            if(!strcmp((aux->name), "\0"))
            {sum_empty = 0; sum = aux_sum;}

            else {sum = aux_sum; sum_empty = 0;}
        }
        if(turn == 0)
        {
            if(!strcmp((aux->name), "\0"))
            {sum_empty += aux->info; sum += aux->info;}
            else
            {sum += aux->info;}
        }
        aux = aux->next;
    }
    printf("\n");
    return;
}

void otimiza(list_t *L, int *Espaco_Livre)
{
    int count = 1;
    data_type x;
    node *aux = L->start;
    while(aux->next != NULL)
    {
        //printf("Cycle_%s\n", aux->name);
        if(!strcmp((aux->name), "\0"))
        {
            //printf("1__%s\n", aux->name);
            pull(L, &x, count);
        }
        //printf("Cycle2\n");
        aux = aux->next;
        count++;
    }
    //printf("2\n");
    //printf("3\n");
    aux->info = *Espaco_Livre;
    //printf("Aux->info: %d", aux->info);
    return;
}

