#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL; 
    new->next = NULL;
    return new;
}

List * createList() {
    List* list = (List*)malloc(sizeof(List));
    
    list->head = NULL;
    list->tail = NULL;
    list->current = NULL;
  
    return list;
}

void * firstList(List * list) {

    if(list->head == NULL){  //Lista vacia
      list->current = NULL;
      return NULL;
    }
  
    list->current = list->head;
    return list->head->data;
}

void * nextList(List * list) {

    if(list->head == NULL|| list->current == NULL || list->current->next == NULL){
      list->current = NULL;
      return NULL;
    }
  
    void *dato = list->current->next->data;
    list->current = list->current->next;
      
    return dato;
}

void * lastList(List * list) {
    if(list->head == NULL || list->tail == NULL){  //Lista vacia
      list->current = NULL;
      return NULL;
    }

    list->current = list->tail;
    return list->tail->data;
}

void * prevList(List * list) {
    if(list->tail == NULL|| list->current == NULL || list->current->prev == NULL){
      list->current = NULL;
      return NULL;
    }
  
    void *dato = list->current->prev->data;
    list->current = list->current->prev;
      
    return dato;
}

void pushFront(List * list, void * data) {
    Node *nuevoNodo = createNode(data);
  
    if(nuevoNodo == NULL){
      return;
    }

    nuevoNodo->next = list->head;
  
    if(list->head != NULL){
      list->head->prev = nuevoNodo;
    }
    else{
      list->tail = nuevoNodo;
    }
    
    list->head = nuevoNodo;
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
    Node *nuevoNodo = createNode(data);
  
    if(nuevoNodo == NULL){
      return;
    }

    nuevoNodo->prev = list->current;
  
    if(list->current != NULL){
      nuevoNodo->next = list->current->next;
      
      if(list->current->next != NULL){
        list->current->next->prev = nuevoNodo;
        
      } else{
      list->tail = nuevoNodo;
    }
      
    list->current->next = nuevoNodo;
    } else{
      list->head = nuevoNodo;
      list->tail = nuevoNodo;
    }

    list->current = nuevoNodo;
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {

    if(list->current == NULL){
      return NULL;
    }
    
    Node *nodoEliminar = list->current;
    void *data = nodoEliminar->data;
  
    if(nodoEliminar->prev != NULL){
        nodoEliminar->prev->next = nodoEliminar->next;
    }
    else{
        list->head = nodoEliminar->next;
    }

    if(nodoEliminar->next != NULL){
        nodoEliminar->next->prev = nodoEliminar->prev;
    }
    else{
        list->tail = nodoEliminar->prev;
    }

    list->current = nodoEliminar->next;
    free(nodoEliminar);
  
    return data; 
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}