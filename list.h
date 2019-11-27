#ifndef LAB3_LIST_H
#define LAB3_LIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    struct Node *prev;
    struct Node *next;
    char *value;
} Node;

typedef struct{
    Node* head;
    Node* tail;
    int size;
} List;

/**
 * @list concepts
 * */

void list_init(List* list);
void list_add_value(List* list, int position, char* value);
void list_print(Node* node, int step);
void list_remove_value(List* list, int position);
Node* list_rewind_to(List* list, int position);
void list_delete(List* list);

void list_add_to_front(List* list, char *value);
void list_add_to_back(List* list, char *value);

/**
 * @node concepts
 * */

void node_init(Node* node);
void node_print(Node* node);
void node_remove(Node* node);


#endif //LAB3_LIST_H