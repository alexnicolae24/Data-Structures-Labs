#ifndef SORTED_LIST_H
#define SORTED_LIST_H

#include <stdlib.h>
#include <assert.h>

/*
    IMPORTANT!

    As we stick to pure C, we cannot use templates. We will just asume
    some type T was previously defined.
*/

// -----------------------------------------------------------------------------

typedef struct node {
    T value;
    struct node* next;
} TNode, *TSortedList;

// TODO : Cerința 1 & Cerința 2

TSortedList create(T value) {
    TSortedList node = malloc(sizeof(TNode));
    node -> value = value;
    node -> next = NULL;
    return node;
}

T isEmpty(TSortedList list) {
    if(list == NULL) 
        return 1;
    else
        return 0;
}

TSortedList insert(TSortedList list, T x) {
    // TODO (se va completa la Cerința 2)
    TSortedList newNode = create(x);
    if(list == NULL){
       return newNode;
    }
    if(x < list -> value){
       newNode -> next = list;
       list = newNode;
       return newNode;
    }
    TSortedList previous,current;
    previous = list;
    current = list -> next;
    while(current != NULL){
        if(x < current -> value){
            newNode -> next = current ;
            previous -> next = newNode;
            return list;
        }
        previous = current;
        current = current->next;
    }
    previous -> next = newNode;
    return list;
}

long  length(TSortedList list) {
    long nr = 0;
    TSortedList current = malloc(sizeof(TNode));
    current = list;
    while(current != NULL){ 
        nr++;
        current = current -> next;
    }
    return nr;
}

T contains(TSortedList list, T x) {
    while (list != NULL){ 
        if(list->value == x)
           return 1;
        list = list -> next;
    }
    return 0;
}

TSortedList deleteOnce(TSortedList list, T x) {
    if(list == NULL){
        free(list);
       return list -> next;
    }
    TSortedList previous, current;
    previous = list;
    current = list -> next;
    while(current != NULL){
        if(x == current -> value){
            previous -> next = current -> next;
            free(current);
            return list;
        }
        previous = current;
        current = current->next;
    }
    previous -> next = NULL;
    return list; 
}

T getNth(TSortedList list , T N) {
    int count = 1;
    while (list != NULL) {
        if (count == N){
            return (list -> value);
        }
        count++;
        list = list -> next;
    }
}

TSortedList freeTSortedList(TSortedList list) {
    TSortedList tmp;
    while (list != NULL){
       tmp = list;
       list = list -> next;
       free(tmp);
    }
    return NULL;
}

#endif
