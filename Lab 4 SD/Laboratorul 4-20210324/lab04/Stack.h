#ifndef STACK_H_
#define STACK_H_

#include <stdio.h>
#include <stdlib.h>



typedef struct StackNode{
	Item elem;
	struct StackNode *next;
}StackNode;

typedef StackNode TCelSt; // Redenumirea unui nod la notatiile din curs 
typedef StackNode *ACelSt; // Redenumirea unui pointer la nod la notatiile din curs

typedef struct Stack{
	StackNode* head;  // Varful stivei
	long size; // Numarul de elemente din stiva
}Stack;

typedef Stack TStiva; // Redenumirea stivei la notatiile din curs
typedef Stack *ASt;//  // Redenumirea unui pointer la stiva la notatiile din curs

Stack* createStack(void){
	// TODO: Cerinta 1
	Stack *stack = (Stack*)malloc(sizeof(Stack));
	stack -> head = NULL;
	stack -> size = 0;
	return stack;
}

int isStackEmpty(Stack* stack){
	// TODO: Cerinta 1
	if(stack -> head == NULL)
	   return 1;
	else
	   return 0;
}

void push(Stack *stack, Item elem){
	// TODO: Cerinta 1
	if (stack -> size >= 1000)
    {
        return;
    }
    StackNode *newnode = (StackNode*) malloc(sizeof(StackNode));
    newnode -> elem = elem;
	newnode -> next = stack -> head; 
	stack -> head = newnode;     
    stack -> size++;
}

Item top(Stack *stack){	
	// TODO: Cerinta 1
	return stack -> head -> elem;
} 

void pop(Stack *stack){
	// TODO: Cerinta 1
	StackNode *top ;
	top = stack -> head;
    if (top == NULL)
    {
        return;
    }
    else
        top = top -> next;
    free(stack -> head);
    stack -> head = top;
    stack -> size--;
}

void destroyStack(Stack *stack){
	// TODO: Cerinta 1
	StackNode *top,*top1 ;
	top = stack -> head;
    while (top != NULL)
    {
		top1 = top -> next;
		free(top);
		top = top1;
    }
	free(top);
    stack -> head = NULL;
    stack -> size = 0;
	free(stack);
}

#endif 
