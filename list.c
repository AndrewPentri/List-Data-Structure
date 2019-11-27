#include "list.h"
#include <string.h>

/*  List functions  */
void list_init(List* list) {
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

void list_add_value(List* list, int position, char* value) {
    Node *temp = (Node *) malloc(sizeof(Node));
    node_init(temp);

    temp->value = (char *) malloc((strlen(value)+1) * sizeof(char));
    strcpy(temp->value, value);

    if(position != 0 && list->size != 0) {
        Node* ptr = list_rewind_to(list, position);
    /*  If position bigger then list size  */
        if(ptr == NULL) {
            temp->next = NULL;
            temp->prev = list->tail;
            list->tail->next = temp;
            list->tail = temp;
        }
        else {
    /*  If it is not the last one    */
            if(ptr->next != NULL) {
                temp->prev = ptr->prev;
                ptr->prev->next = temp;
                ptr->prev = temp;
                temp->next = ptr;
            }
            else {
                temp->next = list->tail;
                list->tail->prev->next = temp;
                temp->prev = list->tail->prev;
                list->tail->prev = temp;
            }
        }
    }
    /*  If it should be on first place    */
    else {
        if(list->size == 0) {
            temp->next = NULL;
            list->tail = temp;
        }
        else {
            temp->next = list->head;
            temp->next->prev = temp;
        }
        temp->prev = NULL;
        list->head = temp;
    }

    list->size++;
}

void list_remove_value(List* list, int position) {
    if(position > list->size - 1) {
        return;
    }
    Node* ptr = list_rewind_to(list, position);
    if(list->size > 1) {
        if(ptr->prev != NULL) {
            ptr->prev->next = ptr->next;
        }
        else {
            list->head = ptr->next;
            ptr->next->prev = NULL;
        }
        if(ptr->next != NULL) {
            ptr->next->prev = ptr->prev;
        }
        else {
            list->tail = ptr->prev;
            ptr->prev->next = NULL;
        }
    }
    else {
        list->head = NULL;
        list->tail = NULL;
    }

    node_remove(ptr);

    free(ptr);

    list->size--;
}

void list_delete(List* list) {
    for(int i = list->size - 1; i >= 0 ; i--) {
        list_remove_value(list, i);
    }
}

Node* list_rewind_to(List* list, int position) {
    if(position > list->size - 1 && list->size > 0) {
        return NULL;
    }

    Node* ptr = list->head;

    for(int i = 0; i < position; i++) {
        ptr = ptr->next;
    }

    return ptr;
}

void list_print(Node* node, int step) {
    if(node->value == NULL) {
        printf("Nothing to show. List is empty.");
        return;
    }
    node_print(node);
    if(node->next == NULL) {
        return;
    }
    list_print(node->next, step - 1);
}

void list_add_to_front(List* list, char* value) {
    list_add_value(list, 0, value);
}

void list_add_to_back(List* list, char* value) {
    list_add_value(list, list->size, value);
}

/*  Node functions  */
void node_init(Node* node) {
    node->next = NULL;
    node->prev = NULL;
    node->value = NULL;
}

void node_print(Node* node) {
    printf("%s(0x%p)<-%s(0x%p)->%s(0x%p)\n",
            node->prev != NULL ? node->prev->value : "NULL", node->prev,
            node->value, node,
            node->next != NULL ? node->next->value : "NULL" , node->next);
}

void node_remove(Node* node) {
    free(node->value);
    node->next = NULL;
    node->prev = NULL;
    free(node);
}