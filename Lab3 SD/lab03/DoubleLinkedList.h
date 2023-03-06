#ifndef _DOUBLE_LINKED_LIST_H_
#define _DOUBLE_LINKED_LIST_H_
#include <stdlib.h>
/*
  IMPORTANT!

  As we stick to pure C, we cannot use templates. We will just asume
  some type T was previously defined.
*/

// -----------------------------------------------------------------------------
/**
 *  Linked list representation -- R2 Curs2 (Slide 8)
 */
typedef struct ListNode{
	Item elem; // Stored node value
	struct ListNode* next; // link to next node
	struct ListNode* prev; // link to prev node
} ListNode;

/**
 *  Double linked list representation -- desen Curs 3 (Slide 19)
 */
typedef struct List{
	ListNode* first; // link to the first node
	ListNode* last; // link to the last node
}List;
// -----------------------------------------------------------------------------

/**
 * Create a new node
 *  [input]: Item
 *  [output]: List*
 */
ListNode *createNode(Item elem){
	// TODO: Cerinta 1a
	ListNode *node = malloc(sizeof(ListNode));
    node -> elem = elem;
    node -> next = NULL;
	node -> prev = NULL;
    return node;
}

/**
 * Create a new (empty)  list  -- Silde-urile 13/14 Curs 2
 *  [input]: None
 *  [output]: List*
 */
List* createList(void){
	// TODO: Cerinta 1a
    List *list = (List*)calloc(1,sizeof(List));
    return list;
}
// -----------------------------------------------------------------------------


/**
 * Determines if the list is empty
 *  [input]: List*
 *  [output]: 1 - empty/ 0 - not empty
 */
int isEmpty(List *list){
	// TODO: Cerinta 1b
	if((list -> first == NULL) && (list -> last == NULL))
 	   return 1;
 	else
	   return 0;
}
// -----------------------------------------------------------------------------


/**
 * Determines if a list contains a specified element
 *  [input]: List*, Item
 *  [output]: int (1 - contains/ 0 - not contains)
 */
int contains(List *list, Item elem){
	// TODO: Cerinta 1c
    for(ListNode* base = list -> first; base != NULL;base = base -> next){
        if(base-> elem == elem)
          return 1;     
	}
	return 0;
}
// -----------------------------------------------------------------------------


/**
 * Compute list length
 *  [input]: List*
 *  [output]: int
 */
int length(List *list){
	// TODO: Cerinta 1f
	int size = 0;
    for(ListNode* base = list -> first; base != NULL;base = base -> next){
        size++;
    }
    return size;
}
// -----------------------------------------------------------------------------


/**
 * Insert a new element in the list at the specified position.
 * Note: Position numbering starts with the position at index zero
 *  [input]: List*, Item, int
 *  [output]: void
 */
void insertAt(List* list, Item elem, int pos){
	// TODO: Cerinta 1d
	int i = 0;
 	ListNode *temp;
 	ListNode *newnode = createNode(elem);
 	int l = length(list);
 	if(pos < 0 || pos > (l+1)){
 		  return;
	}
	else{
	    if(pos == 0){
 		    list -> first -> prev = newnode;
 		    newnode -> next = list -> first;
 		    list -> first = newnode;
 	    }
		else{
	        if(pos == l){
		        list -> last -> next = newnode;
 		        newnode -> prev = list -> last;
		        list -> last = newnode;
		    }
 		    else{
                temp = list -> first;
 			    while(i < pos){
 				     temp =temp -> next;
 				     i++;
 			    }
 			    newnode -> prev = temp;
 			    newnode -> next = temp -> next;
 			    temp -> next = newnode;
		        newnode -> next -> prev = newnode;
 		    }
		}
	}
}
// -----------------------------------------------------------------------------


/**
 * Delete the first element instance form a list.
 *  [input]: List*, Item
 *  [output]: void
 */
void deleteOnce(List *list, Item elem){
	// Guard against young player errors
	if(list == NULL) return;

	//TODO: Cerinta 1e
}
// -----------------------------------------------------------------------------


/**
 * Destroy a list.
 *  [input]: List*
 *  [output]: void
 */
List* destroyList(List* list){
	//TODO: Cerinta 1g
	ListNode *tail,*base;
 	tail = list -> last;
 	while(tail != NULL){
 	      base = tail;
 		  tail = tail -> prev;
 		  free(base);
 	}
 	free(list);
	return NULL;
}
// -----------------------------------------------------------------------------


#endif //_DOUBLE_LINKED_LIST_H_
